/* readable reconstruction; identity: FUN_0101233c @ 0x0101233c
 * public-name: FUN_0101233c
 * durable-map: recon/catalogs/function_names_net.json
 */
/* CPUNET private timing/state setup @ 0x0101233c.
 * Raw back-map: FUN_0101233c@0x0101233c; extent 0xe6. */
#include <stdint.h>

extern unsigned FUN_0100aa04(unsigned kind, void *destination);
extern unsigned controller_indexed_state_byte_get(void); /* FUN_0100bc04@0x0100bc04 */
extern uint32_t FUN_0100c738(void);
extern unsigned FUN_0100c744(uint8_t selector, void *state);
extern void FUN_0101124c(void *context, unsigned reserved);
extern uint64_t controller_time_now(void); /* thunk_FUN_01025034 -> FUN_01022f08 */

unsigned FUN_0101233c(volatile uint8_t *context)
{
    uint8_t kind = context[0x12];
    uint8_t state_code;
    unsigned kind_is_2_or_3 = (uint8_t)(kind - 2u) < 2u;
    unsigned kind_is_other = (kind & 0xfdu) != 0u;

    if (kind_is_2_or_3) {
        state_code = (uint8_t)FUN_0100c744(context[0x67],
                                          (void *)(context + 0x68));
        if ((*(volatile uint16_t *)(context + 2) & 0x20u) != 0u)
            goto configure;
        if (state_code == 8u)
            goto continue_checks;
        if (controller_indexed_state_byte_get() == 0u)
            goto configure;
    } else {
        state_code = 8u;
        if ((*(volatile uint16_t *)(context + 2) & 0x20u) != 0u)
            goto configure;
    }

continue_checks:
    if (!kind_is_other) {
        if (FUN_0100aa04(0, (void *)(context + 0x61)) != 0u)
            goto configure;
    } else {
        if (context[0x19] == 0u)
            return 0;
        *(volatile uint32_t *)(context + 0x61) =
            *(volatile uint32_t *)(context + 0x13);
        *(volatile uint16_t *)(context + 0x65) =
            *(volatile uint16_t *)(context + 0x17);
    }

configure:
    context[0x1b] = state_code;
    context[0x1a] = (uint8_t)kind_is_2_or_3;
    context[0x60] = (uint8_t)kind_is_other;
    {
        uint32_t ticks = FUN_0100c738();
        uint64_t deadline =
            controller_time_now() + (uint64_t)ticks * UINT64_C(1000000);
        context[0x6e] = 0;
        *(volatile uint64_t *)(context + 0x58) = deadline;
    }
    FUN_0101124c((void *)context, 0);
    return 1;
}
