/* readable reconstruction; identity: FUN_0005a540 @ 0x0005a540
 * public-name: gatt_write_ccc
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   ADDR_gatt_write_ccc_rsp_THUMB            @ 0x0005a1b1
 *   ADDR_gatt_write_ccc_buf_THUMB            @ 0x00082b6f
 */
/* gatt_write_ccc @ 0x0005a540; raw FUN_0005a540 */
#include <stdint.h>

extern int atomic_or_0(volatile long*, long); /* FUN_000826e0 */
extern int gatt_req_send(void *, void *, void *, void *, uint32_t, uint32_t); /* FUN_00082aee */

int gatt_write_ccc(void *connection, uint8_t *params)
{
    atomic_or_0((uint32_t *)(params + 0x14), 8);
    return gatt_req_send(connection, (void *)0x0005a1b1u, params,
                         (void *)0x00082b6fu, 0x12, 4);
}
