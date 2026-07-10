#include "g1_app_symbols.h"
/* named: verify_image_checksum */
/* Reconstructed verify_image_checksum @ 0x302cc  (parity: 300/300 trials, PROVEN) */

int verify_image_checksum(void)
{
  unsigned char *pbVar1;
  int iVar2;
  int iVar3;

  iVar2 = 0;
  iVar3 = 4;
  do {
    pbVar1 = (unsigned char *)("M$\t" /*=0xa49a5*/ + iVar3);
    iVar3 = iVar3 + 1;
    iVar2 = iVar2 + (unsigned int)*(volatile unsigned char*)pbVar1;
  } while (iVar3 != 0x1be4);
  iVar2 = iVar2 - ((uintptr_t)&rodata_9244d) /*=0x9244d*/;
  if (iVar2 != 0) {
    iVar2 = -1;
  }
  return iVar2;
}

