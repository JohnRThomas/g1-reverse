#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00079528 @ 0x00079528
 * public-name: write_r_capture_errno
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   read                                     <= FUN_0004b088 @ 0x0004b088
 *   write_r_capture_errno                    <= FUN_00079528 @ 0x00079528
 * address symbols (name @ address):
 *   g_errno                                  @ 0x2000cc24
 */
/* Reconstructed FUN_00079528 @ 0x79528  (parity: 300/300 trials, PROVEN) */

extern int read(unsigned int,unsigned int,unsigned int,unsigned int,unsigned int);
void write_r_capture_errno(int *param_1,unsigned int param_2,unsigned int param_3,unsigned int param_4)
{
  int *piVar1;
  int iVar2;
  piVar1 = (int*)((unsigned long)&g_errno) /*=0x2000cc24*/;
  *(volatile int*)((unsigned long)&g_errno) /*=0x2000cc24*/ = 0;
  iVar2 = read(param_2,param_3,param_4,param_4,param_4);
  if ((iVar2 == -1) && (*(volatile int*)piVar1 != 0)) {
    *param_1 = *(volatile int*)piVar1;
  }
  return;
}
