#include <stdio.h>
#include "config.h"
#include "processor.h"
#include "events.h"


int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("Usage: chip-shmoneh <rom file>\n");
		return 1;
	}

	if (!read_config())
	{
		return 1;
	}

	char *rom_path = argv[1];
	struct Hardware hw;
	hardware_init(&hw, rom_path);

	int running = 1;
	uint8_t instruction[2];
	while (running)
	{
		if (hw.is_turned_on &&
			fetch(&hw, instruction) && 
			execute(&hw, instruction))
		{
			clock_tick(&hw);
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
