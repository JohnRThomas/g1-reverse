/* net-core FUN_01012308 @ 0x1012308  (parity 300 trials PROVEN) */

extern void FUN_01011d14(unsigned int a, void *b);

void FUN_01012308(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned short param_4)
{
  unsigned char buf[20];
  *(unsigned int *)(buf + 0) = param_1 + 0x28;
  *(unsigned short *)(buf + 4) = param_4;
  *(unsigned int *)(buf + 8) = *(unsigned int *)(param_1 + 8);
  *(unsigned short *)(buf + 0xc) = *(unsigned short *)(param_1 + 4);
  FUN_01011d14(param_2, buf);
  return;
}

