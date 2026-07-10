#include "g1_app_symbols.h"
/* named: FUN_00052edc */
/* Reconstructed FUN_00052edc @ 0x52edc  (parity: 300/300 trials, PROVEN) */

extern int settings_subsys_init(void);
extern void FUN_0004d944(unsigned int a, unsigned int b, void *c, unsigned int d);

int FUN_00052edc(void)
{
    int iVar1 = settings_subsys_init();
    if (iVar1 != 0) {
        struct { unsigned int f0; unsigned int f1; unsigned int f2; } s;
        s.f0 = 3;
        s.f1 = "settings_subsys_init failed (err %d)" /*=0xf2c46*/;
        s.f2 = iVar1;
        FUN_0004d944(((uintptr_t)&tbl_880d8) /*=0x88178*/, 0x1840, &s, 0);
    }
    return iVar1;
}

