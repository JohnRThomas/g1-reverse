#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00086634 @ 0x00086634
 * public-name: z_reschedule_irqlock
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   arch_swap                                <= FUN_000501d4 @ 0x000501d4
 *   z_reschedule_irqlock                     <= FUN_00086634 @ 0x00086634
 */
/* Reconstructed FUN_00086634 @ 0x86634  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include <cmsis_gcc.h>

extern void arch_swap(void);
void z_reschedule_irqlock(int param_1) {
    if (param_1 == 0) {
        unsigned int ipsr = __get_IPSR();
        if (ipsr == 0) {
            arch_swap();
            return;
        }
    }
    __set_BASEPRI((unsigned int)param_1);
    __ISB();
}
