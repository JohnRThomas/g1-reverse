/* readable reconstruction; identity: FUN_00050170 @ 0x00050170
 * public-name: wfi_idle_loop
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   wfi_idle_loop                            <= FUN_00050170 @ 0x00050170
 */
/* Reconstructed FUN_00050170 @ 0x50170, exact extent 6 bytes.
 * CFG_VERIFY_PREFIX_FIRST: intentional WFI idle loop. */
#include <stdint.h>
#include <cmsis_gcc.h>

void wfi_idle_loop(void)
{
    for (;;)
        __WFI();
}
