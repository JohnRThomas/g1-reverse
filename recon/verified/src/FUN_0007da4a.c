/* Reconstructed FUN_0007da4a @ 0x7da4a  (parity: 300/300 trials, PROVEN) */

extern unsigned int FUN_0007d9c0(unsigned int seed, unsigned int polynomial,
        unsigned int xor_out, int reflect_input, char reflect_output,
        const unsigned char *src, int len);

unsigned int FUN_0007da4a(unsigned int seed, const unsigned char *src, int len)
{
  unsigned int uVar1;
  if (src == 0 || len < 1) {
    uVar1 = 0;
  } else {
    uVar1 = FUN_0007d9c0(seed, 0x8005, 0xffff, 1, 1, src, len);
  }
  return uVar1;
}
