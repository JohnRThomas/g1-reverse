#include "g1_app_symbols.h"
/* readable reconstruction; identity: set_imu_thread_delay @ 0x00025d8c
 * public-name: set_imu_thread_delay
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   log_message                              <= FUN_0007dda4 @ 0x0007dda4
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 * address symbols (name @ address):
 *   rodata_9f721                             @ 0x0009f721   [INLINED -- G6 literal batch]
 *   rodata_9fb00                             @ 0x0009fb00   [INLINED -- G6 literal batch]
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
#include "../../headers/g1_log.h"


#define LOG_LEVEL (*(volatile int32_t *)((unsigned long)&g_log_level) /*=0x2000230c*/)
#define LOG_SINK  (*(volatile int32_t *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)

/* G7-B2 defect fix, two corrections, both read off 0x25d8c..0x25db0.
 *
 * (1) RETURN TYPE.  The body used to be `int` and to `return` the result of
 *     the logging call.  The shipped function never writes r0 on the fall
 *     through path -- 0x25db0 is a bare `bx lr` with the incoming `context`
 *     pointer still in r0 -- and the two logging paths are TAIL calls
 *     (`b.w 0x19c70` / `b.w 0x7dda4`), so what they leave in r0 is the sink's
 *     scratch, not a value this function computes.  Both sinks are `void`
 *     (recon/headers/g1_log.h), so the `int` was a decompiler artefact.  As
 *     `void` the codegen is unchanged: the fall-through is still `bx lr` with
 *     r0 untouched and both logging paths are still tail calls.
 *
 * (2) ARGUMENT COUNT.  0x0009f721 is "%s(): %d(ms)\n" -- two specifiers, so
 *     three arguments.  0x25d9e..0x25da4 load exactly r0 (format), r1 (tag)
 *     and r2 (already `mov r2, r1` at 0x25d8e, the delay).  The fourth
 *     argument the body used to pass was r3, which holds the
 *     g_log_use_alt_sink value the branch at 0x25da6 had just loaded.
 */
void set_imu_thread_delay(unsigned char *context, int delay_ms)
{
    if (*(volatile int32_t *)(context + 0x18) != delay_ms) {
        *(volatile int32_t *)(context + 0x18) = delay_ms;
        if (LOG_LEVEL > 2) {
            if (LOG_SINK == 0) {
                log_message(((unsigned long)"%s(): %d(ms)\n") /*=0x9f721*/,
                            ((unsigned long)"set_imu_thread_delay") /*=0x9fb00*/,
                            (uint32_t)delay_ms);
                return;
            }
            debug_print(((unsigned long)"%s(): %d(ms)\n") /*=0x9f721*/,
                        ((unsigned long)"set_imu_thread_delay") /*=0x9fb00*/,
                        (uint32_t)delay_ms);
        }
    }
}
