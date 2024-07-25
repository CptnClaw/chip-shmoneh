#ifndef CONFIG_H_
#define CONFIG_H_

#include <stdint.h>

struct Config
{
	/* See comments in chip-shmoneh.conf for more information about the following fields. */
	int INSTRUCTIONS_PER_SECOND;
	int DISPLAY_SCALE;
	int PIXEL_GRID_GAP;
	int COLOR_MODE;
	int DOUBLE_BUFFERING;
	int RENDER_UNCHANGED_FRAMES;
	int DEBUG;
	int SHIFT_BEHAVIOR;
	int JUMP_OFFSET_BEHAVIOR;
	int STORE_MEM_BEHAVIOR;
	int QUIRK_RESET_FLAG;
	int QUIRK_WAIT_VBLANK;
	int PIXEL_CLIP_BEHAVIOR;
	int AUTOLOAD;
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
