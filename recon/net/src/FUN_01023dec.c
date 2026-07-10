/* net-core FUN_01023dec @ 0x1023dec  (parity 300 trials PROVEN) */
#define P 0x210016f0

extern void FUN_010256dc(int, int);
extern unsigned int FUN_01024440(unsigned int, unsigned int, int, unsigned int);

int FUN_01023dec(unsigned int param_1)
{
  unsigned char bVar1;
  unsigned int uVar2, uVar3, uVar4, uVar5;
  int iVar6;
  unsigned char field49;

  if (*(unsigned char *)(P + 0x4a) == 0x20) {
    for (;;) {
      FUN_010256dc(0x70, 0xb86);
    }
  }
  bVar1 = *(unsigned char *)(P + 0x4a);
  uVar3 = *(unsigned char *)(P + (unsigned int)(*(unsigned char *)(P + 0x49)) * 3 + 0x30);
  if (uVar3 != 0x20) {
    field49 = *(unsigned char *)(P + 0x49);
    for (;;) {
      if (*(unsigned char *)(P + uVar3 * 32 + 0xe8) <= param_1) {
        unsigned int a = *(unsigned int *)(P + bVar1 * 32 + 0xe0);
        unsigned int b = *(unsigned int *)(P + bVar1 * 32 + 0xd8);
        unsigned int carry = ((a + b) < a) ? 1u : 0u;
        uVar2 = a + b;
        uVar5 = *(unsigned int *)(P + uVar3 * 32 + 0xd8);
        uVar3 = *(unsigned int *)(P + uVar3 * 32 + 0xdc);
        uVar4 = *(unsigned int *)(P + bVar1 * 32 + 0xdc) + carry;
        if (uVar4 < uVar3 || (uVar3 - uVar4) < (unsigned int)(uVar2 <= uVar5)) {
          iVar6 = *(int *)(P + 0);
          uVar3 = FUN_01024440(uVar5 - uVar2, uVar3, P, (uVar3 - uVar4) - (unsigned int)(uVar2 > uVar5));
          if ((unsigned int)(iVar6 + 0x76) <= uVar3) {
            return uVar3 - iVar6;
          }
        }
        return 0;
      }
      uVar3 = *(unsigned char *)(P + (uVar3 + (unsigned int)field49 * 0x20) * 2 + 0x51);
      if (uVar3 == 0x20) break;
    }
  }
  return -1;
}

