#ifndef _DISPLAY_
#define _DISPLAY_

#define LOGICAL_DISPLAY_W	64
#define LOGICAL_DISPLAY_H	32
#define DISPLAY_SIZE 		LOGICAL_DISPLAY_H * LOGICAL_DISPLAY_W	

#define BLACK 	0
#define WHITE	-1

struct Display
{
	/* Buffer of black and white pixels */
	uint32_t *pixels;

	/* Will be set to TRUE whenever display_clear or display_draw are called. */
	/* Graphics library should reset to FALSE after rendering to avoid redundant renderings. */
	int should_be_rendered;
};

/* Allocates pixels and initializes. Call this function before using display. */
void display_init(struct Display *display);

/* Frees resources. */
void display_free(struct Display *display);

/* Clear the screen, i.e. sets all pixels to black. */
void display_clear(struct Display *display);

/* Draws a sprite of a given height to the (x,y) position.
 * Sets the collision flag to 1 if any white pixels was drawn over by
 * another white pixel (resulting in a black pixel). Otherwise,
 * the collision flag will be set to 0. */
void display_draw(struct Display *display, 
					uint8_t x, uint8_t y, 
					uint8_t *sprite, uint8_t sprite_height, 
					uint8_t *collision);


#endif /* ifndef _DISPLAY_ */