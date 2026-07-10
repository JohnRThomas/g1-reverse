/* named: set_dashboard_close_pending_flag */
/* globals referenced:
//   0x2001b80f  g_dashboard_close_pending    
*/
/* Reconstructed set_dashboard_close_pending_flag @ 0x36024  (parity: 300/300 trials, PROVEN) */

void set_dashboard_close_pending_flag(void)
{
    *(volatile unsigned char*)0x2001b80fUL = 1;
}

