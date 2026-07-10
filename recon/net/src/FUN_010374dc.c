/* net-core FUN_010374dc @ 0x10374dc  (parity 300 trials PROVEN) */

extern void FUN_01036f74(unsigned int a);
extern void FUN_0103735c(unsigned int a, unsigned int b);

void FUN_010374dc(int param_1)
{
  if (*(volatile signed char *)(param_1 + 0xd) < 0) {
    *(volatile unsigned char *)(param_1 + 0xd) = *(volatile unsigned char *)(param_1 + 0xd) & 0x7f;
    FUN_0103735c(0x21004b40u, (unsigned int)param_1);
  }
  FUN_01036f74((unsigned int)(*(volatile int *)(0x21004b28u + 8) == param_1));
  return;
}

