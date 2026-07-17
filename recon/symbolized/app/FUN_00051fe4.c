#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00051fe4 @ 0x00051fe4
 * public-name: FUN_00051fe4
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   img_mgmt_state                           @ 0x2000ab80
 */
/* Reconstructed FUN_00051fe4 @ 0x51fe4  (parity: 300/300 trials, PROVEN) */

extern unsigned int memset_bytes(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);

void FUN_00051fe4(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3)
{
    unsigned int iVar1 = memset_bytes(((unsigned long)img_mgmt_state) /*=0x2000ab80*/, 0, 0x2c, ((unsigned long)img_mgmt_state) /*=0x2000ab80*/, p3);
    *(volatile unsigned int*)(iVar1 - 4) = 0xffffffffUL;
}
