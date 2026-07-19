/* readable reconstruction; identity: FUN_0005c8d8 @ 0x0005c8d8
 * public-name: gatt_connected
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gatt_settings_delete_key                 <= FUN_0005306c @ 0x0005306c
 *   find_cf_cfg_by_addr                      <= FUN_00059b5c @ 0x00059b5c
 *   bt_gatt_clear_sc                         <= FUN_0005a044 @ 0x0005a044
 *   gatt_cf_cfg_clear                        <= FUN_0005a39c @ 0x0005a39c
 *   gatt_connected                           <= FUN_0005c8d8 @ 0x0005c8d8
 *   bt_addr_le_eq_0                          <= FUN_000826b2 @ 0x000826b2
 *   list_unlink_and_release                  <= FUN_000828e8 @ 0x000828e8
 *   bt_gatt_foreach_attr_0                   <= FUN_00082c9c @ 0x00082c9c
 * address symbols (name @ address):
 *   rodata_5a2d5                             @ 0x0005a2d5
 *   g_known_device_table                     @ 0x2000af18
 *   g_known_device_table_addr0               @ 0x2000af19
 */
/* Reconstructed FUN_0005c8d8 @ 0x5c8d8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int gatt_settings_delete_key(unsigned,int);
extern int find_cf_cfg_by_addr(unsigned,int);
extern int bt_gatt_clear_sc(unsigned,int);
extern void gatt_cf_cfg_clear(void);
extern int bt_addr_le_eq_0(int,int);
extern void list_unlink_and_release(int,int,int,void*);
extern void bt_gatt_foreach_attr_0(int,int,int,void*);
int gatt_connected(unsigned param_1, int param_2, int param_3){
  uint32_t context[3] = {
    (uint32_t)param_2,
    ((uint32_t)param_2 & 0xffffff00u) | (param_1 & 0xffu),
    (uint32_t)param_3
  };
  int iVar1, iVar2, iVar4;
  int *piVar3;
  bt_gatt_foreach_attr_0(1, 0xffff, 0x0005a2d5, context);
  iVar1 = gatt_settings_delete_key(param_1, param_2);
  if (iVar1 >= 0 && (iVar1 = bt_gatt_clear_sc(param_1,param_2)) >= 0){
    iVar1 = find_cf_cfg_by_addr(param_1,param_2);
    if (iVar1 != 0) gatt_cf_cfg_clear();
    iVar1 = gatt_settings_delete_key(param_1,param_2);
    if (iVar1 >= 0){
      iVar4 = 0; iVar1 = 0x2000af19;
      do {
        if ((unsigned)*(volatile unsigned char*)(iVar1-1) == param_1 &&
            (iVar2 = bt_addr_le_eq_0(param_2, iVar1)) != 0){
          iVar4 = iVar4 + 0x2000af18;
          piVar3 = *(int**)(iVar4 + 8);
          if (piVar3 != 0){
            iVar1 = *piVar3;
            if (iVar1 != 0) iVar1 -= 0x18;
            *(volatile unsigned short*)((char*)piVar3 - 8) = 0;
            list_unlink_and_release(0, iVar4, 0, piVar3 - 6);
            if (iVar1 != 0){
              while ((iVar2 = *(volatile int*)(iVar1+0x18)) != 0){
                *(volatile unsigned short*)(iVar1+0x10) = 0;
                list_unlink_and_release(0, iVar4, 0, (void*)iVar1);
                iVar1 = iVar2 - 0x18;
              }
              *(volatile unsigned short*)(iVar1+0x10) = 0;
              list_unlink_and_release(0, iVar4, 0, (void*)iVar1);
            }
          }
          break;
        }
        iVar4 += 0x10;
        iVar1 += 0x10;
      } while (iVar4 != 0x30);
      iVar1 = 0;
    }
  }
  return iVar1;
}
