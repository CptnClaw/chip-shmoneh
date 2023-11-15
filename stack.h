#include <stdint.h>

#define STACK_SIZE 64


struct Stack
{
	uint16_t data[STACK_SIZE];
	int index;
};

/* Always call init before using stack for the first time */
void stack_init(struct Stack *stack);

/* Returns 0 if stack is full */
int stack_push(struct Stack *stack, uint16_t item);

/* Return 0 if stack is empty */
int stack_pop(struct Stack *stack, uint16_t *item);

