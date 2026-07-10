#include "g1_app_symbols.h"
/* named: mutex_lock_wait_forever */
/* Reconstructed mutex_lock_wait_forever @ 0x8583a  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void mutex_lock_syscall_handler(unsigned int,unsigned int,unsigned int,unsigned int);
void mutex_lock_wait_forever(unsigned int param_1,unsigned int param_2)
{
  mutex_lock_syscall_handler(param_1,param_2,0xffffffff,0xffffffff);
  return;
}

