/* readable reconstruction; identity: FUN_0101621c @ 0x0101621c
 * public-name: FUN_0101621c
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   rodata_102a1bf                           @ 0x0102a1bf
 */
/* net-core FUN_0101621c @ 0x101621c  (parity 300 trials PROVEN) */

void FUN_0101621c(void) {
  *(volatile unsigned int *)(0x21000078 + 0x58) = 0x0102a1bf;
  *(volatile unsigned int *)(0x21000078 + 0x60) = 0x01020195;
  *(volatile unsigned int *)(0x21000124 + 0x58) = 0x01029ef9;
  *(volatile unsigned int *)(0x21000124 + 0x5c) = 0x01015091;
}
