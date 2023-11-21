#include <SDL.h>
#include "config.h"
#include "clock.h"

void clock_init(struct Clock *clock)
{
	clock->timer = SDL_GetTicks64();
	clock->num_ticks = 0;
}

void clock_tick(struct Clock *clock)
{
	clock->num_ticks++;
	if (clock->num_ticks == INSTRUCTIONS_PER_SECOND)
	{
		while (SDL_GetTicks64() <= (clock->timer + 1000))
		{
			/* Wait */
		}
		clock_init(clock);
	}
}
