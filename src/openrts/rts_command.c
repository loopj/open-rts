#include "rts_command.h"

const char *rts_command_to_string(enum rts_command command)
{
    switch (command) {
    case RTS_COMMAND_MY:
        return "My";
    case RTS_COMMAND_UP:
        return "Up";
    case RTS_COMMAND_MY_UP:
        return "My+Up";
    case RTS_COMMAND_DOWN:
        return "Down";
    case RTS_COMMAND_MY_DOWN:
        return "My+Down";
    case RTS_COMMAND_UP_DOWN:
        return "Up+Down";
    case RTS_COMMAND_MY_UP_DOWN:
        return "My+Up+Down";
    case RTS_COMMAND_PROG:
        return "Prog";
    case RTS_COMMAND_SUN_FLAG:
        return "Sun+Flag";
    case RTS_COMMAND_FLAG:
        return "Flag";
    default:
        return "Unknown";
    }
}