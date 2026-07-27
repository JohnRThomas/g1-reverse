/* Reconstructed imu_fusion_init @ 0x25fac  (CFG-directed candidate) */
/* Reconstructed imu_fusion_init @ 0x25fac (uncatalogued Ghidra gap
 * 0x25f90..0x26100; 0x25f90..0x25fac is panel_level_calc_cached's literal
 * pool, code 0x25fac..0x260d0, literal pool 0x260d0..0x26100).
 *
 * Vtable slot +0x8c written by register_imu_funsion_context (0x26250); main()
 * calls it as ctx->fn[+0x8c](ctx) via `ldr r3,[r4,#0xf70] ; blx r3`.
 * Name self-evidenced: the log tag 0x0009fae1 is "imu_fusion_init".
 * Contains the 13th (and only uncatalogued) k_thread_create call site,
 * 0x260c2, which creates imu_fusion_thread (entry 0x0000fe89, thread object
 * 0x20003fe8, stack 0x20023568 size 0x700, priority -11, K_NO_WAIT).
 */
#include <stdint.h>

extern void FUN_0007dda4(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);
extern int FUN_00016568(void);                                   /* get_device_type */
extern int FUN_0007ca54(uint32_t device, int slot, void *value); /* dev_api_call_slot0 */
extern void FUN_000265b8(void *state);                           /* imu_fusion_state_init */
extern int FUN_00025ecc(void *context);                          /* panel_level_calc_cached */
extern int FUN_00071eac(uint32_t thread, uint32_t stack, uint32_t stack_size,
                        uint32_t entry, uint32_t p1, uint32_t p2, uint32_t p3,
                        int prio, uint32_t options, unsigned long long delay);

#define LOG_LEVEL (*(volatile int32_t *)0x2000230cUL)
#define LOG_SINK  (*(volatile int32_t *)0x20007554UL)
#define LOG_TAG   0x0009fae1UL

int imu_fusion_init(unsigned char *context, uint32_t p2, uint32_t p3)
{
    int32_t sink;
    int rc;

    if (context[0x14] != 0) {
        if (LOG_LEVEL > 1) {
            sink = LOG_SINK;
            if (sink == 0) {
                FUN_0007dda4(0x0009f773UL, LOG_TAG, p3, (uint32_t)sink);
            } else {
                FUN_00019c70(0x0009f773UL, LOG_TAG, p3, (uint32_t)sink);
            }
        }
        return -1;
    }

    FUN_00016568();
    *(volatile uint32_t *)(context + 0x1c) = 0x00087d58UL;
    if (LOG_LEVEL > 1) {
        sink = LOG_SINK;
        if (sink == 0) {
            FUN_0007dda4(0x0009f797UL, LOG_TAG, p3, (uint32_t)sink);
        } else {
            FUN_00019c70(0x0009f797UL, LOG_TAG, p3, (uint32_t)sink);
        }
    }

    *(volatile uint32_t *)(context + 0x20) =
        (FUN_00016568() == 1) ? 0x34u : 0u;
    *(volatile uint32_t *)(context + 0x24) = 0u;
    rc = FUN_0007ca54(*(volatile uint32_t *)(context + 0x1c), 3,
                      (void *)(context + 0x20));
    if (rc < 0) {
        if (LOG_LEVEL > 1) {
            sink = LOG_SINK;
            if (sink == 0) {
                FUN_0007dda4(0x0009f7c3UL, LOG_TAG, (uint32_t)rc, (uint32_t)sink);
            } else {
                FUN_00019c70(0x0009f7c3UL, LOG_TAG, (uint32_t)rc, (uint32_t)sink);
            }
        }
        return -3;
    }

    FUN_00016568();
    *(volatile uint32_t *)(context + 0x20) = 0u;
    *(volatile uint32_t *)(context + 0x24) = 0u;
    rc = FUN_0007ca54(*(volatile uint32_t *)(context + 0x1c), 7,
                      (void *)(context + 0x20));
    if (rc < 0) {
        if (LOG_LEVEL > 1) {
            sink = LOG_SINK;
            if (sink == 0) {
                FUN_0007dda4(0x0009f812UL, LOG_TAG,
                             (uint32_t)(unsigned long)(context + 0x20), (uint32_t)sink);
            } else {
                FUN_00019c70(0x0009f812UL, LOG_TAG,
                             (uint32_t)(unsigned long)(context + 0x20), (uint32_t)sink);
            }
        }
        return -4;
    }

    *(volatile uint32_t *)(context + 0x18) = 0u;
    if (LOG_LEVEL > 1) {
        sink = LOG_SINK;
        if (sink == 0) {
            FUN_0007dda4(0x0009f851UL, LOG_TAG,
                         (uint32_t)(unsigned long)(context + 0x20), (uint32_t)sink);
        } else {
            FUN_00019c70(0x0009f851UL, LOG_TAG,
                         (uint32_t)(unsigned long)(context + 0x20), (uint32_t)sink);
        }
    }

    FUN_000265b8((void *)(context + 0x28));
    *(volatile uint16_t *)(context + 0x14) = 0x100u;
    FUN_00025ecc((void *)context);
    FUN_00071eac(0x20003fe8UL, 0x20023568UL, 0x700u, 0x0000fe89UL,
                 (uint32_t)(unsigned long)context, 0u, 0u, -11, 0u, 0ULL);
    return 0;
}
