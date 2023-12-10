#include <SDL.h>

struct Graphics
{
	/* The physical window dimensions,
	 * which are given by the interal resolution of CHIP-8 
	 * times the scaling factor. */
	int display_w;
	int display_h;
	SDL_Rect display_rect;

	/* Buffer of black (0) and white (-1) pixels */
	uint32_t *pixels;

	/* SDL variables used to directly draw to the screen */
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *texture;
};

/* Initializes SDL et cetera. Call this function before using gfx. */
void graphics_init(struct Graphics *gfx, char *window_title);

/* Frees SDL resources. */
void graphics_free(struct Graphics *gfx);

/* Clear the screen, i.e. sets all pixels to black. */
void graphics_clear(struct Graphics *gfx);

/* Draws a sprite of a given height to the (x,y) position.
 * Sets the collision flag to 1 if any white pixels was drawn over by
 * another white pixel (resulting in a black pixel). Otherwise,
 * the collision flag will be set to 0. */
void graphics_draw(struct Graphics *gfx, 
					uint8_t x, uint8_t y, 
					uint8_t *sprite, uint8_t sprite_height, 
					uint8_t *collision);
