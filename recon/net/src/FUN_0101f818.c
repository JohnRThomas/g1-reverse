/* net-core FUN_0101f818 @ 0x101f818  (parity 300 trials PROVEN) */

extern void FUN_0100ebc4(void);
extern void FUN_0100f5d8(void);
extern void FUN_0101e888(void);
extern void FUN_010294c2(unsigned int);

void FUN_0101f818(unsigned int param_1, unsigned int param_2)
{
  unsigned int base = 0x21001230;

  FUN_0100ebc4();
  *(volatile unsigned int*)(base + 0x104) = param_2;
  FUN_010294c2(*(volatile unsigned int*)(base + 0x20c));
  FUN_0101e888();
  FUN_0100f5d8();
  *(volatile unsigned char*)(base + 0x218) = 1;
}

