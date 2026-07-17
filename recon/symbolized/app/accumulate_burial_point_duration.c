#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007db50 @ 0x0007db50
 * public-name: accumulate_burial_point_duration
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   __aeabi_ldivmod                          <= FUN_0000e1a4 @ 0x0000e1a4
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   get_current_burial_point_type            <= FUN_0007dac0 @ 0x0007dac0
 *   accumulate_burial_point_duration         <= FUN_0007db50 @ 0x0007db50
 */
/* Reconstructed FUN_0007db50 @ 0x7db50  (parity: 300/300 trials, PROVEN) */

extern unsigned int get_current_burial_point_type(void);
extern int get_device_info(void);
extern int __aeabi_ldivmod(int param_1, int param_2, int param_3, int param_4, int param_5);

void accumulate_burial_point_duration(int param_1, int param_2, int param_3, int param_4)
{
    unsigned int uVar1;
    int iVar2;
    int iVar3;

    uVar1 = get_current_burial_point_type();
    if (uVar1 < 7) {
        iVar2 = get_device_info();
        iVar3 = __aeabi_ldivmod(param_1, param_2, 1000, 0, param_4);
        iVar2 = uVar1 * 0xc + iVar2;
        *(int *)(iVar2 + 0x1136) = *(int *)(iVar2 + 0x1136) + iVar3;
        iVar2 = get_device_info();
        *(int *)(iVar2 + 0x10d2) = *(int *)(iVar2 + 0x10d2) + iVar3;
    }
}
