/* readable reconstruction; identity: FUN_0005a39c @ 0x0005a39c
 * public-name: gatt_cf_cfg_clear
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gatt_cf_cfg_clear                        <= FUN_0005a39c @ 0x0005a39c
 *   bt_addr_le_copy_828da                    <= FUN_000828da @ 0x000828da
 * address symbols (name @ address):
 *   rodata_f2b3a                             @ 0x000f2b3a
 */
/* Reconstructed FUN_0005a39c @ 0x5a39c, exact extent 34 bytes. */
#include <stdint.h>

extern void bt_addr_le_copy_828da(uintptr_t destination, uintptr_t source,
                         uintptr_t object, uint32_t mode);

void gatt_cf_cfg_clear(uintptr_t object, uint32_t a1, uint32_t a2, uint32_t mode)
{
    (void)a1; (void)a2;
    bt_addr_le_copy_828da(object + 1u, 0x000f2b3au, object, mode);
    *(volatile uint8_t *)(object + 8u) = 0;
    __atomic_store_n((volatile uint32_t *)(object + 0xcu), 0u,
                     __ATOMIC_RELAXED);
}
