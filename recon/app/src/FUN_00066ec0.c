/* Reconstructed FUN_00066ec0 @ 0x66ec0  (parity: 60/60 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int uint;

extern void FUN_000500ac(int);
extern void FUN_00066e70(uint32_t,int,int,uint32_t,int);
extern void FUN_0007e2ec(uint32_t,uint32_t) __attribute__((noreturn));
extern void FUN_0007e2fa(uint32_t,uint32_t,uint32_t,uint32_t);

void FUN_00066ec0(int *param_1, uint32_t *param_2)
{
  volatile char *p1 = (volatile char*)param_1;
  volatile char *p2 = (volatile char*)param_2;
  int iVar7 = 0x2000b384;
  uint32_t uVar9 = *(volatile uint32_t*)(p2 + 0x14);
  uint32_t uVar14 = *(volatile uint8_t*)(p1 + 4);
  uint32_t uVar13;

  if (uVar9 == 0x001e8480UL) { uVar13 = 0x20000000UL; }
  else if (uVar9 <= 0x001e8480UL) {
    if (uVar9 == 0x0007a120UL) { uVar13 = 0x08000000UL; }
    else if (uVar9 <= 0x0007a120UL) {
      if (uVar9 == 0x0001e848UL) { uVar13 = 0x02000000UL; }
      else {
        if (uVar9 != 0x0003d090UL) goto FAIL;
        uVar13 = 0x04000000UL;
      }
    } else {
      if (uVar9 != 0x000f4240UL) goto FAIL;
      uVar13 = 0x10000000UL;
    }
  }
  else if (uVar9 == 0x00f42400UL) { uVar13 = 0x0a000000UL; }
  else if (uVar9 <= 0x00f42400UL) {
    if (uVar9 == 0x003d0900UL) { uVar13 = 0x40000000UL; }
    else {
      if (uVar9 != 0x007a1200UL) goto FAIL;
      uVar13 = 0x80000000UL;
    }
  }
  else {
    if (uVar9 != 0x01e84800UL) goto FAIL;
    uVar13 = 0x14000000UL;
  }
  goto SWITCH_DONE;
FAIL:
  FUN_0007e2fa(0x00099cbdUL,0x000f7a30UL,0x000f6df0UL,0x15c);
  FUN_0007e2ec(0x000f6df0UL,0x15c);
  __builtin_unreachable();
SWITCH_DONE:;

  int iVar10 = uVar14 * 0x24 + iVar7;
  *(volatile uint8_t*)(iVar10 + 0x1e) =
      (*(volatile uint8_t*)(iVar10 + 0x1e) & 0xfe) | (*(volatile uint8_t*)(p2 + 0x23) & 1);
  *(volatile uint8_t*)(((uint32_t)*(volatile uint8_t*)(p1 + 4)) * 0x24 + iVar7 + 0x1f) =
      *(volatile uint8_t*)(p2 + 0x10);

  if (*(volatile int8_t*)(p2 + 0x23) == 0) {
    uint32_t uVar15 = (*(volatile uint32_t*)(p2 + 0x14) == 0x01e84800UL) ? 3 : 0;
    FUN_00066e70(*(volatile uint32_t*)(p2 + 0), 1, 0, uVar15, (1 < *(volatile uint8_t*)(p2 + 0x18)));
    FUN_00066e70(*(volatile uint32_t*)(p2 + 4), 1, 0, uVar15, 0);
    FUN_00066e70(*(volatile uint32_t*)(p2 + 8), 0, *(volatile uint8_t*)(p2 + 0x1a), uVar15, 0);
    FUN_00066e70(*(volatile uint32_t*)(p2 + 0xc), 1, 0, uVar15, (*(volatile uint8_t*)(p2 + 0x10)) ^ 1);
    FUN_00066e70(*(volatile uint32_t*)(p2 + 0x1c), 1, 0, uVar15, 1);
  }

  uVar9 = *(volatile uint8_t*)(p1 + 4);
  int8_t cVar2 = *(volatile int8_t*)(p2 + 0x21);
  if (uVar9 == 0 || cVar2 == 0) {
    int iVar10b = uVar14 * 0x24 + iVar7;
    *(volatile uint32_t*)(iVar10b + 0x20) = *(volatile uint32_t*)(p2 + 0xc);
    *(volatile uint8_t*)(iVar10b + 0x1f) = *(volatile uint8_t*)(p2 + 0x10);
  } else {
    *(volatile uint32_t*)(uVar14 * 0x24 + iVar7 + 0x20) = 0xffffffffUL;
  }

  uint32_t uVar14b = *(volatile uint8_t*)(p2 + 0x19);
  uint8_t bVar3 = *(volatile uint8_t*)(p2 + 0x12);
  int8_t cVar4 = *(volatile int8_t*)(p2 + 0x18);
  int iVar10c = *(volatile int32_t*)(p2 + 0x1c);
  int iVar8 = (*(volatile int8_t*)(p2 + 0x21) == 0) ? -1 : *(volatile int32_t*)(p2 + 0xc);
  uint8_t bVar1 = *(volatile uint8_t*)(p2 + 0x10);
  uint8_t bVar5 = *(volatile uint8_t*)(p2 + 0x22);
  uint8_t bVar6 = *(volatile uint8_t*)(p2 + 0x20);

  if (uVar9 != 0) {
    if (cVar2 == 0) {
      uVar9 = (uint32_t)(iVar10c + 1);
      if (uVar9 != 0) uVar9 = 1;
    } else {
      uVar9 = 1;
    }
  }

  int8_t cVar2b = *(volatile int8_t*)(p2 + 0x24);
  int iVar11 = *(volatile int32_t*)p1;
  if (cVar2b == 0) {
    uint32_t uVar15b = *(volatile uint32_t*)(p2 + 4);
    uint32_t uVar12 = *(volatile uint32_t*)(p2 + 8);
    *(volatile uint32_t*)(iVar11 + 0x508) = *(volatile uint32_t*)(p2 + 0);
    *(volatile uint32_t*)(iVar11 + 0x50c) = uVar15b;
    *(volatile uint32_t*)(iVar11 + 0x510) = uVar12;
  }
  *(volatile uint32_t*)(iVar11 + 0x5c0) = (uint32_t)bVar3;
  if (uVar14b != 0) uVar14b = 1;
  *(volatile uint32_t*)(iVar11 + 0x524) = uVar13;
  if (cVar4 == 2) uVar14b |= 4;
  else if (cVar4 == 3) uVar14b |= 6;
  else if (cVar4 == 1) uVar14b |= 2;
  *(volatile uint32_t*)(iVar11 + 0x554) = uVar14b;

  if (uVar9 != 0) {
    if (cVar2b == 0) {
      if (iVar10c != -1) *(volatile int32_t*)(iVar11 + 0x56c) = iVar10c;
      int bVar16 = ((uint32_t)(iVar8 + 1) != 0);
      uint32_t uv = (uint32_t)(iVar8 + 1);
      if (bVar16) uv = bVar1;
      if (bVar16) *(volatile int32_t*)(iVar11 + 0x514) = iVar8;
      if (bVar16) *(volatile uint32_t*)(iVar11 + 0x568) = uv;
      if (bVar16) *(volatile uint32_t*)(iVar11 + 0x564) = (uint32_t)bVar5;
    }
    *(volatile uint32_t*)(iVar11 + 0x560) = (uint32_t)bVar6;
  }

  if (*(volatile int32_t*)(iVar7 + (uint32_t)*(volatile uint8_t*)(p1 + 4) * 0x24) == 0) return;
  FUN_000500ac((*(volatile int32_t*)p1 << 0xc) >> 0x18);
}
