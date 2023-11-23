#include <SDL.h>

struct Graphics
{
	int display_w;
	int display_h;
	SDL_Rect display_rect;
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *texture;
	uint32_t *pixels;
};

void demo(int screen_scale);
void graphics_init(struct Graphics *gfx, char *window_title);
void graphics_free(struct Graphics *gfx);
void graphics_clear(struct Graphics *gfx);
void graphics_draw(struct Graphics *gfx, uint8_t x, uint8_t y, uint8_t *sprite, uint8_t sprite_height);
