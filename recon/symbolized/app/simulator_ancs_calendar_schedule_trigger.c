#include "g1_app_symbols.h"
#include "../../headers/g1_log.h"
/* readable reconstruction; identity: FUN_00021cd8 @ 0x00021cd8
 * public-name: simulator_ancs_calendar_schedule_trigger
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ancs_get_conn_ctx                        <= FUN_000181fc @ 0x000181fc
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   log_notification_fields_debug            <= FUN_0004a3d0 @ 0x0004a3d0
 *   log_message                              <= FUN_0007dda4 @ 0x0007dda4
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 *   strncpy_zero_pad                         <= FUN_0008705a @ 0x0008705a
 * address symbols (name @ address):
 *   rodata_99969                             @ 0x00099969
 *   rodata_9d7b8                             @ 0x0009d7b8
 *   rodata_9d7cc                             @ 0x0009d7cc
 *   rodata_9d7d4                             @ 0x0009d7d4
 *   rodata_9d7e1                             @ 0x0009d7e1
 *   rodata_9d7e8                             @ 0x0009d7e8
 *   rodata_9dfbf                             @ 0x0009dfbf
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed simulator_ancs_calendar_schedule_trigger @ 0x21cd8  (parity: 300/300 trials, PROVEN) */

extern int ancs_get_conn_ctx(void);
extern void memset_bytes(void*, int, int);
extern void strncpy_zero_pad(unsigned int, unsigned int, int);
extern void log_notification_fields_debug(unsigned int, unsigned int);
extern unsigned long process_sync_buffer(unsigned int, ...);

void simulator_ancs_calendar_schedule_trigger(void)
{
    unsigned int iVar1;

    iVar1 = ancs_get_conn_ctx();
    if (2 < *(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/) {
        if (*(volatile unsigned int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
            log_message(((unsigned long)&rodata_99969) /*=0x99969*/, ((unsigned long)&rodata_9dfbf) /*=0x9dfbf*/);
        } else {
            debug_print(((unsigned long)&rodata_99969) /*=0x99969*/, ((unsigned long)&rodata_9dfbf) /*=0x9dfbf*/);
        }
    }
    memset_bytes(iVar1 + 0x34, 0, 0x1b4);
    strncpy_zero_pad(iVar1 + 0x44, ((unsigned long)&rodata_9d7b8) /*=0x9d7b8*/, 0x20);
    strncpy_zero_pad(iVar1 + 0x84, ((unsigned long)&rodata_9d7cc) /*=0x9d7cc*/, 0x20);
    strncpy_zero_pad(iVar1 + 0xc4, ((unsigned long)&rodata_9d7d4) /*=0x9d7d4*/, 0x100);
    strncpy_zero_pad(iVar1 + 0x64, ((unsigned long)&rodata_9d7e1) /*=0x9d7e1*/, 0x20);
    log_notification_fields_debug(((unsigned long)&rodata_9d7e8) /*=0x9d7e8*/, iVar1 + 0x34);
    process_sync_buffer(iVar1 + 0x1e8);
}
