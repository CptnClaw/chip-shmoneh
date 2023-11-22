#include <SDL.h>
#include <SDL_image.h>
#include "config.h"
#include "graphics.h"

#define LOGICAL_DISPLAY_W 64
#define LOGICAL_DISPLAY_H 32
#define WINDOW_TITLE "chip-shmoneh"

void graphics_clear(struct Graphics *gfx)
{
	SDL_Rect dst_rect = {0, 0, gfx->display_w, gfx->display_h};
	SDL_RenderClear(gfx->renderer);
	SDL_RenderPresent(gfx->renderer);
}

void graphics_draw(struct Graphics *gfx, uint8_t x, uint8_t y, uint8_t n)
{
	/* SDL_UpdateTexture(texture, NULL, pixels, sizeof(uint32_t) * visual_screen_w); */
	/* SDL_RenderCopy(renderer, texture, NULL, &dst_rect); */
}

void graphics_init(struct Graphics *gfx, char *window_title)
{
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	
	gfx->display_w = LOGICAL_DISPLAY_W * DISPLAY_SCALE;
	gfx->display_h = LOGICAL_DISPLAY_H * DISPLAY_SCALE;
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


void demo(int screen_scale)
{



/* 	SDL_Event event; */
/* 	int quit = 0; */
/* 	int count = 0; */


/* 	while (!quit) */
/* 	{ */
/* 		SDL_PollEvent(&event); */
/* 		switch (event.type) */
/* 		{ */
/* 			case SDL_QUIT: */
/* 				quit = 1; */
/* 				break; */
/* 			case SDL_KEYDOWN: */
/* 				switch (event.key.keysym.sym) */
/* 				{ */
/* 					case SDLK_ESCAPE: quit = 1; break; */
/* 				} */
/* 				break; */
/* 		} */

/* 		/1* SDL_Delay(2); *1/ */
/* 		if (count < logical_screen_w * logical_screen_h) */
/* 		{ */
/* 			int loc_y = count / logical_screen_w; */
/* 			int loc_x = count % logical_screen_w + loc_y % 2; */
/* 			flip_pixel(loc_x, loc_y, pixels, logical_screen_w, logical_screen_h, screen_scale); */
/* 			count += 2; */
/* 		} */
/* 		else */
/* 		{ */
/* 			count = 0; */
/* 		} */

/* 	} */

}

void flip_pixel(int x, int y, uint32_t *pixels, int w, int h, int screen_scale)
{
	int vis_x = x * screen_scale;
	int vis_y = y * screen_scale;
	int vis_w = w * screen_scale;

	uint32_t cur_val = pixels[vis_y * vis_w + vis_x];
	uint32_t new_val = 0;
	if (cur_val == 0)	new_val = -1;
	
	for (int i = 0 ; i < screen_scale ; i++)
	{
		for (int j = 0 ; j < screen_scale ; j++)
		{
			pixels[(vis_y+i)*vis_w + (vis_x+j)] = new_val;
		}
	}
}

