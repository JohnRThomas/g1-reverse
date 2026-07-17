/* readable reconstruction; identity: FUN_0101f974 @ 0x0101f974
 * public-name: FUN_0101f974
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0101f974 @ 0x101f974  (parity 300 trials PROVEN) */

extern void FUN_0100eec8(void *, unsigned int);
void FUN_0101f974(int param_1) {
  unsigned char *r0 = *(unsigned char **)(param_1 + 4);
  unsigned int r1 = 0x1029e75;
  unsigned short r3 = *(unsigned short *)r0;
  *(unsigned short *)(r0 + 0x1fe) = r3;
  r3 = *(unsigned short *)(r0 + 0x66);
  r0 = r0 + 0x1f5;
  *(unsigned short *)(r0 + 0xb) = r3;
  FUN_0100eec8(r0, r1);
}
