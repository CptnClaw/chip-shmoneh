#include "config.h"
#include "hardware.h"

/* Variable 0xF is the flag register */
#define FLAG_REG 0xF

/* opcode decoding */
#define OPCODE(inst) (inst[0] >> 4)
#define X(inst) ((inst)[0] & 0x0F)
#define Y(inst) ((inst)[1] >> 4)
#define N(inst) ((inst)[1] & 0x0F)
#define NN(inst) ((inst)[1])
#define NNN(inst) (((uint16_t)((inst)[0] & 0x0F) << 8) + (uint16_t)(inst)[1])
#define WHOLE(inst) (((uint16_t)(inst)[0] << 8) + (uint16_t)(inst)[1])

/* Reads the current instruction into the second argument and increases pc by 2.
 * This function also prints debug information (address of next instruction, i.e. pc)
 * if the DEBUG config is greater or equal to 1. 
 * Returns:
 *		1 if successful.
 *		0 if there are no more instructions left in memory. */
int fetch(struct Hardware *hw, uint8_t *instruction);

/* Executes a single instruction.
 * Cycle is the number of instructions ran since last frame,
 * needed because some instructions must execute only on the first cycle (also known as vblank).
 * Returns:
 *		1 if successful.
 *		0 if there was any problem. In that case, the error will also be printed. */
int execute(struct Hardware *hw, uint8_t *instruction, int cycle);
