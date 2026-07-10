/* net-core FUN_0102edac @ 0x102edac  (parity 300 trials PROVEN) */
/* net-core FUN_0102edac @ 0x102edac  (parity 300 trials PROVEN) */
/* net-core FUN_0102edac @ 0x102edac  (parity 300 trials PROVEN) */

extern void FUN_0103b614(int,int);
extern void FUN_0103b62e(int,int,int);
int FUN_0102edac(int param_1, int param_2)
{
  unsigned int c_edf8=1, c_edfc=0, c_ee00=4, c_ee04=4;
  int c_ee08=0x0103c0fc;
  unsigned int iVar3 = c_edf8 * (((c_edfc + c_edf8) - 1) / c_edf8);
  unsigned int iVar2 = c_ee04 * (((c_ee00 + c_ee04) - 1) / c_ee04) + iVar3;
  int p2 = param_2 - (int)iVar2;
  FUN_0103b614(p2, c_ee08);
  FUN_0103b62e(p2 + (int)iVar3, 0, (int)c_ee00);
  *(volatile int*)(param_1+0x88) = p2 - 8;
  return (int)iVar2 + 8;
}



