#include "events.h"

int events_handle(struct Hardware *hw)
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT: return 0;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					return 0;
				}
				switch (event.key.keysym.scancode)
				{
					case SDL_SCANCODE_1: keyboard_down(hw, 0x1); break;
					case SDL_SCANCODE_2: keyboard_down(hw, 0x2); break;
					case SDL_SCANCODE_3: keyboard_down(hw, 0x3); break;
					case SDL_SCANCODE_4: keyboard_down(hw, 0xC); break;
					case SDL_SCANCODE_Q: keyboard_down(hw, 0x4); break;
					case SDL_SCANCODE_W: keyboard_down(hw, 0x5); break;
					case SDL_SCANCODE_E: keyboard_down(hw, 0x6); break;
					case SDL_SCANCODE_R: keyboard_down(hw, 0xD); break;
					case SDL_SCANCODE_A: keyboard_down(hw, 0x7); break;
					case SDL_SCANCODE_S: keyboard_down(hw, 0x8); break;
					case SDL_SCANCODE_D: keyboard_down(hw, 0x9); break;
					case SDL_SCANCODE_F: keyboard_down(hw, 0xE); break;
					case SDL_SCANCODE_Z: keyboard_down(hw, 0xA); break;
					case SDL_SCANCODE_X: keyboard_down(hw, 0x0); break;
					case SDL_SCANCODE_C: keyboard_down(hw, 0xB); break;
					case SDL_SCANCODE_V: keyboard_down(hw, 0xF); break;
					default: break;
				}
				break;
			case SDL_KEYUP:
				switch (event.key.keysym.scancode)
				{
					case SDL_SCANCODE_1: keyboard_up(hw, 0x1); break;
					case SDL_SCANCODE_2: keyboard_up(hw, 0x2); break;
					case SDL_SCANCODE_3: keyboard_up(hw, 0x3); break;
					case SDL_SCANCODE_4: keyboard_up(hw, 0xC); break;
					case SDL_SCANCODE_Q: keyboard_up(hw, 0x4); break;
					case SDL_SCANCODE_W: keyboard_up(hw, 0x5); break;
					case SDL_SCANCODE_E: keyboard_up(hw, 0x6); break;
					case SDL_SCANCODE_R: keyboard_up(hw, 0xD); break;
					case SDL_SCANCODE_A: keyboard_up(hw, 0x7); break;
					case SDL_SCANCODE_S: keyboard_up(hw, 0x8); break;
					case SDL_SCANCODE_D: keyboard_up(hw, 0x9); break;
					case SDL_SCANCODE_F: keyboard_up(hw, 0xE); break;
					case SDL_SCANCODE_Z: keyboard_up(hw, 0xA); break;
					case SDL_SCANCODE_X: keyboard_up(hw, 0x0); break;
					case SDL_SCANCODE_C: keyboard_up(hw, 0xB); break;
					case SDL_SCANCODE_V: keyboard_up(hw, 0xF); break;
					default: break;
				}
				break;
		}
	}
	return 1;
}
