#include <SDL.h>
#include <SDL_image.h>
#include "config.h"
#include "graphics.h"

void graphics_init(struct Graphics *gfx, char *window_title)
{
	/* Set physical screen dimensions and allocate pixels buffer */
	gfx->width = LOGICAL_DISPLAY_W * CONFIG.DISPLAY_SCALE;
	gfx->height = LOGICAL_DISPLAY_H * CONFIG.DISPLAY_SCALE;
	gfx->buffer = malloc(sizeof(uint32_t) * gfx->height * gfx->width);
	memset(gfx->buffer, BLACK, sizeof(uint32_t) * gfx->height * gfx->width);
	display_init(&(gfx->prev_frame));

	/* Initialize SDL and open window */
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	gfx->window = SDL_CreateWindow(window_title, 
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			gfx->width, gfx->height, 0);
	gfx->renderer = SDL_CreateRenderer(gfx->window, -1, 0);
	gfx->texture = SDL_CreateTexture(gfx->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, gfx->width, gfx->height);
	SDL_Rect dr = {0, 0, gfx->width, gfx->height};
	gfx->rect = dr;

	SDL_SetRenderDrawColor(gfx->renderer, 0, 0, 0, 0);
	SDL_RenderClear(gfx->renderer);
	SDL_RenderPresent(gfx->renderer);
	
	/* Define colors */
	gfx->colors_pallete[0] = 0xFF0000;
	gfx->colors_pallete[1] = 0xFF7B00;
	gfx->colors_pallete[2] = 0xFFFF00;
	gfx->colors_pallete[3] = 0x00FF00;
	gfx->colors_pallete[4] = 0x00FF7B;
	gfx->colors_pallete[5] = 0x00FFFF;
	gfx->colors_pallete[6] = 0x0000FF;
	gfx->colors_pallete[7] = 0xFF00FF;
}

void graphics_free(struct Graphics *gfx)
{
	free(gfx->buffer);
	SDL_DestroyTexture(gfx->texture);
	SDL_DestroyRenderer(gfx->renderer);
	SDL_DestroyWindow(gfx->window);
	IMG_Quit();
	SDL_Quit();
}

void put_to_buffer(uint8_t *pixels, struct Graphics *gfx, int use_double_buffering)
{
	for (int y = 0; y < LOGICAL_DISPLAY_H; y++)
	{
		/* Pick color based on y coordinate */
		int color = WHITE;
		if (CONFIG.COLOR_MODE == COLOR_RAINBOW)
		{
			color = gfx->colors_pallete[y * PALETTE_SIZE / LOGICAL_DISPLAY_H];
		}

		for (int x_byte = 0; x_byte < LOGICAL_DISPLAY_W / 8; x_byte++)
		{
			/* Get a chunk of 8 pixels (byte) to draw */
			uint8_t byte = pixels[y * (LOGICAL_DISPLAY_W / 8) + x_byte];
			uint8_t prev_byte = gfx->prev_frame.pixels[y * (LOGICAL_DISPLAY_W / 8) + x_byte];
			
			for (int bit = 0; bit < 8; bit++)
			{
				/* Calculate on-screen coordinates */
				int x = x_byte * 8 + bit;
				int vis_x = x * CONFIG.DISPLAY_SCALE;
				int vis_y = y * CONFIG.DISPLAY_SCALE;
				int vis_w = LOGICAL_DISPLAY_W * CONFIG.DISPLAY_SCALE;

				/* Find the value of a specific pixel to draw */
				int value = (byte >> (8-bit-1)) & 0x01;
				int prev_value = (prev_byte >> (8-bit-1)) & 0x01;

				// Double buffering: use OR with previous frame to reduce flicker
				if (use_double_buffering)
				{
					value |= prev_value;
				}

				// Draw pixel to screen, surrounded by gap
				int gap = CONFIG.PIXEL_GRID_GAP;
				for (int i = gap; i < CONFIG.DISPLAY_SCALE - gap; i++)
				{
					for (int j = gap; j < CONFIG.DISPLAY_SCALE - gap; j++)
					{
						gfx->buffer[(vis_y + i) * vis_w + (vis_x + j)] = value ? color : BLACK;
					}
				}
			}
		}
	}
}

void graphics_render(struct Graphics *gfx, struct Display *display, int use_double_buffering)
{
	if (CONFIG.RENDER_UNCHANGED_FRAMES || display->should_be_rendered)
	{
		put_to_buffer(display->pixels, gfx, use_double_buffering);
		if (use_double_buffering)
		{
			memcpy(gfx->prev_frame.pixels, display->pixels, sizeof(uint8_t) * DISPLAY_SIZE / 8);
		}
		SDL_UpdateTexture(gfx->texture, NULL, gfx->buffer, sizeof(uint32_t) * gfx->width);
		SDL_RenderCopy(gfx->renderer, gfx->texture, NULL, &(gfx->rect));
		SDL_RenderPresent(gfx->renderer);
		display->should_be_rendered = 0;
	}
}
