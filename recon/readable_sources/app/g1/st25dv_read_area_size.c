#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00024d50 @ 0x00024d50
 * public-name: st25dv_read_area_size
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   st25dv_read_area_size                    <= FUN_00024d50 @ 0x00024d50
 *   ipc_read_u16_field                       <= FUN_0007c968 @ 0x0007c968
 * address symbols (name @ address):
 *   g_st25dv_dev                             @ 0x20007a44
 */
/* Reconstructed FUN_00024d50 @ 0x24d50  (parity: 300/300 trials, PROVEN) */

extern void ipc_read_u16_field(unsigned int, void *, unsigned int, unsigned int, unsigned int);

int st25dv_read_area_size(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
  int iVar1;
  unsigned int local_c;
  unsigned int uStack_8;

  local_c = param_2;
  uStack_8 = param_3;
  ipc_read_u16_field(*(volatile unsigned int*)((unsigned long)&g_st25dv_dev) /*=0x20007a44*/,&local_c,param_3,((unsigned long)&g_st25dv_dev) /*=0x20007a44*/,param_1);
  iVar1 = (int)(local_c >> 0x10) + 1;
  return (int)(local_c & 0xff) * iVar1 + iVar1;
}
