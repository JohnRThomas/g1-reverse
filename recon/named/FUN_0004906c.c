/* named: FUN_0004906c */
/* globals referenced:
//   0x2000a09c  g_display_thread_id          [g_obj_2000a018.f_84]
//   0x2001d446  g_display_reflash_pending    
*/
/* Reconstructed FUN_0004906c @ 0x4906c  (parity: 300/300 trials, PROVEN) */

extern void FUN_00074554(unsigned int,unsigned int);
void FUN_0004906c(void)
{
  if (*(volatile unsigned char *)0x2001d446UL == 1) {
    FUN_00074554(*(volatile unsigned int *)0x2000a09cUL, 0xfffffff2u);
    *(volatile unsigned char *)0x2001d446UL = 0;
  }
}

