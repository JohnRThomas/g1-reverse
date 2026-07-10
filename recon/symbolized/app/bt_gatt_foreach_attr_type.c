#include "g1_app_symbols.h"
/* named: bt_gatt_foreach_attr_type */
/* Reconstructed bt_gatt_foreach_attr_type @ 0x5aa84  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int assert_post_action(int,...);
extern int printk(int,...);
extern int gatt_foreach_iter(int,...);
void bt_gatt_foreach_attr_type(unsigned int param_1, int param_2, int param_3, int param_4, short param_5, int param_6, int param_7)
{
  short local_2a[3];
  if (param_5 == 0) param_5 = -1;
  if (param_1 <= *(volatile unsigned short*)((uintptr_t)&last_static_handle) /*=0x2000ff3c*/) {
    int *piVar4 = (int*)((uintptr_t)&tbl_88058) /*=0x88058*/;
    unsigned int uVar6 = 1;
    unsigned int uVar2 = 0;
    while (1) {
      if ((int*)((uintptr_t)&tbl_88058) /*=0x88070*/ < piVar4) {
        printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,"static_svc <= _bt_gatt_service_static_list_end" /*=0xf49a5*/,"WEST_TOPDIR/zephyr/subsys/bluetooth/host/gatt.c" /*=0xf46b8*/,0x7d7);
        printk("\tunexpected list end location\n" /*=0xf0d20*/);
        assert_post_action("WEST_TOPDIR/zephyr/subsys/bluetooth/host/gatt.c" /*=0xf46b8*/,0x7d7);
      }
      if ((int*)((uintptr_t)&tbl_88058) /*=0x88070*/ <= piVar4) break;
      if ((unsigned int)(*(volatile int*)((int)piVar4+4) + uVar6) < param_1) {
        uVar2 = (*(volatile int*)((int)piVar4+4) + uVar6) & ((uintptr_t)&tbl_ffc8) /*=0xffff*/;
      } else {
        unsigned int uVar5;
        for (uVar5 = 0; (uVar2 = (uVar6+uVar5)&((uintptr_t)&tbl_ffc8) /*=0xffff*/), uVar5 < (unsigned int)*(volatile int*)((int)piVar4+4); uVar5++) {
          int iVar1 = gatt_foreach_iter(uVar5*0x14 + *(volatile int*)piVar4, uVar2, param_1, param_2, param_3, param_4, &param_5, param_6, param_7);
          if (iVar1 == 0) return;
        }
      }
      piVar4 += 2;
      uVar6 = uVar2;
    }
  }
  local_2a[0] = param_5;
  unsigned int *puVar3 = (unsigned int*)*(volatile int*)((uintptr_t)&g_bt_gatt_dynamic_db) /*=0x2000af08*/;
  if (puVar3 != 0) {
    do {
      unsigned int uVar6 = *puVar3;
      if (uVar6 == 0) {
        LAB_ab44:
        for (; uVar6 < puVar3[-1]; uVar6++) {
          int iVar1 = uVar6*0x14 + puVar3[-2];
          iVar1 = gatt_foreach_iter(iVar1, *(unsigned short*)(iVar1+0x10), param_1, param_2, param_3, param_4, local_2a, param_6, param_7);
          if (iVar1 == 0) return;
        }
      } else if (param_1 < *(unsigned short*)(*(int*)(uVar6-8)+0x10)) {
        uVar6 = 0; goto LAB_ab44;
      }
      puVar3 = (unsigned int*)*puVar3;
    } while (puVar3 != 0);
  }
}

