/* named: mutex_lock_wait_forever_dup */
/* Reconstructed mutex_lock_wait_forever_dup @ 0x859b6  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void mutex_lock_syscall_handler(unsigned int,unsigned int,unsigned int,unsigned int);
void mutex_lock_wait_forever_dup(unsigned int param_1,unsigned int param_2)
{
  mutex_lock_syscall_handler(param_1,param_2,0xffffffff,0xffffffff);
  return;
}

