#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   local_2a         => struct g1_layout_gatt_foreach_attr_locals__stack_1219   [stack_1219; G1-original]
 * Raw function identity: 0x0005aa84.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0005aa84 @ 0x0005aa84
 * public-name: bt_gatt_foreach_attr_type
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_gatt_foreach_attr_type                <= FUN_0005aa84 @ 0x0005aa84
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   gatt_foreach_iter                        <= FUN_00082712 @ 0x00082712
 * address symbols (name @ address):
 *   rodata_88058                             @ 0x00088058
 *   rodata_88070                             @ 0x00088070
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f0d20                             @ 0x000f0d20
 *   rodata_f46b8                             @ 0x000f46b8
 *   rodata_f49a5                             @ 0x000f49a5
 *   g_bt_gatt_dynamic_db                     @ 0x2000af08
 *   last_static_handle                       @ 0x2000ff3c
 */
/* Reconstructed FUN_0005aa84 @ 0x5aa84  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int assert_post_action(int,...);
extern int printk(int,...);
extern int gatt_foreach_iter(int,...);
void bt_gatt_foreach_attr_type(unsigned int param_1, int param_2, int param_3, int param_4, short param_5, int param_6, int param_7)
{
  short local_2a[3];
  if (param_5 == 0) param_5 = -1;
  if (param_1 <= *(volatile unsigned short*)((unsigned long)&last_static_handle) /*=0x2000ff3c*/) {
    int *piVar4 = (int*)((unsigned long)&rodata_88058) /*=0x88058*/;
    unsigned int uVar6 = 1;
    unsigned int uVar2 = 0;
    while (1) {
      if ((int*)((unsigned long)&rodata_88070) /*=0x88070*/ < piVar4) {
        printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/,((unsigned long)&rodata_f49a5) /*=0xf49a5*/,((unsigned long)&rodata_f46b8) /*=0xf46b8*/,0x7d7);
        printk(((unsigned long)&rodata_f0d20) /*=0xf0d20*/);
        assert_post_action(((unsigned long)&rodata_f46b8) /*=0xf46b8*/,0x7d7);
      }
      if ((int*)((unsigned long)&rodata_88070) /*=0x88070*/ <= piVar4) break;
      if ((unsigned int)(*(volatile int*)((int)piVar4+4) + uVar6) < param_1) {
        uVar2 = (*(volatile int*)((int)piVar4+4) + uVar6) & 0xffff;
      } else {
        unsigned int uVar5;
        for (uVar5 = 0; (uVar2 = (uVar6+uVar5)&0xffff), uVar5 < (unsigned int)*(volatile int*)((int)piVar4+4); uVar5++) {
          int iVar1 = gatt_foreach_iter(uVar5*0x14 + *(volatile int*)piVar4, uVar2, param_1, param_2, param_3, param_4, &param_5, param_6, param_7);
          if (iVar1 == 0) return;
        }
      }
      piVar4 += 2;
      uVar6 = uVar2;
    }
  }
  local_2a[0] = param_5;
  unsigned int *puVar3 = (unsigned int*)*(volatile int*)((unsigned long)&g_bt_gatt_dynamic_db) /*=0x2000af08*/;
  if (puVar3 != 0) {
    do {
      unsigned int uVar6 = *puVar3;
      if (uVar6 == 0) {
        control_label_ab44:
        for (; uVar6 < puVar3[-1]; uVar6++) {
          int iVar1 = uVar6*0x14 + puVar3[-2];
          iVar1 = gatt_foreach_iter(iVar1, *(unsigned short*)(iVar1+0x10), param_1, param_2, param_3, param_4, local_2a, param_6, param_7);
          if (iVar1 == 0) return;
        }
      } else if (param_1 < *(unsigned short*)(*(int*)(uVar6-8)+0x10)) {
        uVar6 = 0; goto control_label_ab44;
      }
      puVar3 = (unsigned int*)*puVar3;
    } while (puVar3 != 0);
  }
}
