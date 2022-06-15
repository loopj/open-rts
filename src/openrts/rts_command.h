#ifndef RTS_COMMAND_H
#define RTS_COMMAND_H

/**
 * @file
 */

/**
 * @addtogroup openrts
 * @{
 */

/**
 * Command sent by a remote, or received by a receiver as part of
 * an rts_frame event.
 *
 * Commands reflect buttons on a remote, eg "Up", "Down", "My", or certain
 * combinations of button presses.
 */
enum rts_command {
    RTS_COMMAND_MY         = 0x1, ///< My/Stop button pressed
    RTS_COMMAND_UP         = 0x2, ///< Up button pressed
    RTS_COMMAND_MY_UP      = 0x3, ///< My and Up buttons both pressed
    RTS_COMMAND_DOWN       = 0x4, ///< Down button pressed
    RTS_COMMAND_MY_DOWN    = 0x5, ///< My and Down buttons both pressed
    RTS_COMMAND_UP_DOWN    = 0x6, ///< Up and Down buttons both pressed
    RTS_COMMAND_MY_UP_DOWN = 0x7, ///< My, Up and Down buttons all pressed
    RTS_COMMAND_PROG       = 0x8, ///< Prog button pressed
    RTS_COMMAND_SUN_FLAG   = 0x9, ///< Sun and Flag button pressed (Soliris)
    RTS_COMMAND_FLAG       = 0xA, ///< Flag button pressed (Soliris)
};

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Get a string representation of the given rts_command
 *
 * @param command the rts_command to convert
 * @return const char* a string representation of the rts_command
 */
const char *rts_command_to_string(enum rts_command command);

#ifdef __cplusplus
} // extern "C"
#endif

/**
 * @}
 */

#endif // RTS_COMMAND_H