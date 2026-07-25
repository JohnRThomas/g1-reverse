#include "g1_app_symbols.h"
/* readable reconstruction; identity: panel_resume @ 0x00046f20
 * public-name: panel_resume
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   log_message                              <= FUN_0007dda4 @ 0x0007dda4
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   jbd_panel_resume                         <= FUN_00047638 @ 0x00047638
 *   spi_read_id                              <= FUN_00047724 @ 0x00047724
 *   panel_on                                 <= FUN_00046dd8 @ 0x00046dd8
 *   set_brightness_to_panel_reg              <= FUN_00046e3c @ 0x00046e3c
 * address symbols (name @ address):
 *   rodata_d7272                             @ 0x000d7272
 *   rodata_d728d                             @ 0x000d728d
 *   rodata_d72c4                             @ 0x000d72c4
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed panel_resume @ 0x46f20 (uncatalogued: Ghidra folded it into the
 * tail of set_brightness_to_panel_reg; code 0x46f20..0x46fa8, literal pool
 * 0x46fac..0x46fc0).  (parity: cfg_verify PASS, 200/200 trials)
 * Vtable slot +0x08 (device_ctx + 0xb74) written by quicknote_buffer_pool_init.
 * Name self-evidenced: the log tag 0x000d72c4 is "panel_resume"; the failure
 * string 0x000d728d is "%s(): JBD PANEL init failure!\n".
 * This is the E4 display bring-up path: it calls spi_read_id (0x47724) and
 * requires the JBD panel ID 0x4010.
 */
#include <stdint.h>

extern void log_message(uint32_t format, ...);
extern void debug_print(uint32_t format, ...);
extern void jbd_panel_resume(uint8_t *context);
extern uint32_t spi_read_id(void);
extern void panel_on(uint8_t *context);
extern void set_brightness_to_panel_reg(uint32_t level);

int32_t panel_resume(uint8_t *context)
{
    int32_t state;

    *(void * volatile *)(context + 0x374) = (void *)(context - 0x5c);
    if ((*(volatile uint16_t *)(context + 0x4f0) & 0x100u) == 0)
        return -1;
    if (*(volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/ > 2) {
        if (*(volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
            log_message(((unsigned long)&rodata_d7272) /*=0xd7272*/, ((unsigned long)&rodata_d72c4) /*=0xd72c4*/);
        } else {
            debug_print(((unsigned long)&rodata_d7272) /*=0xd7272*/, ((unsigned long)&rodata_d72c4) /*=0xd72c4*/);
        }
    }
    state = *(volatile int32_t *)(context + 0x35c);
    if (state != 0)
        return -1;
    if (*(volatile uint32_t *)(*(void * volatile *)(context + 0x374) + 0x14) == 0) {
        panel_on(context);
        set_brightness_to_panel_reg(*(volatile uint8_t *)(context + 0x369));
        return state;
    }
    jbd_panel_resume(context);
    if (spi_read_id() != 0x4010u) {
        if (*(volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/ > 0) {
            if (*(volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                log_message(((unsigned long)&rodata_d728d) /*=0xd728d*/, ((unsigned long)&rodata_d72c4) /*=0xd72c4*/);
            } else {
                debug_print(((unsigned long)&rodata_d728d) /*=0xd728d*/, ((unsigned long)&rodata_d72c4) /*=0xd72c4*/);
            }
        }
    }
    *(volatile int32_t *)(context + 0x35c) = 1;
    return state;
}
