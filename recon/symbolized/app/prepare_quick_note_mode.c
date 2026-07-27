#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007cdb6 @ 0x0007cdb6
 * public-name: prepare_quick_note_mode
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   display_panel_is_secondary               <= FUN_0002bed0 @ 0x0002bed0
 *   update_persist_task_status_to_idle       <= FUN_0002c0e8 @ 0x0002c0e8
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 */
/* Reconstructed prepare_quick_note_mode @ 0x7cdb6  (parity: 300/300 trials, PROVEN) */

extern int display_panel_is_secondary(unsigned long);
extern void update_persist_task_status_to_idle(void);
extern void memset_bytes(void);
extern void send_event(void);

void prepare_quick_note_mode(unsigned char *param_1, int param_2, unsigned int param_3, unsigned int param_4)
{
    int iVar1 = display_panel_is_secondary(param_1);
    if ((iVar1 != 0) && ((param_1[0xd5]==6) || (param_1[0xd5]==4))) {
        if (param_2 != 0) {
            send_event();
        }
        update_persist_task_status_to_idle();
        memset_bytes();
        return;
    }
    return;
}
