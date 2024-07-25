#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "display.h"


void display_init(struct Display *display)
{
	display->colors_pallete[0] = 0xFF0000;
	display->colors_pallete[1] = 0xFF7B00;
	display->colors_pallete[2] = 0xFFFF00;
	display->colors_pallete[3] = 0x00FF00;
	display->colors_pallete[4] = 0x00FF7B;
	display->colors_pallete[5] = 0x00FFFF;
	display->colors_pallete[6] = 0x0000FF;
	display->colors_pallete[7] = 0xFF00FF;
	display->cur_color = 0;
	display_clear(display);
}

void display_clear(struct Display *display)
{
	memset(display->pixels, BLACK, sizeof(uint32_t) * DISPLAY_SIZE);
	display->should_be_rendered = 1;
}

uint8_t draw_sprite_line(uint32_t *pixels, int x, int y, uint8_t line, uint32_t color)
{
	uint8_t has_collision = 0;
	for (uint8_t j = 0; j < 8; j++)
	{
		uint8_t column = x+j;
		if (!CONFIG.PIXEL_CLIP_BEHAVIOR)
		{
			column = column % LOGICAL_DISPLAY_W;
		}
		if (column >= LOGICAL_DISPLAY_W)
		{
			break;
		}
		if ((line & (128 >> j)) != 0)
		{
			int location = y * LOGICAL_DISPLAY_W + column;
			uint32_t cur_val = pixels[location];
			uint32_t new_val = BLACK;
			if (cur_val == BLACK) 	new_val = color;
			else 					has_collision = 1;
			pixels[location] = new_val;
		}
	}
	return has_collision;
}

void display_draw(struct Display *display, uint8_t x, uint8_t y, uint8_t *sprite, uint8_t sprite_height, uint8_t *collision)
{
	x = x % LOGICAL_DISPLAY_W;
	y = y % LOGICAL_DISPLAY_H;
	
	uint32_t color = WHITE;
	if (CONFIG.COLOR_MODE == COLOR_PER_SPRITE)
	{
		color = display->colors_pallete[display->cur_color++];
		display->cur_color %= PALETTE_SIZE;
	}

	(*collision) = 0;
	for (uint8_t i = 0; i < sprite_height; i++)
	{
		uint8_t line = y+i;
		if (!CONFIG.PIXEL_CLIP_BEHAVIOR)
		{
			line = line % LOGICAL_DISPLAY_H;
		}
		if (line >= LOGICAL_DISPLAY_H)
		{
			break;
		}

		if (CONFIG.COLOR_MODE == COLOR_RAINBOW)
		{
			color = display->colors_pallete[line * PALETTE_SIZE / LOGICAL_DISPLAY_H];
		}

		(*collision) |= draw_sprite_line(display->pixels, x, line, *(sprite+i), color);
	}
	display->should_be_rendered = 1;
}


