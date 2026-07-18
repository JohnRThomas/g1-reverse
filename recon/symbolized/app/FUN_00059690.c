#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00059690 @ 0x00059690
 * public-name: FUN_00059690
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_gatt_init                             <= FUN_0005a954 @ 0x0005a954
 *   g1_recon_z_impl_k_queue_init             <= FUN_000864e8 @ 0x000864e8
 *   net_pkt_skip                             <= FUN_00086502 @ 0x00086502
 * address symbols (name @ address):
 *   g_bt_att_pool                            @ 0x20003a28
 *   g_bt_gatt_indicate_ctx_pool              @ 0x2000add4
 */
/* Reconstructed FUN_00059690 @ 0x59690. */
#include <stdint.h>

#define g1_recon_z_impl_k_queue_init g1_recon_z_impl_k_queue_init
extern void g1_recon_z_impl_k_queue_init(void *queue);
extern void net_pkt_skip(void *owner,void *item);
extern void bt_gatt_init(void);

void FUN_00059690(void)
{
  void *const owner = (void *)((unsigned long)&g_bt_att_pool) /*=0x20003a28*/;
  uintptr_t item = ((unsigned long)&g_bt_gatt_indicate_ctx_pool) /*=0x2000add4*/;

  g1_recon_z_impl_k_queue_init(owner);
  for (unsigned index = 0; index < 10; ++index, item += 0x14)
    net_pkt_skip(owner,(void *)item);

  bt_gatt_init();
}
