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
	/* print_inst(instruction); */
	switch (OPCODE(instruction)) {

		case 0x0: 
			/* 00E0 Clear screen */
			if (NNN(instruction) == 0x0E0)
			{
				graphics_clear(&hw->gfx);
			}
			/* 00EE Subroutine (return) */
			else if (NNN(instruction) == 0x0EE)
			{
				stack_pop(&(hw->stack), &(hw->pc));
			}
			else
			{
				return error_msg(instruction);
			}
			break;

		/* 1NNN Jump */
		case 0x1:
			hw->pc = NNN(instruction);
			break;
			
		/* 2NNN Subroutine (call) */
		case 0x2:
			stack_push(&(hw->stack), hw->pc);
			hw->pc = NNN(instruction);
			break;

		/* 3XNN Skip (if VX == NN) */
		case 0x3:
			if (hw->variables[X(instruction)] == NNN(instruction))
			{
				hw->pc += 2;
			}
			break;

		/* 4XNN Skip (if VX != NN) */
		case 0x4:
			if (hw->variables[X(instruction)] != NNN(instruction))
			{
				hw->pc += 2;
			}
			break;

		/* 5XY0 Skip (if VX == VY) */
		case 0x5:
			if (N(instruction) != 0)
			{
				return error_msg(instruction);
			}
			if (hw->variables[X(instruction)] == hw->variables[Y(instruction)])
			{
				hw->pc += 2;
			}
			break;

		/* 9XY0 Skip (if VX != VY) */
		case 0x9:
			if (N(instruction) != 0)
			{
				return error_msg(instruction);
			}
			if (hw->variables[X(instruction)] != hw->variables[Y(instruction)])
			{
				hw->pc += 2;
			}
			break;

		/* Logical and arithmetic instructions */
		case 0x8:
			break;
			switch (N(instruction)) {
				/* 8XY0 Set */ 
				case 0x0:
					hw->variables[X(instruction)] =
						hw->variables[Y(instruction)];
					break;
				/* 8XY1 OR */
				case 0x1:
					hw->variables[X(instruction)] |=
						hw->variables[Y(instruction)];
					break;
				/* 8XY2 AND */
				case 0x2:
					hw->variables[X(instruction)] &=
						hw->variables[Y(instruction)];
					break;
				/* 8XY3 XOR */
				case 0x3:
					hw->variables[X(instruction)] ^=
						hw->variables[Y(instruction)];
					break;
				/* 8XY4 Add */ 
				case 0x4:
					hw->variables[X(instruction)] +=
						hw->variables[Y(instruction)];
					/* Set flag=1 if overflow, flag=0 otherwise */
					hw->variables[FLAG_REG] =
						(hw->variables[X(instruction)] > 
						0xFF - hw->variables[Y(instruction)]) 
					break;
				/* 8XY5 Subtract (I) */
				case 0x5:
					hw->variables[X(instruction)] =
						hw->variables[X(instruction)] -
						hw->variables[Y(instruction)];
					/* Set flag=1 if overflow, flag=0 otherwise */
					hw->variables[FLAG_REG] =
						(hw->variables[X(instruction)] >=
						 hw->variables[Y(instruction)])
					break;
				/* 8XY7 Subtract (II) */
				case 0x7:
					hw->variables[X(instruction)] =
						hw->variables[Y(instruction)] -
						hw->variables[X(instruction)];
					/* Set flag=1 if overflow, flag=0 otherwise */
					hw->variables[FLAG_REG] =
						(hw->variables[Y(instruction)] >=
						 hw->variables[X(instruction)])
					break;
				/* 8XY6 Shift (right) */
				case 0x6:
					break;
				/* 8XYE Shift (left) */
				case 0xE:
					break;
				default:
					return error_msg(instruction);
			}

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
			graphics_draw(&hw->gfx, 
					hw->variables[X(instruction)],
					hw->variables[Y(instruction)],
					hw->memory + hw->index,
					N(instruction));
			break;
	
		default:
			return 1;  /* TODO: Remove */
			return error_msg(instruction);
	}
	return 1;
}

