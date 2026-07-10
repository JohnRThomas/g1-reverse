/* Reconstructed FUN_00084ade @ 0x84ade  (parity: 300/300 trials, PROVEN) */

extern long long is_tx_ready(unsigned int);
extern void FUN_0008496c(unsigned int, unsigned int, unsigned int);

void FUN_00084ade(unsigned int param_1)
{
  long long uVar2;
  int iVar1;
  int field;
  uVar2 = is_tx_ready(*(unsigned int *)(param_1 + 4));
  iVar1 = (int)(uVar2 >> 32);
  field = *(int *)(iVar1 + 0xc);
  if ((int)uVar2 == 0) {
    *(unsigned char *)(field + 0xcd) = 1;
    return;
  }
  *(unsigned char *)(field + 0xcd) = 0;
  *(unsigned int *)(field + 0xbc) = 0xffffffff;
  FUN_0008496c(param_1, *(unsigned int *)(field + 0x10), *(unsigned int *)(field + 0x14));
}

