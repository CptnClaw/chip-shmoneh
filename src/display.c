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
				if (cur_val == BLACK) {
				// Custom color palette support (only supports that devide into Integers)
				if (CONFIG.CUSTOM_COLORS == 0) {
					new_val = WHITE;
				}
				else if (CONFIG.CUSTOM_COLORS > 32) {
					new_val = WHITE;
				}
				// disable non-Integers numbers being used (defaults to white instead)
				else if (CONFIG.CUSTOM_COLORS == 3) {
					new_val = WHITE;
				}
				else if (CONFIG.CUSTOM_COLORS == 5) {
					new_val = WHITE;
				}
				else if (CONFIG.CUSTOM_COLORS == 6) {
					new_val = WHITE;
				}
				else if (CONFIG.CUSTOM_COLORS == 7) {
					new_val = WHITE;
				}
				else if (CONFIG.CUSTOM_COLORS == 9) {
					new_val = WHITE;
				}
				else if (CONFIG.CUSTOM_COLORS == 11) {
					new_val = WHITE;
				}
				else if (CONFIG.CUSTOM_COLORS == 12) {
					new_val = WHITE;
				}
				else if (CONFIG.CUSTOM_COLORS == 13) {
					new_val = WHITE;
				}
				else if (CONFIG.CUSTOM_COLORS == 14) {
					new_val = WHITE;
				}
				else if (CONFIG.CUSTOM_COLORS == 15) {
					new_val = WHITE;
				}
				else if (CONFIG.CUSTOM_COLORS == 17) {
					new_val = WHITE;
				}
				else if (CONFIG.CUSTOM_COLORS == 18) {
					new_val = WHITE;
				}
				else if (CONFIG.CUSTOM_COLORS == 19) {
					new_val = WHITE;
				}
				else if (CONFIG.CUSTOM_COLORS == 20) {
					new_val = WHITE;
				}
				else if (CONFIG.CUSTOM_COLORS == 21) {
					new_val = WHITE;
				}
				else if (CONFIG.CUSTOM_COLORS == 22) {
					new_val = WHITE;
				}
				else if (CONFIG.CUSTOM_COLORS == 23) {
					new_val = WHITE;
				}
				else if (CONFIG.CUSTOM_COLORS == 24) {
					new_val = WHITE;
				}
				else if (CONFIG.CUSTOM_COLORS == 25) {
					new_val = WHITE;
				}
				else if (CONFIG.CUSTOM_COLORS == 26) {
					new_val = WHITE;
				}
				else if (CONFIG.CUSTOM_COLORS == 27) {
					new_val = WHITE;
				}
				else if (CONFIG.CUSTOM_COLORS == 28) {
					new_val = WHITE;
				}
				else if (CONFIG.CUSTOM_COLORS == 29) {
					new_val = WHITE;
				}
				else if (CONFIG.CUSTOM_COLORS == 30) {
					new_val = WHITE;
				}
				else if (CONFIG.CUSTOM_COLORS == 31) {
					new_val = WHITE;
				}
				// 1 custom color
				else if (CONFIG.CUSTOM_COLORS == 1) {
					new_val = CONFIG.COLOR1;
				}
				// 2 custom colors
				else if (CONFIG.CUSTOM_COLORS == 2) {
					if (y < 16)
					new_val = CONFIG.COLOR1;
					else
					new_val = CONFIG.COLOR2;
				}
				// 4 custom colors
				else if (CONFIG.CUSTOM_COLORS == 4) {
					if (y < 8)
						new_val = CONFIG.COLOR1;
					else if (y < 16 | y < 8)
						new_val = CONFIG.COLOR2;
					else if (y < 24 | y < 16)
						new_val = CONFIG.COLOR3;
					else
						new_val = CONFIG.COLOR4;
				}
				// 8 custom colors
				else if (CONFIG.CUSTOM_COLORS == 8) {
					if (y < 4)
						new_val = CONFIG.COLOR1;
					else if (y < 8 | y < 4) {
						new_val = CONFIG.COLOR2;
					}
					else if (y < 12 | y < 8) {
						new_val = CONFIG.COLOR3;
					}
					else if (y < 16 | y < 12) {
						new_val = CONFIG.COLOR4;
					}
					else if (y < 20 | y < 16) {
						new_val = CONFIG.COLOR5;
					}
					else if (y < 24 | y < 20) {
						new_val = CONFIG.COLOR6;
					}
					else if (y < 28 | y < 24) {
						new_val = CONFIG.COLOR7;
					}
					else
						new_val = CONFIG.COLOR8;
				}
				// 16 custom colors
				else if (CONFIG.CUSTOM_COLORS == 16) {
					if (y < 2)
						new_val = CONFIG.COLOR1;
					else if (y < 4 | y < 2) {
						new_val = CONFIG.COLOR2;
					}
					else if (y < 6 | y < 4) {
						new_val = CONFIG.COLOR3;
					}
					else if (y < 8 | y < 6) {
						new_val = CONFIG.COLOR4;
					}
					else if (y < 10 | y < 8) {
						new_val = CONFIG.COLOR5;
					}
					else if (y < 12 | y < 10) {
						new_val = CONFIG.COLOR6;
					}
					else if (y < 14 | y < 12) {
						new_val = CONFIG.COLOR7;
					}
					else if (y < 16 | y < 14) {
						new_val = CONFIG.COLOR8;
					}
					else if (y < 18 | y < 16) {
						new_val = CONFIG.COLOR9;
					}
					else if (y < 20 | y < 18) {
						new_val = CONFIG.COLOR10;
					}
					else if (y < 22 | y < 20) {
						new_val = CONFIG.COLOR11;
					}
					else if (y < 24 | y < 22) {
						new_val = CONFIG.COLOR12;
					}
					else if (y < 26 | y < 24) {
						new_val = CONFIG.COLOR13;
					}
					else if (y < 28 | y < 24) {
						new_val = CONFIG.COLOR14;
					}
					else if (y < 30 | y < 28) {
						new_val = CONFIG.COLOR15;
					}
					else
						new_val = CONFIG.COLOR16;
				}
				// 32 custom colors
				else if (CONFIG.CUSTOM_COLORS == 32) {
					if (y < 1)
						new_val = CONFIG.COLOR1;
					else if (y < 2 | y < 1) {
						new_val = CONFIG.COLOR2;
					}
					else if (y < 3 | y < 2) {
						new_val = CONFIG.COLOR3;
					}
					else if (y < 4 | y < 3) {
						new_val = CONFIG.COLOR4;
					}
					else if (y < 5 | y < 4) {
						new_val = CONFIG.COLOR5;
					}
					else if (y < 6 | y < 5) {
						new_val = CONFIG.COLOR6;
					}
					else if (y < 7 | y < 6) {
						new_val = CONFIG.COLOR7;
					}
					else if (y < 8 | y < 7) {
						new_val = CONFIG.COLOR8;
					}
					else if (y < 9 | y < 8) {
						new_val = CONFIG.COLOR9;
					}
					else if (y < 10 | y < 9) {
						new_val = CONFIG.COLOR10;
					}
					else if (y < 11 | y < 10) {
						new_val = CONFIG.COLOR11;
					}
					else if (y < 12 | y < 11) {
						new_val = CONFIG.COLOR12;
					}
					else if (y < 13 | y < 12) {
						new_val = CONFIG.COLOR13;
					}
					else if (y < 14 | y < 13) {
						new_val = CONFIG.COLOR14;
					}
					else if (y < 15 | y < 14) {
						new_val = CONFIG.COLOR15;
					}
					else if (y < 16 | y < 15) {
						new_val = CONFIG.COLOR16;
					}
					else if (y < 17 | y < 16) {
						new_val = CONFIG.COLOR17;
					}
					else if (y < 18 | y < 17) {
						new_val = CONFIG.COLOR18;
					}
					else if (y < 19 | y < 18) {
						new_val = CONFIG.COLOR19;
					}
					else if (y < 20 | y < 19) {
						new_val = CONFIG.COLOR20;
					}
					else if (y < 21 | y < 20) {
						new_val = CONFIG.COLOR21;
					}
					else if (y < 22 | y < 21) {
						new_val = CONFIG.COLOR22;
					}
					else if (y < 23 | y < 22) {
						new_val = CONFIG.COLOR23;
					}
					else if (y < 24 | y < 23) {
						new_val = CONFIG.COLOR24;
					}
					else if (y < 25 | y < 24) {
						new_val = CONFIG.COLOR25;
					}
					else if (y < 26 | y < 25) {
						new_val = CONFIG.COLOR26;
					}
					else if (y < 27 | y < 26) {
						new_val = CONFIG.COLOR27;
					}
					else if (y < 28 | y < 27) {
						new_val = CONFIG.COLOR28;
					}
					else if (y < 29 | y < 28) {
						new_val = CONFIG.COLOR29;
					}
					else if (y < 30 | y < 29) {
						new_val = CONFIG.COLOR30;
					}
					else if (y < 31 | y < 30) {
						new_val = CONFIG.COLOR31;
					}
					else
						new_val = CONFIG.COLOR32;
				}
				else new_val = WHITE;
				}
				// end of custom color support
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
		(*collision) |= draw_sprite_line(display->pixels, x, line, *(sprite+i));
	}
	display->should_be_rendered = 1;
}


