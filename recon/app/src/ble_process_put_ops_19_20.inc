/* Exact outer PUT handlers 0x19..0x20. Included by the dispatcher. */
#ifndef BLE_PROCESS_PUT_OPS_19_20_INC
#define BLE_PROCESS_PUT_OPS_19_20_INC

#include "ble_process_put_common.h"

extern int FUN_00023514();
extern int FUN_00024420();
extern int FUN_000244a8();
extern int FUN_0002efe4();
extern int FUN_0002f878();
extern int FUN_00042a64();
extern int FUN_00047bf8();
extern int FUN_00048840();
extern int thunk_FUN_00072880();
extern int FUN_00086fee();

#define OP19_NOTE_TOTAL  (*(volatile uint16_t *)(uintptr_t)0x2000d6f6)
#define OP19_NOTE_PACKET (*(volatile uint16_t *)(uintptr_t)0x2000d6f8)
#define OP19_NOTE_SIZE   (*(volatile uint16_t *)(uintptr_t)0x2000d6fa)
#define OP19_BAD_EXPECT  (*(volatile uint16_t *)(uintptr_t)0x2000d706)
#define OP19_NOTE_SLOT   (*(volatile uint8_t *)(uintptr_t)0x20010327)
#define OP19_NOTE_TEXT   ((uint8_t *)(uintptr_t)0x20010328)
#define OP19_NOTE_TITLE  ((uint8_t *)(uintptr_t)0x20010441)
#define OP20_PACKET_ID   (*(volatile uint8_t *)(uintptr_t)0x20002fe2)

BLE_PUT_ALWAYS_INLINE void
ble_put_ack10(struct ble_put_context *ctx, const uint8_t *request,
              uint8_t response[20], uint8_t status)
{
    *(uint32_t *)(void *)response = *(const uint32_t *)(const void *)request;
    *(uint32_t *)(void *)(response + 4) =
        *(const uint32_t *)(const void *)(request + 4);
    response[8] = request[8];
    response[9] = status;
    ctx->post_to_host(response, 10);
}

BLE_PUT_ALWAYS_INLINE void ble_put_note_reset(void)
{
    OP19_NOTE_TOTAL = 0;
    OP19_NOTE_PACKET = 0;
    OP19_NOTE_SIZE = 0;
    FUN_00086c78(OP19_NOTE_TEXT, 0, 0x119);
    FUN_00086c78(OP19_NOTE_TITLE, 0, 0x29);
}

BLE_PUT_ALWAYS_INLINE void
ble_put_op19_1a_1b_1d(struct ble_put_context *ctx, uint8_t response[20])
{
    if (BLE_LOG_LEVEL > 1) {
        if (BLE_IS_DEBUG == 0)
            DEBUG_PRINT("%s(): @tx error put req_type: %d\n", "ble_process_put_req");
        else
            FUN_00019c70();
    }
    response[1] = 0xca;
    response[2] = 0x15;
    FUN_00086fee(response + 2, "error put req.");
    ctx->post_to_host(response, 20);
}

BLE_PUT_ALWAYS_INLINE void
ble_put_op1c(struct ble_put_context *ctx, const uint8_t *request,
             uint8_t response[20])
{
    uint8_t *base = (uint8_t *)ctx;
    uint8_t *left = *(uint8_t **)(void *)(base + 0x888);
    uint8_t *right = *(uint8_t **)(void *)(base + 0x88c);
    if (request[2] != 0 && request[3] != 0) {
        left[0] = request[3]; left[1] = request[2];
        right[0] = request[3]; right[1] = request[2];
    }
    left[2] = request[1];
    right[2] = request[1];
    FUN_0002efe4(request[1]);
    if (BLE_LOG_LEVEL > 2) {
        if (BLE_IS_DEBUG == 0)
            DEBUG_PRINT("%s(): received start/Pause command,origin language type = %d,translate origin language type = %d,Suspend status = %d\n",
                        "ble_process_put_req", right[1], right[0], left[2]);
        else
            FUN_00019c70("%s(): received start/Pause command,origin language type = %d,translate origin language type = %d,Suspend status = %d\n");
    }
    response[1] = 0xc9;
    ctx->post_to_host(response, 20);
}

BLE_PUT_ALWAYS_INLINE void
ble_put_op1e_note(struct ble_put_context *ctx, const uint8_t *request,
                  uint16_t actual, uint8_t response[20])
{
    uint8_t *base = (uint8_t *)ctx;
    uint8_t *notes = *(uint8_t **)(void *)(base + 0x8a4);
    uint16_t total = ble_put_le16(request + 5);
    uint16_t seq = ble_put_le16(request + 7);
    uint32_t slot = request[9] & 0x0fu;
    uint32_t slot_index = slot - 1u;
    uint8_t *note = notes + slot_index * 0x143u;

    if (total == 1) {
        uint32_t title_length, title_copy, text_length, text_copy;
        FUN_00086c78(note + 4, 0, 0x29);
        FUN_00086c78(note + 0x2d, 0, 0x119);
        if ((int8_t)request[10] == 0) {
            note[3] = 0;
            if (BLE_LOG_LEVEL > 2) {
                if (BLE_IS_DEBUG == 0)
                    DEBUG_PRINT("%s(): received empty quick note data ,delete quick note num.%d\n",
                                "ble_process_put_req", slot);
                else FUN_00019c70();
            }
            ble_put_ack10(ctx, request, response, 0);
            FUN_000244a8(slot_index);
            return;
        }
        title_length = request[11];
        title_copy = title_length > 0x28u ? 0x29u : title_length;
        FUN_00086c04(note + 4, request + 12, title_copy);
        text_length = ble_put_le16(request + 12 + title_length);
        text_copy = text_length < 0x11au ? text_length : 0x119u;
        FUN_00086c04(note + 0x2d, request + 14 + title_length, text_copy);
        if (BLE_LOG_LEVEL > 2) {
            if (BLE_IS_DEBUG == 0)
                DEBUG_PRINT("%s(): title length = %d,text length = %d\n",
                            "ble_process_put_req", title_length, text_length);
            else FUN_00019c70("%s(): title length = %d,text length = %d\n",
                              "ble_process_put_req", title_length, text_length);
        }
        note[3] = 1;
        if (BLE_LOG_LEVEL > 2) {
            if (BLE_IS_DEBUG == 0)
                DEBUG_PRINT("%s(): Quick Note Title = %s,TXET = %s\n",
                            "ble_process_put_req", note + 4, note + 0x2d);
            else FUN_00019c70("%s(): Quick Note Title = %s,TXET = %s\n",
                              "ble_process_put_req");
        }
        FUN_00024420(slot_index);
        ble_put_ack10(ctx, request, response, 0);
        return;
    }

    if (seq == 1) {
        uint32_t title_length, title_copy, chunk, text_copy;
        FUN_00086c78(OP19_NOTE_TEXT, 0, 0x119);
        FUN_00086c78(OP19_NOTE_TITLE, 0, 0x29);
        OP19_NOTE_SIZE = 0;
        OP19_NOTE_SLOT = request[9];
        OP19_NOTE_PACKET = 0;
        OP19_NOTE_TOTAL = total;
        notes[((uint32_t)OP19_NOTE_SLOT - 1u) * 0x143u + 3] = 0;
        if (OP19_NOTE_SLOT < 5 && OP19_NOTE_SLOT != 0) {
            title_length = request[11];
            title_copy = title_length > 0x28u ? 0x29u : title_length;
            FUN_00086c04(OP19_NOTE_TITLE, request + 12, title_copy);
            chunk = (uint16_t)((uint32_t)actual - 14u - title_length);
            text_copy = chunk < 0x11au ? chunk : 0x119u;
            FUN_00086c04(OP19_NOTE_TEXT + OP19_NOTE_SIZE,
                          request + 14 + title_length, text_copy);
            OP19_NOTE_SIZE = (uint16_t)chunk;
            ++OP19_NOTE_PACKET;
            ble_put_ack10(ctx, request, response, 0);
        } else {
            if (BLE_LOG_LEVEL > 0) {
                if (BLE_IS_DEBUG == 0)
                    DEBUG_PRINT("%s(): app send parameter error,qucik note num = %d\n",
                                "ble_process_put_req", OP19_NOTE_SLOT);
                else FUN_00019c70("%s(): app send parameter error,qucik note num = %d\n",
                                  "ble_process_put_req", OP19_NOTE_SLOT);
            }
            ble_put_ack10(ctx, request, response, 1);
        }
        return;
    }

    if (seq < total) {
        if ((uint32_t)OP19_NOTE_PACKET == (uint32_t)seq - 1u) {
            FUN_00086c04(OP19_NOTE_TEXT + OP19_NOTE_SIZE, request + 9,
                          (uint16_t)(actual - 9u));
            OP19_NOTE_SIZE = (uint16_t)(OP19_NOTE_SIZE + actual - 9u);
            ++OP19_NOTE_PACKET;
            ble_put_ack10(ctx, request, response, 0);
        } else {
            if (BLE_LOG_LEVEL > 1) {
                if (BLE_IS_DEBUG == 0)
                    DEBUG_PRINT("%s(): ACTION ID = 3,There is a packet order error, current packet order = %d, expected packet order =%d\n",
                                "ble_process_put_req", seq, OP19_BAD_EXPECT + 1u);
                else FUN_00019c70("%s(): ACTION ID = 3,There is a packet order error, current packet order = %d, expected packet order =%d\n",
                                  "ble_process_put_req");
            }
            ble_put_note_reset();
            ble_put_ack10(ctx, request, response, 1);
        }
        return;
    }

    if (total == seq) {
        if ((uint32_t)OP19_NOTE_PACKET == (uint32_t)total - 1u &&
            OP19_NOTE_TOTAL == total) {
            uint8_t *destination = notes + ((uint32_t)OP19_NOTE_SLOT - 1u) * 0x143u;
            FUN_00086c04(OP19_NOTE_TEXT + OP19_NOTE_SIZE, request + 9,
                          (uint16_t)(actual - 9u));
            OP19_NOTE_SIZE = (uint16_t)(OP19_NOTE_SIZE + actual - 9u);
            FUN_00086c78(destination + 4, 0, 0x29);
            *(uint32_t *)(void *)(destination + 4) =
                *(const uint32_t *)(const void *)(OP19_NOTE_TITLE + 0);
            *(uint32_t *)(void *)(destination + 8) =
                *(const uint32_t *)(const void *)(OP19_NOTE_TITLE + 4);
            *(uint32_t *)(void *)(destination + 12) =
                *(const uint32_t *)(const void *)(OP19_NOTE_TITLE + 8);
            *(uint32_t *)(void *)(destination + 16) =
                *(const uint32_t *)(const void *)(OP19_NOTE_TITLE + 12);
            *(uint32_t *)(void *)(destination + 20) =
                *(const uint32_t *)(const void *)(OP19_NOTE_TITLE + 16);
            *(uint32_t *)(void *)(destination + 24) =
                *(const uint32_t *)(const void *)(OP19_NOTE_TITLE + 20);
            *(uint32_t *)(void *)(destination + 28) =
                *(const uint32_t *)(const void *)(OP19_NOTE_TITLE + 24);
            *(uint32_t *)(void *)(destination + 32) =
                *(const uint32_t *)(const void *)(OP19_NOTE_TITLE + 28);
            *(uint32_t *)(void *)(destination + 36) =
                *(const uint32_t *)(const void *)(OP19_NOTE_TITLE + 32);
            *(uint32_t *)(void *)(destination + 40) =
                *(const uint32_t *)(const void *)(OP19_NOTE_TITLE + 36);
            destination[44] = OP19_NOTE_TITLE[40];
            FUN_00086c78(destination + 0x2d, 0, 0x119);
            FUN_00086c04(destination + 0x2d, OP19_NOTE_TEXT, 0x119);
            destination[3] = 1;
            if (BLE_LOG_LEVEL > 2) {
                if (BLE_IS_DEBUG == 0)
                    DEBUG_PRINT("%s(): Quick Note Title =%s,QuickNote TXET =%s\n",
                                "ble_process_put_req", destination + 4,
                                destination + 0x2d);
                else FUN_00019c70("%s(): Quick Note Title =%s,QuickNote TXET =%s\n",
                                  "ble_process_put_req", destination + 4,
                                  destination + 0x2d);
            }
            FUN_00024420((uint32_t)OP19_NOTE_SLOT - 1u);
            ble_put_ack10(ctx, request, response, 0);
            OP19_NOTE_SIZE = 0;
            OP19_NOTE_PACKET = 0;
            OP19_NOTE_TOTAL = 0;
        } else {
            if (BLE_LOG_LEVEL > 1) {
                if (BLE_IS_DEBUG == 0)
                    DEBUG_PRINT("%s(): ACTION ID = 3,There is a packet order error, current packet order = %d, expected packet order =%d\n",
                                "ble_process_put_req", seq, OP19_BAD_EXPECT + 1u);
                else FUN_00019c70("%s(): ACTION ID = 3,There is a packet order error, current packet order = %d, expected packet order =%d\n",
                                  "ble_process_put_req");
            }
            FUN_00086c78(OP19_NOTE_TEXT, 0, 0x119);
            FUN_00086c78(OP19_NOTE_TITLE, 0, 0x29);
            OP19_NOTE_SIZE = 0;
            OP19_NOTE_PACKET = 0;
            OP19_NOTE_TOTAL = 0;
            ble_put_ack10(ctx, request, response, 1);
        }
    }
}

BLE_PUT_ALWAYS_INLINE void
ble_put_op1e(struct ble_put_context *ctx, const uint8_t *packet,
             const uint8_t *request, uint8_t response[20])
{
    uint16_t actual = ble_put_le16(request + 1);
    uint16_t advertised = ble_put_le16(packet + 2);
    if (actual != advertised) {
        if (BLE_LOG_LEVEL > 1) {
            if (BLE_IS_DEBUG == 0)
                DEBUG_PRINT("%s(): packet length error,input data length = %d,packet data length = %d\n",
                            "ble_process_put_req", advertised, actual);
            else FUN_00019c70("%s(): packet length error,input data length = %d,packet data length = %d\n",
                              "ble_process_put_req", advertised, actual);
        }
        return;
    }
    switch (request[4]) {
    case 1:
        if (FUN_00016568() == 1 && actual == 6 && request[5] == 1)
            FUN_00048840(0);
        break;
    case 2:
        if (FUN_00016568() == 1) {
            if (actual == 6) {
                if (BLE_LOG_LEVEL > 2) {
                    if (BLE_IS_DEBUG == 0)
                        DEBUG_PRINT("%s(): received request voice data commmand\n", "ble_process_put_req");
                    else FUN_00019c70();
                }
                FUN_00047bf8(0, request[5]);
            } else if (actual == 11) {
                if (request[10] == 0) {
                    if (BLE_LOG_LEVEL > 2) {
                        if (BLE_IS_DEBUG == 0)
                            DEBUG_PRINT("%s(): received request voice data next data\n", "ble_process_put_req");
                        else FUN_00019c70();
                    }
                } else if (request[10] == 0xaa) {
                    if (BLE_LOG_LEVEL > 2) {
                        if (BLE_IS_DEBUG == 0)
                            DEBUG_PRINT("%s(): APP success received audio data ,delete voice block num %d\n",
                                        "ble_process_put_req", request[9]);
                        else FUN_00019c70();
                    }
                    if (FUN_00016568() == 1) {
                        if ((uint8_t)(request[9] - 1u) < 4)
                            FUN_0002f878(request[9]);
                        else if (BLE_LOG_LEVEL > 1) {
                            if (BLE_IS_DEBUG == 0)
                                DEBUG_PRINT("%s(): APP delete voice block num error %d\n",
                                            "ble_process_put_req");
                            else FUN_00019c70();
                        }
                    }
                } else if (BLE_LOG_LEVEL > 0) {
                    if (BLE_IS_DEBUG == 0)
                        DEBUG_PRINT("%s(): app return error response information\n", "ble_process_put_req");
                    else FUN_00019c70();
                }
            }
        }
        break;
    case 3:
        ble_put_op1e_note(ctx, request, actual, response);
        break;
    case 4:
        if (request[5] < 5) {
            if (BLE_LOG_LEVEL > 2) {
                if (BLE_IS_DEBUG == 0)
                    DEBUG_PRINT("%s(): delete audio record num = %d\n",
                                "ble_process_put_req", request[5] - 1u);
                else FUN_00019c70();
            }
            if (FUN_00016568() == 1) FUN_0002f878(request[5]);
        } else {
            if (BLE_LOG_LEVEL > 2) {
                if (BLE_IS_DEBUG == 0)
                    DEBUG_PRINT("%s(): received delete all quick note audio file command .\n",
                                "ble_process_put_req");
                else FUN_00019c70();
            }
            if (FUN_00016568() == 1) FUN_0002f878(0xff);
        }
        *(uint32_t *)(void *)response = *(const uint32_t *)(const void *)request;
        response[4] = request[4]; response[5] = 0;
        ctx->post_to_host(response, 6);
        break;
    case 5:
        if (BLE_LOG_LEVEL > 2) {
            if (BLE_IS_DEBUG == 0)
                DEBUG_PRINT("%s(): received clean audio voice command\n", "ble_process_put_req");
            else FUN_00019c70();
        }
        if (FUN_00016568() == 1) {
            FUN_0002f878(0xff);
            *(uint32_t *)(void *)response = *(const uint32_t *)(const void *)request;
            response[4] = request[4]; response[5] = 0;
            ctx->post_to_host(response, 6);
        }
        break;
    default:
        break;
    }
}

BLE_PUT_ALWAYS_INLINE void
ble_put_op1f(struct ble_put_context *ctx, const uint8_t *packet,
             const uint8_t *request, uint8_t response[20])
{
    uint8_t *base = (uint8_t *)ctx;
    int length;
    int ret;
    if (BLE_LOG_LEVEL > 2) {
        if (BLE_IS_DEBUG == 0)
            DEBUG_PRINT("%s(): received onboarding init packet ....\n", "ble_process_put_req");
        else FUN_00019c70();
    }
    length = FUN_00042a64(base - 0x77c, packet, request, response);
    if (length > 0) {
        FUN_00086c04(ctx->transfer + 4, request, ble_put_le16(packet + 2));
        ret = ctx->post_to_host(response, (uint16_t)length);
        if (ret < 0 && BLE_LOG_LEVEL > 0) {
            if (BLE_IS_DEBUG == 0)
                DEBUG_PRINT("%s(): onboarding post_to_host failed ret = %d\n", "ble_process_put_req");
            else FUN_00019c70();
        }
    }
}

BLE_PUT_ALWAYS_INLINE void
ble_put_op20(struct ble_put_context *ctx, const uint8_t *packet,
             const uint8_t *request, uint8_t response[20])
{
    uint8_t *base = (uint8_t *)ctx;
    uint16_t length = ble_put_le16(packet + 2);
    if (length < 0x15 && request[1] == 0x0d && request[2] == 0x0e) {
        FUN_00023514(request + 1, (uint16_t)(length - 1u) & 0xffu);
        *(uint32_t *)(void *)(base + 0x8d0) = 0x20;
        thunk_FUN_00072880(base - 0x6fc);
        if (BLE_LOG_LEVEL > 0) {
            if (BLE_IS_DEBUG == 0)
                DEBUG_PRINT("%s(): recv upgrade font success\n", "ble_process_put_req");
            else FUN_00019c70();
        }
        response[1] = 0xc9;
        ctx->post_to_host(response, 20);
    } else {
        response[1] = 0xca;
        ctx->post_to_host(response, 20);
        if (BLE_LOG_LEVEL > 0) {
            if (BLE_IS_DEBUG == 0)
                DEBUG_PRINT("%s(): recv upgrade font failed\n", "ble_process_put_req");
            else FUN_00019c70();
        }
    }
    OP20_PACKET_ID = 0xff;
}

#endif
