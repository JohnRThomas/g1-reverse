/* Reconstructed FUN_00052f18 @ 0x52f18  (parity: 300/300 trials, PROVEN) */

extern unsigned int FUN_0004e374(void* a, unsigned int b, unsigned int c);
extern void FUN_00052e7c(void* a, unsigned int b, unsigned int c, int d, void* e);
extern void FUN_0007dc4a(void* a, unsigned int b, void* c);
extern int FUN_0007ddbe(void* a, unsigned int b, unsigned int c, unsigned int d);

unsigned int FUN_00052f18(unsigned int param_1, unsigned char *param_2, int param_3, unsigned int param_4, unsigned int param_5)
{
  unsigned int uVar1;
  int iVar2;
  unsigned char auStack_38[4];
  unsigned char auStack_34[36];

  if (param_3 == 0) {
    iVar2 = FUN_0007ddbe(auStack_34, 0x24, 0xf2c6b, param_1);
    if (iVar2 < 0) {
      return 0xffffffea;
    }
  } else {
    if (param_2 != 0) {
      FUN_0007dc4a(auStack_38, 4, param_2);
      param_2 = auStack_38;
    }
    FUN_00052e7c(auStack_34, 0x24, param_1, param_3, param_2);
  }
  uVar1 = FUN_0004e374(auStack_34, param_4, param_5);
  return uVar1;
}

