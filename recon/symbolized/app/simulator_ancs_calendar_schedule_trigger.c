#include "g1_app_symbols.h"
/* named: simulator_ancs_calendar_schedule_trigger */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed simulator_ancs_calendar_schedule_trigger @ 0x21cd8  (parity: 300/300 trials, PROVEN) */

extern unsigned int ancs_get_conn_ctx(void);
extern void DEBUG_PRINT(unsigned int, unsigned int, ...);
extern void debug_print(void);
extern void memset_bytes(unsigned int, int, int);
extern void strncpy_zero_pad(unsigned int, unsigned int, int);
extern void log_notification_fields_debug(unsigned int, unsigned int);
extern void thunk_FUN_00072880(unsigned int);

void simulator_ancs_calendar_schedule_trigger(void)
{
    unsigned int iVar1;

    iVar1 = ancs_get_conn_ctx();
    if (2 < *(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/) {
        if (*(volatile unsigned int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
            DEBUG_PRINT("%s(): enter\n" /*=0x99969*/, "simulator_ancs_calendar_schedule_trigger" /*=0x9dfbf*/);
        } else {
            debug_print();
        }
    }
    memset_bytes(iVar1 + 0x34, 0, 0x1b4);
    strncpy_zero_pad(iVar1 + 0x44, "com.apple.mobilecal" /*=0x9d7b8*/, 0x20);
    strncpy_zero_pad(iVar1 + 0x84, ((uintptr_t)&tbl_9d64e) /*=0x9d7cc*/, 0x20);
    strncpy_zero_pad(iVar1 + 0xc4, ((uintptr_t)&tbl_9d64e) /*=0x9d7d4*/, 0x100);
    strncpy_zero_pad(iVar1 + 0x64, ((uintptr_t)&tbl_9d64e) /*=0x9d7e1*/, 0x20);
    log_notification_fields_debug("calendar-sched" /*=0x9d7e8*/, iVar1 + 0x34);
    thunk_FUN_00072880(iVar1 + 0x1e8);
}

