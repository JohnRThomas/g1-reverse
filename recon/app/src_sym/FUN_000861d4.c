/* Reconstructed FUN_000861d4 @ 0x861d4  (parity: 300/300 trials, PROVEN) */

extern long long FUN_000861ae(unsigned int);
extern void FUN_000861c2(unsigned int *, unsigned int);

int FUN_000861d4(unsigned int *param_1, unsigned int param_2, unsigned int param_3)
{
  unsigned int uVar1;
  unsigned char *pbVar2;
  long long uVar3;
  uVar3 = FUN_000861ae(param_1[5]);
  if ((int)uVar3 != 0) {
    pbVar2 = (unsigned char *)param_1[0];
    if (pbVar2 < (unsigned char *)param_1[3]) {
      if (param_3 < 0x20) {
        param_1[0] = (unsigned int)(pbVar2 + 1);
        *pbVar2 = (unsigned char)param_3 | (unsigned char)((int)(uVar3 >> 32) << 5);
        return (int)uVar3;
      }
      uVar1 = 0xe;
    } else {
      uVar1 = 8;
    }
    FUN_000861c2(param_1, uVar1);
  }
  return 0;
}

