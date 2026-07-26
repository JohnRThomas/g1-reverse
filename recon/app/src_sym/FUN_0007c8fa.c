/* Reconstructed FUN_0007c8fa @ 0x7c8fa  (parity: 300/300 trials, PROVEN) */

extern int FUN_000257ec(int, int, void*, int, int, int);
extern void FUN_00025850(int, int, void*, int);

void FUN_0007c8fa(int param_1, int param_2)
{
  int iVar1;
  unsigned char local;
  iVar1 = FUN_000257ec(param_1, 1, &local, 1, param_1, param_2);
  if (iVar1 == 0) {
    local = (local & ~0x1f) | (param_2 & 0x1f);
    FUN_00025850(param_1, 1, &local, 1);
  }
}

