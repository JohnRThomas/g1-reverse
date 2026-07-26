#include "g1_app_symbols.h"
/* readable reconstruction; identity: imu_fusion_suspend @ 0x00025df8
 * public-name: imu_fusion_suspend
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   log_message                              <= FUN_0007dda4 @ 0x0007dda4
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 * address symbols (name @ address):
 *   rodata_9f72f                             @ 0x0009f72f   [INLINED -- G6 literal batch]
 *   rodata_9faf1                             @ 0x0009faf1   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed imu_fusion_suspend @ 0x25df8 (uncatalogued Ghidra gap
 * 0x25d8c..0x25ecc; code 0x25df8..0x25e1c, literal pool 0x25e1c..0x25e2c).
 * (parity: cfg_verify PASS, 200/200 trials)
 * Vtable slot +0x90 written by register_imu_funsion_context (0x26250).
 * Name self-evidenced: the log tag 0x0009faf1 is "suspend".
 */
#include <stdint.h>
#include "../../headers/g1_log.h"


#define LOG_LEVEL (*(volatile int32_t *)((unsigned long)&g_log_level) /*=0x2000230c*/)
#define LOG_SINK  (*(volatile int32_t *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)

int imu_fusion_suspend(uint32_t p1, uint32_t p2, uint32_t p3)
{
    (void)p1; (void)p2;
    if (LOG_LEVEL > 2) {
        int32_t sink = LOG_SINK;
        if (sink == 0) {
            log_message(((unsigned long)"%s(): enter!\n") /*=0x9f72f*/,
                        ((unsigned long)"suspend") /*=0x9faf1*/, p3, (uint32_t)sink);
        } else {
            debug_print(((unsigned long)"%s(): enter!\n") /*=0x9f72f*/,
                        ((unsigned long)"suspend") /*=0x9faf1*/, p3, (uint32_t)sink);
        }
    }
    return 0;
}
