/* readable reconstruction; identity: FUN_000836e8 @ 0x000836e8
 * public-name: net_buf_get
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Reconstructed net_buf_get @ 0x836e8 (raw FUN_000836e8). */
#include <stdint.h>

extern void *net_buf_get_impl(void *fifo, uint64_t timeout); /* FUN_000727ac */

void *net_buf_get(void *fifo, uint64_t timeout)
{
    return net_buf_get_impl(fifo, timeout);
}
