#ifndef BLE_PROCESS_PUT_OPS_21_27_INC
#define BLE_PROCESS_PUT_OPS_21_27_INC

#include <stdint.h>
#include <stddef.h>

extern void DEBUG_PRINT(unsigned long, ...);
extern int FUN_00016568();
extern int FUN_00019b54(unsigned long, unsigned long, unsigned long);
extern void FUN_00019c70(unsigned long, ...);
extern int FUN_00032ee4();
extern int FUN_00037060();
extern int FUN_00047b1c();
extern int FUN_0007c1dc();
extern int FUN_00086c04();
extern int FUN_00086c78();
extern int FUN_00086fee();
extern int thunk_FUN_00072880();

#define OP21_LOG_LEVEL (*(volatile int32_t *)(uintptr_t)0x2000230c)
#define OP21_IS_DEBUG (*(volatile uint32_t *)(uintptr_t)0x20007554)
#define OP25_SYNC_COUNT (*(volatile uint32_t *)(uintptr_t)0x20007564)
#define OP26_MIC_SEM ((void *)(uintptr_t)0x20007bd4)

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
        FUN_00086fee(response + 2, (const void *)0x0009d4d5);
        (void)ctx->post_to_host(response, 20);
        return 1;
    }

    if (command == 0x22U) {
        advertised = ble_put_21_rd16(payload + 1);
        actual = ble_put_21_rd16(packet + 2);
        if (advertised != actual) {
            if (OP21_LOG_LEVEL > 0) {
                if (OP21_IS_DEBUG == 0)
                    DEBUG_PRINT(((unsigned long)"%s(): dashboard information packet length error,input data length = %d,packet data length = %d\n"),
                                "ble_process_put_req");
                else
                    FUN_00019c70(((unsigned long)"%s(): dashboard information packet length error,input data length = %d,packet data length = %d\n"),
                                 "ble_process_put_req");
            }
            return 1;
        }
        if (OP21_LOG_LEVEL > 2) {
            if (OP21_IS_DEBUG == 0)
                DEBUG_PRINT(((unsigned long)"%s(): received sync id = %d\n"),
                            "ble_process_put_req", (unsigned)payload[3]);
            else
                FUN_00019c70(((unsigned long)"%s(): received sync id = %d\n"),
                            "ble_process_put_req", (unsigned)payload[3]);
        }
        if (payload[4] == 1U) {
            for (unsigned i = 8; i != 20; ++i)
                response[i] = 0;
            *(uint32_t *)(void *)response = *(const uint32_t *)(const void *)payload;
            response[4] = payload[4];
            response[5] = *((uint8_t *)(void *)ctx - 0x69f);
            response[6] = (uint8_t)(FUN_00037060() + 1);
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
                FUN_00019c70(((unsigned long)"%s(): teleprompter packet length error,input data length = %d,packet data length = %d\n"),
                             "ble_process_put_req", (unsigned)actual,
                             (unsigned)advertised);
                return 1;
            }
            DEBUG_PRINT(((unsigned long)"%s(): teleprompter packet length error,input data length = %d,packet data length = %d\n"),
                        "ble_process_put_req", (unsigned)actual,
                        (unsigned)advertised);
            return 1;
        }
        if (payload[4] != 6U)
            return 1;
        if (OP21_LOG_LEVEL > 2) {
            if (OP21_IS_DEBUG == 0)
                DEBUG_PRINT(((unsigned long)"%s(): received teleprompter suspend packet ....\n"),
                            "ble_process_put_req");
            else
                FUN_00019c70(((unsigned long)"%s(): received teleprompter suspend packet ....\n"),
                            "ble_process_put_req");
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
                DEBUG_PRINT(((unsigned long)"%s(): SUSPEND status ,app send counter time = %d\n"),
                            "ble_process_put_req",
                            *(uint32_t *)(void *)(tele + 0x11));
            else
                FUN_00019c70(((unsigned long)"%s(): SUSPEND status ,app send counter time = %d\n"),
                            "ble_process_put_req",
                            *(uint32_t *)(void *)(tele + 0x11));
        }
        ctx->frame_length = (uint32_t)ble_put_21_rd16(ctx->rx + 2) + 4U;
        FUN_00086c78(response + 6, 0, 14);
        *(uint32_t *)(void *)response = *(const uint32_t *)(const void *)payload;
        response[4] = payload[4]; response[5] = payload[5];
        if (FUN_00016568() == 1)
            FUN_00047b1c(response, 6);
        else {
            ret = ctx->post_to_host(response, 6);
            if (ret < 0 && OP21_LOG_LEVEL > 0) {
                if (OP21_IS_DEBUG == 0)
                    DEBUG_PRINT(((unsigned long)"%s(): post_to_host failed ret = %d\n"),
                                "ble_process_put_req", ret);
                else
                    FUN_00019c70(((unsigned long)"%s(): post_to_host failed ret = %d\n"),
                                "ble_process_put_req", ret);
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
                    DEBUG_PRINT(((unsigned long)"%s(): teleprompter packet length error,input data length = %d,packet data length = %d\n"),
                                "ble_process_put_req");
                else
                    FUN_00019c70(((unsigned long)"%s(): teleprompter packet length error,input data length = %d,packet data length = %d\n"),
                                 "ble_process_put_req");
            }
            return 1;
        }
        if (payload[4] == 4U) {
            if (OP21_LOG_LEVEL > 2) {
                if (OP21_IS_DEBUG == 0)
                    DEBUG_PRINT(((unsigned long)"%s(): received app send sync packet ....\n"),
                                "ble_process_put_req");
                else
                    FUN_00019c70(((unsigned long)"%s(): received app send sync packet ....\n"),
                                "ble_process_put_req");
            }
            OP25_SYNC_COUNT = OP25_SYNC_COUNT + 1U;
            ctx->frame_length = (uint32_t)ble_put_21_rd16(ctx->rx + 2) + 4U;
            FUN_00086c78(response + 6, 0, 14);
            *(uint32_t *)(void *)response = *(const uint32_t *)(const void *)payload;
            response[4] = payload[4]; response[5] = payload[5];
            ret = ctx->post_to_host(response, 6);
            if (ret < 0 && OP21_LOG_LEVEL > 0) {
                if (OP21_IS_DEBUG == 0)
                    DEBUG_PRINT(((unsigned long)"%s(): post_to_host failed ret = %d\n"),
                                "ble_process_put_req", ret);
                else
                    FUN_00019c70(((unsigned long)"%s(): post_to_host failed ret = %d\n"),
                                "ble_process_put_req", ret);
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
                FUN_00086c04(ctx->rx + 4, payload, actual);
                FUN_00019b54(ctx, completion, 8);
            }
        } else if (subcommand == 3U) {
            if (FUN_00032ee4() == 1) {
                if (OP21_LOG_LEVEL > 2) {
                    if (OP21_IS_DEBUG == 0)
                        DEBUG_PRINT(((unsigned long)"%s(): give mic_transm_sem\n"),
                                    "ble_process_put_req");
                    else
                        FUN_00019c70(((unsigned long)"%s(): give mic_transm_sem\n"),
                                    "ble_process_put_req");
                }
                thunk_FUN_00072880(OP26_MIC_SEM);
            }
        } else if (subcommand == 4U) {
            uint8_t gear = payload[5];
            if (OP21_LOG_LEVEL > 1) {
                if (OP21_IS_DEBUG == 0)
                    DEBUG_PRINT(((unsigned long)"%s(): ble set lum gear:%d\n"),
                                "ble_process_put_req", (unsigned)gear);
                else
                    FUN_00019c70(((unsigned long)"%s(): ble set lum gear:%d\n"),
                                "ble_process_put_req", (unsigned)gear);
            }
            if (gear < 0x40U &&
                *(uint16_t *)(void *)((uint8_t *)(void *)ctx + 0x762) != gear) {
                *(uint16_t *)(void *)((uint8_t *)(void *)ctx + 0x762) = gear;
                *(uint16_t *)(void *)((uint8_t *)(void *)ctx + 0x75c) = gear;
                *(uint32_t *)(void *)((uint8_t *)(void *)ctx + 0x8d0) = packet[0];
                thunk_FUN_00072880((uint8_t *)(void *)ctx - 0x6fc);
            }
        }
        return 1;
    }

    if (command == 0x27U) {
        *((uint8_t *)(void *)ctx + 0x911) = payload[1];
        *(uint32_t *)(void *)((uint8_t *)(void *)ctx + 0x8d0) = 0x27;
        thunk_FUN_00072880((uint8_t *)(void *)ctx - 0x6fc);
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
