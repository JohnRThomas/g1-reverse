#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000327c4 @ 0x000327c4
 * public-name: get_glassbox_charge_percent
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 * address symbols (name @ address):
 *   rodata_a742d                             @ 0x000a742d
 *   rodata_a7735                             @ 0x000a7735
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_glassbox_charge_status_byte            @ 0x20019ef4
 */
/* Reconstructed get_glassbox_charge_percent @ 0x327c4. */
#include <stdint.h>

extern void DEBUG_PRINT(uint32_t, uint32_t, ...);
extern void debug_print(uint32_t, uint32_t, ...);

uint8_t get_glassbox_charge_percent(void)
{
    uint8_t percent = *(volatile uint8_t *)((unsigned long)&g_glassbox_charge_status_byte) /*=0x20019ef4*/ & 0x7f;

    if (2 < *(volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/) {
        if (*(volatile uint32_t *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0)
            DEBUG_PRINT(((unsigned long)&rodata_a742d) /*=0xa742d*/, ((unsigned long)&rodata_a7735) /*=0xa7735*/, percent);
        else
            debug_print(((unsigned long)&rodata_a742d) /*=0xa742d*/, ((unsigned long)&rodata_a7735) /*=0xa7735*/, percent);
    }
    /* The firmware deliberately reloads after the diagnostic call.  The
       status byte is volatile and may be updated while the logger runs. */
    return *(volatile uint8_t *)((unsigned long)&g_glassbox_charge_status_byte) /*=0x20019ef4*/ & 0x7f;
}
