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
