#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01020a6c @ 0x01020a6c
 * public-name: controller_radio_transition_schedule
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 *   sdc_llcp_note_unsupported_pdu            <= FUN_01020500 @ 0x01020500
 *   controller_radio_transition_schedule     <= FUN_01020a6c @ 0x01020a6c
 * address symbols (name @ address):
 *   rodata_103c4d0                           @ 0x0103c4d0
 *   rodata_103c578                           @ 0x0103c578
 *   REG_41008000                             @ 0x41008000
 *   REG_41008304                             @ 0x41008304
 */
/* net-core FUN_01020a6c @ 0x01020a6c */
#include <stdint.h>

extern void sdc_assertion_fail(uint32_t, uint32_t);
extern uint32_t FUN_01023e88(void);
extern int FUN_01025bb0(void *);
extern void FUN_01020a00(int);
extern void FUN_010216d4(int, uint32_t, int, void *);
extern void FUN_010215a8(int);
extern uint64_t FUN_010218fc(void *);
extern void FUN_01020108(uint32_t, uint32_t);
extern void sdc_llcp_note_unsupported_pdu(void);
extern uint64_t FUN_01020168(int);
extern void FUN_01025c9c(void *);
extern int FUN_010218cc(void *, const void *);
extern int FUN_010218c0(void *, uint32_t);
extern int FUN_01025bc8(void *);

#define STATE ((volatile uint8_t *)G1N_210015f0)
#define TABLE ((volatile uint8_t *)((unsigned long)&rodata_103c4d0) /*=0x103c4d0*/)
#define RADIO ((volatile uint32_t *)REG_41008000 /*=0x41008000*/)
#define TIMER ((volatile uint32_t *)0x4100c000u)
#define REQUEST ((volatile uint32_t *)G1N_21000028)
#define REQUEST_DESCRIPTOR ((const void *)((unsigned long)&rodata_103c578) /*=0x103c578*/)
#define SCALE 0x10624dd3u
#define TASK 0x80000008u

int controller_radio_transition_schedule(int kind, uint32_t deadline, int channel)
{
    uint8_t result = 0;
    int8_t command;
    uint8_t available;
    uint8_t unused = 0;
    uint32_t timer_base;
    uint32_t reserved = 0;
    uint32_t adjusted_deadline;
    uint32_t duration;
    uint64_t start = 0;
    uint32_t mode;
    int rc;

    if (kind == 0) {
        command = 4;
        available = FUN_01023e88() <= 1 ? 0xff : 0;
        if (FUN_01025bb0(&command) != 0)
            goto fatal_a69;

        STATE[0x45] = 1;
        FUN_01020a00(channel);
        mode = STATE[0x1a];
        RADIO[0x508 / 4] = TABLE[mode];
        RADIO[0x554 / 4] = mode & 0x7f;
        FUN_010216d4(channel, mode, (int8_t)STATE[0x19], &command);
        FUN_010215a8(command);
        start = FUN_010218fc(&available);
        if ((uint32_t)start != 0)
            goto fatal_57e;
        STATE[9] = 1;
        mode = STATE[7];
        if (mode != 1) {
            uint64_t product = (uint64_t)SCALE *
                ((volatile uint16_t *)TABLE)[channel + 0x70] +
                (uint64_t)SCALE * 500u;
            deadline -= (uint32_t)(product >> 38);
            start = product << 32;
            if (mode == 0)
                RADIO[0x80 / 4] = TASK;
        }
    } else {
        command = 2;
        available = FUN_01023e88() <= 1 ? 0xff : 0;
        if (FUN_01025bb0(&command) != 0)
            goto fatal_a69;
        STATE[0x45] = 1;
        if (kind != 1)
            goto fatal_7c3;
        start = FUN_01020168(channel);
        STATE[9] = 2;
        mode = STATE[7];
        if (mode != 1) {
            deadline -= 0x29;
            if (mode == 0)
                RADIO[0x84 / 4] = TASK;
        }
    }

    TIMER[0x540 / 4] = deadline;
    TIMER[0x1c0 / 4] = TASK;
    *(volatile uint32_t *)REG_41008304 /*=0x41008304*/ = 0x10;
    if (STATE[7] == 0)
        STATE[0x35] |= 2;
    else if (STATE[7] == 1)
        STATE[0x35] |= 4;

    FUN_01020108((uint32_t)start, (uint32_t)(start >> 32));
    timer_base = 0x4100c000u;
    TIMER[0x4c / 4] = 1;
    if (deadline <= TIMER[0x54c / 4]) {
        TIMER[0x540 / 4] = 0;
        TIMER[0x1c0 / 4] = 0;
        sdc_llcp_note_unsupported_pdu();
        return 0;
    }

    command = 0;
    reserved = 0;
    available = kind == 0;
    adjusted_deadline = deadline;
    if (kind != 0) {
        duration = 0x28;
        FUN_01025c9c(&command);
        if (*(volatile uint16_t *)(STATE + 0x1c) > 0x95) {
            if (kind != 1)
                goto fatal_6fa;
            REQUEST[2] = deadline;
            REQUEST[3] = deadline + 0x29;
            rc = FUN_010218cc((void *)REQUEST, REQUEST_DESCRIPTOR);
            if ((uint32_t)(rc + 1) > 1) {
                sdc_assertion_fail(0x3e, 0x6f6);
                result = (uint8_t)((((deadline + 0x29) ^ 2u) >> 1) & 1u);
                goto store_result;
            }
        }
    } else {
        uint64_t product = (uint64_t)SCALE *
            ((volatile uint16_t *)TABLE)[channel + 0x70] +
            (uint64_t)SCALE * 600u;
        duration = (uint32_t)(product >> 38);
        FUN_01025c9c(&command);
        if (*(volatile uint16_t *)(STATE + 0x1c) > 0x95) {
            REQUEST[2] = deadline;
            REQUEST[3] = deadline + 0x28;
            rc = FUN_010218c0((void *)REQUEST, (uint32_t)kind + 0xa8);
            if ((uint32_t)(rc + 1) > 1)
                goto fatal_6e9;
        }
    }

after_request:
    rc = FUN_01025bc8(&result);
    if (rc != 0)
        goto fatal_a8b;
    if (STATE[9] == 1)
        result = (uint8_t)(((result ^ 4u) >> 2) & 1u);
    else if (STATE[9] == 2)
        result = (uint8_t)(((result ^ 2u) >> 1) & 1u);
    else
        result = 0;

store_result:
    STATE[0x46] = result;
    if (result != 0) {
        RADIO[0x80 / 4] = 0;
        RADIO[0x84 / 4] = 0;
        RADIO[0x10 / 4] = 1;
    }
    (void)unused;
    (void)timer_base;
    (void)reserved;
    (void)adjusted_deadline;
    (void)duration;
    return 1;

fatal_a69: sdc_assertion_fail(0x3e, 0xa69);
    REQUEST[2] = deadline;
    REQUEST[3] = deadline + 0x28;
    rc = FUN_010218c0((void *)REQUEST, (uint32_t)kind + 0xa8);
    if ((uint32_t)(rc + 1) <= 1) goto after_request;
fatal_6e9: sdc_assertion_fail(0x3e, 0x6e9);
fatal_a8b: sdc_assertion_fail(0x3e, 0xa8b);
fatal_7c3: sdc_assertion_fail(0x3e, 0x7c3);
fatal_57e: sdc_assertion_fail(0x3e, 0x57e);
fatal_6fa: sdc_assertion_fail(0x3e, 0x6fa);
    for (;;) sdc_assertion_fail(0, 0);
}
