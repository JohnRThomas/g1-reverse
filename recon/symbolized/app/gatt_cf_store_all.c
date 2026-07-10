#include "g1_app_symbols.h"
/* named: gatt_cf_store_all */
/* globals referenced:
//   0x2000aed4  g_bt_gatt_cf_cfg             
*/
/* Reconstructed gatt_cf_store_all @ 0x5a91c  (parity: 300/300 trials, PROVEN) */

extern int bt_addr_le_eq_0(void *a, unsigned int b);
extern void set_change_aware_no_store(void *a, unsigned int b);
extern void bt_gatt_store_cf(unsigned int a, void *b);

void gatt_cf_store_all(void)
{
    unsigned int uVar1 = ((uintptr_t)&rodata_f2b3a) /*=0xf2b3a*/;
    int iVar4 = 0;
    unsigned char *puVar3 = (unsigned char *)((uintptr_t)&g_bt_gatt_cf_cfg) /*=0x2000aed4*/;
    int iVar2;
    do {
        iVar2 = bt_addr_le_eq_0((void*)(puVar3+1), uVar1);
        if (iVar2 == 0) {
            set_change_aware_no_store((void*)puVar3, 0);
            bt_gatt_store_cf(*(volatile unsigned char*)puVar3, (void*)(puVar3+1));
        }
        iVar4 = iVar4 + 1;
        puVar3 = puVar3 + 0x10;
    } while (iVar4 != 3);
}

