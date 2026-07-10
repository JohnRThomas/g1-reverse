/* named: FUN_00080b32 */
/* Reconstructed FUN_00080b32 @ 0x80b32  (parity: 300/300 trials, PROVEN) */

unsigned int FUN_00080b32(unsigned char *param_1) {
  if (*(unsigned int*)(param_1 + 0x40) != 0) {
    return (unsigned int)*(unsigned short*)(param_1 + 0x44);
  }
  return 0xffffffea;
}

