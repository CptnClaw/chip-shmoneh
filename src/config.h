#ifndef CONFIG_H_
#define CONFIG_H_

#include <stdint.h>

struct Config
{
	/* Default 1000 */
	int INSTRUCTIONS_PER_SECOND;

	/* Default 10 */
	int DISPLAY_SCALE;

	/* Default 0
	 *	   Must be non-negative and at most DISPLAY_SCALE / 2. */
	int PIXEL_GRID_GAP;

	/* Default 1
	 *	   Double buffering may be used to reduce flickering
	 *	   Set 0 to not use double buffering.
	 *	   Set 1 to use double buffering. */
	int DOUBLE_BUFFERING;

	/* Default 0
	 *	   Render every frame even if unchanged from previous frame.
	 *	   Not recommended due to being computationally expensive
	 *	   but might mitigate some visual artifacts caused by double buffering,
	 *	   for example in the test rom 6-keypad.ch8. */
	int RENDER_UNCHANGED_FRAMES;

	/* 0=No debug info, 1=Instruction, 2=Instruction+disasm */
	int DEBUG;

	/* Instructions 8XY6 and 8XYE (Shift) are ambiguous.
	 *	   Set 0 for legacy behavior, namely put VY into VX before shifting.
	 *	   Set 1 for modern behavior (default), involving VX only. */
	int SHIFT_BEHAVIOR;

	/* Instruction BNNN/BXNN is ambiguous.
	 *	   Set 0 for legacy behavior (default), namely jump to index+V0.
	 *	   Set 1 for modern behavior, jump to index+VX. */
	int JUMP_OFFSET_BEHAVIOR;

	/* Instructions FX55 and FX65 are ambiguous.
	 *	   Set 0 for legacy behavior, namely increment the index after loading/saving memory.
	 *	   Set 1 for modern behavior (default), leaving the index unaffected. */
	int STORE_MEM_BEHAVIOR;

	/* Quirk in instructions 8XY1, 8XY2, 8XY3.
	 *	   Set 0 for legacy behavior, namely reset the flag to zero.
	 *	   Set 1 for modern behavior (default), not affecting the flag. */
	int QUIRK_RESET_FLAG;

	/* Draw calls wait for the first cycle of the frame.
	 *	   Set 0 for normal behavior (default), namely to never wait.
	 *	   Set 1 for enabling quirk, namely to wait for vblank. */
	int QUIRK_WAIT_VBLANK;

	/* Whether pixels drawn below display edge are clipped or wrapped.
	 *	   Set 0 for wrapping around to the top of the display.
	 *	   Set 1 for clipping (default). */
	int PIXEL_CLIP_BEHAVIOR;

	/* Allow custom colors
	 *   Non-integer divisions not supported.
	 *   Set 0 to have white pixels.
	 *   Set 1, 2, 4, 8, 16, 32 for custom colors. Other numbers default to white */

	int CUSTOM_COLORS;
	/* Custom colors
	 *	Colors need to be converted from hex to decimal. #FF0000 becomes 16711680 */

	int COLOR1;
	int COLOR2;
	int COLOR3;
	int COLOR4;
	int COLOR5;
	int COLOR6;
	int COLOR7;
	int COLOR8;
	int COLOR9;
	int COLOR10;
	int COLOR11;
	int COLOR12;
	int COLOR13;
	int COLOR14;
	int COLOR15;
	int COLOR16;
	int COLOR17;
	int COLOR18;
	int COLOR19;
	int COLOR20;
	int COLOR21;
	int COLOR22;
	int COLOR23;
	int COLOR24;
	int COLOR25;
	int COLOR26;
	int COLOR27;
	int COLOR28;
	int COLOR29;
	int COLOR30;
	int COLOR31;
	int COLOR32;
};
extern struct Config CONFIG;

/* Read configuration file chip-shmoneh.conf from the current working directory
 * and populates the externally-linked CONFIG.
 * Please call this function before anything else!
 * Returns:
 *		1 if successful.
 *		0 if there was any problem. The error will also be printed. */
int load_config();

/* Prints the config values for debug purposes */
void print_config();

#endif  // CONFIG_H_
