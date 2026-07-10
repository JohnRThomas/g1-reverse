/* named: FUN_00086b7e */
/* Reconstructed FUN_00086b7e @ 0x86b7e  (parity: 300/300 trials, PROVEN) */

extern int _fstat_r(unsigned int a, int b, void* c);
unsigned int FUN_00086b7e(unsigned int param_1,int param_2,unsigned int *param_3,unsigned int *param_4)
{
  int iVar1;
  unsigned int uVar2;
  unsigned int uVar3;
  unsigned char auStack_68[4];
  unsigned int local_64;

  if ((*(short *)(param_2 + 0xe) < 0) ||
     (iVar1 = _fstat_r(param_1,(int)*(short *)(param_2 + 0xe),auStack_68), iVar1 < 0)) {
    uVar2 = 0;
    if ((*(unsigned short *)(param_2 + 0xc) & 0x80) == 0) {
      uVar3 = 0x400;
    } else {
      uVar3 = 0x40;
    }
  } else {
    local_64 = *(unsigned int *)(auStack_68 + 4);
    uVar2 = (unsigned int)((local_64 & 0xf000) == 0x2000);
    uVar3 = 0x400;
  }
  *param_4 = uVar2;
  *param_3 = uVar3;
  return 0;
}

