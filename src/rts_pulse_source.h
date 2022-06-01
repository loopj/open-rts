#ifndef RTS_PULSE_SOURCE_H
#define RTS_PULSE_SOURCE_H

#include "rts_frame_builder.h"

#include <stdbool.h>
#include <stdint.h>

/**
 * Provides an interface for a source of RTS pulses, eg a GPIO or radio.
 *
 * Bundled implementations are provided for Linux/Raspberry Pi gpiod
 * (#rts_pulse_source_init_gpiod).
 *
 * Implementations must define the enable, disable, and update
 * functions and set the function pointers in the rts_pulse_source struct.
 *
 * When a new pulse is detected in rts_pulse_source_update, implementations
 * should call rts_frame_builder_handle_pulse on the observer.
 *
 */
struct rts_pulse_source {
    struct rts_frame_builder *frame_builder;

    void (*enable)(struct rts_pulse_source *pulse_source);
    void (*disable)(struct rts_pulse_source *pulse_source);
    void (*update)(struct rts_pulse_source *pulse_source);

    bool last_state;
    uint64_t last_updated;

    union {
        void *user_data_ptr;
        int user_data_int;
    };
};

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Enable the pulse source
 *
 * @relates rts_pulse_source
 *
 * @param pulse_source the rts_pulse_source struct to enable
 */
void rts_pulse_source_enable(struct rts_pulse_source *pulse_source);

/**
 * Disable the pulse source
 *
 * @relates rts_pulse_source
 *
 * @param pulse_source the rts_pulse_source struct to disable
 */
void rts_pulse_source_disable(struct rts_pulse_source *pulse_source);

/**
 * Check for new pulse data, should be called every loop()
 *
 * @relates rts_pulse_source
 *
 * @param pulse_source the rts_pulse_source struct to update
 */
void rts_pulse_source_update(struct rts_pulse_source *pulse_source);

/**
 * Attach an observer
 *
 * @relates rts_pulse_source
 *
 * @param pulse_source the rts_pulse_source to be observed
 * @param frame_builder the rts_frame_builder observing this source.
 */
void rts_pulse_source_attach(struct rts_pulse_source *pulse_source,
                             struct rts_frame_builder *frame_builder);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // RTS_PULSE_SOURCE_H