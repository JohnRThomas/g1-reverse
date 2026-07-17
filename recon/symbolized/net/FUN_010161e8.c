#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_010161e8 @ 0x010161e8
 * public-name: FUN_010161e8
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   rodata_10102c1                           @ 0x010102c1
 */
/* net-core FUN_010161e8 @ 0x10161e8  (parity 300 trials PROVEN) */

void FUN_010161e8(void) {
  *(volatile unsigned int *)(0x21000078 + 0x50) = 0x01015241;
  *(volatile unsigned int *)(0x21000078 + 0x54) = 0x01010305;
  *(volatile unsigned int *)(0x21000124 + 0x50) = ((unsigned long)&rodata_10102c1) /*=0x10102c1*/;
  *(volatile unsigned int *)(0x21000124 + 0x54) = 0x01015201;
}
