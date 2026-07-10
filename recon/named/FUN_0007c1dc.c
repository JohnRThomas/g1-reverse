/* named: FUN_0007c1dc */
/* Reconstructed FUN_0007c1dc @ 0x7c1dc  (parity: 300/300 trials, PROVEN) */

extern int get_device_info(void);
extern void FUN_0007c176(void);
unsigned int FUN_0007c1dc(unsigned char param_1, unsigned char param_2, int param_3)
{
  int iVar1;
  if (param_3 == 0) {
    iVar1 = get_device_info();
    *(volatile unsigned char *)(iVar1 + 0xcf) = param_2;
    iVar1 = get_device_info();
    *(volatile unsigned char *)(iVar1 + 0xcd) = param_1;
  } else {
    FUN_0007c176();
  }
  return 0;
}

