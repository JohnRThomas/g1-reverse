/* Reconstructed FUN_00051074 @ 0x51074  (parity: 300/300 trials, PROVEN) */

int FUN_00051074(int param_1)
{
  int iVar1;
  unsigned int uVar2;
  unsigned int uVar3;
  iVar1 = 0x2005314c;
  uVar3 = *(volatile unsigned int*)0x2000a808UL;
  uVar2 = (unsigned int)param_1 + uVar3;
  if (uVar2 < (unsigned int)(0x20070000UL - 0x2005314cUL)) {
    *(volatile unsigned int*)0x2000a808UL = uVar2;
    iVar1 = iVar1 + uVar3;
  } else {
    iVar1 = -1;
  }
  return iVar1;
}

