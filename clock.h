#include <SDL.h>

struct Clock
{
	Uint64 timer;
	int num_ticks;
};

/* Initializes the clock, starting the timer and zeroing number of ticks */
void clock_init(struct Clock *clock);

/* Increase the number of ticks by one. 
 * Once it reaches INSTRUCTIONS_PER_SECOND, wait until a second passes since last timer reset,
 * and then re-init the clock */
void clock_tick(struct Clock *clock);
