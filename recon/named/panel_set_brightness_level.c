#include "g1_app_symbols.h"
/* readable reconstruction; identity: panel_set_brightness_level @ 0x00046ce8
 * public-name: panel_set_brightness_level
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   log_message                              <= FUN_0007dda4 @ 0x0007dda4
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 * address symbols (name @ address):
 *   rodata_d720f                             @ 0x000d720f   [INLINED -- G6 literal batch]
 *   rodata_d732c                             @ 0x000d732c   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed panel_set_brightness_level @ 0x46ce8 (uncatalogued: Ghidra
 * folded it into the tail of ui_set_imu_pitch_task; code 0x46ce8..0x46d1a,
 * literal pool 0x46d1c..0x46d2c).  (parity: cfg_verify PASS, 200/200 trials)
 * Vtable slot +0x20 (device_ctx + 0xb8c) written by quicknote_buffer_pool_init.
 * Name self-evidenced: the log tag 0x000d732c is "panel_set_brightness_level".
 */
#include <stdint.h>
#include "../headers/g1_log.h"


uint32_t panel_set_brightness_level(uint8_t *context, uint32_t level)
{
    if (*(volatile uint8_t *)(context + 0x369) != level) {
        *(volatile uint8_t *)(context + 0x369) = (uint8_t)level;
        if (*(volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/ > 2) {
            if (*(volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                log_message(((unsigned long)"%s(): new: %d\n") /*=0xd720f*/, ((unsigned long)"panel_set_brightness_level") /*=0xd732c*/, level);
            } else {
                debug_print(((unsigned long)"%s(): new: %d\n") /*=0xd720f*/, ((unsigned long)"panel_set_brightness_level") /*=0xd732c*/, level);
            }
        }
    }
    return level;
}
