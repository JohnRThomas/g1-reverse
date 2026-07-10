#include "g1_app_symbols.h"
/* named: dev_ctrl_read1 */
/* Reconstructed dev_ctrl_read1 @ 0x83dba  (parity: 300/300 trials, PROVEN) */

extern void dev_ctrl_write2(void);
void dev_ctrl_read1(void)
{
  dev_ctrl_write2();
  return;
}

