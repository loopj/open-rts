#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    RTS_COMMAND_MY          = 0x1, ///< My button pressed (sometimes labelled "Stop")
    RTS_COMMAND_UP          = 0x2, ///< Up button pressed
    RTS_COMMAND_MY_UP       = 0x3, ///< My and Up buttons both pressed
    RTS_COMMAND_DOWN        = 0x4, ///< Down button pressed
    RTS_COMMAND_MY_DOWN     = 0x5, ///< My and Down buttons both pressed
    RTS_COMMAND_UP_DOWN     = 0x6, ///< Up and Down buttons both pressed
    RTS_COMMAND_MY_UP_DOWN  = 0x7, ///< My, Up and Down buttons all pressed
    RTS_COMMAND_PROG        = 0x8, ///< Prog button pressed
    RTS_COMMAND_SUN_FLAG    = 0x9, ///< Sun and Flag button pressed (Soliris)
    RTS_COMMAND_FLAG        = 0xA, ///< Flag button pressed (Soliris)
} rts_command_t;

#ifdef __cplusplus
} // extern "C"
#endif