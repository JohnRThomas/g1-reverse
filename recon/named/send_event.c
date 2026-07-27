/* readable reconstruction; identity: FUN_000276ec @ 0x000276ec
 * public-name: send_event
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   enqueue_bt_data                          <= FUN_00017eec @ 0x00017eec
 *   ancs_get_conn_ctx                        <= FUN_000181fc @ 0x000181fc
 *   process_sync_buffer                      <= FUN_0007cb4c @ 0x0007cb4c
 *   k_msleep                                 <= FUN_0007cb8e @ 0x0007cb8e
 * address symbols (name @ address):
 *   g_send_event_pending_id                  @ 0x2000302e
 */
/* Reconstructed send_event @ 0x276ec. */

#include <stdint.h>

extern int enqueue_bt_data(unsigned long, unsigned char);
extern int ancs_get_conn_ctx(void);
extern unsigned long process_sync_buffer(unsigned int, ...);
extern void k_msleep(int enabled);

void send_event(int event_id, unsigned int unused_2, unsigned int unused_3)
{
    uint8_t *pending_event = (uint8_t *)0x2000302eUL;
    uint8_t event[3];
    uint8_t *state = ancs_get_conn_ctx();

    (void)unused_2;
    (void)unused_3;

    if ((unsigned int)(event_id - 0xf0) <= 2 && *pending_event != 0xff) {
        return;
    }

    *pending_event = (uint8_t)event_id;
    if (state[0x248] != 0 || *(uint32_t *)(state + 0x220) != 0) {
        event[0] = 0xf5;
        event[1] = (uint8_t)event_id;
        event[2] = 0xcb;
        enqueue_bt_data(event, sizeof(event));
        *pending_event = 0xff;
        return;
    }

    if (state[0x248] == 0) {
        process_sync_buffer(state + 0x218);
        k_msleep(1);
    }
}
