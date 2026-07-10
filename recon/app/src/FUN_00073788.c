/* Reconstructed FUN_00073788 @ 0x73788  (parity: 300/300 trials, PROVEN) */

extern void FUN_00074d74(int a);
extern int FUN_000736ec(int a);
extern void FUN_00074bf4(int a,int b,int c,int d);
void FUN_00073788(int param_1)
{
  unsigned char bVar1;
  int iVar2;
  int iVar3;

  bVar1 = *(volatile unsigned char *)(0x2000b448UL + 0x10);
  iVar3 = 0x200069c8 + (unsigned int)bVar1 * 0x18;
  FUN_00074d74(iVar3);
  *(volatile unsigned char *)(0x2001d565UL + bVar1) = 0;
  iVar2 = FUN_000736ec(param_1);
  if (iVar2 != 0) {
    int t = *(volatile int *)0x2000b48cUL - 1;
    FUN_00074bf4(iVar3, 0x00073729, t, t >> 0x1f);
    return;
  }
}

