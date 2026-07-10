/* Reconstructed FUN_00045764 @ 0x45764  (parity: 300/300 trials, PROVEN) */

int FUN_00045764(unsigned int param_1, int *param_2, unsigned int *param_3)
{
  int iVar2 = 0;
  unsigned int uVar1 = 0;
  unsigned short *puVar3 = (unsigned short*)0x00098fe8UL;
  unsigned int key;
  unsigned char val = 0;
  while (1) {
    if (*(volatile int*)0x0008ac34UL <= iVar2) {
      return 0;
    }
    key = *(volatile unsigned short*)puVar3;
    val = *(volatile unsigned char*)((char*)puVar3 + 2);
    puVar3 = puVar3 + 2;
    if (key == param_1) break;
    uVar1 = (uVar1 + (unsigned int)val * 0x27) & 0xffff;
    iVar2 = iVar2 + 1;
  }
  *param_2 = (unsigned int)val << 1;
  *param_3 = 0x27;
  return 0xe5248 + uVar1;
}

