#include "events.h"

int events_handle(struct Hardware *hw, struct Commands *cmd)
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT: 
				hw->is_turned_on = 0;
				return 0;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					hw->is_turned_on = 0;
					return 0;
				}
				switch (event.key.keysym.scancode)
				{
					case SDL_SCANCODE_1: keyboard_press(hw, 0x1); break;
					case SDL_SCANCODE_2: keyboard_press(hw, 0x2); break;
					case SDL_SCANCODE_3: keyboard_press(hw, 0x3); break;
					case SDL_SCANCODE_4: keyboard_press(hw, 0xC); break;
					case SDL_SCANCODE_Q: keyboard_press(hw, 0x4); break;
					case SDL_SCANCODE_W: keyboard_press(hw, 0x5); break;
					case SDL_SCANCODE_E: keyboard_press(hw, 0x6); break;
					case SDL_SCANCODE_R: keyboard_press(hw, 0xD); break;
					case SDL_SCANCODE_A: keyboard_press(hw, 0x7); break;
					case SDL_SCANCODE_S: keyboard_press(hw, 0x8); break;
					case SDL_SCANCODE_D: keyboard_press(hw, 0x9); break;
					case SDL_SCANCODE_F: keyboard_press(hw, 0xE); break;
					case SDL_SCANCODE_Z: keyboard_press(hw, 0xA); break;
					case SDL_SCANCODE_X: keyboard_press(hw, 0x0); break;
					case SDL_SCANCODE_C: keyboard_press(hw, 0xB); break;
					case SDL_SCANCODE_V: keyboard_press(hw, 0xF); break;
					case SDL_SCANCODE_SPACE: cmd->restrict_speed = 0; break;
					default: break;
				}
				break;
			case SDL_KEYUP:
				switch (event.key.keysym.scancode)
				{
					case SDL_SCANCODE_1: keyboard_release(hw, 0x1); break;
					case SDL_SCANCODE_2: keyboard_release(hw, 0x2); break;
					case SDL_SCANCODE_3: keyboard_release(hw, 0x3); break;
					case SDL_SCANCODE_4: keyboard_release(hw, 0xC); break;
					case SDL_SCANCODE_Q: keyboard_release(hw, 0x4); break;
					case SDL_SCANCODE_W: keyboard_release(hw, 0x5); break;
					case SDL_SCANCODE_E: keyboard_release(hw, 0x6); break;
					case SDL_SCANCODE_R: keyboard_release(hw, 0xD); break;
					case SDL_SCANCODE_A: keyboard_release(hw, 0x7); break;
					case SDL_SCANCODE_S: keyboard_release(hw, 0x8); break;
					case SDL_SCANCODE_D: keyboard_release(hw, 0x9); break;
					case SDL_SCANCODE_F: keyboard_release(hw, 0xE); break;
					case SDL_SCANCODE_Z: keyboard_release(hw, 0xA); break;
					case SDL_SCANCODE_X: keyboard_release(hw, 0x0); break;
					case SDL_SCANCODE_C: keyboard_release(hw, 0xB); break;
					case SDL_SCANCODE_V: keyboard_release(hw, 0xF); break;
					case SDL_SCANCODE_SPACE: cmd->restrict_speed = 1; break;
					default: break;
				}
				break;
		}
	}
	return 1;
}
