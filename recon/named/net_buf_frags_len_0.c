/* readable reconstruction; identity: FUN_00081bc0 @ 0x00081bc0
 * public-name: net_buf_frags_len_0
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Reconstructed net_buf_frags_len_0 @ 0x00081bc0 from Zephyr net/buf.h.
 * Raw backmap: FUN_00081bc0@0x00081bc0. */

#include <stddef.h>
#include <stdint.h>
struct net_buf_view {
    void *node_next;
    struct net_buf_view *frags;
    uint8_t ref;
    uint8_t flags;
    uint8_t pool_id;
    uint8_t user_data_size;
    uint8_t *data;
    uint16_t len;
};

size_t net_buf_frags_len_0(struct net_buf_view *buf)
{
    size_t bytes = 0;
    while (buf != 0) {
        bytes += buf->len;
        buf = buf->frags;
    }
    return bytes;
}
