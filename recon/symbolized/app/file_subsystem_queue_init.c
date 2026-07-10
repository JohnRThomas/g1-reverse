#include "g1_app_symbols.h"
/* named: file_subsystem_queue_init */
/* globals referenced:
//   0x200079a0  g_file_msg_pipe              
*/
/* Reconstructed file_subsystem_queue_init @ 0x234e8  (parity: 300/300 trials, PROVEN) */

extern int z_impl_k_msgq_alloc_init(void *, int, int);
extern void DEBUG_PRINT(unsigned int);

int file_subsystem_queue_init(void)
{
  int iVar1;
  unsigned int format_string;

  iVar1 = z_impl_k_msgq_alloc_init((void*)((uintptr_t)&g_file_msg_pipe) /*=0x200079a0*/,0xc9,0x1e);
  format_string = "file init success\r\n" /*=0x9e810*/;
  if (iVar1 != 0) {
    format_string = "file init failed\r\n" /*=0x9e7fd*/;
  }
  DEBUG_PRINT(format_string);
  return iVar1;
}

