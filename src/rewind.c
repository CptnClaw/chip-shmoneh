#include <stdio.h>
#include "rewind.h"

void rewind_init(struct Rewind *rewind)
{ 
	rewind->stack = malloc(sizeof(uint8_t*) * REWIND_SIZE);
	for (int i=0; i < REWIND_SIZE; i++)
	{
		rewind->stack[i] = malloc(sizeof(struct Hardware));
	}
	rewind->top_idx = 0;
	rewind->bottom_idx = 0;
	rewind->stack_is_full = 0;
}

/* Here the denominator (b) is assumed to be positive. */

void rewind_push_state(struct Rewind *rewind, struct Hardware *hw)
{
	/* Put new serialized hardware in array */
	memcpy(rewind->stack[rewind->top_idx], hw, sizeof(struct Hardware));
	
	/* Increase top pointer, signifying new element was added to stack */
	rewind->top_idx++;
	rewind->top_idx %= REWIND_SIZE;

	/* If top pointer reached bottom pointer (recall indices are cyclic), 
	   this means the stack just became full */
	if (rewind->top_idx == rewind->bottom_idx)
	{
		rewind->stack_is_full = 1;
	}
	
	/* If stack is full, increase bottom pointer, signifying deletion of oldest element in stack */
	if (rewind->stack_is_full)
	{
		rewind->bottom_idx++;
		rewind->bottom_idx %= REWIND_SIZE;
	}
}

void rewind_pop_state(struct Rewind *rewind, struct Hardware *hw)
{
	/* Check if stack is not empty */
	if (rewind->top_idx != rewind->bottom_idx)
	{
		/* Decrease top pointer, signifying deletion of lastest element in stack*/
		rewind->top_idx--;
		rewind->top_idx %= REWIND_SIZE;
		if (rewind->top_idx < 0)
		{
			/* Take into account the fact that % in C is the reminder operation
			   but we actually want the modulo operation, which is different
			   for negative numbers. */
			rewind->top_idx += REWIND_SIZE;
		}

		/* Put lastest serialized hardware from array to second function argument */
		memcpy(hw, rewind->stack[rewind->top_idx], sizeof(struct Hardware));
		
		/* Regardless of previous status, mark that the stack is not full */
		rewind->stack_is_full = 0;
	}
}

