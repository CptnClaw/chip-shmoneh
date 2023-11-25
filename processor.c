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

int error_config(char *field)
{
	printf("Error: miconfigured %s", field);
	return 0;
}

int execute(struct Hardware *hw, uint8_t *instruction)
{
	int key;
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

		/* 6XNN Set */
		case 0x6: 
			hw->variables[X(instruction)] = NN(instruction);
			break;

		/* 7XNN Add */
		case 0x7:
			hw->variables[X(instruction)] += NN(instruction);
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
						0xFF - hw->variables[Y(instruction)]);
					break;
				/* 8XY5 Subtract (X=X-Y) */
				case 0x5:
					hw->variables[X(instruction)] =
						hw->variables[X(instruction)] -
						hw->variables[Y(instruction)];
					/* Set flag=1 if overflow, flag=0 otherwise */
					hw->variables[FLAG_REG] =
						(hw->variables[X(instruction)] >=
						 hw->variables[Y(instruction)]);
					break;
				/* 8XY7 Subtract (X=Y-X) */
				case 0x7:
					hw->variables[X(instruction)] =
						hw->variables[Y(instruction)] -
						hw->variables[X(instruction)];
					/* Set flag=1 if overflow, flag=0 otherwise */
					hw->variables[FLAG_REG] =
						(hw->variables[Y(instruction)] >=
						 hw->variables[X(instruction)]);
					break;
				/* 8XY6 Shift (right) */
				case 0x6:
					switch (SHIFT_BEHAVIOR) 
					{
						case 0:
							hw->variables[X(instruction)] =
								hw->variables[Y(instruction)];
							break;
						case 1:
							/* Do nothing */
							break;
						default:
							return error_config("SHIFT_BEHAVIOR");
					}
					hw->variables[FLAG_REG] = 
						hw->variables[X(instruction)] >> 7;
					hw->variables[X(instruction)] <<= 1;
					break;
				/* 8XYE Shift (left) */
				case 0xE:
					switch (SHIFT_BEHAVIOR) 
					{
						case 0:
							hw->variables[X(instruction)] =
								hw->variables[Y(instruction)];
							break;
						case 1:
							/* Do nothing */
							break;
						default:
							return error_config("SHIFT_BEHAVIOR");
					}
					hw->variables[FLAG_REG] = 
						hw->variables[X(instruction)] & 1;
					hw->variables[X(instruction)] >>= 1;
					break;
				default:
					return error_msg(instruction);
			}

		/* ANNN Set index */
		case 0xA:
			hw->index = NNN(instruction);
			break;

		/* BNNN Jump with offset */
		case 0xB:
			hw->pc = NNN(instruction);
			switch (JUMP_OFFSET_BEHAVIOR)
			{
				case 0:
					hw->pc += hw->variables[0];
					break;
				case 1:
					hw->pc += hw->variables[X(instruction)];
					break;
				default:
					return error_config("JUMP_OFFSET_BEHAVIOR");
			}
			break;

		/* CXNN Random */
		case 0xC:
			hw->variables[X(instruction)] =
				gen_random() & NNN(instruction);
			break;

		/* DXYN Display */
		case 0xD:
			graphics_draw(&hw->gfx, 
					hw->variables[X(instruction)],
					hw->variables[Y(instruction)],
					hw->memory + hw->index,
					N(instruction));
			break;

		case 0xE:
			switch (NN(instruction))
			{
				/* EX9E Skip if key (pressed) */
				case 0x9E:
					if (is_key_pressed(hw, hw->variables[X(instruction)]))
					{
						hw->pc += 2;
					}
					break;
				/* EXA1 Skip if key (not pressed) */ 
				case 0xA1:
					if (!is_key_pressed(hw, hw->variables[X(instruction)]))
					{
						hw->pc += 2;
					}
					break;
				default:
					return error_msg(instruction);
			}
			break;

		case 0xF:
			switch (NN(instruction))
			{
				case 0x07: break;
				case 0x15: break;
				case 0x18: break;
				case 0x1E: break;
				/* 0xFX0A Get key */
				case 0x0A:
					key = is_any_key_pressed(hw);
					if (key == -1)
					{
						hw->pc -= 2;
					}
					else
					{
						hw->variables[X(instruction)] = key;
					}
					break;
				/* FX29 Font character */
				case 0x29: break;
				/* FX33 Binary-coded decimal conversion */
				case 0x33: break;
				/* FX55 Store memory */
				case 0x55: break;
				/* FX65 Load memory */
				case 0x65: break;
				default:
					return error_msg(instruction);
			}
			break;
	
		default:
			return 1;  /* TODO: Remove */
			return error_msg(instruction);
	}
	return 1;
}

