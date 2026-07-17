#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007cce8 @ 0x0007cce8
 * public-name: update_display_status
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   display_panel_is_secondary               <= FUN_0002bed0 @ 0x0002bed0
 *   mark_master_or_low_battery_flag          <= FUN_0002efc0 @ 0x0002efc0
 *   reset_esb_sync_state                     <= FUN_0007ce60 @ 0x0007ce60
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 */
/* Reconstructed update_display_status @ 0x7cce8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int display_panel_is_secondary(void);
extern void mark_master_or_low_battery_flag(void);
extern void reset_esb_sync_state(int);
extern void memset_bytes(void*, int, int);
extern void send_event_status(int);

void update_display_status(int param_1, int param_2)
{
    int iVar1;
    char *pcVar2;
    char cVar3 = 0;

    iVar1 = display_panel_is_secondary();
    if (iVar1 == 0) {
        return;
    }
    if ((*(char*)(intptr_t)(*(int*)(intptr_t)(param_1 + 0x1004) + 6) != 0) ||
        ((cVar3 = *(char*)(intptr_t)(*(int*)(intptr_t)(param_1 + 0x1008) + 6)), cVar3 != 0)) {
        mark_master_or_low_battery_flag();
        memset_bytes((void*)(intptr_t)(*(int*)(intptr_t)(param_1 + 0x1008) + 6), 0, 400);
        memset_bytes((void*)(intptr_t)(*(int*)(intptr_t)(param_1 + 0x1004) + 6), 0, 400);
        cVar3 = 1;
    }
    if (**(char**)(intptr_t)(param_1 + 0x1000) != 0) {
        **(char**)(intptr_t)(param_1 + 0x1000) = 0;
        cVar3 = 1;
    }
    if (*(char*)(intptr_t)(*(int*)(intptr_t)(param_1 + 0xffc) + 1) != 0) {
        mark_master_or_low_battery_flag();
        *(unsigned char*)(intptr_t)(*(int*)(intptr_t)(param_1 + 0xffc) + 1) = 0;
        cVar3 = 1;
    }
    if (**(char**)(intptr_t)(param_1 + 0x1020) != 0) {
        mark_master_or_low_battery_flag();
        **(unsigned char**)(intptr_t)(param_1 + 0x1020) = 0;
        cVar3 = 1;
    }
    if (**(char**)(intptr_t)(param_1 + 0x1010) != 0) {
        **(char**)(intptr_t)(param_1 + 0x1010) = 0;
        cVar3 = 1;
    }
    if (**(char**)(intptr_t)(param_1 + 0x1014) != 0) {
        **(char**)(intptr_t)(param_1 + 0x1014) = 0;
        cVar3 = 1;
    }
    if (*(char*)(intptr_t)(*(int*)(intptr_t)(param_1 + 0x100c) + 7) == 0) {
        pcVar2 = *(char**)(intptr_t)(param_1 + 0x101c);
        if (*pcVar2 == 0) {
            if (cVar3 == 0) {
                return;
            }
            goto LAB_0007cd8a;
        }
    } else {
        mark_master_or_low_battery_flag();
        reset_esb_sync_state(1);
        pcVar2 = *(char**)(intptr_t)(param_1 + 0x101c);
        if (*pcVar2 == 0) goto LAB_0007cd8a;
    }
    *pcVar2 = 0;
LAB_0007cd8a:
    if (param_2 != 0) {
        send_event_status(0);
    }
    memset_bytes((void*)(intptr_t)(param_1 + 0xef), 0, 0x5dc);
    return;
}
