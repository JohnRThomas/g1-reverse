/* Reconstructed FUN_0001793c @ 0x1793c  (parity: 300/300 trials, PROVEN) */

extern int get_device_info(void);
extern void FUN_00017858(int, int);
extern void FUN_00072880(int);

void FUN_0001793c(int param_1, int param_2, int param_3)
{
  int iVar1;
  FUN_00017858(0x889d0, 0x200000);
  if ((param_3 == 0x200) && (*(volatile int*)0x20007bccUL != 0)) {
    *(volatile int*)0x20006a00UL = 1;
    iVar1 = get_device_info();
    FUN_00072880(iVar1 + 0xb0);
  }
  FUN_00017858(0x889d0, 0x5c00000);
}

