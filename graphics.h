#include <SDL.h>

struct Graphics
{
	int x;
};

void demo(int screen_scale);
void graphics_clear(struct Graphics *gfx);
void graphics_draw(struct Graphics *gfx, uint8_t x, uint8_t y, uint8_t n);
