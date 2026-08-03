#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0004ea78 @ 0x0004ea78
 * public-name: discovery_callback
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gatt_dm_notify_discovery_complete        <= FUN_0004e964 @ 0x0004e964
 *   gatt_dm_data_add_attribute               <= FUN_0004e9a0 @ 0x0004e9a0
 *   uuid_store                               <= FUN_0004ea28 @ 0x0004ea28
 *   bt_gatt_discover                         <= FUN_0005b9cc @ 0x0005b9cc
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   attr_find_by_handle                      <= FUN_0007f386 @ 0x0007f386
 *   gatt_dm_log_helper                       <= FUN_0007f406 @ 0x0007f406
 *   discovery_complete_error                 <= FUN_0007f40c @ 0x0007f40c
 *   discovery_complete_not_found             <= FUN_0007f438 @ 0x0007f438
 *   bt_gatt_dm_attr_service_val              <= FUN_0007f460 @ 0x0007f460
 *   bt_gatt_dm_attr_chrc_val                 <= FUN_0007f4a0 @ 0x0007f4a0
 *   bt_uuid_cmp                              <= FUN_00080d3e @ 0x00080d3e
 * address symbols (name @ address):
 *   rodata_88130                             @ 0x00088130
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f11bc                             @ 0x000f11bc
 *   rodata_f1299                             @ 0x000f1299
 *   rodata_f12bb                             @ 0x000f12bb   [INLINED -- G6 literal batch]
 *   rodata_f13bc                             @ 0x000f13bc
 *   rodata_f13e5                             @ 0x000f13e5   [INLINED -- G6 literal batch]
 *   rodata_f1404                             @ 0x000f1404
 *   rodata_f1432                             @ 0x000f1432
 *   rodata_f1459                             @ 0x000f1459
 *   rodata_f1484                             @ 0x000f1484
 *   rodata_f14c2                             @ 0x000f14c2   [INLINED -- G6 literal batch]
 *   rodata_f1541                             @ 0x000f1541   [INLINED -- G6 literal batch]
 *   rodata_f155e                             @ 0x000f155e   [INLINED -- G6 literal batch]
 *   rodata_f7a30                             @ 0x000f7a30
 *   cur_service_val                          @ 0x2000a154
 *   g_gatt_dm_discover_params_uuid           @ 0x2000a15c
 */
/* Reconstructed FUN_0004ea78 @ 0x4ea78  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "../../../headers/g1_log.h"
#include "g1_unsorted.h"
typedef unsigned char byte; typedef uint32_t undefined4; typedef unsigned int uint; typedef unsigned short ushort;
extern void gatt_dm_notify_discovery_complete(void); extern int gatt_dm_data_add_attribute(int,int); extern int uuid_store(int);
extern int bt_gatt_discover(int, int *); extern int assert_post_action(int, int);
extern int attr_find_by_handle(int,int); extern int gatt_dm_log_helper(int,int,int); extern int discovery_complete_error(int,int);
extern int discovery_complete_not_found(int); extern int bt_gatt_dm_attr_service_val(int); extern int bt_gatt_dm_attr_chrc_val(int);

#define discovery_complete gatt_dm_notify_discovery_complete
#define attr_store gatt_dm_data_add_attribute
#define uuid_store uuid_store
#define bt_gatt_discover bt_gatt_discover
#define attr_find_by_handle attr_find_by_handle
#define discovery_complete_error discovery_complete_error
#define discovery_complete_not_found discovery_complete_not_found
#define bt_gatt_dm_attr_service_val bt_gatt_dm_attr_service_val
#define bt_gatt_dm_attr_chrc_val bt_gatt_dm_attr_chrc_val
#define bt_uuid_cmp bt_uuid_cmp

#define LOG_WITH_U32(message_, value_) do {                            \
  uint32_t *record_ = (uint32_t *)__builtin_alloca(32);                \
  record_ += 4;                                                        \
  record_[0] = 3;                                                     \
  record_[1] = (uint32_t)(message_);                                  \
  record_[2] = (uint32_t)(value_);                                    \
  gatt_dm_log_helper(((unsigned long)&rodata_88130) /*=0x88130*/, 0x1840, (int)record_);                         \
} while (0)

undefined4 discovery_callback(int param_1,undefined4 *param_2,int param_3)
{
  byte bVar1; int *piVar2; int iVar3; int iVar4; int *piVar5; undefined4 *puVar6; undefined4 *puVar7;
  uint uVar8; register undefined4 uVar9 asm("r9"); int *piVar10;
  uint uStack_48;
  struct dm_selector { byte zero; byte reserved; ushort uuid; };
  struct {
    uint32_t unused0;
    struct dm_selector primary;
    struct dm_selector fallback;
    uint32_t reserved[3];
    undefined4 log[2];
  } frame;
#define local_28 frame.log[0]
#define local_24 frame.log[1]
  /* Preserve the source callback frame as one object: the two selectors are
   * at offsets 4/8 and the fixed logger record is at offset 24. */
  __asm__ volatile ("" : "+m" (frame));
  piVar2 = (int*)((unsigned long)&cur_service_val) /*=0x2000a154*/;
  if (*(volatile int *)piVar2 != param_1) {
    local_24 = ((unsigned long)&rodata_f1299) /*=0xf1299*/; local_28 = 2;
    gatt_dm_log_helper(((unsigned long)&rodata_88130) /*=0x88130*/,0x1040,(int)frame.log);
    uVar8 = 0xfffffff2;
    goto LAB_eaa6;
  }
  bVar1 = *(byte*)(param_3 + 0x10);
  if (bVar1 == 3) {
    if (param_2 == 0) { LAB_ebe6: discovery_complete(); return 0; }
    frame.fallback.zero = 0; frame.fallback.uuid = 0x2803;
    iVar3 = bt_uuid_cmp(*param_2,(int)&frame.fallback);
    if (iVar3 != 0) { printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)"bt_uuid_cmp(attr->uuid, ((struct bt_uuid *) ((struct bt_uuid_16[]) {{ .uuid = { BT_UUID_TYPE_16 }, .val = (0x2803), }}))) == 0") /*=0xf14c2*/,((unsigned long)&rodata_f11bc) /*=0xf11bc*/,0x19c); uVar9 = 0x19c; goto LAB_eb7e; }
    iVar3 = attr_find_by_handle((int)piVar2,*(ushort*)(param_2 + 4));
    if (iVar3 == 0) { uVar8 = 0xfffffffd; goto LAB_eaa6; }
    piVar5 = (int*)param_2[3];
    piVar10 = (int*)bt_gatt_dm_attr_chrc_val(iVar3);
    if (piVar10 == 0) { printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)"cur_gatt_chrc != ((void *)0)") /*=0xf1541*/,((unsigned long)&rodata_f11bc) /*=0xf11bc*/,0x1a8); uVar9 = 0x1a8; goto LAB_eb7e; }
    *piVar10 = *piVar5; piVar10[1] = piVar5[1];
    iVar3 = uuid_store(*piVar10); *piVar10 = iVar3;
    if (iVar3 != 0) return 1;
LAB_ec80:
    uVar8 = 0xfffffff4;
LAB_eaa6:
    discovery_complete_error((int)piVar2,uVar8);
    return 0;
  }
  if (bVar1 < 4) {
    if (bVar1 != 2) {
      if (param_2 == 0) { discovery_complete_not_found((int)((unsigned long)&cur_service_val) /*=0x2000a154*/); return 0; }
      piVar10 = (int*)param_2[3];
      iVar3 = attr_store((int)param_2,8);
      frame.primary.zero = 0; frame.primary.uuid = 0x2800;
      iVar4 = bt_uuid_cmp(*param_2,(int)&frame.primary);
      if (iVar4 != 0) {
        frame.fallback.zero = 0; frame.fallback.uuid = 0x2801;
        iVar4 = bt_uuid_cmp(*param_2,(int)&frame.fallback);
        if (iVar4 != 0) { printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)"bt_uuid_cmp(attr->uuid, ((struct bt_uuid *) ((struct bt_uuid_16[]) {{ .uuid = { BT_UUID_TYPE_16 }, .val = (0x2800), }}))) == 0 || bt_uuid_cmp(attr->uuid, ((struct bt_uuid *) ((struct bt_uuid_16[]) {{ .uuid = { BT_UUID_TYPE_16 }, .val = (0x2801), }}))) == 0") /*=0xf12bb*/,((unsigned long)&rodata_f11bc) /*=0xf11bc*/,0x127); uVar9 = 0x127; goto LAB_eb7e; }
      }
      uVar9 = ((unsigned long)&rodata_f13bc) /*=0xf13bc*/;
      if (iVar3 == 0) {
LAB_eb88:
        local_28 = 2; local_24 = uVar9;
        gatt_dm_log_helper(((unsigned long)&rodata_88130) /*=0x88130*/,0x1040,(int)&local_28);
      } else {
        piVar5 = (int*)bt_gatt_dm_attr_service_val(iVar3);
        if (piVar5 == 0) { printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)"cur_service_val != ((void *)0)") /*=0xf13e5*/,((unsigned long)&rodata_f11bc) /*=0xf11bc*/,0x13b); uVar9 = 0x13b; goto LAB_eb7e; }
        *piVar5 = *piVar10; piVar5[1] = piVar10[1];
        iVar4 = uuid_store(*piVar5); *piVar5 = iVar4;
        uVar9 = ((unsigned long)&rodata_f1404) /*=0xf1404*/;
        if (iVar4 == 0) goto LAB_eb88;
        iVar4 = piVar5[1];
        *(short*)((int)piVar2 + 0x16) = (short)iVar4;
        if (*(short*)(iVar3 + 4) == (short)iVar4) goto LAB_ebe6;
        piVar2[2] = 0; *(char*)((int)piVar2 + 0x18) = 5;
        uVar9 = ((unsigned long)&g_gatt_dm_discover_params_uuid) /*=0x2000a15c*/;
        *(short*)((int)piVar2 + 0x10) = *(short*)(iVar3 + 4) + 1;
        uStack_48 = bt_gatt_discover(*piVar2,uVar9);
        if (uStack_48 == 0) return 0;
        LOG_WITH_U32(((unsigned long)&rodata_f1432) /*=0xf1432*/, uStack_48);
      }
      uVar8 = 0xfffffff4; piVar2 = (int*)((unsigned long)&cur_service_val) /*=0x2000a154*/;
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
      LOG_WITH_U32(((unsigned long)&rodata_f1459) /*=0xf1459*/, uVar8);
      goto LAB_eaa6;
    }
    frame.fallback.zero = 0; frame.fallback.uuid = 0x2803;
    iVar3 = bt_uuid_cmp(*param_2,(int)&frame.fallback);
    if (iVar3 == 0) {
      puVar6 = (undefined4*)attr_store((int)param_2,8);
      puVar7 = (undefined4*)bt_gatt_dm_attr_chrc_val((int)puVar6);
      *puVar7 = *puVar6; return 1;
    }
    iVar3 = attr_store((int)param_2,0);
    if (iVar3 != 0) return 1;
    uStack_48 = (uint)*(ushort*)(param_2 + 4);
    LOG_WITH_U32(((unsigned long)&rodata_f1484) /*=0xf1484*/, uStack_48);
    goto LAB_ec80;
  }
  printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)&rodata_f7a30) /*=0xf7a30*/,((unsigned long)&rodata_f11bc) /*=0xf11bc*/,0x1d2);
  printk(((unsigned long)"\tUnknown param type.\n") /*=0xf155e*/);
  uVar9 = 0x1d2;
LAB_eb7e:
  assert_post_action(((unsigned long)&rodata_f11bc) /*=0xf11bc*/,uVar9);
  return 0;
}
#undef local_28
#undef local_24
#undef LOG_WITH_U32
