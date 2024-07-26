#ifndef _COMMANDS_
#define _COMMANDS_

struct Commands
{
	// Controls whether FPS should be restricted to 60 FPS or unrestricted
	int restrict_speed;
	
	// Next frame should be saved or loaded from file
	int save_state;
	int load_state; 

	// Pause emulation while this is true
	int pause;
	
	// Rewind to previous emulation states while this is true
	int rewind;
};

void commands_init(struct Commands *cmd);

#endif /* ifndef _COMMANDS_ */
