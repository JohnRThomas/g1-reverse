/* readable reconstruction; identity: FUN_010090c0 @ 0x010090c0
 * public-name: FUN_010090c0
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_layout_count_table                 @ 0x21000a30
 */
/* net-core FUN_010090c0 @ 0x10090c0  (parity 300 trials PROVEN) */

extern void FUN_0101f7a8(void);
extern void FUN_0101f7e0(void);

unsigned int FUN_010090c0(void)
{
  unsigned int iVar1 = 0x21000a30u;
  unsigned int uVar2;

  if ((*(volatile unsigned char *)(iVar1 + 0x2d) == 0) && (*(volatile unsigned char *)(iVar1 + 0x2c) == 0)) {
    if (*(volatile unsigned char *)(iVar1 + 0x20) == 0) {
      FUN_0101f7a8();
    } else {
      FUN_0101f7e0();
    }
    uVar2 = 0;
    *(volatile unsigned char *)(iVar1 + 0x1f) = 1;
  } else {
    uVar2 = 0xffffffff;
  }
  return uVar2;
}
