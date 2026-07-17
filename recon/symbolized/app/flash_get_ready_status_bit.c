#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000304f0 @ 0x000304f0
 * public-name: flash_get_ready_status_bit
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   attr_store_get                           <= FUN_000302f8 @ 0x000302f8
 *   flash_get_ready_status_bit               <= FUN_000304f0 @ 0x000304f0
 */
/* Reconstructed FUN_000304f0 @ 0x304f0  (parity: 300/300 trials, PROVEN) */

extern int attr_store_get(unsigned int, int*, unsigned int, int, unsigned int);

int flash_get_ready_status_bit(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
    int local_c = 0;
    int iVar1 = attr_store_get(0xff00, &local_c, param_3, 0, param_1);
    if (iVar1 < 0 || (unsigned int)(0xdfddcdfdU + local_c) > 4) {
        return -1;
    } else {
        return (int)((0x15U >> ((0xdfddcdfdU + local_c) & 0xffU)) & 1) - 1;
    }
}
