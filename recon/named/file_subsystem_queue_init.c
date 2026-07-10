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

  iVar1 = z_impl_k_msgq_alloc_init((void*)0x200079a0UL,0xc9,0x1e);
  format_string = 0x0009e810UL;
  if (iVar1 != 0) {
    format_string = 0x0009e7fdUL;
  }
  DEBUG_PRINT(format_string);
  return iVar1;
}

