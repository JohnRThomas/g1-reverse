#include "g1_net_symbols.h"
/* net-core FUN_010333b4 @ 0x10333b4 — true extent 556 bytes */
#include <stdint.h>

extern void FUN_01033354(void);
extern uint32_t FUN_0103b62e(uint32_t, uint32_t, uint32_t);
/* This leaf returns status in r0 and deliberately preserves its incoming r1;
 * model that live-through pair as one AAPCS 64-bit result. */
extern uint64_t FUN_01032764(uint32_t, uint32_t);
extern uint32_t *FUN_010327a0(uint32_t);
extern uint32_t FUN_01034fa8(uint32_t, void *, uint32_t);
extern int FUN_01033df0(void);
extern uint8_t FUN_01033de4(void);
extern void FUN_0103a83e(void);
extern void FUN_0102eb8c(uint32_t, uint32_t, uint32_t);
extern void FUN_0103a38a(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t);
extern void FUN_0102eb2c(uint32_t);
extern void FUN_0102e284(uint32_t, uint32_t, void *, uint32_t);

struct timer_init {
    uint32_t period;
    uint32_t flags;
    uint32_t context;
};

int FUN_010333b4(const uint32_t *configuration)
{
    volatile uint8_t *const initialized = (volatile uint8_t *)((unsigned long)&g_esb_enabled_flag) /*=0x21006459*/;
    volatile uint8_t *const active = (volatile uint8_t *)((unsigned long)&g_net_radio_busy_flag) /*=0x21006458*/;
    volatile uint32_t *const saved_word = (volatile uint32_t *)((unsigned long)&g_21004a90) /*=0x21004a90*/;
    volatile uint8_t *const saved = (volatile uint8_t *)((unsigned long)&g_esb_state) /*=0x21004a94*/;
    volatile uint32_t *const control = (volatile uint32_t *)((unsigned long)&g_210049b0) /*=0x210049b0*/;
    volatile uint32_t *callback_slot;
    volatile uint32_t *const radio = (volatile uint32_t *)REG_41008000 /*=0x41008000*/;
    volatile uint8_t *const device_state = (volatile uint8_t *)0x2100065cU;
    volatile uint32_t *table;
    uint32_t value;
    int status;

    if (configuration == 0)
        return -22;
    if (*initialized != 0)
        FUN_01033354();

    *saved_word = configuration[1];
    for (unsigned i = 0; i < 4; ++i) {
        *(volatile uint32_t *)(saved + i * 4U) = configuration[i];
    }
    *(volatile uint32_t *)(saved + 16) = configuration[4];

    *control = 0;
    value = FUN_0103b62e(0x21004b7cU, 0, 0x20);
    *(volatile uint32_t *)((unsigned long)&g_esb_pipe_pid_cnt) /*=0x21006256*/ = 0;
    *(volatile uint32_t *)((unsigned long)&g_2100625a) /*=0x2100625a*/ = 0;
    uint64_t init_result = FUN_01032764(value, ((unsigned long)&g_esb_event_handler_fn) /*=0x2100499c*/);
    callback_slot = (volatile uint32_t *)(uintptr_t)(uint32_t)(init_result >> 32);

    if (saved[0] == 0)
        *callback_slot = ((unsigned long)&rodata_10333a5) /*=0x10333a5*/;
    else if (saved[0] == 1)
        *callback_slot = ADDR_FUN_010333e4_THUMB /*=0x10333e5*/;

    if (saved[9] == 0) {
        radio[0x53c / 4] = 0;
        radio[0x534 / 4] = 0;
        radio[0x538 / 4] = 0;
    } else if (saved[9] == 1) {
        radio[0x53c / 4] = 0xff;
        radio[0x534 / 4] = 1;
        radio[0x538 / 4] = 0x107;
    } else if (saved[9] == 2) {
        radio[0x53c / 4] = 0xffff;
        radio[0x534 / 4] = 2;
        radio[0x538 / 4] = 0x11021;
    }
    ((void (*)(uint32_t))(uintptr_t)*callback_slot)(saved[0x11]);

    radio[0x51c / 4] = 0xe7e7e7e7U;
    radio[0x520 / 4] = 0x43434343U;
    radio[0x524 / 4] = 0x23c343e7U;
    radio[0x528 / 4] = 0x13e363a3U;

    table = FUN_010327a0(0x21004a60U);
    value = 0x21005a56U;
    for (unsigned i = 0; i < 8; ++i, value += 0x100U)
        table[i] = value;

    table = (uint32_t *)((unsigned long)&g_net_queue_stats_block_b) /*=0x21004a34*/;
    value = 0x21005256U;
    for (unsigned i = 0; i < 8; ++i, value += 0x100U)
        *(volatile uint32_t *)&table[i] = value;

    value = 0x21005a56U;
    for (unsigned i = 0; i < 8; ++i, value += 0x100U) {
        volatile uint8_t *entry = (volatile uint8_t *)(((unsigned long)&g_esb_tx_buf_pool) /*=0x210049d4*/ + 12U * i);
        *(volatile uint32_t *)(entry + 0) = value;
        entry[4] = 0;
        *(volatile uint32_t *)(entry + 8) = 0;
    }

    FUN_0103b62e(0x210049b4U, 0, 0x20);
    struct timer_init timer = { 1000000U, 0, 0 };
    status = (int)FUN_01034fa8(((unsigned long)&g_net_log_msg_ctx) /*=0x21000698*/, &timer, ((unsigned long)&rodata_1032fbd) /*=0x1032fbd*/);
    if ((uint32_t)status != 0x0bad0000U) {
        struct { uint32_t count, text, code; } first = {
            3, ((unsigned long)&rodata_103e414) /*=0x103e414*/, (uint32_t)status
        };
        FUN_0102e284(((unsigned long)&rodata_103c05c) /*=0x103c05c*/, 0x1840U, &first, 0);
        struct { uint32_t count, text; } second = { 2, ((unsigned long)&rodata_103e43d) /*=0x103e43d*/ };
        FUN_0102e284(((unsigned long)&rodata_103c05c) /*=0x103c05c*/, 0x1040U, &second, 0);
        return -14;
    }

    status = FUN_01033df0();
    if (status != 0) {
        struct { uint32_t count, text; } message = { 2, ((unsigned long)&rodata_103e463) /*=0x103e463*/ };
        FUN_0102e284(((unsigned long)&rodata_103c05c) /*=0x103c05c*/, 0x1040U, &message, 0);
        return status;
    }

    device_state[4] = FUN_01033de4();
    radio[0x650 / 4] = (radio[0x650 / 4] & 0x300U) | saved[0x13];
    FUN_0103a83e();
    FUN_0102eb8c(8, 1, 0);
    FUN_0102eb8c(0x1d, 2, 0);
    FUN_0102eb8c(0x19, 2, 0);
    FUN_0103a38a(8, 1, ((unsigned long)&rodata_1032fd9) /*=0x1032fd9*/, 0, 0);
    FUN_0103a38a(0x1d, 2, ((unsigned long)&rodata_103309d) /*=0x103309d*/, 0, 0);
    FUN_0103a38a(0x19, 2, 0x0103b03bU, 0, 0);
    FUN_0102eb2c(8);
    FUN_0102eb2c(0x1d);
    FUN_0102eb2c(0x19);
    *active = 0;
    *initialized = 1;
    return 0;
}
