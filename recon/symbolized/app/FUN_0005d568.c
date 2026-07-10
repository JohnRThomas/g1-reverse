#include "g1_app_symbols.h"
/* named: FUN_0005d568 */
/* globals referenced:
//   0x2001d532  g_bt_settings_load_done      
*/
/* Reconstructed FUN_0005d568 @ 0x5d568  (parity: 300/300 trials, PROVEN) */

extern int smp_auth_get_pairing_method(int param_1);

unsigned int FUN_0005d568(int param_1, unsigned int param_2)
{
    int iVar1;
    unsigned int *puVar2;
    unsigned char newval;

    if (*(volatile unsigned char *)((uintptr_t)&g_bt_settings_load_done) /*=0x2001d532*/ == 0) {
        param_2 = param_2 & 7;
    } else {
        param_2 = param_2 & 0xf;
    }
    iVar1 = smp_auth_get_pairing_method(param_1);
    if (iVar1 == 3) {
        param_2 = param_2 & 0xb;
    } else {
        param_2 = param_2 | 4;
    }
    puVar2 = (unsigned int *)(param_1 + 0x23c);
    newval = *(volatile unsigned char *)((uintptr_t)&g_smp_bondable_default) /*=0x200035ae*/;
    if (*(volatile unsigned int *)puVar2 == 0xffffffff) {
        *(volatile unsigned int *)puVar2 = (unsigned int)newval;
    }
    if (*(volatile unsigned int *)puVar2 == 0) {
        param_2 = param_2 & 0xfe;
    } else {
        param_2 = param_2 | 1;
    }
    return param_2;
}

