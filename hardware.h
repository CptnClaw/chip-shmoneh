#include "config.h"
#include "stack.h"
#include "graphics.h"

#define MEM_SIZE 0x1000  /* 4 kilobytes */
#define MEM_LOC_FONT 0x050
#define MEM_LOC_PROG 0x200
#define is_prog_size_ok(rom_size)	( (rom_size) + MEM_LOC_PROG <= MEM_SIZE ? 1 : 0)

struct Hardware
{
	uint8_t memory[MEM_SIZE];
	uint16_t rom_size;
	
	/* Registers */
	uint16_t pc;
	uint16_t index;
	/* delay timer */
	/* sound timer */
	uint8_t variables[16];
	struct Stack stack;
	struct Graphics gfx;
};

int hardware_init(struct Hardware *hw, char *rom_path);
void hardware_free(struct Hardware *hw);
int load_font(uint8_t *memory);
uint16_t load_rom(char *rom_path, uint8_t *memory);
