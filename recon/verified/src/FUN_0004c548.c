/* Reconstructed FUN_0004c548 @ 0x4c548  (parity: 150/150 trials, PROVEN) */
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
static inline int isCurrentModePrivileged(void){unsigned c;__asm__ volatile("mrs %0, control":"=r"(c));return (c&1)==0;}
static inline int getBasePriority(void){unsigned b;__asm__ volatile("mrs %0, basepri":"=r"(b));return (int)b;}
static inline void setBasePriority(int p){__asm__ volatile("msr basepri, %0"::"r"(p):"memory");}
static inline void InstructionSynchronizationBarrier(int x){(void)x;__asm__ volatile("isb":::"memory");}

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

extern long long FUN_0004c4e4();
extern long long FUN_000723b8();
extern long long FUN_00072558();
extern long long FUN_0007e53e();
extern long long FUN_0007e55a();
extern long long FUN_0007e5da();
extern long long FUN_0007e624();
extern long long FUN_0007e658();
extern long long FUN_0007e65e();
extern long long FUN_0007e672();
extern long long FUN_0007e80c();
extern long long FUN_0007e83a();
extern long long FUN_00083a92();
extern long long FUN_000864c2();
#define DAT_0004c7a0 0xf0af8UL
#define DAT_0004c7a4 0x881b8UL
#define DAT_0004c7a8 0xf0b1aUL
#define DAT_0004c7ac 0xf0b37UL
#define DAT_0004c7b0 0xf0b4fUL
#define DAT_0004c7b4 0xf0b63UL
#define DAT_0004c7b8 0xf0bc0UL
#define DAT_0004c7bc 0xffff0000UL
#define DAT_0004c8e0 0xf0b86UL
#define DAT_0004c8e4 0x881b8UL
#define DAT_0004c8e8 0xf0b9dUL
#define DAT_0004c8ec 0xf0bafUL
#define DAT_0004c8f0 0xf0be7UL
#define DAT_0004c8f4 0xffff0000UL


int FUN_0004c548(undefined4 *param_1)

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
  FUN_000864c2(puVar9);
  iVar2 = (**(code **)(*(int *)(param_1[10] + 8) + 0xc))();
  param_1[0xb] = iVar2;
  uVar6 = DAT_0004c7a0;
  if ((iVar2 == 0) ||
     (piVar3 = (int *)(**(code **)(*(int *)(param_1[10] + 8) + 0xc))(), uVar6 = DAT_0004c7a8,
     0x1f < *piVar3 - 1U)) {
LAB_0004c56a:
    local_30 = 2;
    local_2c = uVar6;
    FUN_0007e658(DAT_0004c7a4,0x1040,&local_30);
    return -0x16;
  }
  uVar11 = FUN_00083a92(param_1[10],*param_1,auStack_4c);
  uVar6 = DAT_0004c7ac;
  if (((int)uVar11 != 0) ||
     (((local_60 = (uint)*(ushort *)(param_1 + 3), uVar6 = DAT_0004c7b0, local_60 == 0 ||
       (local_60 = local_60 - local_48 * (local_60 / local_48), local_60 != 0)) ||
      (uVar6 = DAT_0004c7b4, *(ushort *)((int)param_1 + 0xe) < 2)))) goto LAB_0004c56a;
  cVar1 = *(char *)(param_1[0xb] + 4);
  FUN_000723b8(puVar9,(int)((ulonglong)uVar11 >> 0x20),0xffffffff,0xffffffff);
  iVar2 = FUN_0007e65e(param_1[0xb],8);
  uVar8 = 0;
  for (uVar10 = 0; (uVar10 & 0xffff) < (uint)*(ushort *)((int)param_1 + 0xe); uVar10 = uVar10 + 1) {
    local_60 = uVar10 * 0x10000 + ((uint)*(ushort *)(param_1 + 3) - iVar2 & 0xffff);
    iVar4 = FUN_0007e5da(param_1,local_60,cVar1,8);
    if (iVar4 != 0) {
      FUN_0007e55a(param_1,&local_60);
      uVar8 = uVar8 + 1 & 0xffff;
      iVar4 = FUN_0007e5da(param_1,local_60,cVar1,8);
      if (iVar4 == 0) break;
    }
  }
  if (*(ushort *)((int)param_1 + 0xe) == uVar8) {
    FUN_00072558(puVar9);
    return -0x2d;
  }
  if (((uint)*(ushort *)((int)param_1 + 0xe) == (uVar10 & 0xffff)) &&
     (iVar4 = FUN_0007e5da(param_1,local_60 - iVar2,cVar1,8), iVar4 == 0)) {
    FUN_0007e55a(param_1,&local_60);
  }
  iVar4 = FUN_0004c4e4(param_1,&local_60);
  if (iVar4 == 0) {
    uVar10 = local_60 & 0xffff0000;
    param_1[1] = local_60;
    param_1[2] = uVar10;
    while ((uint)param_1[2] <= (uint)param_1[1]) {
      iVar4 = FUN_0007e53e(param_1,param_1[1],local_5c,8);
      if (iVar4 != 0) goto LAB_0004c672;
      iVar4 = 0;
      pcVar7 = local_5c;
      while (cVar1 == *pcVar7) {
        iVar4 = iVar4 + 1;
        pcVar7 = pcVar7 + 1;
        if (iVar4 == 8) goto LAB_0004c6b2;
      }
      iVar4 = FUN_0007e672(param_1,local_5c);
      iVar5 = param_1[1];
      if (iVar4 != 0) {
        uVar8 = (uint)local_58;
        param_1[2] = uVar10;
        iVar4 = FUN_0007e65e(param_1[0xb],local_5a + uVar8);
        param_1[2] = iVar4 + uVar10;
        if ((iVar4 + uVar10 == iVar5) && (uVar8 != 0)) {
          iVar2 = -0x1d;
          goto LAB_0004c8a4;
        }
      }
      param_1[1] = iVar5 - iVar2;
    }
LAB_0004c6b2:
    local_60 = param_1[1] & 0xffff0000;
    FUN_0007e55a(param_1,&local_60);
    iVar4 = FUN_0007e5da(param_1,local_60,cVar1,*(undefined2 *)(param_1 + 3));
    if (iVar4 < 0) goto LAB_0004c672;
    uVar10 = param_1[1];
    if (iVar4 == 0) {
      while( true ) {
        uVar10 = param_1[2];
        if ((uint)param_1[1] <= uVar10) break;
        iVar4 = FUN_0007e5da(param_1,uVar10,cVar1,param_1[1] - uVar10);
        if (iVar4 < 0) goto LAB_0004c672;
        if (iVar4 == 0) break;
        param_1[2] = param_1[2] + *(int *)param_1[0xb];
      }
      uVar10 = DAT_0004c8f4;
      if ((param_1[1] + iVar2 * 2 == (uint)*(ushort *)(param_1 + 3)) &&
         (param_1[2] != (param_1[1] & DAT_0004c8f4))) {
        iVar4 = FUN_0007e624(param_1);
        if (iVar4 != 0) goto LAB_0004c672;
        param_1[2] = param_1[1] & uVar10;
        goto LAB_0004c814;
      }
    }
    else {
      do {
        uVar10 = iVar2 + uVar10;
        local_60 = uVar10;
        if ((uint)*(ushort *)(param_1 + 3) - iVar2 <= (uVar10 & 0xffff)) {
          local_2c = DAT_0004c7b8;
          local_30 = 2;
          FUN_0007e658(DAT_0004c7a4,0x10c0,&local_30);
          iVar4 = FUN_0007e624(param_1,param_1[1]);
          uVar10 = DAT_0004c7bc;
          if (iVar4 != 0) goto LAB_0004c672;
          uVar8 = (param_1[1] & DAT_0004c7bc) + (uint)*(ushort *)(param_1 + 3) + iVar2 * -2;
          param_1[1] = uVar8;
          param_1[2] = uVar8 & uVar10;
          iVar4 = FUN_0007e83a(param_1);
          goto LAB_0004c730;
        }
        iVar4 = FUN_0007e53e(param_1,uVar10,local_54,8);
        if (iVar4 != 0) goto LAB_0004c672;
        iVar4 = FUN_0007e672(param_1,local_54);
      } while (((iVar4 == 0) || (local_54[0] != -1)) || (local_50 != 0));
      local_2c = DAT_0004c8f0;
      local_30 = 2;
      FUN_0007e658(DAT_0004c8e4,0x10c0,&local_30);
      local_60 = param_1[1] & 0xffff0000;
      FUN_0007e55a(param_1,&local_60);
      iVar4 = FUN_0007e624(param_1,local_60);
    }
LAB_0004c730:
    if (iVar4 == 0) {
LAB_0004c814:
      if ((uint)*(ushort *)(param_1 + 1) == (uint)*(ushort *)(param_1 + 3) + iVar2 * -2) {
        iVar2 = FUN_0007e80c(param_1);
LAB_0004c8a4:
        FUN_00072558(puVar9);
        if (iVar2 != 0) {
          return iVar2;
        }
      }
      else {
        FUN_00072558(puVar9);
      }
      *(undefined1 *)(param_1 + 4) = 1;
      local_68 = (uint)*(ushort *)((int)param_1 + 0xe);
      local_64 = (uint)*(ushort *)(param_1 + 3);
      local_6c = DAT_0004c8e0;
      local_70 = 4;
      FUN_0007e658(DAT_0004c8e4,0x20c0,&local_70);
      local_6c = DAT_0004c8e8;
      local_68 = (uint)param_1[1] >> 0x10;
      local_64 = param_1[1] & 0xffff;
      local_70 = 4;
      FUN_0007e658(DAT_0004c8e4,0x20c0,&local_70);
      local_70 = 4;
      local_6c = DAT_0004c8ec;
      local_68 = (uint)param_1[2] >> 0x10;
      local_64 = param_1[2] & 0xffff;
      FUN_0007e658(DAT_0004c8e4,0x20c0,&local_70);
      return 0;
    }
  }
LAB_0004c672:
  FUN_00072558(puVar9);
  return iVar4;
}


