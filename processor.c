#include "processor.h"
#include "debug.h"

#define VX (hw->variables[X(instruction)])
#define VY (hw->variables[Y(instruction)])

int fetch(struct Hardware *hw, uint8_t *instruction)
{
	if (hw->pc > MEM_LOC_PROG + hw->rom_size) 	
	{
		return 0;
	}

	if (DEBUG >= 1)
	{
		printf("%.4X ||| ", hw->pc);
	}

	instruction[0] = hw->memory[hw->pc];
	hw->pc++;
	instruction[1] = hw->memory[hw->pc];
	hw->pc++;
	return 1;
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
	int temp;
	if (DEBUG >=1)
	{
		print_inst(instruction);
	}
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
			if (hw->variables[X(instruction)] == NN(instruction))
			{
				hw->pc += 2;
			}
			break;

		/* 4XNN Skip (if VX != NN) */
		case 0x4:
			if (hw->variables[X(instruction)] != NN(instruction))
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
					if (LOGIC_FLAG_BEHAVIOR == 0) 
					{
						hw->variables[FLAG_REG] = 0;
					}
					break;
				/* 8XY2 AND */
				case 0x2:
					hw->variables[X(instruction)] &=
						hw->variables[Y(instruction)];
					if (LOGIC_FLAG_BEHAVIOR == 0) 
					{
						hw->variables[FLAG_REG] = 0;
					}
					break;
				/* 8XY3 XOR */
				case 0x3:
					hw->variables[X(instruction)] ^=
						hw->variables[Y(instruction)];
					if (LOGIC_FLAG_BEHAVIOR == 0) 
					{
						hw->variables[FLAG_REG] = 0;
					}
					break;
				/* 8XY4 Add */ 
				case 0x4:
					/* Set flag=1 if overflow, flag=0 otherwise */
					temp = (hw->variables[X(instruction)] > 
						0xFF - hw->variables[Y(instruction)]);
					hw->variables[X(instruction)] +=
						hw->variables[Y(instruction)];
					hw->variables[FLAG_REG] = temp;
					break;
				/* 8XY5 Subtract (X=X-Y) */
				case 0x5:
					/* Set flag=1 if overflow, flag=0 otherwise */
					temp = (hw->variables[X(instruction)] >=
						 hw->variables[Y(instruction)]);
					hw->variables[X(instruction)] =
						hw->variables[X(instruction)] -
						hw->variables[Y(instruction)];
					hw->variables[FLAG_REG] = temp;
					break;
				/* 8XY7 Subtract (X=Y-X) */
				case 0x7:
					/* Set flag=1 if overflow, flag=0 otherwise */
					temp = (hw->variables[Y(instruction)] >=
						 hw->variables[X(instruction)]);
					hw->variables[X(instruction)] =
						hw->variables[Y(instruction)] -
						hw->variables[X(instruction)];
					hw->variables[FLAG_REG] = temp;
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
					temp = hw->variables[X(instruction)] & 1;
					hw->variables[X(instruction)] >>= 1;
					hw->variables[FLAG_REG] = temp;
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
					temp = hw->variables[X(instruction)] >> 7;
					hw->variables[X(instruction)] <<= 1;
					hw->variables[FLAG_REG] = temp;
					break;
				default:
					return error_msg(instruction);
			}
			break;

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
					N(instruction),
					&(hw->variables[FLAG_REG]));
			break;

		case 0xE:
			temp = hw->variables[X(instruction)] & 0x0F;
			switch (NN(instruction))
			{
				/* EX9E Skip if key (pressed) */
				case 0x9E:
					if (is_key_pressed(hw, temp))
					{
						hw->pc += 2;
					}
					break;
				/* EXA1 Skip if key (not pressed) */ 
				case 0xA1:
					if (!is_key_pressed(hw, temp))
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
				/* FX07 Timer (get delay) */
				case 0x07: 
					hw->variables[X(instruction)] = timer_delay_get(hw);
					break;
				/* FX15 Timer (set delay) */
				case 0x15: 
					timer_delay_set(hw, hw->variables[X(instruction)]);
					break;
				/* FX18 Timer (set sound) */
				case 0x18:
					timer_sound_set(hw, hw->variables[X(instruction)]);
					break;
				/* FX1E Add to index */
				case 0x1E: 
					if (ADD_INDEX_BEHAVIOR == 1 &&
						hw->variables[X(instruction)] >
						0x0FFF - hw->index)
					{
						/* Overflow of index above 0x0FFF */
						hw->variables[FLAG_REG] = 1;
					}
					hw->index += hw->variables[X(instruction)];
					break;
				/* 0xFX0A Get key */
				case 0x0A:
					key = is_any_key_pressed(hw);
					if (key == -1)
					{
						/* No key is pressed, go back (try again) */
						hw->pc -= 2;
					}
					else
					{
						hw->variables[X(instruction)] = key;
					}
					break;
				/* FX29 Font character */
				case 0x29: 
					temp = hw->variables[X(instruction)] & 0x0F;
					hw->index = MEM_LOC_FONT + (temp * FONT_WIDTH);
					break;
				/* FX33 Binary-coded decimal conversion */
				case 0x33: 
					temp = hw->variables[X(instruction)];
					hw->memory[hw->index] = temp / 100;
					temp = temp % 100;
					hw->memory[hw->index + 1] = temp / 10;
					temp = temp % 10;
					hw->memory[hw->index + 2] = temp;
					break;
				/* FX55 Store memory */
				case 0x55: 
					for (int i=0; i<=X(instruction); i++)
					{
						hw->memory[hw->index + i] = hw->variables[i];
					}
					if (STORE_MEM_BEHAVIOR == 0)
					{
						hw->index += X(instruction) + 1;
					}
					break;
				/* FX65 Load memory */
				case 0x65: 
					for (int i=0; i<=X(instruction); i++)
					{
						hw->variables[i] = hw->memory[hw->index + i];
					}
					if (STORE_MEM_BEHAVIOR == 0)
					{
						hw->index += X(instruction) + 1;
					}
					break;
				default:
					return error_msg(instruction);
			}
			break;
	
		default:
			return error_msg(instruction);
	}
	return 1;
}

