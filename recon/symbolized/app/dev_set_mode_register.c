#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000841fc @ 0x000841fc
 * public-name: dev_set_mode_register
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   dev_reg_modify_bits                      <= FUN_00083e0e @ 0x00083e0e
 *   dev_set_mode_register                    <= FUN_000841fc @ 0x000841fc
 */
/* Reconstructed FUN_000841fc @ 0x841fc  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int dev_reg_modify_bits(int,int,int,int);
uint32_t dev_set_mode_register(int param_1,int param_2,char param_3,uint32_t param_4,char param_5){
  int eq = (param_2==1);
  uint32_t uVar1 = (uint8_t)(param_3 + 1);
  if(eq) uVar1 <<= 3;
  if(!eq) param_4 = uVar1 | (param_4 << 6);
  else    param_4 = uVar1 | (param_4 << 7);
  param_4 = param_4 & 0xff;
  uint32_t uVar2;
  if(param_5 == 1) uVar2 = 0xd;
  else if(param_5 == 2) uVar2 = 0xe;
  else if(param_5 != 0) return 0xffffff7a;
  else uVar2 = 0xc;
  return dev_reg_modify_bits(*(volatile int*)(param_1+0x1c), 4, uVar2, param_4 & 0xff);
}
