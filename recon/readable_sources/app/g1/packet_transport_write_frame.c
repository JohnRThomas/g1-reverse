#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00024e60 @ 0x00024e60
 * public-name: packet_transport_write_frame
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   st25dv_read_area_size                    <= FUN_00024d50 @ 0x00024d50
 *   st25dv_mailbox_poll_message              <= FUN_00024dac @ 0x00024dac
 *   packet_transport_write_frame             <= FUN_00024e60 @ 0x00024e60
 *   ipc_ept_op_a_locked_retry                <= FUN_000256dc @ 0x000256dc
 * address symbols (name @ address):
 *   g_st25dv_mailbox_msg                     @ 0x20007a14
 *   g_st25dv_dev                             @ 0x20007a44
 */
/* Reconstructed FUN_00024e60 @ 0x00024e60, extent 0xa0.
 * Readable identity: packet_transport_write_frame.
 * Raw/address backmap: packet_transport_write_frame <= FUN_00024e60 @ 0x00024e60.
 * CFG_VERIFY_CALL_ARITIES=1,1,4,4,4
 */
#include <stdint.h>

extern uint32_t st25dv_read_area_size(uint32_t type);
extern int st25dv_mailbox_poll_message(uint32_t cursor);
extern int ipc_ept_op_a_locked_retry(void *transport, uint32_t offset,
                        const void *data, uint32_t length);

int packet_transport_write_frame(uint32_t type, uint32_t length, const void *payload)
{
    volatile uint32_t *const state = (volatile uint32_t *)((unsigned long)&g_st25dv_mailbox_msg) /*=0x20007a14*/;
    void *transport = *(void * volatile *)((unsigned long)&g_st25dv_dev) /*=0x20007a44*/;
    uint8_t header[4];
    uint8_t delimiter = 0xfe;
    uint32_t cursor = st25dv_read_area_size(type);
    uint32_t header_length = length > 0xfeU ? 4U : 2U;

    if (length > cursor - state[3] - 1U - header_length)
        return -2;
    if (st25dv_mailbox_poll_message(cursor) != 0)
        return -1;

    header[0] = (uint8_t)type;
    if (length > 0xfeU) {
        header[1] = 0xffU;
        header[2] = (uint8_t)(length >> 8);
        header[3] = (uint8_t)length;
    } else {
        header[1] = (uint8_t)length;
    }

    cursor = state[3];
    if (ipc_ept_op_a_locked_retry(transport, cursor, header, header_length) != 0)
        return -1;
    cursor += header_length;
    if (ipc_ept_op_a_locked_retry(transport, cursor, payload, length) != 0)
        return -1;
    return ipc_ept_op_a_locked_retry(transport, cursor + length, &delimiter, 1U) != 0 ? -1 : 0;
}
