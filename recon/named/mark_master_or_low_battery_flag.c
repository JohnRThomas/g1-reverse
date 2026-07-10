/* named: mark_master_or_low_battery_flag */
/* globals referenced:
//   0x2000302f  g_low_battery_sync_flag      
*/
/* Reconstructed mark_master_or_low_battery_flag @ 0x2efc0  (parity: 300/300 trials, PROVEN) */

extern int is_battery_critical(void);
extern char *get_device_info(void);
unsigned int mark_master_or_low_battery_flag(void)
{
  int iVar1;
  char *pcVar2;
  iVar1 = is_battery_critical();
  if ((iVar1 == 1) || (pcVar2 = get_device_info(), *pcVar2 == (char)1)) {
    *(volatile unsigned char*)0x2000302fUL = 1;
  }
  return 0;
}

