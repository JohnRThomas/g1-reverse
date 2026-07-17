/* CPUAPP Zephyr Bluetooth chan_req_send @ 0x00082030.
 * Raw/address back-map: FUN_00082030 / 0x00082030.
 */
#include <stdint.h>
extern uint64_t net_buf_frags_len(void *); /* FUN_00081bc0 */
extern int bt_att_chan_send(void *, void *); /* FUN_00058a54 */
#define chan_req_send FUN_00082030

int chan_req_send(uint8_t *chan, uint8_t *request)
{
    void *buffer = *(void **)(request + 8);
    uint32_t length = (uint32_t)net_buf_frags_len(buffer);
    uint32_t mtu = *(uint16_t *)(chan + 0x1e);
    uint32_t enhanced_mtu = *(uint16_t *)(chan + 0x2e);
    if (enhanced_mtu < mtu)
        mtu = enhanced_mtu;
    if (mtu < length)
        return -122;
    *(void **)(chan + 0x124) = request;
    *(void **)(request + 8) = 0;
    int status = bt_att_chan_send(chan, buffer);
    if (status != 0) {
        *(void **)(request + 8) = buffer;
        *(void **)(chan + 0x124) = 0;
    }
    return status;
}
