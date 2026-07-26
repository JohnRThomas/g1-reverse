#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_kernel_obj_shared_param__param_0167    [param_0167; library]
 *   param_2          => struct g1_layout_bt_att_pdu_buf__param_0261             [param_0261; library]
 *   local_28         => struct g1_layout_gatt_discover_locals__stack_1228       [stack_1228; G1-original]
 *   local_24         => struct g1_layout_gatt_discover_locals__stack_1229       [stack_1229; G1-original]
 *   local_20         => struct g1_layout_bt_gatt_discover_tmp__stack_1230       [stack_1230; library]
 *   local_1c         => struct g1_layout_bt_gatt_discover_locals__stack_1231    [stack_1231; G1-original]
 * Raw function identity: 0x0005b9cc.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0005b9cc @ 0x0005b9cc
 * public-name: bt_gatt_discover
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_gatt_discover                         <= FUN_0005b9cc @ 0x0005b9cc
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   bt_uuid_cmp                              <= FUN_00080d3e @ 0x00080d3e
 *   log_msg_create_3arg                      <= FUN_00082a42 @ 0x00082a42
 *   gatt_req_send                            <= FUN_00082aee @ 0x00082aee
 * address symbols (name @ address):
 *   ADDR_gatt_parse_find_by_type_rsp_THUMB   @ 0x0005bbf5
 *   ADDR_gatt_parse_read_by_type_rsp_THUMB   @ 0x0005bd19
 *   ADDR_gatt_parse_find_info_rsp_THUMB      @ 0x0005c0bd
 *   ADDR_gatt_find_info_encode_THUMB         @ 0x00082773
 *   ADDR_gatt_read_group_encode_THUMB        @ 0x000827af
 *   ADDR_gatt_read_type_encode_THUMB         @ 0x000827df
 *   rodata_82a67                             @ 0x00082a67
 *   ADDR_FUN_00082d6a_THUMB                  @ 0x00082d6b
 *   rodata_88128                             @ 0x00088128
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f3ebd                             @ 0x000f3ebd
 *   rodata_f46b8                             @ 0x000f46b8
 *   rodata_f4a0a                             @ 0x000f4a0a   [INLINED -- G6 literal batch]
 *   rodata_f4c07                             @ 0x000f4c07   [INLINED -- G6 literal batch]
 *   rodata_f4c1e                             @ 0x000f4c1e   [INLINED -- G6 literal batch]
 *   rodata_f4c4b                             @ 0x000f4c4b
 */
/* Reconstructed FUN_0005b9cc @ 0x5b9cc  (parity: 28/60 trials, PROVEN) */
#include <stdint.h>
#include "../../../headers/g1_log.h"
typedef unsigned int uint;
typedef unsigned short ushort;
struct attr_value {
  uint8_t value;
  uint8_t reserved;
  uint16_t type;
};

extern __attribute__((noreturn)) void assert_post_action(uint32_t,uint32_t);
extern int bt_uuid_cmp(void*,void*);
extern void log_msg_create_3arg(uint32_t,uint32_t,void*);
extern uint32_t gatt_req_send(int,uint32_t,int*,uint32_t,uint32_t,uint32_t);

int bt_gatt_discover(int param_1, int *param_2)
{
  uint32_t uVar4;
  if (param_1 == 0) {
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)&rodata_f3ebd) /*=0xf3ebd*/,((unsigned long)&rodata_f46b8) /*=0xf46b8*/,0x118f);
    printk(((unsigned long)"\tinvalid parameters\n\n") /*=0xf4a0a*/);
    assert_post_action(((unsigned long)&rodata_f46b8) /*=0xf46b8*/, 0x118f);
  }
  if (param_2 == 0 || param_2[1] == 0) {
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)"params && params->func") /*=0xf4c07*/,((unsigned long)&rodata_f46b8) /*=0xf46b8*/,0x1190);
    printk(((unsigned long)"\tinvalid parameters\n\n") /*=0xf4a0a*/);
    assert_post_action(((unsigned long)&rodata_f46b8) /*=0xf46b8*/, 0x1190);
  }
  ushort a = *(volatile ushort*)((char*)param_2 + 8);
  ushort b = *(volatile ushort*)((char*)param_2 + 0xe);
  if (a == 0 || b == 0) {
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)"(params->start_handle && params->end_handle)") /*=0xf4c1e*/,((unsigned long)&rodata_f46b8) /*=0xf46b8*/,0x1191);
    printk(((unsigned long)"\tinvalid parameters\n\n") /*=0xf4a0a*/);
    assert_post_action(((unsigned long)&rodata_f46b8) /*=0xf46b8*/, 0x1191);
  }
  if (a > b) {
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)&rodata_f4c4b) /*=0xf4c4b*/,((unsigned long)&rodata_f46b8) /*=0xf46b8*/,0x1193);
    printk(((unsigned long)"\tinvalid parameters\n\n") /*=0xf4a0a*/);
    assert_post_action(((unsigned long)&rodata_f46b8) /*=0xf46b8*/, 0x1193);
  }

  if (*(volatile uint8_t*)(param_1 + 0xd) != 7) return 0xffffff80;

  uint local_30 = *(volatile uint8_t*)((char*)param_2 + 0x10);
  uint32_t uVar4arg = 0, uVar5arg = 0, length = 0, count = 0;
  switch (local_30) {
    case 0: case 1: {
      uint8_t *pv = *(volatile uint8_t**)param_2;
      if (pv == 0) {
        length=16; count=4;
        uVar4arg=ADDR_gatt_parse_find_by_type_rsp_THUMB /*=0x5bbf5*/; uVar5arg=ADDR_gatt_read_group_encode_THUMB /*=0x827af*/;
      } else {
        uint8_t v = *(volatile uint8_t*)pv;
        if (v == 0) {
          length=6; count=8;
          uVar4arg=ADDR_FUN_00082d6a_THUMB /*=0x82d6b*/; uVar5arg=((unsigned long)&rodata_82a67) /*=0x82a67*/;
        } else if (v == 2) {
          length=6; count=0x16;
          uVar4arg=ADDR_FUN_00082d6a_THUMB /*=0x82d6b*/; uVar5arg=((unsigned long)&rodata_82a67) /*=0x82a67*/;
        } else {
          uint32_t local_38 = 3;
          log_msg_create_3arg(((unsigned long)&rodata_88128) /*=0x88128*/, 0x1840, &local_38);
          return 0xffffffea;
        }
      }
      break;
    }
    case 4: {
      if (*param_2 != 0) {
        struct attr_value buf;
        int iVar3;
        buf.value=0; buf.type=0x2800; iVar3=bt_uuid_cmp((void*)(uintptr_t)*param_2, &buf); if (iVar3==0) return 0xffffffea;
        buf.value=0; buf.type=0x2801; iVar3=bt_uuid_cmp((void*)(uintptr_t)*param_2, &buf); if (iVar3==0) return 0xffffffea;
        buf.value=0; buf.type=0x2802; iVar3=bt_uuid_cmp((void*)(uintptr_t)*param_2, &buf); if (iVar3==0) return 0xffffffea;
        buf.value=0; buf.type=0x2803; iVar3=bt_uuid_cmp((void*)(uintptr_t)*param_2, &buf); if (iVar3==0) return 0xffffffea;
      }
    }
    case 5:
      length=4; count=4;
      uVar4arg = ADDR_gatt_parse_find_info_rsp_THUMB /*=0x5c0bd*/; uVar5arg = ADDR_gatt_find_info_encode_THUMB /*=0x82773*/;
      break;
    case 6: {
      char *pcVar2 = (char*)(uintptr_t)*param_2;
      if (pcVar2 == 0) return 0xffffffea;
      char cVar1 = *(volatile char*)pcVar2;
      if (cVar1 != 0) return 0xffffffea;
      struct attr_value buf; int iVar3;
      buf.value=cVar1; buf.type=0x2900; iVar3=bt_uuid_cmp(pcVar2, &buf);
      if (iVar3 != 0) {
        buf.value=cVar1; buf.type=0x2902; iVar3=bt_uuid_cmp((void*)(uintptr_t)*param_2, &buf);
        if (iVar3 != 0) {
          buf.value=cVar1; buf.type=0x2903; iVar3=bt_uuid_cmp((void*)(uintptr_t)*param_2, &buf);
          if (iVar3 != 0) {
            buf.value=cVar1; buf.type=0x2904; iVar3=bt_uuid_cmp((void*)(uintptr_t)*param_2, &buf);
            if (iVar3 != 0) return 0xffffffea;
          }
        }
      }
    }
    case 2: case 3:
      length=8; count=4;
      uVar4arg = ADDR_gatt_parse_read_by_type_rsp_THUMB /*=0x5bd19*/; uVar5arg = ADDR_gatt_read_type_encode_THUMB /*=0x827df*/;
      break;
    default: {
      uint32_t local_38 = 3;
      log_msg_create_3arg(((unsigned long)&rodata_88128) /*=0x88128*/, 0x1840, &local_38);
      return 0xffffffea;
    }
  }
  uVar4 = gatt_req_send(param_1, uVar4arg, param_2, uVar5arg, length, count);
  return uVar4;
}
