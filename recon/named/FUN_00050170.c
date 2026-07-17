/* readable reconstruction; identity: FUN_00050170 @ 0x00050170
 * public-name: FUN_00050170
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Reconstructed FUN_00050170 @ 0x50170, exact extent 6 bytes.
 * CFG_VERIFY_PREFIX_FIRST: intentional WFI idle loop. */
#include <stdint.h>
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"

void FUN_00050170(void)
{
    for (;;)
        __WFI();
}
