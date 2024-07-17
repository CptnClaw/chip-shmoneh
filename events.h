#include <SDL.h>
#include "hardware.h"
#include "commands.h"

/* Processes incoming events and updates hardware and commands accordingly.
 * Returns: 
 *		1 if everything is in order,
		0 if recieved exit signal. */
int events_handle(struct Hardware *hw, struct Commands *cmd);
