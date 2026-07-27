/* Reconstructed ancs_connected @ 0x1861c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(unsigned long, ...);
extern int FUN_000167a8(void);
extern void FUN_00018334(unsigned, void*);
extern void FUN_00019c70(unsigned long, ...);
extern int FUN_00032ee4(void);
extern void FUN_00056a68(int,int);
extern unsigned int FUN_0007c0c8(void);
extern int FUN_00081526(int);
extern void FUN_0008157a(int,unsigned);
extern int FUN_00086be4(int,unsigned,int);
void ancs_connected(int param_1, int param_2)
{
  unsigned char bVar1, bVar2;
  int *piVar3; unsigned uVar4; int iVar5; unsigned uVar6;
  unsigned char auStack_38[32];
  uVar4 = FUN_00081526(param_1);
  FUN_00018334(uVar4, auStack_38);
  bVar1 = *(unsigned char*)(param_1+2);
  bVar2 = *(unsigned char*)(param_1+3);
  iVar5 = FUN_000167a8();
  uVar6 = (unsigned)*(unsigned char*)(iVar5+0x1071);
  DEBUG_PRINT(0x0009a5ae, auStack_38, (unsigned)bVar1, (unsigned)bVar2, uVar6);
  if (param_2 == 0) {
    iVar5 = FUN_00032ee4();
    if ((iVar5 == 0) && (iVar5 = FUN_000167a8(), *(char*)(iVar5+0x1071) == 0)) {
      iVar5 = FUN_000167a8();
      iVar5 = FUN_00086be4(iVar5+0x1069, uVar4, 7);
      if (iVar5 != 0) {
        if (0 < *(int*)0x2000230c) {
          if (*(int*)0x20007554 == 0)
            DEBUG_PRINT(0x0009a5f4, 0x0009b1b9, auStack_38,
                        (unsigned)*(unsigned char*)(param_1+2), (unsigned)*(unsigned char*)(param_1+3));
          else
            FUN_00019c70(0x0009a5f4, 0x0009b1b9, auStack_38,
                         (unsigned)*(unsigned char*)(param_1+2),
                         (unsigned)*(unsigned char*)(param_1+3));
        }
        FUN_00056a68(param_1, 5);
        return;
      }
    }
    FUN_0008157a(param_1, 0x20002f60);
    iVar5 = FUN_000167a8();
    uVar4 = FUN_0007c0c8();
    *(volatile unsigned*)(iVar5+0xae4) = uVar4;
    iVar5 = FUN_000167a8();
    uVar4 = FUN_0007c0c8();
    piVar3 = (int*)0x20006ab8;
    *(volatile unsigned*)(iVar5+0xae8) = uVar4;
    iVar5 = *piVar3;
    *(volatile unsigned char*)(iVar5+0x365) = 1;
    *(volatile unsigned char*)(iVar5+0x367) = 1;
    *(volatile int*)0x20007518 = param_1;
  }
  else if (0 < *(int*)0x2000230c) {
    if (*(int*)0x20007554 == 0)
      DEBUG_PRINT(0x0009a5d8, 0x0009b1b9, param_2, 0, uVar6);
    else
      FUN_00019c70(0x0009a5d8, 0x0009b1b9, param_2,
                   *(volatile unsigned*)0x20007554, uVar6);
  }
  return;
}
