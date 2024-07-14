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

void put_to_buffer(uint32_t *pixels, uint32_t *buffer)
{
	for (int x=0; x<LOGICAL_DISPLAY_W; x++)
	{
		for (int y=0; y<LOGICAL_DISPLAY_H; y++)
		{
			int vis_x = x * CONFIG.DISPLAY_SCALE;
			int vis_y = y * CONFIG.DISPLAY_SCALE;
			int vis_w = LOGICAL_DISPLAY_W * CONFIG.DISPLAY_SCALE;
			int gap = CONFIG.PIXEL_GRID_GAP;
			
			uint32_t value = pixels[y * LOGICAL_DISPLAY_W + x];
			
			for (int i = gap ; i < CONFIG.DISPLAY_SCALE - gap ; i++)
			{
				for (int j = gap ; j < CONFIG.DISPLAY_SCALE - gap ; j++)
				{
					buffer[(vis_y+i)*vis_w + (vis_x+j)] = value;	
				}
			}
		}
	}
}

void graphics_render(struct Graphics *gfx, struct Display *display)
{
	if (display->should_be_rendered)
	{
		put_to_buffer(display->pixels, gfx->buffer);
		SDL_UpdateTexture(gfx->texture, NULL, gfx->buffer, sizeof(uint32_t) * gfx->width);
		/* SDL_RenderClear(gfx->renderer); */
		SDL_RenderCopy(gfx->renderer, gfx->texture, NULL, &(gfx->rect));
		SDL_RenderPresent(gfx->renderer);
		display->should_be_rendered = 0;
	}
}


