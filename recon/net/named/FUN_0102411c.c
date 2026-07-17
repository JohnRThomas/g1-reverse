/* readable reconstruction; identity: FUN_0102411c @ 0x0102411c
 * public-name: FUN_0102411c
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_cpu_relax                            <= FUN_0102a21e @ 0x0102a21e
 * address symbols (name @ address):
 *   g_libc_tz_calc_state                     @ 0x210016f0
 */
/* net-core FUN_0102411c @ 0x102411c — executable extent 654 bytes */
#include <stdint.h>
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"

extern uint64_t sdc_cpu_relax(uint32_t, uint32_t);
extern void FUN_010256dc(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t);

struct words4 { uint32_t word[4]; };

uint64_t FUN_0102411c(uint32_t requested, uint32_t context,
                      uint32_t fatal_arg, uint32_t fatal_extra)
{
    volatile uint8_t *const state = (volatile uint8_t *)0x210016f0U;
    volatile struct words4 *const snapshots =
        (volatile struct words4 *)0x21001740U;
    uint8_t active = state[0x49];
    volatile uint8_t *requested_state =
        state + ((active * 0x20U + requested) * 2U) + 0x50U;

    if (*requested_state == 0) {
        FUN_010256dc(0x70, 0xbf1, fatal_arg, 0, fatal_extra);
        return 0;
    }

    /* Bring a stopped/starting/stopping entry to the stable state.  The
       diagnostic-build flag at 0x10243b0 is a literal zero in this image. */
    uint64_t transition = ((uint64_t)context << 32) | requested;
    while (*requested_state != 1) {
        uint8_t s = *requested_state;
        if ((uint8_t)(s - 4U) <= 2U) {
            *requested_state = 1;
            break;
        }
        transition = sdc_cpu_relax((uint32_t)transition,
                                  (uint32_t)(transition >> 32));
    }

restart_snapshot:
    state[0x39] = 0;
    active = state[0x49];
    uint8_t alternate = (active + 1U) & 1U;

    /* Four 16-byte transfers match the original LDM/STM snapshot copy. */
    snapshots[alternate * 4U + 0] = snapshots[active * 4U + 0];
    snapshots[alternate * 4U + 1] = snapshots[active * 4U + 1];
    snapshots[alternate * 4U + 2] = snapshots[active * 4U + 2];
    snapshots[alternate * 4U + 3] = snapshots[active * 4U + 3];

    volatile uint8_t *old_meta = state + 0x30U + 3U * active;
    volatile uint8_t *new_meta = state + 0x30U + 3U * alternate;
    *(volatile uint16_t *)new_meta = *(volatile uint16_t *)old_meta;
    new_meta[2] = old_meta[2];
    if (state[0x39] != 0)
        goto restart_snapshot;

    /* Remove requested from the alternate snapshot's singly-linked list.
       0x20 is the end-of-list sentinel. */
    uint8_t head = new_meta[1];
    if (head != 0x20U) {
        if (head == (uint8_t)requested) {
            new_meta[1] = state[(alternate * 0x20U + head) * 2U + 0x51U];
            if (new_meta[2] == head)
                new_meta[2] = 0x20U;
        } else {
            uint8_t previous = head;
            uint8_t current = state[(alternate * 0x20U + previous) * 2U + 0x51U];
            while (current != 0x20U && current != (uint8_t)requested) {
                previous = current;
                current = state[(alternate * 0x20U + current) * 2U + 0x51U];
            }
            if (current != 0x20U) {
                state[(alternate * 0x20U + previous) * 2U + 0x51U] =
                    state[(alternate * 0x20U + current) * 2U + 0x51U];
                if (new_meta[2] == current)
                    new_meta[2] = previous;
            }
        }
    }

    uint32_t irq_key = __get_PRIMASK();
    __disable_irq();
    if (state[0x39] != 0) {
        __set_PRIMASK(irq_key);
        goto restart_snapshot;
    }
    state[0x49] = alternate;
    state[0x39] = 0xff;
    if (irq_key == 0)
        __enable_irq();
    return (uint64_t)head;
}
