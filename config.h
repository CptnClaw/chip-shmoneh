#define INSTRUCTIONS_PER_SECOND 700
#define DISPLAY_SCALE 20

/* Instructions 8XY6 and 8XYE (Shift) are ambiguous.
Set 0 for legacy behavior.
Set 1 for modern behavior (default). */
#define SHIFT_BEHAVIOR 1 

/* Instruction BNNN/BXNN is ambiguous. 
Set 0 for legacy behavior (default). 
Set 1 for modern behavior. */
#define JUMP_OFFSET_BEHAVIOR 0
