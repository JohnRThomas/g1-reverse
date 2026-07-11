/* Reconstructed FUN_0005505c @ 0x5505c  true code extent: 0x34 bytes */
extern void TAIL_54ea8(unsigned char *identity);
void FUN_0005505c(unsigned char *param_1){
  if (param_1 == 0) return;
  volatile unsigned char *g = (volatile unsigned char*)0x20002000UL;
  unsigned char b120 = g[0x120];
  unsigned char b121 = g[0x121];
  if (b120 == 0 || b120 < b121) {
    g[0x121] = (unsigned char)(b121 + 1);
    *(volatile unsigned char*)(param_1 + 8) = *(volatile unsigned char*)(param_1 + 8) | 4;
    return;
  }
  TAIL_54ea8(param_1);
}
