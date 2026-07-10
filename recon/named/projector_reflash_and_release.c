/* named: projector_reflash_and_release */
/* Reconstructed projector_reflash_and_release @ 0x7d874  (parity: 300/300 trials, PROVEN) */

extern void display_reflash(void*,unsigned int,unsigned int,unsigned int,unsigned int);
extern void mutex_unlock_syscall_handler(void);
unsigned int projector_reflash_and_release(unsigned int param_1,unsigned int param_2,unsigned int param_3)
{
  unsigned char buf[2];
  buf[0] = 1;
  buf[1] = (unsigned char)param_1;
  display_reflash(buf,2,param_3,1,param_1);
  mutex_unlock_syscall_handler();
  return 0;
}

