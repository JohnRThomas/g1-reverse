#include <zephyr/kernel.h>
#undef NRF_NVMC_S
#include "g1_app_symbols.h"
/* readable reconstruction; identity: imu_fusion_init @ 0x00025fac
 * public-name: imu_fusion_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_type                          <= FUN_00016568 @ 0x00016568
 *   dev_api_call_slot0                       <= FUN_0007ca54 @ 0x0007ca54
 *   imu_fusion_state_init                    <= FUN_000265b8 @ 0x000265b8
 *   panel_level_calc_cached                  <= FUN_00025ecc @ 0x00025ecc
 *   z_impl_k_thread_create                   <= FUN_00071eac @ 0x00071eac
 *   log_message                              <= FUN_0007dda4 @ 0x0007dda4
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 * address symbols (name @ address):
 *   rodata_9f773                             @ 0x0009f773
 *   rodata_9f797                             @ 0x0009f797
 *   rodata_9f7c3                             @ 0x0009f7c3
 *   rodata_9f812                             @ 0x0009f812
 *   rodata_9f851                             @ 0x0009f851
 *   rodata_9fae1                             @ 0x0009fae1
 *   rodata_87d58                             @ 0x00087d58   (LSM6DSO struct device)
 *   ADDR_imu_fusion_thread_THUMB             @ 0x0000fe89
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_imu_fusion_thread                      @ 0x20003fe8
 *   g_imu_fusion_thread_stack                @ 0x20023568
 */
/* Reconstructed imu_fusion_init @ 0x25fac (uncatalogued Ghidra gap
 * 0x25f90..0x26100; 0x25f90..0x25fac is panel_level_calc_cached's literal
 * pool, code 0x25fac..0x260d0, literal pool 0x260d0..0x26100).
 * (parity: cfg_verify PASS, 200/200 trials)
 *
 * Vtable slot +0x8c written by register_imu_funsion_context (0x26250); main()
 * calls it as ctx->fn[+0x8c](ctx) via `ldr r3,[r4,#0xf70] ; blx r3`.
 * Name self-evidenced: the log tag 0x0009fae1 is "imu_fusion_init".
 * Contains the 13th (and only uncatalogued) k_thread_create call site,
 * 0x260c2 -- the sole creator of imu_fusion_thread.
 */
#include <stdint.h>

extern int log_message(uint32_t format, uint32_t function, uint32_t a, uint32_t b);
extern int debug_print(uint32_t format, uint32_t function, uint32_t a, uint32_t b);
extern int get_device_type(void);
extern int dev_api_call_slot0(uint32_t device, int slot, void *value);
extern void imu_fusion_state_init(void *state);
extern int panel_level_calc_cached(void *context);

#define LOG_LEVEL (*(volatile int32_t *)((unsigned long)&g_log_level) /*=0x2000230c*/)
#define LOG_SINK  (*(volatile int32_t *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)
#define LOG_TAG   ((unsigned long)&rodata_9fae1) /*=0x9fae1*/

int imu_fusion_init(unsigned char *context, uint32_t p2, uint32_t p3)
{
    int32_t sink;
    int rc;

    (void)p2;
    if (context[0x14] != 0) {
        if (LOG_LEVEL > 1) {
            sink = LOG_SINK;
            if (sink == 0) {
                log_message(((unsigned long)&rodata_9f773) /*=0x9f773*/, LOG_TAG, p3, (uint32_t)sink);
            } else {
                debug_print(((unsigned long)&rodata_9f773) /*=0x9f773*/, LOG_TAG, p3, (uint32_t)sink);
            }
        }
        return -1;
    }

    get_device_type();
    *(volatile uint32_t *)(context + 0x1c) = ((unsigned long)&rodata_87d58) /*=0x87d58*/;
    if (LOG_LEVEL > 1) {
        sink = LOG_SINK;
        if (sink == 0) {
            log_message(((unsigned long)&rodata_9f797) /*=0x9f797*/, LOG_TAG, p3, (uint32_t)sink);
        } else {
            debug_print(((unsigned long)&rodata_9f797) /*=0x9f797*/, LOG_TAG, p3, (uint32_t)sink);
        }
    }

    *(volatile uint32_t *)(context + 0x20) = (get_device_type() == 1) ? 0x34u : 0u;
    *(volatile uint32_t *)(context + 0x24) = 0u;
    rc = dev_api_call_slot0(*(volatile uint32_t *)(context + 0x1c), 3,
                            (void *)(context + 0x20));
    if (rc < 0) {
        if (LOG_LEVEL > 1) {
            sink = LOG_SINK;
            if (sink == 0) {
                log_message(((unsigned long)&rodata_9f7c3) /*=0x9f7c3*/, LOG_TAG, (uint32_t)rc, (uint32_t)sink);
            } else {
                debug_print(((unsigned long)&rodata_9f7c3) /*=0x9f7c3*/, LOG_TAG, (uint32_t)rc, (uint32_t)sink);
            }
        }
        return -3;
    }

    get_device_type();
    *(volatile uint32_t *)(context + 0x20) = 0u;
    *(volatile uint32_t *)(context + 0x24) = 0u;
    rc = dev_api_call_slot0(*(volatile uint32_t *)(context + 0x1c), 7,
                            (void *)(context + 0x20));
    if (rc < 0) {
        if (LOG_LEVEL > 1) {
            sink = LOG_SINK;
            if (sink == 0) {
                log_message(((unsigned long)&rodata_9f812) /*=0x9f812*/, LOG_TAG,
                            (uint32_t)(unsigned long)(context + 0x20), (uint32_t)sink);
            } else {
                debug_print(((unsigned long)&rodata_9f812) /*=0x9f812*/, LOG_TAG,
                            (uint32_t)(unsigned long)(context + 0x20), (uint32_t)sink);
            }
        }
        return -4;
    }

    *(volatile uint32_t *)(context + 0x18) = 0u;
    if (LOG_LEVEL > 1) {
        sink = LOG_SINK;
        if (sink == 0) {
            log_message(((unsigned long)&rodata_9f851) /*=0x9f851*/, LOG_TAG,
                        (uint32_t)(unsigned long)(context + 0x20), (uint32_t)sink);
        } else {
            debug_print(((unsigned long)&rodata_9f851) /*=0x9f851*/, LOG_TAG,
                        (uint32_t)(unsigned long)(context + 0x20), (uint32_t)sink);
        }
    }

    imu_fusion_state_init((void *)(context + 0x28));
    *(volatile uint16_t *)(context + 0x14) = 0x100u;
    panel_level_calc_cached((void *)context);
    k_thread_create((struct k_thread *)((unsigned long)&g_imu_fusion_thread) /*=0x20003fe8*/,
                    (k_thread_stack_t *)((unsigned long)&g_imu_fusion_thread_stack) /*=0x20023568*/,
                    0x700,
                    (k_thread_entry_t)(unsigned long)(ADDR_imu_fusion_thread_THUMB /*=0xfe89*/),
                    (void *)context, NULL, NULL,
                    -11, 0, K_NO_WAIT);
    return 0;
}
