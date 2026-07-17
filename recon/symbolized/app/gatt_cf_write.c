#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0005a5bc @ 0x0005a5bc
 * public-name: gatt_cf_write
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   find_cf_cfg                              <= FUN_00059c04 @ 0x00059c04
 *   gatt_cf_write                            <= FUN_0005a5bc @ 0x0005a5bc
 *   set_change_aware                         <= FUN_00082bb8 @ 0x00082bb8
 * address symbols (name @ address):
 *   rodata_88128                             @ 0x00088128
 *   rodata_f4889                             @ 0x000f4889
 */
/* Reconstructed FUN_0005a5bc @ 0x5a5bc  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern uint8_t* find_cf_cfg(void);
extern void FUN_000828da(void*, int);
extern void FUN_00082a42(uint32_t, int, void*);
extern void set_change_aware(void*, int);

int gatt_cf_write(int param_1, uint32_t param_2, uint8_t *param_3, int param_4, uint16_t param_5){
  uint8_t *puVar1;
  uint32_t uVar2;
  volatile uint32_t local_20, local_1c;
  if (param_5 < 2){
    if ((int)((uint32_t)param_5 + param_4) < 2){
      puVar1 = find_cf_cfg();
      if (puVar1 == 0 && (puVar1 = find_cf_cfg(), puVar1 == 0)){
        param_4 = -0x11;
        local_1c = ((unsigned long)&rodata_f4889) /*=0xf4889*/;
        local_20 = 2;
        FUN_00082a42(((unsigned long)&rodata_88128) /*=0x88128*/, 0x1080, (void*)&local_20);
      } else {
        if (param_4 != 0){
          uVar2 = 0;
          do {
            if ((((puVar1[8] >> (uVar2 & 0xff)) & 1) != 0) &&
                (((*param_3 >> (uVar2 & 0xff)) & 1) == 0)){
              return -0x13;
            }
            uVar2 = uVar2 + 1;
          } while (uVar2 != 3);
          puVar1[8] = puVar1[8] | (*param_3 & 7);
        }
        FUN_000828da((void*)(puVar1+1), param_1 + 0x90);
        *puVar1 = *(uint8_t*)(param_1 + 8);
        set_change_aware((void*)puVar1, 1);
      }
    } else {
      param_4 = -0xd;
    }
  } else {
    param_4 = -7;
  }
  return param_4;
}
