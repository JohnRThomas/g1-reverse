/* readable reconstruction; identity: FUN_0001a75c @ 0x0001a75c
 * public-name: ble_process_put_req
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   put_whitelist_app_from_app               <= FUN_00035688 @ 0x00035688
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 *   strcpy                                   <= FUN_00086fee @ 0x00086fee
 */
/* Reconstructed ble_process_put_req @ 0x1a75c */
#include "ble_process_put_common.h"
#include "ble_process_put_ops_01_08.inc"
#include "ble_process_put_ops_09_10.inc"
#include "ble_process_put_ops_0b_18.inc"
#include "ble_process_put_ops_19_20.inc"
#include "ble_process_put_ops_21_27.inc"

extern int put_whitelist_app_from_app();

void ble_process_put_req(struct ble_put_context *ctx, uint8_t *packet,
                         uint32_t *request_words)
{
    const uint8_t *request = (const uint8_t *)(const void *)request_words;
    uint8_t response[20];
    uint8_t command = packet[0];
    enum ble_put_handler_result result;

    *(uint32_t *)(void *)response = 0;
    memset_bytes(response + 4, 0, 16);
    *(uint32_t *)(void *)ctx->transfer = *(const uint32_t *)(const void *)packet;
    ctx->transfer_length = (uint32_t)ble_put_le16(packet + 2) + 4U;
    response[0] = command;

    switch (command) {
    case 1: case 2: case 3: case 5:
        ble_put_copy_ack(ctx, packet, request, response);
        break;
    case 4:
        put_whitelist_app_from_app(ctx, ctx->transfer + 4, request_words, packet[2], response);
        break;
    case 6:
        switch (request[4]) {
        case 1: case 2: case 6:
            result = ble_put_op06_01_02(ctx, packet, request, response);
            break;
        case 3:
            result = ble_put_op06_03(ctx, request, response);
            break;
        case 4:
            result = ble_put_le16(request + 5) == 1U
                ? ble_put_op06_04_single(ctx, request, response)
                : ble_put_op06_04_multipart_assemble(ctx, request, response);
            break;
        case 5:
            result = ble_put_le16(request + 5) == 1U
                ? ble_put_op06_05_single(ctx, request, response)
                : ble_put_op06_05_multipart_assemble(ctx, request, response);
            break;
        default:
            result = BLE_PUT_HANDLER_BREAK;
            break;
        }
        if (result == BLE_PUT_HANDLER_RETURN)
            return;
        break;
    case 7:
        ble_put_op07(ctx, request, response);
        break;
    case 8:
        ble_put_op08(ctx, packet, request, response);
        break;
    case 9:
        (void)ble_put_op9_dispatch((struct ble_put_context_09_10 *)(void *)ctx,
                                   packet, request, response);
        break;
    case 10:
        (void)ble_put_op10_dispatch((struct ble_put_context_09_10 *)(void *)ctx,
                                    packet, request, response);
        break;
    case 0x0b: case 0x14:
        ble_put_op0b_14(ctx, packet, request, response);
        break;
    case 0x0c: case 0x11: case 0x12: case 0x13:
        ble_put_op0c_11_12_13(ctx, response);
        break;
    case 0x0d:
        ble_put_op0d_0f(ctx, packet, request, response, 0);
        break;
    case 0x0e:
        ble_put_op0e(ctx, request, response);
        break;
    case 0x0f:
        ble_put_op0d_0f(ctx, packet, request, response, 1);
        break;
    case 0x10:
        ble_put_op10_media(ctx, packet, request, response);
        break;
    case 0x15:
        ble_put_op15(ctx, packet, request, response);
        break;
    case 0x16:
        ble_put_op16(ctx, packet, request, response);
        break;
    case 0x17:
        ble_put_op17(ctx, packet, response);
        break;
    case 0x18:
        ble_put_op18(ctx, response);
        break;
    case 0x19: case 0x1a: case 0x1b: case 0x1d:
        ble_put_op19_1a_1b_1d(ctx, response);
        break;
    case 0x1c:
        ble_put_op1c(ctx, request, response);
        break;
    case 0x1e:
        ble_put_op1e(ctx, packet, request, response);
        break;
    case 0x1f:
        ble_put_op1f(ctx, packet, request, response);
        break;
    case 0x20:
        ble_put_op20(ctx, packet, request, response);
        break;
    case 0x21: case 0x22: case 0x23: case 0x24:
    case 0x25: case 0x26: case 0x27:
        (void)ble_put_ops_21_27((struct ble_put_context_21_27 *)(void *)ctx,
                                command, packet, request, response);
        break;
    default:
        response[1] = 0xca;
        response[2] = 0x15;
        strcpy(response + 2, "error put req.");
        ctx->post_to_host(response, 20);
        break;
    }
}
