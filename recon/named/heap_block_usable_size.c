/* named: heap_block_usable_size */
/* Reconstructed heap_block_usable_size @ 0x87996  (parity: 300/300 trials, PROVEN) */

int heap_block_usable_size(unsigned int param_1,char *param_2)
{
  int iVar1 = *(int *)(param_2 - 4);
  int r0 = iVar1 - 4;
  if (iVar1 < 0) {
    r0 = r0 + *(int *)(param_2 + r0);
  }
  return r0;
}

