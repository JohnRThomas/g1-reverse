/* Reconstructed FUN_00078570 @ 0x78570  (parity: 300/300 trials, PROVEN) */

extern int FUN_000807de(unsigned int);
void FUN_00078570(int *param_1,unsigned int param_2)
{
  *(volatile int *)0x2000cc24UL = 0;
  int iVar2 = FUN_000807de(param_2);
  if (iVar2 == -1) {
    int v = *(volatile int *)0x2000cc24UL;
    if (v != 0) {
      *(volatile int *)param_1 = v;
    }
  }
}

