/* Reconstructed draw_message @ 0x35afc  (parity: 30/30 trials, PROVEN) */
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

extern long long DEBUG_PRINT(long long format, ...);
extern long long FUN_00019c70(void);
extern long long FUN_00034390(void);
extern long long FUN_0003483c(void);
extern long long FUN_000357dc(long long, long long);
extern long long FUN_00043484(long long,long long,long long,long long,long long,long long);
extern long long FUN_00043e90(long long,long long,long long,long long,long long,long long,long long,long long,long long,long long,long long,long long);
extern long long FUN_00044818(long long,long long,long long,long long,long long,long long,long long,long long,long long,long long,long long,long long);
extern long long FUN_00044bd8(long long,long long,long long,long long,long long,long long,long long,long long,long long,long long,long long,long long);
extern long long FUN_000451e0(long long,long long,long long,long long,long long,long long,long long,long long,long long,long long,long long,long long);
extern long long FUN_00077914(long long destination, long long size, long long format, ...);
extern long long FUN_0007d3ee(void);
extern long long FUN_0007d446(void);
extern long long FUN_00086c78(long long,long long,long long);
extern long long FUN_00086f00(long long,long long,long long,long long,long long);
#define DAT_00035e74 ((volatile int*)0x20007554UL)
#define DAT_00035e78 0xa8ce7UL
#define DAT_00035e7c 0xa8bcdUL
#define DAT_00035e80 0xa8be6UL
#define DAT_00035e84 0xa8c37UL
#define DAT_00035e88 0xa8c09UL
#define DAT_00035e8c 0xa8c11UL
#define DAT_00035e90 0xf4ca5UL
#define DAT_00035f1c 0xa8c34UL
#define DAT_00035f20 0xa8c37UL
#define DAT_00035f24 (*(volatile int*)0x35f24UL)


void draw_message(undefined4 param_1,undefined4 *param_2)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  int iVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  undefined4 local_1b4;
  undefined4 uStack_1b0;
  undefined4 local_1ac;
  undefined1 auStack_1a8 [28];
  undefined4 local_18c;
  undefined1 auStack_188 [68];
  uint local_144;
  undefined1 auStack_140 [288];
  
  local_18c = 0;
  FUN_00086c78(auStack_188,0,0x44);
  local_1ac = 0;
  FUN_00086c78(auStack_1a8,0,0x1c);
  local_1b4 = 0;
  uStack_1b0 = 0;
  local_144 = 0;
  FUN_00086c78(auStack_140,0,0x11f);
  piVar1 = DAT_00035e74;
  if (param_2 == (undefined4 *)0x0) {
    if (*DAT_00035e74 != 0) {
      FUN_00019c70();
      return;
    }
    DEBUG_PRINT(DAT_00035e7c,DAT_00035e78,0xdb);
    return;
  }
  FUN_00034390();
  iVar2 = FUN_0003483c();
  if (*piVar1 == 0) {
    DEBUG_PRINT(DAT_00035e80,iVar2,param_1);
  }
  else {
    FUN_00019c70();
  }
  puVar9 = param_2 + 0x24;
  switch(iVar2) {
  case 0:
    uVar6 = FUN_0007d3ee();
    iVar7 = FUN_0007d446();
    uVar5 = 0x38;
    goto LAB_00035e0a;
  case 1:
    uVar6 = FUN_0007d3ee();
    iVar7 = FUN_0007d446();
    FUN_00043484(0x37,uVar6,iVar7 + 4,0,0,0);
    FUN_00086c78(&local_18c,0,0x48);
    puVar8 = puVar9;
    break;
  case 2:
    FUN_00086c78(&local_18c,0,0x48);
    FUN_00077914(&local_18c,0x48,DAT_00035e84,puVar9);
    uVar6 = FUN_0007d3ee();
    iVar2 = FUN_0007d446();
    iVar7 = FUN_0007d3ee();
    iVar3 = FUN_0007d446();
    FUN_00044bd8(0,&local_18c,0,uVar6,iVar2 + 0x36,iVar7 + 0x240,iVar3 + 0x51,1,0,0,0,0);
    uVar6 = FUN_0007d3ee();
    iVar2 = FUN_0007d446();
    FUN_00043484(0x36,uVar6,iVar2 + 0x3a,0,0,0);
    FUN_00086c78(&local_144,0,0x123);
    FUN_00077914(&local_144,0x123,DAT_00035e84,param_2 + 0x14);
    if ((local_144 & 0xff) == 0) {
      return;
    }
    uVar6 = FUN_0007d3ee();
    iVar2 = FUN_0007d446();
    iVar7 = FUN_0007d3ee();
    iVar3 = FUN_0007d446();
    FUN_00044bd8(0,&local_144,0,uVar6,iVar2 + 0x51,iVar7 + 0x240,iVar3 + 0x51,1,0,0,0,0);
    return;
  case 3:
    uVar6 = FUN_0007d3ee();
    iVar7 = FUN_0007d446();
    FUN_00043484(0x3a,uVar6,iVar7 + 4,0,0,0);
    FUN_00086c78(&local_18c,0,0x48);
LAB_00035cba:
    FUN_00077914(&local_18c,0x48,DAT_00035e88,param_2 + 0xc,param_2 + 0x1c);
    goto LAB_00035cc4;
  case 4:
    uVar6 = FUN_0007d3ee();
    iVar7 = FUN_0007d446();
    uVar5 = 0x39;
LAB_00035e0a:
    FUN_00043484(uVar5,uVar6,iVar7 + 4,0,0,0);
    FUN_00086c78(&local_18c,0,0x48);
    puVar8 = param_2 + 0xc;
    break;
  default:
    uVar6 = FUN_0007d3ee();
    iVar7 = FUN_0007d446();
    FUN_00043484(0x38,uVar6,iVar7 + 4,0,0,0);
    FUN_00086c78(&local_18c,0,0x48);
    puVar8 = param_2 + 0xc;
    if (*(char *)(param_2 + 0x1c) != '\0') goto LAB_00035cba;
  }
  FUN_00077914(&local_18c,0x48,DAT_00035e84,puVar8);
LAB_00035cc4:
  iVar7 = FUN_0007d3ee();
  uVar6 = FUN_0007d446();
  iVar3 = FUN_0007d3ee();
  iVar4 = FUN_0007d446();
  FUN_00044818(0,&local_18c,0,iVar7 + 0x24,uVar6,iVar3 + 0x186,iVar4 + 0x1b,1,0,0,0,0);
  if (*DAT_00035e74 == 0) {
    DEBUG_PRINT(DAT_00035e8c,*param_2,puVar9);
  }
  else {
    FUN_00019c70();
  }
  FUN_000357dc(&local_1ac,*param_2);
  iVar7 = FUN_0007d3ee();
  uVar6 = FUN_0007d446();
  FUN_00043484(0x3c,iVar7 + 0x210,uVar6,0,0,0);
  local_1b4 = 0;
  uStack_1b0 = 0;
  FUN_00086f00(&local_1b4,0,8,DAT_00035e90,param_1);
  iVar7 = FUN_0007d3ee();
  uVar6 = FUN_0007d446();
  iVar3 = FUN_0007d3ee();
  iVar4 = FUN_0007d446();
  FUN_00043e90(0,&local_1b4,0,iVar7 + 0x22c,uVar6,iVar3 + 0x244,iVar4 + 0x1b,1,0,0,0,0);
  FUN_00086c78(&local_144,0,0x123);
  if (iVar2 == 1) {
    FUN_00077914(&local_144,0x123,DAT_00035e84,param_2 + 0x14);
  }
  else {
    if (iVar2 != 4) {
      if (*(char *)(param_2 + 0x14) == '\0') {
        FUN_00077914(&local_144,0x123,DAT_00035f20,puVar9);
      }
      else {
        FUN_00077914(&local_144,0x123,DAT_00035f24,param_2 + 0x14,puVar9);
      }
      if ((local_144 & 0xff) == 0) {
        return;
      }
      uVar6 = FUN_0007d3ee();
      iVar2 = FUN_0007d446();
      iVar7 = FUN_0007d3ee();
      iVar3 = FUN_0007d446();
      goto LAB_00035de8;
    }
    FUN_00077914(&local_144,0x123,DAT_00035f1c,param_2 + 0x14,puVar9);
  }
  if ((local_144 & 0xff) == 0) {
    return;
  }
  uVar6 = FUN_0007d3ee();
  iVar2 = FUN_0007d446();
  iVar7 = FUN_0007d3ee();
  iVar3 = FUN_0007d446();
LAB_00035de8:
  FUN_000451e0(0,&local_144,0,uVar6,iVar2 + 0x36,iVar7 + 0x240,iVar3 + 0x87,3,0,0,0,0);
  return;
}
