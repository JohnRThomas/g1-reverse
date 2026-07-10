#include "g1_app_symbols.h"
/* named: ancs_discover_start */
/* globals referenced:
//   0x20006abc  g_ancs_discover_params       
*/
/* Reconstructed ancs_discover_start @ 0x182c8  (parity: 300/300 trials, PROVEN) */

extern int gatt_dm_start(unsigned int a, void *b, unsigned int c, unsigned int d, unsigned int e);
extern void DEBUG_PRINT(unsigned int a, int b);

void ancs_discover_start(unsigned int param_1, unsigned short param_2, unsigned int param_3)
{
    int iVar1;
    unsigned short local_c;
    unsigned short local_a;
    unsigned int uStack_8;
    local_c = (unsigned short)(param_2 & ((uintptr_t)&rodata_ff00) /*=0xff00*/);
    local_a = 0x1801;
    uStack_8 = param_3;
    (void)local_a; (void)uStack_8;
    iVar1 = gatt_dm_start(param_1, &local_c, ((uintptr_t)&tbl_889d0) /*=0x88a00*/, ((uintptr_t)&g_ancs_discover_params) /*=0x20006abc*/, param_1);
    if (iVar1 != 0) {
        DEBUG_PRINT("Failed to start discovery for GATT Service (err %d)\n" /*=0x9a401*/, iVar1);
    }
}

