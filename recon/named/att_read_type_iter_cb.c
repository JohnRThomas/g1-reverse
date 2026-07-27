/* readable reconstruction; identity: FUN_00058808 @ 0x00058808
 * public-name: att_read_type_iter_cb
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   att_read_type_iter_cb                    <= FUN_00058808 @ 0x00058808
 *   net_buf_frag_last                        <= FUN_0005f304 @ 0x0005f304
 *   net_buf_simple_add                       <= FUN_0005f5d0 @ 0x0005f5d0
 *   bt_uuid_cmp                              <= FUN_00080d3e @ 0x00080d3e
 *   net_buf_frags_len_0                      <= FUN_00081bc0 @ 0x00081bc0
 *   att_chan_read                            <= FUN_00081e2a @ 0x00081e2a
 *   bt_gatt_check_perm                       <= FUN_00082cba @ 0x00082cba
 * address symbols (name @ address):
 *   ADDR_attr_read_type_cb_THUMB             @ 0x00081bd1
 */
/* Full reconstruction FUN_00058808 @ 0x58808, exact extent 166 bytes. */
#include <stdint.h>
#include <stdbool.h>

extern int bt_uuid_cmp(uint32_t, uint32_t, void *, uint32_t);
extern int bt_gatt_check_perm(unsigned long, void*, unsigned long);
extern uint32_t net_buf_frag_last(uint32_t);
extern void *net_buf_simple_add(uint32_t, uint32_t);
extern int32_t att_chan_read(void *, void *, uint32_t, uint32_t, uintptr_t, void *);
extern uint32_t net_buf_frags_len_0(uint32_t);

struct request_58808 {
    void *owner;
    uint32_t value;
    uint32_t buffer;
    uint8_t *limit;
    uint16_t *payload;
    uint8_t status;
};

bool att_read_type_iter_cb(uint32_t *context, uint32_t value,
                  struct request_58808 *request, uint32_t arg3)
{
    uint8_t *owner = request->owner;
    uint32_t connection = *(uint32_t *)(owner + 8);
    int status = bt_uuid_cmp(*context, request->value, request, arg3);

    if (status != 0)
        return true;

    status = bt_gatt_check_perm(connection, context, 0x95);
    request->status = (uint8_t)status;
    if (status != 0) {
        if (*request->limit != 0)
            request->status = 0;
        return false;
    }

    request->payload = net_buf_simple_add(net_buf_frag_last(request->buffer) + 12, 2);
    *request->payload = (uint16_t)value;
    status = att_chan_read(owner, context, request->buffer, 0,
                          0x00081bd1u, request);
    if (status < 0) {
        request->status = status < -255 ? 14 : (uint8_t)-status;
        return false;
    }
    if (request->payload != 0) {
        uint32_t used = net_buf_frags_len_0(request->buffer);
        uint32_t available = *(uint16_t *)(owner + 0x2e);
        uint32_t alternate = *(uint16_t *)(owner + 0x1e);
        if (alternate <= available)
            available = alternate;
        return *request->limit < available - used;
    }
    return false;
}
