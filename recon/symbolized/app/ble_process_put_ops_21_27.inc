#ifndef BLE_PROCESS_PUT_OPS_21_27_INC
#define BLE_PROCESS_PUT_OPS_21_27_INC

#include <stdint.h>
#include <stddef.h>

extern int log_message();
extern int get_device_type();
extern int audio_fw_load_get_wrapper();
extern int debug_print();
extern int is_battery_critical();
extern int sync_dashboard_default_language();
extern int send_response_data_to_msgqueue();
extern int FUN_0007c1dc();
extern int memcpy();
extern int memset_bytes();
extern int strcpy();
extern int process_sync_buffer();

#define OP21_LOG_LEVEL (*(volatile int32_t *)(uintptr_t)((unsigned long)&g_log_level) /*=0x2000230c*/)
#define OP21_IS_DEBUG (*(volatile uint32_t *)(uintptr_t)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)
#define OP25_SYNC_COUNT (*(volatile uint32_t *)(uintptr_t)((unsigned long)&g_20007564) /*=0x20007564*/)
#define OP26_MIC_SEM ((void *)(uintptr_t)((unsigned long)&g_20007bd4) /*=0x20007bd4*/)

typedef int (*ble_put_post_21_fn)(const void *, uint32_t);

struct ble_put_context_21_27 {
    uint8_t reserved_000[0x0c];
    ble_put_post_21_fn post_to_host;
    uint8_t *rx;
    uint32_t frame_length;
    uint8_t reserved_018[0x858];
    uint8_t *imu_state;
    uint8_t reserved_874[0x0c];
    uint8_t *teleprompter;
};

BLE_PUT_ALWAYS_INLINE uint16_t ble_put_21_rd16(const uint8_t *p)
{
    return (uint16_t)p[0] | (uint16_t)((uint16_t)p[1] << 8);
}

BLE_PUT_ALWAYS_INLINE uint32_t ble_put_21_rd32_explicit(const uint8_t *p)
{
    return (uint32_t)p[0] | ((uint32_t)p[1] << 8) |
           ((uint32_t)p[2] << 16) | ((uint32_t)p[3] << 24);
}

static inline __attribute__((always_inline))
int ble_put_ops_21_27(struct ble_put_context_21_27 *ctx, uint8_t command,
                      const uint8_t *packet, const uint8_t *payload,
                      uint8_t response[20])
{
    uint16_t advertised;
    uint16_t actual;
    uint8_t subcommand;
    uint8_t *tele;
    int ret;

    if (command == 0x21U || command == 0x23U) {
        response[0] = command;
        response[1] = 0xca;
        response[2] = 0x15;
        strcpy(response + 2, (const void *)0x0009d4d5);
        (void)ctx->post_to_host(response, 20);
        return 1;
    }

    if (command == 0x22U) {
        advertised = ble_put_21_rd16(payload + 1);
        actual = ble_put_21_rd16(packet + 2);
        if (advertised != actual) {
            if (OP21_LOG_LEVEL > 0) {
                if (OP21_IS_DEBUG == 0)
                    log_message("%s(): dashboard information packet length error,input data length = %d,packet data length = %d\n",
                                "ble_process_put_req");
                else
                    debug_print("%s(): dashboard information packet length error,input data length = %d,packet data length = %d\n",
                                 "ble_process_put_req");
            }
            return 1;
        }
        if (OP21_LOG_LEVEL > 2) {
            if (OP21_IS_DEBUG == 0)
                log_message("%s(): received sync id = %d\n",
                            "ble_process_put_req", (unsigned)payload[3]);
            else
                debug_print();
        }
        if (payload[4] == 1U) {
            for (unsigned i = 8; i != 20; ++i)
                response[i] = 0;
            *(uint32_t *)(void *)response = *(const uint32_t *)(const void *)payload;
            response[4] = payload[4];
            response[5] = *((uint8_t *)(void *)ctx - 0x69f);
            response[6] = (uint8_t)(sync_dashboard_default_language() + 1);
            response[7] = ctx->imu_state[0x5f];
            (void)ctx->post_to_host(response, 8);
        }
        return 1;
    }

    if (command == 0x24U) {
        advertised = ble_put_21_rd16(payload + 1);
        actual = ble_put_21_rd16(packet + 2);
        if (advertised != actual) {
            if (OP21_LOG_LEVEL < 1)
                return 1;
            if (OP21_IS_DEBUG != 0) {
                debug_print("%s(): teleprompter packet length error,input data length = %d,packet data length = %d\n",
                             "ble_process_put_req", (unsigned)actual,
                             (unsigned)advertised);
                return 1;
            }
            log_message("%s(): teleprompter packet length error,input data length = %d,packet data length = %d\n",
                        "ble_process_put_req", (unsigned)actual,
                        (unsigned)advertised);
            return 1;
        }
        if (payload[4] != 6U)
            return 1;
        if (OP21_LOG_LEVEL > 2) {
            if (OP21_IS_DEBUG == 0)
                log_message("%s(): received teleprompter suspend packet ....\n",
                            "ble_process_put_req");
            else
                debug_print();
        }
        *((uint8_t *)(void *)ctx - 0x6af) = payload[3];
        FUN_0007c1dc(payload[3], 0);
        tele = ctx->teleprompter;
        tele[0x10] = payload[5] == 1U ? 1U : 0U;
        *(uint32_t *)(void *)(tele + 2) =
            ble_put_21_rd32_explicit(payload + (uint32_t)advertised - 12U);
        *(uint32_t *)(void *)(tele + 6) =
            *(const uint32_t *)(const void *)(payload + (uint32_t)advertised - 8U);
        *(uint32_t *)(void *)(tele + 0x11) =
            ble_put_21_rd32_explicit(payload + (uint32_t)advertised - 4U);
        if (OP21_LOG_LEVEL > 2) {
            if (OP21_IS_DEBUG == 0)
                log_message("%s(): SUSPEND status ,app send counter time = %d\n",
                            "ble_process_put_req",
                            *(uint32_t *)(void *)(tele + 0x11));
            else
                debug_print();
        }
        ctx->frame_length = (uint32_t)ble_put_21_rd16(ctx->rx + 2) + 4U;
        memset_bytes(response + 6, 0, 14);
        *(uint32_t *)(void *)response = *(const uint32_t *)(const void *)payload;
        response[4] = payload[4]; response[5] = payload[5];
        if (get_device_type() == 1)
            send_response_data_to_msgqueue(response, 6);
        else {
            ret = ctx->post_to_host(response, 6);
            if (ret < 0 && OP21_LOG_LEVEL > 0) {
                if (OP21_IS_DEBUG == 0)
                    log_message("%s(): post_to_host failed ret = %d\n",
                                "ble_process_put_req", ret);
                else
                    debug_print();
            }
        }
        return 1;
    }

    if (command == 0x25U) {
        advertised = ble_put_21_rd16(payload + 1);
        actual = ble_put_21_rd16(packet + 2);
        if (advertised != actual) {
            if (OP21_LOG_LEVEL > 0) {
                if (OP21_IS_DEBUG == 0)
                    log_message("%s(): teleprompter packet length error,input data length = %d,packet data length = %d\n",
                                "ble_process_put_req");
                else
                    debug_print("%s(): teleprompter packet length error,input data length = %d,packet data length = %d\n",
                                 "ble_process_put_req");
            }
            return 1;
        }
        if (payload[4] == 4U) {
            if (OP21_LOG_LEVEL > 2) {
                if (OP21_IS_DEBUG == 0)
                    log_message("%s(): received app send sync packet ....\n",
                                "ble_process_put_req");
                else
                    debug_print();
            }
            OP25_SYNC_COUNT = OP25_SYNC_COUNT + 1U;
            ctx->frame_length = (uint32_t)ble_put_21_rd16(ctx->rx + 2) + 4U;
            memset_bytes(response + 6, 0, 14);
            *(uint32_t *)(void *)response = *(const uint32_t *)(const void *)payload;
            response[4] = payload[4]; response[5] = payload[5];
            ret = ctx->post_to_host(response, 6);
            if (ret < 0 && OP21_LOG_LEVEL > 0) {
                if (OP21_IS_DEBUG == 0)
                    log_message("%s(): post_to_host failed ret = %d\n",
                                "ble_process_put_req", ret);
                else
                    debug_print();
            }
        }
        return 1;
    }

    if (command == 0x26U) {
        subcommand = payload[4];
        response[0] = command; response[1] = 6; response[2] = 0;
        response[3] = payload[3]; response[4] = subcommand;
        actual = ble_put_21_rd16(packet + 2);
        advertised = ble_put_21_rd16(payload + 1);
        if (actual != advertised || subcommand >= 5U) {
            response[5] = 0xca;
            (void)ctx->post_to_host(response, 20);
            return 1;
        }
        response[5] = 0xc9;
        (void)ctx->post_to_host(response, 20);
        if (subcommand == 1U) {
            *((uint8_t *)(void *)ctx + 0x912) = 1;
        } else if (subcommand == 2U) {
            if (payload[6] < 9U && payload[7] < 10U) {
                uint32_t completion[2];
                *((uint8_t *)(void *)ctx - 0x6af) = payload[3];
                memcpy(ctx->rx + 4, payload, actual);
                audio_fw_load_get_wrapper(ctx, completion, 8);
            }
        } else if (subcommand == 3U) {
            if (is_battery_critical() == 1) {
                if (OP21_LOG_LEVEL > 2) {
                    if (OP21_IS_DEBUG == 0)
                        log_message("%s(): give mic_transm_sem\n",
                                    "ble_process_put_req");
                    else
                        debug_print();
                }
                process_sync_buffer(OP26_MIC_SEM);
            }
        } else if (subcommand == 4U) {
            uint8_t gear = payload[5];
            if (OP21_LOG_LEVEL > 1) {
                if (OP21_IS_DEBUG == 0)
                    log_message("%s(): ble set lum gear:%d\n",
                                "ble_process_put_req", (unsigned)gear);
                else
                    debug_print();
            }
            if (gear < 0x40U &&
                *(uint16_t *)(void *)((uint8_t *)(void *)ctx + 0x762) != gear) {
                *(uint16_t *)(void *)((uint8_t *)(void *)ctx + 0x762) = gear;
                *(uint16_t *)(void *)((uint8_t *)(void *)ctx + 0x75c) = gear;
                *(uint32_t *)(void *)((uint8_t *)(void *)ctx + 0x8d0) = packet[0];
                process_sync_buffer((uint8_t *)(void *)ctx - 0x6fc);
            }
        }
        return 1;
    }

    if (command == 0x27U) {
        *((uint8_t *)(void *)ctx + 0x911) = payload[1];
        *(uint32_t *)(void *)((uint8_t *)(void *)ctx + 0x8d0) = 0x27;
        process_sync_buffer((uint8_t *)(void *)ctx - 0x6fc);
        response[0] = command; response[1] = 0xc9;
        (void)ctx->post_to_host(response, 20);
        return 1;
    }
    return 0;
}

_Static_assert(offsetof(struct ble_put_context_21_27, post_to_host) == 0x0c,
               "post callback offset");
_Static_assert(offsetof(struct ble_put_context_21_27, rx) == 0x10,
               "rx offset");
_Static_assert(offsetof(struct ble_put_context_21_27, imu_state) == 0x870,
               "imu offset");
_Static_assert(offsetof(struct ble_put_context_21_27, teleprompter) == 0x880,
               "teleprompter offset");

#endif
