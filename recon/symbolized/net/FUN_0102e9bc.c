#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0102e9bc @ 0x0102e9bc
 * public-name: FUN_0102e9bc
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0102e9bc @ 0x102e9bc
 *
 * Exact stock owner: Zephyr 3.4.99-ncs1-1
 *   arch/arm/core/aarch32/cpu_idle.S:arch_cpu_idle
 * Raw address back-map remains FUN_0102e9bc / 0x0102e9bc.
 */
#include <stdint.h>
#include <cmsis_gcc.h>

#define arch_cpu_idle FUN_0102e9bc
#define z_arm_on_enter_cpu_idle_prepare FUN_0102d0c4
#define z_arm_on_enter_cpu_idle FUN_0102d1c0

extern void z_arm_on_enter_cpu_idle_prepare(void);
extern uint32_t z_arm_on_enter_cpu_idle(void);

void arch_cpu_idle(void)
{
    z_arm_on_enter_cpu_idle_prepare();

    __disable_irq();
    __set_BASEPRI(0u);
    __ISB();

    if (z_arm_on_enter_cpu_idle() != 0u) {
        __DSB();
        __WFI();
    }

    __enable_irq();
    __ISB();
}
