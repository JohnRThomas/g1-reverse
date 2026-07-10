/* Reconstructed FUN_0007c3ea @ 0x7c3ea  (parity: 300/300 trials, PROVEN) */

unsigned char * FUN_0007c3ea(unsigned char *param_1)
{
  int iVar1;

  if (param_1 != (unsigned char *)0x0) {
    if ((*param_1 & 0x10) == 0) {
      iVar1 = 6;
    }
    else {
      iVar1 = 3;
    }
    if ((int)((unsigned int)*param_1 << 0x1c) < 0) {
      iVar1 = iVar1 + 1;
    }
    param_1 = (unsigned char *)((unsigned int)param_1[1] + (unsigned int)param_1[2] + iVar1);
  }
  return param_1;
}

