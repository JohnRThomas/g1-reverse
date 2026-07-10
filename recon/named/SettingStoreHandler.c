/* named: SettingStoreHandler */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20003994  g_flash_store_cmd_msgq       
//   0x20007554  g_log_use_alt_sink           
//   0x20018462  g_ui_mode_flag               
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
typedef long long(*code)();
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
static inline int isCurrentModePrivileged(void){unsigned c;__asm__ volatile("mrs %0, control":"=r"(c));return (c&1)==0;}
static inline int getBasePriority(void){unsigned b;__asm__ volatile("mrs %0, basepri":"=r"(b));return (int)b;}
static inline void setBasePriority(int p){__asm__ volatile("msr basepri, %0"::"r"(p):"memory");}
static inline void InstructionSynchronizationBarrier(int x){(void)x;__asm__ volatile("isb":::"memory");}
static inline int CARRY4(unsigned a,unsigned b){return (a+b)<a;}
static inline int CARRY1(unsigned a,unsigned b){return ((a&0xff)+(b&0xff))>0xff;}
static inline int CARRY2(unsigned a,unsigned b){return ((a&0xffff)+(b&0xffff))>0xffff;}
static inline int SCARRY4(int a,int b){int r=(int)((unsigned)a+(unsigned)b);return (((a^r)&(b^r))<0);}
static inline int SBORROW4(int a,int b){int r=(int)((unsigned)a-(unsigned)b);return (((a^b)&(a^r))<0);}
static inline int SBORROW1(int a,int b){signed char r=(signed char)(a-b);return ((((signed char)a^(signed char)b)&((signed char)a^r))<0);}
static inline int SBORROW2(int a,int b){short r=(short)(a-b);return ((((short)a^(short)b)&((short)a^r))<0);}

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

extern long long DEBUG_PRINT();
extern long long get_device_info();
extern long long debug_print();
extern long long k_msgq_get();
extern long long z_device_is_ready();
#define DAT_0002418c 0x20003994UL
#define DAT_00024190 ((volatile int*)0x2000230cUL)
#define DAT_00024194 ((volatile int*)0x20007554UL)
#define DAT_00024198 0x9ecd5UL
#define DAT_0002419c 0x9ea7bUL
#define DAT_000241a0 0x9ecf5UL
#define DAT_000241a4 0x9eaa5UL
#define DAT_000241a8 0x9ead2UL
#define DAT_000241ac 0x9eaf4UL
#define DAT_000241b0 0x9eb2eUL
#define DAT_000241b4 0x20018462UL
#define DAT_000241b8 0x9eb66UL
#define DAT_000241bc 0x87bf0UL
#define DAT_000241c0 0x9e9eaUL
#define DAT_000241c4 0x9eba7UL
#define DAT_000241c8 0x9ebc6UL
#define DAT_000241cc 0x9ebe5UL
#define DAT_000241d0 0x9ea0aUL
#define DAT_000243dc (*(volatile int**)0x243dcUL)
#define DAT_000243e0 (*(volatile int*)0x243e0UL)
#define DAT_000243e4 (*(volatile int*)0x243e4UL)
#define DAT_000243e8 (*(volatile int*)0x243e8UL)
#define DAT_000243ec (*(volatile int*)0x243ecUL)
#define DAT_000243f0 (*(volatile int*)0x243f0UL)
#define DAT_000243f4 (*(volatile int*)0x243f4UL)
#define DAT_000243f8 (*(volatile int*)0x243f8UL)


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
  undefined1 local_20 [4];
  byte local_1c;
  
  iVar4 = k_msgq_get(DAT_0002418c,local_20,0,0);
  piVar2 = DAT_00024194;
  piVar1 = DAT_00024190;
  if (iVar4 == 0) {
    if (2 < *DAT_00024190) {
      if (*DAT_00024194 == 0) {
        DEBUG_PRINT(DAT_000241a8,DAT_000241a0);
      }
      else {
        debug_print();
      }
    }
    puVar3 = DAT_000243f4;
    puVar10 = DAT_000241bc;
    uVar8 = 0;
    switch(local_20[0]) {
    case 1:
      uVar8 = (uint)local_1c;
      if (2 < *piVar1) {
        if (*DAT_00024194 == 0) {
          DEBUG_PRINT(DAT_000241ac,DAT_000241a0,uVar8);
        }
        else {
          debug_print();
        }
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
            local_24 = CONCAT11(local_1c,0xaa);
            iVar7 = get_device_info();
            pcVar11 = *(code **)(iVar7 + 0x1038);
            uVar6 = get_device_info();
            uVar8 = (*pcVar11)(uVar6,0x13e000,0x1000);
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
          uVar8 = (*pcVar11)(uVar6,0x13e000,0x1000);
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
              debug_print();
              return uVar9;
            }
            DEBUG_PRINT(uVar6,uVar5,uVar8);
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
              if (*DAT_000243dc == 0) {
                DEBUG_PRINT(DAT_000243e4,DAT_000243e0);
              }
              else {
                debug_print();
              }
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
      uVar8 = (uint)local_1c;
      if (2 < *piVar1) {
        if (*DAT_000243dc == 0) {
          DEBUG_PRINT(DAT_000243ec,DAT_000243e0,uVar8);
        }
        else {
          debug_print();
        }
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
            local_22 = local_1c;
            local_24 = CONCAT11(((unsigned long long)(local_24)>>8 & 0xffULL),0xaa);
            iVar7 = get_device_info();
            pcVar11 = *(code **)(iVar7 + 0x1038);
            uVar6 = get_device_info();
            uVar8 = (*pcVar11)(uVar6,0x13e000,0x1000);
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
      uVar8 = (*pcVar11)(uVar6,0x13e000,0x1000);
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
          if (*DAT_000243dc == 0) {
            DEBUG_PRINT(DAT_000243e4,DAT_000243e0);
          }
          else {
            debug_print();
          }
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
        if (iVar4 == 0) {
          DEBUG_PRINT(uVar5,DAT_000241a0,uVar6);
        }
        else {
          debug_print();
        }
      }
      break;
    default:
      goto switchD_00023f2c_caseD_4;
    }
  }
  else if (0 < *DAT_00024190) {
    if (*DAT_00024194 == 0) {
      DEBUG_PRINT(DAT_0002419c,DAT_00024198);
    }
    else {
      debug_print();
    }
    if (0 < *piVar1) {
      iVar4 = *piVar2;
      uVar6 = DAT_000241a4;
      uVar5 = DAT_000241a0;
LAB_00023f56:
      if (iVar4 == 0) {
        DEBUG_PRINT(uVar6,uVar5);
      }
      else {
        debug_print();
      }
    }
  }
  uVar8 = 0xffffffff;
switchD_00023f2c_caseD_4:
  return uVar8;
}


