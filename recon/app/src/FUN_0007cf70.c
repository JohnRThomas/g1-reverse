/* Reconstructed FUN_0007cf70 @ 0x7cf70  (parity: 300/300 trials, PROVEN) */

extern int FUN_000302f8(int a, int *b);
extern void FUN_0003016c(int a);
int FUN_0007cf70(void)
{
  int iVar1;
  unsigned char cVar2 = 0x65;
  int local_c = 0;
  while (1) {
    iVar1 = FUN_000302f8(0x4410, &local_c);
    if (iVar1 < 0) return -1;
    if ((local_c & 1) != 0) break;
    cVar2 = cVar2 - 1;
    FUN_0003016c(1);
    if (cVar2 == 0) return -2;
  }
  return 0;
}

