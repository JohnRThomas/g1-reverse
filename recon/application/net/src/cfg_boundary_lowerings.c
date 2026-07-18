/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Strong owner for the sole synthetic CFG-boundary call retained by the
 * differential reconstruction harness.  Original CPUNET instructions at
 * 0x0100d4cc are exactly:
 *
 *     movs r0, #0
 *     bx   lr
 *
 * Keeping this as an out-of-line owner preserves the harness's boundary-call
 * model while giving the integrated image the original C semantics.
 */
unsigned int FUN_shadow_default(void)
{
    return 0;
}

#include <stddef.h>
#include <stdint.h>

#include <ipc_rpmsg_static_vrings.h>

/* Compiler-outlined forms of two pinned NCS 2.5.1 static inline helpers. */
size_t ipc_static_vrings_shm_size(unsigned int descriptor_count,
                                  unsigned int buffer_size)
{
    return shm_size(descriptor_count, buffer_size);
}

int rtc_compare_event_clear(int32_t channel)
{
    volatile uint32_t *event =
        (volatile uint32_t *)(0x41016000u + 0x140u +
                              (uint32_t)channel * sizeof(uint32_t));

    *event = 0u;
    (void)*event;
    return 0;
}

/*
 * Ghidra missed this 88-byte function boundary at 0x0101b4f4.  The raw
 * back-map remains in FUN_01018df8.c.  This source is an integration closure,
 * not an archive alias: it follows the complete Thumb body through 0x0101b54a
 * and deliberately leaves the 24-byte call frame uninitialized as firmware
 * does before FUN_0101a38c fills it.
 */
extern int controller_timing_snapshot_build(void *frame, unsigned int,
                                            unsigned int, unsigned int);
extern uint8_t *controller_radio_state_get(void);
extern void controller_radio_event_cleanup(void);
extern void FUN_01022a84(void);
extern int sdc_conn_window_admit(unsigned int, void *frame);
extern void sdc_assertion_fail(unsigned int, unsigned int)
    __attribute__((noreturn));

void sdc_event_publish(unsigned int unused0, unsigned int unused1,
                       unsigned int unused2, unsigned int unused3)
{
    volatile uint8_t *const state = (volatile uint8_t *)0x210010a0u;
    uint8_t frame[24];

    (void)unused0;
    (void)unused1;
    (void)unused2;
    (void)unused3;

    for (;;) {
        if (state[20] == 0u) {
            return;
        }
        if (state[1] == 0u) {
            break;
        }
        if (controller_timing_snapshot_build(frame, 0u, 0u, 0u) == 0) {
            state[2] = 1u;
            continue;
        }
        if (sdc_conn_window_admit(*controller_radio_state_get(), frame) == 0) {
            sdc_assertion_fail(0x21u, 0x7cbu);
        }
    }

    controller_radio_event_cleanup();
    FUN_01022a84();
    state[20] = 0u;
    state[21] = 0u;
}
