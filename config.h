#ifndef CONFIG_H_
#define CONFIG_H_

#include <stdint.h>

struct Config 
{
	/* Default 1000 */
	int INSTRUCTIONS_PER_SECOND;

	/* Default 10 */
	int DISPLAY_SCALE; 

	/* 0=No debug info, 1=Instruction, 2=Instruction+disasm */
	int DEBUG; 

	/* Instructions 8XY6 and 8XYE (Shift) are ambiguous.
	   Set 0 for legacy behavior, namely put VY into VX before shifting.
	   Set 1 for modern behavior (default), involving VX only. */
	int SHIFT_BEHAVIOR;

	/* Instruction BNNN/BXNN is ambiguous. 
	   Set 0 for legacy behavior (default), namely jump to index+V0. 
	   Set 1 for modern behavior, jump to index+VX. */
	int JUMP_OFFSET_BEHAVIOR;

	/* Instruction FX1E is ambiguous.
	   Set 0 for legacy behavior.
	   Set 1 for modern behavior (default). */
	int ADD_INDEX_BEHAVIOR;

	/* Instructions FX55 and FX65 are ambiguous.
	   Set 0 for legacy behavior, namely increment the index after loading/saving memory.
	   Set 1 for modern behavior (default), leaving the index unaffected. */
	int STORE_MEM_BEHAVIOR;

	/* Quirk in instructions 8XY1, 8XY2, 8XY3.
	   Set 0 for legacy behavior, namely reset the flag to zero.
	   Set 1 for modern behavior (default), not affecting the flag. */
	int LOGIC_FLAG_BEHAVIOR;
};

extern struct Config CONFIG;

/* Read configuration file chip-shmoneh.conf from the current working directory
 * and populates the externally-linked CONFIG.
 * Returns:
 *		1 if successful.
 *		0 if there was any problem. The error will also be printed. */
int read_config();


#endif  // CONFIG_H_
