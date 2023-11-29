#include <stdio.h>
#include "stack.h"


void stack_init(struct Stack *stack)
{
	stack->index = 0;
}

int stack_push(struct Stack *stack, uint16_t item)
{
	if (stack->index >= STACK_SIZE)
	{
		return 0;
	}
	stack->data[stack->index] = item;
	stack->index++;
	return 1;
}

int stack_pop(struct Stack *stack, uint16_t *item)
{
	stack->index--;
	if (stack->index < 0)
	{
		return 0;
	}
	*(item) = stack->data[stack->index];
	return 1;
}

