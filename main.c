#include <stdio.h>
#include "config.h"
#include "processor.h"
#include "events.h"
#include "graphics.h"

// Frames per second
#define FPS  60


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
	hardware_init(&hw, rom_path);
	graphics_init(&gfx, rom_path);

	int running = 1;
	uint8_t instruction[2];
	int IPF = CONFIG.INSTRUCTIONS_PER_SECOND / FPS;  // Instuctions per frame
	while (running)
	{
		for (int i=0; i < IPF; i++)
		{
			if (!hw.is_turned_on ||
				!events_handle(&hw) ||
				!fetch(&hw, instruction) ||
				!execute(&hw, instruction))
			{
				/* Either reached end of memory, instruction failed, or got a quit signal */
				running = 0;
				break;
			}
		}
		graphics_render(&gfx, &hw.display);
		SDL_Delay((int)(1000.0 / FPS + 0.5));
	}
	hardware_free(&hw);
	graphics_free(&gfx);
	return 0;
}
