/* Reconstructed FUN_00019c44 @ 0x19c44  (parity: 300/300 trials, PROVEN) */

extern int FUN_00072240(unsigned int a0, void *a1, unsigned int a2, unsigned int a3);
extern void FUN_00086c04(unsigned int a0, void *a1, unsigned int a2);

int FUN_00019c44(unsigned int param_1)
{
  int iVar1;
  unsigned char auStack_d8[204];
  iVar1 = FUN_00072240(0x2000751c, auStack_d8, 0, 0);
  if (iVar1 == 0) {
    FUN_00086c04(param_1, auStack_d8, 200);
  }
  return iVar1;
}

