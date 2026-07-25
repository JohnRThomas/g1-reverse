#include "g1_app_symbols.h"
/* readable reconstruction; identity: panel_suspend @ 0x00046d8c
 * public-name: panel_suspend
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   log_message                              <= FUN_0007dda4 @ 0x0007dda4
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   jbd_panel_suspend                        <= FUN_000475f0 @ 0x000475f0
 *   panel_off                                <= FUN_00046d2c @ 0x00046d2c
 * address symbols (name @ address):
 *   rodata_d721e                             @ 0x000d721e
 *   rodata_d72db                             @ 0x000d72db
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed panel_suspend @ 0x46d8c (uncatalogued: Ghidra folded it into
 * the tail of panel_off; code 0x46d8c..0x46dc6, literal pool 0x46dc8..0x46dd8).
 * (parity: cfg_verify PASS, 200/200 trials)
 * Vtable slot +0x04 (device_ctx + 0xb70) written by quicknote_buffer_pool_init
 * (0x47148) -- the pointer global_system_suspend (0x2bd7c) dispatches through.
 * Name self-evidenced: the log tag 0x000d72db is "panel_suspend".
 */
#include <stdint.h>

extern void log_message(uint32_t format, ...);
extern void debug_print(uint32_t format, ...);
extern void jbd_panel_suspend(void);
extern uint32_t panel_off(uint8_t *context);

uint32_t panel_suspend(uint8_t *context)
{
    *(void * volatile *)(context + 0x374) = (void *)(context - 0x5c);
    if (*(volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/ > 2) {
        if (*(volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
            log_message(((unsigned long)&rodata_d721e) /*=0xd721e*/, ((unsigned long)&rodata_d72db) /*=0xd72db*/);
        } else {
            debug_print(((unsigned long)&rodata_d721e) /*=0xd721e*/, ((unsigned long)&rodata_d72db) /*=0xd72db*/);
        }
    }
    jbd_panel_suspend();
    panel_off(context);
    *(volatile uint32_t *)(context + 0x35c) = 0;
    return 0;
}
