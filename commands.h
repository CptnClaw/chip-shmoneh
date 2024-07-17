#ifndef _COMMANDS_
#define _COMMANDS_

struct Commands
{
	// Controls whether FPS should be restricted to 60 FPS or unrestricted
	int restrict_speed;
};

int commands_init(struct Commands *cmd);

#endif /* ifndef _COMMANDS_ */
