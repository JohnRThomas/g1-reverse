### FUN_0005ffa4  @ 0x0005ffa4  (size=316)

callers (0): (none / root or address-taken)
callees (7): FUN_0004ba38, nrfx_pdm_buffer_set, nrfx_pdm_stop, k_mem_slab_alloc, k_mem_slab_free, k_msgq_put, FUN_000837a2
strings: "Failed to allocate buffer: %d" | "Failed to set buffer: 0x%08x" | "No room in RX queue"

```c
/* readable reconstruction; identity: FUN_0005ffa4 @ 0x0005ffa4
 * public-name: FUN_0005ffa4
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   nrfx_pdm_buffer_set                      <= FUN_00066270 @ 0x00066270
 *   nrfx_pdm_stop                            <= FUN_00066300 @ 0x00066300
 *   k_mem_slab_alloc                         <= FUN_00071c20 @ 0x00071c20
 *   k_mem_slab_free                          <= FUN_00071cf4 @ 0x00071cf4
 *   k_msgq_put                               <= FUN_000720d0 @ 0x000720d0
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

extern void FUN_0004ba38(uint32_t handle);
extern int nrfx_pdm_buffer_set(uint32_t decoded, uint32_t selector);
extern void nrfx_pdm_stop(void);
extern int k_mem_slab_alloc(uint32_t handle, void *decoded, uint32_t zero, uint32_t zero2);
extern void k_mem_slab_free(uint32_t handle, ...);
extern int k_msgq_put(uintptr_t queue, void *payload, uint32_t zero, uint32_t zero2);
extern void FUN_000837a2(uintptr_t source, uint32_t level, const void *record);

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

#define STATE_WORD(off) (*(volatile uint32_t *)(0x2000b008u + (off)))
#define STATE_BYTE(off) (*(volatile uint8_t *)(0x2000b008u + (off)))

static __attribute__((always_inline)) inline void clear_pending_activity(void)
{
    if (STATE_BYTE(0x51) != 0) {
        STATE_BYTE(0x51) = 0;
        if ((STATE_BYTE(0x50) & 1u) != 0)
            FUN_0004ba38(STATE_WORD(0));
    }
}

void FUN_0005ffa4(struct notification *notification)
{
    uint8_t wake_recovery = notification->response_ready;

    if (notification->response_ready != 0) {
        struct decoded_status decoded;
        int status = k_mem_slab_alloc(STATE_WORD(0x14), &decoded, 0, 0);
        uintptr_t diagnostic = 0x000f5822u;

        if (status >= 0) {
            status = nrfx_pdm_buffer_set(decoded.words[0],
                                  (STATE_WORD(0x18) >> 1) & 0xffffu);
            diagnostic = 0x000f5840u;
        }

        if (status < 0 || status != 0x0bad0000) {
            const struct log3 record = {3, diagnostic, status};
            FUN_000837a2(0x000881a0u, 0x1840u, &record);

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
        if (k_msgq_put(0x2000b024u, &notification->payload, 0, 0) < 0) {
            const struct log2 record = {2, 0x000f585du};
            FUN_000837a2(0x000881a0u, 0x1040u, &record);
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
```