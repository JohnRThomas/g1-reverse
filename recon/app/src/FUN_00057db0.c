/* Reconstructed FUN_00057db0 @ 0x57db0  (parity: 30/30 trials, PROVEN) */
#pragma GCC diagnostic ignored "-Wint-conversion"
#pragma GCC diagnostic ignored "-Wpointer-to-int-cast"
#pragma GCC diagnostic ignored "-Wint-to-pointer-cast"
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
#include <stdint.h>
#include <cmsis_gcc.h>
typedef unsigned char undefined,undefined1,byte,uchar,uint1;
typedef unsigned short undefined2,ushort,uint2,wchar_t;
typedef unsigned int undefined4,uint,uint3,code_t;
typedef unsigned long long undefined8,ulonglong;
typedef long long longlong; typedef unsigned long ulong; typedef signed char sbyte;
typedef long long(*code0)(void);
typedef long long(*code1)(int);
typedef long long(*code2)(int, void *);
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
static inline int isCurrentModePrivileged(void){ return (__get_CONTROL() & 1u) == 0; }
static inline int getBasePriority(void){ return (int)__get_BASEPRI(); }
static inline void setBasePriority(int p){ __set_BASEPRI((uint32_t)p); }
static inline void InstructionSynchronizationBarrier(int x){ (void)x; __ISB(); }
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

extern long long FUN_000573f4(int, ...);
extern long long FUN_00057484(int, ...);
extern long long FUN_000574ec(int, ...);
extern long long FUN_00057874(int, ...);
extern long long FUN_000579b4(int, ...);
extern long long FUN_0005f24c(int, ...);
extern long long FUN_0005f594(int, ...);
extern long long FUN_0005f5d0(int, ...);
extern long long FUN_00073518(int, ...);
extern long long FUN_0008145c(int, ...);
extern long long FUN_0008149a(int, ...);
extern long long FUN_00081626(int, ...);
extern long long FUN_00081660(int, ...);
extern long long FUN_000816a2(int, ...);
extern long long FUN_00081720(int, ...);
extern long long FUN_00081746(int, ...);
extern long long FUN_0008174c(int, ...);
extern long long FUN_00081788(int, ...);
extern long long FUN_000817b6(int, ...);
extern long long FUN_00081820(int, ...);
extern long long FUN_00081940(int, ...);
extern long long FUN_00081a4e(int, ...);
extern long long FUN_00081b30(int, ...);
extern long long FUN_00083740(int, ...);
#define DAT_00058054 0xf41a7UL
#define DAT_00058058 0x88160UL
#define DAT_0005805c 0xf41c5UL
#define DAT_00058060 0xf41e6UL
#define DAT_00058064 0xf4207UL
#define DAT_00058068 0xf4223UL
#define DAT_0005806c 0xf4245UL
#define DAT_00058070 0xf426fUL
#define DAT_00058074 0x816afUL
#define DAT_00058078 0xf4291UL
#define DAT_0005807c 0xf42b3UL
#define DAT_000582a0 0xf42d4UL
#define DAT_000582a4 0xf42f9UL
#define DAT_000582a8 0xf431aUL
#define DAT_000582ac 0xf4346UL
#define DAT_000582b0 0x88160UL
#define DAT_000582b4 (*(volatile int*)0x582b4UL)


/* WARNING: Removing unreachable block (ram,0x0005811a) */

undefined4 FUN_00057db0(int *param_1,int param_2)

{
  byte bVar1;
  ushort uVar2;
  ushort uVar3;
  undefined2 uVar4;
  undefined2 uVar5;
  undefined2 uVar6;
  byte *pbVar7;
  undefined4 *puVar8;
  int iVar9;
  int *piVar10;
  int iVar11;
  undefined1 *puVar12;
  undefined4 uVar13;
  uint uVar14;
  undefined2 *puVar15;
  int iVar16;
  uint uVar17;
  uint uVar18;
  uint *puVar19;
  short sVar20;
  int iVar21;
  undefined4 local_60;
  undefined4 local_5c;
  uint local_58;
  uint local_54;
  uint local_50;
  uint local_4c;
  int local_44;
  undefined2 local_40;
  undefined2 local_3e;
  undefined4 local_30;
  undefined4 local_2c;
  struct { uint count, format, value0, value1; } log4;
  struct { uint count, format, value; } log3;
  
  uVar13 = DAT_00058054;
  if (*(ushort *)(param_2 + 0x10) < 4) goto LAB_00057dc4;
  pbVar7 = (byte *)FUN_0005f594(param_2 + 0xc,4);
  uVar17 = (uint)*(ushort *)(param_2 + 0x10);
  local_54 = (uint)*(ushort *)(pbVar7 + 2);
  if (uVar17 != local_54) {
    local_5c = DAT_0005805c;
    local_58 = uVar17;
LAB_00057e04:
    log4.count = 4;
    log4.format = local_5c;
    log4.value0 = local_58;
    log4.value1 = local_54;
    FUN_00081746(DAT_00058058,0x2040,&log4);
    return 0;
  }
  uVar18 = (uint)pbVar7[1];
  uVar13 = DAT_00058060;
  if (uVar18 == 0) goto LAB_00057dc4;
  uVar14 = (uint)*pbVar7;
  if (uVar14 == 1) {
    piVar10 = (int *)FUN_00081626(*param_1,uVar18);
LAB_000581ee:
    if (piVar10 == (int *)0x0) {
      return 0;
    }
    goto LAB_00058136;
  }
  if ((uVar14 - 6 & 0xff) < 0x11) {
    uVar13 = DAT_00058068;
    switch(uVar14 - 6) {
    case 0:
      iVar21 = *param_1;
      puVar15 = *(undefined2 **)(param_2 + 0xc);
      if (uVar17 < 4) break;
      iVar16 = FUN_00081660(iVar21,*puVar15);
      if (iVar16 == 0) {
        local_40 = puVar15[1];
        local_3e = *puVar15;
        iVar11 = FUN_000573f4(1,uVar18,6);
        if (iVar11 == 0) {
          return 0;
        }
        puVar12 = (undefined1 *)FUN_0005f5d0(iVar11 + 0xc,2);
        puVar12[1] = 0;
        *puVar12 = 2;
        FUN_00083740(iVar11 + 0xc,&local_40,4);
      }
      else {
        iVar11 = FUN_000573f4(7,uVar18,4);
        if (iVar11 == 0) {
          return 0;
        }
        puVar15 = (undefined2 *)FUN_0005f5d0(iVar11 + 0xc,4);
        *puVar15 = *(undefined2 *)(iVar16 + 0x14);
        puVar15[1] = *(undefined2 *)(iVar16 + 0x24);
        FUN_000817b6(iVar16);
      }
      goto LAB_000581ac;
    case 1:
      uVar13 = DAT_000582a0;
      if (3 < uVar17) {
        piVar10 = (int *)FUN_00081660(*param_1,*(undefined2 *)(*(int *)(param_2 + 0xc) + 2));
        goto LAB_000581ee;
      }
      break;
    default:
      goto switchD_00057e38_caseD_2;
    case 0xd:
      uVar13 = DAT_00058064;
      if (1 < uVar17) {
        return 0;
      }
      break;
    case 0xe:
      iVar21 = *param_1;
      puVar15 = *(undefined2 **)(param_2 + 0xc);
      if (9 < uVar17) {
        local_58 = (uint)(ushort)puVar15[2];
        uVar2 = puVar15[1];
        uVar3 = puVar15[3];
        uVar4 = *puVar15;
        local_50 = (uint)(ushort)puVar15[4];
        local_54 = (uint)uVar3;
        local_4c = local_58;
        if ((local_58 < 0x17) || (local_54 < 0x17)) {
          local_5c = DAT_0005806c;
          goto LAB_00057e04;
        }
        iVar11 = FUN_000573f4(0x15,uVar18,10);
        if (iVar11 == 0) {
          return 0;
        }
        puVar8 = (undefined4 *)FUN_0005f5d0(iVar11 + 0xc,10);
        *puVar8 = 0;
        puVar8[1] = 0;
        *(undefined2 *)(puVar8 + 2) = 0;
        puVar15 = (undefined2 *)FUN_000579b4(uVar4);
        if (puVar15 == (undefined2 *)0x0) {
LAB_00057ed4:
          sVar20 = 2;
          goto LAB_00057ed6;
        }
        if (*(byte *)(iVar21 + 9) < *(byte *)(puVar15 + 1)) {
          if ((*(byte *)(iVar21 + 9) < 2) && (iVar16 = FUN_0008145c(iVar21), iVar16 != 0)) {
            sVar20 = 8;
          }
          else {
            sVar20 = 5;
          }
          goto LAB_00057ed6;
        }
        if (0x3f < uVar2 - 0x40) {
          sVar20 = 9;
          goto LAB_00057ed6;
        }
        local_44 = FUN_00081a4e(iVar21,(uint)uVar2);
        if (local_44 != 0) {
          sVar20 = 10;
          goto LAB_00057ed6;
        }
        iVar9 = (**(code2 **)(puVar15 + 2))(iVar21,&local_44);
        iVar16 = local_44;
        uVar13 = DAT_00058074;
        if (iVar9 < 0) {
          if (iVar9 == -0xc) {
LAB_00057f58:
            sVar20 = 4;
            goto LAB_00057ed6;
          }
          if (iVar9 + 0xb < 0 == SCARRY4(iVar9,0xb)) {
            if (iVar9 == -1) {
              sVar20 = 7;
              goto LAB_00057ed6;
            }
          }
          else {
            if (iVar9 == -0x86) goto LAB_00057ed4;
            if (iVar9 == -0xd) {
              sVar20 = 6;
              goto LAB_00057ed6;
            }
          }
        }
        else {
          if (*(int *)(*(int *)(local_44 + 4) + 0x14) != 0) {
            *(undefined1 *)(local_44 + 0xb9) = *(undefined1 *)(puVar15 + 1);
            iVar9 = FUN_00057874(iVar21,local_44,uVar13);
            if (iVar9 != 0) {
              FUN_000574ec(iVar16);
              *(undefined2 *)(iVar16 + 0x26) = (undefined2)local_4c;
              *(ushort *)(iVar16 + 0x24) = uVar2;
              *(ushort *)(iVar16 + 0x28) = uVar3;
              FUN_0008174c(iVar16,local_50);
              FUN_00057484(iVar16);
              sVar20 = 0;
              *(undefined2 *)(iVar16 + 0xb6) = *puVar15;
              *(undefined1 *)(local_44 + 0xb4) = 3;
              *(undefined2 *)puVar8 = *(undefined2 *)(local_44 + 0x14);
              *(undefined2 *)(puVar8 + 1) = *(undefined2 *)(local_44 + 0x18);
              *(undefined2 *)((int)puVar8 + 2) = *(undefined2 *)(local_44 + 0x16);
              *(short *)((int)puVar8 + 6) = (short)*(undefined4 *)(local_44 + 0x1c);
              goto LAB_00057ed6;
            }
            goto LAB_00057f58;
          }
          local_2c = DAT_00058070;
          local_30 = 2;
          FUN_00081746(DAT_00058058,0x1040,&local_30);
        }
        sVar20 = 0xb;
LAB_00057ed6:
        *(short *)(puVar8 + 2) = sVar20;
        local_58 = 0;
        iVar21 = FUN_00081820(iVar21,5,iVar11);
        if (iVar21 != 0) {
          FUN_0005f24c(iVar11);
          return 0;
        }
        if (sVar20 != 0) {
          return 0;
        }
        if ((code0 *)**(undefined4 **)(local_44 + 4) == (code0 *)0x0) {
          return 0;
        }
        (*(code0 *)**(undefined4 **)(local_44 + 4))();
        return 0;
      }
      break;
    case 0xf:
      iVar21 = *param_1;
      puVar15 = *(undefined2 **)(param_2 + 0xc);
      uVar13 = DAT_00058078;
      if (9 < uVar17) {
        local_4c = (uint)(ushort)puVar15[3];
        uVar4 = puVar15[1];
        uVar5 = puVar15[2];
        uVar2 = puVar15[4];
        uVar6 = *puVar15;
        if (((uVar2 & 0xfff7) == 0) || (uVar2 == 5)) {
          piVar10 = (int *)FUN_00081626(iVar21,uVar18,0);
          if (piVar10 == (int *)0x0) goto LAB_00058032;
          FUN_00073518(piVar10 + 0x30);
          *(undefined1 *)(piVar10 + 0x2e) = 0;
          if (uVar2 != 5) goto LAB_0005809c;
          puVar19 = (uint *)(piVar10 + 4);
          iVar16 = *piVar10;
          iVar11 = FUN_000816a2(puVar19);
          if (-1 < iVar11 << 0x1d) {
            bVar1 = *(byte *)(iVar16 + 9);
            if (bVar1 < 2) goto LAB_00058142;
            if (bVar1 == 2) {
              uVar13 = 3;
            }
            else {
              if (bVar1 != 3) goto LAB_0005812c;
              uVar13 = 4;
            }
            goto LAB_000580fc;
          }
        }
        else {
          piVar10 = (int *)FUN_00081626(iVar21,uVar18,1);
          if (piVar10 == (int *)0x0) {
LAB_00058032:
            log3.count = 3;
            log3.format = DAT_0005807c;
            log3.value = uVar18;
            FUN_00081746(DAT_00058058,0x1840,&log3);
            return 0;
          }
          FUN_00073518(piVar10 + 0x30);
          *(undefined1 *)(piVar10 + 0x2e) = 0;
LAB_0005809c:
          if (uVar2 != 8) {
            if (uVar2 == 0) {
              *(undefined1 *)(piVar10 + 0x2d) = 3;
              *(undefined2 *)(piVar10 + 9) = uVar6;
              *(undefined2 *)((int)piVar10 + 0x26) = uVar4;
              *(undefined2 *)(piVar10 + 10) = uVar5;
              if (*(code1 **)piVar10[1] != (code1 *)0x0) {
                (**(code1 **)piVar10[1])((int)piVar10);
              }
              FUN_0008174c(piVar10,local_4c);
              return 0;
            }
            goto LAB_00058136;
          }
          puVar19 = (uint *)(piVar10 + 4);
          iVar16 = *piVar10;
          iVar11 = FUN_000816a2(puVar19);
          if ((-1 < iVar11 << 0x1d) && (*(byte *)(iVar16 + 9) < 2)) {
LAB_00058142:
            uVar13 = 2;
LAB_000580fc:
            iVar11 = FUN_0008149a(*piVar10,uVar13);
            if (-1 < iVar11) {
              *puVar19 = *puVar19 | 4;
              return 0;
            }
          }
        }
LAB_0005812c:
        FUN_00081788(iVar21,piVar10);
LAB_00058136:
        FUN_000817b6(piVar10);
        return 0;
      }
      break;
    case 0x10:
      uVar13 = DAT_000582a4;
      if (3 < uVar17) {
        uVar17 = (uint)(ushort)(*(undefined2 **)(param_2 + 0xc))[1];
        iVar21 = FUN_00081a4e(*param_1,**(undefined2 **)(param_2 + 0xc));
        uVar13 = DAT_000582a8;
        if (iVar21 != 0) {
          iVar11 = FUN_000816a2(iVar21 + 0x2c);
          if (0xffff < (int)(iVar11 + uVar17)) {
            local_2c = DAT_000582ac;
            local_30 = 2;
            FUN_00081746(DAT_000582b0,0x1040,&local_30);
            FUN_00081b30(iVar21);
            return 0;
          }
          FUN_0008174c(iVar21,uVar17);
          FUN_00081720(iVar21);
          return 0;
        }
      }
    }
LAB_00057dc4:
    local_30 = 2;
    local_2c = uVar13;
    FUN_00081746(DAT_00058058,0x1040,&local_30);
  }
  else {
switchD_00057e38_caseD_2:
    log3.count = 3;
    log3.format = DAT_000582b4;
    log3.value = uVar14;
    FUN_00081746(DAT_000582b0,0x1880,&log3);
    iVar21 = *param_1;
    iVar11 = FUN_000573f4(1,pbVar7[1],2);
    if (iVar11 == 0) {
      return 0;
    }
    puVar12 = (undefined1 *)FUN_0005f5d0(iVar11 + 0xc,2);
    *puVar12 = 0;
    puVar12[1] = 0;
LAB_000581ac:
    FUN_00081940(iVar21,iVar11);
  }
  return 0;
}
