/* Reconstructed FUN_00086b7e @ 0x86b7e  (parity: 300/300 trials, PROVEN) */

extern int FUN_00077e4c(unsigned int a, int b, void* c);
unsigned int FUN_00086b7e(unsigned int param_1,int param_2,unsigned int *param_3,unsigned int *param_4)
{
  int iVar1;
  unsigned int uVar2;
  unsigned int uVar3;
  /* FUN_00077e4c fills an 88-byte descriptor.  This function consumes the
     flags word at offset four; keeping the complete object contiguous also
     preserves the callback's stack-object identity. */
  unsigned char descriptor[0x58];

  if ((*(short *)(param_2 + 0xe) < 0) ||
     (iVar1 = FUN_00077e4c(param_1,(int)*(short *)(param_2 + 0xe),descriptor), iVar1 < 0)) {
    uVar2 = 0;
    if ((*(unsigned short *)(param_2 + 0xc) & 0x80) == 0) {
      uVar3 = 0x400;
    } else {
      uVar3 = 0x40;
    }
  } else {
    unsigned int flags = *(unsigned int *)(descriptor + 4);
    uVar2 = (unsigned int)((flags & 0xf000) == 0x2000);
    uVar3 = 0x400;
  }
  *param_4 = uVar2;
  *param_3 = uVar3;
  return 0;
}
