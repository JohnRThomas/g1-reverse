/* Reconstructed init_dashboard_info @ 0x36ed8  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int FUN_000165b4(void);
extern void FUN_00016658(void);
extern int FUN_000167a8(void);
extern void FUN_00019c70(int, int, ...);
extern int FUN_00024534(int,int,int,int,int);
extern void FUN_0004a4b4(int,int);
extern void DEBUG_PRINT(int,int,int);
#define VB(a) (*(volatile unsigned char*)(a))
#define VI(a) (*(volatile int*)(a))

void init_dashboard_info(void){
  volatile int *p40 = (volatile int*)0x2000230cUL;
  volatile int *p44 = (volatile int*)0x20007554UL;
  int iVar3, iVar4, iVar5, iVar7;
  iVar3 = FUN_000165b4();
  if (iVar3 == 0) {
    if (2 < *p40) {
      if (*p44 == 0) { DEBUG_PRINT(0x000a8eee, 0x000a95f9, 0); }
      else { FUN_00019c70(0x000a8eee, 0x000a95f9); }
    }
    FUN_00016658();
  } else {
    if (2 < *p40) {
      if (*p44 == 0) { DEBUG_PRINT(0x000a8f19, 0x000a95f9, 0); }
      else { FUN_00019c70(0x000a8f19, 0x000a95f9); }
    }
    iVar3 = FUN_000167a8();
    { unsigned int pb = VI(iVar3 + 0xfec);
      VB(pb) = 0x80; VB(pb+2) = 0x92; VB(pb+1) = 0; VB(pb+3) = 0x65; }
    iVar3 = FUN_000167a8();
    iVar3 = VI(iVar3 + 0xfec);
    VB(iVar3+6)=0; VB(iVar3+7)=0xf4; VB(iVar3+8)=0x51; VB(iVar3+9)=0xc2;
    VB(iVar3+10)=0x8c; VB(iVar3+0xc)=0; VB(iVar3+0xb)=1; VB(iVar3+0xd)=0;
    iVar3 = FUN_000167a8();
    { int q = VI(iVar3+0xfec); FUN_0004a4b4(VI(q+6), VI(q+10)); }
  }
  iVar7 = 4;
  iVar3 = 0;
  do {
    iVar4 = FUN_000167a8();
    iVar5 = VI(iVar4 + 0x1020);
    iVar4 = FUN_000167a8();
    iVar4 = FUN_00024534(iVar3, iVar5+iVar7, 0x29, iVar7+0x29+VI(iVar4+0x1020), 0x119);
    if (iVar4 == -1) {
      iVar4 = FUN_000167a8();
      VB(iVar3*0x143 + VI(iVar4+0x1020) + 3) = 0;
      if (2 < *p40) {
        if (*p44 == 0) DEBUG_PRINT(0x000a8f46, 0x000a95f9, iVar3);
        else FUN_00019c70(0x000a8f46, 0x000a95f9, iVar3);
      }
    } else if (iVar4 == 0) {
      iVar4 = FUN_000167a8();
      VB(iVar3*0x143 + VI(iVar4+0x1020) + 3) = 1;
      if (2 < *p40) {
        if (*p44 == 0) DEBUG_PRINT(0x000a8f72, 0x000a95f9, iVar3);
        else FUN_00019c70(0x000a8f72, 0x000a95f9, iVar3);
      }
    } else if (0 < *p40) {
      if (*p44 == 0) DEBUG_PRINT(0x000a8fb7, 0x000a95f9, 0);
      else FUN_00019c70(0x000a8fb7, 0x000a95f9);
    }
    iVar3++;
    iVar7 += 0x143;
    if (iVar3 == 4) return;
  } while (1);
}
