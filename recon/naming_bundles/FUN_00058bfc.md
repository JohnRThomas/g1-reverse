### FUN_00058bfc  @ 0x00058bfc  (size=194)

callers (0): (none / root or address-taken)
callees (10): settings_load_subtree_direct, bt_settings_encode_key, k_work_init_delayable, u8_to_dec, bt_addr_le_is_bonded, g1_recon_bt_conn_set_security, bt_conn_get_security, FUN_00081c22, FUN_00082a42, bt_gatt_foreach_attr_0
strings: "Failed to set security for bonded peer (%d)"

```c
/* readable reconstruction; identity: FUN_00058bfc @ 0x00058bfc
 * public-name: FUN_00058bfc
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   k_work_init_delayable                    <= FUN_000732d4 @ 0x000732d4
 * address symbols (name @ address):
 *   ADDR_att_timeout_THUMB                   @ 0x00059921
 */
/* Reconstructed FUN_00058bfc @ 0x58bfc */
#include <stdint.h>

extern void FUN_00081c22(void *object);
extern void k_work_init_delayable(void *object, uint32_t event);
extern void bt_gatt_connected(void *object);

void FUN_00058bfc(void **context)
{
    volatile uint32_t *flags =
        (volatile uint32_t *)((uint8_t *)context + 0x118);
    __atomic_fetch_or(flags, UINT32_C(4), __ATOMIC_ACQ_REL);
    FUN_00081c22((uint8_t *)context - 8);
    k_work_init_delayable((uint8_t *)context + 0x158, UINT32_C(0x00059921));
    bt_gatt_connected(*context);
}
```