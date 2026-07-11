/* Reconstructed FUN_000646c0 @ 0x646c0  (parity: 150/150 trials, PROVEN) */
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

extern long long FUN_0000d588(int,int,int,int);
extern long long FUN_0000d8f8(int,int,int,int);
extern long long FUN_0000dddc(int,int,int,int,int,int);
extern long long FUN_0000ddf0(int,int,int,int);
extern long long FUN_0000de2c(int,int,int,int);
extern long long FUN_0000ef12(void);
extern long long FUN_000644f8(int, ...);
extern long long FUN_00077914(int,int,int);
extern long long FUN_000779bc(int,int,int);
extern long long FUN_00084f16(int);
extern long long FUN_00084f58(int,int);
extern long long FUN_00086c04(int,int,int);
extern long long FUN_00086c78(int,int,int);
extern long long FUN_00086fee(int,int);
extern long long FUN_0008705a(int,int,int);
#define DAT_0006498c 0xf6977UL
#define DAT_00064990 ((volatile int*)0xf698eUL)
#define DAT_00064994 0xf6994UL
#define DAT_00064998 0x7fefffffUL
#define DAT_0006499c 0xf697cUL
#define DAT_000649a0 0xf6983UL
#define DAT_000649a4 0x3cb00000UL
#define DAT_000649a8 0xf6987UL


uint FUN_000646c0(int param_1,int param_2)

{
  byte bVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  undefined1 *puVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined1 *puVar8;
  uint uVar9;
  int *piVar10;
  uint uVar11;
  undefined4 uVar12;
  undefined4 uVar13;
  uint uVar14;
  undefined8 uVar15;
  undefined8 uVar16;
  uint uVar17;
  undefined4 local_50;
  uint uStack_4c;
  undefined4 local_44;
  undefined2 local_40 [14];
  
  if ((param_1 == 0) || (param_2 == 0)) goto switchD_000646e2_caseD_3;
  bVar1 = *(byte *)(param_1 + 0xc);
  uVar9 = (uint)bVar1;
  if (uVar9 == 0x10) {
    uVar9 = FUN_000644f8(*(undefined4 *)(param_1 + 0x10));
    return uVar9;
  }
  if (0x10 < uVar9) {
    if (uVar9 == 0x40) {
      piVar10 = *(int **)(param_1 + 8);
      if (*(int *)(param_2 + 0x14) == 0) {
        iVar6 = 1;
      }
      else {
        iVar6 = 2;
      }
      puVar5 = (undefined1 *)FUN_00084f58(param_2,iVar6 + 1);
      if (puVar5 != (undefined1 *)0x0) {
        *puVar5 = 0x7b;
        *(int *)(param_2 + 0xc) = *(int *)(param_2 + 0xc) + 1;
        if (*(int *)(param_2 + 0x14) != 0) {
          puVar5[1] = 10;
        }
        *(int *)(param_2 + 8) = *(int *)(param_2 + 8) + iVar6;
        for (; piVar10 != (int *)0x0; piVar10 = (int *)*piVar10) {
          if (*(int *)(param_2 + 0x14) != 0) {
            puVar8 = (undefined1 *)FUN_00084f58(param_2,*(undefined4 *)(param_2 + 0xc));
            puVar5 = puVar8;
            if (puVar8 == (undefined1 *)0x0) goto switchD_000646e2_caseD_3;
            for (; (uint)((int)puVar5 - (int)puVar8) < *(uint *)(param_2 + 0xc); puVar5 = puVar5 + 1
                ) {
              *puVar5 = 9;
            }
            *(uint *)(param_2 + 8) = *(int *)(param_2 + 8) + *(uint *)(param_2 + 0xc);
          }
          iVar6 = FUN_000644f8(piVar10[8],param_2);
          if (iVar6 == 0) goto switchD_000646e2_caseD_3;
          FUN_00084f16(param_2);
          if (*(int *)(param_2 + 0x14) == 0) {
            iVar6 = 1;
          }
          else {
            iVar6 = 2;
          }
          puVar5 = (undefined1 *)FUN_00084f58(param_2,iVar6);
          if (puVar5 == (undefined1 *)0x0) goto switchD_000646e2_caseD_3;
          *puVar5 = 0x3a;
          if (*(int *)(param_2 + 0x14) != 0) {
            puVar5[1] = 9;
          }
          *(int *)(param_2 + 8) = *(int *)(param_2 + 8) + iVar6;
          iVar6 = FUN_000646c0(piVar10,param_2);
          if (iVar6 == 0) goto switchD_000646e2_caseD_3;
          FUN_00084f16(param_2);
          iVar6 = *(int *)(param_2 + 0x14);
          if (iVar6 != 0) {
            iVar6 = 1;
          }
          if (*piVar10 != 0) {
            iVar6 = iVar6 + 1;
          }
          puVar5 = (undefined1 *)FUN_00084f58(param_2,iVar6 + 1);
          if (puVar5 == (undefined1 *)0x0) goto switchD_000646e2_caseD_3;
          puVar8 = puVar5;
          if (*piVar10 != 0) {
            puVar8 = puVar5 + 1;
            *puVar5 = 0x2c;
          }
          puVar5 = puVar8;
          if (*(int *)(param_2 + 0x14) != 0) {
            puVar5 = puVar8 + 1;
            *puVar8 = 10;
          }
          *puVar5 = 0;
          *(int *)(param_2 + 8) = *(int *)(param_2 + 8) + iVar6;
        }
        if (*(int *)(param_2 + 0x14) == 0) {
          iVar6 = 2;
        }
        else {
          iVar6 = *(int *)(param_2 + 0xc) + 1;
        }
        puVar5 = (undefined1 *)FUN_00084f58(param_2,iVar6);
        if (puVar5 != (undefined1 *)0x0) {
          puVar8 = puVar5;
          if (*(int *)(param_2 + 0x14) != 0) {
            for (; (uint)((int)puVar8 - (int)puVar5) < *(int *)(param_2 + 0xc) - 1U;
                puVar8 = puVar8 + 1) {
              *puVar8 = 9;
            }
          }
          *puVar8 = 0x7d;
          puVar8[1] = 0;
LAB_000648d0:
          *(int *)(param_2 + 0xc) = *(int *)(param_2 + 0xc) + -1;
          goto LAB_00064728;
        }
      }
    }
    else if (uVar9 == 0x80) {
      if (*(int *)(param_1 + 0x10) != 0) {
        iVar6 = FUN_0000ef12();
        iVar4 = FUN_00084f58(param_2,iVar6 + 1);
        if (iVar4 != 0) {
          FUN_00086c04(iVar4,*(undefined4 *)(param_1 + 0x10),iVar6 + 1);
          goto LAB_00064728;
        }
      }
    }
    else if (uVar9 == 0x20) {
      piVar10 = *(int **)(param_1 + 8);
      puVar5 = (undefined1 *)FUN_00084f58(param_2,1);
      if (puVar5 != (undefined1 *)0x0) {
        *puVar5 = 0x5b;
        *(int *)(param_2 + 8) = *(int *)(param_2 + 8) + 1;
        *(int *)(param_2 + 0xc) = *(int *)(param_2 + 0xc) + 1;
        for (; piVar10 != (int *)0x0; piVar10 = (int *)*piVar10) {
          iVar6 = FUN_000646c0(piVar10,param_2);
          if (iVar6 == 0) goto switchD_000646e2_caseD_3;
          FUN_00084f16(param_2);
          if (*piVar10 != 0) {
            if (*(int *)(param_2 + 0x14) == 0) {
              iVar6 = 1;
            }
            else {
              iVar6 = 2;
            }
            puVar5 = (undefined1 *)FUN_00084f58(param_2,iVar6 + 1);
            if (puVar5 == (undefined1 *)0x0) goto switchD_000646e2_caseD_3;
            *puVar5 = 0x2c;
            if (*(int *)(param_2 + 0x14) == 0) {
              puVar8 = puVar5 + 1;
            }
            else {
              puVar8 = puVar5 + 2;
              puVar5[1] = bVar1;
            }
            *puVar8 = 0;
            *(int *)(param_2 + 8) = *(int *)(param_2 + 8) + iVar6;
          }
        }
        puVar5 = (undefined1 *)FUN_00084f58(param_2,2);
        if (puVar5 != (undefined1 *)0x0) {
          puVar5[1] = 0;
          *puVar5 = 0x5d;
          goto LAB_000648d0;
        }
      }
    }
    goto switchD_000646e2_caseD_3;
  }
  switch(uVar9) {
  case 1:
    local_44 = *DAT_00064990;
    local_40[0] = *(undefined2 *)(DAT_00064990 + 1);
    iVar6 = FUN_00084f58(param_2,6);
    if (iVar6 != 0) {
      FUN_0008705a(iVar6,&local_44,*(int *)(param_2 + 4) - *(int *)(param_2 + 8));
      return uVar9;
    }
  default:
switchD_000646e2_caseD_3:
    uVar9 = 0;
    break;
  case 2:
    puVar7 = DAT_00064994;
    goto LAB_00064706;
  case 4:
    puVar7 = DAT_0006498c;
LAB_00064706:
    local_44 = *puVar7;
    local_40[0] = CONCAT11(((unsigned long long)(local_40[0])>>8 & 0xffULL),*(undefined1 *)(puVar7 + 1));
    uVar9 = FUN_00084f58(param_2,5);
    if (uVar9 != 0) {
      FUN_0008705a(uVar9,&local_44,*(int *)(param_2 + 4) - *(int *)(param_2 + 8));
LAB_00064728:
      uVar9 = 1;
    }
    break;
  case 8:
    uVar12 = *(undefined4 *)(param_1 + 0x18);
    uVar9 = *(uint *)(param_1 + 0x1c);
    local_44 = 0;
    FUN_00086c78(local_40,0,0x16);
    local_50 = 0;
    uStack_4c = 0;
    iVar6 = FUN_0000de2c(uVar12,uVar9,uVar12,uVar9);
    if (iVar6 == 0) {
      uVar14 = uVar9 & 0x7fffffff;
      iVar6 = FUN_0000de2c(uVar12,uVar14,0xffffffff,DAT_00064998);
      if ((iVar6 == 0) && (iVar6 = FUN_0000ddf0(uVar12,uVar14,0xffffffff,DAT_00064998), iVar6 == 0))
      goto LAB_000647a8;
      uVar13 = uVar12;
      uVar17 = uVar9;
      iVar6 = FUN_00077914(&local_44,0x1a,DAT_0006499c);
      iVar4 = FUN_000779bc(&local_44,DAT_000649a0,&local_50);
      uVar3 = uStack_4c;
      uVar2 = local_50;
      if (iVar4 == 1) {
        uVar11 = uStack_4c & 0x7fffffff;
        iVar4 = FUN_0000dddc(uVar12,uVar14,local_50,uVar11,uVar13,uVar17);
        uVar13 = uVar12;
        if (iVar4 != 0) {
          uVar13 = uVar2;
          uVar14 = uVar11;
        }
        uVar15 = FUN_0000d588(uVar2,uVar3,uVar12,uVar9);
        uVar16 = FUN_0000d8f8(uVar13,uVar14,0,DAT_000649a4);
        iVar4 = FUN_0000ddf0((int)uVar15,(uint)((ulonglong)uVar15 >> 0x20) & 0x7fffffff,(int)uVar16,
                             (int)((ulonglong)uVar16 >> 0x20));
        if (iVar4 == 0) goto LAB_00064840;
      }
      else {
LAB_00064840:
        iVar6 = FUN_00077914(&local_44,0x1a,DAT_000649a8);
      }
      if (0x19 < iVar6) goto switchD_000646e2_caseD_3;
    }
    else {
LAB_000647a8:
      FUN_00086fee(&local_44,DAT_0006498c);
      iVar6 = 4;
    }
    puVar5 = (undefined1 *)FUN_00084f58(param_2,iVar6 + 1);
    if (puVar5 == (undefined1 *)0x0) goto switchD_000646e2_caseD_3;
    puVar7 = &local_44;
    for (puVar8 = puVar5; puVar5 + iVar6 != puVar8; puVar8 = puVar8 + 1) {
      *puVar8 = *(undefined1 *)puVar7;
      puVar7 = (undefined4 *)((int)puVar7 + 1);
    }
    puVar5[iVar6] = 0;
    *(int *)(param_2 + 8) = *(int *)(param_2 + 8) + iVar6;
    goto LAB_00064728;
  }
  return uVar9;
}

