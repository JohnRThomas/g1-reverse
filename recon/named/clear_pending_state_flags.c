/* named: clear_pending_state_flags */
/* globals referenced:
//   0x20018da6  g_ancs_inbox_flag_current    
*/
/* Reconstructed clear_pending_state_flags @ 0x2ebc8  (parity: 300/300 trials, PROVEN) */

void clear_pending_state_flags(void)
{
  *(volatile unsigned char *)0x20018da6UL = 0;
  *(volatile unsigned char *)0x20018da7UL = 0;
  *(volatile unsigned char *)0x20018da8UL = 0;
}

