#include <stdio.h>
#include <SDL.h>
#include "clock.h"

void clock_init(struct Clock *clk)
{
	clk->time_before = SDL_GetTicks64();
	clk->prev_sec = clk->time_before / 1000;
	clk->frame_count = 0;
}

void clock_tick(struct Clock *clk)
{
	clk->time_before = SDL_GetTicks64();
	Uint64 cur_sec = clk->time_before / 1000;

	if (cur_sec > clk->prev_sec)
	{
		printf("FPS = %d\n", clk->frame_count);
		clk->frame_count = 0;
		clk->prev_sec = cur_sec;
	}
	else
	{
		clk->frame_count++;
	}
}

void clock_tock(struct Clock *clk, int restrict_speed)
{
	if (restrict_speed)
	{
		Uint64 time_after = SDL_GetTicks64();
		Uint32 time_interval = time_after - clk->time_before;
		Uint32 time_to_wait = MS_PER_FRAME > time_interval ? MS_PER_FRAME - time_interval : 0;
		SDL_Delay(time_to_wait);
	}
}

