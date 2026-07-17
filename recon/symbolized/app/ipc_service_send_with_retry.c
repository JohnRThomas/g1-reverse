#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0002563c @ 0x0002563c
 * public-name: ipc_service_send_with_retry
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ipc_service_send_with_retry              <= FUN_0002563c @ 0x0002563c
 * address symbols (name @ address):
 *   rodata_9f1af                             @ 0x0009f1af
 *   g_st25dv_dev                             @ 0x20007a44
 */
/* Reconstructed FUN_0002563c @ 0x2563c  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(int);
extern int FUN_0007ca18(int,int);
int ipc_service_send_with_retry(int param_1)
{
    volatile int *piVar1 = (volatile int*)((unsigned long)&g_st25dv_dev) /*=0x20007a44*/;
    if (param_1 == 0 || *piVar1 == 0) {
        DEBUG_PRINT(((unsigned long)&rodata_9f1af) /*=0x9f1af*/);
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
