#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   0x000600e0       => struct g1_layout_pdm_mic_event_ctx__global_1272         [global_1272; G1-original]
 *   local_30         => struct g1_layout_pdm_mic_event_data__stack_1273         [stack_1273; G1-original]
 * Raw function identity: 0x0005ffa4.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0005ffa4 @ 0x0005ffa4
 * public-name: pdm_mic_event_handler
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   onoff_release                            <= FUN_0004ba38 @ 0x0004ba38
 *   pdm_mic_event_handler                    <= FUN_0005ffa4 @ 0x0005ffa4
 *   nrfx_pdm_buffer_set                      <= FUN_00066270 @ 0x00066270
 *   nrfx_pdm_stop                            <= FUN_00066300 @ 0x00066300
 *   k_mem_slab_alloc                         <= FUN_00071c20 @ 0x00071c20
 *   k_mem_slab_free                          <= FUN_00071cf4 @ 0x00071cf4
 *   k_msgq_put                               <= FUN_000720d0 @ 0x000720d0
 *   log_forward_zero_arg                     <= FUN_000837a2 @ 0x000837a2
 * address symbols (name @ address):
 *   rodata_881a0                             @ 0x000881a0
 *   rodata_f5822                             @ 0x000f5822
 *   rodata_f5840                             @ 0x000f5840
 *   rodata_f585d                             @ 0x000f585d
 *   g_pdm_mic_ctrl_blk                       @ 0x2000b008
 *   g_pdm_mic_rx_msgq                        @ 0x2000b024
 */
/* Reconstructed FUN_0005ffa4 @ 0x0005ffa4 (316-byte executable extent). */
#include <stdint.h>

extern void onoff_release(uint32_t handle);
extern int nrfx_pdm_buffer_set(uint32_t decoded, uint32_t selector);
extern void nrfx_pdm_stop(void);
extern int k_mem_slab_alloc(uint32_t handle, void *decoded, uint32_t zero, uint32_t zero2);
extern void k_mem_slab_free(uint32_t handle, ...);
extern int k_msgq_put(uintptr_t queue, void *payload, uint32_t zero, uint32_t zero2);
extern void log_forward_zero_arg(uintptr_t source, uint32_t level, const void *record);

struct notification {
    uint8_t response_ready;
    uint8_t reserved[3];
    uint32_t payload;
};

struct decoded_status {
    uint32_t words[4];
};

struct log2 {
    uint32_t count;
    uintptr_t format;
};

struct log3 {
    uint32_t count;
    uintptr_t format;
    int32_t value;
};

#define STATE_WORD(off) (*(volatile uint32_t *)(((unsigned long)&g_pdm_mic_ctrl_blk) /*=0x2000b008*/ + (off)))
#define STATE_BYTE(off) (*(volatile uint8_t *)(((unsigned long)&g_pdm_mic_ctrl_blk) /*=0x2000b008*/ + (off)))

static __attribute__((always_inline)) inline void clear_pending_activity(void)
{
    if (STATE_BYTE(0x51) != 0) {
        STATE_BYTE(0x51) = 0;
        if ((STATE_BYTE(0x50) & 1u) != 0)
            onoff_release(STATE_WORD(0));
    }
}

void pdm_mic_event_handler(struct notification *notification)
{
    uint8_t wake_recovery = notification->response_ready;

    if (notification->response_ready != 0) {
        struct decoded_status decoded;
        int status = k_mem_slab_alloc(STATE_WORD(0x14), &decoded, 0, 0);
        uintptr_t diagnostic = ((unsigned long)&rodata_f5822) /*=0xf5822*/;

        if (status >= 0) {
            status = nrfx_pdm_buffer_set(decoded.words[0],
                                  (STATE_WORD(0x18) >> 1) & 0xffffu);
            diagnostic = ((unsigned long)&rodata_f5840) /*=0xf5840*/;
        }

        if (status < 0 || status != 0x0bad0000) {
            const struct log3 record = {3, diagnostic, status};
            log_forward_zero_arg(((unsigned long)&rodata_881a0) /*=0x881a0*/, 0x1840u, &record);

            if (STATE_BYTE(0x52) == 0) {
                if (notification->payload == 0)
                    goto recover;
                goto transfer;
            }

            wake_recovery = STATE_BYTE(0x52);
            if (notification->payload == 0) {
                clear_pending_activity();
                goto recover;
            }
        } else {
            if (STATE_BYTE(0x52) == 0) {
                if (notification->payload == 0)
                    return;
                wake_recovery = 0;
                goto transfer;
            }
            if (notification->payload == 0) {
                clear_pending_activity();
                return;
            }
            wake_recovery = 0;
        }

        k_mem_slab_free(STATE_WORD(0x14));
        clear_pending_activity();
    } else {
        if (STATE_BYTE(0x52) != 0) {
            if (notification->payload == 0) {
                clear_pending_activity();
                return;
            }
            k_mem_slab_free(STATE_WORD(0x14));
            clear_pending_activity();
            return;
        }
        if (notification->payload == 0)
            return;
        wake_recovery = 0;
transfer:
        if (k_msgq_put(((unsigned long)&g_pdm_mic_rx_msgq) /*=0x2000b024*/, &notification->payload, 0, 0) < 0) {
            const struct log2 record = {2, ((unsigned long)&rodata_f585d) /*=0xf585d*/};
            log_forward_zero_arg(((unsigned long)&rodata_881a0) /*=0x881a0*/, 0x1040u, &record);
            k_mem_slab_free(STATE_WORD(0x14), notification->payload);
            goto recover;
        }
    }

    if (wake_recovery == 0)
        return;
recover:
    STATE_BYTE(0x52) = 1;
    nrfx_pdm_stop();
}
