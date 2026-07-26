#include "g1_app_symbols.h"
#include "../../headers/g1_log.h"
/* readable reconstruction; identity: FUN_0004a3d0 @ 0x0004a3d0
 * public-name: log_notification_fields_debug
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   log_notification_fields_debug            <= FUN_0004a3d0 @ 0x0004a3d0
 * address symbols (name @ address):
 *   rodata_f0229                             @ 0x000f0229   [INLINED -- G6 literal batch]
 *   rodata_f024d                             @ 0x000f024d   [INLINED -- G6 literal batch]
 *   rodata_f028c                             @ 0x000f028c   [INLINED -- G6 literal batch]
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed FUN_0004a3d0 @ 0x4a3d0  (parity: 300/300 trials, PROVEN)
 * CFG_VERIFY_CALL_ARITIES=2,2,4 */


void log_notification_fields_debug(int param_1, int param_2, int param_3, int param_4)
{
    volatile int *piVar1 = (volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
    if (*piVar1 == 0) {
        log_message(((unsigned long)"app_identifier:(%s)\n") /*=0xf0229*/, param_2 + 0x10);
    } else {
        debug_print(((unsigned long)"app_identifier:(%s)\n") /*=0xf0229*/, param_2 + 0x10, param_3, param_4);
    }
    if (*piVar1 == 0) {
        log_message(((unsigned long)"message:(%s)\n") /*=0xf024d*/, param_2 + 0x90);
    } else {
        debug_print(((unsigned long)"message:(%s)\n") /*=0xf024d*/, param_2 + 0x90, param_3, param_4);
    }
    if (*piVar1 != 0) {
        debug_print(((unsigned long)"uid :(%d)\n") /*=0xf028c*/, *(volatile int*)(param_2+8), param_3, param_4);
        return;
    }
    log_message(((unsigned long)"uid :(%d)\n") /*=0xf028c*/, *(volatile int*)(param_2+8), param_3, param_4);
}
