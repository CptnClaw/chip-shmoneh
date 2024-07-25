#ifndef _HARDWARE_
#define _HARDWARE_

#include <SDL.h>
#include "config.h"
#include "stack.h"
#include "display.h"

#define MEM_SIZE 0x1000  /* 4 kilobytes */
#define MEM_LOC_FONT 0x050
#define MEM_LOC_PROG 0x200
#define FONT_WIDTH 5
#define TIMERS_RATE 60  /* in Hz (updates per second) */
#define MAX_FILEPATH_SIZE 200

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
	struct Display display;
	uint8_t keyboard[16];
	
	/* Saves previous keyboard to be used for FX0A (get key) */
	int is_waiting_key;
	int prev_keyboard[16]; 

	/* Misc hardware */
	int is_turned_on;
	int timer_delay;
	int timer_sound;
	char save_file_path[MAX_FILEPATH_SIZE+1];
};

/* Loads the ROM and initializes all members.
 * Call this function before any other! 
 * Returns:
 *		0 if there was a problem loading ROM or font to memory.
 *		1 if successful. */
int hardware_init(struct Hardware *hw, char *rom_path);

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

/* Decreases both timers by 1 step, if they are not already zero. 
 * This function should be called 60 times per second (or once per frame). */
void timers_step(struct Hardware *hw);

/* Save/load hardware state to/from the file hw->save_file_path */
/* Returns 1 if successfull, 0 otherwise. */
int save_state(struct Hardware *hw);
int load_state(struct Hardware *hw);

#endif /* ifndef _HARDWARE_ */
