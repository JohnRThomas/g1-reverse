#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00086634 @ 0x00086634
 * public-name: z_reschedule_irqlock
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_reschedule_irqlock                     <= FUN_00086634 @ 0x00086634
 */
/* Reconstructed FUN_00086634 @ 0x86634  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"

extern void FUN_000501d4(void);
void z_reschedule_irqlock(int param_1) {
    if (param_1 == 0) {
        unsigned int ipsr = __get_IPSR();
        if (ipsr == 0) {
            FUN_000501d4();
            return;
        }
    }
    __set_BASEPRI((unsigned int)param_1);
    __ISB();
}
