/* Included by the dispatcher: always_inline preserves original direct calls. */

BLE_PUT_ALWAYS_INLINE void ble_put_copy_ack(struct ble_put_context *ctx,
                                             const uint8_t *packet,
                                             const uint8_t *request,
                                             uint8_t response[20])
{
    uint32_t sync_state[2];
    uint16_t length = ble_put_le16(packet + 2);

    memcpy(ctx->transfer + 4, request + 1, (uint16_t)(length - 1));
    if (BLE_LOG_LEVEL > 2) {
        if (BLE_IS_DEBUG == 0) {
            log_message((const void *)0x0009b9bd, (const void *)0x0009e077,
                        ctx->transfer[4], ctx->transfer[5],
                        ctx->transfer[6], ctx->transfer[7]);
        } else {
            debug_print();
        }
    }
    audio_fw_load_get_wrapper(ctx, sync_state, 8);
    response[1] = 0xc9;
    ctx->post_to_host(response, 20);
}

BLE_PUT_ALWAYS_INLINE enum ble_put_handler_result
ble_put_op06_01_02(struct ble_put_context *ctx,
                   const uint8_t *packet,
                   const uint8_t *request,
                   uint8_t response[20])
{
    uint16_t request_length = ble_put_le16(request + 1);
    uint16_t packet_length = ble_put_le16(packet + 2);

    if (request_length != packet_length) {
        if (BLE_LOG_LEVEL > 0) {
            if (BLE_IS_DEBUG == 0)
                log_message((const void *)0x0009bafd,
                            (const void *)0x0009e077,
                            packet_length, request_length);
            else
                debug_print((const void *)0x0009bafd,
                             (const void *)0x0009e077,
                             packet_length, request_length);
        }
        /* Original zero begins at local_138+2 (message byte 6), leaving the
         * request header copied below and the explicit subop/status bytes. */
        memset_bytes(response + 6, 0, 14);
        *(uint32_t *)(void *)response = *(const uint32_t *)(const void *)request;
        response[4] = request[4];
        response[5] = 1;
        ctx->post_to_host(response, 20);
        return BLE_PUT_HANDLER_BREAK;
    }

    if (BLE_LOG_LEVEL > 2) {
        if (BLE_IS_DEBUG == 0)
            log_message((const void *)0x0009bb5d,
                        (const void *)0x0009e077, request[3]);
        else
            debug_print();
    }

    if (request[4] == 1) {
        uint8_t *config = *(uint8_t **)((uint8_t *)ctx + 0x870);
        uint32_t primary = ble_put_le32(request + 5);
        uint32_t left = ble_put_le32(request + 9);
        uint32_t right = ble_put_le32(request + 13);
        uint32_t axes[3] = {0, 0, 0};

        record_dashboard_startup_snapshot(left, right);
        if (BLE_LOG_LEVEL > 2) {
            if (BLE_IS_DEBUG == 0)
                log_message((const void *)0x0009bb7a,
                            (const void *)0x0009e077,
                            left, right, primary);
            else
                debug_print((const void *)0x0009bb7a,
                             (const void *)0x0009e077, left, right);
        }

        config[4] = request[17];
        config[5] = request[18];
        *(uint32_t *)(void *)config = primary;
        *(uint32_t *)(void *)(config + 6) = left;
        *(uint32_t *)(void *)(config + 10) = right;
        unix_timestamp_to_datetime(primary, axes);
        if (BLE_LOG_LEVEL > 2) {
            if (BLE_IS_DEBUG == 0)
                log_message((const void *)0x0009bbb9,
                            (const void *)0x0009e077, primary,
                            axes[0] & 0xffffu, axes[0] >> 16,
                            axes[1] & 0xffffu, axes[1] >> 16,
                            axes[2] & 0xffffu, axes[2] >> 16);
            else
                debug_print();
        }
        rate_limited_elapsed_seconds_tick(config, 0, 1);
        config[0x5d] = request[19];
        config[0x5e] = request[20];
        if (BLE_LOG_LEVEL > 2) {
            const void *word0 = (const void *)0x0009b9a8;
            const void *word1 = (const void *)0x0009b9ab;
            if (config[0x5e] != 0) {
                word0 = (const void *)0x0009b99a;
                word1 = (const void *)0x0009b99d;
            }
            if (BLE_IS_DEBUG == 0)
                log_message((const void *)0x0009bbe8,
                            (const void *)0x0009e077, word0, word1);
            else
                debug_print((const void *)0x0009bbe8,
                             (const void *)0x0009e077, word0, word1);
        }
        device_info_copy_record_fields();
        dashboard_startup_info_write_magic();
        memset_bytes(response + 5, 0, 15);
        *(uint32_t *)(void *)response = *(const uint32_t *)(const void *)request;
        response[4] = request[4];
        ctx->post_to_host(response, 6);
    } else if (request[4] == 2) {
        memset_bytes(response + 5, 0, 15);
        *(uint32_t *)(void *)response = *(const uint32_t *)(const void *)request;
        response[4] = request[4];
        ctx->post_to_host(response, 6);
    } else if (request[4] == 6) {
        uint8_t *config = *(uint8_t **)((uint8_t *)ctx + 0x870);
        config[0x64] = request[5];
        config[0x65] = request[6];
        if (BLE_LOG_LEVEL > 2) {
            if (BLE_IS_DEBUG == 0)
                log_message((const void *)0x0009bc2d,
                            (const void *)0x0009e077,
                            config[0x64], config[0x65]);
            else
                debug_print((const void *)0x0009bc2d,
                             (const void *)0x0009e077);
        }
        device_info_copy_record_fields();
        dashboard_startup_info_write_magic();
        memset_bytes(response + 5, 0, 15);
        *(uint32_t *)(void *)response = *(const uint32_t *)(const void *)request;
        response[4] = request[4];
        ctx->post_to_host(response, 6);
    } else {
        /* Subops 3..5 are deliberately owned by their separate reviewed
         * handlers; report that fact without performing any substitute work. */
        return BLE_PUT_HANDLER_UNHANDLED;
    }
    return BLE_PUT_HANDLER_BREAK;
}

BLE_PUT_ALWAYS_INLINE enum ble_put_handler_result
ble_put_op06_03(struct ble_put_context *ctx,
                const uint8_t *request,
                uint8_t response[20])
{
    volatile uint16_t *const assembled_length =
        (volatile uint16_t *)(uintptr_t)0x2000d6fa;
    volatile uint8_t *const assembled_slot =
        (volatile uint8_t *)(uintptr_t)0x20010327;
    volatile uint16_t *const packet_index =
        (volatile uint16_t *)(uintptr_t)0x2000d6f8;
    volatile uint16_t *const packet_count =
        (volatile uint16_t *)(uintptr_t)0x2000d6f6;
    uint8_t *const assembled_text = (uint8_t *)(uintptr_t)0x20010328;
    uint8_t *const assembled_title = (uint8_t *)(uintptr_t)0x20010441;
    uint8_t *const notes =
        *(uint8_t **)((uint8_t *)ctx + 0x8a4);
    uint16_t total = ble_put_le16(request + 5);
    uint32_t current = ble_put_le16(request + 7);
    uint32_t request_length = ble_put_le16(request + 1);

#define BLE_PUT_NOTE_ACK(status_) do {                                      \
        *(uint32_t *)(void *)response =                                    \
            *(const uint32_t *)(const void *)request;                       \
        *(uint32_t *)(void *)(response + 4) =                              \
            *(const uint32_t *)(const void *)(request + 4);                 \
        response[8] = request[8];                                           \
        response[9] = (uint8_t)(status_);                                   \
        ctx->post_to_host(response, 10);                                    \
    } while (0)

    if (total == 1) {
        uint8_t *config;
        config = *(uint8_t **)(uintptr_t)(get_device_info() + 0xfec);
        config[0x64] = request[9];
        config = *(uint8_t **)(uintptr_t)(get_device_info() + 0xfec);
        config[0x65] = request[10];
        config = *(uint8_t **)(uintptr_t)(get_device_info() + 0xfec);
        config[0x66] = request[11];
        config = *(uint8_t **)(uintptr_t)(get_device_info() + 0xfec);
        if (config[0x66] != 3) {
            *(uint32_t *)(void *)response = *(const uint32_t *)(const void *)request;
            *(uint32_t *)(void *)(response + 4) =
                *(const uint32_t *)(const void *)(request + 4);
            response[8] = request[8];
            for (unsigned i = 9; i < 20; ++i)
                response[i] = 0;
            if (ctx->post_to_host(response, 10) >= 0)
                return BLE_PUT_HANDLER_RETURN;
        }
    } else if (current == 1) {
        volatile uint16_t *length = (volatile uint16_t *)(uintptr_t)0x2000f6de;
        volatile uint16_t *expected = (volatile uint16_t *)(uintptr_t)0x2000f6e0;
        volatile uint16_t *accepted = (volatile uint16_t *)(uintptr_t)0x2000f6e2;
        uint8_t *assembled = (uint8_t *)(uintptr_t)0x20011559;
        *accepted = 0; *expected = 0; *length = 0;
        memset_bytes(assembled, 0, 0x420);
        safe_memcpy_checked(assembled, request + 9, request_length - 9u, 0x420);
        *length = (uint16_t)(request_length - 9u);
        *accepted = 1; *expected = (uint16_t)total;
        BLE_PUT_NOTE_ACK(0);
    } else if (current < total) {
        volatile uint16_t *length = (volatile uint16_t *)(uintptr_t)0x2000f6de;
        volatile uint16_t *expected = (volatile uint16_t *)(uintptr_t)0x2000f6e0;
        volatile uint16_t *accepted = (volatile uint16_t *)(uintptr_t)0x2000f6e2;
        uint8_t *assembled = (uint8_t *)(uintptr_t)0x20011559;
        if ((uint32_t)*accepted == current - 1u) {
            memcpy(assembled + *length, request + 9, request_length - 9u);
            *length = (uint16_t)(*length + request_length - 9u);
            *accepted = (uint16_t)(*accepted + 1u);
            BLE_PUT_NOTE_ACK(0);
        } else {
            *expected = 0; *accepted = 0;
            memset_bytes(assembled, 0, 0x420);
            BLE_PUT_NOTE_ACK(1);
        }
    } else if (current == total) {
        volatile uint16_t *length = (volatile uint16_t *)(uintptr_t)0x2000f6de;
        volatile uint16_t *expected = (volatile uint16_t *)(uintptr_t)0x2000f6e0;
        volatile uint16_t *accepted = (volatile uint16_t *)(uintptr_t)0x2000f6e2;
        uint8_t *assembled = (uint8_t *)(uintptr_t)0x20011559;
        if ((uint32_t)*accepted == current - 1u && *expected == current) {
            uint8_t *config;
            memcpy(assembled + *length, request + 9, request_length - 9u);
            *length = (uint16_t)(*length + request_length - 9u);
            *accepted = (uint16_t)(*accepted + 1u);
            config = *(uint8_t **)(uintptr_t)(get_device_info() + 0xfec);
            config[0x64] = assembled[0];
            config = *(uint8_t **)(uintptr_t)(get_device_info() + 0xfec);
            config[0x65] = assembled[1];
            config = *(uint8_t **)(uintptr_t)(get_device_info() + 0xfec);
            config[0x66] = assembled[2];
            (void)get_device_info();
            BLE_PUT_NOTE_ACK(0);
        } else {
            *expected = 0; *accepted = 0;
            memset_bytes(assembled, 0, 0x420);
            BLE_PUT_NOTE_ACK(1);
        }
    } else if (current == 1) {
        uint32_t title_length;
        uint32_t title_copy;
        uint16_t remaining;
        uint32_t text_copy;

        memset_bytes(assembled_text, 0, 0x119);
        *assembled_length = 0;
        *assembled_slot = request[9];
        *packet_index = 0;
        *packet_count = total;
        notes[((uint32_t)(*assembled_slot) - 1u) * 0x143u + 3u] = 0;
        if (*assembled_slot < 5 && *assembled_slot != 0) {
            title_length = request[11];
            title_copy = title_length > 0x28u ? 0x29u : title_length;
            safe_memcpy_checked(assembled_title, request + 12, title_copy, 0x29);
            remaining = (uint16_t)(request_length - 14u - title_length);
            text_copy = remaining < 0x11au ? remaining : 0x119u;
            memcpy(assembled_text, request + title_length + 14, text_copy);
            *assembled_length = remaining;
            *packet_index = (uint16_t)(*packet_index + 1u);
            BLE_PUT_NOTE_ACK(0);
        } else {
            if (BLE_LOG_LEVEL > 0) {
                if (BLE_IS_DEBUG == 0)
                    log_message((const void *)0x0009bd38,
                                (const void *)0x0009e077,
                                (uint32_t)*assembled_slot);
                else
                    debug_print((const void *)0x0009bd38,
                                 (const void *)0x0009e077,
                                 (uint32_t)*assembled_slot);
            }
            BLE_PUT_NOTE_ACK(1);
        }
    } else if (current < total) {
        if ((uint32_t)*packet_index == current - 1u) {
            uint16_t chunk_length = (uint16_t)(request_length - 9u);
            memcpy(assembled_text + *assembled_length,
                         request + 9, chunk_length);
            *assembled_length = (uint16_t)(*assembled_length + chunk_length);
            *packet_index = (uint16_t)(*packet_index + 1u);
            BLE_PUT_NOTE_ACK(0);
        } else {
            if (BLE_LOG_LEVEL > 1) {
                if (BLE_IS_DEBUG == 0)
                    log_message((const void *)0x0009b967,
                                (const void *)0x0009e077, current,
                                (uint32_t)*(volatile uint16_t *)(uintptr_t)0x2000d706 + 1u);
                else
                    debug_print((const void *)0x0009b967,
                                 (const void *)0x0009e077);
            }
            *packet_count = 0;
            *packet_index = 0;
            *assembled_length = 0;
            memset_bytes(assembled_text, 0, 0x119);
            memset_bytes(assembled_title, 0, 0x29);
            BLE_PUT_NOTE_ACK(1);
        }
    } else if (current == total) {
        if ((uint32_t)*packet_index == current - 1u && *packet_count == current) {
            uint16_t chunk_length = (uint16_t)(request_length - 9u);
            uint8_t *note;

            memcpy(assembled_text + *assembled_length,
                         request + 9, chunk_length);
            *assembled_length = (uint16_t)(*assembled_length + chunk_length);
            note = notes + ((uint32_t)(*assembled_slot) - 1u) * 0x143u;
            memset_bytes(note + 4, 0, 0x29);
            {
                uint32_t *dst = (uint32_t *)(void *)(note + 4);
                const uint32_t *src =
                    (const uint32_t *)(const void *)assembled_title;
                do {
                    *dst++ = *src++;
                } while ((uintptr_t)src != 0x20010469u);
                *(uint8_t *)(void *)dst = *(const uint8_t *)(uintptr_t)0x20010469;
            }
            memset_bytes(note + 0x2d, 0, 0x119);
            memcpy(note + 0x2d, assembled_text, 0x119);
            note[3] = 1;
            if (BLE_LOG_LEVEL > 2) {
                if (BLE_IS_DEBUG == 0)
                    log_message((const void *)0x0009bd6c,
                                (const void *)0x0009e077,
                                note + 4, note + 0x2d);
                else
                    debug_print((const void *)0x0009bd6c,
                                 (const void *)0x0009e077,
                                 note + 4, note + 0x2d);
            }
            upgradeQuickNoteDataToFlash((uint32_t)(*assembled_slot) - 1u);
            BLE_PUT_NOTE_ACK(0);
            *assembled_length = 0;
            *packet_index = 0;
            *packet_count = 0;
        } else {
            if (BLE_LOG_LEVEL > 1) {
                if (BLE_IS_DEBUG == 0)
                    log_message((const void *)0x0009b967,
                                (const void *)0x0009e077, current,
                                (uint32_t)*(volatile uint16_t *)(uintptr_t)0x2000d706 + 1u);
                else
                    debug_print((const void *)0x0009b967,
                                 (const void *)0x0009e077);
            }
            memset_bytes(assembled_text, 0, 0x119);
            memset_bytes(assembled_title, 0, 0x29);
            *assembled_length = 0;
            *packet_index = 0;
            *packet_count = 0;
            BLE_PUT_NOTE_ACK(1);
        }
    }
#undef BLE_PUT_NOTE_ACK
    return BLE_PUT_HANDLER_BREAK;
}

BLE_PUT_ALWAYS_INLINE void ble_put_op07(struct ble_put_context *ctx,
                                         const uint8_t *request,
                                         uint8_t response[20])
{
    uint32_t sync_state[2];
    if (BLE_LOG_LEVEL > 2) {
        if (BLE_IS_DEBUG == 0)
            log_message((const void *)0x0009ba85, (const void *)0x0009e077);
        else
            debug_print();
    }
    *(uint32_t *)(void *)(ctx->transfer + 4) =
        *(const uint32_t *)(const void *)(request + 1);
    ctx->transfer[8] = request[5];
    *(uint16_t *)(void *)(ctx->transfer + 2) = 5;
    ctx->transfer_length = 9;
    if (BLE_LOG_LEVEL > 2) {
        if (BLE_IS_DEBUG == 0)
            log_message((const void *)0x0009baaa, (const void *)0x0009e077,
                        *(uint32_t *)(ctx->transfer + 4), ctx->transfer[8]);
        else
            debug_print((const void *)0x0009baaa, (const void *)0x0009e077);
        if (BLE_LOG_LEVEL > 2) {
            if (BLE_IS_DEBUG == 0)
                log_message((const void *)0x0009bad3, (const void *)0x0009e077,
                            ctx->transfer[4], ctx->transfer[5],
                            ctx->transfer[6], ctx->transfer[7], ctx->transfer[8]);
            else
                debug_print();
        }
    }
    audio_fw_load_get_wrapper(ctx, sync_state, 8);
    response[1] = 0xc9;
    ctx->post_to_host(response, 20);
}

BLE_PUT_ALWAYS_INLINE void ble_put_op08(struct ble_put_context *ctx,
                                         const uint8_t *packet,
                                         const uint8_t *request,
                                         uint8_t response[20])
{
    uint16_t actual = ble_put_le16(request + 1);
    uint16_t advertised = ble_put_le16(packet + 2);
    if (actual != advertised) {
        if (BLE_LOG_LEVEL > 1) {
            if (BLE_IS_DEBUG == 0)
                log_message((const void *)((unsigned long)&rodata_9b8fd) /*=0x9b8fd*/, (const void *)0x0009e077,
                            advertised, actual);
            else
                debug_print((const void *)((unsigned long)&rodata_9b8fd) /*=0x9b8fd*/, (const void *)0x0009e077,
                             advertised, actual);
        }
        return;
    }
    if (BLE_LOG_LEVEL > 2) {
        if (BLE_IS_DEBUG == 0)
            log_message((const void *)0x0009ba29, (const void *)0x0009e077);
        else
            debug_print();
    }
    if (request[4] == 3) {
        if (request[5] < 3) {
            if (get_device_type() == 1) {
                BLE_LUMINANCE_SOURCE = request[3];
                SendDashBoardStartupModeInfoToSlave(request[5]);
            } else {
                memset_bytes(response, 0, 20);
                safe_memcpy_checked(response, request, actual, 20);
                ctx->post_to_host(response, actual);
            }
        } else if (BLE_LOG_LEVEL > 0) {
            if (BLE_IS_DEBUG == 0)
                log_message((const void *)0x0009ba52, (const void *)0x0009e077);
            else
                debug_print();
        }
    } else if (request[4] == 4) {
        memset_bytes(response, 0, 20);
        safe_memcpy_checked(response, request, actual, 20);
        response[5] = (uint8_t)get_ui_mode_flag2();
        ctx->post_to_host(response, actual);
    }
}

/* Opcode 6/subop 4, total-packets == 1 only.  The multipart state machine is
 * intentionally outside this helper. */
BLE_PUT_ALWAYS_INLINE enum ble_put_handler_result
ble_put_op06_04_single(struct ble_put_context *ctx,
                       const uint8_t *request,
                       uint8_t response[20])
{
    uint8_t *config;
    uint8_t *record;
    uint32_t slot;
    uint32_t code_len, company_len, price_len, change_len, rate_len;
    uint32_t p;
    uint16_t image_len;
    int ret;

#define BLE_STOCK_REPLY(status_) do {                                      \
        *(uint32_t *)(void *)response =                                    \
            *(const uint32_t *)(const void *)request;                       \
        *(uint32_t *)(void *)(response + 4) =                              \
            *(const uint32_t *)(const void *)(request + 4);                 \
        response[8] = request[8];                                           \
        response[9] = (uint8_t)(status_);                                   \
        ret = ctx->post_to_host(response, 10);                              \
        if (ret < 0 && BLE_LOG_LEVEL > 0) {                                \
            if (BLE_IS_DEBUG == 0)                                         \
                log_message("%s(): post_to_host failed ret = %d\n",       \
                            "ble_process_put_req", ret);                   \
            else                                                            \
                debug_print();                                             \
        }                                                                   \
    } while (0)
#define BLE_STOCK_REJECT(message_) do {                                    \
        if (BLE_LOG_LEVEL > 0) {                                           \
            if (BLE_IS_DEBUG == 0)                                         \
                log_message((message_), "ble_process_put_req");            \
            else                                                            \
                debug_print();                                             \
        }                                                                   \
        BLE_STOCK_REPLY(1);                                                 \
        return BLE_PUT_HANDLER_RETURN;                                      \
    } while (0)
#define BLE_STOCK_OVERSIZE(message_) do {                                  \
        if (BLE_LOG_LEVEL > 1) {                                           \
            if (BLE_IS_DEBUG == 0)                                         \
                log_message((message_), "ble_process_put_req");            \
            else                                                            \
                debug_print();                                             \
        }                                                                   \
        BLE_STOCK_REPLY(1);                                                 \
    } while (0)

    if (ble_put_le16(request + 5) != 1)
        return BLE_PUT_HANDLER_UNHANDLED;

    config = *(uint8_t **)(uintptr_t)(get_device_info() + 0xfec);
    config[0x64] = request[9];
    config = *(uint8_t **)(uintptr_t)(get_device_info() + 0xfec);
    config[0x65] = request[10];
    config = *(uint8_t **)(uintptr_t)(get_device_info() + 0xfec);
    config[0x68] = request[11];
    if (BLE_LOG_LEVEL > 2) {
        if (BLE_IS_DEBUG == 0) {
            uint8_t *shown = *(uint8_t **)((uint8_t *)ctx + 0x870);
            log_message("%s(): Dashboard display mode :%d  custom display Area value : %d\n",
                        "ble_process_put_req", shown[0x64], shown[0x65]);
        } else {
            debug_print("%s(): Dashboard display mode :%d  custom display Area value : %d\n",
                         "ble_process_put_req");
        }
        if (BLE_LOG_LEVEL > 2) {
            config = *(uint8_t **)(uintptr_t)(get_device_info() + 0xfec);
            if (BLE_IS_DEBUG == 0)
                log_message("%s(): stocks display mode = %d\n",
                            "ble_process_put_req", config[0x68]);
            else {
                config = *(uint8_t **)(uintptr_t)(get_device_info() + 0xfec);
                debug_print("%s(): stocks display mode = %d\n",
                             "ble_process_put_req", config[0x68]);
            }
        }
    }

    config = *(uint8_t **)(uintptr_t)(get_device_info() + 0xfec);
    if ((int8_t)config[0x68] != 2) {
        BLE_STOCK_REPLY(0);
        return BLE_PUT_HANDLER_BREAK;
    }
    slot = request[12];
    if (slot >= 5) {
        if (BLE_LOG_LEVEL > 0) {
            if (BLE_IS_DEBUG == 0)
                log_message("%s(): stocks data oversize!!!!\n",
                            "ble_process_put_req");
            else
                debug_print();
        }
        BLE_STOCK_REPLY(1);
        return BLE_PUT_HANDLER_BREAK;
    }
    if (BLE_LOG_LEVEL > 2) {
        if (BLE_IS_DEBUG == 0)
            log_message("%s(): current stocks index num = %d\n",
                        "ble_process_put_req", slot);
        else
            debug_print();
    }
    record = (uint8_t *)(uintptr_t)(((unsigned long)&g_2000d716) /*=0x2000d716*/ + (slot - 1u) * 0x7f2u);
    if ((int8_t)request[13] == 2) {
        if (BLE_LOG_LEVEL > 2) {
            if (BLE_IS_DEBUG == 0)
                log_message("%s(): delete stocks index num = %d\n",
                            "ble_process_put_req", slot);
            else
                debug_print();
        }
        memset_bytes(record, 0);
        cleanStocksIndex();
        BLE_STOCK_REPLY(0);
        return BLE_PUT_HANDLER_BREAK;
    }
    if ((int8_t)request[14] != 1)
        BLE_STOCK_REJECT("%s(): stock code data struct error, error type = %d\n");
    code_len = request[15];
    if (code_len > 0x20)
        BLE_STOCK_OVERSIZE("%s(): stocks code oversize !!!\n");
    if (memcmp(record + 4, request + 16,
                     code_len > 0x1f ? 0x20 : code_len) != 0) {
        memset_bytes(record + 4, 0, 0x20);
        cleanStocksIndex();
    }
    memcpy(record + 4, request + 16,
                 code_len > 0x1f ? 0x20 : code_len);
    p = code_len + 16;
    if ((int8_t)request[p] != 2)
        BLE_STOCK_REJECT("%s(): stocks company name data struct error, error type = %d\n");
    company_len = request[p + 1];
    if (company_len > 0x40)
        BLE_STOCK_OVERSIZE("%s(): stocks share price oversize !!!\n");
    if (memcmp(record + 0x24, request + p + 2,
                     company_len > 0x3f ? 0x40 : company_len) != 0) {
        memset_bytes(record + 0x24, 0, 0x40);
        cleanStocksIndex();
    }
    memcpy(record + 0x24, request + p + 2,
                 company_len > 0x3f ? 0x40 : company_len);
    p += company_len + 2;
    if ((int8_t)request[p] != 3)
        BLE_STOCK_REJECT("%s(): stocks share price data struct error, error type = %d\n");
    price_len = request[p + 1];
    if (price_len > 0x10)
        BLE_STOCK_OVERSIZE("%s(): stocks share price oversize !!!\n");
    memset_bytes(record + 0x64, 0, 0x10);
    memcpy(record + 0x64, request + p + 2,
                 price_len > 0x0f ? 0x10 : price_len);
    p += price_len + 2;
    if ((int8_t)request[p] != 4)
        BLE_STOCK_REJECT("%s(): stocks price change data struct error, error type = %d\n");
    change_len = request[p + 1];
    if (change_len > 0x10)
        BLE_STOCK_OVERSIZE("%s(): stocks price change oversize !!!\n");
    memset_bytes(record + 0x74, 0, 0x10);
    memcpy(record + 0x74, request + p + 2,
                 change_len > 0x0f ? 0x10 : change_len);
    p += change_len + 2;
    if ((int8_t)request[p] != 5)
        BLE_STOCK_REJECT("%s(): stocks change rate data struct error, error type = %d\n");
    rate_len = request[p + 1];
    if (rate_len > 0x10)
        BLE_STOCK_OVERSIZE("%s(): stocks price change oversize !!!\n");
    memset_bytes(record + 0x84, 0, 0x10);
    memcpy(record + 0x84, request + p + 2,
                 rate_len > 0x0f ? 0x10 : rate_len);
    p += rate_len + 2;
    if ((int8_t)request[p] != 6)
        BLE_STOCK_REJECT("%s(): stocks change rate data struct error, error type = %d\n");
    if ((int8_t)request[p + 1] != 1)
        BLE_STOCK_REJECT("%s(): stocks change status sformat error !!!\n");
    record[1] = request[p + 2];
    p += request[p + 1] + 2;
    if ((int8_t)request[p] != 7)
        BLE_STOCK_REJECT("%s(): stocks change rate data struct error, error type = %d\n");
    image_len = ble_put_le16(request + p + 1);
    if (image_len > 0x75e)
        BLE_STOCK_REJECT("%s(): stocks image format oversize !!!\n");
    *(uint16_t *)(void *)(record + 2) = image_len;
    memset_bytes(record + 0x94, 0);
    memcpy(record + 0x94, request + p + 3, image_len);
    record[0] = 1;
    BLE_STOCK_REPLY(0);
#undef BLE_STOCK_OVERSIZE
#undef BLE_STOCK_REJECT
#undef BLE_STOCK_REPLY
    return BLE_PUT_HANDLER_BREAK;
}

/* Parse the completed multipart stock payload at 0x20010d47.  Its byte zero
 * is the dashboard mode (the single-packet request's byte 9). */
BLE_PUT_ALWAYS_INLINE enum ble_put_handler_result
ble_put_op06_04_assembled(struct ble_put_context *ctx,
                          const uint8_t *request,
                          uint8_t response[20])
{
    uint8_t *const data = (uint8_t *)(uintptr_t)0x20010d47;
    volatile uint16_t *const expected_total =
        (volatile uint16_t *)(uintptr_t)0x2000d712;
    volatile uint16_t *const accepted_count =
        (volatile uint16_t *)(uintptr_t)0x2000d714;
    uint8_t *config;
    uint8_t *record;
    uint32_t slot, p, n;
    uint16_t image_len;
    int ret;

#define BLE_STOCK_FINAL_ACK(status_) do {                                  \
        *(uint32_t *)(void *)response =                                    \
            *(const uint32_t *)(const void *)request;                       \
        *(uint32_t *)(void *)(response + 4) =                              \
            *(const uint32_t *)(const void *)(request + 4);                 \
        response[8] = request[8];                                           \
        response[9] = (uint8_t)(status_);                                   \
        ret = ctx->post_to_host(response, 10);                              \
        if (ret < 0 && BLE_LOG_LEVEL > 0) {                                \
            if (BLE_IS_DEBUG == 0)                                         \
                log_message("%s(): post_to_host failed ret = %d\n",       \
                            "ble_process_put_req", ret);                   \
            else                                                            \
                debug_print();                                             \
        }                                                                   \
    } while (0)
#define BLE_STOCK_FINAL_BAD(message_) do {                                 \
        if (BLE_LOG_LEVEL > 0) {                                           \
            if (BLE_IS_DEBUG == 0)                                         \
                log_message((message_), "ble_process_put_req");           \
            else                                                            \
                debug_print();                                             \
        }                                                                   \
        BLE_STOCK_FINAL_ACK(1);                                             \
        return BLE_PUT_HANDLER_RETURN;                                      \
    } while (0)
#define BLE_STOCK_FINAL_LARGE(message_) do {                               \
        if (BLE_LOG_LEVEL > 1) {                                           \
            if (BLE_IS_DEBUG == 0)                                         \
                log_message((message_), "ble_process_put_req");           \
            else                                                            \
                debug_print();                                             \
        }                                                                   \
        BLE_STOCK_FINAL_ACK(1);                                             \
    } while (0)

    config = *(uint8_t **)(uintptr_t)(get_device_info() + 0xfec);
    config[0x64] = data[0];
    config = *(uint8_t **)(uintptr_t)(get_device_info() + 0xfec);
    config[0x65] = data[1];
    config = *(uint8_t **)(uintptr_t)(get_device_info() + 0xfec);
    config[0x68] = data[2];
    if (BLE_LOG_LEVEL > 2) {
        if (BLE_IS_DEBUG == 0) {
            uint8_t *shown = *(uint8_t **)((uint8_t *)ctx + 0x870);
            log_message("%s(): Dashboard display mode :%d  custom display Area value : %d\n",
                        "ble_process_put_req", shown[0x64], shown[0x65]);
        } else
            debug_print("%s(): Dashboard display mode :%d  custom display Area value : %d\n",
                         "ble_process_put_req");
        if (BLE_LOG_LEVEL > 2) {
            config = *(uint8_t **)(uintptr_t)(get_device_info() + 0xfec);
            if (BLE_IS_DEBUG == 0)
                log_message("%s(): stocks display mode = %d\n",
                            "ble_process_put_req", config[0x68]);
            else {
                config = *(uint8_t **)(uintptr_t)(get_device_info() + 0xfec);
                debug_print("%s(): stocks display mode = %d\n",
                             "ble_process_put_req", config[0x68]);
            }
        }
    }
    config = *(uint8_t **)(uintptr_t)(get_device_info() + 0xfec);
    if ((int8_t)config[0x68] != 2) {
        BLE_STOCK_FINAL_ACK(0);
        return BLE_PUT_HANDLER_BREAK;
    }

    slot = data[3];
    if (slot >= 5) {
        if (BLE_LOG_LEVEL > 0) {
            if (BLE_IS_DEBUG == 0)
                log_message("%s(): stocks data oversize!!!!\n", "ble_process_put_req");
            else debug_print();
        }
        BLE_STOCK_FINAL_ACK(1);
        return BLE_PUT_HANDLER_BREAK;
    }
    if (BLE_LOG_LEVEL > 2) {
        if (BLE_IS_DEBUG == 0)
            log_message("%s(): current stocks index num = %d\n",
                        "ble_process_put_req", slot);
        else debug_print();
    }
    record = (uint8_t *)(uintptr_t)(((unsigned long)&g_2000d716) /*=0x2000d716*/ + (slot - 1u) * 0x7f2u);
    if ((int8_t)data[4] == 2) {
        if (BLE_LOG_LEVEL > 2) {
            if (BLE_IS_DEBUG == 0)
                log_message("%s(): delete stocks index num = %d\n",
                            "ble_process_put_req", slot);
            else debug_print();
        }
        cleanStocksIndex();
        memset_bytes(record, 0);
        BLE_STOCK_FINAL_ACK(0);
        return BLE_PUT_HANDLER_BREAK;
    }
    if ((int8_t)data[5] != 1)
        BLE_STOCK_FINAL_BAD("%s(): stock code data struct error, error type = %d\n");
    n = data[6];
    if (n > 0x20) BLE_STOCK_FINAL_LARGE("%s(): stocks code oversize !!!\n");
    if (memcmp(record + 4, data + 7, n > 0x1f ? 0x20 : n) != 0) {
        memset_bytes(record + 4, 0, 0x20); cleanStocksIndex();
    }
    memcpy(record + 4, data + 7, n > 0x1f ? 0x20 : n);
    p = n + 7;
    if ((int8_t)data[p] != 2)
        BLE_STOCK_FINAL_BAD("%s(): stocks company name data struct error, error type = %d\n");
    n = data[p + 1];
    if (n > 0x40) BLE_STOCK_FINAL_LARGE("%s(): stocks share price oversize !!!\n");
    if (memcmp(record + 0x24, data + p + 2, n > 0x3f ? 0x40 : n) != 0) {
        memset_bytes(record + 0x24, 0, 0x40); cleanStocksIndex();
    }
    memcpy(record + 0x24, data + p + 2, n > 0x3f ? 0x40 : n);
    p += n + 2;
    if ((int8_t)data[p] != 3)
        BLE_STOCK_FINAL_BAD("%s(): stocks share price data struct error, error type = %d\n");
    n = data[p + 1];
    if (n > 0x10) BLE_STOCK_FINAL_LARGE("%s(): stocks share price oversize !!!\n");
    memset_bytes(record + 0x64, 0, 0x10);
    memcpy(record + 0x64, data + p + 2, n > 0xf ? 0x10 : n);
    p += n + 2;
    if ((int8_t)data[p] != 4)
        BLE_STOCK_FINAL_BAD("%s(): stocks price change data struct error, error type = %d\n");
    n = data[p + 1];
    if (n > 0x10) BLE_STOCK_FINAL_LARGE("%s(): stocks price change oversize !!!\n");
    memset_bytes(record + 0x74, 0, 0x10);
    memcpy(record + 0x74, data + p + 2, n > 0xf ? 0x10 : n);
    p += n + 2;
    if ((int8_t)data[p] != 5)
        BLE_STOCK_FINAL_BAD("%s(): stocks change rate data struct error, error type = %d\n");
    n = data[p + 1];
    if (n > 0x10) BLE_STOCK_FINAL_LARGE("%s(): stocks price change oversize !!!\n");
    memset_bytes(record + 0x84, 0, 0x10);
    memcpy(record + 0x84, data + p + 2, n > 0xf ? 0x10 : n);
    p += n + 2;
    if ((int8_t)data[p] != 6)
        BLE_STOCK_FINAL_BAD("%s(): stocks change rate data struct error, error type = %d\n");
    if ((int8_t)data[p + 1] != 1)
        BLE_STOCK_FINAL_BAD("%s(): stocks change status sformat error !!!\n");
    record[1] = data[p + 2];
    if (BLE_LOG_LEVEL > 2) {
        if (BLE_IS_DEBUG == 0)
            log_message("%s(): stock change status : %d\n", "ble_process_put_req");
        else debug_print();
    }
    p += 3;
    if ((int8_t)data[p] != 7)
        BLE_STOCK_FINAL_BAD("%s(): stocks change rate data struct error, error type = %d\n");
    image_len = ble_put_le16(data + p + 1);
    if (image_len > 0x75e)
        BLE_STOCK_FINAL_BAD("%s(): stocks image format oversize !!!\n");
    *(uint16_t *)(void *)(record + 2) = image_len;
    memset_bytes(record + 0x94, 0);
    memcpy(record + 0x94, data + p + 3, image_len);
    record[0] = 1;
    if (BLE_LOG_LEVEL > 2) {
        if (BLE_IS_DEBUG == 0)
            log_message("%s(): We received %d byte of data from the App\n",
                        "ble_process_put_req",
                        (uint32_t)*(uint16_t *)(void *)(record + 2));
        else
            debug_print();
    }
    *expected_total = 0;
    *accepted_count = 0;
    BLE_STOCK_FINAL_ACK(0);

#undef BLE_STOCK_FINAL_LARGE
#undef BLE_STOCK_FINAL_BAD
#undef BLE_STOCK_FINAL_ACK
    return BLE_PUT_HANDLER_BREAK;
}

/* Opcode 6/subop 4 multipart transport and final assembled-buffer parser. */
BLE_PUT_ALWAYS_INLINE enum ble_put_handler_result
ble_put_op06_04_multipart_assemble(struct ble_put_context *ctx,
                                  const uint8_t *request,
                                  uint8_t response[20])
{
    volatile uint16_t *const assembled_length =
        (volatile uint16_t *)(uintptr_t)0x2000d710;
    volatile uint16_t *const expected_total =
        (volatile uint16_t *)(uintptr_t)0x2000d712;
    volatile uint16_t *const accepted_count =
        (volatile uint16_t *)(uintptr_t)0x2000d714;
    volatile uint16_t *const diagnostic_count =
        (volatile uint16_t *)(uintptr_t)0x2000f6e2;
    uint8_t *const assembled = (uint8_t *)(uintptr_t)0x20010d47;
    uint32_t total = ble_put_le16(request + 5);
    uint32_t current = ble_put_le16(request + 7);
    uint32_t request_length = ble_put_le16(request + 1);
    int ret;

#define BLE_STOCK_PART_ACK(status_) do {                                   \
        *(uint32_t *)(void *)response =                                    \
            *(const uint32_t *)(const void *)request;                       \
        *(uint32_t *)(void *)(response + 4) =                              \
            *(const uint32_t *)(const void *)(request + 4);                 \
        response[8] = request[8];                                           \
        response[9] = (uint8_t)(status_);                                   \
        ret = ctx->post_to_host(response, 10);                              \
        if (ret < 0 && BLE_LOG_LEVEL > 0) {                                \
            if (BLE_IS_DEBUG == 0)                                         \
                log_message("%s(): post_to_host failed ret = %d\n",       \
                            "ble_process_put_req", ret);                   \
            else                                                            \
                debug_print();                                             \
        }                                                                   \
    } while (0)

    if (total == 1)
        return BLE_PUT_HANDLER_UNHANDLED;

    if (current == 1) {
        if (BLE_LOG_LEVEL > 2) {
            if (BLE_IS_DEBUG == 0)
                log_message("%s(): Action ID = 1,Received schedule multiple initialization packets, currently the first packet of data\n",
                            "ble_process_put_req");
            else
                debug_print();
        }
        *accepted_count = 0;
        *expected_total = 0;
        *assembled_length = 0;
        memset_bytes(assembled, 0, 0x812);
        safe_memcpy_checked(assembled, request + 9, request_length - 9u, 0x812);
        *assembled_length = (uint16_t)(*assembled_length + request_length - 9u);
        *accepted_count = (uint16_t)(*accepted_count + 1u);
        *expected_total = (uint16_t)total;
        BLE_STOCK_PART_ACK(0);
        return BLE_PUT_HANDLER_BREAK;
    }

    if (current < total) {
        if ((uint32_t)*accepted_count == current - 1u) {
            memcpy(assembled + *assembled_length,
                         request + 9, request_length - 9u);
            *assembled_length =
                (uint16_t)(*assembled_length + request_length - 9u);
            *accepted_count = (uint16_t)(*accepted_count + 1u);
            BLE_STOCK_PART_ACK(0);
            return BLE_PUT_HANDLER_BREAK;
        }
        if (BLE_LOG_LEVEL > 1) {
            if (BLE_IS_DEBUG == 0)
                log_message("%s(): There is a packet order error, current packet order = %d, expected packet order =%d\n",
                            "ble_process_put_req", current,
                            (uint32_t)*diagnostic_count + 1u);
            else
                debug_print("%s(): There is a packet order error, current packet order = %d, expected packet order =%d\n",
                             "ble_process_put_req");
        }
        *expected_total = 0;
        *accepted_count = 0;
        memset_bytes(assembled, 0, 0x812);
        BLE_STOCK_PART_ACK(1);
        return BLE_PUT_HANDLER_BREAK;
    }

    if (current == total) {
        if ((uint32_t)*accepted_count == current - 1u &&
            (uint32_t)*expected_total == current) {
            memcpy(assembled + *assembled_length,
                         request + 9, request_length - 9u);
            *assembled_length =
                (uint16_t)(*assembled_length + request_length - 9u);
            *accepted_count = (uint16_t)(*accepted_count + 1u);
            return ble_put_op06_04_assembled(ctx, request, response);
        }
        if (BLE_LOG_LEVEL > 1) {
            if (BLE_IS_DEBUG == 0)
                log_message("%s(): There is a packet order error, current packet order = %d, expected packet order =%d\n",
                            "ble_process_put_req", current,
                            (uint32_t)*accepted_count + 1u);
            else
                debug_print("%s(): There is a packet order error, current packet order = %d, expected packet order =%d\n",
                             "ble_process_put_req");
        }
        *expected_total = 0;
        *accepted_count = 0;
        memset_bytes(assembled, 0, 0x812);
        BLE_STOCK_PART_ACK(1);
    }
#undef BLE_STOCK_PART_ACK
    return BLE_PUT_HANDLER_BREAK;
}

/* Opcode 6/subop 5, single-packet news record.  Multipart packets are owned
 * by the separate assembler and are deliberately reported as unhandled. */
BLE_PUT_ALWAYS_INLINE enum ble_put_handler_result
ble_put_op06_05_single(struct ble_put_context *ctx,
                       const uint8_t *request,
                       uint8_t response[20])
{
    uint8_t *config;
    uint8_t *record;
    uint32_t slot, source_length, text_length;
    uint32_t text_tag;
    int ret;

#define BLE_NEWS_ACK(status_) do {                                         \
        *(uint32_t *)(void *)response =                                    \
            *(const uint32_t *)(const void *)request;                       \
        *(uint32_t *)(void *)(response + 4) =                              \
            *(const uint32_t *)(const void *)(request + 4);                 \
        response[8] = request[8];                                           \
        response[9] = (uint8_t)(status_);                                   \
        ret = ctx->post_to_host(response, 10);                              \
        if (ret < 0 && BLE_LOG_LEVEL > 0) {                                \
            if (BLE_IS_DEBUG == 0)                                         \
                log_message("%s(): post_to_host failed ret = %d\n",       \
                            "ble_process_put_req", ret);                   \
            else                                                            \
                debug_print();                                             \
        }                                                                   \
    } while (0)
#define BLE_NEWS_BAD(message_) do {                                        \
        if (BLE_LOG_LEVEL > 0) {                                           \
            if (BLE_IS_DEBUG == 0)                                         \
                log_message((message_), "ble_process_put_req");           \
            else                                                            \
                debug_print();                                             \
        }                                                                   \
        BLE_NEWS_ACK(1);                                                    \
        return BLE_PUT_HANDLER_RETURN;                                      \
    } while (0)

    if (ble_put_le16(request + 5) != 1)
        return BLE_PUT_HANDLER_UNHANDLED;

    config = *(uint8_t **)(uintptr_t)(get_device_info() + 0xfec);
    config[0x64] = request[9];
    config = *(uint8_t **)(uintptr_t)(get_device_info() + 0xfec);
    config[0x65] = request[10];
    config = *(uint8_t **)(uintptr_t)(get_device_info() + 0xfec);
    config[0x69] = request[11];
    if (BLE_LOG_LEVEL > 2) {
        if (BLE_IS_DEBUG == 0) {
            uint8_t *shown = *(uint8_t **)((uint8_t *)ctx + 0x870);
            log_message("%s(): Dashboard display mode :%d  custom display Area value : %d\n",
                        "ble_process_put_req", shown[0x64], shown[0x65]);
        } else {
            debug_print("%s(): Dashboard display mode :%d  custom display Area value : %d\n",
                         "ble_process_put_req");
        }
        if (BLE_LOG_LEVEL > 2) {
            config = *(uint8_t **)(uintptr_t)(get_device_info() + 0xfec);
            if (BLE_IS_DEBUG == 0)
                log_message("%s(): news display mode = %d\n",
                            "ble_process_put_req", config[0x69]);
            else {
                config = *(uint8_t **)(uintptr_t)(get_device_info() + 0xfec);
                debug_print("%s(): news display mode = %d\n",
                             "ble_process_put_req", config[0x69]);
            }
        }
    }

    config = *(uint8_t **)(uintptr_t)(get_device_info() + 0xfec);
    if ((int8_t)config[0x69] != 2) {
        BLE_NEWS_ACK(0);
        return BLE_PUT_HANDLER_BREAK;
    }

    slot = request[12];
    if (slot >= 5) {
        if (BLE_LOG_LEVEL > 0) {
            if (BLE_IS_DEBUG == 0)
                log_message("%s(): news index num  oversize!!!!\n",
                            "ble_process_put_req");
            else
                debug_print();
        }
        BLE_NEWS_ACK(1);
        return BLE_PUT_HANDLER_BREAK;
    }
    if (BLE_LOG_LEVEL > 2) {
        if (BLE_IS_DEBUG == 0)
            log_message("%s(): current news index num = %d\n",
                        "ble_process_put_req", slot);
        else
            debug_print();
    }

    record = (uint8_t *)(uintptr_t)(((unsigned long)&g_200107e3) /*=0x200107e3*/ + (slot - 1u) * 0x159u);
    if ((int8_t)request[13] == 2) {
        if (BLE_LOG_LEVEL > 2) {
            if (BLE_IS_DEBUG == 0)
                log_message("%s(): delete news index num = %d\n",
                            "ble_process_put_req", slot);
            else
                debug_print();
        }
        memset_bytes(record, 0);
        cleanNewsIndex();
        BLE_NEWS_ACK(0);
        return BLE_PUT_HANDLER_BREAK;
    }

    if ((int8_t)request[14] != 1)
        BLE_NEWS_BAD("%s(): news data struct error, error type = %d\n");
    source_length = request[15];
    if (source_length > 0x40) {
        if (BLE_LOG_LEVEL > 1) {
            if (BLE_IS_DEBUG == 0)
                log_message("%s(): news source oversize !!!\n",
                            "ble_process_put_req");
            else
                debug_print();
        }
        BLE_NEWS_ACK(1);
    }
    if (memcmp(record + 1, request + 16,
                     source_length > 0x3f ? 0x40 : source_length) != 0) {
        memset_bytes(record + 1, 0, 0x40);
        cleanNewsIndex();
    }
    memcpy(record + 1, request + 16,
                 source_length > 0x3f ? 0x40 : source_length);
    if (BLE_LOG_LEVEL > 2) {
        if (BLE_IS_DEBUG == 0)
            log_message("%s(): news source : %s\n",
                        "ble_process_put_req", record + 1);
        else
            debug_print();
    }

    text_tag = source_length + 16u;
    if ((int8_t)request[text_tag] != 2)
        BLE_NEWS_BAD("%s(): news change rate data struct error, error type = %d\n");
    text_length = ble_put_le16(request + text_tag + 1);
    if (text_length > 0x118)
        BLE_NEWS_BAD("%s(): news txt format oversize !!!\n");

    /* The original comparison begins one byte before the copied text and
     * passes only the low length byte; retain that observable quirk. */
    if (memcmp(record + 0x41, request + text_tag + 2,
                     request[text_tag + 1]) != 0) {
        memset_bytes(record + 0x41, 0, 0x118);
        cleanNewsIndex();
    }
    memcpy(record + 0x41, request + text_tag + 3, text_length);
    record[0] = 1;
    if (BLE_LOG_LEVEL > 2) {
        if (BLE_IS_DEBUG == 0)
            log_message("%s(): We received %d byte of data from the News App\n",
                        "ble_process_put_req", text_length);
        else
            debug_print();
    }
    BLE_NEWS_ACK(0);

#undef BLE_NEWS_BAD
#undef BLE_NEWS_ACK
    return BLE_PUT_HANDLER_BREAK;
}

BLE_PUT_ALWAYS_INLINE enum ble_put_handler_result
ble_put_op06_05_assembled(struct ble_put_context *ctx,
                          const uint8_t *request,
                          uint8_t response[20])
{
    uint8_t *const data = (uint8_t *)(uintptr_t)0x20010682;
    volatile uint16_t *const expected_total =
        (volatile uint16_t *)(uintptr_t)0x2000d70c;
    volatile uint16_t *const accepted_count =
        (volatile uint16_t *)(uintptr_t)0x2000d70e;
    uint8_t *config, *record;
    uint32_t slot, source_length, text_length, text_tag;
    int ret;

#define BLE_NEWS_FINAL_ACK(status_) do {                                   \
        *(uint32_t *)(void *)response =                                    \
            *(const uint32_t *)(const void *)request;                       \
        *(uint32_t *)(void *)(response + 4) =                              \
            *(const uint32_t *)(const void *)(request + 4);                 \
        response[8] = request[8];                                           \
        response[9] = (uint8_t)(status_);                                   \
        ret = ctx->post_to_host(response, 10);                              \
        if (ret < 0 && BLE_LOG_LEVEL > 0) {                                \
            if (BLE_IS_DEBUG == 0)                                         \
                log_message("%s(): post_to_host failed ret = %d\n",       \
                            "ble_process_put_req", ret);                   \
            else debug_print();                                            \
        }                                                                   \
    } while (0)
#define BLE_NEWS_FINAL_BAD(message_) do {                                  \
        if (BLE_LOG_LEVEL > 0) {                                           \
            if (BLE_IS_DEBUG == 0)                                         \
                log_message((message_), "ble_process_put_req");           \
            else debug_print();                                            \
        }                                                                   \
        BLE_NEWS_FINAL_ACK(1);                                              \
        return BLE_PUT_HANDLER_RETURN;                                      \
    } while (0)

    config = *(uint8_t **)(uintptr_t)(get_device_info() + 0xfec);
    config[0x64] = data[0];
    config = *(uint8_t **)(uintptr_t)(get_device_info() + 0xfec);
    config[0x65] = data[1];
    config = *(uint8_t **)(uintptr_t)(get_device_info() + 0xfec);
    config[0x69] = data[2];
    if (BLE_LOG_LEVEL > 2) {
        if (BLE_IS_DEBUG == 0) {
            uint8_t *shown = *(uint8_t **)((uint8_t *)ctx + 0x870);
            log_message("%s(): Dashboard display mode :%d  custom display Area value : %d\n",
                        "ble_process_put_req", shown[0x64], shown[0x65]);
        } else debug_print("%s(): Dashboard display mode :%d  custom display Area value : %d\n",
                            "ble_process_put_req");
        if (BLE_LOG_LEVEL > 2) {
            config = *(uint8_t **)(uintptr_t)(get_device_info() + 0xfec);
            if (BLE_IS_DEBUG == 0)
                log_message("%s(): news display mode = %d\n",
                            "ble_process_put_req", config[0x69]);
            else {
                config = *(uint8_t **)(uintptr_t)(get_device_info() + 0xfec);
                debug_print("%s(): news display mode = %d\n",
                             "ble_process_put_req", config[0x69]);
            }
        }
    }
    config = *(uint8_t **)(uintptr_t)(get_device_info() + 0xfec);
    if ((int8_t)config[0x69] != 2) {
        BLE_NEWS_FINAL_ACK(0);
        return BLE_PUT_HANDLER_BREAK;
    }
    slot = data[3];
    if (slot >= 5) {
        if (BLE_LOG_LEVEL > 0) {
            if (BLE_IS_DEBUG == 0)
                log_message("%s(): stocks data oversize!!!!\n", "ble_process_put_req");
            else debug_print();
        }
        BLE_NEWS_FINAL_ACK(1);
        return BLE_PUT_HANDLER_BREAK;
    }
    if (BLE_LOG_LEVEL > 2) {
        if (BLE_IS_DEBUG == 0)
            log_message("%s(): current news index num = %d\n",
                        "ble_process_put_req", slot);
        else debug_print();
    }
    record = (uint8_t *)(uintptr_t)(((unsigned long)&g_200107e3) /*=0x200107e3*/ + (slot - 1u) * 0x159u);
    if ((int8_t)data[4] == 2) {
        if (BLE_LOG_LEVEL > 2) {
            if (BLE_IS_DEBUG == 0)
                log_message("%s(): delete news index num = %d\n",
                            "ble_process_put_req", slot);
            else debug_print();
        }
        memset_bytes(record, 0);
        BLE_NEWS_FINAL_ACK(0);
        return BLE_PUT_HANDLER_BREAK;
    }
    if ((int8_t)data[5] != 1)
        BLE_NEWS_FINAL_BAD("%s(): news data struct error, error type = %d\n");
    source_length = data[6];
    if (source_length > 0x40) {
        if (BLE_LOG_LEVEL > 1) {
            if (BLE_IS_DEBUG == 0)
                log_message("%s(): news source oversize !!!\n", "ble_process_put_req");
            else debug_print();
        }
        BLE_NEWS_FINAL_ACK(1);
    }
    if (memcmp(record + 1, data + 7,
                     source_length > 0x3f ? 0x40 : source_length) != 0) {
        memset_bytes(record + 1, 0, 0x40);
        cleanNewsIndex();
    }
    memcpy(record + 1, data + 7,
                 source_length > 0x3f ? 0x40 : source_length);
    if (BLE_LOG_LEVEL > 2) {
        if (BLE_IS_DEBUG == 0)
            log_message("%s(): stock code name : %s\n",
                        "ble_process_put_req", record + 1);
        else debug_print();
    }
    text_tag = source_length + 7u;
    if ((int8_t)data[text_tag] != 2)
        BLE_NEWS_FINAL_BAD("%s(): news change rate data struct error, error type = %d\n");
    text_length = ble_put_le16(data + text_tag + 1);
    if (text_length > 0x118)
        BLE_NEWS_FINAL_BAD("%s(): news txt format oversize !!!\n");
    if (memcmp(record + 0x41, data + text_tag + 2,
                     data[text_tag + 1]) != 0) {
        memset_bytes(record + 0x41, 0, 0x118);
        cleanNewsIndex();
    }
    memcpy(record + 0x41, data + text_tag + 3, text_length);
    record[0] = 1;
    if (BLE_LOG_LEVEL > 2) {
        if (BLE_IS_DEBUG == 0)
            log_message("%s(): We received %d byte of data from the News App\n",
                        "ble_process_put_req", text_length);
        else debug_print();
    }
    *expected_total = 0;
    *accepted_count = 0;
    BLE_NEWS_FINAL_ACK(0);

#undef BLE_NEWS_FINAL_BAD
#undef BLE_NEWS_FINAL_ACK
    return BLE_PUT_HANDLER_BREAK;
}

BLE_PUT_ALWAYS_INLINE enum ble_put_handler_result
ble_put_op06_05_multipart_assemble(struct ble_put_context *ctx,
                                  const uint8_t *request,
                                  uint8_t response[20])
{
    volatile uint16_t *const assembled_length =
        (volatile uint16_t *)(uintptr_t)0x2000d70a;
    volatile uint16_t *const expected_total =
        (volatile uint16_t *)(uintptr_t)0x2000d70c;
    volatile uint16_t *const accepted_count =
        (volatile uint16_t *)(uintptr_t)0x2000d70e;
    uint8_t *const assembled = (uint8_t *)(uintptr_t)0x20010682;
    uint32_t total = ble_put_le16(request + 5);
    uint32_t current = ble_put_le16(request + 7);
    uint32_t request_length = ble_put_le16(request + 1);
    int ret;

#define BLE_NEWS_PART_ACK(status_) do {                                    \
        *(uint32_t *)(void *)response =                                    \
            *(const uint32_t *)(const void *)request;                       \
        *(uint32_t *)(void *)(response + 4) =                              \
            *(const uint32_t *)(const void *)(request + 4);                 \
        response[8] = request[8];                                           \
        response[9] = (uint8_t)(status_);                                   \
        ret = ctx->post_to_host(response, 10);                              \
        if (ret < 0 && BLE_LOG_LEVEL > 0) {                                \
            if (BLE_IS_DEBUG == 0)                                         \
                log_message("%s(): post_to_host failed ret = %d\n",       \
                            "ble_process_put_req", ret);                   \
            else debug_print();                                            \
        }                                                                   \
    } while (0)

    if (total == 1)
        return BLE_PUT_HANDLER_UNHANDLED;
    if (current == 1) {
        if (BLE_LOG_LEVEL > 2) {
            if (BLE_IS_DEBUG == 0)
                log_message("%s(): Action ID = 1,Received schedule multiple initialization packets, currently the first packet of data\n",
                            "ble_process_put_req");
            else debug_print();
        }
        *accepted_count = 0;
        *expected_total = 0;
        *assembled_length = 0;
        memset_bytes(assembled, 0, 0x161);
        safe_memcpy_checked(assembled, request + 9, request_length - 9u, 0x161);
        *assembled_length = (uint16_t)(*assembled_length + request_length - 9u);
        *accepted_count = (uint16_t)(*accepted_count + 1u);
        *expected_total = (uint16_t)total;
        BLE_NEWS_PART_ACK(0);
        return BLE_PUT_HANDLER_BREAK;
    }
    if (current < total) {
        if ((uint32_t)*accepted_count == current - 1u) {
            memcpy(assembled + *assembled_length,
                         request + 9, request_length - 9u);
            *assembled_length =
                (uint16_t)(*assembled_length + request_length - 9u);
            *accepted_count = (uint16_t)(*accepted_count + 1u);
            BLE_NEWS_PART_ACK(0);
            return BLE_PUT_HANDLER_BREAK;
        }
        if (BLE_LOG_LEVEL > 1) {
            if (BLE_IS_DEBUG == 0)
                log_message("%s(): There is a packet order error, current packet order = %d, expected packet order =%d\n",
                            "ble_process_put_req", current,
                            (uint32_t)*accepted_count + 1u);
            else debug_print("%s(): There is a packet order error, current packet order = %d, expected packet order =%d\n",
                              "ble_process_put_req", current,
                              (uint32_t)*accepted_count + 1u);
        }
        *expected_total = 0;
        *accepted_count = 0;
        memset_bytes(assembled, 0, 0x161);
        BLE_NEWS_PART_ACK(1);
        return BLE_PUT_HANDLER_BREAK;
    }
    if (current == total) {
        if ((uint32_t)*accepted_count == current - 1u &&
            (uint32_t)*expected_total == current) {
            memcpy(assembled + *assembled_length,
                         request + 9, request_length - 9u);
            *assembled_length =
                (uint16_t)(*assembled_length + request_length - 9u);
            *accepted_count = (uint16_t)(*accepted_count + 1u);
            return ble_put_op06_05_assembled(ctx, request, response);
        }
        if (BLE_LOG_LEVEL > 1) {
            if (BLE_IS_DEBUG == 0)
                log_message("%s(): There is a packet order error, current packet order = %d, expected packet order =%d\n",
                            "ble_process_put_req", current,
                            (uint32_t)*accepted_count + 1u);
            else debug_print("%s(): There is a packet order error, current packet order = %d, expected packet order =%d\n",
                              "ble_process_put_req", current,
                              (uint32_t)*accepted_count + 1u);
        }
        *expected_total = 0;
        *accepted_count = 0;
        memset_bytes(assembled, 0, 0x161);
        BLE_NEWS_PART_ACK(1);
    }
#undef BLE_NEWS_PART_ACK
    return BLE_PUT_HANDLER_BREAK;
}
