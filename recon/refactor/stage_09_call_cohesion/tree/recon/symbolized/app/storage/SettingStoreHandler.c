#include "g1_app_symbols.h"
#include "../../../headers/g1_dedupe.h"
/* readable reconstruction; identity: FUN_00023f04 @ 0x00023f04
 * public-name: SettingStoreHandler
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   k_msgq_get                               <= FUN_00072240 @ 0x00072240
 *   z_device_is_ready                        <= FUN_0008638c @ 0x0008638c
 * address symbols (name @ address):
 *   rodata_243dc                             @ 0x000243dc
 *   rodata_243e0                             @ 0x000243e0
 *   rodata_243e4                             @ 0x000243e4
 *   rodata_243e8                             @ 0x000243e8
 *   rodata_243ec                             @ 0x000243ec
 *   rodata_243f0                             @ 0x000243f0
 *   rodata_243f4                             @ 0x000243f4
 *   rodata_243f8                             @ 0x000243f8
 *   rodata_87bf0                             @ 0x00087bf0
 *   rodata_9e9ea                             @ 0x0009e9ea
 *   rodata_9ea0a                             @ 0x0009ea0a
 *   rodata_9ea7b                             @ 0x0009ea7b   [INLINED -- G6 literal batch]
 *   rodata_9ead2                             @ 0x0009ead2   [INLINED -- G6 literal batch]
 *   rodata_9eaf4                             @ 0x0009eaf4   [INLINED -- G6 literal batch]
 *   rodata_9eb2e                             @ 0x0009eb2e   [INLINED -- G6 literal batch]
 *   rodata_9eba7                             @ 0x0009eba7
 *   rodata_9ebc6                             @ 0x0009ebc6
 *   rodata_9ecd5                             @ 0x0009ecd5   [INLINED -- G6 literal batch]
 *   rodata_9ecf5                             @ 0x0009ecf5   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_flash_store_cmd_msgq                   @ 0x20003994
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_ui_mode_flag                           @ 0x20018462
 */
/* Reconstructed SettingStoreHandler @ 0x23f04  (parity: 30/30 trials, PROVEN) */
#pragma GCC diagnostic ignored "-Wint-conversion"
#pragma GCC diagnostic ignored "-Wpointer-to-int-cast"
#pragma GCC diagnostic ignored "-Wint-to-pointer-cast"
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
typedef unsigned char undefined,undefined1,byte,uchar,uint1;
typedef unsigned short undefined2,ushort,uint2,wchar_t;
typedef unsigned int undefined4,uint,uint3,code_t;
typedef unsigned long long undefined8,ulonglong;
typedef long long longlong; typedef unsigned long ulong; typedef signed char sbyte;
typedef unsigned int(*code)(unsigned int,unsigned int,unsigned int,unsigned int);
typedef unsigned int(*code3)(unsigned int,unsigned int,unsigned int);
#define bool int
#define false 0
#define true 1
#define NAN(x) __builtin_isnan((double)(x))
#define ABS(x) __builtin_fabs((double)(x))
#define SQRT(x) __builtin_sqrt((double)(x))
#define FPMaxNum(a,b) __builtin_fmaxf((a),(b))
#define FPMinNum(a,b) __builtin_fminf((a),(b))
#define FPMax(a,b) __builtin_fmaxf((a),(b))
#define FPMin(a,b) __builtin_fminf((a),(b))
#include "../../../headers/g1_ghidra_ops.h"
#include "../../../headers/g1_log.h"

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
#define CONCAT61(a,b) (((unsigned long long)(a)<<8)|(unsigned char)(b))
#define SUB41(x,n) ((unsigned char)((unsigned)(x)>>((n)*8)))
#define SUB42(x,n) ((unsigned short)((unsigned)(x)>>((n)*8)))
#define SUB84(x,n) ((unsigned)((unsigned long long)(x)>>((n)*8)))
#define SUB81(x,n) ((unsigned char)((unsigned long long)(x)>>((n)*8)))
#define SUB82(x,n) ((unsigned short)((unsigned long long)(x)>>((n)*8)))
#define SUB83(x,n) ((unsigned)(((unsigned long long)(x)>>((n)*8))&0xffffffu))
#define SUB168(x,n) ((unsigned long long)(x))
#define ZEXT14(a) ((unsigned)(unsigned char)(a))
#define ZEXT18(a) ((unsigned long long)(unsigned char)(a))
#define ZEXT24(a) ((unsigned)(unsigned short)(a))
#define ZEXT28(a) ((unsigned long long)(unsigned short)(a))
#define ZEXT48(a) ((unsigned long long)(unsigned)(a))
#define ZEXT12(a) ((unsigned short)(unsigned char)(a))
#define ZEXT816(a) ((unsigned long long)(a))
#define SEXT14(a) ((unsigned)(int)(signed char)(a))
#define SEXT18(a) ((unsigned long long)(long long)(signed char)(a))
#define SEXT24(a) ((unsigned)(int)(short)(a))
#define SEXT48(a) ((unsigned long long)(long long)(int)(a))
#define __ROL4(x,n) (((unsigned)(x)<<((n)&31))|((unsigned)(x)>>((32-((n)&31))&31)))
#define __ROR4(x,n) (((unsigned)(x)>>((n)&31))|((unsigned)(x)<<((32-((n)&31))&31)))
#define __ROL1(x,n) ((unsigned char)(((unsigned)(unsigned char)(x)<<((n)&7))|((unsigned)(unsigned char)(x)>>((8-((n)&7))&7))))

extern int get_device_info(void);
extern int k_msgq_get(unsigned int,void*,unsigned int,unsigned int);
extern int z_device_is_ready(int);
#define DAT_0002418c ((unsigned long)&g_flash_store_cmd_msgq) /*=0x20003994*/
#define DAT_00024190 ((volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/)
#define DAT_00024194 ((volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)
#define DAT_00024198 ((unsigned long)"getSettingStorageQueueCacheData") /*=0x9ecd5*/
#define DAT_0002419c ((unsigned long)"%s(): setting storage queue get failed\r\n\n") /*=0x9ea7b*/
#define DAT_000241a0 ((unsigned long)"SettingStoreHandler") /*=0x9ecf5*/
#define DAT_000241a4 0x9eaa5UL
#define DAT_000241a8 ((unsigned long)"%s(): received setting command .\n") /*=0x9ead2*/
#define DAT_000241ac ((unsigned long)"%s(): start setting  parameter check. language type = %d\n") /*=0x9eaf4*/
#define DAT_000241b0 ((unsigned long)"%s(): Setting Task received error language parameters.\n") /*=0x9eb2e*/
#define DAT_000241b4 ((unsigned long)&g_ui_mode_flag) /*=0x20018462*/
#define DAT_000241b8 0x9eb66UL
#define DAT_000241bc ((unsigned long)&rodata_87bf0) /*=0x87bf0*/
#define DAT_000241c0 ((unsigned long)&rodata_9e9ea) /*=0x9e9ea*/
#define DAT_000241c4 ((unsigned long)&rodata_9eba7) /*=0x9eba7*/
#define DAT_000241c8 ((unsigned long)&rodata_9ebc6) /*=0x9ebc6*/
#define DAT_000241cc 0x9ebe5UL
#define DAT_000241d0 ((unsigned long)&rodata_9ea0a) /*=0x9ea0a*/
#define DAT_000243dc (*(volatile int**)((unsigned long)&rodata_243dc) /*=0x243dc*/)
#define DAT_000243e0 (*(volatile int *)((unsigned long)&rodata_243e0) /*=0x243e0*/)
#define DAT_000243e4 (*(volatile int *)((unsigned long)&rodata_243e4) /*=0x243e4*/)
#define DAT_000243e8 (*(volatile int *)((unsigned long)&rodata_243e8) /*=0x243e8*/)
#define DAT_000243ec (*(volatile int *)((unsigned long)&rodata_243ec) /*=0x243ec*/)
#define DAT_000243f0 (*(volatile int *)((unsigned long)&rodata_243f0) /*=0x243f0*/)
#define DAT_000243f4 (*(volatile int *)((unsigned long)&rodata_243f4) /*=0x243f4*/)
#define DAT_000243f8 (*(volatile int *)((unsigned long)&rodata_243f8) /*=0x243f8*/)


uint SettingStoreHandler(void)

{
  int *piVar1;
  int *piVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  undefined4 *puVar10;
  code *pcVar11;
  bool bVar12;
  bool bVar13;
  undefined2 local_24;
  byte local_22;
  undefined1 local_20 [5];

  iVar4 = k_msgq_get(DAT_0002418c,local_20,0,0);
  piVar2 = DAT_00024194;
  piVar1 = DAT_00024190;
  if (iVar4 == 0) {
    if (2 < *DAT_00024190) {
      G1_LOG_ROUTE(*DAT_00024194 == 0, DAT_000241a8,DAT_000241a0);
    }
    puVar3 = DAT_000243f4;
    puVar10 = DAT_000241bc;
    uVar8 = 0;
    switch(local_20[0]) {
    case 1:
      uVar8 = (uint)local_20[4];
      if (2 < *piVar1) {
        G1_LOG_ROUTE(*DAT_00024194 == 0, DAT_000241ac,DAT_000241a0,uVar8);
      }
      puVar10 = DAT_000241bc;
      iVar4 = DAT_000241b4;
      if (uVar8 - 1 < 0x12) {
        if (*(byte *)(DAT_000241b4 + 1) == uVar8) {
          iVar7 = *piVar1;
          bVar13 = SBORROW4(iVar7,2);
          iVar4 = iVar7 + -2;
          bVar12 = iVar7 == 2;
          goto LAB_00023fc4;
        }
        iVar7 = z_device_is_ready(DAT_000241bc);
        if (iVar7 != 0) {
          local_24 = 0;
          local_22 = 0;
          iVar7 = get_device_info();
          pcVar11 = *(code **)(iVar7 + 0x1030);
          uVar6 = get_device_info();
          iVar7 = (*pcVar11)(uVar6,0x13e000,&local_24,3);
          if (iVar7 == 0) {
            local_24 = CONCAT11(local_20[4],0xaa);
            iVar7 = get_device_info();
            pcVar11 = *(code **)(iVar7 + 0x1038);
            uVar6 = get_device_info();
            uVar8 = ((code3)pcVar11)(uVar6,0x13e000,0x1000);
            if (uVar8 != 0) goto LAB_00024044;
            iVar7 = get_device_info();
            pcVar11 = *(code **)(iVar7 + 0x1034);
            uVar6 = get_device_info();
            uVar8 = (*pcVar11)(uVar6,0x13e000,&local_24,3);
            if (uVar8 != 0) goto LAB_00024074;
            local_24 = 0;
            local_22 = 0;
            iVar7 = get_device_info();
            pcVar11 = *(code **)(iVar7 + 0x1030);
            uVar6 = get_device_info();
            iVar7 = (*pcVar11)(uVar6,0x13e000,&local_24,3);
            if (iVar7 == 0) {
              *(undefined1 *)(iVar4 + 1) = ((unsigned long long)(local_24)>>8 & 0xffULL);
              uVar9 = 0;
              if (*piVar1 < 3) {
                return 0;
              }
              uVar8 = (uint)*(byte *)(iVar4 + 1);
              iVar4 = *DAT_00024194;
              uVar6 = DAT_000241cc;
              uVar5 = DAT_000241a0;
              goto LAB_000240c6;
            }
          }
          goto LAB_0002401a;
        }
LAB_00023fda:
        if (*piVar1 < 1) break;
        uVar6 = *puVar10;
LAB_00023fe2:
        iVar4 = *DAT_00024194;
        uVar5 = DAT_000241c0;
        goto LAB_00023fea;
      }
      if (0 < *piVar1) {
        iVar4 = *DAT_00024194;
        uVar6 = DAT_000241b0;
        uVar5 = DAT_000241a0;
        goto LAB_00023f56;
      }
      break;
    case 2:
      iVar4 = z_device_is_ready(DAT_000241bc);
      if (iVar4 != 0) {
        local_24 = 0;
        local_22 = 0;
        iVar4 = get_device_info();
        pcVar11 = *(code **)(iVar4 + 0x1030);
        uVar6 = get_device_info();
        iVar4 = (*pcVar11)(uVar6,0x13e000,&local_24,3);
        if (iVar4 == 0) {
          local_24 = 0x2aa;
          iVar4 = get_device_info();
          pcVar11 = *(code **)(iVar4 + 0x1038);
          uVar6 = get_device_info();
          uVar8 = ((code3)pcVar11)(uVar6,0x13e000,0x1000);
          if (uVar8 != 0) {
LAB_00024044:
            if (*piVar1 < 3) {
              return uVar8;
            }
            iVar4 = *DAT_00024194;
            uVar6 = DAT_000241c4;
            uVar5 = DAT_000241a0;
            uVar9 = uVar8;
LAB_000240c6:
            if (iVar4 != 0) {
              debug_print(uVar6,uVar5,uVar8);
              return uVar9;
            }
            log_message(uVar6,uVar5,uVar8);
            return uVar9;
          }
          iVar4 = get_device_info();
          pcVar11 = *(code **)(iVar4 + 0x1034);
          uVar6 = get_device_info();
          uVar8 = (*pcVar11)(uVar6,0x13e000,&local_24,3);
          if (uVar8 != 0) {
LAB_00024074:
            if (*piVar1 < 1) {
              return uVar8;
            }
            iVar4 = *DAT_00024194;
            uVar6 = DAT_000241c8;
            uVar5 = DAT_000241a0;
            uVar9 = uVar8;
            goto LAB_000240c6;
          }
          local_24 = 0;
          local_22 = 0;
          iVar4 = get_device_info();
          pcVar11 = *(code **)(iVar4 + 0x1030);
          uVar6 = get_device_info();
          iVar4 = (*pcVar11)(uVar6,0x13e000,&local_24,3);
          iVar7 = *piVar1;
          if (iVar4 == 0) {
            if (2 < iVar7) {
              G1_LOG_ROUTE(*DAT_000243dc == 0, DAT_000243e4,DAT_000243e0);
            }
            *(undefined1 *)(DAT_000243e8 + 1) = 2;
            return 0;
          }
        }
        else {
LAB_0002401a:
          iVar7 = *piVar1;
        }
        goto LAB_00024178;
      }
LAB_000240dc:
      if (0 < *piVar1) {
        uVar6 = *puVar10;
        goto LAB_00023fe2;
      }
      break;
    case 3:
      uVar8 = (uint)local_20[4];
      if (2 < *piVar1) {
        G1_LOG_ROUTE(*DAT_000243dc == 0, DAT_000243ec,DAT_000243e0,uVar8);
      }
      puVar10 = DAT_000243f4;
      iVar4 = DAT_000243e8;
      if (*(byte *)(DAT_000243e8 + 2) == uVar8) {
        iVar4 = *piVar1;
        bVar13 = false;
        bVar12 = iVar4 == 0;
LAB_00023fc4:
        if (!bVar12 && iVar4 < 0 == bVar13) {
          iVar4 = *DAT_00024194;
          uVar6 = DAT_000241b8;
          uVar5 = DAT_000241a0;
          goto LAB_00023f56;
        }
      }
      else {
        if (uVar8 < 3) {
          iVar7 = z_device_is_ready(DAT_000243f4);
          if (iVar7 == 0) goto LAB_00023fda;
          local_24 = 0;
          local_22 = 0;
          iVar7 = get_device_info();
          pcVar11 = *(code **)(iVar7 + 0x1030);
          uVar6 = get_device_info();
          iVar7 = (*pcVar11)(uVar6,0x13e000,&local_24,3);
          if (iVar7 == 0) {
            local_22 = local_20[4];
            local_24 = CONCAT11(((unsigned long long)(local_24)>>8 & 0xffULL),0xaa);
            iVar7 = get_device_info();
            pcVar11 = *(code **)(iVar7 + 0x1038);
            uVar6 = get_device_info();
            uVar8 = ((code3)pcVar11)(uVar6,0x13e000,0x1000);
            if (uVar8 != 0) goto LAB_00024044;
            iVar7 = get_device_info();
            pcVar11 = *(code **)(iVar7 + 0x1034);
            uVar6 = get_device_info();
            uVar8 = (*pcVar11)(uVar6,0x13e000,&local_24,3);
            if (uVar8 != 0) goto LAB_00024074;
            local_24 = 0;
            local_22 = 0;
            iVar7 = get_device_info();
            pcVar11 = *(code **)(iVar7 + 0x1030);
            uVar6 = get_device_info();
            iVar7 = (*pcVar11)(uVar6,0x13e000,&local_24,3);
            if (iVar7 == 0) {
              *(byte *)(iVar4 + 2) = local_22;
              uVar9 = 0;
              if (*piVar1 < 3) {
                return 0;
              }
              uVar8 = (uint)*(byte *)(iVar4 + 2);
              iVar4 = *DAT_000243dc;
              uVar6 = DAT_000243f8;
              uVar5 = DAT_000243e0;
              goto LAB_000240c6;
            }
          }
          goto LAB_0002401a;
        }
        if (0 < *piVar1) {
          iVar4 = *DAT_000243dc;
          uVar6 = DAT_000243f0;
          uVar5 = DAT_000243e0;
          goto LAB_00023f56;
        }
      }
      break;
    case 4:
      iVar4 = z_device_is_ready(DAT_000243f4);
      puVar10 = puVar3;
      if (iVar4 == 0) goto LAB_000240dc;
      local_24 = 0;
      local_22 = 0;
      iVar4 = get_device_info();
      pcVar11 = *(code **)(iVar4 + 0x1030);
      uVar6 = get_device_info();
      iVar4 = (*pcVar11)(uVar6,0x13e000,&local_24,3);
      if (iVar4 != 0) goto LAB_0002401a;
      local_22 = 0;
      local_24 = CONCAT11(((unsigned long long)(local_24)>>8 & 0xffULL),0xaa);
      iVar4 = get_device_info();
      pcVar11 = *(code **)(iVar4 + 0x1038);
      uVar6 = get_device_info();
      uVar8 = ((code3)pcVar11)(uVar6,0x13e000,0x1000);
      if (uVar8 != 0) goto LAB_00024044;
      iVar4 = get_device_info();
      pcVar11 = *(code **)(iVar4 + 0x1034);
      uVar6 = get_device_info();
      uVar8 = (*pcVar11)(uVar6,0x13e000,&local_24,3);
      if (uVar8 != 0) goto LAB_00024074;
      local_24 = 0;
      local_22 = 0;
      iVar4 = get_device_info();
      pcVar11 = *(code **)(iVar4 + 0x1030);
      uVar6 = get_device_info();
      iVar4 = (*pcVar11)(uVar6,0x13e000,&local_24,3);
      iVar7 = *piVar1;
      if (iVar4 == 0) {
        if (2 < iVar7) {
          G1_LOG_ROUTE(*DAT_000243dc == 0, DAT_000243e4,DAT_000243e0);
        }
        *(undefined1 *)(DAT_000243e8 + 2) = 0;
        return 0;
      }
LAB_00024178:
      if (0 < iVar7) {
        uVar6 = 0x13e000;
        iVar4 = *DAT_00024194;
        uVar5 = DAT_000241d0;
LAB_00023fea:
        G1_LOG_ROUTE(iVar4 == 0, uVar5,DAT_000241a0,uVar6);
      }
      break;
    default:
      goto switchD_00023f2c_caseD_4;
    }
  }
  else if (0 < *DAT_00024190) {
    G1_LOG_ROUTE(*DAT_00024194 == 0, DAT_0002419c,DAT_00024198);
    if (0 < *piVar1) {
      iVar4 = *piVar2;
      uVar6 = DAT_000241a4;
      uVar5 = DAT_000241a0;
LAB_00023f56:
      G1_LOG_ROUTE(iVar4 == 0, uVar6,uVar5);
    }
  }
  uVar8 = 0xffffffff;
switchD_00023f2c_caseD_4:
  return uVar8;
}
