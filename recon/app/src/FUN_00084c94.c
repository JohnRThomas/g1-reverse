/* Reconstructed FUN_00084c94 @ 0x84c94  (parity: 300/300 trials, PROVEN) */

extern int FUN_00083dc8(unsigned int,unsigned int,unsigned int);
void FUN_00084c94(int param_1)
{
  unsigned char *puVar2 = *(volatile unsigned char **)(param_1 + 0x10);
  unsigned int *p = *(volatile unsigned int **)(param_1 + 4);
  int iVar1 = FUN_00083dc8(*(volatile unsigned int *)p, 7, 1);
  if (-1 < iVar1) {
    *(volatile unsigned char *)puVar2 = 0;
  }
}

