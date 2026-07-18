/* readable reconstruction; identity: FUN_0101b4f4 @ 0x0101b4f4
 * public-name: sdc_event_publish
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_event_publish                        <= FUN_0101b4f4 @ 0x0101b4f4
 * address symbols (name @ address):
 *   g_net_session_state_block                @ 0x210010a0
 */
/* net-core sdc_event_publish @ 0x0101b4f4
 * Catalog-missing 88-byte SoftDevice Controller event-publication bridge.
 * Raw backmap: FUN_0101b4f4@0x0101b4f4; executable end: 0x0101b54c.
 */
#include <stdint.h>

/* Keep the emitted parity symbol reversible while presenting its real role. */
#define sdc_event_publish sdc_event_publish

extern int controller_timing_snapshot_build(void *frame, uint32_t,
                                            uint32_t, uint32_t);
/* controller_timing_snapshot_build -> FUN_0101a38c@0x0101a38c */
extern uint8_t *controller_radio_state_get(void);
/* controller_radio_state_get -> FUN_01019204@0x01019204 */
extern int sdc_conn_window_admit(uint32_t radio_state, const void *frame);
/* sdc_conn_window_admit -> FUN_010231c8@0x010231c8 */
extern void controller_radio_event_cleanup(void);
/* controller_radio_event_cleanup -> FUN_01020634@0x01020634 */
extern void FUN_01022a84(void); /* raw owner @ 0x01022a84 */
extern void sdc_assertion_fail(uint32_t module, uint32_t line)
    __attribute__((noreturn));
/* sdc_assertion_fail -> FUN_01008d00@0x01008d00 */

void sdc_event_publish(uint32_t call_context, uint32_t event_count,
                       uint32_t pending_flag, uint32_t user_data)
{
    volatile uint8_t *const state = (volatile uint8_t *)UINT32_C(0x210010a0);
    uint8_t timing_frame[24];

    /* The callback ABI supplies these values; this bridge reads shared state. */
    (void)call_context;
    (void)event_count;
    (void)pending_flag;
    (void)user_data;

    if (state[20] == 0u)
        return;

    if (state[1] == 0u) {
        if (controller_timing_snapshot_build(timing_frame, 0u, 0u, 0u) == 0) {
            state[2] = 1u;
        } else if (sdc_conn_window_admit(*controller_radio_state_get(),
                                         timing_frame) == 0) {
            sdc_assertion_fail(0x21u, 0x7cbu);
        }
    }

    controller_radio_event_cleanup();
    FUN_01022a84();
    state[20] = 0u;
    state[21] = 0u;
}
