#include "debug.h"
#include "processor.h"
#include "config.h"

void print_disasm(uint8_t *instruction)
{
	switch (OPCODE(instruction)) {
		case 0x0: 
			/* 00E0 Clear screen */
			if (NNN(instruction) == 0x0E0)	printf("Clear screen");
			/* 00EE Subroutine (return) */
			else if (NNN(instruction) == 0x0EE) printf("Return");
			break;
		/* 1NNN Jump */
		case 0x1:
			printf("Jump %.4X", NNN(instruction));
			break;
		/* 2NNN Subroutine (call) */
		case 0x2:
			printf("Call %.4X", NNN(instruction));
			break;
		/* 3XNN Skip (if VX == NN) */
		case 0x3:
			printf("Skip if VX == %d", NN(instruction));
			break;

		/* 4XNN Skip (if VX != NN) */
		case 0x4:
			printf("Skip if VX != %d", NN(instruction));
			break;

		/* 5XY0 Skip (if VX == VY) */
		case 0x5:
			printf("Skip if VX == VY");
			break;

		/* 9XY0 Skip (if VX != VY) */
		case 0x9:
			printf("Skip if VX != VY");
			break;

		/* 6XNN Set */
		case 0x6: 
			printf("Set VX = %d", NN(instruction));
			break;

		/* 7XNN Add */
		case 0x7:
			printf("Add VX += %d", NN(instruction));
			break;

		/* Logical and arithmetic instructions */
		case 0x8:
			switch (N(instruction)) {
				/* 8XY0 Set */ 
				case 0x0:
					printf("Set VX = VY");
					break;
				/* 8XY1 OR */
				case 0x1:
					printf("OR VX |= VY");
					break;
				/* 8XY2 AND */
				case 0x2:
					printf("AND VX &= VY");
					break;
				/* 8XY3 XOR */
				case 0x3:
					printf("XOR VX ^= VY");
					break;
				/* 8XY4 Add */ 
				case 0x4:
					printf("Add VX += VY");
					break;
				/* 8XY5 Subtract (X=X-Y) */
				case 0x5:
					printf("Subtract VX -= VY");
					break;
				/* 8XY7 Subtract (X=Y-X) */
				case 0x7:
					printf("Subtract VX = VY - VX");
					break;
				/* 8XY6 Shift (right) */
				case 0x6:
					printf("Shift right");
					break;
				/* 8XYE Shift (left) */
				case 0xE:
					printf("Shift left");
					break;
			}
			break;

		/* ANNN Set index */
		case 0xA:
			printf("Set index = %.4X", NNN(instruction));
			break;

		/* BNNN Jump with offset */
		case 0xB:
			printf("Jump with offset %.4X", NNN(instruction));
			break;

		/* CXNN Random */
		case 0xC:
			printf("Random");
			break;

			/* DXYN Display */
		case 0xD:
			printf("Display");
			break;

		case 0xE:
			switch (NN(instruction))
			{
				/* EX9E Skip if key (pressed) */
				case 0x9E:
					printf("Skip if key pressed");
					break;
				/* EXA1 Skip if key (not pressed) */ 
				case 0xA1:
					printf("Skip if key not pressed");
					break;
			}
			break;

		case 0xF:
			switch (NN(instruction))
			{
				/* FX07 Timer (get delay) */
				case 0x07: 
					printf("Get delay timer");
					break;
				/* FX15 Timer (set delay) */
				case 0x15: 
					printf("Set delay timer");
					break;
				/* FX18 Timer (set sound) */
				case 0x18:
					printf("Set sound timer");
					break;
				/* FX1E Add to index */
				case 0x1E: 
					printf("Add VX to index");
					break;
				/* 0xFX0A Get key */
				case 0x0A:
					printf("Get key");
					break;
				/* FX29 Font character */
				case 0x29: 
					printf("Get font at VX");
					break;
				/* FX33 Binary-coded decimal conversion */
				case 0x33: 
					printf("Binary decimal conversion");
					break;
				/* FX55 Store memory */
				case 0x55: 
					printf("Store memory");
					break;
				/* FX65 Load memory */
				case 0x65: 
					printf("Load memory");
					break;
			}
			break;
	
		default:
			{}
	}

}

void print_inst(uint8_t *instruction)
{
	printf("%.4X ||| OP:%X X:%X Y:%X N:%X NN:%.2X NNN:%.3X ||| ",
			WHOLE(instruction),
			OPCODE(instruction),
			X(instruction),
			Y(instruction),
			N(instruction),
			NN(instruction),
			NNN(instruction));

	if (CONFIG.DEBUG == 2)
	{
		print_disasm(instruction);
	}
	printf("\n");
}
