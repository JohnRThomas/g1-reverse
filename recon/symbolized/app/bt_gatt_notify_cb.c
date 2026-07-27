#include "g1_app_symbols.h"
#include "../../headers/g1_log.h"
/* readable reconstruction; identity: FUN_0005b754 @ 0x0005b754
 * public-name: bt_gatt_notify_cb
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_gatt_attr_get_handle                  <= FUN_0005a9f4 @ 0x0005a9f4
 *   bt_gatt_foreach_attr_type                <= FUN_0005aa84 @ 0x0005aa84
 *   gatt_notify                              <= FUN_0005b680 @ 0x0005b680
 *   bt_gatt_notify_cb                        <= FUN_0005b754 @ 0x0005b754
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   bt_uuid_cmp                              <= FUN_00080d3e @ 0x00080d3e
 *   read_struct_first_word                   <= FUN_0008270c @ 0x0008270c
 *   bt_gatt_attr_value_handle                <= FUN_00082c0e @ 0x00082c0e
 * address symbols (name @ address):
 *   ADDR_gatt_send_ccc_update_THUMB          @ 0x0005b891
 *   rodata_825fb                             @ 0x000825fb
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f46b8                             @ 0x000f46b8
 *   rodata_f4a0a                             @ 0x000f4a0a   [INLINED -- G6 literal batch]
 *   rodata_f4b3d                             @ 0x000f4b3d   [INLINED -- G6 literal batch]
 *   rodata_f4b44                             @ 0x000f4b44
 *   g_ble_dev_ncmd_sem                       @ 0x200020d4
 */
/* Reconstructed FUN_0005b754 @ 0x5b754  (parity: 300/300 trials, PROVEN) */

extern int bt_gatt_attr_get_handle();
extern int bt_gatt_foreach_attr_type(int,...);
extern unsigned int gatt_notify(int, unsigned short, int);
extern int assert_post_action(int, int);
extern int bt_uuid_cmp(int, int);
extern int read_struct_first_word(unsigned long);
extern int bt_gatt_attr_value_handle();

int bt_gatt_notify_cb(int param_1, int *param_2)
{
  int iVar1;
  int uVar2;
  unsigned char local_28[2];
  unsigned short local_26;
  unsigned int *local_24;
  unsigned short local_20;
  int local_1c;
  unsigned short local_18;
  int *local_14;

  if (param_2 == 0) {
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)"params") /*=0xf4b3d*/, ((unsigned long)&rodata_f46b8) /*=0xf46b8*/, 0xae3);
    printk(((unsigned long)"\tinvalid parameters\n\n") /*=0xf4a0a*/);
    uVar2 = 0xae3;
    assert_post_action(((unsigned long)&rodata_f46b8) /*=0xf46b8*/, uVar2);
    param_2 = (int *)0xae3;
  } else {
again:
    if (param_2[1] != 0 || param_2[0] != 0) {
      iVar1 = read_struct_first_word(((unsigned long)&g_ble_dev_ncmd_sem) /*=0x200020d4*/);
      if ((iVar1 & 4) == 0) {
        return 0xfffffff5;
      }
      if (param_1 != 0 && *(char*)(param_1+0xd) != 7) {
        return 0xffffff80;
      }
      local_24 = (unsigned int*)param_2[1];
      iVar1 = bt_gatt_attr_get_handle();
      local_20 = (unsigned short)iVar1;
      if (param_2[0] == 0) {
        if (iVar1 != 0) goto LAB;
      } else {
        local_24 = 0;
        bt_gatt_foreach_attr_type(iVar1, 0xffff, param_2[0], 0, 1, ((unsigned long)&rodata_825fb) /*=0x825fb*/, &local_24);
        if (local_24 != 0) {
          param_2[1] = (int)local_24;
LAB:
          local_28[0] = 0;
          local_26 = 0x2803;
          iVar1 = bt_uuid_cmp(*local_24, local_28);
          if (iVar1 == 0) {
            if ((*(unsigned char*)(local_24[3]+6) & 0x10) == 0) {
              return 0xffffffea;
            }
            local_20 = (unsigned short)bt_gatt_attr_value_handle();
          }
          if (param_1 != 0) {
            uVar2 = gatt_notify(param_1, local_20, param_2);
            return uVar2;
          }
          local_1c = 0xffffff80;
          local_26 = 0x2902;
          local_18 = 1;
          local_28[0] = 0;
          local_14 = param_2;
          bt_gatt_foreach_attr_type(local_20, 0xffff, local_28, 0, 1, ADDR_gatt_send_ccc_update_THUMB /*=0x5b891*/, &local_24);
          return local_1c;
        }
      }
      return 0xfffffffe;
    }
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)&rodata_f4b44) /*=0xf4b44*/, ((unsigned long)&rodata_f46b8) /*=0xf46b8*/, 0xae4);
    printk(((unsigned long)"\tinvalid parameters\n\n") /*=0xf4a0a*/);
    uVar2 = 0xae4;
    assert_post_action(((unsigned long)&rodata_f46b8) /*=0xf46b8*/, uVar2);
    param_2 = (int *)0xae4;
    goto again;
  }
  /* A returning diagnostic oracle continues at the common dereference. */
  goto again;
}
