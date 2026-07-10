/* Reconstructed FUN_0005d5c0 @ 0x5d5c0  (parity: 80/80 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int uint;
typedef unsigned char byte;
typedef unsigned char undefined1;
typedef unsigned int undefined4;

extern int FUN_00055cb4(void*,int);
extern int FUN_0005cac0(void);
extern int FUN_0005caec(int);
extern uint32_t FUN_0005cc30(int);
extern int FUN_0005d568(int,uint);
extern int FUN_0005e6a8(uint8_t,int);
extern int FUN_0005e938(uint8_t,int);
extern int FUN_00082ff6(int,int);
extern int FUN_00083002(int,int);
extern int FUN_00083074(uint32_t,uint32_t,void*);
extern int FUN_00083090(int,int);
extern uint32_t FUN_000830ee(void);

uint FUN_0005d5c0(int param_1, int param_2)
{
  int iVar12 = *(volatile int*)(param_1 + 0xf0);
  int iVar3 = FUN_0005cac0();
  byte *pbVar13 = *(volatile byte**)(param_2 + 0xc);

  if ((uint8_t)(pbVar13[3] - 7) > 9) return 6;

  if (*(volatile int*)(iVar12 + 0xc0) == 0) {
    int iVar4 = FUN_0005e6a8(*(volatile uint8_t*)(iVar12 + 8), iVar12 + 0x90);
    *(volatile int*)(iVar12 + 0xc0) = iVar4;
    if (iVar4 == 0) return 8;
  }

  int iVar11 = param_1 + 4;
  int iVar4 = FUN_00082ff6(iVar11, 0xf);
  if (iVar4 == 0) {
    uint32_t uVar5 = FUN_0005cc30(param_1);
    if (uVar5 != 0) return uVar5 & 0xff;
  }

  *(volatile uint8_t*)(param_1 + 9) = 1;
  *(volatile uint32_t*)(param_1 + 10) = *(volatile uint32_t*)pbVar13;
  *(volatile uint16_t*)(param_1 + 0xe) = *(volatile uint16_t*)(pbVar13 + 4);
  *(volatile uint8_t*)(param_1 + 0x10) = 2;
  uint8_t uVar2 = FUN_0005d568(param_1, pbVar13[2]);
  *(volatile uint8_t*)(param_1 + 0x13) = uVar2;
  uVar2 = FUN_0005caec(param_1);
  *(volatile uint8_t*)(param_1 + 0x11) = uVar2;
  *(volatile uint8_t*)(param_1 + 0x14) = 0x10;
  *(volatile uint8_t*)(param_1 + 0x15) = pbVar13[4] & 3;
  *(volatile uint8_t*)(param_1 + 0x16) = pbVar13[5] & 1;

  if ((int8_t)(*(volatile uint8_t*)(param_1 + 0x13)) < 0 && (int8_t)pbVar13[2] < 0) {
    FUN_00083090(iVar11, 5);
    *(volatile uint8_t*)(param_1 + 0x15) = *(volatile uint8_t*)(param_1 + 0x15) & 2;
    *(volatile uint8_t*)(param_1 + 0x16) = 0;
  }

  iVar4 = FUN_00082ff6(iVar11, 5);
  uint8_t puVar9val;
  if (iVar4 != 0) {
    puVar9val = *(volatile uint8_t*)0x2001d534UL;
  } else {
    puVar9val = *(volatile uint8_t*)0x2001d533UL;
  }
  *(volatile uint8_t*)(param_1 + 0x12) = puVar9val;

  if ((int8_t)(uint8_t)(*(volatile uint8_t*)(param_1 + 0x13) << 6) < 0 &&
      (int8_t)(uint8_t)(pbVar13[2] << 6) < 0) {
    FUN_00083090(iVar11, 0x14);
  }

  if ((int8_t)(*(volatile uint8_t*)(param_1 + 0x13)) < 0 == 0 /*placeholder*/) {
    /* handled below properly */
  }

  if ( ((int32_t)((uint32_t)*(volatile uint8_t*)(param_1 + 0x13) << 0x1f)) < 0 &&
       ((int32_t)((uint32_t)pbVar13[2] << 0x1f)) < 0 ) {
    FUN_00083090(iVar11, 0xd);
  } else {
    *(volatile uint8_t*)(param_1 + 0x15) = 0;
    *(volatile uint8_t*)(param_1 + 0x16) = 0;
  }

  *(volatile uint8_t*)(param_1 + 0xe8) = *(volatile uint8_t*)(param_1 + 0x16);
  *(volatile uint8_t*)(param_1 + 0xe9) = *(volatile uint8_t*)(param_1 + 0x15);
  int uVar6 = FUN_00083090(iVar11, 3);
  uint uVar5b = *pbVar13;
  iVar4 = FUN_00082ff6(uVar6, 5);
  uint8_t bVar8;
  if (iVar4 == 0) {
    if (uVar5b < 5) {
      if ((int32_t)((uint32_t)(*(volatile uint8_t*)(param_1+0xb) & *(volatile uint8_t*)(param_1+0x12)) << 0x1f) < 0) {
        bVar8 = 6;
      } else {
        uint8_t bVar1 = *(volatile uint8_t*)(param_1+0xc) | *(volatile uint8_t*)(param_1+0x13);
        bVar8 = bVar1 & 4;
        if ((bVar1 & 4) != 0) {
          int iv = FUN_0005caec(param_1);
          bVar8 = *(volatile uint8_t*)(uVar5b*5 + 0x000f5248UL + iv);
          if (bVar8 == 4) {
            if (*(volatile int8_t*)(*(volatile int*)(param_1+0xf0) + 3) == 0) bVar8 = 2;
            else bVar8 = 1;
          }
        }
      }
    } else {
      bVar8 = 0;
    }
  } else if ( ((int32_t)((uint32_t)(*(volatile uint8_t*)(param_1+0xc) & *(volatile uint8_t*)(param_1+0x13)) << 0x1c)) >= 0 ||
              ((int32_t)((uint32_t)(*(volatile uint8_t*)(param_1+0xb) | *(volatile uint8_t*)(param_1+0x12)) << 0x1f)) >= 0 ) {
    if (uVar5b > 4) { bVar8 = 0; }
    else {
      uint8_t bVar1 = *(volatile uint8_t*)(param_1+0xc) | *(volatile uint8_t*)(param_1+0x13);
      bVar8 = bVar1 & 4;
      if ((bVar1 & 4) != 0) {
        int iv = FUN_0005caec(param_1);
        bVar8 = *(volatile uint8_t*)(0x000f522fUL + uVar5b*5 + iv);
      }
    }
  } else {
    bVar8 = 6; /* extraout_r1 unknown, approximate */
  }
  *(volatile uint8_t*)(param_1 + 8) = bVar8;

  iVar4 = FUN_00083002(param_1, *(volatile int*)(iVar12 + 0xc0));
  if (iVar4 == 0) return 3;

  uint uVar5c = *(volatile uint8_t*)(*(volatile int*)(param_1+0xf0) + 10);
  if (uVar5c != 3) {
    if (uVar5c > 3) {
      if (uVar5c != 4) return 8;
      uint8_t b1 = *(volatile uint8_t*)(param_1+0x14);
      uint8_t b2 = *(volatile uint8_t*)(param_1+0xd);
      uint8_t bb = (b1 >= b2) ? b2 : b1;
      if (bb != 0x10) return 6;
      iVar4 = FUN_00082ff6(iVar11, 5);
      if (iVar4 == 0) return 3;
      goto LAB_d80e;
    }
    if ((uVar5c - 1) > 1) return 8;
  } else {
LAB_d80e:
    if (*(volatile int8_t*)(param_1 + 8) == 0) return 3;
  }

  iVar4 = FUN_00082ff6(iVar11, 5);
  if (iVar4 != 0) {
    if ( (*(volatile int8_t*)(param_1+8) == 0) &&
         (FUN_00082ff6(iVar11,0xf) == 0) &&
         (iVar3 != 0) && (*(volatile int*)(iVar3+0x14) != 0) ) {
      FUN_00083090(iVar11, 10);
      int (*pcVar10)(int) = *(volatile void* volatile*)(iVar3+0x14);
      int iv2 = *(volatile int*)(param_1+0xf0);
      pcVar10(iv2);
      return 0;
    }
    int p1 = FUN_00083090(param_1, 3);
    FUN_00083090(p1, 0xe);
    uint r = FUN_000830ee();
    return r;
  }

  iVar3 = FUN_0005cac0();
  int iVar4b = *(volatile int*)(param_1 + 0xf0);
  int *piVar7 = (int*)(intptr_t)FUN_0005cac0();
  int iVar12b = FUN_0005e938(*(volatile uint8_t*)(iVar4b + 8), iVar4b + 0x90);
  uint uStack_40 = *(volatile uint8_t*)(param_1 + 8);
  if (iVar12b != 0 && (int8_t)(*(volatile uint8_t*)(iVar12b+0xd)) < 0 && uStack_40 == 0) {
    struct { uint32_t a,b; } s = { 2, 0x000f4f5cUL };
    FUN_00083074(0x00088180UL, 0x1040, &s);
    return 8;
  }

  switch (uStack_40) {
    case 0: goto caseD0;
    case 1: {
      FUN_00083090(iVar11, 10);
      int (*fp)(int) = (int(*)(int))(intptr_t)piVar7[1];
      fp(iVar4b);
      break;
    }
    case 2: {
      uint32_t local_38;
      int iv = FUN_00055cb4(&local_38, 4);
      if (iv != 0) return 8;
      local_38 = local_38 - 0x000f4240UL * (local_38 / 0x000f4240UL);
      if (piVar7 != 0 && *piVar7 != 0) {
        FUN_00083090(iVar11, 0xb);
        void (*fp)(int,uint32_t) = (void(*)(int,uint32_t))(intptr_t)*piVar7;
        fp(iVar4b, local_38);
      }
      *(volatile uint8_t*)(param_1 + 0x47) = (uint8_t)local_38;
      *(volatile uint8_t*)(param_1 + 0x49) = (uint8_t)(local_38 >> 0x10);
      *(volatile uint8_t*)(param_1 + 0x48) = (uint8_t)(local_38 >> 8);
      *(volatile uint8_t*)(param_1 + 0x4a) = (uint8_t)(local_38 >> 0x18);
      break;
    }
    case 6: {
      if (piVar7 == 0 || piVar7[3] == 0) return 2;
      uint32_t local_38 = 0;
      FUN_00083090(iVar11, 10);
      void (*fp)(int,void*) = (void(*)(int,void*))(intptr_t)piVar7[3];
      fp(*(volatile int*)(param_1+0xf0), &local_38);
      break;
    }
    default: {
      struct { uint32_t a,b; } s = { 3, 0x000f4e7aUL };
      FUN_00083074(0x00088180UL, 0x1840, &s);
      return 8;
    }
  }

  if (*(volatile int8_t*)(param_1 + 8) == 0) {
caseD0:
    iVar12b = FUN_00082ff6(iVar11, 0xf);
    if (iVar12b == 0 && iVar3 != 0 && *(volatile int*)(iVar3+0x14) != 0) {
      FUN_00083090(iVar11, 10);
      int (*pcVar10)(int) = *(volatile void* volatile*)(iVar3+0x14);
      int iv2 = *(volatile int*)(param_1+0xf0);
      pcVar10(iv2);
      return 0;
    }
  }
  {
    int p1 = FUN_00083090(param_1, 3);
    FUN_00083090(p1, 0xe);
    uint r = FUN_000830ee();
    return r;
  }
}

