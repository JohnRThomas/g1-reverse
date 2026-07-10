/* named: expand_bytes_via_lut32 */
/* Reconstructed expand_bytes_via_lut32 @ 0x4790c  (parity: 300/300 trials, PROVEN) */

void expand_bytes_via_lut32(int param_1,int param_2,int param_3)
{
  unsigned int *base = (unsigned int *)0xd753aUL;
  __asm__ volatile ("" : "+r"(base));
  int iVar2;
  unsigned char b;
  for (iVar2 = 0; iVar2 < param_2; iVar2 = iVar2 + 1) {
    b = *(volatile unsigned char *)(param_1 + iVar2);
    *(volatile unsigned int *)(param_3 + iVar2 * 4) = *(volatile unsigned int *)((char*)base + b * 4);
  }
}

