#ifndef _REWIND_
#define _REWIND_

#include <stdint.h>
#include "hardware.h" 

#define REWIND_SIZE 100 

/* A cyclical, finite stack keeps track of REWIND_SIZE recent states */
struct Rewind
{
	// uint8_t stack[REWIND_SIZE][sizeof(struct Hardware)];
	uint8_t **stack;
	int top_idx;
	int bottom_idx;
	int stack_is_full;
};

/* Always call init before using rewind for the first time */
void rewind_init(struct Rewind *rewind);

/* Push new state into the rewind stack. */
/* If the stack is already full, drop the oldest state before inserting. */
void rewind_push_state(struct Rewind *rewind, struct Hardware *hw);

/* Pop the latest state from the rewind stack into the second argument. */
/* If the stack is empty, the second argument will not be changed. */
void rewind_pop_state(struct Rewind *rewind, struct Hardware *hw);

#endif /* ifndef _REWIND_ */