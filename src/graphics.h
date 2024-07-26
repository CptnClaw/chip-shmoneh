#include <SDL.h>
#include "display.h"

#define BLACK 	0
#define WHITE	-1

#define COLOR_BW 			0
#define COLOR_RAINBOW 		1
#define PALETTE_SIZE 		8	

struct Graphics
{
	/* The physical window dimensions,
	 * which are given by the interal resolution of CHIP-8 
	 * times the scaling factor. */
	int width;
	int height;
	SDL_Rect rect;
	
	/* Color options to be used on the display. */
	uint32_t colors_pallete[PALETTE_SIZE];

	/* Buffer of (optionally colored) pixels, scaled to fit rect */
	uint32_t *buffer;
	
	/* Keep a copy of previous frame for double buffering (reduce flicker) */
	struct Display prev_frame;

	/* SDL variables used to directly draw to the screen */
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *texture;
};

/* Initializes SDL et cetera. Call this function before using gfx. */
void graphics_init(struct Graphics *gfx, char *window_title);

/* Frees SDL resources. */
void graphics_free(struct Graphics *gfx);

/* Renders a frame (if the display should be rendered). */
void graphics_render(struct Graphics *gfx, struct Display *display, int use_double_buffering);

