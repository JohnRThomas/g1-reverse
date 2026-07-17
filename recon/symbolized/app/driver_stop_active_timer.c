#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00084c2c @ 0x00084c2c
 * public-name: driver_stop_active_timer
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   driver_stop_active_timer                 <= FUN_00084c2c @ 0x00084c2c
 */
/* Reconstructed FUN_00084c2c @ 0x84c2c  (parity: 300/300 trials, PROVEN) */

extern void FUN_0008673e(int);
int driver_stop_active_timer(int param_1)
{
    int iVar3 = *(int*)(param_1 + 0x10);
    int iVar4 = **(int**)(param_1 + 4);
    int iVar2 = *(int*)(iVar3 + 0xc);
    if (*(int*)(iVar2 + 8) == 0) {
        return 0xfffffff2;
    }
    *(char*)(iVar2 + 0xcd) = 0;
    FUN_0008673e(*(int*)(iVar3 + 0xc) + 0x20);
    *(int*)(iVar4 + 0xc) = 1;
    return 0;
}
