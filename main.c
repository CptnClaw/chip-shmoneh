#include <stdio.h>
#include <sys/stat.h>
#include "graphics.h"
#include "font.h"

#define MEM_SIZE 0x1000  /* 4 kilobytes */
#define MEM_LOC_FONT 0x050
#define MEM_LOC_PROG 0x200
#define is_prog_size_ok(rom_size)	( (rom_size) + MEM_LOC_PROG <= MEM_SIZE ? 1 : 0)

#define FLAG_REG 0xF

/* opcode decoding */
#define OPCODE(inst) inst[0] >> 4
#define X(inst) (inst)[0] & 0x0F
#define Y(inst) (inst)[1] >> 4
#define N(inst) (inst)[1] & 0x0F
#define NN(inst) (inst)[1]
#define NNN(inst) ((uint16_t)((inst)[0] & 0x0F) << 8) + (uint16_t)(inst)[1]


int load_font(uint8_t *memory)
{
	memcpy(memory + MEM_LOC_FONT, font_data, FONT_SIZE * sizeof(uint8_t));
	return 1;
}

int load_rom(char *rom_path, uint8_t *memory)
{
	FILE *rom_file = fopen(rom_path, "rb");
	if (!rom_file)
	{
		printf("ROM file not found: %s\n", rom_path);
		return 0;
	}

	struct stat rom_stat;
	if (stat(rom_path, &rom_stat) == -1)
	{
		printf("Cannot read ROM file size: %s\n", rom_path);
		return 0;
	}

	int rom_size = rom_stat.st_size;
	printf("%s weighs %d bytes\n", rom_path, rom_size);
	if (!is_prog_size_ok(rom_size))
	{
		printf("Error: ROM file too large\n");
		return 0;
	}

	/* Read ROM file directly to memory in the correct location */
	fread(memory + MEM_LOC_PROG, rom_size * sizeof(uint8_t), 1, rom_file);

	fclose(rom_file);
	return rom_size;
}

void print_inst(uint8_t *instruction)
{
	printf("OP:%X X:%X Y:%X N:%X NN:%.2X NNN:%.3X\n",
			OPCODE(instruction),
			X(instruction),
			Y(instruction),
			N(instruction),
			NN(instruction),
			NNN(instruction));
}

void execute(uint8_t *instruction)
{
	print_inst(instruction);
}

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("Usage: chip-shmoneh <rom file>\n");
		return 0;
	}

	/* Registers */
	uint16_t pc = MEM_LOC_PROG;
	uint16_t index = 0;
	/* stack */
	/* delay timer */
	/* sound timer */
	uint8_t variables[16];

	/* Initialize memory */
	char *rom_path = argv[1];
	uint8_t memory[MEM_SIZE];
	int rom_size = load_rom(rom_path, memory);
	if (!rom_size && !load_font(memory))
	{
		return 1;
	}

	/* Main loop */
	int running = 1;
	uint8_t instruction[2];
	while (running)
	{
		instruction[0] = memory[pc];
		pc++;
		instruction[1] = memory[pc];
		pc++;
		execute(instruction);

		if (pc > MEM_LOC_PROG + rom_size) running = 0;
	}

	demo(10);

	return 0;
}
