/* Reconstructed FUN_00084fec @ 0x84fec  (parity: 300/300 trials, PROVEN) */

extern int FUN_0000ef12(void);
extern void FUN_00064b64(int,int,unsigned int,unsigned int);
void FUN_00084fec(int param_1,unsigned int param_2,unsigned int param_3)
{
  int iVar1;
  if (param_1 != 0) {
    iVar1 = FUN_0000ef12();
    FUN_00064b64(param_1,iVar1+1,param_2,param_3);
    return;
  }
  return;
}

