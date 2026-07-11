/* Reconstructed FUN_000417f8 @ 0x417f8  (parity: 300/300 trials, PROVEN) */
typedef unsigned char      undefined1;
typedef unsigned int       undefined4;
typedef unsigned long long undefined8;
typedef unsigned int       uint;
typedef unsigned char      byte;
typedef unsigned long long ulonglong;

/* external callee oracles (order-keyed by the parity harness) */
extern unsigned long long FUN_0007d382(void);
extern int  FUN_000167a8(void);
extern int  FUN_00023ee0(void);
extern int  FUN_0007d3ee(void);
extern int  FUN_0007d446(void);
extern int  FUN_0007d4b2(int);
extern int  FUN_0000ef12(void);
extern void FUN_00086c78(void*, int, int);
extern void FUN_00043308(void);
extern void FUN_0004334c(int,int,int,int,int,int,int);
extern void FUN_00043484(int,int,int,int,int,int);
extern void FUN_000435d4(int,int,int,void*,int);
extern void FUN_00043e90(int,int,int,int,int,int,int,int,int,int,int,int);
extern void send_event_status(int);

/* dereferenced byte globals (absolute RAM addresses) */
#define DAT_00041a70 ((volatile unsigned char *)0x2001cdd0)
#define DAT_00041a74 ((volatile unsigned char *)0x2001cdce)
#define DAT_00041a78 ((volatile unsigned char *)0x2001cdd1)
#define DAT_00041db0 ((volatile unsigned char *)0x2001cdd1)
#define DAT_00041db4 ((volatile unsigned char *)0x2001cdd2)
#define DAT_000421f4 ((volatile unsigned char *)0x2001cdd1)
#define DAT_00042480 ((volatile unsigned char *)0x2001cdce)
#define DAT_00042484 ((volatile unsigned char *)0x2001cdd2)
#define DAT_000427b0 ((volatile unsigned char *)0x2001cdd1)
#define DAT_000427b4 ((volatile unsigned char *)0x2001cdd2)
#define DAT_000429f4 ((volatile unsigned char *)0x2001cdd0)

/* rodata pointer constants passed as arguments */
#define DAT_00041db8 ((unsigned int)0x000aa608)
#define DAT_00041dbc ((unsigned int)0x000aa60e)
#define DAT_00041dc0 ((unsigned int)0x000f212c)
#define DAT_00041dc4 ((unsigned int)0x000f341d)
#define DAT_00041dc8 ((unsigned int)0x000aa604)
#define DAT_000421f0 ((unsigned int)0x000f7b6f)
#define DAT_000421f8 ((unsigned int)0x000f7a30)
#define DAT_000421fc ((unsigned int)0x000aa604)
#define DAT_00042200 ((unsigned int)0x000aa600)
#define DAT_000427b8 ((unsigned int)0x000f341d)
#define DAT_000427bc ((unsigned int)0x000f7a30)

void FUN_000417f8(void)

{
  uint uVar1;
  uint uVar2;
  volatile byte *pbVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  int iVar11;
  undefined4 uVar12;
  undefined1 uVar13;
  uint uVar14;
  bool bVar15;
  undefined8 uVar16;
  undefined4 local_428;
  undefined1 auStack_424 [1024];
  
  local_428 = 0;
  FUN_00086c78(auStack_424,0,0x3fc);
  iVar4 = FUN_000167a8();
  pbVar3 = DAT_000429f4;
  switch(*(undefined1 *)(*(int *)(iVar4 + 0x1014) + 2)) {
  case 0:
    uVar16 = FUN_0007d382();
    iVar4 = FUN_000167a8();
    uVar14 = *(uint *)(*(int *)(iVar4 + 0x1014) + 4);
    uVar1 = (int)((ulonglong)uVar16 >> 0x20) - *(int *)(*(int *)(iVar4 + 0x1014) + 8);
    uVar2 = (uint)((uint)uVar16 < uVar14);
    if (uVar1 == uVar2 && (uint)(4000 < (uint)uVar16 - uVar14) <= uVar1 - uVar2) {
      return;
    }
    iVar4 = FUN_000167a8();
    *(char *)(*(int *)(iVar4 + 0x1014) + 3) = *(char *)(*(int *)(iVar4 + 0x1014) + 3) + '\x01';
    iVar4 = FUN_000167a8();
    if (*(byte *)(*(int *)(iVar4 + 0x1014) + 3) < 2) {
      return;
    }
    iVar4 = FUN_000167a8();
    uVar13 = 0;
    iVar5 = *(int *)(iVar4 + 0x1014);
    goto LAB_000418a6;
  case 3:
    iVar4 = FUN_000167a8();
    iVar5 = FUN_000167a8();
    pbVar3 = DAT_00041a70;
    *(undefined1 *)(*(int *)(iVar5 + 0x1014) + 3) = *(undefined1 *)(iVar4 + 0xee4);
    if (5 < *pbVar3) {
      return;
    }
    if (*pbVar3 != 0) {
      uVar16 = FUN_0007d382();
      iVar4 = FUN_000167a8();
      uVar14 = *(uint *)(*(int *)(iVar4 + 0x1014) + 4);
      uVar1 = (int)((ulonglong)uVar16 >> 0x20) - *(int *)(*(int *)(iVar4 + 0x1014) + 8);
      uVar2 = (uint)((uint)uVar16 < uVar14);
      if (uVar1 == uVar2 && (uint)(1000 < (uint)uVar16 - uVar14) <= uVar1 - uVar2) {
        return;
      }
    }
    uVar12 = 0x10;
    *pbVar3 = *pbVar3 + 1;
    goto LAB_000418d2;
  case 4:
    iVar4 = FUN_0007d3ee();
    iVar5 = FUN_0007d446();
    iVar5 = iVar5 + 0x70;
    iVar4 = iVar4 + 0x8a;
    goto LAB_00041938;
  case 5:
  case 0x14:
  case 0x15:
    iVar4 = FUN_000167a8();
    iVar5 = FUN_000167a8();
    *(undefined1 *)(*(int *)(iVar5 + 0x1014) + 3) = *(undefined1 *)(iVar4 + 0xee4);
    if (*DAT_00041a74 == '\x01') {
      iVar4 = FUN_000167a8();
      if ((*(char *)(*(int *)(iVar4 + 0x1014) + 2) == '\x05') && (*DAT_00041a78 == '\0')) {
        uVar16 = FUN_0007d382();
        iVar4 = FUN_000167a8();
        uVar14 = *(uint *)(*(int *)(iVar4 + 0x1014) + 4);
        uVar1 = (int)((ulonglong)uVar16 >> 0x20) - *(int *)(*(int *)(iVar4 + 0x1014) + 8);
        uVar2 = (uint)((uint)uVar16 < uVar14);
        if (uVar1 == uVar2 && (uint)(499 < (uint)uVar16 - uVar14) <= uVar1 - uVar2) {
          return;
        }
      }
      iVar4 = FUN_00023ee0();
      if (iVar4 == 6) {
        iVar4 = FUN_0007d3ee();
        iVar5 = FUN_0007d446();
        FUN_0004334c(2,iVar4 + 0x42,iVar5 + 0x70,0,0,0,0);
        uVar12 = FUN_0007d4b2(0x13);
        iVar4 = FUN_0007d3ee();
        iVar6 = FUN_0007d446();
        iVar5 = FUN_0007d3ee();
        iVar7 = FUN_0007d446();
        iVar4 = iVar4 + 0x66;
      }
      else {
        iVar4 = FUN_0007d3ee();
        iVar5 = FUN_0007d446();
        FUN_0004334c(2,iVar4 + 0x82,iVar5 + 0x70,0,0,0,0);
        uVar12 = FUN_0007d4b2(0x13);
        iVar4 = FUN_0007d3ee();
        iVar6 = FUN_0007d446();
        iVar5 = FUN_0007d3ee();
        iVar7 = FUN_0007d446();
        iVar4 = iVar4 + 0xa6;
      }
      FUN_00043e90(0,uVar12,0,iVar4,iVar6 + 0x6d,iVar5 + 0x240,iVar7 + 0x88,1,0,0,0,0);
      return;
    }
    if (*DAT_00041a74 != '\x02') {
      return;
    }
    uVar16 = FUN_0007d382();
    iVar4 = FUN_000167a8();
    uVar14 = *(uint *)(*(int *)(iVar4 + 0x1014) + 4);
    uVar1 = (int)((ulonglong)uVar16 >> 0x20) - *(int *)(*(int *)(iVar4 + 0x1014) + 8);
    uVar2 = (uint)((uint)uVar16 < uVar14);
    if ((uVar1 != uVar2 || uVar1 - uVar2 < (uint)(2000 < (uint)uVar16 - uVar14)) ||
       (*DAT_00041db0 != '\0')) {
      if (*DAT_00041db4 == '\0') {
        *DAT_00041db4 = '\x01';
        uVar12 = FUN_0007d4b2(0x14);
        uVar8 = FUN_0007d3ee();
        uVar9 = FUN_0007d446();
        iVar4 = FUN_0007d3ee();
        iVar5 = FUN_0007d446();
        FUN_0007d4b2(0x14);
        uVar10 = FUN_0000ef12();
        FUN_00043e90(0,uVar12,3,uVar8,uVar9,iVar4 + 0x76,iVar5 + 0x1b,1,uVar10,0,0,0);
        uVar12 = FUN_0007d3ee();
        iVar4 = FUN_0007d446();
        iVar5 = FUN_0007d3ee();
        iVar6 = FUN_0007d446();
        FUN_00043e90(0,DAT_00041db8,1,uVar12,iVar4 + 0x1b,iVar5 + 0x68,iVar6 + 0x42,1,5,0,0,0);
        iVar4 = FUN_0007d3ee();
        iVar5 = FUN_0007d446();
        FUN_000435d4(0x29,iVar4 + 0xa6,iVar5 + 4,&local_428,0x55);
        iVar4 = FUN_0007d3ee();
        iVar5 = FUN_0007d446();
        iVar6 = FUN_0007d3ee();
        iVar7 = FUN_0007d446();
        FUN_00043e90(0,DAT_00041dbc,3,iVar4 + 0xc2,iVar5 + 3,iVar6 + 0xea,iVar7 + 0x1e,1,2,0,0,0);
        iVar4 = FUN_0007d3ee();
        iVar5 = FUN_0007d446();
        iVar6 = FUN_0007d3ee();
        iVar7 = FUN_0007d446();
        FUN_00043e90(0,DAT_00041dc0,3,iVar4 + 0xde,iVar5 + 3,iVar6 + 0xec,iVar7 + 0x1e,1,1,0,0,0);
        iVar4 = FUN_000167a8();
        bVar15 = *(char *)(*(int *)(iVar4 + 0x1014) + 2) != '\x05';
        if (bVar15) {
          iVar4 = FUN_0007d3ee();
          iVar5 = FUN_0007d446();
          FUN_000435d4(0x3c,iVar4 + 0xa6,iVar5 + 0x23,&local_428,0x55);
          iVar6 = FUN_0007d3ee();
          iVar7 = FUN_0007d446();
          iVar4 = FUN_0007d3ee();
          iVar5 = FUN_0007d446();
          uVar12 = DAT_000421f8;
        }
        else {
          iVar4 = FUN_0007d3ee();
          iVar5 = FUN_0007d446();
          FUN_00043484(0x3c,iVar4 + 0xa6,iVar5 + 0x23,0,0,0);
          iVar6 = FUN_0007d3ee();
          iVar7 = FUN_0007d446();
          iVar4 = FUN_0007d3ee();
          iVar5 = FUN_0007d446();
          uVar12 = DAT_00041dc4;
        }
        FUN_00043e90(0,uVar12,3,iVar6 + 0xc2,iVar7 + 0x23,iVar4 + 0xd6,iVar5 + 0x3e,1,bVar15,0,0,0);
        uVar12 = FUN_0007d3ee();
        iVar4 = FUN_0007d446();
        FUN_000435d4(0x39,uVar12,iVar4 + 0x51,&local_428,0x55);
        uVar12 = FUN_0007d4b2(0x16);
        iVar4 = FUN_0007d3ee();
        iVar5 = FUN_0007d446();
        iVar6 = FUN_0007d3ee();
        iVar7 = FUN_0007d446();
        FUN_0007d4b2(0x16);
        uVar8 = FUN_0000ef12();
        FUN_00043e90(0,uVar12,0,iVar4 + 0x1c,iVar5 + 0x51,iVar6 + 0xf2,iVar7 + 0x6c,1,uVar8,0,0,0);
        uVar12 = FUN_0007d4b2(0x15);
        uVar8 = FUN_0007d3ee();
        iVar4 = FUN_0007d446();
        iVar5 = FUN_0007d3ee();
        iVar6 = FUN_0007d446();
        FUN_0007d4b2(0x15);
        uVar9 = FUN_0000ef12();
        FUN_00043e90(0,uVar12,0,uVar8,iVar4 + 0x6d,iVar5 + 0xf2,iVar6 + 0x88,1,uVar9,0,0,0);
        iVar4 = FUN_000167a8();
        if (*(char *)(*(int *)(iVar4 + 0x1014) + 2) == '\x14') {
          iVar4 = FUN_0007d3ee();
          iVar5 = FUN_0007d446();
          FUN_00043484(0x3b,iVar4 + 0x108,iVar5 + 1,0,0,0);
          uVar12 = FUN_0007d4b2(0x17);
          iVar4 = FUN_0007d3ee();
          uVar8 = FUN_0007d446();
          iVar5 = FUN_0007d3ee();
          iVar6 = FUN_0007d446();
          FUN_00043e90(0,uVar12,0,iVar4 + 0x126,uVar8,iVar5 + 0x202,iVar6 + 0x1b,1,0,0,0,0);
          iVar7 = FUN_0007d3ee();
          iVar6 = FUN_0007d446();
          iVar5 = FUN_0007d3ee();
          iVar4 = FUN_0007d446();
          uVar8 = 0;
          uVar12 = DAT_00041dc8;
        }
        else {
          iVar4 = FUN_0007d3ee();
          iVar5 = FUN_0007d446();
          FUN_000435d4(0x3b,iVar4 + 0x108,iVar5 + 1,&local_428,0x55);
          uVar12 = FUN_0007d4b2(0x17);
          iVar4 = FUN_0007d3ee();
          uVar8 = FUN_0007d446();
          iVar5 = FUN_0007d3ee();
          iVar6 = FUN_0007d446();
          FUN_0007d4b2(0x17);
          uVar9 = FUN_0000ef12();
          FUN_00043e90(0,uVar12,0,iVar4 + 0x126,uVar8,iVar5 + 0x202,iVar6 + 0x1b,1,uVar9,0,0,0);
          iVar4 = FUN_000167a8();
          uVar12 = DAT_000421fc;
          if (*(char *)(*(int *)(iVar4 + 0x1014) + 2) == '\x15') {
            uVar12 = DAT_00042200;
          }
          iVar7 = FUN_0007d3ee();
          iVar6 = FUN_0007d446();
          iVar5 = FUN_0007d3ee();
          iVar4 = FUN_0007d446();
          uVar8 = 3;
        }
        FUN_00043e90(0,uVar12,3,iVar7 + 0x210,iVar6 + 1,iVar5 + 0x234,iVar4 + 0x1c,1,uVar8,0,0,0);
        iVar4 = FUN_000167a8();
        if (*(char *)(*(int *)(iVar4 + 0x1014) + 2) == '\x15') {
          uVar12 = 0xe;
        }
        else {
          uVar12 = 0x18;
        }
        uVar12 = FUN_0007d4b2(uVar12);
        iVar4 = FUN_0007d3ee();
        iVar5 = FUN_0007d446();
        iVar6 = FUN_0007d3ee();
        iVar7 = FUN_0007d446();
        iVar11 = FUN_000167a8();
        if (*(char *)(*(int *)(iVar11 + 0x1014) + 2) == '\x15') {
          uVar8 = 0xe;
        }
        else {
          uVar8 = 0x18;
        }
        FUN_0007d4b2(uVar8);
        uVar8 = FUN_0000ef12();
        FUN_00043e90(0,uVar12,0,iVar4 + 0x108,iVar5 + 0x1b,iVar6 + 0x232,iVar7 + 0x87,4,uVar8,0,0,0)
        ;
        iVar4 = FUN_0007d3ee();
        uVar12 = FUN_0007d446();
        FUN_000435d4(0x4e,iVar4 + 0xfc,uVar12,&local_428,0x55);
        iVar4 = FUN_0007d3ee();
        uVar12 = FUN_0007d446();
        FUN_000435d4(0x4f,iVar4 + 0x23e,uVar12,&local_428,0x55);
        uVar12 = FUN_0007d3ee();
        iVar4 = FUN_0007d446();
        iVar5 = FUN_0007d3ee();
        iVar6 = FUN_0007d446();
        FUN_00043e90(0,DAT_000421f0,0,uVar12,iVar4 + 0x6d,iVar5 + 0x240,iVar6 + 0x88,1,0,0,0,0);
        iVar4 = FUN_000167a8();
        if (*(char *)(*(int *)(iVar4 + 0x1014) + 2) == '\x05') {
          iVar4 = FUN_00023ee0();
          if (iVar4 == 6) {
            uVar12 = FUN_0007d4b2(9);
            iVar4 = FUN_0007d3ee();
            iVar5 = FUN_0007d446();
            iVar6 = FUN_0007d3ee();
            iVar7 = FUN_0007d446();
            FUN_00043e90(0,uVar12,0,iVar4 + 0x5c,iVar5 + 0x6d,iVar6 + 0x240,iVar7 + 0x88,1,0,0,0,0);
            iVar4 = FUN_0007d3ee();
            iVar5 = FUN_0007d446();
            iVar4 = iVar4 + 0xae;
          }
          else {
            uVar12 = FUN_0007d4b2(9);
            iVar4 = FUN_0007d3ee();
            iVar5 = FUN_0007d446();
            iVar6 = FUN_0007d3ee();
            iVar7 = FUN_0007d446();
            FUN_00043e90(0,uVar12,0,iVar4 + 0x6a,iVar5 + 0x6d,iVar6 + 0x240,iVar7 + 0x88,1,0,0,0,0);
            iVar4 = FUN_0007d3ee();
            iVar5 = FUN_0007d446();
            iVar4 = iVar4 + 0xca;
          }
          uVar12 = 0x7a;
        }
        else {
          iVar4 = FUN_000167a8();
          if (*(char *)(*(int *)(iVar4 + 0x1014) + 2) != '\x14') {
            iVar4 = FUN_000167a8();
            if (*(char *)(*(int *)(iVar4 + 0x1014) + 2) == '\x15') {
              iVar4 = FUN_00023ee0();
              if (iVar4 == 6) {
                uVar12 = FUN_0007d4b2(0xf);
                iVar4 = FUN_0007d3ee();
                iVar5 = FUN_0007d446();
                iVar6 = FUN_0007d3ee();
                iVar7 = FUN_0007d446();
                iVar4 = iVar4 + 100;
              }
              else {
                uVar12 = FUN_0007d4b2(0xf);
                iVar4 = FUN_0007d3ee();
                iVar5 = FUN_0007d446();
                iVar6 = FUN_0007d3ee();
                iVar7 = FUN_0007d446();
                iVar4 = iVar4 + 0x92;
              }
              FUN_00043e90(0,uVar12,0,iVar4,iVar5 + 0x6d,iVar6 + 0x240,iVar7 + 0x88,1,0,0,0,0);
            }
            goto LAB_00041f3a;
          }
          uVar12 = FUN_0007d4b2(0xb);
          iVar4 = FUN_0007d3ee();
          iVar5 = FUN_0007d446();
          iVar6 = FUN_0007d3ee();
          iVar7 = FUN_0007d446();
          FUN_00043e90(0,uVar12,0,iVar4 + 0x54,iVar5 + 0x6d,iVar6 + 0x240,iVar7 + 0x88,1,0,0,0,0);
          iVar4 = FUN_00023ee0();
          if (iVar4 == 6) {
            iVar4 = FUN_0007d3ee();
            iVar5 = FUN_0007d446();
            iVar4 = iVar4 + 0xaa;
          }
          else {
            iVar4 = FUN_0007d3ee();
            iVar5 = FUN_0007d446();
            iVar4 = iVar4 + 0xb2;
          }
          uVar12 = 0x7b;
        }
        FUN_00043484(uVar12,iVar4,iVar5 + 0x87,0,0,0);
      }
LAB_00041f3a:
      iVar4 = FUN_000167a8();
      if (*(char *)(*(int *)(iVar4 + 0x1014) + 2) == '\x05') {
        iVar4 = FUN_00023ee0();
        if (iVar4 == 6) {
          iVar4 = FUN_0007d3ee();
          iVar5 = FUN_0007d446();
          iVar5 = iVar5 + 0x70;
          iVar4 = iVar4 + 0x38;
        }
        else {
          iVar4 = FUN_0007d3ee();
          iVar5 = FUN_0007d446();
          iVar5 = iVar5 + 0x70;
          iVar4 = iVar4 + 0x46;
        }
      }
      else {
        iVar4 = FUN_000167a8();
        if (*(char *)(*(int *)(iVar4 + 0x1014) + 2) != '\x14') {
          iVar4 = FUN_000167a8();
          if (*(char *)(*(int *)(iVar4 + 0x1014) + 2) != '\x15') goto LAB_00041f76;
          iVar4 = FUN_00023ee0();
          if (iVar4 == 6) {
            iVar4 = FUN_0007d3ee();
            iVar5 = FUN_0007d446();
            iVar5 = iVar5 + 0x70;
            iVar4 = iVar4 + 0x40;
          }
          else {
            iVar4 = FUN_0007d3ee();
            iVar5 = FUN_0007d446();
            iVar5 = iVar5 + 0x70;
            iVar4 = iVar4 + 0x6e;
          }
          goto LAB_000422ba;
        }
        iVar4 = FUN_0007d3ee();
        iVar5 = FUN_0007d446();
        iVar5 = iVar5 + 0x70;
        iVar4 = iVar4 + 0x30;
      }
LAB_00041f70:
      uVar12 = 0xb;
LAB_00041f72:
      FUN_0004334c(uVar12,iVar4,iVar5,0,0,0,0);
    }
LAB_00041f76:
    iVar4 = FUN_000167a8();
    if (*(char *)(*(int *)(iVar4 + 0x1014) + 3) == '\x01') {
      *DAT_000421f4 = 1;
    }
    break;
  case 6:
  case 0x13:
    iVar4 = FUN_000167a8();
    iVar5 = FUN_000167a8();
    *(undefined1 *)(*(int *)(iVar5 + 0x1014) + 3) = *(undefined1 *)(iVar4 + 0xee4);
    if (*DAT_00042480 != '\x01') {
      if (*DAT_00042480 != '\x02') {
        return;
      }
      uVar16 = FUN_0007d382();
      iVar4 = FUN_000167a8();
      uVar14 = *(uint *)(*(int *)(iVar4 + 0x1014) + 4);
      uVar1 = (int)((ulonglong)uVar16 >> 0x20) - *(int *)(*(int *)(iVar4 + 0x1014) + 8);
      uVar2 = (uint)((uint)uVar16 < uVar14);
      if ((uVar1 == uVar2 && (uint)(2000 < (uint)uVar16 - uVar14) <= uVar1 - uVar2) &&
         (*DAT_000427b0 == '\0')) goto LAB_00041f76;
      if (*DAT_000427b4 == '\0') {
        *DAT_000427b4 = '\x01';
        iVar4 = FUN_000167a8();
        if (-1 < (int)((uint)*(byte *)(*(int *)(iVar4 + 0x1014) + 0x1f) << 0x1d)) {
          send_event_status(0x15);
          iVar4 = FUN_000167a8();
          *(byte *)(*(int *)(iVar4 + 0x1014) + 0x1f) =
               *(byte *)(*(int *)(iVar4 + 0x1014) + 0x1f) | 4;
        }
        iVar4 = FUN_000167a8();
        if (*(char *)(*(int *)(iVar4 + 0x1014) + 2) == '\x06') {
          iVar4 = FUN_0007d3ee();
          iVar5 = FUN_0007d446();
          FUN_000435d4(0x3c,iVar4 + 0x212,iVar5 + 4,&local_428,0x55);
          iVar4 = FUN_0007d3ee();
          iVar5 = FUN_0007d446();
          iVar6 = FUN_0007d3ee();
          iVar7 = FUN_0007d446();
          uVar8 = 1;
          uVar12 = DAT_000427b8;
LAB_00042560:
          FUN_00043e90(0,uVar12,3,iVar4 + 0x22e,iVar5 + 3,iVar6 + 0x23e,iVar7 + 0x1e,1,uVar8,0,0,0);
        }
        else {
          iVar4 = FUN_000167a8();
          if (*(char *)(*(int *)(iVar4 + 0x1014) + 2) == '\x13') {
            iVar4 = FUN_0007d3ee();
            iVar5 = FUN_0007d446();
            FUN_00043484(0x3c,iVar4 + 0x212,iVar5 + 4,0,0,0);
            iVar4 = FUN_0007d3ee();
            iVar5 = FUN_0007d446();
            iVar6 = FUN_0007d3ee();
            iVar7 = FUN_0007d446();
            uVar8 = 0;
            uVar12 = DAT_000427bc;
            goto LAB_00042560;
          }
        }
        uVar12 = FUN_0007d3ee();
        iVar4 = FUN_0007d446();
        FUN_000435d4(0x38,uVar12,iVar4 + 4,&local_428,0x55);
        uVar12 = FUN_0007d4b2(0x1a);
        iVar4 = FUN_0007d3ee();
        iVar5 = FUN_0007d446();
        iVar6 = FUN_0007d3ee();
        iVar7 = FUN_0007d446();
        FUN_0007d4b2(0x1a);
        uVar8 = FUN_0000ef12();
        FUN_00043e90(0,uVar12,0,iVar4 + 0x24,iVar5 + 3,iVar6 + 0x150,iVar7 + 0x1e,1,uVar8,0,0,0);
        iVar4 = FUN_000167a8();
        if (*(char *)(*(int *)(iVar4 + 0x1014) + 2) == '\x06') {
          uVar12 = FUN_0007d4b2(0x1c);
          uVar8 = FUN_0007d3ee();
          iVar4 = FUN_0007d446();
          iVar5 = FUN_0007d3ee();
          iVar6 = FUN_0007d446();
          uVar9 = 0x1c;
LAB_00042606:
          FUN_0007d4b2(uVar9);
          uVar9 = FUN_0000ef12();
          FUN_00043e90(0,uVar12,0,uVar8,iVar4 + 0x37,iVar5 + 0x240,iVar6 + 0x6d,2,uVar9,0,0,0);
        }
        else {
          iVar4 = FUN_000167a8();
          if (*(char *)(*(int *)(iVar4 + 0x1014) + 2) == '\x13') {
            uVar12 = FUN_0007d4b2(0xc);
            uVar8 = FUN_0007d3ee();
            iVar4 = FUN_0007d446();
            iVar5 = FUN_0007d3ee();
            iVar6 = FUN_0007d446();
            uVar9 = 0xc;
            goto LAB_00042606;
          }
        }
        iVar4 = FUN_000167a8();
        if (*(char *)(*(int *)(iVar4 + 0x1014) + 2) == '\x06') {
          iVar4 = FUN_00023ee0();
          if (iVar4 == 6) {
            uVar12 = FUN_0007d4b2(0x10);
            iVar4 = FUN_0007d3ee();
            iVar5 = FUN_0007d446();
            iVar6 = FUN_0007d3ee();
            iVar7 = FUN_0007d446();
            iVar4 = iVar4 + 0x34;
          }
          else {
            uVar12 = FUN_0007d4b2(0x10);
            iVar4 = FUN_0007d3ee();
            iVar5 = FUN_0007d446();
            iVar6 = FUN_0007d3ee();
            iVar7 = FUN_0007d446();
            iVar4 = iVar4 + 0x72;
          }
          FUN_00043e90(0,uVar12,0,iVar4,iVar5 + 0x6d,iVar6 + 0x240,iVar7 + 0x88,1,0,0,0,0);
        }
        else {
          iVar4 = FUN_000167a8();
          if (*(char *)(*(int *)(iVar4 + 0x1014) + 2) == '\x13') {
            iVar4 = FUN_00023ee0();
            if (iVar4 == 6) {
              uVar12 = FUN_0007d4b2(10);
              iVar4 = FUN_0007d3ee();
              iVar5 = FUN_0007d446();
              iVar6 = FUN_0007d3ee();
              iVar7 = FUN_0007d446();
              FUN_00043e90(0,uVar12,0,iVar4 + 0x8a,iVar5 + 0x6d,iVar6 + 0x240,iVar7 + 0x88,1,0,0,0,0
                          );
              iVar4 = FUN_0007d3ee();
              iVar5 = FUN_0007d446();
              iVar4 = iVar4 + 0xdc;
            }
            else {
              uVar12 = FUN_0007d4b2(10);
              iVar4 = FUN_0007d3ee();
              iVar5 = FUN_0007d446();
              iVar6 = FUN_0007d3ee();
              iVar7 = FUN_0007d446();
              FUN_00043e90(0,uVar12,0,iVar4 + 0x94,iVar5 + 0x6d,iVar6 + 0x240,iVar7 + 0x88,1,0,0,0,0
                          );
              iVar4 = FUN_0007d3ee();
              iVar5 = FUN_0007d446();
              iVar4 = iVar4 + 0xf4;
            }
            FUN_00043484(0x7a,iVar4,iVar5 + 0x87,0,0,0);
          }
        }
      }
      iVar4 = FUN_000167a8();
      if (*(char *)(*(int *)(iVar4 + 0x1014) + 2) == '\x06') {
        iVar4 = FUN_00023ee0();
        if (iVar4 == 6) {
          iVar4 = FUN_0007d3ee();
          iVar5 = FUN_0007d446();
          iVar5 = iVar5 + 0x70;
          iVar4 = iVar4 + 0x10;
        }
        else {
          iVar4 = FUN_0007d3ee();
          iVar5 = FUN_0007d446();
          iVar5 = iVar5 + 0x70;
          iVar4 = iVar4 + 0x4e;
        }
LAB_000422ba:
        uVar12 = 3;
        goto LAB_00041f72;
      }
      iVar4 = FUN_000167a8();
      if (*(char *)(*(int *)(iVar4 + 0x1014) + 2) == '\x13') {
        iVar4 = FUN_00023ee0();
        if (iVar4 == 6) {
          iVar4 = FUN_0007d3ee();
          iVar5 = FUN_0007d446();
          iVar5 = iVar5 + 0x70;
          iVar4 = iVar4 + 0x66;
        }
        else {
          iVar4 = FUN_0007d3ee();
          iVar5 = FUN_0007d446();
          iVar5 = iVar5 + 0x70;
          iVar4 = iVar4 + 0x70;
        }
        goto LAB_00041f70;
      }
      goto LAB_00041f76;
    }
    iVar4 = FUN_000167a8();
    if (*(char *)(*(int *)(iVar4 + 0x1014) + 2) == '\x06') {
      uVar16 = FUN_0007d382();
      iVar4 = FUN_000167a8();
      uVar14 = *(uint *)(*(int *)(iVar4 + 0x1014) + 4);
      uVar1 = (int)((ulonglong)uVar16 >> 0x20) - *(int *)(*(int *)(iVar4 + 0x1014) + 8);
      uVar2 = (uint)((uint)uVar16 < uVar14);
      if (uVar1 == uVar2 && (uint)(2000 < (uint)uVar16 - uVar14) <= uVar1 - uVar2) {
        return;
      }
      if (*DAT_00042484 == '\0') {
        *DAT_00042484 = '\x01';
        FUN_00043308();
        uVar12 = FUN_0007d3ee();
        iVar4 = FUN_0007d446();
        FUN_000435d4(0x38,uVar12,iVar4 + 0x37,&local_428,0x55);
        iVar4 = FUN_00023ee0();
        if (iVar4 == 6) {
          uVar12 = FUN_0007d4b2(0x19);
          iVar4 = FUN_0007d3ee();
          iVar7 = FUN_0007d446();
          iVar6 = FUN_0007d3ee();
          iVar5 = FUN_0007d446();
          iVar4 = iVar4 + 0x34;
        }
        else {
          uVar12 = FUN_0007d4b2(0x19);
          iVar4 = FUN_0007d3ee();
          iVar7 = FUN_0007d446();
          iVar6 = FUN_0007d3ee();
          iVar5 = FUN_0007d446();
          iVar4 = iVar4 + 0x8c;
        }
        FUN_00043e90(0,uVar12,0,iVar4,iVar7 + 0x6d,iVar6 + 0x240,iVar5 + 0x88,1,0,0,0,0);
      }
      iVar4 = FUN_00023ee0();
      if (iVar4 == 6) {
        iVar4 = FUN_0007d3ee();
        iVar5 = FUN_0007d446();
        iVar5 = iVar5 + 0x70;
        iVar4 = iVar4 + 0x10;
      }
      else {
        iVar4 = FUN_0007d3ee();
        iVar5 = FUN_0007d446();
        iVar5 = iVar5 + 0x70;
        iVar4 = iVar4 + 0x68;
      }
    }
    else {
      iVar4 = FUN_000167a8();
      if (*(char *)(*(int *)(iVar4 + 0x1014) + 2) != '\x13') {
        return;
      }
      iVar4 = FUN_00023ee0();
      if (iVar4 == 6) {
        iVar4 = FUN_0007d3ee();
        iVar5 = FUN_0007d446();
        iVar5 = iVar5 + 0x70;
        iVar4 = iVar4 + 0x74;
      }
      else {
        iVar4 = FUN_0007d3ee();
        iVar5 = FUN_0007d446();
        iVar5 = iVar5 + 0x70;
        iVar4 = iVar4 + 0x82;
      }
    }
    uVar12 = 2;
    goto LAB_000423d0;
  case 8:
    iVar4 = FUN_00023ee0();
    if (iVar4 == 6) {
      iVar4 = FUN_0007d3ee();
      iVar5 = FUN_0007d446();
      iVar5 = iVar5 + 0x70;
      iVar4 = iVar4 + 0x88;
    }
    else {
      iVar4 = FUN_0007d3ee();
      iVar5 = FUN_0007d446();
      iVar5 = iVar5 + 0x70;
      iVar4 = iVar4 + 0x66;
    }
LAB_00041938:
    uVar12 = 0xc;
LAB_000423d0:
    FUN_0004334c(uVar12,iVar4,iVar5,0,0,0,0);
    break;
  case 0xf:
  case 0x11:
    iVar4 = FUN_000167a8();
    iVar5 = FUN_000167a8();
    iVar5 = *(int *)(iVar5 + 0x1014);
    uVar13 = *(undefined1 *)(iVar4 + 0xee4);
LAB_000418a6:
    *(undefined1 *)(iVar5 + 3) = uVar13;
    break;
  case 0x16:
    uVar16 = FUN_0007d382();
    iVar4 = FUN_000167a8();
    uVar14 = *(uint *)(*(int *)(iVar4 + 0x1014) + 4);
    uVar1 = (int)((ulonglong)uVar16 >> 0x20) - *(int *)(*(int *)(iVar4 + 0x1014) + 8);
    uVar2 = (uint)((uint)uVar16 < uVar14);
    if (uVar1 != uVar2 || uVar1 - uVar2 < (uint)(4000 < (uint)uVar16 - uVar14)) {
      iVar4 = FUN_000167a8();
      *(undefined1 *)(*(int *)(iVar4 + 0x1014) + 2) = 5;
    }
    break;
  case 0x17:
    if (5 < *DAT_000429f4) {
      return;
    }
    if (*DAT_000429f4 != 0) {
      uVar16 = FUN_0007d382();
      iVar4 = FUN_000167a8();
      uVar14 = *(uint *)(*(int *)(iVar4 + 0x1014) + 4);
      uVar1 = (int)((ulonglong)uVar16 >> 0x20) - *(int *)(*(int *)(iVar4 + 0x1014) + 8);
      uVar2 = (uint)((uint)uVar16 < uVar14);
      if (uVar1 == uVar2 && (uint)(1000 < (uint)uVar16 - uVar14) <= uVar1 - uVar2) {
        return;
      }
    }
    uVar12 = 0x14;
    *pbVar3 = *pbVar3 + 1;
LAB_000418d2:
    send_event_status(uVar12);
    uVar16 = FUN_0007d382();
    iVar4 = FUN_000167a8();
    *(undefined8 *)(*(int *)(iVar4 + 0x1014) + 4) = uVar16;
  }
  return;
}

