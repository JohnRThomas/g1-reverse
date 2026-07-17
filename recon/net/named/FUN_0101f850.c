/* readable reconstruction; identity: FUN_0101f850 @ 0x0101f850
 * public-name: FUN_0101f850
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0101f850 @ 0x101f850  (parity 300 trials PROVEN) */

extern void FUN_0101e828(void);
extern void FUN_0101f8b0(unsigned int);
extern void FUN_010294c2(unsigned int);

void FUN_0101f850(void)
{
  unsigned int base = 0x21001230;

  FUN_010294c2(*(volatile unsigned int*)(base + 0x210));
  FUN_010294c2(*(volatile unsigned int*)(base + 0x214));
  FUN_0101e828();
  FUN_0101f8b0(0x20);
  *(volatile unsigned char*)(base + 0x218) = 0;
}
