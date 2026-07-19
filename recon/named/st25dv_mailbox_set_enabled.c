/* readable reconstruction; identity: FUN_00024cc8 @ 0x00024cc8
 * public-name: st25dv_mailbox_set_enabled
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   st25dv_mailbox_set_enabled               <= FUN_00024cc8 @ 0x00024cc8
 *   st25dv_mailbox_send_id_pair              <= FUN_0007c99e @ 0x0007c99e
 *   read_bool_attr_0x2004                    <= FUN_0007ca24 @ 0x0007ca24
 * address symbols (name @ address):
 *   g_st25dv_dev                             @ 0x20007a44
 */
/* Reconstructed FUN_00024cc8 @ 0x24cc8 */
#include <stdint.h>

extern void read_bool_attr_0x2004(uint32_t, void *);
extern void st25dv_mailbox_send_id_pair(uint32_t, void *);

struct controller_mode_frame {
    uint8_t reserved[11];
    uint8_t mode;
    uint32_t interval[2];
};

uint8_t st25dv_mailbox_set_enabled(uint32_t enable)
{
    struct controller_mode_frame frame;
    volatile uint32_t *controller = (volatile uint32_t *)0x20007a44u;

    frame.mode = 0;
    read_bool_attr_0x2004(*controller, &frame.mode);
    if (frame.mode == 0) {
        if (enable != 0) {
            frame.interval[0] = 0;
            frame.interval[1] = 0;
            st25dv_mailbox_send_id_pair(*controller, frame.interval);
        }
    } else if (frame.mode == 1 && enable == 0) {
        frame.interval[0] = 0x12345678u;
        frame.interval[1] = 0x13245678u;
        st25dv_mailbox_send_id_pair(*controller, frame.interval);
    }
    read_bool_attr_0x2004(*controller, &frame.mode);
    return frame.mode;
}
