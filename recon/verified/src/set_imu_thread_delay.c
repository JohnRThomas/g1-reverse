/* Reconstructed set_imu_thread_delay @ 0x25d8c  (CFG-directed candidate) */
/* Reconstructed set_imu_thread_delay @ 0x25d8c (uncatalogued Ghidra gap
 * 0x25d8c..0x25ecc; code 0x25d8c..0x25db4, literal pool 0x25db4..0x25dc4).
 * Vtable slot +0x98 written by register_imu_funsion_context (0x26250).
 * Name self-evidenced: the log tag 0x0009fb00 is "set_imu_thread_delay".
 */
#include <stdint.h>

extern int FUN_0007dda4(uint32_t format, uint32_t function, uint32_t a, uint32_t b);
extern int FUN_00019c70(uint32_t format, uint32_t function, uint32_t a, uint32_t b);

#define LOG_LEVEL (*(volatile int32_t *)0x2000230cUL)
#define LOG_SINK  (*(volatile int32_t *)0x20007554UL)
#define LOG_TAG   0x0009fb00UL

int set_imu_thread_delay(unsigned char *context, int delay_ms)
{
    if (*(volatile int32_t *)(context + 0x18) != delay_ms) {
        *(volatile int32_t *)(context + 0x18) = delay_ms;
        if (LOG_LEVEL > 2) {
            int32_t sink = LOG_SINK;
            if (sink == 0) {
                return FUN_0007dda4(0x0009f721UL, LOG_TAG, (uint32_t)delay_ms, (uint32_t)sink);
            }
            return FUN_00019c70(0x0009f721UL, LOG_TAG, (uint32_t)delay_ms, (uint32_t)sink);
        }
    }
    return (int)(unsigned long)context;
}
