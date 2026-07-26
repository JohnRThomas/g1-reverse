#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00032ef0 @ 0x00032ef0
 * public-name: set_test_mode
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   set_test_mode                            <= FUN_00032ef0 @ 0x00032ef0
 *   log_message                              <= FUN_0007dda4 @ 0x0007dda4
 * address symbols (name @ address):
 *   rodata_a756a                             @ 0x000a756a   [INLINED -- G6 literal batch]
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_test_mode_flag                         @ 0x20019ef3
 */
/* Reconstructed FUN_00032ef0 @ 0x32ef0  (parity: 300/300 trials, PROVEN) */

extern void log_message(unsigned int, ...);
extern void debug_print(unsigned int, ...);

void set_test_mode(unsigned int param_1)
{
  if (*(volatile unsigned int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
    log_message(((unsigned long)"set testmode is %d \n") /*=0xa756a*/, param_1);
  }
  else {
    debug_print(((unsigned long)"set testmode is %d \n") /*=0xa756a*/, param_1);
  }
  *(volatile unsigned char*)((unsigned long)&g_test_mode_flag) /*=0x20019ef3*/ = (unsigned char)param_1;
  return;
}
