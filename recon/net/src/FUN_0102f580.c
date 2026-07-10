/* net-core FUN_0102f580 @ 0x102f580  (parity 300 trials PROVEN) */
typedef unsigned int uint;
extern void tailcall_body_0102f580(void);

void FUN_0102f580(int param_1)
{
  int iVar_cmp = *(volatile int *)(0x21004b28 + 8);
  if (iVar_cmp == param_1) {
    unsigned int ipsr;
    __asm volatile ("mrs %0, ipsr" : "=r"(ipsr));
    if (ipsr != 0) {
      *(volatile uint *)(0xe000ed00 + 4) = *(volatile uint *)(0xe000ed00 + 4) | 0x10000000;
      *(volatile uint *)(0xe000ed00 + 0x24) = *(volatile uint *)(0xe000ed00 + 0x24) & 0xffff7fff;
    }
  }
  tailcall_body_0102f580();
}

