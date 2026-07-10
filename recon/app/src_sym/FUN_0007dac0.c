/* Reconstructed FUN_0007dac0 @ 0x7dac0  (parity: 300/300 trials, PROVEN) */

extern int update_burial_point_day_index(void);
extern int get_device_info(void);
unsigned char FUN_0007dac0(void)
{
  unsigned char uVar1;
  int iVar2;
  iVar2 = update_burial_point_day_index();
  if (iVar2 == 0) {
    iVar2 = get_device_info();
    uVar1 = *(volatile unsigned char *)(iVar2 + 0x10db);
  } else {
    uVar1 = 7;
  }
  return uVar1;
}

