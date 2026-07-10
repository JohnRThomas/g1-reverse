/* Reconstructed FUN_000778f4 @ 0x778f4  (parity: 300/300 trials, PROVEN) */

extern int FUN_00051074(unsigned int);
void FUN_000778f4(int *param_1,unsigned int param_2)
{
  *(volatile int *)0x2000cc24UL = 0;
  int iVar2 = FUN_00051074(param_2);
  if (iVar2 == -1) {
    int v = *(volatile int *)0x2000cc24UL;
    if (v != 0) {
      *(volatile int *)param_1 = v;
    }
  }
}

