#include "g1_app_symbols.h"
/* readable reconstruction; identity: imu_fusion_resume @ 0x00025dc4
 * public-name: imu_fusion_resume
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   log_message                              <= FUN_0007dda4 @ 0x0007dda4
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 * address symbols (name @ address):
 *   rodata_9f72f                             @ 0x0009f72f   [INLINED -- G6 literal batch]
 *   rodata_9faf9                             @ 0x0009faf9   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed imu_fusion_resume @ 0x25dc4 (uncatalogued Ghidra gap
 * 0x25d8c..0x25ecc; code 0x25dc4..0x25de8, literal pool 0x25de8..0x25df8).
 * (parity: cfg_verify PASS, 200/200 trials)
 * Vtable slot +0x94 written by register_imu_funsion_context (0x26250).
 * Name self-evidenced: the log tag 0x0009faf9 is "resume".
 */
#include <stdint.h>

extern int log_message(uint32_t format, uint32_t function, uint32_t a, uint32_t b);
extern int debug_print(uint32_t format, uint32_t function, uint32_t a, uint32_t b);

#define LOG_LEVEL (*(volatile int32_t *)((unsigned long)&g_log_level) /*=0x2000230c*/)
#define LOG_SINK  (*(volatile int32_t *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)

int imu_fusion_resume(uint32_t p1, uint32_t p2, uint32_t p3)
{
    (void)p1; (void)p2;
    if (LOG_LEVEL > 2) {
        int32_t sink = LOG_SINK;
        if (sink == 0) {
            log_message(((unsigned long)"%s(): enter!\n") /*=0x9f72f*/,
                        ((unsigned long)"resume") /*=0x9faf9*/, p3, (uint32_t)sink);
        } else {
            debug_print(((unsigned long)"%s(): enter!\n") /*=0x9f72f*/,
                        ((unsigned long)"resume") /*=0x9faf9*/, p3, (uint32_t)sink);
        }
    }
    return 0;
}
