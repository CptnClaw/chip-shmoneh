#ifndef _CLOCK_
#define _CLOCK_

#include <SDL.h>

// Frames per second
#define FPS  60
#define MS_PER_FRAME  (1000 / FPS)

struct Clock
{
	// Keeps track of main loop speed
	Uint64 time_before;

	// Used to calculate FPS
	int frame_count;
	int prev_sec;
};

// Call this before using the clock.
void clock_init(struct Clock *clk);

// Call this at the start of main loop.
void clock_tick(struct Clock *clk);

// Call this is at the end of main loop.
// Sleeps until ready for next frame.
void clock_tock(struct Clock *clk);

#endif /* ifndef _CLOCK_ */
