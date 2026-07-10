/* named: log_msg_pool_init */
/* globals referenced:
//   0x20003648  g_log_msg_mpsc_buffer        
//   0x2000a0cc  g_log_msg_pool_ptr           
*/
/* Reconstructed log_msg_pool_init @ 0x4d508  (parity: 300/300 trials, PROVEN) */

extern void mpsc_pbuf_init(unsigned int, unsigned int);
void log_msg_pool_init(void)
{
  mpsc_pbuf_init(0x20003648UL, 0x0008aca0UL);
  *(volatile unsigned int *)0x2000a0ccUL = 0x20003648UL;
}

