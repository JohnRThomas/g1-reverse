#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00055454 @ 0x00055454
 * public-name: FUN_00055454
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   set_random_address                       <= FUN_000810f2 @ 0x000810f2
 *   bt_id_set_adv_private_addr               <= FUN_00081102 @ 0x00081102
 * address symbols (name @ address):
 *   rodata_88150                             @ 0x00088150
 *   rodata_f37df                             @ 0x000f37df
 *   g_ble_dev_state                          @ 0x20002000
 */
/* Reconstructed FUN_00055454 @ 0x55454  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void FUN_0008104a(uint32_t,int,void*);
extern int set_random_address(uint8_t*,int);
extern int bt_id_set_adv_private_addr(uint8_t*,uint32_t);

int FUN_00055454(uint8_t *param_1, int param_2, int param_3, uint8_t *param_4){
    uint32_t local_20, local_1c;
    if (param_1 == 0 || param_4 == 0) return -0x16;
    uint32_t uVar4 = *(volatile uint8_t*)param_1;
    volatile uint8_t *tbl = (volatile uint8_t*)((unsigned long)&g_ble_dev_state) /*=0x20002000*/;
    uint8_t bVar3;
    int iVar2;
    if ((((uint32_t)param_2 << 0xc) & 0x80000000UL) != 0){          /* bit19 set */
        if ((((uint32_t)param_2 << 0x1d) & 0x80000000UL) != 0){     /* bit2 set */
            local_1c = ((unsigned long)&rodata_f37df) /*=0xf37df*/; local_20 = 2;
            FUN_0008104a(((unsigned long)&rodata_88150) /*=0x88150*/, 0x1040, &local_20);
            return -0x16;
        }
        iVar2 = bt_id_set_adv_private_addr(param_1, (uint32_t)param_2 << 12);
        if (iVar2 != 0) return iVar2;
        bVar3 = 1;
        goto L_551e;
    }
    if ((((uint32_t)param_2 << 0x1f) & 0x80000000UL) != 0){          /* bit0 set */
        if (param_3 == 0){
            bVar3 = tbl[uVar4*7];
            if (bVar3 != 1) goto L_554d8;
          L_554dc:
            iVar2 = set_random_address(param_1, (int)(uVar4*7) + ((unsigned long)&g_ble_dev_state) /*=0x20002000*/ + 1);
            if (iVar2 != 0) return iVar2;
            bVar3 = tbl[uVar4*7];
            *param_4 = bVar3;
            if (param_3 == 0) return 0;
        } else {
            if ((((uint32_t)param_2 << 0x1a) & 0x80000000UL) != 0 &&
                (((int)((uint32_t)tbl[0xd8] << 0x19)) >= 0)){
                return -0x86;
            }
            bVar3 = tbl[uVar4*7];
            if (bVar3 == 1) goto L_554dc;
            *param_4 = bVar3;
        }
        if (((int)((uint32_t)param_2 << 0x1a)) >= 0) return 0;       /* bit5 clear */
        bVar3 = bVar3 | 2;
      L_554d8:
        *param_4 = bVar3;
        return 0;
    }
    if ((((uint32_t)param_2 << 0x1d) & 0x80000000UL) != 0){          /* bit2 set */
        bVar3 = tbl[uVar4*7];
        if (bVar3 != 1) goto L_554d8;
        iVar2 = set_random_address(param_1, (int)((int16_t)(uint16_t)*(volatile uint8_t*)param_1 * 7) + 1 + ((unsigned long)&g_ble_dev_state) /*=0x20002000*/);
        bVar3 = tbl[uVar4*7];
        goto L_551e;
    }
    iVar2 = bt_id_set_adv_private_addr(param_1, (uint32_t)param_2 << 12);
    bVar3 = 1;
  L_551e:
    *param_4 = bVar3;
    return iVar2;
}
