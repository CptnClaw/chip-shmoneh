#include "events.h"

int events_check_quit()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	if (event.type == SDL_QUIT ||
		(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
	switch (event.type)
	{
		case SDL_QUIT: return 1; break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
				case SDLK_ESCAPE: return 1; break;
			}
			break;
	}
	return 0;
}
