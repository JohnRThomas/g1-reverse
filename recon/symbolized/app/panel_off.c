#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00046d2c @ 0x00046d2c
 * public-name: panel_off
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   power_down_panel                         <= FUN_00015fdc @ 0x00015fdc
 *   get_ambient_light_sensor_ready_flag      <= FUN_0001655c @ 0x0001655c
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   opt3007_chip_deinit                      <= FUN_0002e8b4 @ 0x0002e8b4
 * address symbols (name @ address):
 *   rodata_d721e                             @ 0x000d721e   [INLINED -- G6 literal batch]
 *   rodata_d72d1                             @ 0x000d72d1   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed panel_off @ 0x46d2c. */
#include <stdint.h>
#include "../../headers/g1_log.h"

typedef void (*panel_callback_t)(void *panel);
extern int get_ambient_light_sensor_ready_flag(void);
extern void opt3007_chip_deinit(void);
extern unsigned int power_down_panel(void);

uint32_t panel_off(uint8_t *context)
{
    void *panel = context - 0x5c;

    *(void **)(context + 0x374) = panel;
    if (*(uint32_t *)(context - 0x48) != 0) {
        *(uint32_t *)(context + 0x35c) = 0;
        if (*(volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/ > 2) {
            if (*(volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                log_message(((unsigned long)"%s(): panel_suspend enter!\n") /*=0xd721e*/, ((unsigned long)"panel_off") /*=0xd72d1*/);
            } else {
                debug_print(((unsigned long)"%s(): panel_suspend enter!\n") /*=0xd721e*/, ((unsigned long)"panel_off") /*=0xd72d1*/);
            }
        }
        if (get_ambient_light_sensor_ready_flag() == 0)
            opt3007_chip_deinit();
        ((panel_callback_t)*(uintptr_t *)(context - 0x58))(panel);
        power_down_panel();
    }
    return 0;
}
