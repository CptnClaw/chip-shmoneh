#define INSTRUCTIONS_PER_SECOND 1000
#define DISPLAY_SCALE 10
#define DEBUG 0  /* 0=No debug info, 1=Instruction, 2=Instruction+disasm */

/* Instructions 8XY6 and 8XYE (Shift) are ambiguous.
   Set 0 for legacy behavior.
   Set 1 for modern behavior (default). */
#define SHIFT_BEHAVIOR 1 

/* Instruction BNNN/BXNN is ambiguous. 
   Set 0 for legacy behavior (default). 
   Set 1 for modern behavior. */
#define JUMP_OFFSET_BEHAVIOR 0

/* Instruction FX1E is ambiguous.
   Set 0 for legacy behavior.
   Set 1 for modern behavior (default). */
#define ADD_INDEX_BEHAVIOR 1

/* Instructions FX55 and FX65 are ambiguous.
   Set 0 for legacy behavior.
   Set 1 for modern behavior (default). */
#define STORE_MEM_BEHAVIOR 1
