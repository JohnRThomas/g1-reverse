/* readable reconstruction; identity: FUN_000604e4 @ 0x000604e4
 * public-name: clock_control_nrf_on
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   clock_control_nrf_on                     <= FUN_000604e4 @ 0x000604e4
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f5ad9                             @ 0x000f5ad9
 *   rodata_f5b16                             @ 0x000f5b16
 */
/* Full reconstruction FUN_000604e4 @ 0x000604e4 (114-byte exact extent). */
#include <stdint.h>
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"

extern void printk(uintptr_t, uintptr_t, uintptr_t, uint32_t);
extern void assert_post_action(uintptr_t, uint32_t) __attribute__((noreturn));

int clock_control_nrf_on(uint8_t *device, uint8_t type, uint32_t owner)
{
    uint8_t *state = *(uint8_t **)(device + 0x10);
    if (type >= 4) {
        printk(0x00099cbdu, 0x000f5b16u, 0x000f5ad9u, 0x15du);
        assert_post_action(0x000f5ad9u, 0x15du);
    }

    uint32_t saved = __get_BASEPRI();
    __set_BASEPRI_MAX(0x20u);
    __ISB();
    uint32_t offset = 12u * type;
    uint32_t current = *(volatile uint32_t *)(state + offset + 0x88) & 0xc0u;
    if (current != 0 && current != owner) {
        __set_BASEPRI(saved);
        __ISB();
        return -1;
    }

    *(volatile uint32_t *)(state + offset + 0x88) = 1;
    __set_BASEPRI(saved);
    __ISB();
    void (*callback)(void) = *(void (**)(void))(*(uint8_t **)(device + 4) + offset + 4);
    callback();
    return 0;
}
