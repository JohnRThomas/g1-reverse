#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00083cb4 @ 0x00083cb4
 * public-name: flash_area_has_driver
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   flash_area_has_driver                    <= FUN_00083cb4 @ 0x00083cb4
 *   z_device_is_ready                        <= FUN_0008638c @ 0x0008638c
 */
/* Reconstructed FUN_00083cb4 @ 0x83cb4  (parity: 300/300 trials, PROVEN) */

extern int z_device_is_ready(int);

unsigned int flash_area_has_driver(void *param_1)
{
    int iVar1;
    unsigned int uVar2;
    int *p = *(volatile int**)((char*)param_1 + 4);
    iVar1 = z_device_is_ready(*(volatile unsigned int*)((char*)p + 4));
    if (iVar1 == 0) {
        uVar2 = 0xffffffed;
    } else {
        uVar2 = 0;
    }
    return uVar2;
}
