/* Reconstructed check_work_mode @ 0x27758  (parity: 30/30 trials, PROVEN) */
#pragma GCC diagnostic ignored "-Wint-conversion"
#pragma GCC diagnostic ignored "-Wpointer-to-int-cast"
#pragma GCC diagnostic ignored "-Wint-to-pointer-cast"
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
typedef unsigned char undefined,undefined1,byte,uchar,uint1;
typedef unsigned short undefined2,ushort,uint2,wchar_t;
typedef unsigned int undefined4,uint,uint3,code_t,undefined3,undefined5,undefined6,undefined7;
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

extern void DEBUG_PRINT(unsigned long, ...);
extern long long FUN_00010840(long long);
extern long long FUN_000167a8(void);
extern long long FUN_00016940(void);
extern void FUN_00019c70(unsigned long, ...);
extern long long FUN_00027448(long long,long long,long long,long long);
extern long long FUN_0002bed0(void);
extern long long FUN_0002eba0(void);
extern long long FUN_000304f0(void);
extern long long FUN_00030c90(void);
extern long long FUN_00032784(void);
extern long long FUN_000327c4(void);
extern long long FUN_0004a890(void);
extern unsigned long long FUN_0007cb2c(void);
extern long long FUN_0007cbfe(long long,long long);
extern long long FUN_0007dada(void);
extern long long change_work_mode_to(long long);
extern long long send_event_status(long long);
extern long long sync_to_slave(long long,long long,long long,long long);
extern long long thunk_FUN_00072908(long long,long long,long long,long long);
typedef long long (*log2_fn)(long long,long long);
typedef long long (*log3_fn)(long long,long long,long long);
typedef long long (*log4_fn)(long long,long long,long long,long long);
#define DAT_00027a6c ((volatile int*)0x200069e8UL)
#define DAT_00027a70 ((volatile int*)0x20018d93UL)
#define DAT_00027a74 ((volatile int*)0x2000230cUL)
#define DAT_00027a78 ((volatile int*)0x20007554UL)
#define DAT_00027a7c 0xa1b00UL
#define DAT_00027a80 0xa0132UL
#define DAT_00027a84 ((volatile int*)0x20018d87UL)
#define DAT_00027a88 ((volatile int*)0x20018d92UL)
#define DAT_00027a8c 0xa014fUL
#define DAT_00027a90 ((volatile int*)0x20018d86UL)
#define DAT_00027a94 0xa01c7UL
#define DAT_00027a98 0xa0169UL
#define DAT_00027a9c 0xa018bUL
#define DAT_00027aa0 0xa01a7UL
#define DAT_00027aa4 0xa01eaUL
#define DAT_00027aa8 ((volatile int*)0x2000302dUL)
#define DAT_00027aac 0xa020eUL
#define DAT_00027ab0 0xa0231UL
#define DAT_00027ab4 0xa024aUL
#define DAT_00027ab8 ((volatile int*)0x20003029UL)
#define DAT_00027abc ((volatile int*)0x20003028UL)
#define DAT_00027ac0 ((volatile int*)0x20018d85UL)
#define DAT_00027ac4 ((volatile int*)0x20018d84UL)
#define DAT_00027ac8 ((volatile int*)0x2000302aUL)
#define DAT_00027cc0 ((volatile int*)0x20003027UL)
#define DAT_00027cc4 ((volatile int*)0x20007554UL)
#define DAT_00027cc8 0xa1b00UL
#define DAT_00027ccc 0xa0266UL
#define DAT_00027cd0 ((volatile int*)0x20018d84UL)
#define DAT_00027cd4 ((volatile int*)0x20003026UL)
#define DAT_00027cd8 ((volatile int*)0x20003028UL)
#define DAT_00027cdc ((volatile int*)0x20018d85UL)
#define DAT_00027ce0 ((volatile int*)0x20003029UL)
#define DAT_00027ce4 0xa030dUL
#define DAT_00027ce8 ((volatile int*)0x20003025UL)
#define DAT_00027cec 0xa028cUL
#define DAT_00027cf0 0xa02abUL
#define _DAT_00027cf4 0xa02ccUL
#define _DAT_00027cf8 (*(volatile int*)0x27cf8UL)
#define _event_id2 event_id2


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void check_work_mode(int param_1,int param_2,int param_3)

{
  bool bVar1;
  int *piVar2;
  byte *pbVar3;
  byte event_id2;
  uint uVar4;
  int iVar5;
  char *pcVar6;
  uint new_box_charging_status;
  byte *pbVar7;
  byte bVar8;
  byte event_id;
  undefined8 uVar9;
  
  uVar4 = FUN_00016940();
  uVar4 = uVar4 & 0xff;
  if (uVar4 < 2) {
    return;
  }
  if (uVar4 == 8) {
    return;
  }
  uVar9 = FUN_0007cb2c();
  if ((int)((ulonglong)uVar9 >> 0x20) < (int)(uint)((uint)uVar9 < 10000)) {
    return;
  }
  iVar5 = FUN_000167a8();
  if ((((*(byte *)(iVar5 + 0xfc4) < 0x83) &&
       (iVar5 = FUN_000167a8(), 0x50 < *(byte *)(iVar5 + 0xfc4))) &&
      (iVar5 = FUN_000167a8(), '\0' < *(char *)(iVar5 + 0xfc8))) &&
     ((iVar5 = FUN_000167a8(), *(byte *)(iVar5 + 0xfc0) < 2 && (param_1 == 0)))) {
    pcVar6 = (char *)FUN_000167a8();
    if (*pcVar6 == '\x01') {
      _event_id2 = FUN_000167a8();
      sync_to_slave(_event_id2,3,0,0);
    }
    else {
      _event_id2 = FUN_000167a8();
      FUN_00027448(_event_id2,5,0,0);
    }
    _event_id2 = FUN_000167a8();
    FUN_0007cbfe(_event_id2,1);
    change_work_mode_to(7);
    return;
  }
  if (*DAT_00027a6c < 0x33) {
    if (*DAT_00027a6c < 0x28) {
      *DAT_00027a90 = 0;
      FUN_000167a8();
      iVar5 = FUN_0002bed0();
      if (iVar5 == 0) {
        bVar8 = 3;
      }
      else {
        iVar5 = FUN_000167a8();
        if (**(char **)(iVar5 + 0x1014) == '\0') {
          bVar8 = 0x3c;
        }
        else {
          bVar8 = 10;
        }
      }
      if ((byte)(*DAT_00027a84 + 1) < bVar8) {
        *DAT_00027a84 = *DAT_00027a84 + 1;
      }
      else {
        *DAT_00027a84 = bVar8;
        *DAT_00027a70 = 0;
        *DAT_00027a88 = 0;
        FUN_0007dada();
        piVar2 = DAT_00027a74;
        if (param_1 == 0) {
          if (uVar4 != 4) {
            _event_id2 = FUN_000167a8();
            FUN_0007cbfe(_event_id2,1);
            change_work_mode_to(4);
            if (0 < *DAT_00027a74) {
              iVar5 = *DAT_00027a78;
              _event_id2 = DAT_00027aa0;
              goto LAB_00027964;
            }
          }
        }
        else if (param_2 == 0) {
          _event_id2 = FUN_000167a8();
          FUN_0007cbfe(_event_id2,1);
          change_work_mode_to(5);
          if (0 < *piVar2) {
            iVar5 = *DAT_00027a78;
            _event_id2 = DAT_00027a9c;
            goto LAB_00027964;
          }
        }
        else {
          _event_id2 = FUN_000167a8();
          FUN_0007cbfe(_event_id2,1);
          change_work_mode_to(6);
          if (0 < *piVar2) {
            iVar5 = *DAT_00027a78;
            _event_id2 = DAT_00027a98;
LAB_00027964:
            if (iVar5 == 0) {
              DEBUG_PRINT(_event_id2,DAT_00027a7c);
            }
            else {
              FUN_00019c70(_event_id2,DAT_00027a7c);
            }
          }
        }
      }
    }
    bVar1 = false;
  }
  else {
    *DAT_00027a70 = 1;
    FUN_0004a890();
    if (uVar4 - 2 < 2) {
      FUN_000167a8();
      iVar5 = FUN_0002bed0();
      if ((iVar5 != 0) && (change_work_mode_to(2), 0 < *DAT_00027a74)) {
        iVar5 = *DAT_00027a78;
        _event_id2 = DAT_00027a8c;
        goto LAB_0002782c;
      }
    }
    else {
      _event_id2 = FUN_000167a8();
      FUN_0007cbfe(_event_id2,0);
      change_work_mode_to(3);
      if (0 < *DAT_00027a74) {
        iVar5 = *DAT_00027a78;
        _event_id2 = DAT_00027a80;
LAB_0002782c:
        if (iVar5 == 0) {
          DEBUG_PRINT(_event_id2,DAT_00027a7c);
        }
        else {
          FUN_00019c70(_event_id2,DAT_00027a7c);
        }
      }
    }
    pbVar7 = DAT_00027a88;
    *DAT_00027a84 = 0;
    bVar8 = *pbVar7 + 1;
    if (bVar8 < 2) {
LAB_00027844:
      *pbVar7 = bVar8;
    }
    else {
      *pbVar7 = 2;
      bVar8 = *DAT_00027a90 + 1;
      pbVar7 = DAT_00027a90;
      if (bVar8 < 10) goto LAB_00027844;
      *DAT_00027a90 = 0;
      iVar5 = FUN_000304f0();
      if (iVar5 != 0) {
        FUN_00030c90();
      }
    }
    bVar1 = true;
  }
  pbVar7 = DAT_00027ce0;
  pcVar6 = DAT_00027ac8;
  piVar2 = DAT_00027a74;
  if (param_3 == 0) {
    *DAT_00027ac8 = -1;
    *pbVar7 = 0xff;
    *DAT_00027cd8 = 0xff;
    *DAT_00027cc0 = 0xff;
    *DAT_00027cd4 = 0xff;
    *DAT_00027ce8 = -1;
    *DAT_00027cdc = 4;
    *DAT_00027cd0 = 4;
    return;
  }
  if ((*DAT_00027ac8 == -1) || (iVar5 = FUN_000167a8(), *(int *)(iVar5 + 0x9b4) == 2)) {
    iVar5 = FUN_000167a8();
    if (*(int *)(iVar5 + 0x9b4) == 2) {
      uVar9 = FUN_000167a8();
      thunk_FUN_00072908((int)uVar9 + 0x9ac,(int)((ulonglong)uVar9 >> 0x20),0xffffffff,0xffffffff);
    }
    if (0 < *piVar2) {
      if (*DAT_00027a78 == 0) {
        DEBUG_PRINT(DAT_00027a94,DAT_00027a7c);
      }
      else {
        FUN_00019c70(DAT_00027a94,DAT_00027a7c);
      }
    }
    send_event_status(0x11);
    *pcVar6 = -2;
    return;
  }
  iVar5 = *piVar2;
  if (param_1 == 0) {
    if (bVar1) {
      if (0 < iVar5) {
        if (*DAT_00027a78 == 0) {
          DEBUG_PRINT(DAT_00027ab0,DAT_00027a7c);
        }
        else {
          FUN_00019c70(DAT_00027ab0,DAT_00027a7c);
        }
      }
      event_id = 0x6;
    }
    else {
      if (0 < iVar5) {
        if (*DAT_00027a78 == 0) {
          DEBUG_PRINT(DAT_00027ab4,DAT_00027a7c);
        }
        else {
          FUN_00019c70(DAT_00027ab4,DAT_00027a7c);
        }
      }
      event_id = 0x7;
    }
    *DAT_00027ab8 = 0xff;
    *DAT_00027abc = 0xff;
    *DAT_00027ac0 = 4;
    *DAT_00027ac4 = 4;
  }
  else if (param_2 == 0) {
    if (0 < iVar5) {
      if (*DAT_00027a78 == 0) {
        DEBUG_PRINT(DAT_00027aac,DAT_00027a7c);
      }
      else {
        FUN_00019c70(DAT_00027aac,DAT_00027a7c);
      }
    }
    event_id = 0x8;
  }
  else {
    if (0 < iVar5) {
      if (*DAT_00027a78 == 0) {
        DEBUG_PRINT(DAT_00027aa4,DAT_00027a7c);
      }
      else {
        FUN_00019c70(DAT_00027aa4,DAT_00027a7c);
      }
    }
    event_id = 0xb;
  }
  pbVar7 = DAT_00027aa8;
  if (*DAT_00027aa8 != event_id) {
    send_event_status(event_id);
    *pbVar7 = event_id;
    return;
  }
  iVar5 = FUN_000167a8();
  pbVar3 = DAT_00027cd4;
  pbVar7 = DAT_00027cd0;
  bVar8 = *(byte *)(iVar5 + 0xfc0);
  if ((*DAT_00027cc0 != bVar8) && (bVar8 < 0x65)) {
    *DAT_00027cc0 = bVar8;
    if (0 < *piVar2) {
      if (*DAT_00027cc4 == 0) {
        DEBUG_PRINT(DAT_00027ccc,DAT_00027cc8);
      }
      else {
        FUN_00019c70(DAT_00027ccc,DAT_00027cc8);
      }
    }
    _event_id2 = 0xa;
    goto LAB_00027af8;
  }
  if (param_1 == 0) {
    if (*DAT_00027cd4 != 0) {
LAB_00027b70:
      uVar4 = 0;
LAB_00027b72:
      if ((byte)(*pbVar7 + 1) < 5) {
        *pbVar7 = *pbVar7 + 1;
        return;
      }
      *pbVar7 = 0;
      iVar5 = FUN_000167a8();
      *(byte *)(iVar5 + 0x794) = (byte)uVar4;
      *pbVar3 = (byte)uVar4;
      send_event_status(9);
      if (*piVar2 < 1) {
        return;
      }
      if (*DAT_00027cc4 == 0) {
        DEBUG_PRINT(DAT_00027cec,DAT_00027cc8,uVar4);
        return;
      }
      FUN_00019c70(DAT_00027cec,DAT_00027cc8,uVar4);
      return;
    }
    *DAT_00027cd0 = 0;
  }
  else {
    uVar4 = FUN_0002eba0();
    if (uVar4 == 0) {
      if (*pbVar3 != 0) goto LAB_00027b70;
    }
    else {
      *pbVar7 = 4;
      if (*pbVar3 != uVar4) goto LAB_00027b72;
    }
    *pbVar7 = 0;
    new_box_charging_status = FUN_00032784();
    pbVar3 = DAT_00027cdc;
    pbVar7 = DAT_00027cd8;
    if (*DAT_00027cd8 != new_box_charging_status) {
      bVar8 = *DAT_00027cdc;
      *DAT_00027cdc = bVar8 + 1;
      if (4 < (byte)(bVar8 + 1)) {
        iVar5 = *piVar2;
        *pbVar3 = 0;
        *pbVar7 = (byte)new_box_charging_status;
        if (0 < iVar5) {
          if (*DAT_00027cc4 == 0) {
            DEBUG_PRINT(DAT_00027cf0,DAT_00027cc8,new_box_charging_status);
          }
          else {
            FUN_00019c70(DAT_00027cf0,DAT_00027cc8,new_box_charging_status);
          }
        }
        send_event_status(0xe);
      }
      if (*piVar2 < 1) {
        return;
      }
      uVar4 = (uint)*pbVar7;
      if (*DAT_00027cc4 == 0) {
        DEBUG_PRINT(_DAT_00027cf4,DAT_00027cc8,uVar4,new_box_charging_status);
        return;
      }
      ((log4_fn)FUN_00019c70)(_DAT_00027cf4,DAT_00027cc8,uVar4,new_box_charging_status);
      return;
    }
    *DAT_00027cdc = 0;
    uVar4 = FUN_000327c4();
    if ((*DAT_00027ce0 != uVar4) && (uVar4 < 0x65)) {
      iVar5 = *piVar2;
      *DAT_00027ce0 = (byte)uVar4;
      if (0 < iVar5) {
        if (*DAT_00027cc4 == 0) {
          DEBUG_PRINT(DAT_00027ce4,DAT_00027cc8,uVar4,uVar4);
        }
        else {
          ((log3_fn)FUN_00019c70)(DAT_00027ce4,DAT_00027cc8,uVar4);
        }
      }
      _event_id2 = 0xf;
      goto LAB_00027af8;
    }
    if (0 < *piVar2) {
      if (*DAT_00027cc4 == 0) {
        DEBUG_PRINT(_DAT_00027cf8,DAT_00027cc8,(uint)*DAT_00027ce0,uVar4);
      }
      else {
        ((log2_fn)FUN_00019c70)(_DAT_00027cf8,DAT_00027cc8);
      }
    }
  }
  pcVar6 = (char *)FUN_000167a8();
  if ((*pcVar6 == '\x01') && (iVar5 = FUN_000167a8(), *(int *)(iVar5 + 0xf90) != 0)) {
    iVar5 = FUN_000167a8();
    iVar5 = FUN_00010840(iVar5 + 0xf80);
    if ((iVar5 != 0xff) &&
       (iVar5 = FUN_000167a8(), pcVar6 = DAT_00027ce8, *(char *)(iVar5 + 0xed5) != *DAT_00027ce8)) {
      iVar5 = FUN_000167a8();
      _event_id2 = 0x12;
      *pcVar6 = *(char *)(iVar5 + 0xed5);
LAB_00027af8:
      send_event_status(_event_id2);
      return;
    }
  }
  return;
}
