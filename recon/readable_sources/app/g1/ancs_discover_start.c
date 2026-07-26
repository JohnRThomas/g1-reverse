#include "g1_app_symbols.h"
#include "../../../headers/g1_log.h"
/* readable reconstruction; identity: FUN_000182c8 @ 0x000182c8
 * public-name: ancs_discover_start
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ancs_discover_start                      <= FUN_000182c8 @ 0x000182c8
 *   gatt_dm_start                            <= FUN_0004ed8c @ 0x0004ed8c
 * address symbols (name @ address):
 *   rodata_88a00                             @ 0x00088a00
 *   rodata_9a401                             @ 0x0009a401   [INLINED -- G6 literal batch]
 *   g_ancs_discover_params                   @ 0x20006abc
 */
/* Reconstructed FUN_000182c8 @ 0x182c8  (parity: 300/300 trials, PROVEN) */

extern int gatt_dm_start(unsigned int a, void *b, unsigned int c, unsigned int d, unsigned int e);

void ancs_discover_start(unsigned int param_1, unsigned short param_2, unsigned int param_3)
{
    int iVar1;
    unsigned int request;
    (void)param_3;
    request = 0x18010000U | (param_2 & 0xff00U);
    iVar1 = gatt_dm_start(param_1, &request, ((unsigned long)&rodata_88a00) /*=0x88a00*/, ((unsigned long)&g_ancs_discover_params) /*=0x20006abc*/, param_1);
    if (iVar1 != 0) {
        log_message(((unsigned long)"Failed to start discovery for GATT Service (err %d)\n") /*=0x9a401*/, iVar1);
    }
}
