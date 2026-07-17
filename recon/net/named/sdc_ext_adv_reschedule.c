/* readable reconstruction; identity: FUN_010140ec @ 0x010140ec
 * public-name: sdc_ext_adv_reschedule
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 *   sdc_controller_random_get                <= FUN_0100f63c @ 0x0100f63c
 *   controller_radio_event_cleanup           <= FUN_01020634 @ 0x01020634
 *   sdc_conn_window_admit                    <= FUN_010231c8 @ 0x010231c8
 */
/* net-core sdc_ext_adv_reschedule @ 0x010140ec
 * Raw backmap: FUN_010140ec. */
#include <stdint.h>

extern void sdc_assertion_fail(uint32_t, uint32_t);
extern uint32_t sdc_controller_random_get(void);
extern uint64_t FUN_010122b4(volatile uint8_t *, uint32_t);
extern uint32_t FUN_0101232c(volatile uint8_t *);
extern void FUN_010128bc(volatile uint8_t *, uint32_t, uint32_t, uint32_t);
extern uint16_t FUN_01012c14(volatile uint8_t *);
extern void controller_radio_event_cleanup(void);
extern void FUN_01022a84(void);
extern int sdc_conn_window_admit(uint32_t, volatile uint8_t *);

void sdc_ext_adv_reschedule(volatile uint8_t *adv, uint32_t mode)
{
    uint32_t jitter = 0;
    uint32_t low;
    uint32_t high;
    uint32_t add;
    uint32_t carry;
    uint16_t period;

    if (mode != 0) {
        if (mode == 1) {
            adv[0x108] = 0;
            controller_radio_event_cleanup();
            FUN_01022a84();
            return;
        }
        sdc_assertion_fail(0x30u, 0x7ddu);
        __builtin_unreachable();
    }
    period = *(volatile uint16_t *)(adv + 0x22);
    if (period != 0) {
        jitter = sdc_controller_random_get() % period;
    }
    low = *(volatile uint32_t *)(adv + 0x118);
    high = *(volatile uint32_t *)(adv + 0x11c);
    add = FUN_0101232c(adv) + jitter;
    carry = add + low < add;
    *(volatile uint16_t *)(adv + 0x132) = 0x102;
    *(volatile uint32_t *)(adv + 0x138) = add + low;
    adv[0x128] = 0;
    *(volatile uint32_t *)(adv + 0x13c) = high + carry;
    *(volatile uint16_t *)(adv + 0x130) = FUN_01012c14(adv);
    low = *(volatile uint32_t *)(adv + 0x138);
    high = *(volatile uint32_t *)(adv + 0x13c);
    *(volatile uint32_t *)(adv + 0x118) = low;
    *(volatile uint32_t *)(adv + 0x11c) = high;

    if (adv[0x148] == 0) {
        uint32_t deadline_low = *(volatile uint32_t *)(adv + 0x140);
        uint32_t deadline_high = *(volatile uint32_t *)(adv + 0x144);
        if (deadline_high != 0x7fffffffu || deadline_low != 0xffffffffu) {
            uint64_t duration = FUN_010122b4(adv, 0);
            uint64_t current = ((uint64_t)high << 32) | low;
            uint64_t deadline =
                ((uint64_t)deadline_high << 32) | deadline_low;
            uint64_t difference =
                deadline - current - ((uint32_t)duration + 0x152u);
            if ((int32_t)(difference >> 32) < 0) {
                FUN_010128bc(adv, (uint32_t)(duration >> 32),
                              (uint32_t)(difference >> 32),
                              (uint32_t)difference);
                goto finish;
            }
        }
        if (sdc_conn_window_admit(adv[0x100], adv + 0x128) == 0) {
            sdc_assertion_fail(0x30u, 0x737u);
            __builtin_unreachable();
        }
    }

finish:
    *(volatile uint16_t *)(adv + 0x122) = 0;
    controller_radio_event_cleanup();
    FUN_01022a84();
}
