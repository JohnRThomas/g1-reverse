/* Reconstructed FUN_00082572 @ 0x82572  (parity: 300/300 trials, PROVEN) */

extern int FUN_0005858c(void);
extern void atomic_clear_bit_0(int *a, int b);
void FUN_00082572(void)
{
  int iVar1;
  int *piVar2;

  iVar1 = FUN_0005858c();
  if (iVar1 != 0) {
    for (piVar2 = *(volatile int **)(iVar1 + 0x30); piVar2 != (int *)0; piVar2 = (int *)*(volatile int *)piVar2) {
      atomic_clear_bit_0(piVar2 + -0x1c, 5);
    }
  }
}

