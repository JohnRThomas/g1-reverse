#include "g1_app_symbols.h"
/* named: parse_whitelist_json */
/* globals referenced:
//   0x20007554  g_log_use_alt_sink           
//   0x2001a22c  g_app_whitelist_buffer       
*/
/* Reconstructed parse_whitelist_json @ 0x34dbc  (parity: 300/300 trials, PROVEN) */
typedef unsigned int undefined4;
typedef unsigned char byte;
typedef unsigned int uint;

extern void DEBUG_PRINT(undefined4 fmt, ...);
extern void debug_print(void);
extern void cjson_delete(int a);
extern int FUN_0008500c(void);
extern unsigned int sllist_count_nodes(int a);
extern int sllist_node_at_index(int a);
extern int sllist_find_by_name_ci(int a, ...);
extern int FUN_000850c8(void);
extern void memset_bytes(void *dst, int val, int n);
extern void strncpy_zero_pad(void *dst, void *src, int n);

undefined4 parse_whitelist_json(undefined4 param_1,undefined4 param_2,undefined4 param_3)
{
  volatile byte *pbVar2;
  byte bVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar9;
  uint uVar10;
  volatile byte *pbVar11;
  uint uVar12;
  byte bVar13;
  int bVar14;

  iVar5 = FUN_0008500c();
  pbVar2 = (volatile byte *)(g_app_whitelist_buffer) /*=0x2001a22c*/;
  if (iVar5 == 0) {
    if (*(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
      DEBUG_PRINT(0,param_1);
    } else {
      debug_print();
    }
    return 0;
  }
  memset_bytes((void*)pbVar2,0,0x15e2);
  iVar6 = sllist_find_by_name_ci(iVar5,0);
  if (iVar6 == 0) {
    iVar6 = *(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
    goto tail;
  }
  bVar14 = *(int *)(iVar6 + 0xc) == 2;
  bVar4 = (byte)((*pbVar2 & 0xfe) | (byte)bVar14);
  *pbVar2 = bVar4;
  iVar6 = sllist_find_by_name_ci(iVar5,0,bVar4,bVar14,param_1,param_2,param_3);
  if (iVar6 == 0) {
    iVar6 = *(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
    goto tail;
  }
  uVar12 = (uint)(*(int *)(iVar6 + 0xc) == 2);
  uVar10 = (uint)((*pbVar2 & 0xfffffffd) | (uVar12 << 1));
  *pbVar2 = (byte)uVar10;
  iVar6 = sllist_find_by_name_ci(iVar5,0,uVar10,uVar12,param_1,param_2,param_3);
  if (iVar6 == 0) {
    iVar6 = *(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
    goto tail;
  }
  *pbVar2 = (byte)((*pbVar2 & 0xf7) | (byte)((*(int *)(iVar6 + 0xc) == 2) << 3));
  iVar6 = sllist_find_by_name_ci(iVar5,0);
  if (iVar6 == 0) {
    iVar6 = *(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
    goto tail;
  }
  *pbVar2 = (byte)((*pbVar2 & 0xfb) | (byte)((*(int *)(iVar6 + 0xc) == 2) << 2));
  iVar6 = sllist_find_by_name_ci(iVar5,0);
  if (iVar6 == 0) {
    iVar6 = *(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
    goto tail;
  }
  iVar7 = sllist_find_by_name_ci(iVar6,0);
  if (iVar7 == 0) {
    iVar6 = *(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
    goto tail;
  }
  *pbVar2 = (byte)((*pbVar2 & 0xef) | (byte)((*(int *)(iVar7 + 0xc) == 2) << 4));
  iVar6 = sllist_find_by_name_ci(iVar6,0);
  if (iVar6 == 0) {
    iVar6 = *(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
    goto tail;
  }
  iVar7 = FUN_000850c8();
  if (iVar7 != 0) {
    bVar4 = (byte)(sllist_count_nodes(iVar6) & 0xffu);
    bVar13 = 0;
    if (99 < bVar4) {
      bVar4 = 100;
    }
    uVar12 = 0;
    pbVar2[1] = bVar4;
    for (; bVar13 < pbVar2[1]; bVar13 = bVar13 + 1) {
      iVar7 = sllist_node_at_index(iVar6);
      if (iVar7 == 0) {
        iVar7 = *(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
        if (iVar7 == 0) {
          DEBUG_PRINT(0);
        } else {
          debug_print();
        }
        continue;
      }
      iVar9 = sllist_find_by_name_ci(iVar7,0);
      if (iVar9 == 0) {
        iVar7 = *(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
        if (iVar7 == 0) {
          DEBUG_PRINT(0);
        } else {
          debug_print();
        }
        continue;
      }
      iVar7 = sllist_find_by_name_ci(iVar7,0);
      if (iVar7 == 0) {
        iVar7 = *(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
        if (iVar7 == 0) {
          DEBUG_PRINT(0);
        } else {
          debug_print();
        }
        continue;
      }
      pbVar11 = pbVar2 + uVar12 * 0x38 + 2;
      memset_bytes((void*)pbVar11,0,0x28);
      memset_bytes((void*)(pbVar2 + uVar12 * 0x38 + 0x2a),0,0x10);
      strncpy_zero_pad((void*)pbVar11,*(void **)(iVar9 + 0x10),0x27);
      strncpy_zero_pad((void*)(pbVar2 + uVar12 * 0x38 + 0x2a),*(void **)(iVar7 + 0x10),0xf);
      uVar12 = (uVar12 + 1) & 0xff;
    }
  }
  cjson_delete(iVar5);
  return 1;

tail:
  if (iVar6 == 0) {
    DEBUG_PRINT(0);
  } else {
    debug_print();
  }
  cjson_delete(iVar5);
  return 0;
}

