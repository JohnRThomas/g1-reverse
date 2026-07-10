#include "g1_app_symbols.h"
/* named: ipc_service_send_with_retry */
/* globals referenced:
//   0x20007a44  g_st25dv_dev                 
*/
/* Reconstructed ipc_service_send_with_retry @ 0x2563c  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(int);
extern int FUN_0007ca18(int,int);
int ipc_service_send_with_retry(int param_1)
{
    volatile int *piVar1 = (volatile int*)((uintptr_t)&g_st25dv_dev) /*=0x20007a44*/;
    if (param_1 == 0 || *piVar1 == 0) {
        DEBUG_PRINT("input param valid \n" /*=0x9f1af*/);
        return -1;
    }
    int iVar3 = 10;
    int iVar2;
    do {
        iVar2 = FUN_0007ca18(*piVar1, param_1);
        if (iVar2 == 0) {
            return 0;
        }
        iVar3 = iVar3 - 1;
    } while (iVar3 != 0);
    return iVar2;
}

