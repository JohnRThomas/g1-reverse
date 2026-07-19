#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00083d60 @ 0x00083d60
 * public-name: dev_ctrl_write1
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   dev_ctrl_write1                          <= FUN_00083d60 @ 0x00083d60
 */
/* Reconstructed FUN_00083d60 @ 0x83d60  (parity: 300/300 trials, PROVEN) */

typedef void (*fnptr)(int, void*, int, short, void*);
void dev_ctrl_write1(int *param_1,unsigned int param_2,unsigned int param_3,unsigned int param_4)
{
  unsigned int local_14;
  unsigned int uStack_10;
  int base;
  int vt;
  fnptr f;
  unsigned short h;
  local_14 = param_2;
  uStack_10 = param_3;
  base = *param_1;
  vt = *(volatile int*)(base + 8);
  f = (fnptr)(*(volatile int*)(vt + 8));
  h = *(volatile unsigned short*)((char*)param_1 + 4);
  f(base, &local_14, 1, (short)h, param_1);
  return;
}
