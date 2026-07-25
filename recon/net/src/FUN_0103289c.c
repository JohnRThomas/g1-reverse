/* net-core FUN_0103289c @ 0x103289c  (P4 iteration 24; parity 300/300 trials + 50 directed null-handler trials, 0 mismatches) */
/* CPUNET ESB EVENT DISPATCH (IRQ 0x1d / SWI handler) @ 0x0103289c.
 * Raw back-map: FUN_0103289c@0x0103289c; true extent 0x5e (a nop pad then the
 * literal pool 0x010328fc = 0x210049a8, 0x01032900 = 0x210049b0,
 * 0x01032904 = 0x21004a90).
 *
 * FUN_010333b4 installs it with connect_radio_irq_handler(0x1d, 2, ...) as the
 * RUNTIME Thumb pointer 0x0103309d (= analysis 0x0103289c | 1).  It drains the
 * pending-event bitmap at 0x210049b0 under BASEPRI and calls the ESB
 * `event_handler` published at 0x21004a90 once per set bit, with a stack event
 * object whose byte 0 is the event id (0 = TX failed, 1 = TX success,
 * 2 = RX received) -- exactly what FUN_0102b50c reads.
 */
#include <stdint.h>

struct g1_esb_event {
    uint8_t id;
    uint8_t reserved[3];
    uint32_t tx_attempts;
    uint32_t scratch;
};

void FUN_0103289c(void)
{
    volatile uint32_t *const attempts = (volatile uint32_t *)0x210049a8u;
    volatile uint32_t *const pending = (volatile uint32_t *)0x210049b0u;
    void (*volatile *const handler)(struct g1_esb_event *) =
        (void (*volatile *)(struct g1_esb_event *))0x21004a90u;
    struct g1_esb_event event;
    uint32_t basepri;
    uint32_t flags;

    event.tx_attempts = *attempts;

    __asm__ volatile ("mrs %0, basepri" : "=r" (basepri));
    __asm__ volatile ("msr basepri_max, %0" :: "r" (0x40u) : "memory");
    __asm__ volatile ("isb 0xf" ::: "memory");
    flags = *pending;
    *pending = 0;
    __asm__ volatile ("msr basepri, %0" :: "r" (basepri) : "memory");
    __asm__ volatile ("isb 0xf" ::: "memory");

    if (*handler == 0)
        return;
    if (flags & 1u) {
        event.id = 0;
        (*handler)(&event);
    }
    if (flags & 2u) {
        event.id = 1;
        (*handler)(&event);
    }
    if (flags & 4u) {
        event.id = 2;
        (*handler)(&event);
    }
}
