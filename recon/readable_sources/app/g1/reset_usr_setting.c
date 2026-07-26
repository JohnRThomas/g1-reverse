#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_g1_device_runtime_state__param_0027    [param_0027; G1-original]
 * Raw function identity: 0x00022ddc.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00022ddc @ 0x00022ddc
 * public-name: reset_usr_setting
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   set_test_mode                            <= FUN_00032ef0 @ 0x00032ef0
 *   save_usr_setting                         <= FUN_0007c28e @ 0x0007c28e
 * address symbols (name @ address):
 *   rodata_9e5f3                             @ 0x0009e5f3   [INLINED -- G6 literal batch]
 *   rodata_9e7b7                             @ 0x0009e7b7   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed reset_usr_setting @ 0x22ddc */

#include <stdint.h>
#include "../../../headers/g1_log.h"

extern void set_test_mode(uint32_t mode);
extern void save_usr_setting(void *settings, uint32_t value);

uint32_t reset_usr_setting(uint8_t *settings)
{
    if (*(volatile int32_t *)((unsigned long)&g_log_level) /*=0x2000230c*/ > 2) {
        if (*(volatile uint32_t *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
            log_message(((unsigned long)"%s(): reset_usr_setting\n") /*=0x9e5f3*/, ((unsigned long)"reset_usr_setting") /*=0x9e7b7*/);
        } else {
            debug_print(((unsigned long)"%s(): reset_usr_setting\n") /*=0x9e5f3*/, ((unsigned long)"reset_usr_setting") /*=0x9e7b7*/);
        }
    }

    *(volatile uint8_t *)(settings + 0xfea) = 10;
    *(volatile uint8_t *)(settings + 0xed5) = 0x15;
    *(volatile uint32_t *)(settings + 0xf6c) = 400;
    *(volatile uint8_t *)(settings + 0xf60) = 1;
    *(volatile uint8_t *)(settings + 0xf98) = 1;
    *(volatile uint8_t *)(settings + 0x108d) = 1;
    *(volatile uint8_t *)(settings + 0x1070) = 0;
    *(volatile uint8_t *)(settings + 0xec0) = 3;
    *(volatile uint32_t *)(settings + 0x1069) = UINT32_MAX;
    *(volatile uint32_t *)(settings + 0x106c) = UINT32_MAX;
    *(volatile uint16_t *)(settings + 0xef4) = 0x114;
    *(volatile uint8_t *)(settings + 0x108f) = 0;
    *(volatile uint16_t *)(settings + 0x1090) = 0;

    set_test_mode(0);
    *(volatile uint8_t *)(settings + 0xec1) = 3;
    *(volatile uint32_t *)(settings + 0xf68) = 0;
    save_usr_setting(settings, 0);
    return 0;
}
