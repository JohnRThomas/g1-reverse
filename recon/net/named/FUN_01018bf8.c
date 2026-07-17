/* readable reconstruction; identity: FUN_01018bf8 @ 0x01018bf8
 * public-name: FUN_01018bf8
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_llcp_get_active_link_index           <= FUN_0100d760 @ 0x0100d760
 * address symbols (name @ address):
 *   g_net_ble_pending_channel_idx            @ 0x2100001c
 */
/* net-core FUN_01018bf8 @ 0x1018bf8  (parity 300 trials PROVEN) */

extern unsigned char sdc_llcp_get_active_link_index(void);
extern unsigned int  FUN_010187e0(unsigned char *, unsigned int);
extern void          FUN_010196e0(void);

unsigned int FUN_01018bf8(unsigned char *param_1)
{
  unsigned char uVar2;
  unsigned char bVar1;
  volatile unsigned char *out = (volatile unsigned char*)0x2100001c;

  uVar2 = sdc_llcp_get_active_link_index();
  bVar1 = *param_1;
  *out = uVar2;
  if ((bVar1 & 0xf) == 7) {
    return FUN_010187e0(param_1, 3);
  }
  FUN_010196e0();
  return 1;
}
