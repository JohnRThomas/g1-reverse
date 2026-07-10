/* named: set_box_link_state_flag */
/* globals referenced:
//   0x2000302f  g_low_battery_sync_flag      
*/
/* Reconstructed set_box_link_state_flag @ 0x2efe4  (parity: 300/300 trials, PROVEN) */

extern void *get_device_info(void);

unsigned int set_box_link_state_flag(int param_1)
{
  unsigned char *pcVar1;

  pcVar1 = (unsigned char *)get_device_info();
  if (*pcVar1 == 1) {
    if (param_1 == 0) {
      *(volatile unsigned char*)0x2000302fUL = 0;
    }
    else {
      *(volatile unsigned char*)0x2000302fUL = 2;
    }
  }
  return 0;
}

