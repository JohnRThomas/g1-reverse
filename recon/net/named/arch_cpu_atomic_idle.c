/* readable reconstruction; identity: FUN_0102ea00 @ 0x0102ea00
 * public-name: arch_cpu_atomic_idle
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   arch_cpu_atomic_idle                     <= FUN_0102ea00 @ 0x0102ea00
 */
/* Reconstructed arch_cpu_atomic_idle @ 0x0102ea00.
 * Raw/address back-map: FUN_0102ea00 / 0x0102ea00.
 */
#include <stdint.h>
#include <cmsis_gcc.h>

extern void FUN_0102d0c4(void); /* enter-idle tracing/prepare hook */
extern uint32_t FUN_0102d1c0(void); /* sleep-policy predicate */

void arch_cpu_atomic_idle(uint32_t key)
{
    FUN_0102d0c4();
    __disable_irq();
    __set_BASEPRI(0u);
    if (FUN_0102d1c0() != 0u) {
        __DSB();
        __WFE();
    }
    __set_BASEPRI(key);
    __enable_irq();
}
