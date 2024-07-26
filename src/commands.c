#include "commands.h"

void commands_init(struct Commands *cmd)
{
    cmd->restrict_speed = 1;
    cmd->save_state = 0;
    cmd->load_state = 0;
    cmd->pause = 0;
    cmd->rewind = 0;
}