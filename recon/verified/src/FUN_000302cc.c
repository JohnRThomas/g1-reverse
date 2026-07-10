/* Reconstructed FUN_000302cc @ 0x302cc  (parity: 300/300 trials, PROVEN) */

int FUN_000302cc(void)
{
  unsigned char *pbVar1;
  int iVar2;
  int iVar3;

  iVar2 = 0;
  iVar3 = 4;
  do {
    pbVar1 = (unsigned char *)(0x000a49a5UL + iVar3);
    iVar3 = iVar3 + 1;
    iVar2 = iVar2 + (unsigned int)*(volatile unsigned char*)pbVar1;
  } while (iVar3 != 0x1be4);
  iVar2 = iVar2 - 0x0009244d;
  if (iVar2 != 0) {
    iVar2 = -1;
  }
  return iVar2;
}

