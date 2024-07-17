#include <stdio.h>
#include "config.h"
#include "processor.h"
#include "events.h"
#include "graphics.h"
#include "clock.h"
#include "commands.h"

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
	hardware_init(&hw, rom_path);
	graphics_init(&gfx, rom_path);
	clock_init(&clk);
	commands_init(&cmd);

	int running = 1;
	uint8_t instruction[2];
	int IPF = CONFIG.INSTRUCTIONS_PER_SECOND / FPS;  // Instuctions per frame
	while (running)
	{
		clock_tick(&clk);
		graphics_render(&gfx, &hw.display);
		timers_step(&hw);
		for (int i=0; i < IPF; i++)
		{
			running = hw.is_turned_on &&
					events_handle(&hw, &cmd) &&
					fetch(&hw, instruction) &&
					execute(&hw, instruction, i);
		}
		clock_tock(&clk, cmd.restrict_speed);
	}
	hardware_free(&hw);
	graphics_free(&gfx);
	return 0;
}
