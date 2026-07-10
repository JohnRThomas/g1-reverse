/* Reconstructed FUN_0005b9cc @ 0x5b9cc  (parity: 28/60 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int uint;
typedef unsigned short ushort;

extern void FUN_0007e2ec(uint32_t,uint32_t);
extern void FUN_0007e2fa(uint32_t,uint32_t,uint32_t,uint32_t);
extern int FUN_00080d3e(void*,void*);
extern void FUN_00082a42(uint32_t,uint32_t,void*);
extern uint32_t FUN_00082aee(int,uint32_t,int*,uint32_t);

int FUN_0005b9cc(int param_1, int *param_2)
{
  uint32_t uVar4;
  if (param_1 == 0) {
    FUN_0007e2fa(0x000f3ebdUL,0x000f46b8UL,0x00099cbdUL,0x118f);
    for (;;) { FUN_0007e2ec(0x000f46b8UL, 0x118f); FUN_0007e2fa(0x000f4a0aUL,0,0,0); }
  }
  if (param_2 == 0 || param_2[1] == 0) {
    FUN_0007e2fa(0x000f4c07UL,0x000f46b8UL,0x00099cbdUL,0x1190);
    for (;;) { FUN_0007e2ec(0x000f46b8UL, 0x1190); FUN_0007e2fa(0x000f4a0aUL,0,0,0); }
  }
  ushort a = *(volatile ushort*)((char*)param_2 + 8);
  ushort b = *(volatile ushort*)((char*)param_2 + 0xe);
  if (a == 0 || b == 0) {
    FUN_0007e2fa(0x000f4c1eUL,0x000f46b8UL,0x00099cbdUL,0x1191);
    for (;;) { FUN_0007e2ec(0x000f46b8UL, 0x1191); FUN_0007e2fa(0x000f4a0aUL,0,0,0); }
  }
  if (a > b) {
    FUN_0007e2fa(0x000f4c4bUL,0x000f46b8UL,0x00099cbdUL,0x1193);
    for (;;) { FUN_0007e2ec(0x000f46b8UL, 0x1193); FUN_0007e2fa(0x000f4a0aUL,0,0,0); }
  }

  if (*(volatile uint8_t*)(param_1 + 0xd) != 7) return 0xffffff80;

  uint local_30 = *(volatile uint8_t*)((char*)param_2 + 0x10);
  uint32_t uVar4arg = 0, uVar5arg = 0;
  switch (local_30) {
    case 0: case 1: {
      uint8_t *pv = *(volatile uint8_t**)param_2;
      if (pv == 0) {
        uVar4arg=0x000827afUL; uVar5arg=4;
      } else {
        uint8_t v = *(volatile uint8_t*)pv;
        if (v == 0) {
          uVar4arg=0x00082d6bUL; uVar5arg=0x00082a67UL;
        } else if (v == 2) {
          uVar4arg=0x00082d6bUL; uVar5arg=0x00082a67UL;
        } else {
          uint32_t local_38 = 3;
          FUN_00082a42(0x00088128UL, 0x1840, &local_38);
          return 0xffffffea;
        }
      }
      break;
    }
    case 4: {
      if (*param_2 != 0) {
        uint8_t buf[4];
        int iVar3;
        buf[0]=0; iVar3=FUN_00080d3e((void*)(uintptr_t)*param_2, buf); if (iVar3==0) return 0xffffffea;
        buf[0]=0; iVar3=FUN_00080d3e((void*)(uintptr_t)*param_2, buf); if (iVar3==0) return 0xffffffea;
        buf[0]=0; iVar3=FUN_00080d3e((void*)(uintptr_t)*param_2, buf); if (iVar3==0) return 0xffffffea;
        buf[0]=0; iVar3=FUN_00080d3e((void*)(uintptr_t)*param_2, buf); if (iVar3==0) return 0xffffffea;
      }
    }
    case 5:
      uVar4arg = 0x0005c0bdUL; uVar5arg = 0x00082773UL;
      break;
    case 6: {
      char *pcVar2 = (char*)(uintptr_t)*param_2;
      if (pcVar2 == 0) return 0xffffffea;
      char cVar1 = *(volatile char*)pcVar2;
      if (cVar1 != 0) return 0xffffffea;
      uint8_t buf[4]; int iVar3;
      buf[0]=cVar1; iVar3=FUN_00080d3e(pcVar2, buf);
      if (iVar3 != 0) {
        buf[0]=cVar1; iVar3=FUN_00080d3e((void*)(uintptr_t)*param_2, buf);
        if (iVar3 != 0) {
          buf[0]=cVar1; iVar3=FUN_00080d3e((void*)(uintptr_t)*param_2, buf);
          if (iVar3 != 0) {
            buf[0]=cVar1; iVar3=FUN_00080d3e((void*)(uintptr_t)*param_2, buf);
            if (iVar3 == 0) return 0xffffffea;
          }
        }
      }
    }
    case 2: case 3:
      uVar4arg = 0x0005bd19UL; uVar5arg = 0x000827dfUL;
      break;
    default: {
      uint32_t local_38 = 3;
      FUN_00082a42(0x00088128UL, 0x1840, &local_38);
      return 0xffffffea;
    }
  }
  uVar4 = FUN_00082aee(param_1, uVar4arg, param_2, uVar5arg);
  return uVar4;
}

