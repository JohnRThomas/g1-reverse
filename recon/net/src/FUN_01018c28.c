/* net-core FUN_01018c28 @ 0x1018c28  (parity 300 trials PROVEN) */

extern unsigned char FUN_0100d760(void);
extern unsigned int FUN_010187e0(unsigned char *param_1, unsigned int x);
extern void FUN_010196e0(void);
static volatile unsigned char * const DAT_01018c54 = (unsigned char *)0x2100001c;

unsigned int FUN_01018c28(unsigned char *param_1)
{
  unsigned char bVar1;
  unsigned char uVar2;
  unsigned int uVar3;

  uVar2 = FUN_0100d760();
  bVar1 = *param_1;
  *DAT_01018c54 = uVar2;
  if ((bVar1 & 0xf) == 7) {
    uVar3 = FUN_010187e0(param_1,1);
    return uVar3;
  }
  FUN_010196e0();
  return 1;
}

