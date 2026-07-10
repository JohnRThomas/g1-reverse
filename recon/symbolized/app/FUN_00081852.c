#include "g1_app_symbols.h"
/* named: FUN_00081852 */
/* Reconstructed FUN_00081852 @ 0x81852  (parity: 300/300 trials, PROVEN) */

extern unsigned long long net_buf_frags_len(int a);
extern int FUN_0005757c(int a, int b, int c);
extern int FUN_0005f3d8(int a, int b);
extern void net_buf_unref(int a);
unsigned FUN_00081852(int param_1, int *param_2, unsigned param_3){
    int iVar2 = *param_2;
    unsigned long long uVar4 = net_buf_frags_len(iVar2);
    unsigned r6hi = (unsigned)(uVar4 >> 32);
    int iVar3 = (int)param_3 + (int)(unsigned)uVar4;
    if ((int)(unsigned)*(volatile unsigned short*)(param_1 + 0x26) < iVar3) return 0xffffff86u;
    if (*(volatile unsigned short*)(iVar2 + 0x10) == 0){
        int t = *(volatile int*)(iVar2 + 4);
        if (t != 0) iVar2 = t;
    }
    int uVar1;
    if (param_3 == 0){
        uVar1 = FUN_0005757c(param_1, iVar2, 2);
        if (uVar1 < 0){
            if ((unsigned)uVar1 == 0xfffffff5u)
                *(volatile unsigned*)(*(volatile int*)(iVar2 + 0x18)) = param_3;
            *(volatile int*)r6hi = iVar2;
            return (unsigned)uVar1;
        }
        param_3 = (unsigned)uVar1 & ((uintptr_t)&tbl_ffc8) /*=0xffff*/;
    }
    while ((int)param_3 < iVar3){
        if (*(volatile unsigned short*)(iVar2 + 0x10) == 0)
            iVar2 = FUN_0005f3d8(0, iVar2);
        uVar1 = FUN_0005757c(param_1, iVar2, 0);
        if (uVar1 < 0){
            if ((unsigned)uVar1 == 0xfffffff5u)
                *(volatile unsigned*)(*(volatile int*)(iVar2 + 0x18)) = param_3;
            *(volatile int*)r6hi = iVar2;
            return (unsigned)uVar1;
        }
        param_3 = (param_3 + (unsigned)uVar1) & ((uintptr_t)&tbl_ffc8) /*=0xffff*/;
    }
    net_buf_unref(iVar2);
    return param_3;
}

