/* named: set_time_mark */
/* globals referenced:
//   0x20007a28  g_elapsed_time_mark          
*/
/* Reconstructed set_time_mark @ 0x24d40  (parity: 300/300 trials, PROVEN) */

extern unsigned int thunk_FUN_00074f68(void);
void set_time_mark(void)
{
  unsigned int uVar1 = thunk_FUN_00074f68();
  *(volatile unsigned int *)0x20007a28UL = uVar1;
}

