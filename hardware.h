#ifndef _HARDWARE_
#define _HARDWARE_

#include "config.h"
#include "stack.h"
#include "graphics.h"

#define MEM_SIZE 0x1000  /* 4 kilobytes */
#define MEM_LOC_FONT 0x050
#define MEM_LOC_PROG 0x200
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
	uint8_t variables[16];
	struct Stack stack;

	/* Peripherals */
	struct Graphics gfx;
	uint8_t keyboard[16];
	
	/* Saves previous keyboard to be used for FX0A (get key) */
	int is_waiting_key;
	int prev_keyboard[16]; 

	/* Clock */
	Uint64 clock;
	int num_ticks;

	/* Misc hardware */
	int is_turned_on;
	Uint64 timer_delay;
	Uint64 timer_sound;
};

/* Loads the ROM and initializes all members.
 * Call this function before any other! 
 * Returns:
 *		0 if there was a problem loading ROM or font to memory.
 *		1 if successful. */
int hardware_init(struct Hardware *hw, char *rom_path);

/* Frees allocated resources (graphics).
 * Call this function after you are done using hw! */
void hardware_free(struct Hardware *hw);

/* Loads font data (from font.h) into memory address MEM_LOC_FONT.
 * Returns:
 *		1 if successful. */
int load_font(uint8_t *memory);

/* Loads ROM file into memory address MEM_LOC_PROG.
 * Returns:
 *		The size (in bytes) of the loaded ROM.
 *		0 if the loading filed. */
uint16_t load_rom(char *rom_path, uint8_t *memory);

/* Generates and returns a random number from 0 to 65535 */
uint16_t gen_random();

/* Reset the keyboard, i.e. set all keys to released state */
void keyboard_reset(struct Hardware *hw);

/* Set a specific key to pressed state */
void keyboard_press(struct Hardware *hw, int key);

/* Set a specific key to released state */
void keyboard_release(struct Hardware *hw, int key);

/* Check the state of a specific key.
 * Returns: 
 *		1 if the key is pressed.
 *		0 if the key is released. */
int is_key_pressed(struct Hardware *hw, int key);

/* The first time this function is called, 
 * it just captures the current state of the entire keyboard
 * and returns -1.
 * In subsequent calls, it check if any key was released
 * since any previous calls. If so, return it and reset.
 * Returns:
 *		The key that was released.
 *		-1 if no key was released. */
int did_any_key_release(struct Hardware *hw);

/* Returns the value of the delay timer. The units are TIMERS_RATE per second. */
uint8_t timer_delay_get(struct Hardware *hw);

/* Sets the value of the delay timer. The units are TIMERS_RATE per second. */
void timer_delay_set(struct Hardware *hw, uint8_t amount);

/* Sets the value of the sound timer. The units are TIMERS_RATE per second. 
 * A beep will sound while the sound timer is greater than zero. */
void timer_sound_set(struct Hardware *hw, uint8_t amount);

/* Initializes the clock, starting the timer and zeroing number of ticks */
void clock_reset(struct Hardware *hw);

/* Increase the number of ticks by one. 
 * Processes incoming events while making sure the number of instructions per second
 * does not exceed INSTRUCTIONS_PER_SECOND */
void clock_tick(struct Hardware *hw);

#endif /* ifndef _HARDWARE_ */
