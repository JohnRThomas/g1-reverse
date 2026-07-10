#include "g1_app_symbols.h"
/* named: FUN_0004ea78 */
/* Reconstructed FUN_0004ea78 @ 0x4ea78  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned char byte; typedef uint32_t undefined4; typedef unsigned int uint; typedef unsigned short ushort;
extern int FUN_0004e964(int,...); extern int gatt_dm_data_add_attribute(int,...); extern int gatt_dm_data_add_uuid(int,...);
extern int bt_gatt_discover(int,...); extern int assert_post_action(int,...); extern int printk(int,...);
extern int attr_find_by_handle(int,...); extern int FUN_0007f406(int,...); extern int discovery_complete_error(int,...);
extern int discovery_complete_not_found(int,...); extern int bt_gatt_dm_attr_service_val(int,...); extern int bt_gatt_dm_attr_chrc_val(int,...);
extern int bt_uuid_cmp(int,...);

undefined4 FUN_0004ea78(int param_1,undefined4 *param_2,int param_3)
{
  byte bVar1; int *piVar2; int iVar3; int iVar4; int *piVar5; undefined4 *puVar6; undefined4 *puVar7;
  uint uVar8; undefined4 uVar9; int *piVar10;
  undefined4 local_50, local_4c; uint uStack_48; unsigned char local_3c[2]; unsigned short local_3a;
  unsigned char local_38[2]; unsigned short local_36; undefined4 local_28, local_24;
  piVar2 = (int*)((uintptr_t)&cur_service_val) /*=0x2000a154*/;
  if (*(volatile int*)piVar2 != param_1) {
    local_24 = "Unexpected conn object. Aborting." /*=0xf1299*/; local_28 = 2;
    FUN_0007f406(((uintptr_t)&tbl_880d8) /*=0x88130*/,0x1040,(int)&local_28);
    uVar8 = 0xfffffff2;
    goto LAB_eaa6;
  }
  bVar1 = *(byte*)(param_3 + 0x10);
  if (bVar1 == 3) {
    if (param_2 == 0) { LAB_ebe6: FUN_0004e964(0); return 0; }
    local_38[0] = 0; local_36 = 0x2803;
    iVar3 = bt_uuid_cmp(*param_2,(int)local_38);
    if (iVar3 != 0) { printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,"bt_uuid_cmp(attr->uuid, ((struct bt_uuid *) ((struct bt_uuid_16[]) {{ .uuid = { BT_UUID_TYPE_16 }, .val = (0x2803), }}))) == 0" /*=0xf14c2*/,"WEST_TOPDIR/nrf/subsys/bluetooth/gatt_dm.c" /*=0xf11bc*/,0x19c); uVar9 = 0x19c; goto LAB_eb7e; }
    iVar3 = attr_find_by_handle((int)piVar2,*(ushort*)(param_2 + 4));
    if (iVar3 == 0) { uVar8 = 0xfffffffd; goto LAB_eaa6; }
    piVar5 = (int*)param_2[3];
    piVar10 = (int*)bt_gatt_dm_attr_chrc_val(0);
    if (piVar10 == 0) { printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,"cur_gatt_chrc != ((void *)0)" /*=0xf1541*/,"WEST_TOPDIR/nrf/subsys/bluetooth/gatt_dm.c" /*=0xf11bc*/,0x1a8); uVar9 = 0x1a8; goto LAB_eb7e; }
    *piVar10 = *piVar5; piVar10[1] = piVar5[1];
    iVar3 = gatt_dm_data_add_uuid(*piVar10); *piVar10 = iVar3;
    if (iVar3 != 0) return 1;
LAB_ec80:
    uVar8 = 0xfffffff4;
LAB_eaa6:
    discovery_complete_error((int)piVar2,uVar8);
    return 0;
  }
  if (bVar1 < 4) {
    if (bVar1 != 2) {
      if (param_2 == 0) { discovery_complete_not_found((int)((uintptr_t)&cur_service_val) /*=0x2000a154*/); return 0; }
      piVar10 = (int*)param_2[3];
      iVar3 = gatt_dm_data_add_attribute((int)param_2,8);
      local_3c[0] = 0; local_3a = 0x2800;
      iVar4 = bt_uuid_cmp(*param_2,(int)local_3c);
      if (iVar4 != 0) {
        local_38[0] = 0; local_36 = 0x2801;
        iVar4 = bt_uuid_cmp(*param_2,(int)local_38);
        if (iVar4 != 0) { printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,((uintptr_t)&rodata_f12bb) /*=0xf12bb*/,"WEST_TOPDIR/nrf/subsys/bluetooth/gatt_dm.c" /*=0xf11bc*/,0x127); uVar9 = 0x127; goto LAB_eb7e; }
      }
      uVar9 = "Not enough memory for service attribute." /*=0xf13bc*/;
      if (iVar3 == 0) {
LAB_eb88:
        local_28 = 2; local_24 = uVar9;
        FUN_0007f406(((uintptr_t)&tbl_880d8) /*=0x88130*/,0x1040,(int)&local_28);
      } else {
        piVar5 = (int*)bt_gatt_dm_attr_service_val(iVar3);
        if (piVar5 == 0) { printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,"cur_service_val != ((void *)0)" /*=0xf13e5*/,"WEST_TOPDIR/nrf/subsys/bluetooth/gatt_dm.c" /*=0xf11bc*/,0x13b); uVar9 = 0x13b; goto LAB_eb7e; }
        *piVar5 = *piVar10; piVar5[1] = piVar10[1];
        iVar4 = gatt_dm_data_add_uuid(*piVar5); *piVar5 = iVar4;
        uVar9 = "Not enough memory for service attribute data." /*=0xf1404*/;
        if (iVar4 == 0) goto LAB_eb88;
        iVar4 = piVar5[1];
        *(short*)((int)piVar2 + 0x16) = (short)iVar4;
        if (*(short*)(iVar3 + 4) == (short)iVar4) goto LAB_ebe6;
        piVar2[2] = 0; *(char*)((int)piVar2 + 0x18) = 5;
        uVar9 = ((uintptr_t)&g_gatt_dm_discover_params_uuid) /*=0x2000a15c*/;
        *(short*)((int)piVar2 + 0x10) = *(short*)(iVar3 + 4) + 1;
        uStack_48 = bt_gatt_discover(*piVar2,uVar9);
        if (uStack_48 == 0) return 0;
        local_4c = "Descriptor discover failed, error: %d." /*=0xf1432*/; local_50 = 3;
        FUN_0007f406(((uintptr_t)&tbl_880d8) /*=0x88130*/,0x1840,(int)&local_50);
      }
      uVar8 = 0xfffffff4; piVar2 = (int*)((uintptr_t)&cur_service_val) /*=0x2000a154*/;
      goto LAB_eaa6;
    }
  } else if (bVar1 == 5) {
    if (param_2 == 0) {
      if ((uint)piVar2[0x4d] < 2) goto LAB_ebe6;
      piVar10 = piVar2 + 2;
      *(short*)((int)piVar2 + 0x10) = (short)piVar2[8] + 1;
      *(char*)((int)piVar2 + 0x18) = 3;
      uVar8 = bt_gatt_discover(param_1,(int)piVar10);
      if (uVar8 == 0) return 0;
      local_4c = "Characteristic discover failed, error: %d." /*=0xf1459*/; local_50 = 3; uStack_48 = uVar8;
      FUN_0007f406(((uintptr_t)&tbl_880d8) /*=0x88130*/,0x1840,(int)&local_50);
      goto LAB_eaa6;
    }
    local_38[0] = 0; local_36 = 0x2803;
    iVar3 = bt_uuid_cmp(*param_2,(int)local_38);
    if (iVar3 == 0) {
      puVar6 = (undefined4*)gatt_dm_data_add_attribute((int)param_2,8);
      puVar7 = (undefined4*)bt_gatt_dm_attr_chrc_val(0);
      *puVar7 = *puVar6; return 1;
    }
    iVar3 = gatt_dm_data_add_attribute((int)param_2,0);
    if (iVar3 != 0) return 1;
    uStack_48 = (uint)*(ushort*)(param_2 + 4);
    local_4c = "Not enough memory for next attribute descriptor at handle %u." /*=0xf1484*/; local_50 = 3;
    FUN_0007f406(((uintptr_t)&tbl_880d8) /*=0x88130*/,0x1840,(int)&local_50);
    goto LAB_ec80;
  }
  printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,((uintptr_t)&rodata_f7a30) /*=0xf7a30*/,"WEST_TOPDIR/nrf/subsys/bluetooth/gatt_dm.c" /*=0xf11bc*/,0x1d2);
  printk("\tUnknown param type.\n" /*=0xf155e*/);
  uVar9 = 0x1d2;
LAB_eb7e:
  assert_post_action("WEST_TOPDIR/nrf/subsys/bluetooth/gatt_dm.c" /*=0xf11bc*/,uVar9);
  return 0;
}

