/* readable reconstruction; identity: FUN_01019254 @ 0x01019254
 * public-name: FUN_01019254
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_01019254 @ 0x1019254  (parity 300 trials PROVEN) */

unsigned int FUN_01019254(void)
{
  unsigned int iVar1 = 0x21000f90u;
  unsigned int iVar2;

  if (*(volatile int *)(iVar1 + 0x64) != 0) {
    *(volatile unsigned char *)(iVar1 + 0x69) = 0xff;
    *(volatile unsigned int *)(iVar1 + 0x64) = 0;
    iVar2 = 0x4100f000u;
    *(volatile unsigned char *)(iVar1 + 0x69) = 0;
    *(volatile int *)(iVar2 + 0x508) = 1 << *(volatile signed char *)(iVar1 + 0x68);
    return 0;
  }
  return 0xc;
}
