#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_net_buf__param_0172                    [param_0172; library]
 * Raw function identity: 0x00081616.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00081616 @ 0x00081616
 * public-name: net_buf_frags_len
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Reconstructed net_buf_frags_len @ 0x00081616 from configured Zephyr 3.4.99 net/buf.h.
 * Identity/backmap: FUN_00081616.
 */
#include <stddef.h>
#include <stdint.h>

struct configured_net_buf_view {
    void *node_next;
    struct configured_net_buf_view *frags;
    uint8_t ref;
    uint8_t flags;
    uint8_t pool_id;
    uint8_t user_data_size;
    uint8_t *data;
    uint16_t len;
};

size_t net_buf_frags_len(struct configured_net_buf_view *buf)
{
    size_t bytes = 0;
    while (buf != 0) {
        bytes += buf->len;
        buf = buf->frags;
    }
    return bytes;
}
