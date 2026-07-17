/* readable reconstruction; identity: FUN_01013d64 @ 0x01013d64
 * public-name: FUN_01013d64
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_radio_ack_pending_flag             @ 0x21000f54
 */
/* net-core FUN_01013d64 @ 0x1013d64  (parity 300 trials PROVEN) */

extern unsigned int FUN_010202f0(void);

unsigned char FUN_01013d64(unsigned int param_1)
{
  unsigned int uVar1;
  unsigned int base = 0x21000f54;

  uVar1 = FUN_010202f0();
  if ((uVar1 <= *(volatile unsigned int *)(base + 0xc)) &&
      (0x1d4b < *(unsigned int *)(param_1 + 0x14))) {
    return (*(volatile unsigned char *)(base + 0x10)) ^ 1;
  }
  return 0;
}
