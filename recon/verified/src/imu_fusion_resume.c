/* Reconstructed imu_fusion_resume @ 0x25dc4  (CFG-directed candidate) */
/* Reconstructed imu_fusion_resume @ 0x25dc4 (uncatalogued Ghidra gap
 * 0x25d8c..0x25ecc; code 0x25dc4..0x25de8, literal pool 0x25de8..0x25df8).
 * Vtable slot +0x94 written by register_imu_funsion_context (0x26250).
 * Name self-evidenced: the log tag 0x0009faf9 is "resume".
 */
#include <stdint.h>

extern int FUN_0007dda4(uint32_t format, uint32_t function, uint32_t a, uint32_t b);
extern int FUN_00019c70(uint32_t format, uint32_t function, uint32_t a, uint32_t b);

#define LOG_LEVEL (*(volatile int32_t *)0x2000230cUL)
#define LOG_SINK  (*(volatile int32_t *)0x20007554UL)

int imu_fusion_resume(uint32_t p1, uint32_t p2, uint32_t p3)
{
    (void)p1; (void)p2;
    if (LOG_LEVEL > 2) {
        int32_t sink = LOG_SINK;
        if (sink == 0) {
            FUN_0007dda4(0x0009f72fUL, 0x0009faf9UL, p3, (uint32_t)sink);
        } else {
            FUN_00019c70(0x0009f72fUL, 0x0009faf9UL, p3, (uint32_t)sink);
        }
    }
    return 0;
}
