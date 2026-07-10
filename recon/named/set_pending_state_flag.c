/* named: set_pending_state_flag */
/* globals referenced:
//   0x20018da6  g_ancs_inbox_flag_current    
*/
/* Reconstructed set_pending_state_flag @ 0x2eb28  (parity: 300/300 trials, PROVEN) */

void set_pending_state_flag(unsigned int param_1,int param_2)
{
  if (param_1 < 3) {
    if (param_2 != 0) {
      *(volatile unsigned char *)(0x20018da6UL + param_1) = 1;
      return;
    }
    *(volatile unsigned char *)(0x20018da6UL + param_1) = 0;
  }
}

