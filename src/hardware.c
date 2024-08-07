#include <sys/stat.h>
#include <time.h>
#include <stdlib.h>
#include "hardware.h"
#include "font.h"
#include "events.h"

#define MS_TO_TIMER(ms)		((ms) * TIMERS_RATE / 1000)
#define TIMER_TO_MS(amt)	((amt) * 1000 / TIMERS_RATE)
#define INST_PER_10MS		CONFIG.INSTRUCTIONS_PER_SECOND / 100

int hardware_init(struct Hardware *hw, char *rom_path)
{
	hw->pc = MEM_LOC_PROG;
	hw->index = 0;
	hw->timer_delay = 0;
	hw->timer_sound = 0;
	stack_init(&(hw->stack));
	keyboard_reset(hw);
	display_init(&(hw->display));
	hw->rom_size = load_rom(rom_path, hw->memory);
	if (!hw->rom_size || !load_font(hw->memory))
	{
		return 0;
	}
	srand(time(NULL));
	hw->is_turned_on = 1;
	hw->is_waiting_key = 0;

	int len = strlen(rom_path);
	memcpy(hw->save_file_path, rom_path, sizeof(char) * (len+1));
	memcpy(hw->save_file_path + len - 3, "sav", sizeof(char) * 3); 
	if (CONFIG.AUTOLOAD)
	{
		if (!load_state(hw))
		{
			printf("Failed to autoload state file\n");
		}
	}
	return 1;
}

int load_font(uint8_t *memory)
{
	memcpy(memory + MEM_LOC_FONT, font_data, FONT_SIZE * sizeof(uint8_t));
	return 1;
}

uint16_t load_rom(char *rom_path, uint8_t *memory)
{
	int len = strlen(rom_path);
	if (len > MAX_FILEPATH_SIZE)
	{
		printf("ROM file path too long (%d). Supported up to %d\n", len, MAX_FILEPATH_SIZE);
		return 0;
	}

	if (0 != strcmp(rom_path + len - 4, ".ch8"))
	{
		printf("ROM file path must end in .ch8\n");
		return 0;
	}

	FILE *rom_file = fopen(rom_path, "rb");
	if (!rom_file)
	{
		printf("ROM file not found: %s\n", rom_path);
		return 0;
	}

	struct stat rom_stat;
	if (stat(rom_path, &rom_stat) == -1)
	{
		printf("Cannot read ROM file size: %s\n", rom_path);
		return 0;
	}

	int rom_size = rom_stat.st_size;
	if (rom_size + MEM_LOC_FONT > MEM_SIZE)
	{
		printf("Error: ROM file too large\n");
		return 0;
	}

	/* Read ROM file directly to memory in the correct location */
	memset(memory, 0, sizeof(uint8_t)*MEM_LOC_PROG);
	fread(memory + MEM_LOC_PROG, rom_size * sizeof(uint8_t), 1, rom_file);

	fclose(rom_file);
	return (uint16_t)rom_size;
}

uint16_t gen_random()
{
	return (uint16_t)rand();
}

void keyboard_reset(struct Hardware *hw)
{
	for (int i=0; i<16; i++)
	{
		hw->keyboard[i] = 0;
		hw->prev_keyboard[i] = 0;
	}
}

void keyboard_press(struct Hardware *hw, int key)
{
	hw->keyboard[key] = 1;
}

void keyboard_release(struct Hardware *hw, int key)
{
	hw->keyboard[key] = 0;
}

int is_key_pressed(struct Hardware *hw, int key)
{
	return (hw->keyboard[key] == 1);
}

int did_any_key_release(struct Hardware *hw)
{
	if (hw->is_waiting_key)
	{
		/* Check if a key was up since last time the keyboard was saved */
		for (int i=0; i<16; i++)
		{
			if (hw->prev_keyboard[i] && !hw->keyboard[i])
			{
				hw->is_waiting_key = 0;
				return i;
			}
		}
	}

	/* Save a copy of the current keyboard */
	hw->is_waiting_key = 1;
	for (int i=0; i<16; i++)
	{
		hw->prev_keyboard[i] = hw->keyboard[i];
	}
	return -1;
}

void timers_step(struct Hardware *hw)
{
	if (hw->timer_delay > 0) 	hw->timer_delay--;
	if (hw->timer_sound > 0) 	hw->timer_sound--;
}

int save_state(struct Hardware *hw)
{
	FILE *state_file = fopen(hw->save_file_path, "wb");
	if (!state_file)
	{
		printf("Cannot open state file: %s\n", hw->save_file_path);
		return 0;
	}
	
	fwrite(hw, sizeof(struct Hardware), 1, state_file);
	fclose(state_file);
	return 1;
}

int load_state(struct Hardware *hw)
{
	FILE *state_file = fopen(hw->save_file_path, "rb");
	if (!state_file)
	{
		printf("Cannot open state file: %s\n", hw->save_file_path);
		return 0;
	}

	struct stat state_stat;
	if (stat(hw->save_file_path, &state_stat) == -1)
	{
		printf("Cannot read state file size: %s\n", hw->save_file_path);
		return 0;
	}

	int state_size = state_stat.st_size;
	if (state_size != sizeof(struct Hardware))
	{
		printf("Error: Incorrect state file size\n");
		return 0;
	}
	
	fread(hw, sizeof(struct Hardware), 1, state_file);
	fclose(state_file);
	return 1;
}