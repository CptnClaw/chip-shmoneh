#include <SDL.h>
#include <SDL_image.h>
#include "config.h"
#include "graphics.h"

#define LOGICAL_DISPLAY_W 64
#define LOGICAL_DISPLAY_H 32


void graphics_init(struct Graphics *gfx, char *window_title)
{
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	
	gfx->display_w = LOGICAL_DISPLAY_W * DISPLAY_SCALE;
	gfx->display_h = LOGICAL_DISPLAY_H * DISPLAY_SCALE;
	SDL_Rect dr = {0, 0, gfx->display_w, gfx->display_h};
	gfx->display_rect = dr;
	gfx->pixels = malloc(sizeof(uint32_t) * gfx->display_h * gfx->display_w);

	gfx->window = SDL_CreateWindow(window_title, 
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			gfx->display_w, gfx->display_h, 0);
	gfx->renderer = SDL_CreateRenderer(gfx->window, -1, 0);
	SDL_SetRenderDrawColor(gfx->renderer, 0, 0, 0, 0);
	gfx->texture = SDL_CreateTexture(gfx->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, gfx->display_w, gfx->display_h);

	graphics_clear(gfx);
}

void graphics_free(struct Graphics *gfx)
{
	free(gfx->pixels);
	SDL_DestroyTexture(gfx->texture);
	SDL_DestroyRenderer(gfx->renderer);
	SDL_DestroyWindow(gfx->window);

	IMG_Quit();
	SDL_Quit();
}

void graphics_clear(struct Graphics *gfx)
{
	for (int i=0; i<gfx->display_h * gfx->display_w; i++)
	{
		gfx->pixels[i] = 0;
	}
	SDL_RenderClear(gfx->renderer);
	SDL_RenderPresent(gfx->renderer);
}

void flip_pixel(uint32_t *pixels, int x, int y)
{
	int vis_x = x * DISPLAY_SCALE;
	int vis_y = y * DISPLAY_SCALE;
	int vis_w = LOGICAL_DISPLAY_W * DISPLAY_SCALE;

	uint32_t cur_val = pixels[vis_y * vis_w + vis_x];
	uint32_t new_val = 0;
	if (cur_val == 0)	new_val = -1;
	
	for (int i = 0 ; i < DISPLAY_SCALE ; i++)
	{
		for (int j = 0 ; j < DISPLAY_SCALE ; j++)
		{
			pixels[(vis_y+i)*vis_w + (vis_x+j)] = new_val;
		}
	}
}

void draw_sprite_line(uint32_t *pixels, int x, int y, uint8_t line)
{
	for (uint8_t j=0; j<8; j++)
	{
		if ((line & (128 >> j)) != 0)
		{
			flip_pixel(pixels, x+j, y);
		}
	}
}

void graphics_draw(struct Graphics *gfx, uint8_t x, uint8_t y, uint8_t *sprite, uint8_t sprite_height)
{
	x = x % LOGICAL_DISPLAY_W;
	y = y % LOGICAL_DISPLAY_H;
	for (uint8_t i=0; i<sprite_height; i++)
	{
		draw_sprite_line(gfx->pixels, x, y+i, *(sprite+i));
	}
	SDL_UpdateTexture(gfx->texture, NULL, gfx->pixels, sizeof(uint32_t) * gfx->display_w);
	SDL_RenderCopy(gfx->renderer, gfx->texture, NULL, &(gfx->display_rect));
	SDL_RenderPresent(gfx->renderer);
}


