#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "display.h"


void display_init(struct Display *display)
{
	display_clear(display);
}

void display_clear(struct Display *display)
{
	memset(display->pixels, 0, sizeof(uint8_t) * DISPLAY_SIZE / 8);
	display->should_be_rendered = 1;
}

uint8_t draw_sprite_line(uint8_t *pixels, int x, int y, uint8_t line)
{
	/* Line location intersects at most 2 bytes in the pixel array */
	int loc1 = y * (LOGICAL_DISPLAY_W / 8) + (x / 8);
	int loc2 = loc1 + 1;
	
	/* Check if the second location is outside of the display */
	int loc2_clipped = 0;
	if (x+8 > LOGICAL_DISPLAY_W)
	{
		switch (CONFIG.PIXEL_CLIP_BEHAVIOR)
		{
		case 0:
			/* loc2 wraps to the start of the row */
			loc2 = y * (LOGICAL_DISPLAY_W / 8);
			break;
		case 1:
			/* loc2 clips and should not be drawn */
			loc2_clipped = 1;
			break;
		default:
			printf("ERROR: Value of PIXEL_CLIP_BEHAVIOR is invalid.\n");
			loc2_clipped = 1; 
			break;
		}
	}
	
	/* Split line data into two bytes */
	int offset = x % 8;
	uint8_t byte1 = line >> offset;
	uint8_t byte2 = line << (8 - offset);
	
	/* Check for collisions and then draw */
	uint8_t has_collision = (0 != (pixels[loc1] & byte1));
	pixels[loc1] ^= byte1;
	if (!loc2_clipped)
	{
		has_collision |= (0 != (pixels[loc2] & byte2));
		pixels[loc2] ^= byte2;
	}
	return has_collision;
}

void display_draw(struct Display *display, uint8_t x, uint8_t y, uint8_t *sprite, uint8_t sprite_height, uint8_t *collision)
{
	x = x % LOGICAL_DISPLAY_W;
	y = y % LOGICAL_DISPLAY_H;
	
	(*collision) = 0;
	for (uint8_t i = 0; i < sprite_height; i++)
	{
		uint8_t new_y = y+i;
		if (!CONFIG.PIXEL_CLIP_BEHAVIOR)
		{
			new_y = new_y % LOGICAL_DISPLAY_H;
		}
		if (new_y >= LOGICAL_DISPLAY_H)
		{
			break;
		}
		(*collision) |= draw_sprite_line(display->pixels, x, new_y, *(sprite+i));
	}
	display->should_be_rendered = 1;
}


