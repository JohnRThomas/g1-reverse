/* Reconstructed FUN_00083e70 @ 0x83e70  (parity: 300/300 trials, PROVEN) */

extern int FUN_00083d60(unsigned int, void*, int, unsigned int);
extern int FUN_00083dc8(int, int, int, int);

int FUN_00083e70(int param_1, unsigned int param_2)
{
  unsigned char buf[5];
  int iVar1;
  unsigned int r3;

  if (param_2 < 0x10000000) {
    buf[0] = 0x07;
    buf[1] = 0x08;
    buf[2] = (unsigned char)(param_2 >> 0x14);
    r3 = param_2 >> 4;
    buf[3] = (unsigned char)(r3 >> 8);
    buf[4] = (unsigned char)r3;
    iVar1 = FUN_00083d60(*(unsigned int*)(param_1+4), buf, 5, r3);
    if (iVar1 == 0) {
      iVar1 = FUN_00083dc8(param_1, 7, 3, 1);
    }
  } else {
    iVar1 = -0x16;
  }
  return iVar1;
}
