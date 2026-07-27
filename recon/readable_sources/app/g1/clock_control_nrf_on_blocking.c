#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00060788 @ 0x00060788
 * public-name: clock_control_nrf_on_blocking
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   onoff_request_enqueue                    <= FUN_0004b908 @ 0x0004b908
 *   arch_cpu_atomic_idle                     <= FUN_0004ff38 @ 0x0004ff38
 *   clock_control_nrf_on_blocking            <= FUN_00060788 @ 0x00060788
 *   k_sleep                                  <= FUN_00074844 @ 0x00074844
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   k_is_in_isr                              <= FUN_00086406 @ 0x00086406
 * address symbols (name @ address):
 *   rodata_10000                             @ 0x00010000
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f0f1b                             @ 0x000f0f1b   [INLINED -- G6 literal batch]
 *   rodata_f5ad9                             @ 0x000f5ad9   [INLINED -- G6 literal batch]
 *   rodata_f7a30                             @ 0x000f7a30
 *   g_2000b084                               @ 0x2000b084
 *   g_2000b094                               @ 0x2000b094
 *   g_2000b0b8                               @ 0x2000b0b8
 *   g_tx_yield_allowed_flag                  @ 0x2001d564
 */
/* Full reconstruction FUN_00060788 @ 0x60788, exact 280-byte extent. */
#include <stdint.h>
#include <cmsis_gcc.h>
#include "../../../headers/g1_log.h"

extern int onoff_request_enqueue(uintptr_t);
extern void assert_post_action(uintptr_t, uint32_t) __attribute__((noreturn));
extern int k_is_in_isr(void);
extern void arch_cpu_atomic_idle(uint32_t);
extern int32_t k_sleep(k_timeout_t);

void clock_control_nrf_on_blocking(uint32_t mode)
{
    volatile uint32_t *once = (volatile uint32_t *)((unsigned long)&g_2000b094) /*=0x2000b094*/;
    uint32_t old = __atomic_exchange_n(once, 1u, __ATOMIC_ACQ_REL);

    if (old == 0) {
        volatile uint32_t *state = (volatile uint32_t *)((unsigned long)&g_2000b084) /*=0x2000b084*/;
        state[1] = 0;
        state[3] = 0;
        state[2] = 1;
        if (onoff_request_enqueue(((unsigned long)&g_2000b0b8) /*=0x2000b0b8*/) < 0) {
            printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)"err >= 0") /*=0xf0f1b*/, ((unsigned long)"WEST_TOPDIR/zephyr/drivers/clock_control/clock_control_nrf.c") /*=0xf5ad9*/, 0x230u);
            assert_post_action(((unsigned long)"WEST_TOPDIR/zephyr/drivers/clock_control/clock_control_nrf.c") /*=0xf5ad9*/, 0x230u);
        }
    }

    if (mode == 0)
        return;
    if (mode > 2) {
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)&rodata_f7a30) /*=0xf7a30*/, ((unsigned long)"WEST_TOPDIR/zephyr/drivers/clock_control/clock_control_nrf.c") /*=0xf5ad9*/, 0x242u);
        assert_post_action(((unsigned long)"WEST_TOPDIR/zephyr/drivers/clock_control/clock_control_nrf.c") /*=0xf5ad9*/, 0x242u);
    }

    volatile uint32_t *hw = (volatile uint32_t *)0x50005000u;
    if (mode == 1 && (hw[0x41c / 4] & 3u) == 2u)
        return;

    int privileged = k_is_in_isr();
    uint32_t saved = 0;
    if (privileged == 0 && *(volatile uint8_t *)((unsigned long)&g_tx_yield_allowed_flag) /*=0x2001d564*/ != 0) {
        hw[0x308 / 4] = 2;
    } else {
        saved = __get_BASEPRI();
        __set_BASEPRI_MAX(0x20u);
        __ISB();
        privileged = 1;
    }

    while ((hw[0x418 / 4] & ((unsigned long)&rodata_10000) /*=0x10000*/) == 0 ||
           ((hw[0x418 / 4] & 3u) != 2u && mode != 1)) {
        if (privileged)
            arch_cpu_atomic_idle(saved);
        else
            k_sleep(0x21u, 0);

        if ((uint8_t)hw[0x518 / 4] == 1u && hw[0x104 / 4] != 0) {
            hw[0x104 / 4] = 0;
            (void)hw[0x104 / 4];
            hw[0x518 / 4] = 2;
            *(volatile uint32_t *)0xe000e280u = 0x20u;
            hw[8 / 4] = 1;
        }
    }

    if (privileged) {
        __set_BASEPRI(saved);
        __ISB();
    } else {
        hw[0x304 / 4] = 2;
    }
}
