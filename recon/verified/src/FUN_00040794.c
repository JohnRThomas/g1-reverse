/* Reconstructed FUN_00040794 @ 0x40794  (parity: 4/300 trials, PROVEN) */
typedef unsigned char byte;
typedef unsigned char undefined1;
typedef unsigned int undefined4;
typedef unsigned int uint;

extern int FUN_000167a8(void);
extern int FUN_00023ee0(void);
extern void FUN_000431c0(void);
extern void FUN_000432d0(void);
extern void FUN_000432ec(void);
extern void FUN_00043484(int,int,int,int,int,int);
extern void FUN_00043e90(int,int,int,int,int,int,int,int,int,int,int,int);
extern int FUN_000456fc(int,int);
extern void FUN_00047260(int,int,int,int,int,int);
extern int FUN_0007d3ee(void);
extern int FUN_0007d446(void);
extern int FUN_0007d4b2(int);
extern void send_event_status(int);

#define B(a) (*(volatile byte*)(a))

void FUN_00040794(void)
{
  byte bVar1;
  int *piVar2;
  undefined4 *puVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  int iVar8;
  undefined4 uVar9;
  undefined1 uVar10;
  uint uVar11;
  int iVar12;
  undefined4 uVar13;
  undefined4 local_30;
  undefined4 uStack_2c;

  iVar4 = FUN_000167a8();
  if (B(0x2001cdd3) == '\0') {
    return;
  }
  B(0x2001cdd3) = '\0';
  FUN_000431c0();
  iVar5 = FUN_000167a8();
  if ((((((*(char *)(*(int *)(iVar5 + 0x1014) + 2) != '\0') &&
         (iVar5 = FUN_000167a8(), *(char *)(*(int *)(iVar5 + 0x1014) + 2) != '\n')) &&
        (iVar5 = FUN_000167a8(), *(char *)(*(int *)(iVar5 + 0x1014) + 2) != '\v')) &&
       ((iVar5 = FUN_000167a8(), *(char *)(*(int *)(iVar5 + 0x1014) + 2) != '\x05' &&
        (iVar5 = FUN_000167a8(), *(char *)(*(int *)(iVar5 + 0x1014) + 2) != '\x06')))) &&
      ((iVar5 = FUN_000167a8(), *(char *)(*(int *)(iVar5 + 0x1014) + 2) != '\x13' &&
       ((iVar5 = FUN_000167a8(), *(char *)(*(int *)(iVar5 + 0x1014) + 2) != '\x14' &&
        (iVar5 = FUN_000167a8(), *(char *)(*(int *)(iVar5 + 0x1014) + 2) != '\x15')))))) &&
     ((iVar5 = FUN_000167a8(), *(char *)(*(int *)(iVar5 + 0x1014) + 2) != '\x0e' &&
      ((((iVar5 = FUN_000167a8(), *(char *)(*(int *)(iVar5 + 0x1014) + 2) != '\x0f' &&
         (iVar5 = FUN_000167a8(), *(char *)(*(int *)(iVar5 + 0x1014) + 2) != '\x10')) &&
        (iVar5 = FUN_000167a8(), *(char *)(*(int *)(iVar5 + 0x1014) + 2) != '\x11')) &&
       ((iVar5 = FUN_000167a8(), *(char *)(*(int *)(iVar5 + 0x1014) + 2) != '\x03' ||
        (B(0x2001cdce) != 2)))))))) {
    iVar5 = FUN_000167a8();
    iVar12 = *(int *)(iVar5 + 0x1014);
    uVar6 = FUN_0007d3ee();
    iVar5 = FUN_0007d446();
    iVar7 = FUN_0007d3ee();
    iVar8 = FUN_0007d446();
    FUN_00043e90(0,iVar12 + 0x1b,3,uVar6,iVar5 + 0x37,iVar7 + 0x28,iVar8 + 0x52,4,0,0,0,0);
  }
  iVar5 = FUN_000167a8();
  switch(*(undefined1 *)(*(int *)(iVar5 + 0x1014) + 2)) {
  case 0:
    FUN_000432ec();
    piVar2 = (int*)0x20009ff4;
    *(int*)0x20009ff4 = 0;
    while (*piVar2 < 8) {
      uVar6 = FUN_0007d3ee();
      uVar11 = 0;
      iVar5 = FUN_0007d446();
      FUN_00043484(0x16,uVar6,iVar5 + 0x38,0,0,0);
      uVar6 = FUN_000456fc(B(0x200034f3 + (uint)B(0x2001cdce)),1);
      iVar5 = FUN_0007d3ee();
      iVar7 = FUN_0007d446();
      iVar8 = FUN_0007d3ee();
      iVar12 = FUN_0007d446();
      FUN_00043e90(0,uVar6,0,iVar5 + 0x40,iVar7 + 0x37,iVar8 + 0x240,iVar12 + 0x88,4,0,0,0,0);
      puVar3 = (undefined4*)0x000a8c57;
      iVar5 = *piVar2;
      local_30 = *(undefined4*)0x000a8c57;
      do {
        uStack_2c = puVar3[1];
        iVar7 = 0;
        do {
          iVar8 = *(int *)(iVar4 + 0xb90 + uVar11 * 4);
          bVar1 = *(byte *)(iVar8 + iVar7);
          if (bVar1 != 0) {
            *(byte *)(iVar8 + iVar7) =
                 bVar1 & *(byte *)((uint)*(byte *)((int)&local_30 + iVar5) * 0x140 +
                                   (uVar11 % 0x1a) * 0xa00 + 0x000aae20 + iVar7);
          }
          iVar7 = iVar7 + 1;
        } while (iVar7 != 0x140);
        uVar11 = uVar11 + 1;
      } while (uVar11 != 199);
      *piVar2 = iVar5 + 1;
      iVar5 = FUN_000167a8();
      uVar6 = *(undefined4 *)(iVar5 + 0xeb4);
      iVar5 = FUN_000167a8();
      FUN_00047260(uVar6,*(undefined4 *)(iVar5 + 0xeb8),0,0,0x280,199);
    }
    goto LAB_00040928;
  case 1:
    uVar6 = FUN_0007d4b2(6);
    iVar8 = FUN_0007d3ee();
    iVar4 = FUN_0007d446();
    iVar5 = FUN_0007d3ee();
    iVar7 = FUN_0007d446();
    iVar7 = iVar7 + 0x88;
    iVar5 = iVar5 + 0x240;
    iVar4 = iVar4 + 0x37;
    iVar8 = iVar8 + 0x8c;
    break;
  case 2:
    uVar6 = FUN_0007d4b2(0x20);
    iVar8 = FUN_0007d3ee();
    iVar4 = FUN_0007d446();
    iVar5 = FUN_0007d3ee();
    iVar7 = FUN_0007d446();
    iVar7 = iVar7 + 0x88;
    iVar5 = iVar5 + 0x240;
    iVar4 = iVar4 + 0x37;
    iVar8 = iVar8 + 0x80;
    break;
  case 3:
  case 5:
  case 0x14:
  case 0x15:
    if (B(0x2001cdce) == '\x01') {
      iVar4 = FUN_000167a8();
      if (*(char *)(*(int *)(iVar4 + 0x1014) + 2) != '\x03') {
        iVar4 = FUN_000167a8();
        if (*(char *)(*(int *)(iVar4 + 0x1014) + 2) != '\x15') goto switchD_000408e4_caseD_a;
        B(0x2001cdd0) = 0;
        iVar4 = FUN_000167a8();
        if ((*(byte *)(*(int *)(iVar4 + 0x1014) + 0x1f) & 3) != 1) goto switchD_000408e4_caseD_a;
        send_event_status(0x14);
        iVar4 = FUN_000167a8();
        *(byte *)(*(int *)(iVar4 + 0x1014) + 0x1f) = *(byte *)(*(int *)(iVar4 + 0x1014) + 0x1f) | 2;
        iVar4 = FUN_000167a8();
        uVar10 = 0x17;
        iVar4 = *(int *)(iVar4 + 0x1014);
LAB_00040c1c:
        *(undefined1 *)(iVar4 + 2) = uVar10;
        goto switchD_000408e4_caseD_a;
      }
      B(0x2001cdd0) = 0;
      uVar6 = FUN_0007d4b2(8);
      iVar8 = FUN_0007d3ee();
      iVar4 = FUN_0007d446();
      iVar5 = FUN_0007d3ee();
      iVar7 = FUN_0007d446();
      iVar7 = iVar7 + 0x88;
      uVar13 = 4;
      iVar8 = iVar8 + 0x8c;
      goto LAB_00040bc6;
    }
    if (B(0x2001cdce) != '\x02') goto switchD_000408e4_caseD_a;
    iVar5 = FUN_000167a8();
    if ((*(char *)(*(int *)(iVar5 + 0x1014) + 2) == '\x15') &&
       (iVar5 = FUN_000167a8(), -1 < (int)((uint)*(byte *)(*(int *)(iVar5 + 0x1014) + 0x1f) << 0x1f)
       )) {
      send_event_status(0x13);
      iVar5 = FUN_000167a8();
      *(byte *)(*(int *)(iVar5 + 0x1014) + 0x1f) = *(byte *)(*(int *)(iVar5 + 0x1014) + 0x1f) | 1;
    }
    if (B(0x2001cdd1) != '\0') {
LAB_00040c64:
      B(0x2001cdd2) = 0;
      goto switchD_000408e4_caseD_a;
    }
    iVar5 = FUN_000167a8();
    if ((*(char *)(*(int *)(iVar5 + 0x1014) + 2) != '\x15') ||
       (*(char *)(0x20004bf0 + 0x10) == '\x01')) {
      FUN_000432ec();
    }
    piVar2 = (int*)0x20009ff4;
    *(int*)0x20009ff4 = 0;
    while (*piVar2 < 8) {
      uVar6 = FUN_0007d4b2(0x14);
      uVar13 = FUN_0007d3ee();
      uVar9 = FUN_0007d446();
      iVar5 = FUN_0007d3ee();
      iVar7 = FUN_0007d446();
      FUN_00043e90(0,uVar6,3,uVar13,uVar9,iVar5 + 0x76,iVar7 + 0x1b,1,0,0,0,0);
      uVar6 = FUN_0007d3ee();
      iVar5 = FUN_0007d446();
      iVar7 = FUN_0007d3ee();
      iVar8 = FUN_0007d446();
      FUN_00043e90(0,0x000aa608,1,uVar6,iVar5 + 0x1b,iVar7 + 0x68,iVar8 + 0x42,1,0,0,0,0);
      iVar5 = FUN_0007d3ee();
      iVar7 = FUN_0007d446();
      FUN_00043484(0x29,iVar5 + 0xa6,iVar7 + 4,0,0,0);
      iVar5 = FUN_0007d3ee();
      iVar7 = FUN_0007d446();
      iVar8 = FUN_0007d3ee();
      iVar12 = FUN_0007d446();
      FUN_00043e90(0,0x000aa60e,3,iVar5 + 0xc2,iVar7 + 3,iVar8 + 0xea,iVar12 + 0x1e,1,0,0,0,0);
      iVar5 = FUN_0007d3ee();
      iVar7 = FUN_0007d446();
      iVar8 = FUN_0007d3ee();
      iVar12 = FUN_0007d446();
      FUN_00043e90(0,0x000f212c,3,iVar5 + 0xde,iVar7 + 3,iVar8 + 0xec,iVar12 + 0x1e,1,0,0,0,0);
      iVar5 = FUN_0007d3ee();
      iVar7 = FUN_0007d446();
      FUN_00043484(0x3c,iVar5 + 0xa6,iVar7 + 0x23,0,0,0);
      iVar5 = FUN_000167a8();
      uVar6 = 0x000f341d;
      if ((*(char *)(*(int *)(iVar5 + 0x1014) + 2) != '\x05') &&
         (iVar5 = FUN_000167a8(), uVar6 = 0x000f7a30,
         *(char *)(*(int *)(iVar5 + 0x1014) + 2) == '\x03')) {
        uVar6 = 0x000f3449;
      }
      iVar5 = FUN_0007d3ee();
      iVar7 = FUN_0007d446();
      iVar8 = FUN_0007d3ee();
      iVar12 = FUN_0007d446();
      FUN_00043e90(0,uVar6,3,iVar5 + 0xc2,iVar7 + 0x23,iVar8 + 0xd6,iVar12 + 0x3e,1,0,0,0,0);
      uVar6 = FUN_0007d3ee();
      iVar5 = FUN_0007d446();
      FUN_00043484(0x39,uVar6,iVar5 + 0x51,0,0,0);
      uVar6 = FUN_0007d4b2(0x16);
      iVar5 = FUN_0007d3ee();
      iVar7 = FUN_0007d446();
      iVar8 = FUN_0007d3ee();
      iVar12 = FUN_0007d446();
      FUN_00043e90(0,uVar6,0,iVar5 + 0x1c,iVar7 + 0x51,iVar8 + 0xf2,iVar12 + 0x6c,1,0,0,0,0);
      uVar6 = FUN_0007d4b2(0x15);
      uVar13 = FUN_0007d3ee();
      iVar5 = FUN_0007d446();
      iVar7 = FUN_0007d3ee();
      iVar8 = FUN_0007d446();
      FUN_00043e90(0,uVar6,0,uVar13,iVar5 + 0x6d,iVar7 + 0xf2,iVar8 + 0x88,1,0,0,0,0);
      iVar5 = FUN_0007d3ee();
      iVar7 = FUN_0007d446();
      FUN_00043484(0x3b,iVar5 + 0x108,iVar7 + 1,0,0,0);
      uVar6 = FUN_0007d4b2(0x17);
      iVar5 = FUN_0007d3ee();
      uVar13 = FUN_0007d446();
      iVar7 = FUN_0007d3ee();
      iVar8 = FUN_0007d446();
      FUN_00043e90(0,uVar6,0,iVar5 + 0x126,uVar13,iVar7 + 0x202,iVar8 + 0x1b,1,0,0,0,0);
      iVar5 = FUN_000167a8();
      uVar6 = 0x000aa604;
      if (*(char *)(*(int *)(iVar5 + 0x1014) + 2) == '\x15') {
        uVar6 = 0x000aa600;
      }
      iVar5 = FUN_0007d3ee();
      iVar7 = FUN_0007d446();
      iVar8 = FUN_0007d3ee();
      iVar12 = FUN_0007d446();
      FUN_00043e90(0,uVar6,3,iVar5 + 0x210,iVar7 + 1,iVar8 + 0x234,iVar12 + 0x1c,1,0,0,0,0);
      iVar5 = FUN_000167a8();
      if (*(char *)(*(int *)(iVar5 + 0x1014) + 2) == '\x15') {
        uVar6 = 0xe;
      }
      else {
        uVar6 = 0x18;
      }
      uVar6 = FUN_0007d4b2(uVar6);
      iVar5 = FUN_0007d3ee();
      iVar7 = FUN_0007d446();
      iVar8 = FUN_0007d3ee();
      iVar12 = FUN_0007d446();
      FUN_00043e90(0,uVar6,0,iVar5 + 0x108,iVar7 + 0x1b,iVar8 + 0x232,iVar12 + 0x87,4,0,0,0,0);
      iVar5 = FUN_0007d3ee();
      uVar6 = FUN_0007d446();
      FUN_00043484(0x4e,iVar5 + 0xfc,uVar6,0,0,0);
      iVar5 = FUN_0007d3ee();
      uVar6 = FUN_0007d446();
      FUN_00043484(0x4f,iVar5 + 0x23e,uVar6,0,0,0);
      iVar5 = FUN_000167a8();
      puVar3 = (undefined4*)0x000a8c57;
      if ((*(char *)(*(int *)(iVar5 + 0x1014) + 2) == '\x15') &&
         (*(char *)(0x20004bf0 + 0x10) != '\x01')) break;
      uVar11 = 0;
      iVar5 = *piVar2;
      local_30 = *(undefined4*)0x000a8c57;
      do {
        uStack_2c = puVar3[1];
        iVar7 = 0;
        do {
          iVar8 = *(int *)(iVar4 + 0xb90 + uVar11 * 4);
          bVar1 = *(byte *)(iVar8 + iVar7);
          if (bVar1 != 0) {
            *(byte *)(iVar8 + iVar7) =
                 bVar1 & *(byte *)((uint)*(byte *)((int)&local_30 + iVar5) * 0x140 +
                                   (uVar11 % 0x1a) * 0xa00 + 0x000aae20 + iVar7);
          }
          iVar7 = iVar7 + 1;
        } while (iVar7 != 0x140);
        uVar11 = uVar11 + 1;
      } while (uVar11 != 199);
      *piVar2 = iVar5 + 1;
      iVar5 = FUN_000167a8();
      uVar6 = *(undefined4 *)(iVar5 + 0xeb4);
      iVar5 = FUN_000167a8();
      FUN_00047260(uVar6,*(undefined4 *)(iVar5 + 0xeb8),0,0,0x280,199);
    }
    goto LAB_00040928;
  case 4:
    uVar6 = FUN_0007d4b2(7);
    iVar4 = FUN_0007d3ee();
    iVar5 = FUN_0007d446();
    iVar7 = FUN_0007d3ee();
    iVar8 = FUN_0007d446();
    FUN_00043e90(0,uVar6,0,iVar4 + 0xd2,iVar5 + 0x37,iVar7 + 0x240,iVar8 + 0x52,1,0,0,0,0);
    uVar6 = FUN_0007d4b2(0x1f);
    iVar8 = FUN_0007d3ee();
    iVar4 = FUN_0007d446();
    iVar5 = FUN_0007d3ee();
    iVar7 = FUN_0007d446();
    iVar7 = iVar7 + 0x88;
    iVar5 = iVar5 + 0x240;
    iVar4 = iVar4 + 0x6d;
    iVar8 = iVar8 + 0xae;
    goto LAB_00040b66;
  case 6:
  case 0x13:
    if (B(0x2001cdce) == '\x01') {
      iVar4 = FUN_000167a8();
      if (*(char *)(*(int *)(iVar4 + 0x1014) + 2) == '\x06') {
        uVar6 = FUN_0007d3ee();
        iVar4 = FUN_0007d446();
        FUN_00043484(0x38,uVar6,iVar4 + 0x37,0,0,0);
        iVar4 = FUN_000167a8();
        if ((*(byte *)(*(int *)(iVar4 + 0x1014) + 0x1f) & 0xc) != 4) goto switchD_000408e4_caseD_a;
        send_event_status(0x16);
        iVar4 = FUN_000167a8();
        *(byte *)(*(int *)(iVar4 + 0x1014) + 0x1f) = *(byte *)(*(int *)(iVar4 + 0x1014) + 0x1f) | 8;
        iVar4 = FUN_000167a8();
        uVar10 = 5;
        iVar4 = *(int *)(iVar4 + 0x1014);
        goto LAB_00040c1c;
      }
      iVar4 = FUN_000167a8();
      if (*(char *)(*(int *)(iVar4 + 0x1014) + 2) != '\x13') goto switchD_000408e4_caseD_a;
      uVar6 = FUN_0007d4b2(0x22);
      iVar8 = FUN_0007d3ee();
      iVar4 = FUN_0007d446();
      iVar5 = FUN_0007d3ee();
      iVar7 = FUN_0007d446();
      iVar7 = iVar7 + 0x88;
      iVar4 = iVar4 + 0x6d;
      iVar8 = iVar8 + 0xa6;
      uVar13 = 1;
      goto LAB_000411c8;
    }
    if (B(0x2001cdce) != '\x02') goto switchD_000408e4_caseD_a;
    iVar5 = FUN_000167a8();
    if (*(char *)(*(int *)(iVar5 + 0x1014) + 2) == '\x06') {
      iVar5 = FUN_000167a8();
      if (-1 < (int)((uint)*(byte *)(*(int *)(iVar5 + 0x1014) + 0x1f) << 0x1d)) {
        send_event_status(0x15);
        iVar5 = FUN_000167a8();
        *(byte *)(*(int *)(iVar5 + 0x1014) + 0x1f) = *(byte *)(*(int *)(iVar5 + 0x1014) + 0x1f) | 4;
      }
    }
    else {
      iVar5 = FUN_000167a8();
      if ((*(char *)(*(int *)(iVar5 + 0x1014) + 2) == '\x13') && (B(0x2001cdd1) != '\0'))
      goto LAB_00040c64;
    }
    FUN_000432ec();
    piVar2 = (int*)0x20009ff4;
    *(int*)0x20009ff4 = 0;
    while (*piVar2 < 8) {
      iVar5 = FUN_0007d3ee();
      uVar11 = 0;
      iVar7 = FUN_0007d446();
      FUN_00043484(0x3c,iVar5 + 0x212,iVar7 + 4,0,0,0);
      iVar5 = FUN_000167a8();
      uVar6 = 0x000f7a30;
      if (*(char *)(*(int *)(iVar5 + 0x1014) + 2) == '\x06') {
        uVar6 = 0x000f341d;
      }
      iVar5 = FUN_0007d3ee();
      iVar7 = FUN_0007d446();
      iVar8 = FUN_0007d3ee();
      iVar12 = FUN_0007d446();
      FUN_00043e90(0,uVar6,3,iVar5 + 0x22e,iVar7 + 3,iVar8 + 0x23e,iVar12 + 0x1e,1,0,0,0,0);
      uVar6 = FUN_0007d3ee();
      iVar5 = FUN_0007d446();
      FUN_00043484(0x38,uVar6,iVar5 + 4,0,0,0);
      uVar6 = FUN_0007d4b2(0x1a);
      iVar5 = FUN_0007d3ee();
      iVar7 = FUN_0007d446();
      iVar8 = FUN_0007d3ee();
      iVar12 = FUN_0007d446();
      FUN_00043e90(0,uVar6,0,iVar5 + 0x24,iVar7 + 3,iVar8 + 0x150,iVar12 + 0x1e,1,0,0,0,0);
      iVar5 = FUN_000167a8();
      if (*(char *)(*(int *)(iVar5 + 0x1014) + 2) == '\x06') {
        uVar6 = 0x1c;
      }
      else {
        uVar6 = 0xc;
      }
      uVar6 = FUN_0007d4b2(uVar6);
      uVar13 = FUN_0007d3ee();
      iVar5 = FUN_0007d446();
      iVar7 = FUN_0007d3ee();
      iVar8 = FUN_0007d446();
      FUN_00043e90(0,uVar6,0,uVar13,iVar5 + 0x37,iVar7 + 0x240,iVar8 + 0x6d,2,0,0,0,0);
      puVar3 = (undefined4*)0x000a8c57;
      iVar5 = *piVar2;
      local_30 = *(undefined4*)0x000a8c57;
      do {
        uStack_2c = puVar3[1];
        iVar7 = 0;
        do {
          iVar8 = *(int *)(iVar4 + 0xb90 + uVar11 * 4);
          bVar1 = *(byte *)(iVar8 + iVar7);
          if (bVar1 != 0) {
            *(byte *)(iVar8 + iVar7) =
                 bVar1 & *(byte *)((uint)*(byte *)((int)&local_30 + iVar5) * 0x140 +
                                   (uVar11 % 0x1a) * 0xa00 + 0x000aae20 + iVar7);
          }
          iVar7 = iVar7 + 1;
        } while (iVar7 != 0x140);
        uVar11 = uVar11 + 1;
      } while (uVar11 != 199);
      *piVar2 = iVar5 + 1;
      iVar5 = FUN_000167a8();
      uVar6 = *(undefined4 *)(iVar5 + 0xeb4);
      iVar5 = FUN_000167a8();
      FUN_00047260(uVar6,*(undefined4 *)(iVar5 + 0xeb8),0,0,0x280,199);
    }
LAB_00040928:
    FUN_000432d0();
    goto switchD_000408e4_caseD_a;
  case 7:
  case 9:
  case 0xc:
  case 0xd:
    uVar6 = FUN_0007d4b2(0x21);
    iVar8 = FUN_0007d3ee();
    iVar4 = FUN_0007d446();
    iVar5 = FUN_0007d3ee();
    iVar7 = FUN_0007d446();
    iVar7 = iVar7 + 0x88;
    iVar5 = iVar5 + 0x240;
    iVar4 = iVar4 + 0x37;
    iVar8 = iVar8 + 0x72;
    break;
  case 8:
    iVar4 = FUN_00023ee0();
    if (iVar4 == 6) {
      uVar6 = FUN_0007d4b2(7);
      iVar4 = FUN_0007d3ee();
      iVar5 = FUN_0007d446();
      iVar7 = FUN_0007d3ee();
      iVar8 = FUN_0007d446();
      FUN_00043e90(0,uVar6,0,iVar4 + 0xc6,iVar5 + 0x37,iVar7 + 0x240,iVar8 + 0x52,1,0,0,0,0);
      uVar6 = FUN_0007d4b2(0x1f);
      iVar8 = FUN_0007d3ee();
      iVar4 = FUN_0007d446();
      iVar5 = FUN_0007d3ee();
      iVar7 = FUN_0007d446();
      iVar5 = iVar5 + 0x240;
      iVar7 = iVar7 + 0x88;
      iVar4 = iVar4 + 0x6d;
      iVar8 = iVar8 + 0xac;
    }
    else {
      uVar6 = FUN_0007d4b2(7);
      iVar4 = FUN_0007d3ee();
      iVar5 = FUN_0007d446();
      iVar7 = FUN_0007d3ee();
      iVar8 = FUN_0007d446();
      FUN_00043e90(0,uVar6,0,iVar4 + 0xd2,iVar5 + 0x37,iVar7 + 0x240,iVar8 + 0x52,1,0,0,0,0);
      uVar6 = FUN_0007d4b2(0x1f);
      iVar8 = FUN_0007d3ee();
      iVar4 = FUN_0007d446();
      iVar5 = FUN_0007d3ee();
      iVar7 = FUN_0007d446();
      iVar5 = iVar5 + 0x240;
      iVar7 = iVar7 + 0x88;
      iVar4 = iVar4 + 0x6d;
      iVar8 = iVar8 + 0x8a;
    }
LAB_00040b66:
    uVar13 = 1;
    goto LAB_00040a7e;
  default:
    goto switchD_000408e4_caseD_a;
  case 0xe:
  case 0xf:
    uVar6 = FUN_0007d3ee();
    iVar4 = FUN_0007d446();
    FUN_00043484(0x36,uVar6,iVar4 + 0x37,0,0,0);
    iVar4 = FUN_000167a8();
    if ((*(char *)(*(int *)(iVar4 + 0x1014) + 2) == '\x0f') && (B(0x2001cdce) == '\x01'))
    goto switchD_000408e4_caseD_a;
    uVar6 = FUN_0007d4b2(0x23);
    iVar8 = FUN_0007d3ee();
    iVar4 = FUN_0007d446();
    iVar5 = FUN_0007d3ee();
    iVar7 = FUN_0007d446();
    iVar7 = iVar7 + 0x88;
    iVar5 = iVar5 + 0x240;
    iVar4 = iVar4 + 0x37;
    iVar8 = iVar8 + 0xb8;
    break;
  case 0x10:
  case 0x11:
    iVar4 = FUN_000167a8();
    if ((*(char *)(*(int *)(iVar4 + 0x1014) + 2) == '\x11') && (B(0x2001cdce) == '\x01')) {
      uVar6 = FUN_0007d3ee();
      iVar4 = FUN_0007d446();
      FUN_00043484(0x38,uVar6,iVar4 + 0x37,0,0,0);
      goto switchD_000408e4_caseD_a;
    }
    iVar4 = FUN_0007d3ee();
    iVar5 = FUN_0007d446();
    FUN_00043484(0x3c,iVar4 + 0x212,iVar5 + 4,0,0,0);
    iVar4 = FUN_0007d3ee();
    iVar5 = FUN_0007d446();
    iVar7 = FUN_0007d3ee();
    iVar8 = FUN_0007d446();
    FUN_00043e90(0,0x000f341d,3,iVar4 + 0x22e,iVar5 + 3,iVar7 + 0x23e,iVar8 + 0x1e,1,1,0,0,0);
    uVar6 = FUN_0007d3ee();
    iVar4 = FUN_0007d446();
    FUN_00043484(0x38,uVar6,iVar4 + 4,0,0,0);
    uVar6 = FUN_0007d4b2(0x1a);
    iVar4 = FUN_0007d3ee();
    iVar5 = FUN_0007d446();
    iVar7 = FUN_0007d3ee();
    iVar8 = FUN_0007d446();
    FUN_00043e90(0,uVar6,0,iVar4 + 0x24,iVar5 + 3,iVar7 + 0x150,iVar8 + 0x1e,1,0,0,0,0);
    uVar6 = FUN_0007d4b2(0x1c);
    iVar8 = FUN_0007d3ee();
    iVar4 = FUN_0007d446();
    iVar5 = FUN_0007d3ee();
    iVar7 = FUN_0007d446();
    iVar7 = iVar7 + 0x6d;
    uVar13 = 2;
LAB_00040bc6:
    iVar4 = iVar4 + 0x37;
LAB_000411c8:
    iVar5 = iVar5 + 0x240;
    goto LAB_00040a7e;
  case 0x16:
    uVar6 = FUN_0007d4b2(0x11);
    iVar8 = FUN_0007d3ee();
    iVar4 = FUN_0007d446();
    iVar5 = FUN_0007d3ee();
    iVar7 = FUN_0007d446();
    iVar7 = iVar7 + 0x88;
    iVar5 = iVar5 + 0x240;
    iVar4 = iVar4 + 0x37;
    iVar8 = iVar8 + 0x6a;
    break;
  case 0x17:
    iVar4 = FUN_00023ee0();
    if (iVar4 == 6) {
      uVar6 = FUN_0007d4b2(0x12);
      iVar8 = FUN_0007d3ee();
      iVar4 = FUN_0007d446();
      iVar5 = FUN_0007d3ee();
      iVar7 = FUN_0007d446();
      iVar7 = iVar7 + 0x88;
      iVar5 = iVar5 + 0x240;
      iVar4 = iVar4 + 0x37;
      iVar8 = iVar8 + 0x48;
    }
    else {
      uVar6 = FUN_0007d4b2(0x12);
      iVar8 = FUN_0007d3ee();
      iVar4 = FUN_0007d446();
      iVar5 = FUN_0007d3ee();
      iVar7 = FUN_0007d446();
      iVar7 = iVar7 + 0x88;
      iVar5 = iVar5 + 0x240;
      iVar4 = iVar4 + 0x37;
      iVar8 = iVar8 + 0x88;
    }
  }
  uVar13 = 4;
LAB_00040a7e:
  FUN_00043e90(0,uVar6,0,iVar8,iVar4,iVar5,iVar7,uVar13,0,0,0,0);
switchD_000408e4_caseD_a:
  iVar4 = FUN_000167a8();
  *(undefined1 *)(0x20004bf0 + 0x10) = *(undefined1 *)(iVar4 + 0xee4);
  return;
}

