#include <sys/stat.h>
#include <time.h>
#include <stdlib.h>
#include "hardware.h"
#include "font.h"

#define MS_TO_TIMER(ms)		((ms) * TIMERS_RATE / 1000)
#define TIMER_TO_MS(amt)	((amt) * 1000 / TIMERS_RATE)

int hardware_init(struct Hardware *hw, char *rom_path)
{
	hw->pc = MEM_LOC_PROG;
	hw->index = 0;
	hw->timer_delay = 0;
	hw->timer_sound = 0;
	stack_init(&(hw->stack));
	graphics_init(&(hw->gfx), rom_path);
	hw->rom_size = load_rom(rom_path, hw->memory);
	if (!hw->rom_size && !load_font(hw->memory))
	{
		return 0;
	}
	srand(time(NULL));
	return 1;
}

void hardware_free(struct Hardware *hw)
{
	graphics_free(&(hw->gfx));
}

int load_font(uint8_t *memory)
{
	memcpy(memory + MEM_LOC_FONT, font_data, FONT_SIZE * sizeof(uint8_t));
	return 1;
}

uint16_t load_rom(char *rom_path, uint8_t *memory)
{
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
	/* printf("%s weighs %d bytes\n", rom_path, rom_size); */
	if (!is_prog_size_ok(rom_size))
	{
		printf("Error: ROM file too large\n");
		return 0;
	}

	/* Read ROM file directly to memory in the correct location */
	fread(memory + MEM_LOC_PROG, rom_size * sizeof(uint8_t), 1, rom_file);

	fclose(rom_file);
	return (uint16_t)rom_size;
}

uint16_t gen_random()
{
	return (uint16_t)rand();
}

void keyboard_down(struct Hardware *hw, int key)
{
	hw->keyboard[key] = 1;
}

void keyboard_up(struct Hardware *hw, int key)
{
	hw->keyboard[key] = 0;
}

int is_key_pressed(struct Hardware *hw, int key)
{
	return (hw->keyboard[key] == 1);
}

int is_any_key_pressed(struct Hardware *hw)
{
	for (int i=0; i<16; i++)
	{
		if (hw->keyboard[i] == 1)
		{
			return i;
		}
	}
	return -1;
}

uint8_t timer_delay_get(struct Hardware *hw)
{
	Uint64 now = SDL_GetTicks64();
	if (now > hw->timer_delay)
	{
		return 0;
	}
	Uint64 diff = now - hw->timer_delay;
	return (uint8_t)(MS_TO_TIMER(diff));
}

void timer_delay_set(struct Hardware *hw, uint8_t amount)
{
	hw->timer_delay = SDL_GetTicks64() + TIMER_TO_MS(amount);
}

void timer_sound_set(struct Hardware *hw, uint8_t amount)
{
	hw->timer_sound = SDL_GetTicks64() + TIMER_TO_MS(amount);
}
