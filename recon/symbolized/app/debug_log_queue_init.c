#include "g1_app_symbols.h"
/* named: debug_log_queue_init */
/* globals referenced:
//   0x2000751c  g_debug_msg_pipe             
*/
/* Reconstructed debug_log_queue_init @ 0x19bd0  (parity: 300/300 trials, PROVEN) */

extern int z_impl_k_msgq_alloc_init(void *, int, int);
extern void DEBUG_PRINT(unsigned int);

int debug_log_queue_init(void)
{
  int iVar1;
  unsigned int format_string;

  iVar1 = z_impl_k_msgq_alloc_init((void*)((uintptr_t)&g_debug_msg_pipe) /*=0x2000751c*/,200,0x14);
  format_string = "debug init success\r\n" /*=0x9b345*/;
  if (iVar1 != 0) {
    format_string = "debug init failed\r\n" /*=0x9b331*/;
  }
  DEBUG_PRINT(format_string);
  return iVar1;
}

