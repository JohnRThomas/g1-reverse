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
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f3ebd                             @ 0x000f3ebd
 *   rodata_f46b8                             @ 0x000f46b8
 *   rodata_f4a0a                             @ 0x000f4a0a
 *   rodata_f4c07                             @ 0x000f4c07
 *   rodata_f4c1e                             @ 0x000f4c1e
 *   rodata_f4c4b                             @ 0x000f4c4b
 */
/* Reconstructed FUN_0005b9cc @ 0x5b9cc  (parity: 28/60 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int uint;
typedef unsigned short ushort;
struct attr_value {
  uint8_t value;
  uint8_t reserved;
  uint16_t type;
};

extern __attribute__((noreturn)) void assert_post_action(uint32_t,uint32_t);
extern void printk(uint32_t,...);
extern int bt_uuid_cmp(void*,void*);
extern void log_msg_create_3arg(uint32_t,uint32_t,void*);
extern uint32_t gatt_req_send(int,uint32_t,int*,uint32_t,uint32_t,uint32_t);

int bt_gatt_discover(int param_1, int *param_2)
{
  uint32_t uVar4;
  if (param_1 == 0) {
    printk(0x00099cbdUL,0x000f3ebdUL,0x000f46b8UL,0x118f);
    printk(0x000f4a0aUL);
    assert_post_action(0x000f46b8UL, 0x118f);
  }
  if (param_2 == 0 || param_2[1] == 0) {
    printk(0x00099cbdUL,0x000f4c07UL,0x000f46b8UL,0x1190);
    printk(0x000f4a0aUL);
    assert_post_action(0x000f46b8UL, 0x1190);
  }
  ushort a = *(volatile ushort*)((char*)param_2 + 8);
  ushort b = *(volatile ushort*)((char*)param_2 + 0xe);
  if (a == 0 || b == 0) {
    printk(0x00099cbdUL,0x000f4c1eUL,0x000f46b8UL,0x1191);
    printk(0x000f4a0aUL);
    assert_post_action(0x000f46b8UL, 0x1191);
  }
  if (a > b) {
    printk(0x00099cbdUL,0x000f4c4bUL,0x000f46b8UL,0x1193);
    printk(0x000f4a0aUL);
    assert_post_action(0x000f46b8UL, 0x1193);
  }

  if (*(volatile uint8_t*)(param_1 + 0xd) != 7) return 0xffffff80;

  uint local_30 = *(volatile uint8_t*)((char*)param_2 + 0x10);
  uint32_t uVar4arg = 0, uVar5arg = 0, length = 0, count = 0;
  switch (local_30) {
    case 0: case 1: {
      uint8_t *pv = *(volatile uint8_t**)param_2;
      if (pv == 0) {
        length=16; count=4;
        uVar4arg=0x0005bbf5UL; uVar5arg=0x000827afUL;
      } else {
        uint8_t v = *(volatile uint8_t*)pv;
        if (v == 0) {
          length=6; count=8;
          uVar4arg=0x00082d6bUL; uVar5arg=0x00082a67UL;
        } else if (v == 2) {
          length=6; count=0x16;
          uVar4arg=0x00082d6bUL; uVar5arg=0x00082a67UL;
        } else {
          uint32_t local_38 = 3;
          log_msg_create_3arg(0x00088128UL, 0x1840, &local_38);
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
      uVar4arg = 0x0005c0bdUL; uVar5arg = 0x00082773UL;
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
      uVar4arg = 0x0005bd19UL; uVar5arg = 0x000827dfUL;
      break;
    default: {
      uint32_t local_38 = 3;
      log_msg_create_3arg(0x00088128UL, 0x1840, &local_38);
      return 0xffffffea;
    }
  }
  uVar4 = gatt_req_send(param_1, uVar4arg, param_2, uVar5arg, length, count);
  return uVar4;
}
