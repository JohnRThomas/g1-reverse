/* readable reconstruction; identity: FUN_00024f78 @ 0x00024f78
 * public-name: st25dv_mailbox_send_message
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   st25dv_write_reg_pair                    <= FUN_00024f08 @ 0x00024f08
 *   st25dv_mailbox_send_message              <= FUN_00024f78 @ 0x00024f78
 *   ipc_ept_op_a_locked_retry                <= FUN_000256dc @ 0x000256dc
 * address symbols (name @ address):
 *   g_st25dv_mailbox_msg                     @ 0x20007a14
 *   g_st25dv_dev                             @ 0x20007a44
 */
/* Reconstructed FUN_00024f78 @ 0x24f78 */
#include <stdint.h>

extern int st25dv_write_reg_pair(int, unsigned int, unsigned int, unsigned int);
extern int ipc_ept_op_a_locked_retry(int, unsigned int, unsigned int, int);

struct transport_probe_frame {
    uint8_t reserved[7];
    uint8_t command;
    uint32_t header;
    uint16_t reserved_halfword;
    uint16_t swapped_length;
};

int st25dv_mailbox_send_message(uint32_t inherited_r0, uint32_t inherited_r1,
                 uint32_t inherited_r2, uint32_t inherited_r3)
{
    volatile uint8_t *state = (volatile uint8_t *)0x20007a14u;
    volatile uint32_t *state_words = (volatile uint32_t *)state;
    volatile uint32_t *controller = (volatile uint32_t *)0x20007a44u;
    struct transport_probe_frame frame;

    frame.header = state_words[0];
    state_words[3] = 4;
    if (state[2] == 0) {
        uint16_t length = *(volatile uint16_t *)(state + 6);
        frame.swapped_length = (uint16_t)((length << 8) | (length >> 8));
        state_words[3] = 8;
    }

    int status = (int16_t)st25dv_write_reg_pair(&frame.header, inherited_r1, 4,
                                       state[2]);
    if (status != 0)
        return status;

    frame.command = 3;
    status = ipc_ept_op_a_locked_retry(*controller, state_words[3], &frame.command, 1);
    if (status != 0)
        return -1;

    frame.command = 0;
    status = ipc_ept_op_a_locked_retry(*controller, state_words[3] + 1,
                          &frame.command, 1);
    (void)inherited_r0;
    (void)inherited_r2;
    (void)inherited_r3;
    return status == 0 ? 0 : -1;
}
