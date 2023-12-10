#include <SDL.h>
#include "hardware.h"

/* Processes incoming events and updates hardware accordingly.
 * Returns: 
 *		1 if everything is in order,
		0 if recieved exit signal. */
int events_handle(struct Hardware *hw);
