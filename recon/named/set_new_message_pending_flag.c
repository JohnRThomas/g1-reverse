/* named: set_new_message_pending_flag */
/* globals referenced:
//   0x2001b80e  g_new_message_pending_flag   
*/
/* Reconstructed set_new_message_pending_flag @ 0x36030  (parity: 300/300 trials, PROVEN) */

void set_new_message_pending_flag(void)
{
    *(volatile unsigned char*)0x2001b80eUL = 1;
}

