#include "g1_app_symbols.h"
/* named: bt_gatt_discover */
/* Reconstructed bt_gatt_discover @ 0x5b9cc  (parity: 28/60 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int uint;
typedef unsigned short ushort;

extern void assert_post_action(uint32_t,uint32_t);
extern void printk(uint32_t,uint32_t,uint32_t,uint32_t);
extern int bt_uuid_cmp(void*,void*);
extern void FUN_00082a42(uint32_t,uint32_t,void*);
extern uint32_t gatt_req_send(int,uint32_t,int*,uint32_t);

int bt_gatt_discover(int param_1, int *param_2)
{
  uint32_t uVar4;
  if (param_1 == 0) {
    printk("conn" /*=0xf3ebd*/,"WEST_TOPDIR/zephyr/subsys/bluetooth/host/gatt.c" /*=0xf46b8*/,"ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,0x118f);
    for (;;) { assert_post_action("WEST_TOPDIR/zephyr/subsys/bluetooth/host/gatt.c" /*=0xf46b8*/, 0x118f); printk("\tinvalid parameters\n\n" /*=0xf4a0a*/,0,0,0); }
  }
  if (param_2 == 0 || param_2[1] == 0) {
    printk("params && params->func" /*=0xf4c07*/,"WEST_TOPDIR/zephyr/subsys/bluetooth/host/gatt.c" /*=0xf46b8*/,"ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,0x1190);
    for (;;) { assert_post_action("WEST_TOPDIR/zephyr/subsys/bluetooth/host/gatt.c" /*=0xf46b8*/, 0x1190); printk("\tinvalid parameters\n\n" /*=0xf4a0a*/,0,0,0); }
  }
  ushort a = *(volatile ushort*)((char*)param_2 + 8);
  ushort b = *(volatile ushort*)((char*)param_2 + 0xe);
  if (a == 0 || b == 0) {
    printk("(params->start_handle && params->end_handle)" /*=0xf4c1e*/,"WEST_TOPDIR/zephyr/subsys/bluetooth/host/gatt.c" /*=0xf46b8*/,"ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,0x1191);
    for (;;) { assert_post_action("WEST_TOPDIR/zephyr/subsys/bluetooth/host/gatt.c" /*=0xf46b8*/, 0x1191); printk("\tinvalid parameters\n\n" /*=0xf4a0a*/,0,0,0); }
  }
  if (a > b) {
    printk("(params->start_handle <= params->end_handle)" /*=0xf4c4b*/,"WEST_TOPDIR/zephyr/subsys/bluetooth/host/gatt.c" /*=0xf46b8*/,"ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,0x1193);
    for (;;) { assert_post_action("WEST_TOPDIR/zephyr/subsys/bluetooth/host/gatt.c" /*=0xf46b8*/, 0x1193); printk("\tinvalid parameters\n\n" /*=0xf4a0a*/,0,0,0); }
  }

  if (*(volatile uint8_t*)(param_1 + 0xd) != 7) return 0xffffff80;

  uint local_30 = *(volatile uint8_t*)((char*)param_2 + 0x10);
  uint32_t uVar4arg = 0, uVar5arg = 0;
  switch (local_30) {
    case 0: case 1: {
      uint8_t *pv = *(volatile uint8_t**)param_2;
      if (pv == 0) {
        uVar4arg=((uintptr_t)&tbl_8275f) /*=0x827af*/; uVar5arg=4;
      } else {
        uint8_t v = *(volatile uint8_t*)pv;
        if (v == 0) {
          uVar4arg=((uintptr_t)&rodata_82d6b) /*=0x82d6b*/; uVar5arg=((uintptr_t)&rodata_82a67) /*=0x82a67*/;
        } else if (v == 2) {
          uVar4arg=((uintptr_t)&rodata_82d6b) /*=0x82d6b*/; uVar5arg=((uintptr_t)&rodata_82a67) /*=0x82a67*/;
        } else {
          uint32_t local_38 = 3;
          FUN_00082a42(((uintptr_t)&tbl_880d8) /*=0x88128*/, 0x1840, &local_38);
          return 0xffffffea;
        }
      }
      break;
    }
    case 4: {
      if (*param_2 != 0) {
        uint8_t buf[4];
        int iVar3;
        buf[0]=0; iVar3=bt_uuid_cmp((void*)(uintptr_t)*param_2, buf); if (iVar3==0) return 0xffffffea;
        buf[0]=0; iVar3=bt_uuid_cmp((void*)(uintptr_t)*param_2, buf); if (iVar3==0) return 0xffffffea;
        buf[0]=0; iVar3=bt_uuid_cmp((void*)(uintptr_t)*param_2, buf); if (iVar3==0) return 0xffffffea;
        buf[0]=0; iVar3=bt_uuid_cmp((void*)(uintptr_t)*param_2, buf); if (iVar3==0) return 0xffffffea;
      }
    }
    case 5:
      uVar4arg = ((uintptr_t)&tbl_5c0b4) /*=0x5c0bd*/; uVar5arg = ((uintptr_t)&tbl_8275f) /*=0x82773*/;
      break;
    case 6: {
      char *pcVar2 = (char*)(uintptr_t)*param_2;
      if (pcVar2 == 0) return 0xffffffea;
      char cVar1 = *(volatile char*)pcVar2;
      if (cVar1 != 0) return 0xffffffea;
      uint8_t buf[4]; int iVar3;
      buf[0]=cVar1; iVar3=bt_uuid_cmp(pcVar2, buf);
      if (iVar3 != 0) {
        buf[0]=cVar1; iVar3=bt_uuid_cmp((void*)(uintptr_t)*param_2, buf);
        if (iVar3 != 0) {
          buf[0]=cVar1; iVar3=bt_uuid_cmp((void*)(uintptr_t)*param_2, buf);
          if (iVar3 != 0) {
            buf[0]=cVar1; iVar3=bt_uuid_cmp((void*)(uintptr_t)*param_2, buf);
            if (iVar3 == 0) return 0xffffffea;
          }
        }
      }
    }
    case 2: case 3:
      uVar4arg = ((uintptr_t)&tbl_5bd10) /*=0x5bd19*/; uVar5arg = ((uintptr_t)&tbl_8275f) /*=0x827df*/;
      break;
    default: {
      uint32_t local_38 = 3;
      FUN_00082a42(((uintptr_t)&tbl_880d8) /*=0x88128*/, 0x1840, &local_38);
      return 0xffffffea;
    }
  }
  uVar4 = gatt_req_send(param_1, uVar4arg, param_2, uVar5arg);
  return uVar4;
}

