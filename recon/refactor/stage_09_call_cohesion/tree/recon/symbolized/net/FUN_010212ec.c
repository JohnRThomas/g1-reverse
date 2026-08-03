#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_010212ec @ 0x010212ec
 * public-name: FUN_010212ec
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 *   sdc_llcp_note_unsupported_pdu            <= FUN_01020500 @ 0x01020500
 * address symbols (name @ address):
 *   rodata_103c4d0                           @ 0x0103c4d0
 *   rodata_103c578                           @ 0x0103c578
 *   rodata_103c5b0                           @ 0x0103c5b0
 *   REG_41008000                             @ 0x41008000
 */
/* net-core FUN_010212ec @ 0x10212ec */
#include <stdint.h>

extern void sdc_assertion_fail(uint32_t reason, uint32_t line);
extern void FUN_01020108(void);
extern void FUN_01020168(uint32_t channel);
extern void sdc_llcp_note_unsupported_pdu(void);
extern void FUN_01020a00(uint32_t channel);
extern void FUN_010215a8(int32_t request);
extern void FUN_010216d4(uint32_t, uint32_t, int32_t, void *);
extern int32_t FUN_010218c0(void *, const void *);
extern int32_t FUN_010218cc(void *, const void *);
extern int32_t FUN_010218fc(void *);
extern int32_t FUN_01023ac4(void);
extern uint32_t FUN_01023e88(void);
extern int32_t FUN_01025bb0(void *);
extern int32_t FUN_01025bc8(void *);
extern void FUN_01025c9c(void *, ...);
extern uint64_t thunk_FUN_010251e8(void);

#define STATE       ((volatile uint8_t *)G1N_210015f0)
#define LOOKUP8     ((volatile uint8_t *)UINT32_C(0x0103c4d0))
#define LOOKUP16    ((volatile uint16_t *)UINT32_C(0x0103c5b0))
#define RADIO       ((volatile uint32_t *)UINT32_C(0x41008000))
#define TIMER       ((volatile uint32_t *)UINT32_C(0x4100c000))
#define WORK        ((volatile uint32_t *)G1N_21000028)

static uint32_t scaled_delay(uint32_t channel, uint32_t bias)
{
    uint64_t product = UINT64_C(0x10624dd3) *
                       (uint32_t)(LOOKUP16[channel] + bias);
    return (uint32_t)(product >> 38);
}

uint32_t FUN_010212ec(uint32_t mode, uint32_t channel, uint32_t request)
{
    uint8_t command[3];
    uint8_t observed;
    uint32_t result = 0;
    uint32_t operation;
    uint64_t timer_index;
    struct {
        volatile uint32_t *base;
        uint32_t index;
        uint32_t compare;
        uint32_t delay;
    } timer_request;

    STATE[0x35] |= 2;
    command[2] = 0;
    command[0] = mode == 0 ? 4 : 2;
    command[1] = FUN_01023e88() > 1 ? 0 : UINT8_C(0xff);
    if (FUN_01025bb0(command) != 0)
        goto panic_a69;

    STATE[0x45] = 1;
    if (mode == 0) {
        FUN_01020a00(channel);
        {
            uint32_t selector = STATE[0x1a];
            RADIO[0x508 / 4] = LOOKUP8[selector];
            RADIO[0x554 / 4] = selector & 0x7f;
            FUN_010216d4(channel, selector, (int8_t)STATE[0x19], command);
        }
        FUN_010215a8((int8_t)command[0]);
        if (FUN_010218fc(&command[1]) != 0)
            goto panic_57e;
        STATE[9] = 1;
        if (STATE[7] == 1)
            RADIO[0x200 / 4] |= 8;
        result = scaled_delay(channel, 500);
        RADIO[0x80 / 4] = UINT32_C(0x8000000a);
        request = UINT32_C(0x8000000a);
    } else if (mode == 1) {
        FUN_01020168(channel);
        STATE[9] = 2;
        if (STATE[7] == 1)
            RADIO[0x200 / 4] |= 4;
        result = 0x29;
        RADIO[0x84 / 4] = UINT32_C(0x8000000a);
        request = UINT32_C(0x8000000a);
    }

    if (STATE[7] == 0) {
        STATE[0x35] |= 2;
    } else if (STATE[7] == 1) {
        STATE[0x35] |= 4;
    }
    FUN_01020108();
    if (FUN_01023ac4() != 0) {
        sdc_llcp_note_unsupported_pdu();
        return 0;
    }

    timer_index = thunk_FUN_010251e8();
    operation = mode == 0 ? 1 : 0;
    command[0] = 0;
    command[1] = (uint8_t)operation;
    timer_request.base = TIMER;
    timer_request.index = (uint32_t)timer_index;
    timer_request.compare = TIMER[(uint32_t)timer_index + 0x150];

    if (mode == 0) {
        timer_request.delay = scaled_delay(channel, 600);
        FUN_01025c9c(command, (uint32_t)(timer_index >> 32),
                     (uint32_t)(UINT64_C(0x10624dd3) *
                                (uint32_t)(LOOKUP16[channel] + 600)));
        if (*(volatile uint16_t *)(STATE + 0x1c) > 0x95) {
            WORK[2] = 0;
            WORK[3] = 0x28;
            if ((uint32_t)(FUN_010218c0((void *)WORK, (const void *)(LOOKUP8 + 0xa8)) + 1) > 1)
                sdc_assertion_fail(0x3e, 0x6e9);
        }
    } else {
        timer_request.delay = 0x28;
        FUN_01025c9c(command);
        if (*(volatile uint16_t *)(STATE + 0x1c) > 0x95) {
            if (mode != 1)
                sdc_assertion_fail(0x3e, 0x6fa);
            WORK[2] = 0;
            WORK[3] = 0x29;
            if ((uint32_t)(FUN_010218cc((void *)WORK, (const void *)UINT32_C(0x0103c578)) + 1) > 1)
                sdc_assertion_fail(0x3e, 0x6f6);
        }
    }

    if (FUN_01025bc8(&observed) != 0)
        sdc_assertion_fail(0x3e, 0xa8b);

    if (STATE[9] == 1)
        STATE[0x46] = (uint8_t)(((observed ^ 4u) >> 2) & 1u);
    else if (STATE[9] == 2)
        STATE[0x46] = (uint8_t)(((observed ^ 2u) >> 1) & 1u);
    else {
        STATE[0x46] = 0;
        return result;
    }

    if (STATE[0x46] != 0) {
        RADIO[0x80 / 4] = 0;
        RADIO[0x84 / 4] = 0;
        RADIO[0x10 / 4] = 1;
    }
    return result;

panic_a69:
    sdc_assertion_fail(0x3e, 0xa69);
    /* The diagnostic is noreturn in production.  Preserve the firmware's
       literal fall-through as well, since the parity oracle returns. */
    WORK[2] = mode;
    WORK[3] = 0x28;
    if ((uint32_t)(FUN_010218c0((void *)WORK,
                                (const void *)(LOOKUP8 + 0xa8)) + 1) > 1)
        sdc_assertion_fail(0x3e, 0x6e9);
    FUN_01020168(channel);
    /* r8 is still zero on the mode-zero early-failure path and was loaded
       with two on the nonzero-mode path. */
    STATE[9] = mode == 0 ? 0 : 2;
    if (STATE[7] == 1)
        RADIO[0x200 / 4] |= 4;
    RADIO[0x84 / 4] = UINT32_C(0x8000000a);
    if (STATE[7] == 0)
        STATE[0x35] |= 2;
    else if (STATE[7] == 1)
        STATE[0x35] |= 4;
    FUN_01020108();
    if (FUN_01023ac4() != 0)
        sdc_llcp_note_unsupported_pdu();
    return 0;
panic_57e:
    sdc_assertion_fail(0x3e, 0x57e);
    return 0;
}
