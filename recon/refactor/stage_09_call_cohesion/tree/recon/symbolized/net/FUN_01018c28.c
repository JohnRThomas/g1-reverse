#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01018c28 @ 0x01018c28
 * public-name: FUN_01018c28
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_llcp_get_active_link_index           <= FUN_0100d760 @ 0x0100d760
 * address symbols (name @ address):
 *   g_net_ble_pending_channel_idx            @ 0x2100001c
 */
/* net-core FUN_01018c28 @ 0x1018c28  (parity 300 trials PROVEN) */

extern unsigned char sdc_llcp_get_active_link_index(void);
extern unsigned int FUN_010187e0(unsigned char *param_1, unsigned int x);
extern void FUN_010196e0(void);
static volatile unsigned char * const DAT_01018c54 = (unsigned char *)((unsigned long)&g_net_ble_pending_channel_idx) /*=0x2100001c*/;

unsigned int FUN_01018c28(unsigned char *param_1)
{
  unsigned char bVar1;
  unsigned char uVar2;
  unsigned int uVar3;

  uVar2 = sdc_llcp_get_active_link_index();
  bVar1 = *param_1;
  *DAT_01018c54 = uVar2;
  if ((bVar1 & 0xf) == 7) {
    uVar3 = FUN_010187e0(param_1,1);
    return uVar3;
  }
  FUN_010196e0();
  return 1;
}
