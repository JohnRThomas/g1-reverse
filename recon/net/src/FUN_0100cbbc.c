/* net-core FUN_0100cbbc @ 0x100cbbc  (parity 300 trials PROVEN) */

unsigned int FUN_0100cbbc(unsigned int param_1)
{
  volatile unsigned char *base = (volatile unsigned char *)0x21000d18;
  if (param_1 < base[1] && base[param_1 + 0x142] == 0) {
    return (unsigned int)base + param_1 * 6 + 0x10a;
  }
  return 0;
}

