/* named: fd_table_lookup */
/* globals referenced:
//   0x20002550  g_fd_table                   
*/
/* Reconstructed fd_table_lookup @ 0x4b01c  (parity: 300/300 trials, PROVEN) */

extern void *thunk_FUN_00071678(void);

unsigned int fd_table_lookup(unsigned int param_1)
{
  if (param_1 < 0x10 && *(volatile int*)(param_1 * 0x28 + 0x20002550UL) != 0) {
    return 0;
  }
  unsigned int *puVar1 = (unsigned int*)thunk_FUN_00071678();
  *puVar1 = 9;
  return 0xffffffff;
}

