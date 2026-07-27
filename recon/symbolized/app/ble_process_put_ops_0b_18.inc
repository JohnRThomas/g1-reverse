/* Exact outer PUT handlers 0x0b..0x18. Included by the dispatcher. */
#ifndef BLE_PROCESS_PUT_OPS_0B_18_INC
#define BLE_PROCESS_PUT_OPS_0B_18_INC

#include "ble_process_put_common.h"

extern int set_dashboard_startup_mode_field63();
extern int enqueue_file();
extern int mark_master_or_low_battery_flag();
extern int process_sync_buffer();
extern int device_info_set_bytes_cc_ce();
#ifdef G1_APP_SDK_INLINE_COHESION
extern int64_t z_impl_k_uptime_ticks(void);
/* Exact configured kernel.h/time_units.h owner: floor(ticks * 1000 / 32768). */
static __attribute__((always_inline)) inline uint64_t g1_sdk_uptime_get_0(void)
{
    return ((uint64_t)z_impl_k_uptime_ticks() * 1000u) >> 15;
}
#else
extern uint64_t k_uptime_get_0(void); /* k_uptime_get_0 @ 0x0007c18e */
#define g1_sdk_uptime_get_0() k_uptime_get_0()
#endif
extern int device_info_store_chunk();
extern int store_device_info_bytes_cd_cf();
extern int set_shutdown_flag();
extern int update_display_status();
extern int is_system_idle_ready();
extern int strcpy();
extern int update_persist_task_status();

#define OP0B18_STAGE       ((uint8_t *)(uintptr_t)0x200100ff)
#define OP0B18_PACKET_ID   (*(volatile uint8_t *)(uintptr_t)0x20002fe2)
#define OP0B18_TOKEN       (*(volatile uint32_t *)(uintptr_t)((unsigned long)&g_font_crc32) /*=0x200079e0*/)
#define OP0B18_AUDIO_OBJ   (*(volatile uint32_t *)(uintptr_t)((unsigned long)&g_ble_switch_status_reason) /*=0x20007aac*/)
#define OP0B18_LAST_INDEX  (*(volatile uint8_t *)(uintptr_t)((unsigned long)&g_ble_xfer_seq_prev) /*=0x20018d99*/)
#define OP0B18_LAST_COUNT  (*(volatile uint8_t *)(uintptr_t)((unsigned long)&g_ble_xfer_seq_cur) /*=0x20018d9a*/)
#define OP0B18_LAST_OP     (*(volatile uint8_t *)(uintptr_t)((unsigned long)&g_ble_dispatch_pending_marker) /*=0x20018d9b*/)

BLE_PUT_ALWAYS_INLINE void
ble_put_op0b_14(struct ble_put_context *ctx, const uint8_t *packet,
                const uint8_t *request, uint8_t response[20])
{
    ble_put_copy_ack(ctx, packet, request, response);
}

BLE_PUT_ALWAYS_INLINE void
ble_put_op0c_11_12_13(struct ble_put_context *ctx, uint8_t response[20])
{
    if (BLE_LOG_LEVEL > 1) {
        if (BLE_IS_DEBUG == 0)
            log_message((const void *)0x0009ba22, (const void *)0x0009e077);
        else
            debug_print((const void *)0x0009ba22, (const void *)0x0009e077);
    }
    response[1] = 0xca;
    response[2] = 0x15;
    strcpy(response + 2, (const void *)0x0009d4d5);
    ctx->post_to_host(response, 20);
}

BLE_PUT_ALWAYS_INLINE void
ble_put_op0d_0f(struct ble_put_context *ctx, const uint8_t *packet,
                const uint8_t *request, uint8_t response[20], int right)
{
    uint8_t *base = (uint8_t *)ctx;
    uint8_t *object = *(uint8_t **)(void *)(base + (right ? 0x88c : 0x888));
    uint16_t length = ble_put_le16(packet + 2);
    uint8_t count = request[2];
    uint8_t index = request[3];
    uint16_t fragment_length = (uint16_t)(length - 7u);
    int last = (uint32_t)index == (uint32_t)count - 1u;
    uint32_t sync_state[2];

    if (length != 0) {
        memset_bytes(OP0B18_STAGE, 0, 0x158);
        if (last) {
            response[1] = 0xc9;
        } else {
            device_info_store_chunk(object, 0x198, base[right ? -0x6b0 : -0x6af], right);
            if (right)
                device_info_set_bytes_cc_ce(request[1], 1);
            else
                store_device_info_bytes_cd_cf(request[1], 1, 0);
            response[1] = 0xcb;
        }
        safe_memcpy_checked(OP0B18_STAGE, request + 7, fragment_length, 0x158);
    }
    if ((int8_t)index == 0) {
        memset_bytes(object + 6, 0, 400);
        object[0x196] = 0;
        object[0x197] = 0;
        object[3] = request[4];
        ble_put_store16(object + 4,
                        (uint16_t)(((uint16_t)request[5] << 8) | request[6]));
    }
    memcpy(object + ble_put_le16(object + 0x196) + 6,
                  OP0B18_STAGE, fragment_length);
    ble_put_store16(object + 0x196,
                    (uint16_t)(ble_put_le16(object + 0x196) + fragment_length));
    ble_put_store16(ctx->transfer + 2, length);
    ctx->transfer_length = (uint32_t)length + 4u;
    if (last)
        audio_fw_load_get_wrapper(ctx, sync_state, 8);
    response[2] = request[1];
    response[3] = count;
    response[4] = index;
    if (get_device_type() == 1) {
        if (last) {
            OP0B18_LAST_OP = right ? 0x0f : 0x0d;
            OP0B18_LAST_INDEX = index;
            OP0B18_LAST_COUNT = count;
            if (right)
                device_info_set_bytes_cc_ce(request[1], 0);
            else
                store_device_info_bytes_cd_cf(request[1], 0);
        } else {
            ctx->post_to_host(response, 20);
        }
    } else {
        if (last) {
            if (right)
                device_info_set_bytes_cc_ce(request[1], 0);
            else
                store_device_info_bytes_cd_cf(request[1], 0);
        }
        ctx->post_to_host(response, 20);
    }
}

BLE_PUT_ALWAYS_INLINE void
ble_put_op0e(struct ble_put_context *ctx, const uint8_t *request,
             uint8_t response[20])
{
    uint8_t *base = (uint8_t *)ctx;
    uint8_t status;

    if (request[1] == 1) {
        uint8_t *root;
        int allowed = is_system_idle_ready() != 0;
        if (!allowed) {
            root = (uint8_t *)(uintptr_t)get_device_info();
            allowed = **(int **)(void *)(root + 0x1054) == 9;
        }
        if (!allowed) {
            root = (uint8_t *)(uintptr_t)get_device_info();
            allowed = **(int **)(void *)(root + 0x1054) == 0x10;
        }
        if (!allowed) {
            root = (uint8_t *)(uintptr_t)get_device_info();
            allowed = **(int **)(void *)(root + 0x1054) == 0x0b;
        }
        if (!allowed) {
            root = (uint8_t *)(uintptr_t)get_device_info();
            allowed = root[0xd5] == 0;
            if (allowed) {
                root = (uint8_t *)(uintptr_t)get_device_info();
                allowed = root[0xfe6] == 0;
            }
        }
        if (allowed) {
            root = (uint8_t *)(uintptr_t)get_device_info();
            if (**(int **)(void *)(root + 0x1054) == 0x10) {
                root = (uint8_t *)(uintptr_t)get_device_info();
                if (**(uint8_t **)(void *)(root + 0x100c) == 2) {
                    root = (uint8_t *)(uintptr_t)get_device_info();
                    **(uint8_t **)(void *)(root + 0x100c) = 3;
                }
            }
            base[0x8dd] |= 4;
            if (BLE_LOG_LEVEL > 2) {
                if (BLE_IS_DEBUG == 0)
                    log_message((const void *)0x0009bf34, (const void *)0x0009e077);
                else
                    debug_print((const void *)0x0009bf34, (const void *)0x0009e077);
            }
            process_sync_buffer(base - 0x714);
            status = 0xc9;
        } else {
            status = 0xca;
        }
    } else {
        if (BLE_LOG_LEVEL > 2) {
            if (BLE_IS_DEBUG == 0)
                log_message((const void *)0x0009bf5b, (const void *)0x0009e077);
            else
                debug_print((const void *)0x0009bf5b, (const void *)0x0009e077);
        }
        mark_master_or_low_battery_flag();
        status = 0xc9;
    }
    response[1] = status;
    response[2] = request[1];
    ctx->post_to_host(response, 20);
}

BLE_PUT_ALWAYS_INLINE void
ble_put_op10_media(struct ble_put_context *ctx, const uint8_t *packet,
                   const uint8_t *request, uint8_t response[20])
{
    uint8_t *root;
    uint8_t subcommand = request[4];
    uint8_t status = 0xca;

    response[1] = 6;
    response[2] = 0;
    response[3] = request[3];
    response[4] = subcommand;
    if (ble_put_le16(packet + 2) == ble_put_le16(request + 1) && subcommand < 3) {
        if (subcommand == 1) {
            root = (uint8_t *)(uintptr_t)get_device_info();
            if (*(uint32_t *)(void *)(root + 0xf68) != 0) {
                if (BLE_LOG_LEVEL > 1) {
                    if (BLE_IS_DEBUG == 0)
                        log_message((const void *)0x0009b9e4, (const void *)0x0009e077);
                    else
                        debug_print((const void *)0x0009b9e4, (const void *)0x0009e077);
                }
                root = (uint8_t *)(uintptr_t)get_device_info();
                *(uint32_t *)(void *)(root + 0xf68) = 0;
                root = (uint8_t *)(uintptr_t)get_device_info();
                *(uint32_t *)(void *)(root + 0x104c) = 0;
                root = (uint8_t *)(uintptr_t)get_device_info();
                process_sync_buffer(root + 0x80);
            }
        } else if (subcommand == 2) {
            root = (uint8_t *)(uintptr_t)get_device_info();
            if (request[5] == 1) {
                **(uint8_t **)(void *)(root + 0x101c) = 1;
                root = (uint8_t *)(uintptr_t)get_device_info();
                (*(uint8_t **)(void *)(root + 0x101c))[1] = request[6];
                root = (uint8_t *)(uintptr_t)get_device_info();
                if ((*(uint8_t **)(void *)(root + 0x101c))[1] == 1) {
                    if (BLE_LOG_LEVEL > 1) {
                        if (BLE_IS_DEBUG == 0)
                            log_message((const void *)0x0009ba06,
                                        (const void *)0x0009e077, OP0B18_AUDIO_OBJ);
                        else
                            debug_print((const void *)0x0009ba06,
                                        (const void *)0x0009e077, OP0B18_AUDIO_OBJ);
                    }
                    root = (uint8_t *)(uintptr_t)get_device_info();
                    *(uint32_t *)(void *)(root + 0xf68) = OP0B18_AUDIO_OBJ;
                    root = (uint8_t *)(uintptr_t)get_device_info();
                    *(uint32_t *)(void *)(root + 0x104c) = 0;
                    root = (uint8_t *)(uintptr_t)get_device_info();
                    process_sync_buffer(root + 0x80);
                }
                ((uint8_t *)ctx)[-0x6af] = request[3];
                root = (uint8_t *)(uintptr_t)get_device_info();
                update_persist_task_status(root, 0x11, 2);
            } else {
                **(uint8_t **)(void *)(root + 0x101c) = 0;
            }
        }
        status = 0xc9;
    }
    response[5] = status;
    ctx->post_to_host(response, 20);
}

BLE_PUT_ALWAYS_INLINE void
ble_put_op15(struct ble_put_context *ctx, const uint8_t *packet,
             const uint8_t *request, uint8_t response[20])
{
    uint8_t *base = (uint8_t *)ctx;
    ++OP0B18_PACKET_ID;
    if (request[1] == OP0B18_PACKET_ID) {
        enqueue_file(request + 1, (uint16_t)(ble_put_le16(packet + 2) - 1u) & 0xffu);
        *(uint32_t *)(void *)(base + 0x8d0) = 0x15;
        process_sync_buffer(base - 0x6fc);
    } else {
        response[1] = OP0B18_PACKET_ID;
        response[2] = 0xca;
        ctx->post_to_host(response, 20);
        --OP0B18_PACKET_ID;
        if (BLE_LOG_LEVEL > 0) {
            if (BLE_IS_DEBUG == 0)
                log_message((const void *)0x0009bfa5, (const void *)0x0009e077);
            else
                debug_print((const void *)0x0009bfa5, (const void *)0x0009e077);
        }
    }
    *(uint64_t *)(void *)(base + 0x8e4) = g1_sdk_uptime_get_0();
}

BLE_PUT_ALWAYS_INLINE void
ble_put_op16(struct ble_put_context *ctx, const uint8_t *packet,
             const uint8_t *request, uint8_t response[20])
{
    uint8_t *base = (uint8_t *)ctx;
    uint32_t token = ((uint32_t)request[1] << 24) |
                     ((uint32_t)request[2] << 16) |
                     ((uint32_t)request[3] << 8) | request[4];
    response[1] = request[1];
    response[2] = request[2];
    response[3] = request[3];
    response[4] = request[4];
    response[5] = token == OP0B18_TOKEN ? 0xc9 : 0xca;
    ctx->post_to_host(response, 20);
    *(uint32_t *)(void *)(base + 0x8d0) = packet[0];
    process_sync_buffer(base - 0x6fc);
}

BLE_PUT_ALWAYS_INLINE void
ble_put_op17(struct ble_put_context *ctx, const uint8_t *packet,
             uint8_t response[20])
{
    uint8_t *base = (uint8_t *)ctx;
    set_dashboard_startup_mode_field63(1);
    *(uint64_t *)(void *)(base + 0x8e4) = g1_sdk_uptime_get_0();
    *(uint32_t *)(void *)(base + 0x8d0) = packet[0];
    process_sync_buffer(base - 0x6fc);
    response[1] = 0xc9;
    ctx->post_to_host(response, 20);
}

BLE_PUT_ALWAYS_INLINE void
ble_put_op18(struct ble_put_context *ctx, uint8_t response[20])
{
    uint8_t *base = (uint8_t *)ctx;
    uint8_t *root = (uint8_t *)(uintptr_t)get_device_info();
    if (root[0xd5] == 0x0b ||
        ((root = (uint8_t *)(uintptr_t)get_device_info()), root[0xd5] == 0x10))
        update_display_status(base - 0x77c, 0);
    else
        set_shutdown_flag(base - 0x77c, 0);
    response[1] = 0xc9;
    ctx->post_to_host(response, 20);
}

#endif
