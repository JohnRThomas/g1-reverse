/* readable reconstruction; identity: FUN_0100a9b0 @ 0x0100a9b0
 * public-name: FUN_0100a9b0
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0100a9b0 @ 0x100a9b0  (parity 300 trials PROVEN) */

int FUN_0100a9b0(void) {
  unsigned int base = 0x21000bf8;
  unsigned short a = *(volatile unsigned short *)(base + 0x34);
  unsigned short b = *(volatile unsigned short *)(base + 0x38);
  if (a != b) return 1;
  return *(volatile unsigned char *)(base + 0x32) == 0;
}
