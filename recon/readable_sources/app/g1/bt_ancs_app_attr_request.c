#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_bt_ancs_client_ctx__param_0158         [param_0158; G1-original]
 * Raw function identity: 0x0007f7d2.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0007f7d2 @ 0x0007f7d2
 * public-name: bt_ancs_app_attr_request
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_ancs_cp_write                         <= FUN_0004f198 @ 0x0004f198
 *   bt_ancs_app_attr_request                 <= FUN_0007f7d2 @ 0x0007f7d2
 *   net_buf_simple_init_with_data            <= FUN_000836ec @ 0x000836ec
 *   net_buf_simple_tailroom                  <= FUN_00083730 @ 0x00083730
 *   net_buf_simple_add_mem                   <= FUN_00083740 @ 0x00083740
 *   net_buf_push_u8                          <= FUN_00083758 @ 0x00083758
 */
/* Reconstructed FUN_0007f7d2 @ 0x0007f7d2 (bt_ancs_app_attr_request).
 * Exact configured NCS ANCS app-attribute request owner; extent 0xc2.
 */
#include <stdint.h>
extern void net_buf_simple_init_with_data(void *, void *, uint32_t); /* net_buf_simple_init_with_data */
extern int net_buf_simple_tailroom(int);               /* net_buf_simple_tailroom */
extern void net_buf_push_u8(void *, uint8_t);          /* net_buf_simple_add_u8 */
extern void net_buf_simple_add_mem(void *, const void *, uint32_t); /* net_buf_simple_add_mem */
extern int bt_ancs_cp_write(void *, uint16_t, void *);  /* bt_ancs_cp_write */

struct simple_buffer_recovered {
    uint8_t *data;
    uint16_t length;
    uint16_t size;
    uint8_t *storage;
};

int bt_ancs_app_attr_request(uint8_t *client, const uint8_t *app_id,
                 uint32_t app_id_length, void *callback)
{
    if (app_id_length == 0U)
        return -22;
    client[0x908] = 0;
    if ((__atomic_fetch_or((uint32_t *)(client + 4), 4U,
                           __ATOMIC_SEQ_CST) & 4U) != 0U)
        return -16;
    struct simple_buffer_recovered buffer;
    net_buf_simple_init_with_data(&buffer, client + 0x28, 0x800U);
    buffer.data = buffer.storage;
    buffer.length = 0;
    if (net_buf_simple_tailroom(&buffer) < 1U)
        return -12;
    net_buf_push_u8(&buffer, 1U);
    if (net_buf_simple_tailroom(&buffer) < app_id_length + 1U)
        return -12;
    net_buf_simple_add_mem(&buffer, app_id, app_id_length);
    net_buf_push_u8(&buffer, 0U);
    *(uint32_t *)(client + 0x8f8) = 0;
    if (client[0x8e8] != 0U) {
        if (net_buf_simple_tailroom(&buffer) < 1U)
            return -12;
        net_buf_push_u8(&buffer, 0U);
        *(uint32_t *)(client + 0x8f8) = 1;
    }
    int error = bt_ancs_cp_write(client, buffer.length, callback);
    *(uint32_t *)(client + 0x904) = *(uint32_t *)(client + 0x8f8);
    return error;
}
