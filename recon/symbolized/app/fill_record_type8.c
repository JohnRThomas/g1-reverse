#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000250c4 @ 0x000250c4
 * public-name: fill_record_type8
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   fill_record_type8                        <= FUN_000250c4 @ 0x000250c4
 * address symbols (name @ address):
 *   ADDR_wlcstai_record_value_len_THUMB      @ 0x0007c39d
 *   ADDR_wlcstai_record_next_fragment_THUMB  @ 0x00024ad9
 *   ADDR_wlcstai_record_encode_THUMB         @ 0x00025059
 */
/* Reconstructed FUN_000250c4 @ 0x250c4  (parity: 300/300 trials, PROVEN) */

/* P4 iteration 40: the three op-vtable words below were bare
 * original-image Thumb literals (`PROVIDE(rodata_<odd> = 0x...)`), so
 * invoke_optional_op_offset12 `bx`ed into OUR OWN relocated .text.  They
 * now take the addresses of the recovered functions through the
 * ADDR_<name>_THUMB aliases, which relocates them and roots the bodies. */
unsigned int fill_record_type8(unsigned char *param_1, unsigned int *param_2)
{
  if (param_1 != 0 && param_2 != 0) {
    *param_1 = 8;
    *(unsigned int*)(param_1+4) = ADDR_wlcstai_record_value_len_THUMB /*=0x7c39d*/;
    *(unsigned int*)(param_1+8) = ADDR_wlcstai_record_next_fragment_THUMB /*=0x24ad9*/;
    *(unsigned int*)(param_1+0xc) = ADDR_wlcstai_record_encode_THUMB /*=0x25059*/;
    *(unsigned int*)(param_1+0x10) = param_2[0];
    *(unsigned int*)(param_1+0x14) = param_2[1];
    param_1[0x18] = *((unsigned char*)param_2+8);
    return 0;
  }
  return 7;
}
