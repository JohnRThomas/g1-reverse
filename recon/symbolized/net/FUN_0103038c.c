#include "g1_net_symbols.h"
/* net-core FUN_0103038c @ 0x103038c; exact executable extent 268 bytes. */
#include <stdint.h>
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"

extern int32_t FUN_0102ca80(uint32_t object, uint32_t state);
extern void FUN_01039bbe(uint32_t source, uint32_t message, uint32_t line);
extern void FUN_01039bb0(uint32_t message, uint32_t line)
    __attribute__((noreturn));
extern uint32_t FUN_0103b14a(void);
extern void FUN_0102ea00(uint32_t saved_basepri);
extern void FUN_01037c64(uint32_t irq, uint32_t unused);

#define CLOCK ((volatile uint32_t *)REG_41005000 /*=0x41005000*/)

uint32_t FUN_0103038c(uint32_t mode)
{
    volatile uint32_t *const initialized = (volatile uint32_t *)0x21004810u;
    uint32_t old_initialized;

    /* Atomic acquire/release exchange used by the one-time initializer. */
    do {
        old_initialized = __LDAEX(initialized);
    } while (__STLEX(1u, initialized) != 0u);

    if (old_initialized == 0u) {
        volatile uint32_t *const state = (volatile uint32_t *)0x21004800u;

        state[1] = 0u;
        state[3] = 0u;
        state[2] = 1u;
        if (FUN_0102ca80(0x21004834u, 0x21004800u) < 0) {
            FUN_01039bbe(((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, 0x0103dea5u, 0x230u);
            FUN_01039bb0(0x0103dea5u, 0x230u);
        }
    }

    if (mode == 0u)
        return 0u;
    if (mode > 2u) {
        FUN_01039bbe(((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, 0x0103dea5u, 0x242u);
        FUN_01039bb0(0x0103dea5u, 0x242u);
    }

    if (mode == 1u && (CLOCK[0x41c / 4] & 3u) == 2u)
        return 0u;

    /* A zero helper result requires this routine to establish the BASEPRI
     * context itself.  Thereafter both paths have an active context. */
    uint32_t context_result = FUN_0103b14a();
    uint32_t has_context = context_result;
    uint32_t saved_basepri = 0u;
    if (has_context == 0u) {
        if (*(volatile uint8_t *)0x21006461u != 0u)
            CLOCK[0x308 / 4] = 2u;
        saved_basepri = __get_BASEPRI();
        __set_BASEPRI_MAX(0x40u);
        __ISB();
        has_context = 1u;
    }

    for (;;) {
        uint32_t status = CLOCK[0x418 / 4];
        uint32_t source = CLOCK[0x418 / 4] & 3u;

        if ((status & 0x00010000u) != 0u &&
            (source == 2u || mode == 1u)) {
            if (has_context != 0u) {
                __set_BASEPRI(saved_basepri);
                __ISB();
            } else
                CLOCK[0x304 / 4] = 2u;
            return context_result;
        }

        if (has_context != 0u)
            FUN_0102ea00(saved_basepri);
        else
            FUN_01037c64(0x21u, 0u);

        while ((uint8_t)CLOCK[0x518 / 4] == 1u &&
               CLOCK[0x104 / 4] != 0u) {
            CLOCK[0x104 / 4] = 0u;
            (void)CLOCK[0x104 / 4];
            CLOCK[0x518 / 4] = 2u;
            *(volatile uint32_t *)0xe000e280u = 0x20u;
            CLOCK[2] = 1u;
        }
    }
}
