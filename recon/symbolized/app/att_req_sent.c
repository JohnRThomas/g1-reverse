#include "g1_app_symbols.h"
/* named: att_req_sent */
/* Reconstructed att_req_sent @ 0x822fc  (parity: 300/300 trials, PROVEN) */

extern void FUN_000822ae(void);
extern void FUN_0007350c(int,int*,int,int);
extern void FUN_0005833c(int*);
void att_req_sent(int param_1,int *param_2,int param_3)
{
    int *piVar1 = param_2;
    if (param_3 == 0) {
        FUN_000822ae();
    }
    if (*(int*)(*param_2 + 0x124) != 0) {
        FUN_0007350c(*param_2 + 0x160, piVar1, "eflash command end .......\n" /*=0xf0000*/, 0);
    }
    FUN_0005833c(param_2);
}

