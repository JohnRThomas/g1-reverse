/* readable reconstruction; identity: FUN_00081e2a @ 0x00081e2a
 * public-name: att_chan_read
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   att_chan_read                            <= FUN_00081e2a @ 0x00081e2a
 */
/* CPUAPP Zephyr Bluetooth att_chan_read @ 0x00081e2a.
 * Raw/address back-map: FUN_00081e2a / 0x00081e2a.
 */
#include <stdint.h>
extern uint64_t net_buf_frags_len(void *); /* FUN_00081bc0 */
extern void *net_buf_frag_last(void *); /* FUN_0005f304 */
extern uint32_t net_buf_tailroom(void *); /* FUN_00083730 */
extern uint64_t net_buf_pool_get(uint8_t); /* FUN_0005ee08 */
extern void *net_buf_alloc(uint32_t, uint32_t, uint32_t, uint32_t); /* FUN_000836de */
extern void net_buf_frag_add(void *, void *); /* FUN_0005f390 */
extern void net_buf_add(void *, uint32_t); /* FUN_0005f5d0 */

typedef int32_t (*attribute_read_fn)(void *, void *, void *, uint16_t, uint16_t);
typedef int (*read_filter_fn)(void *, uint32_t, void *);
#define att_chan_read att_chan_read

uint32_t att_chan_read(uint8_t *chan, void *attribute, uint8_t *buffer,
                      uint32_t offset, read_filter_fn filter, void *user_data)
{
    uint32_t mtu = *(uint16_t *)(chan + 0x1e);
    uint32_t enhanced_mtu = *(uint16_t *)(chan + 0x2e);
    if (enhanced_mtu < mtu) mtu = enhanced_mtu;
    if ((uint32_t)net_buf_frags_len(buffer) >= mtu)
        return 0;

    void *connection = *(void **)(chan + 8);
    uint8_t *fragment = net_buf_frag_last(buffer);
    uint32_t total = 0;
    for (;;) {
        uint32_t current = (uint32_t)net_buf_frags_len(buffer);
        uint32_t room_needed = mtu - current;
        uint32_t tailroom = net_buf_tailroom(fragment + 0x0c);
        uint32_t length = room_needed < tailroom ? room_needed : tailroom;
        if (length == 0) {
            uint64_t pool = net_buf_pool_get(buffer[10]);
            fragment = net_buf_alloc((uint32_t)pool,
                                     (uint32_t)(pool >> 32), 0, 0);
            if (fragment == 0)
                return total;
            net_buf_frag_add(buffer, fragment);
            current = (uint32_t)net_buf_frags_len(buffer);
            room_needed = mtu - current;
            tailroom = net_buf_tailroom(fragment + 0x0c);
            length = room_needed < tailroom ? room_needed : tailroom;
        }
        void *destination = *(void **)(fragment + 0x0c) +
                            *(uint16_t *)(fragment + 0x10);
        int32_t read = ((attribute_read_fn)(uintptr_t)
                        *(uint32_t *)((uint8_t *)attribute + 4))(
                            connection, attribute, destination,
                            (uint16_t)length, (uint16_t)offset);
        if (read < 0)
            return total != 0 ? total : (uint32_t)read;
        if (filter != 0 && !filter(fragment, (uint32_t)read, user_data))
            return total;
        net_buf_add(fragment + 0x0c, (uint32_t)read);
        total += (uint32_t)read;
        offset = (offset + (uint32_t)read) & 0xffffu;
        if ((uint32_t)net_buf_frags_len(buffer) >= mtu ||
            (uint32_t)read != length)
            return total;
    }
}
