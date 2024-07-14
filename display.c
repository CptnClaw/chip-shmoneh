#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "display.h"

void display_init(struct Display *display)
{
	display->pixels = malloc(sizeof(uint32_t) * DISPLAY_SIZE);
	display_clear(display);
}

void display_free(struct Display *display)
{
	free(display->pixels);
}

void display_clear(struct Display *display)
{
	memset(display->pixels, BLACK, sizeof(uint32_t) * DISPLAY_SIZE);
	display->should_be_rendered = 1;
}

uint8_t draw_sprite_line(uint32_t *pixels, int x, int y, uint8_t line)
{
	uint8_t has_collision = 0;
	for (uint8_t j=0; j<8 && x+j<LOGICAL_DISPLAY_W; j++)
	{
		if ((line & (128 >> j)) != 0)
		{
			int location = y * LOGICAL_DISPLAY_W + x + j;
			uint32_t cur_val = pixels[location];
			uint32_t new_val = BLACK;
			if (cur_val == BLACK)	new_val = WHITE;
			else					has_collision = 1;
			pixels[location] = new_val;
		}
	}
	return has_collision;
}

void display_draw(struct Display *display, uint8_t x, uint8_t y, uint8_t *sprite, uint8_t sprite_height, uint8_t *collision)
{
	x = x % LOGICAL_DISPLAY_W;
	y = y % LOGICAL_DISPLAY_H;
	(*collision) = 0;
	for (uint8_t i=0; i<sprite_height && y+i<LOGICAL_DISPLAY_H; i++)
	{
		(*collision) |= draw_sprite_line(display->pixels, x, y+i, *(sprite+i));
	}
	display->should_be_rendered = 1;
}

