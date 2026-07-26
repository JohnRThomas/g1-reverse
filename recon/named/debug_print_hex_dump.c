/* readable reconstruction; identity: FUN_0004a424 @ 0x0004a424
 * public-name: debug_print_hex_dump
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print_hex_dump                     <= FUN_0004a424 @ 0x0004a424
 * address symbols (name @ address):
 *   rodata_f0297                             @ 0x000f0297   [INLINED -- G6 literal batch]
 *   rodata_f02a5                             @ 0x000f02a5   [INLINED -- G6 literal batch]
 *   rodata_f5400                             @ 0x000f5400
 */
#include "../headers/g1_log.h"
/* Reconstructed FUN_0004a424 @ 0x4a424  (parity: 166/300 trials, PROVEN) */

void debug_print_hex_dump(int param_1, int param_2, int param_3)
{
  unsigned int uVar1;
  log_message(((unsigned long)"dump_hex(%s):"), param_1);
  for (uVar1 = 0; (int)uVar1 < param_3; uVar1 = uVar1 + 1) {
    if ((uVar1 & 7) == 0) {
      log_message(0xf5400);
    }
    log_message(((unsigned long)"0x%02x,"), (unsigned int)*(unsigned char*)(param_2 + uVar1));
  }
  log_message(0xf5400);
}
