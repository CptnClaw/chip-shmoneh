#include <stdint.h>

/* Prints information regarding the given instruction. 
 * If the DEBUG config equals or greater than 2, then print the disassembly as well. */
void print_inst(uint8_t *instruction);

/* Prints the textual representation of the instruction. */
void print_disasm(uint8_t *instruction);
