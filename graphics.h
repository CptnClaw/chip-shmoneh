#include <SDL.h>
#include "display.h"

struct Graphics
{
	/* The physical window dimensions,
	 * which are given by the interal resolution of CHIP-8 
	 * times the scaling factor. */
	int width;
	int height;
	SDL_Rect rect;

	/* Buffer of black and white pixels, scaled to fit rect */
	uint32_t *buffer;

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
void graphics_render(struct Graphics *gfx, struct Display *display);

