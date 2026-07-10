/* net-core FUN_010202a8 @ 0x10202a8  (parity 300 trials PROVEN) */

int FUN_010202a8(void)
{
  unsigned int base = 0x210015f0u;
  unsigned int lit = 0x0103c4d0u;
  unsigned int idx = *(volatile unsigned char *)(base + 0x28);
  unsigned int iVar1 = lit + idx * 4;
  int r0 = *(volatile int *)(base + 0x24) - *(volatile int *)(base + 0x20);
  int diff = (*(volatile int *)(iVar1 + 0x4c) + 999) - *(volatile int *)(iVar1 + 0x70);
  r0 = r0 + *(volatile int *)(iVar1 + 0x28);
  unsigned long long prod = (unsigned long long)0x10624dd3u * (unsigned long long)(unsigned int)diff;
  unsigned int hi = (unsigned int)(prod >> 32);
  return r0 + (int)(hi >> 6);
}

