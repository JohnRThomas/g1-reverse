#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_nvs_fs__param_0135                     [param_0135; library]
 *   local_54         => struct g1_layout_nvs_mount_ate_local__stack_1060        [stack_1060; G1-original]
 * Raw function identity: 0x0004c548.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0004c548 @ 0x0004c548
 * public-name: nvs_mount
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   nvs_mount                                <= FUN_0004c548 @ 0x0004c548
 *   k_mutex_lock                             <= FUN_000723b8 @ 0x000723b8
 *   k_mutex_unlock                           <= FUN_00072558 @ 0x00072558
 *   nvs_sector_advance                       <= FUN_0007e55a @ 0x0007e55a
 *   nvs_log_err                              <= FUN_0007e658 @ 0x0007e658
 *   nvs_al_size                              <= FUN_0007e65e @ 0x0007e65e
 *   nvs_add_gc_done_ate                      <= FUN_0007e80c @ 0x0007e80c
 *   flash_get_page_info_by_offs              <= FUN_00083a92 @ 0x00083a92
 *   kmutex_dlist_init                        <= FUN_000864c2 @ 0x000864c2
 * address symbols (name @ address):
 *   rodata_10000                             @ 0x00010000
 *   rodata_881b8                             @ 0x000881b8
 *   rodata_f0af8                             @ 0x000f0af8   [INLINED -- G6 literal batch]
 *   rodata_f0b1a                             @ 0x000f0b1a   [INLINED -- G6 literal batch]
 *   rodata_f0b37                             @ 0x000f0b37   [INLINED -- G6 literal batch]
 *   rodata_f0b4f                             @ 0x000f0b4f   [INLINED -- G6 literal batch]
 *   rodata_f0b63                             @ 0x000f0b63   [INLINED -- G6 literal batch]
 *   rodata_f0b86                             @ 0x000f0b86   [INLINED -- G6 literal batch]
 *   rodata_f0b9d                             @ 0x000f0b9d   [INLINED -- G6 literal batch]
 *   rodata_f0baf                             @ 0x000f0baf   [INLINED -- G6 literal batch]
 *   rodata_f0bc0                             @ 0x000f0bc0   [INLINED -- G6 literal batch]
 *   rodata_f0be7                             @ 0x000f0be7
 */
/* Reconstructed FUN_0004c548 @ 0x4c548  (parity: 300/300 trials, PROVEN) */

#pragma GCC diagnostic ignored "-Wint-conversion"
#pragma GCC diagnostic ignored "-Wpointer-to-int-cast"
#pragma GCC diagnostic ignored "-Wint-to-pointer-cast"
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
typedef unsigned char undefined; typedef unsigned char undefined1; typedef unsigned char byte;
typedef unsigned short undefined2; typedef unsigned short ushort;
typedef unsigned int undefined4; typedef unsigned int uint; typedef unsigned int uint3;
typedef unsigned long long undefined8; typedef unsigned long long ulonglong;
typedef long long longlong; typedef unsigned long ulong; typedef unsigned char uint1; typedef unsigned short uint2;
typedef signed char sbyte; typedef long long(*code)();
#define bool int
#define false 0
#define true 1

#define CONCAT11(a,b) ((unsigned short)(((unsigned)(unsigned char)(a)<<8)|(unsigned char)(b)))
#define CONCAT21(a,b) (((unsigned)(unsigned short)(a)<<8)|(unsigned char)(b))
#define CONCAT12(a,b) (((unsigned)(unsigned char)(a)<<16)|(unsigned short)(b))
#define CONCAT31(a,b) (((unsigned)(a)<<8)|(unsigned char)(b))
#define CONCAT13(a,b) (((unsigned)(unsigned char)(a)<<24)|((unsigned)(b)&0xffffffu))
#define CONCAT22(a,b) (((unsigned)(unsigned short)(a)<<16)|(unsigned short)(b))
#define CONCAT41(a,b) (((unsigned long long)(unsigned)(a)<<8)|(unsigned char)(b))
#define CONCAT44(a,b) (((unsigned long long)(unsigned)(a)<<32)|(unsigned)(b))
#define CONCAT62(a,b) (((unsigned long long)(a)<<16)|(unsigned short)(b))
#define CONCAT71(a,b) (((unsigned long long)(a)<<8)|(unsigned char)(b))
#define CONCAT53(a,b) (((unsigned long long)(a)<<24)|((unsigned)(b)&0xffffffu))
#define SUB41(x,n) ((unsigned char)((unsigned)(x)>>((n)*8)))
#define SUB42(x,n) ((unsigned short)((unsigned)(x)>>((n)*8)))
#define SUB84(x,n) ((unsigned)((unsigned long long)(x)>>((n)*8)))
#define SUB81(x,n) ((unsigned char)((unsigned long long)(x)>>((n)*8)))
#define SUB82(x,n) ((unsigned short)((unsigned long long)(x)>>((n)*8)))
#define SUB168(x,n) ((unsigned long long)(x))
#define ZEXT14(a) ((unsigned)(unsigned char)(a))
#define ZEXT18(a) ((unsigned long long)(unsigned char)(a))
#define ZEXT24(a) ((unsigned)(unsigned short)(a))
#define ZEXT48(a) ((unsigned long long)(unsigned)(a))
#define ZEXT12(a) ((unsigned short)(unsigned char)(a))
#define SEXT14(a) ((unsigned)(int)(signed char)(a))
#define SEXT18(a) ((unsigned long long)(long long)(signed char)(a))
#define SEXT24(a) ((unsigned)(int)(short)(a))
#define SEXT48(a) ((unsigned long long)(long long)(int)(a))
#define __ROL4(x,n) (((unsigned)(x)<<((n)&31))|((unsigned)(x)>>((32-(n))&31)))
#define __ROR4(x,n) (((unsigned)(x)>>((n)&31))|((unsigned)(x)<<((32-(n))&31)))

extern long long firmware_function_0004c4e4(long long, long long);
extern long long k_mutex_lock(long long, long long, long long, long long);
extern long long k_mutex_unlock(long long);
extern long long firmware_function_0007e53e(long long, long long, long long, long long);
extern long long nvs_sector_advance(long long, long long);
extern long long firmware_function_0007e5da(long long, long long, long long, long long);
extern long long firmware_function_0007e624(long long, ...);
extern long long nvs_log_err(long long, long long, long long);
extern long long nvs_al_size(long long, long long);
extern long long firmware_function_0007e672(long long, long long);
extern long long nvs_add_gc_done_ate(long long);
extern long long firmware_function_0007e83a(long long);
extern long long flash_get_page_info_by_offs(long long, long long, long long);
extern long long kmutex_dlist_init(long long);
#define firmware_data_0004c7a0 ((unsigned long)"Could not obtain flash parameters") /*=0xf0af8*/
#define firmware_data_0004c7a4 ((unsigned long)&rodata_881b8) /*=0x881b8*/
#define firmware_data_0004c7a8 ((unsigned long)"Unsupported write block size") /*=0xf0b1a*/
#define firmware_data_0004c7ac ((unsigned long)"Unable to get page info") /*=0xf0b37*/
#define firmware_data_0004c7b0 ((unsigned long)"Invalid sector size") /*=0xf0b4f*/
#define firmware_data_0004c7b4 ((unsigned long)"Configuration error - sector count") /*=0xf0b63*/
#define firmware_data_0004c7b8 ((unsigned long)"No GC Done marker found: restarting gc") /*=0xf0bc0*/
#define firmware_data_0004c7bc 0xffff0000UL
#define firmware_data_0004c8e0 ((unsigned long)"%d Sectors of %d bytes") /*=0xf0b86*/
#define firmware_data_0004c8e4 ((unsigned long)&rodata_881b8) /*=0x881b8*/
#define firmware_data_0004c8e8 ((unsigned long)"alloc wra: %d, %x") /*=0xf0b9d*/
#define firmware_data_0004c8ec ((unsigned long)"data wra: %d, %x") /*=0xf0baf*/
#define firmware_data_0004c8f0 ((unsigned long)&rodata_f0be7) /*=0xf0be7*/
#define firmware_data_0004c8f4 0xffff0000UL


int nvs_mount(undefined4 *param_1)

{
  char cVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  char *pcVar7;
  uint uVar8;
  undefined4 *puVar9;
  uint uVar10;
  undefined8 uVar11;
  undefined4 local_70;
  undefined4 local_6c;
  uint local_68;
  uint local_64;
  uint local_60;
  char local_5c [2];
  ushort local_5a;
  ushort local_58;
  short local_54 [2];
  short local_50;
  undefined1 auStack_4c [4];
  uint local_48;
  undefined4 local_30;
  undefined4 local_2c;

  puVar9 = param_1 + 5;
  kmutex_dlist_init(puVar9);
  iVar2 = (**(code **)(*(int *)(param_1[10] + 8) + 0xc))();
  param_1[0xb] = iVar2;
  uVar6 = firmware_data_0004c7a0;
  if ((iVar2 == 0) ||
     (piVar3 = (int *)(**(code **)(*(int *)(param_1[10] + 8) + 0xc))(), uVar6 = firmware_data_0004c7a8,
     0x1f < *piVar3 - 1U)) {
control_label_0004c56a:
    local_30 = 2;
    local_2c = uVar6;
    nvs_log_err(firmware_data_0004c7a4,0x1040,&local_30);
    return -0x16;
  }
  uVar11 = flash_get_page_info_by_offs(param_1[10],*param_1,auStack_4c);
  uVar6 = firmware_data_0004c7ac;
  if (((int)uVar11 != 0) ||
     (((local_60 = (uint)*(ushort *)(param_1 + 3), uVar6 = firmware_data_0004c7b0, local_60 == 0 ||
       (local_60 = local_60 - local_48 * (local_60 / local_48), local_60 != 0)) ||
      (uVar6 = firmware_data_0004c7b4, *(ushort *)((int)param_1 + 0xe) < 2)))) goto control_label_0004c56a;
  cVar1 = *(char *)(param_1[0xb] + 4);
  k_mutex_lock(puVar9,(int)((ulonglong)uVar11 >> 0x20),0xffffffff,0xffffffff);
  iVar2 = nvs_al_size(param_1[0xb],8);
  uVar8 = 0;
  for (uVar10 = 0; (uVar10 & 0xffff) < (uint)*(ushort *)((int)param_1 + 0xe); uVar10 = uVar10 + 1) {
    local_60 = uVar10 * ((unsigned long)&rodata_10000) /*=0x10000*/ + ((uint)*(ushort *)(param_1 + 3) - iVar2 & 0xffff);
    iVar4 = firmware_function_0007e5da(param_1,local_60,cVar1,8);
    if (iVar4 != 0) {
      nvs_sector_advance(param_1,&local_60);
      uVar8 = uVar8 + 1 & 0xffff;
      iVar4 = firmware_function_0007e5da(param_1,local_60,cVar1,8);
      if (iVar4 == 0) break;
    }
  }
  if (*(ushort *)((int)param_1 + 0xe) == uVar8) {
    k_mutex_unlock(puVar9);
    return -0x2d;
  }
  if (((uint)*(ushort *)((int)param_1 + 0xe) == (uVar10 & 0xffff)) &&
     (iVar4 = firmware_function_0007e5da(param_1,local_60 - iVar2,cVar1,8), iVar4 == 0)) {
    nvs_sector_advance(param_1,&local_60);
  }
  iVar4 = firmware_function_0004c4e4(param_1,&local_60);
  if (iVar4 == 0) {
    uVar10 = local_60 & 0xffff0000;
    param_1[1] = local_60;
    param_1[2] = uVar10;
    while ((uint)param_1[2] <= (uint)param_1[1]) {
      iVar4 = firmware_function_0007e53e(param_1,param_1[1],local_5c,8);
      if (iVar4 != 0) goto control_label_0004c672;
      iVar4 = 0;
      pcVar7 = local_5c;
      while (cVar1 == *pcVar7) {
        iVar4 = iVar4 + 1;
        pcVar7 = pcVar7 + 1;
        if (iVar4 == 8) goto control_label_0004c6b2;
      }
      iVar4 = firmware_function_0007e672(param_1,local_5c);
      iVar5 = param_1[1];
      if (iVar4 != 0) {
        uVar8 = (uint)local_58;
        param_1[2] = uVar10;
        iVar4 = nvs_al_size(param_1[0xb],local_5a + uVar8);
        param_1[2] = iVar4 + uVar10;
        if ((iVar4 + uVar10 == iVar5) && (uVar8 != 0)) {
          iVar2 = -0x1d;
          goto control_label_0004c8a4;
        }
      }
      param_1[1] = iVar5 - iVar2;
    }
control_label_0004c6b2:
    local_60 = param_1[1] & 0xffff0000;
    nvs_sector_advance(param_1,&local_60);
    iVar4 = firmware_function_0007e5da(param_1,local_60,cVar1,*(undefined2 *)(param_1 + 3));
    if (iVar4 < 0) goto control_label_0004c672;
    uVar10 = param_1[1];
    if (iVar4 == 0) {
      while( true ) {
        uVar10 = param_1[2];
        if ((uint)param_1[1] <= uVar10) break;
        iVar4 = firmware_function_0007e5da(param_1,uVar10,cVar1,param_1[1] - uVar10);
        if (iVar4 < 0) goto control_label_0004c672;
        if (iVar4 == 0) break;
        param_1[2] = param_1[2] + *(int *)param_1[0xb];
      }
      uVar10 = firmware_data_0004c8f4;
      if ((param_1[1] + iVar2 * 2 == (uint)*(ushort *)(param_1 + 3)) &&
         (param_1[2] != (param_1[1] & firmware_data_0004c8f4))) {
        iVar4 = firmware_function_0007e624(param_1);
        if (iVar4 != 0) goto control_label_0004c672;
        param_1[2] = param_1[1] & uVar10;
        goto control_label_0004c814;
      }
    }
    else {
      do {
        uVar10 = iVar2 + uVar10;
        local_60 = uVar10;
        if ((uint)*(ushort *)(param_1 + 3) - iVar2 <= (uVar10 & 0xffff)) {
          local_2c = firmware_data_0004c7b8;
          local_30 = 2;
          nvs_log_err(firmware_data_0004c7a4,0x10c0,&local_30);
          iVar4 = firmware_function_0007e624(param_1,param_1[1]);
          uVar10 = firmware_data_0004c7bc;
          if (iVar4 != 0) goto control_label_0004c672;
          uVar8 = (param_1[1] & firmware_data_0004c7bc) + (uint)*(ushort *)(param_1 + 3) + iVar2 * -2;
          param_1[1] = uVar8;
          param_1[2] = uVar8 & uVar10;
          iVar4 = firmware_function_0007e83a(param_1);
          goto control_label_0004c730;
        }
        iVar4 = firmware_function_0007e53e(param_1,uVar10,local_54,8);
        if (iVar4 != 0) goto control_label_0004c672;
        iVar4 = firmware_function_0007e672(param_1,local_54);
      } while (((iVar4 == 0) || (local_54[0] != -1)) || (local_50 != 0));
      local_2c = firmware_data_0004c8f0;
      local_30 = 2;
      nvs_log_err(firmware_data_0004c8e4,0x10c0,&local_30);
      local_60 = param_1[1] & 0xffff0000;
      nvs_sector_advance(param_1,&local_60);
      iVar4 = firmware_function_0007e624(param_1,local_60);
    }
control_label_0004c730:
    if (iVar4 == 0) {
control_label_0004c814:
      if ((uint)*(ushort *)(param_1 + 1) == (uint)*(ushort *)(param_1 + 3) + iVar2 * -2) {
        iVar2 = nvs_add_gc_done_ate(param_1);
control_label_0004c8a4:
        k_mutex_unlock(puVar9);
        if (iVar2 != 0) {
          return iVar2;
        }
      }
      else {
        k_mutex_unlock(puVar9);
      }
      *(undefined1 *)(param_1 + 4) = 1;
      local_68 = (uint)*(ushort *)((int)param_1 + 0xe);
      local_64 = (uint)*(ushort *)(param_1 + 3);
      local_6c = firmware_data_0004c8e0;
      local_70 = 4;
      nvs_log_err(firmware_data_0004c8e4,0x20c0,&local_70);
      local_6c = firmware_data_0004c8e8;
      local_68 = (uint)param_1[1] >> 0x10;
      local_64 = param_1[1] & 0xffff;
      local_70 = 4;
      nvs_log_err(firmware_data_0004c8e4,0x20c0,&local_70);
      local_70 = 4;
      local_6c = firmware_data_0004c8ec;
      local_68 = (uint)param_1[2] >> 0x10;
      local_64 = param_1[2] & 0xffff;
      nvs_log_err(firmware_data_0004c8e4,0x20c0,&local_70);
      return 0;
    }
  }
control_label_0004c672:
  k_mutex_unlock(puVar9);
  return iVar4;
}
