#include "g1_app_symbols.h"
/* named: FUN_000549ec */
/* globals referenced:
//   0x20002000  g_ble_dev_state              
*/
/* Reconstructed FUN_000549ec @ 0x549ec  (parity: 300/300 trials, PROVEN) */

extern void FUN_00080ea2(unsigned int a, unsigned int b, void *c);
extern void atomic_or(unsigned int a, unsigned int b, unsigned int c, unsigned int d);
extern void FUN_000548b8(void);

unsigned int FUN_000549ec(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    volatile unsigned char *base = (volatile unsigned char*)((uintptr_t)&g_ble_dev_state) /*=0x20002000*/;
    unsigned char flag = base[7];
    if (flag == 0) {
        struct { unsigned int f0; unsigned int f1; } s;
        s.f0 = 2;
        s.f1 = "No ID address. App must call settings_load()" /*=0xf322e*/;
        FUN_00080ea2(((uintptr_t)&tbl_880d8) /*=0x88138*/, 0x10c0, &s);
    } else {
        atomic_or(((uintptr_t)&g_ble_dev_state) /*=0x20002000*/ + 0xd4, 8, param_3, flag);
        FUN_000548b8();
    }
    return 0;
}

