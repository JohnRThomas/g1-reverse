/* readable reconstruction; identity: FUN_00058568 @ 0x00058568
 * public-name: send_err_rsp_alloc_failure_log
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   send_err_rsp_alloc_failure_log           <= FUN_00058568 @ 0x00058568
 * address symbols (name @ address):
 *   rodata_88100                             @ 0x00088100
 *   rodata_f4408                             @ 0x000f4408
 */
/* Reconstructed FUN_00058568 @ 0x00058568 (send_err_rsp log helper).
 * Raw/address backmap: FUN_00058568 @ 0x00058568, extent 0x0000001c.
 */
#include <stdint.h>
extern void FUN_00081ddc(uint32_t, uint32_t, const void *);
void send_err_rsp_alloc_failure_log(void)
{
    const uint32_t package[2] = { 2U, 0x000f4408U };
    FUN_00081ddc(0x00088100U, 0x1040U, package);
}
