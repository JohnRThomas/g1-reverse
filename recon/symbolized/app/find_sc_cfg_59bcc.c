#include "g1_app_symbols.h"
/* named: find_sc_cfg_59bcc */
/* globals referenced:
//   0x2000ff18  sc_cfg                       
*/
/* Reconstructed find_sc_cfg_59bcc @ 0x59bcc  (parity: 300/300 trials, PROVEN) */

extern int bt_addr_le_eq_0(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);

int find_sc_cfg_59bcc(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    int iVar2 = 0;
    unsigned int iVar3 = ((uintptr_t)&g_bt_gatt_sc_cfg_addr_ff19) /*=0x2000ff19*/;
    while ((*(volatile unsigned char*)(iVar3 - 1) != param_1) ||
           (bt_addr_le_eq_0(iVar3, param_2, param_3, (unsigned int)*(volatile unsigned char*)(iVar3 - 1), param_4) == 0))
    {
        iVar2 = iVar2 + 0xc;
        iVar3 = iVar3 + 0xc;
        if (iVar2 == 0x24) {
            return 0;
        }
    }
    return ((uintptr_t)&sc_cfg) /*=0x2000ff18*/ + iVar2;
}

