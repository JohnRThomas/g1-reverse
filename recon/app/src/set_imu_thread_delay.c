/* Reconstructed set_imu_thread_delay @ 0x25d8c  (CFG-directed candidate) */
/* Reconstructed set_imu_thread_delay @ 0x25d8c (uncatalogued Ghidra gap
 * 0x25d8c..0x25ecc; code 0x25d8c..0x25db4, literal pool 0x25db4..0x25dc4).
 * Vtable slot +0x98 written by register_imu_funsion_context (0x26250).
 * Name self-evidenced: the log tag 0x0009fb00 is "set_imu_thread_delay".
 */
#include <stdint.h>

extern void FUN_0007dda4(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);

#define LOG_LEVEL (*(volatile int32_t *)0x2000230cUL)
#define LOG_SINK  (*(volatile int32_t *)0x20007554UL)
#define LOG_TAG   0x0009fb00UL

/* G7-B2: both sinks are void variadic (see recon/headers/g1_log.h); the
 * fall-through at 0x25db0 is a bare `bx lr` with r0 untouched and both logging
 * paths are tail calls, so this function computes no return value.  0x0009f721
 * is "%s(): %d(ms)\n" -- two specifiers, three arguments; the fourth the body
 * used to pass was the g_log_use_alt_sink value left in r3 by the branch. */
void set_imu_thread_delay(unsigned char *context, int delay_ms)
{
    if (*(volatile int32_t *)(context + 0x18) != delay_ms) {
        *(volatile int32_t *)(context + 0x18) = delay_ms;
        if (LOG_LEVEL > 2) {
            if (LOG_SINK == 0) {
                FUN_0007dda4(0x0009f721UL, LOG_TAG, (uint32_t)delay_ms);
                return;
            }
            FUN_00019c70(0x0009f721UL, LOG_TAG, (uint32_t)delay_ms);
        }
    }
}
