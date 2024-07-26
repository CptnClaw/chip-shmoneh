#include <stdio.h>
#include "config.h"
#include "processor.h"
#include "events.h"
#include "graphics.h"
#include "clock.h"
#include "commands.h"
#include "rewind.h"

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("Usage: chip-shmoneh <rom file>\n");
		return 1;
	}

	if (!load_config())
	{
		return 1;
	}

	char *rom_path = argv[1];
	struct Hardware hw;
	struct Graphics gfx;
	struct Clock clk;
	struct Commands cmd;
	struct Rewind rewind;
	hardware_init(&hw, rom_path);
	graphics_init(&gfx, rom_path);
	clock_init(&clk);
	commands_init(&cmd);
	rewind_init(&rewind);

	int running = 1;
	uint8_t instruction[2];
	int IPF = CONFIG.INSTRUCTIONS_PER_SECOND / FPS;  // Instuctions per frame
	while (running)
	{
		clock_tick(&clk);
		graphics_render(&gfx, &hw.display, CONFIG.DOUBLE_BUFFERING && !cmd.rewind);
		timers_step(&hw);
		for (int i=0; i < IPF; i++)
		{
			/* Process keyboard and window events */
			running = hw.is_turned_on && 
				events_handle(&hw, &cmd);
			
			
			/* If not paused, run emulation cycle */
			if (!cmd.pause)
			{
				running = running && 
					fetch(&hw, instruction) && execute(&hw, instruction, i);
			}
		}
		
		/* If requested, save or load state */
		if (cmd.save_state)
		{
			save_state(&hw);
			cmd.save_state = 0;
		}
		if (cmd.load_state)
		{
			load_state(&hw);
			cmd.load_state = 0;
		}
		
		/* Handle rewind mechanism */
		if (clk.frame_count % 10 == 0)
		{
			if (cmd.rewind)
			{
				/* Rewind to previous state */
				rewind_pop_state(&rewind, &hw);
			}
			else
			{
				/* Do not rewind, but remember current state for later use */
				rewind_push_state(&rewind, &hw);
			}
		}

		clock_tock(&clk, cmd.restrict_speed);
	}
	graphics_free(&gfx);
	return 0;
}
