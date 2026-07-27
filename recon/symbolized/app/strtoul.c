#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00077c1c @ 0x00077c1c
 * public-name: strtoul
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   _strtoul_r                               <= FUN_00077b38 @ 0x00077b38
 *   strtoul                                  <= FUN_00077c1c @ 0x00077c1c
 * address symbols (name @ address):
 *   g_libc_heap_ctrl                         @ 0x20002d20
 */
/* Reconstructed FUN_00077c1c @ 0x77c1c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern unsigned _strtoul_r(int, unsigned char*, void*, unsigned);
int strtoul(int param_1, int param_2, int param_3) {
  return _strtoul_r(*(volatile int*)((unsigned long)&g_libc_heap_ctrl) /*=0x20002d20*/, param_1, param_2, param_3);
}
