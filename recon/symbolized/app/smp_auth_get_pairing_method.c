#include "g1_app_symbols.h"
/* named: smp_auth_get_pairing_method */
/* globals referenced:
//   0x2001d532  g_bt_settings_load_done      
*/
/* Reconstructed smp_auth_get_pairing_method @ 0x5caec  (parity: 300/300 trials, PROVEN) */
extern int FUN_0005cac0(void);

int smp_auth_get_pairing_method(void)
{
    int *piVar1 = (int *)(long)FUN_0005cac0();
    if (piVar1 == 0) return 3;
    int iVar2 = piVar1[1];
    if (piVar1[0] == 0) {
        return (iVar2 == 0) ? 3 : 2;
    }
    if (iVar2 == 0) {
        if (*(volatile unsigned char*)((uintptr_t)&g_bt_settings_load_done) /*=0x2001d532*/ == 0) return 0;
        if (piVar1[2] != 0) return 1;
    } else {
        if (piVar1[2] != 0 || *(volatile unsigned char*)((uintptr_t)&g_bt_settings_load_done) /*=0x2001d532*/ == 0) return 4;
    }
    if (iVar2 != 0) iVar2 = 1;
    return iVar2 << 1;
}
