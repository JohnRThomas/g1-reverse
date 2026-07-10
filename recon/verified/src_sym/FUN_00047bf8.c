/* Reconstructed FUN_00047bf8 @ 0x47bf8  (parity: 300/300 trials, PROVEN) */

extern void memset_bytes(void*, int, int);
extern int FUN_000720d0(unsigned int, void*, int, int);
extern void DEBUG_PRINT(unsigned int, unsigned int);

int FUN_00047bf8(unsigned char param_1, unsigned char param_2)
{
  unsigned char buf[6];
  buf[4] = param_1;
  buf[5] = param_2;
  memset_bytes(buf+1, 0, 0x17);
  int iVar1 = FUN_000720d0(0x2000392c, buf, 0, 0);
  if (iVar1 != 0) {
    DEBUG_PRINT(0xef058, 0xef71d);
    iVar1 = -1;
  }
  return iVar1;
}

