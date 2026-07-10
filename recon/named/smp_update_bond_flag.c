/* named: smp_update_bond_flag */
/* globals referenced:
//   0x20002000  g_ble_dev_state              
//   0x2001d532  g_bt_settings_load_done      
*/
/* Reconstructed smp_update_bond_flag @ 0x5e5b8  (parity: 300/300 trials, PROVEN) */

extern void FUN_00055d08(unsigned int);
unsigned int smp_update_bond_flag(void)
{
  unsigned int uVar1;
  uVar1 = 0x20002a50UL;
  *(volatile unsigned char*)0x2001d532UL = ((*(volatile unsigned char*)(0x20002000UL + 0xa2)) & 6) == 6;
  FUN_00055d08(uVar1);
  return 0;
}

