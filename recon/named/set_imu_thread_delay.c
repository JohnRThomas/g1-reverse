#include "g1_app_symbols.h"
/* readable reconstruction; identity: set_imu_thread_delay @ 0x00025d8c
 * public-name: set_imu_thread_delay
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   log_message                              <= FUN_0007dda4 @ 0x0007dda4
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 * address symbols (name @ address):
 *   rodata_9f721                             @ 0x0009f721
 *   rodata_9fb00                             @ 0x0009fb00
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed set_imu_thread_delay @ 0x25d8c (uncatalogued Ghidra gap
 * 0x25d8c..0x25ecc; code 0x25d8c..0x25db4, literal pool 0x25db4..0x25dc4).
 * (parity: cfg_verify PASS, 200/200 trials)
 * Vtable slot +0x98 written by register_imu_funsion_context (0x26250).
 * Name self-evidenced: the log tag 0x0009fb00 is "set_imu_thread_delay".
 */
#include <stdint.h>

extern int log_message(uint32_t format, uint32_t function, uint32_t a, uint32_t b);
extern int debug_print(uint32_t format, uint32_t function, uint32_t a, uint32_t b);

#define LOG_LEVEL (*(volatile int32_t *)((unsigned long)&g_log_level) /*=0x2000230c*/)
#define LOG_SINK  (*(volatile int32_t *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)

int set_imu_thread_delay(unsigned char *context, int delay_ms)
{
    if (*(volatile int32_t *)(context + 0x18) != delay_ms) {
        *(volatile int32_t *)(context + 0x18) = delay_ms;
        if (LOG_LEVEL > 2) {
            int32_t sink = LOG_SINK;
            if (sink == 0) {
                return log_message(((unsigned long)&rodata_9f721) /*=0x9f721*/,
                                   ((unsigned long)&rodata_9fb00) /*=0x9fb00*/,
                                   (uint32_t)delay_ms, (uint32_t)sink);
            }
            return debug_print(((unsigned long)&rodata_9f721) /*=0x9f721*/,
                               ((unsigned long)&rodata_9fb00) /*=0x9fb00*/,
                               (uint32_t)delay_ms, (uint32_t)sink);
        }
    }
    return (int)(unsigned long)context;
}
