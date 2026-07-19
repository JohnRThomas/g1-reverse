#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_2          => struct g1_layout_bt_gatt_subscribe_params__param_0262   [param_0262; library]
 *   param_1          => struct g1_layout_bt_gatt_subscribe_params__param_0263   [param_0263; library]
 * Raw function identity: 0x0005c4f0.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0005c4f0 @ 0x0005c4f0
 * public-name: bt_gatt_unsubscribe
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gatt_find_conn_in_known_table            <= FUN_00059c70 @ 0x00059c70
 *   gatt_sub_free                            <= FUN_00059e78 @ 0x00059e78
 *   gatt_write_ccc                           <= FUN_0005a540 @ 0x0005a540
 *   bt_gatt_unsubscribe                      <= FUN_0005c4f0 @ 0x0005c4f0
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   read_struct_first_word                   <= FUN_0008270c @ 0x0008270c
 *   sys_slist_find_and_remove_0              <= FUN_00082ab8 @ 0x00082ab8
 *   bt_gatt_cancel                           <= FUN_00082e24 @ 0x00082e24
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f3ebd                             @ 0x000f3ebd
 *   rodata_f46b8                             @ 0x000f46b8
 *   rodata_f4a0a                             @ 0x000f4a0a
 *   rodata_f4b3d                             @ 0x000f4b3d
 */
/* Reconstructed FUN_0005c4f0 @ 0x5c4f0  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void printk(unsigned,unsigned,unsigned,unsigned,unsigned);
extern void assert_post_action(unsigned,unsigned);
extern int gatt_find_conn_in_known_table(void);
extern int gatt_sub_free(int);
extern int gatt_write_ccc(int,int*);
extern int read_struct_first_word(int*);
extern void sys_slist_find_and_remove_0(int,int*);
extern void bt_gatt_cancel(int,int*);
typedef int (*codef)(int,int*,int);
int bt_gatt_unsubscribe(int param_1, int *param_2, unsigned param_3, unsigned param_4)
{
  int iVar1, iVar2, bVar4, bVar6; int *piVar5;
  if (param_1 == 0) {
    printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/,((unsigned long)&rodata_f3ebd) /*=0xf3ebd*/,((unsigned long)&rodata_f46b8) /*=0xf46b8*/,0x14dc,param_4);
    printk(((unsigned long)&rodata_f4a0a) /*=0xf4a0a*/,0,0,0,0);
    assert_post_action(((unsigned long)&rodata_f46b8) /*=0xf46b8*/,0x14dc);
  }
  if (param_2 == 0) {
    printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/,((unsigned long)&rodata_f4b3d) /*=0xf4b3d*/,((unsigned long)&rodata_f46b8) /*=0xf46b8*/,0x14dd,param_4);
    printk(((unsigned long)&rodata_f4a0a) /*=0xf4a0a*/,0,0,0,0);
    assert_post_action(((unsigned long)&rodata_f46b8) /*=0xf46b8*/,0x14dd);
  }
  if (*(char*)(param_1+0xd) != 7) return -0x80;
  iVar1 = gatt_find_conn_in_known_table();
  if ((iVar1 != 0) && (piVar5 = *(int**)(iVar1+8), piVar5 != 0)) {
    bVar4 = 0; bVar6 = 0;
    do {
      if (param_2 == piVar5 + -6) bVar4 = 1;
      else if ((unsigned short)piVar5[-3] == (unsigned short)param_2[3]) bVar6 = 1;
      piVar5 = (int*)*piVar5;
    } while (piVar5 != 0);
    if (bVar4) {
      iVar2 = read_struct_first_word(param_2 + 5);
      if (iVar2 << 0x1d < 0) bt_gatt_cancel(param_1, param_2);
      if (bVar6) {
        sys_slist_find_and_remove_0(iVar1+8, param_2+6);
        if (*(int*)(iVar1+8) == 0) gatt_sub_free(iVar1);
        (*(codef)*param_2)(param_1, param_2, 0);
      } else {
        *(volatile short*)(param_2+4) = 0;
        iVar2 = gatt_write_ccc(param_1, param_2);
        if (iVar2 != 0) return iVar2;
        sys_slist_find_and_remove_0(iVar1+8, param_2+6);
        if (*(int*)(iVar1+8) == 0) gatt_sub_free(iVar1);
      }
      return 0;
    }
  }
  return -0x16;
}
