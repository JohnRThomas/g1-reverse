/* named: FUN_000809f6 */
/* Reconstructed FUN_000809f6 @ 0x809f6  (parity: 300/300 trials, PROVEN) */

extern unsigned int FUN_00051c68(void);
extern unsigned int FUN_00080a46(int a);
extern unsigned int FUN_000809b0(int a, void *b, unsigned int c, unsigned int d, unsigned int e);

int FUN_000809f6(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
  unsigned int uVar1;
  unsigned int uVar2;
  int bVar3;
  unsigned int uVar4;
  unsigned int uStack_14;
  unsigned char byte3;

  uVar1 = param_1;
  uVar4 = param_1;
  uStack_14 = param_2;
  if (3 < param_1) {
    uVar1 = FUN_00051c68();
  }
  uVar2 = FUN_00080a46((int)uVar1 >> 1);
  uStack_14 = uStack_14 & 0xffffff;
  uVar1 = FUN_000809b0((int)uVar1 >> 1, (char*)&uStack_14 + 3, param_3, 0, uVar4);
  byte3 = ((unsigned char*)&uStack_14)[3];
  if (((uVar1 == param_1) && (unsigned char)(byte3 - 1) < 2) ||
      ((uVar1 != uVar2) && (byte3 == 0))) {
    bVar3 = 1;
  } else {
    bVar3 = (uVar2 == param_1);
  }
  return bVar3;
}

