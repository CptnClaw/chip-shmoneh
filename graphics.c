#include <SDL.h>
#include <SDL_image.h>
#include "graphics.h"


void init()
{
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
}

void deinit()
{
	IMG_Quit();
	SDL_Quit();
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


void demo(int screen_scale)
{
	init();

	int logical_screen_w = 64;
	int logical_screen_h = 32;
	int visual_screen_w = logical_screen_w * screen_scale;
	int visual_screen_h = logical_screen_h * screen_scale;

	SDL_Window *screen = SDL_CreateWindow("title", 
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			visual_screen_w, visual_screen_h, 0);
	SDL_Renderer *renderer = SDL_CreateRenderer(screen, -1, 0);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

	SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, visual_screen_w, visual_screen_h);
	uint32_t *pixels = malloc(sizeof(uint32_t) * visual_screen_w * visual_screen_h);
	SDL_Event event;
	int quit = 0;
	int count = 0;


	while (!quit)
	{
		SDL_PollEvent(&event);
		switch (event.type)
		{
			case SDL_QUIT:
				quit = 1;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
					case SDLK_ESCAPE: quit = 1; break;
				}
				break;
		}

		/* SDL_Delay(2); */
		if (count < logical_screen_w * logical_screen_h)
		{
			int loc_y = count / logical_screen_w;
			int loc_x = count % logical_screen_w + loc_y % 2;
			flip_pixel(loc_x, loc_y, pixels, logical_screen_w, logical_screen_h, screen_scale);
			count += 2;
		}
		else
		{
			count = 0;
		}

		SDL_Rect dst_rect = {0, 0, visual_screen_w, visual_screen_h};
		SDL_RenderClear(renderer);
		SDL_UpdateTexture(texture, NULL, pixels, sizeof(uint32_t) * visual_screen_w);
		SDL_RenderCopy(renderer, texture, NULL, &dst_rect);
		SDL_RenderPresent(renderer);
	}

	free(pixels);
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(screen);
}
