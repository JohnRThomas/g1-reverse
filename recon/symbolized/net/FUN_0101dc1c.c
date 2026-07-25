#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0101dc1c @ 0x0101dc1c
 * public-name: FUN_0101dc1c
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   rodata_101ca79                           @ 0x0101ca79
 *   rodata_102a0f1                           @ 0x0102a0f1
 */
/* net-core FUN_0101dc1c @ 0x101dc1c  (parity 300 trials PROVEN) */

void FUN_0101dc1c(void) {
  *(volatile unsigned int *)(G1N_21000354 + 0x58) = ((unsigned long)&rodata_102a0f1) /*=0x102a0f1*/;
  *(volatile unsigned int *)(G1N_21000354 + 0x5c) = 0x0102a25f;
  *(volatile unsigned int *)(G1N_21000400 + 0x58) = 0x01029ef9;
  *(volatile unsigned int *)(G1N_21000400 + 0x60) = ((unsigned long)&rodata_101ca79) /*=0x101ca79*/;
}
