/* readable reconstruction; identity: FUN_00058bfc @ 0x00058bfc
 * public-name: att_fixed_chan_connected
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   att_fixed_chan_connected                 <= FUN_00058bfc @ 0x00058bfc
 *   k_work_init_delayable                    <= FUN_000732d4 @ 0x000732d4
 *   gatt_recompute_max_mtu                   <= FUN_00081c22 @ 0x00081c22
 * address symbols (name @ address):
 *   ADDR_att_timeout_THUMB                   @ 0x00059921
 */
/* Reconstructed FUN_00058bfc @ 0x58bfc */
#include <stdint.h>

extern int gatt_recompute_max_mtu(void*);
extern void k_work_init_delayable(void *object, uint32_t event);
extern void bt_gatt_connected(void *object);

void att_fixed_chan_connected(void **context)
{
    volatile uint32_t *flags =
        (volatile uint32_t *)((uint8_t *)context + 0x118);
    __atomic_fetch_or(flags, UINT32_C(4), __ATOMIC_ACQ_REL);
    gatt_recompute_max_mtu((uint8_t *)context - 8);
    k_work_init_delayable((uint8_t *)context + 0x158, UINT32_C(0x00059921));
    bt_gatt_connected(*context);
}
