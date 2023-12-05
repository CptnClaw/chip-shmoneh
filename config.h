#define INSTRUCTIONS_PER_SECOND 1000
#define DISPLAY_SCALE 10
#define DEBUG 0  /* 0=No debug info, 1=Instruction, 2=Instruction+disasm */

/* Instructions 8XY6 and 8XYE (Shift) are ambiguous.
   Set 0 for legacy behavior, namely put VY into VX before shifting.
   Set 1 for modern behavior (default), involving VX only. */
#define SHIFT_BEHAVIOR 1

/* Instruction BNNN/BXNN is ambiguous. 
   Set 0 for legacy behavior (default), namely jump to index+V0. 
   Set 1 for modern behavior, jump to index+VX. */
#define JUMP_OFFSET_BEHAVIOR 0

/* Instruction FX1E is ambiguous.
   Set 0 for legacy behavior.
   Set 1 for modern behavior (default). */
#define ADD_INDEX_BEHAVIOR 1

/* Instructions FX55 and FX65 are ambiguous.
   Set 0 for legacy behavior, namely increment the index after loading/saving memory.
   Set 1 for modern behavior (default), leaving the index unaffected. */
#define STORE_MEM_BEHAVIOR 1

/* Quirk in instructions 8XY1, 8XY2, 8XY3.
   Set 0 for legacy behavior, namely reset the flag to zero.
   Set 1 for modern behavior (default), not affecting the flag. */
#define LOGIC_FLAG_BEHAVIOR 1

