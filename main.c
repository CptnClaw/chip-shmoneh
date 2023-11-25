#include <stdio.h>
#include "config.h"
#include "clock.h"
#include "processor.h"
#include "events.h"


int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("Usage: chip-shmoneh <rom file>\n");
		return 0;
	}

	char *rom_path = argv[1];
	struct Hardware hw;
	hardware_init(&hw, rom_path);

	int running = 1;
	uint8_t instruction[2];
	struct Clock clock;
	clock_init(&clock);
	while (running)
	{
		if (fetch(&hw, instruction) && execute(&hw, instruction) && events_handle(&hw))
		{
			clock_tick(&clock);
		}
		else
		{
			/* Either reached end of memory, instruction failed, or got a quit signal */
			running = 0;
		}

	}
	hardware_free(&hw);
	return 0;
}
