#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0004f198 @ 0x0004f198
 * public-name: bt_ancs_cp_write
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_ancs_cp_write                         <= FUN_0004f198 @ 0x0004f198
 *   bt_gatt_write                            <= FUN_0005c22c @ 0x0005c22c
 *   atomic_clear_bit                         <= FUN_0007f5d8 @ 0x0007f5d8
 * address symbols (name @ address):
 *   ADDR_bt_ancs_cp_write_callback_THUMB     @ 0x0007f5ef
 */
/* Reconstructed FUN_0004f198 @ 0x4f198  (parity: 300/300 trials, PROVEN) */

extern int bt_gatt_write(unsigned int, void*, unsigned int, void*, unsigned int);
extern void atomic_clear_bit(volatile int *, int);

int bt_ancs_cp_write(unsigned int *param_1, unsigned short param_2, unsigned int param_3, unsigned int param_4)
{
    char *base = (char*)param_1;
    *(volatile unsigned short*)(base + 0x20) = param_2;
    *(volatile unsigned int*)(base + 0x14) = ADDR_bt_ancs_cp_write_callback_THUMB /*=0x7f5ef*/;
    unsigned short v8 = *(volatile unsigned short*)(base + 8);
    *(volatile unsigned int*)(base + 0x24) = param_3;
    *(volatile unsigned short*)(base + 0x18) = v8;
    *(volatile unsigned short*)(base + 0x1a) = 0;
    *(volatile unsigned int*)(base + 0x1c) = (unsigned int)(base + 0x28);
    int iVar2 = bt_gatt_write(*(volatile unsigned int*)base, base + 0x14, param_3, base + 0x28, param_4);
    if (iVar2 != 0) {
        atomic_clear_bit(base + 4, 2);
    }
    return iVar2;
}
