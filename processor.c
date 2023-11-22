#include "processor.h"

int fetch(struct Hardware *hw, uint8_t *instruction)
{
	if (hw->pc > MEM_LOC_PROG + hw->rom_size) 	
	{
		return 0;
	}
	instruction[0] = hw->memory[hw->pc];
	hw->pc++;
	instruction[1] = hw->memory[hw->pc];
	hw->pc++;
	return 1;
}

void print_inst(uint8_t *instruction)
{
	printf("%.4X ||| OP:%X X:%X Y:%X N:%X NN:%.2X NNN:%.3X\n",
			WHOLE(instruction),
			OPCODE(instruction),
			X(instruction),
			Y(instruction),
			N(instruction),
			NN(instruction),
			NNN(instruction));
}

int error_msg(uint8_t *instruction)
{
	printf("Error: Unknown opcode %X\n", OPCODE(instruction));
	return 0;
}

int execute(struct Hardware *hw, uint8_t *instruction)
{
	print_inst(instruction);
	switch (OPCODE(instruction)) {

		/* 0E00 Clear screen */
		case 0x0: 
			if (NNN(instruction) != 0x0E0)
			{
				return error_msg(instruction);
			}
			graphics_clear(&hw->gfx);
			break;

		/* 1NNN Jump */
		case 0x1:
			hw->pc = NNN(instruction);
			break;

		/* 6XNN Set */
		case 0x6: 
			hw->variables[X(instruction)] = NN(instruction);
			break;

		/* 7XNN Add */
		case 0x7:
			hw->variables[X(instruction)] += NN(instruction);
			break;

		/* ANNN Set index */
		case 0xA:
			hw->index = NNN(instruction);
			break;

		/* DXYN Display */
		case 0xD:
			break;
	
		default:
			return error_msg(instruction);
	}
	return 1;
}

