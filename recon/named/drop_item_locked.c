/* readable reconstruction; identity: FUN_0007e3ce @ 0x0007e3ce
 * public-name: drop_item_locked
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   drop_item_locked                         <= FUN_0007e3ce @ 0x0007e3ce
 */
/* CPUAPP Zephyr mpsc_pbuf drop_item_locked @ 0x0007e3ce.
 * Raw/address back-map: FUN_0007e3ce / 0x0007e3ce.
 */
#include <stdint.h>
extern uint32_t idx_inc(uint32_t *, uint32_t, int32_t); /* FUN_0007e35c */
extern void rd_idx_inc(uint32_t *, int32_t); /* FUN_0007e378 */
extern void add_skip_item(uint32_t *, int32_t); /* FUN_0007e390 */

typedef uint32_t (*get_wlen_fn)(uint32_t *);
#define drop_item_locked drop_item_locked

uint32_t drop_item_locked(uint32_t *buffer, uint32_t free_wlen,
                      uint32_t **item_to_drop, uint32_t *tmp_wr_shift)
{
    uint32_t *storage = (uint32_t *)(uintptr_t)buffer[8];
    uint32_t *item = &storage[buffer[3]];
    uint32_t raw = *item;
    *item_to_drop = 0;
    *tmp_wr_shift = 0;
    uint32_t skip_wlen = ((raw & 3u) == 2u) ? raw >> 2 : 0;
    if (skip_wlen != 0) {
        rd_idx_inc(buffer, (int32_t)skip_wlen);
        buffer[2] = buffer[3];
        return 1;
    }
    if ((buffer[4] & 2u) == 0)
        return 0;

    uint32_t item_wlen = ((get_wlen_fn)(uintptr_t)buffer[7])(item);
    raw = *item;
    if ((raw & 1u) == 0)
        return 0;
    if (raw & 2u) {
        if (free_wlen != 0)
            add_skip_item(buffer, (int32_t)free_wlen);
        buffer[1] = idx_inc(buffer, buffer[1], (int32_t)item_wlen);
        if (buffer[3] == buffer[2])
            buffer[2] = idx_inc(buffer, buffer[3], (int32_t)item_wlen);
        buffer[0] = buffer[2];
        buffer[3] = buffer[2];
        buffer[4] |= 8u;
    } else {
        rd_idx_inc(buffer, (int32_t)item_wlen);
        buffer[2] = buffer[3];
        if (free_wlen != 0)
            storage[buffer[0]] = 0;
        *tmp_wr_shift = item_wlen + free_wlen;
        buffer[0] = idx_inc(buffer, buffer[0], (int32_t)*tmp_wr_shift);
        buffer[4] |= 8u;
        *(uint8_t *)item &= 0xfeu;
        *item_to_drop = item;
    }
    return 1;
}
