#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00059edc @ 0x00059edc
 * public-name: ccc_set_direct
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ccc_set_direct                           <= FUN_00059edc @ 0x00059edc
 * address symbols (name @ address):
 *   rodata_88128                             @ 0x00088128
 *   rodata_f471e                             @ 0x000f471e
 */
/* Reconstructed FUN_00059edc @ 0x59edc  (parity: 300/300 trials, PROVEN) */

extern unsigned int FUN_00082a42(unsigned int,unsigned int,void*,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int);
unsigned int ccc_set_direct(unsigned int param_1,unsigned int param_2,unsigned int param_3,unsigned int param_4)
{
  unsigned int local[4];
  local[0]=2;
  local[1]=((unsigned long)&rodata_f471e) /*=0xf471e*/;
  FUN_00082a42(((unsigned long)&rodata_88128) /*=0x88128*/,0x1040,&local[0],2,param_1,param_2,param_3,param_4);
  return 0xffffffea;
}
