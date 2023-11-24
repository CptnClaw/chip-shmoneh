#include "config.h"
#include "hardware.h"

#define FLAG_REG 0xF
/* opcode decoding */
#define OPCODE(inst) (inst[0] >> 4)
#define X(inst) ((inst)[0] & 0x0F)
#define Y(inst) ((inst)[1] >> 4)
#define N(inst) ((inst)[1] & 0x0F)
#define NN(inst) ((inst)[1])
#define NNN(inst) (((uint16_t)((inst)[0] & 0x0F) << 8) + (uint16_t)(inst)[1])
#define WHOLE(inst) (((uint16_t)(inst)[0] << 8) + (uint16_t)(inst)[1])

/* Reads the current instruction into the last variable and increases pc by 2 */
int fetch(struct Hardware *hw, uint8_t *instruction);

/* Executes a single instruction */
int execute(struct Hardware *hw, uint8_t *instruction);
