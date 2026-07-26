/* Reconstructed FUN_00072880 @ 0x72880  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include <cmsis_gcc.h>
extern int FUN_00072040(int);
extern void FUN_00072078(int);
extern void FUN_000738d4(void);
extern void FUN_000739f0(int,int);
extern int FUN_000744a4(int);
extern void FUN_0007e2ec(int,int);
extern void FUN_0007e2fa(int,...);
extern void FUN_0008688e(int,int);
void FUN_00072880(int object)
{
  unsigned int previous_priority = __get_BASEPRI();
  __set_BASEPRI_MAX(0x20);
  __ISB();

  if (FUN_00072040(0x2000b474) == 0) {
    FUN_0007e2fa(0x99cbd, 0xf0920, 0xf08c7, 0x72);
    FUN_0007e2fa(0xf0935, 0x2000b474);
    FUN_0007e2ec(0xf08c7, 0x72);
    return;
  }

  FUN_00072078(0x2000b474);
  int entry = FUN_000744a4(object);
  if (entry == 0) {
    unsigned int completed = *(volatile unsigned int *)(object + 8);
    if (*(volatile unsigned int *)(object + 12) != completed) {
      completed++;
    }
    *(volatile unsigned int *)(object + 8) = completed;
    FUN_0008688e(object + 0x10, 2);
  } else {
    *(volatile unsigned int *)(entry + 0x90) = 0;
    FUN_000738d4();
  }
  FUN_000739f0(0x2000b474, previous_priority);
}
