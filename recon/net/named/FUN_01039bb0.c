/* readable reconstruction; identity: FUN_01039bb0 @ 0x01039bb0
 * public-name: FUN_01039bb0
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_01039bb0 @ 0x1039bb0 */
#include <stdint.h>
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"
extern void z_except_reason(unsigned int reason) __attribute__((noreturn));

unsigned int FUN_01039bb0(void)
{
    __set_BASEPRI(0);
    z_except_reason(4);
}
