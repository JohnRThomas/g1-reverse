#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00052000 @ 0x00052000
 * public-name: FUN_00052000
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   cbor_encode_bstr                         <= FUN_0008633e @ 0x0008633e
 * address symbols (name @ address):
 *   rodata_a24e0                             @ 0x000a24e0
 *   g_img_mgmt_active_slot                   @ 0x2000ab7c
 */
/* Reconstructed FUN_00052000 @ 0x52000  (parity: 300/300 trials, PROVEN) */

extern int cbor_encode_bstr(int, void*);
extern int thunk_FUN_00086320(int, unsigned int);

unsigned int FUN_00052000(int param_1)
{
    int iVar1;
    unsigned int uVar2;
    unsigned int local_10;
    unsigned int local_c;
    local_10 = ((unsigned long)&rodata_a24e0) /*=0xa24e0*/;
    local_c = 3;
    iVar1 = cbor_encode_bstr(param_1 + 4, &local_10);
    if (iVar1 == 0 ||
        (iVar1 = thunk_FUN_00086320(param_1 + 4, *(volatile unsigned int*)(((unsigned long)&g_img_mgmt_active_slot) /*=0x2000ab7c*/ + 4)), iVar1 == 0)) {
        uVar2 = 7;
    } else {
        uVar2 = 0;
    }
    return uVar2;
}
