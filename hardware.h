#ifndef _HARDWARE_
#define _HARDWARE_

#include "config.h"
#include "stack.h"
#include "graphics.h"

#define MEM_SIZE 0x1000  /* 4 kilobytes */
#define MEM_LOC_FONT 0x050
#define MEM_LOC_PROG 0x200
#define is_prog_size_ok(rom_size)	( (rom_size) + MEM_LOC_PROG <= MEM_SIZE ? 1 : 0)
#define FONT_WIDTH 5
#define TIMERS_RATE 60  /* in Hz (updates per second) */

struct Hardware
{
	/* Memory */
	uint8_t memory[MEM_SIZE];
	uint16_t rom_size;
	
	/* Registers */
	uint16_t pc;
	uint16_t index;
	Uint64 timer_delay;
	Uint64 timer_sound;
	uint8_t variables[16];
	struct Stack stack;

	/* Peripherals */
	int is_turned_on;
	struct Graphics gfx;
	uint8_t keyboard[16];

	/* Clock */
	Uint64 clock;
	int num_ticks;
};

int hardware_init(struct Hardware *hw, char *rom_path);
void hardware_free(struct Hardware *hw);
int load_font(uint8_t *memory);
uint16_t load_rom(char *rom_path, uint8_t *memory);
uint16_t gen_random();
void keyboard_reset(struct Hardware *hw);
void keyboard_down(struct Hardware *hw, int key);
void keyboard_up(struct Hardware *hw, int key);
int is_key_pressed(struct Hardware *hw, int key);
int is_any_key_pressed(struct Hardware *hw);
uint8_t timer_delay_get(struct Hardware *hw);
void timer_delay_set(struct Hardware *hw, uint8_t amount);
void timer_sound_set(struct Hardware *hw, uint8_t amount);

/* Initializes the clock, starting the timer and zeroing number of ticks */
void clock_reset(struct Hardware *hw);

/* Increase the number of ticks by one. 
 * Once it reaches INSTRUCTIONS_PER_SECOND, wait until a second passes since last timer reset,
 * and then re-init the clock.
 * All the while, process incoming events */
void clock_tick(struct Hardware *hw);

#endif /* ifndef _HARDWARE_ */
