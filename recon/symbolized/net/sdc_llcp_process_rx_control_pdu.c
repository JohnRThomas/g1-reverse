#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01018690 @ 0x01018690
 * public-name: sdc_llcp_process_rx_control_pdu
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_ble_pending_channel_idx            @ 0x2100001c
 */
/* net-core sdc_llcp_process_rx_control_pdu @ 0x01018690; raw: FUN_01018690 */
/*
 * SoftDevice Controller LLCP receive dispatcher.
 * Exact contiguous ownership: [0x01018690, 0x010187e0) (0x150 bytes).
 * The opcode-7 switch tail-transfers into shared controller continuations at
 * 0x01018f1a/0x01018f22/0x01018fac; those entries are not owned by this body.
 * NCS 2.5.1 reference match: obfuscated SDC symbol
 * sym_D3OF4UKYCAB3P5XZOK7JC3PV7TCXDH2CWS4GEEY, opcode ratio 0.939.
 */
#include <stdint.h>

struct llcp_decoded_pdu {
    uint32_t header;
    uint32_t parameter_0;
    uint32_t parameter_1;
    uint8_t remaining[0x20];
};

struct llcp_controller_state_overlay {
    uint8_t reserved_000[0x44];
    uint8_t unknown_response_result; /* +0x44 */
    uint8_t reserved_045[0x37];
    uint8_t cleanup_pending;         /* +0x7c */
    uint8_t reserved_07d[0x3c];
    uint8_t receive_state;           /* +0xb9 */
};

static volatile uint8_t *const active_link_index =
    (volatile uint8_t *)(uintptr_t)((unsigned long)&g_net_ble_pending_channel_idx) /*=0x2100001c*/;
static volatile struct llcp_controller_state_overlay *const llcp_state =
    (volatile struct llcp_controller_state_overlay *)(uintptr_t)0x21000f90;

extern uint8_t sdc_llcp_get_active_link_index(void);             /* FUN_0100d760 */
extern void sdc_llcp_decode_control_pdu(const uint8_t *pdu,
                                        struct llcp_decoded_pdu *decoded); /* FUN_0101a070 */
extern int sdc_llcp_apply_rx_transition(struct llcp_decoded_pdu *decoded,
                                        uint32_t opcode, uint32_t flags); /* FUN_0101746c */
extern int sdc_llcp_handle_control_opcode(struct llcp_decoded_pdu *decoded,
                                          uint32_t opcode); /* FUN_010168e4 */
extern int sdc_llcp_handle_unknown_response(struct llcp_decoded_pdu *decoded); /* FUN_010183e0 */
extern void sdc_llcp_note_unsupported_pdu(void);                  /* FUN_01020500 */
extern void sdc_llcp_stop_rx_timeout(void);                       /* FUN_010208b0 */
extern void sdc_llcp_release_rx_context(void);                    /* FUN_0101fca8 */
extern void sdc_assertion_fail(uint32_t module, uint32_t line);   /* FUN_01008d00 */

extern void FUN_01018f1a(uint32_t, uint32_t, uintptr_t, uint32_t);
extern void FUN_01018f22(uint32_t, uint32_t, uintptr_t, uint32_t);
extern void FUN_01018fac(uint32_t, uint32_t, uintptr_t, uint32_t);
#define sdc_llcp_store_unknown_result_tail FUN_01018f1a
#define sdc_llcp_return_tail               FUN_01018f22
#define sdc_llcp_continue_procedure_tail   FUN_01018fac

enum llcp_shared_address {
    LLCP_UNKNOWN_RESPONSE_TABLE = 0x0101878c,
};

static int finish_receive(int result)
{
    if (llcp_state->cleanup_pending != 0) {
        sdc_llcp_stop_rx_timeout();
        sdc_llcp_release_rx_context();
        llcp_state->cleanup_pending = 0;
    }
    return result;
}

static void preprocess_unknown_response(struct llcp_decoded_pdu *decoded)
{
    uint8_t response_type = (uint8_t)decoded->header;
    uint8_t response_flags = (uint8_t)(decoded->header >> 8);

    if (response_type == 2) {
        decoded->parameter_0 = 0;
        decoded->parameter_1 = 0;
        response_flags &= (uint8_t)~3u;
    } else if (response_type == 1) {
        decoded->parameter_1 = 0;
        response_flags &= (uint8_t)~2u;
        if (llcp_state->receive_state != 2) {
            decoded->parameter_0 = 0;
            response_flags &= (uint8_t)~1u;
        }
    } else if (response_type == 0 &&
               (llcp_state->receive_state & 0x0c) != 0 &&
               (response_flags & 0x10) != 0) {
        decoded->parameter_0 = 0;
        decoded->parameter_1 = 0;
        response_flags &= (uint8_t)~3u;
    }

    decoded->header = (decoded->header & 0xffff00ffu) |
                      ((uint32_t)response_flags << 8);
}

int sdc_llcp_process_rx_control_pdu(const uint8_t *pdu)
{
    struct llcp_decoded_pdu decoded;
    uint8_t opcode = pdu[0] & 0x0f;

    *active_link_index = sdc_llcp_get_active_link_index();
    sdc_llcp_decode_control_pdu(pdu, &decoded);

    if (opcode == 7) { /* LL_UNKNOWN_RSP */
        preprocess_unknown_response(&decoded);
        int result = sdc_llcp_apply_rx_transition(&decoded, 7, 0);
        uint32_t state_index = (uint32_t)llcp_state->receive_state - 1u;
        switch (state_index) {
        case 0:
        case 3:
        case 7:
            sdc_llcp_return_tail((uint32_t)result,
                                 (uint32_t)result << 4,
                                 LLCP_UNKNOWN_RESPONSE_TABLE, state_index);
            __builtin_unreachable();
        case 1:
            sdc_llcp_store_unknown_result_tail(
                (uint32_t)result, (uint32_t)result << 4,
                LLCP_UNKNOWN_RESPONSE_TABLE, state_index);
            __builtin_unreachable();
        case 2:
        case 4:
        case 5:
        case 6:
            sdc_llcp_continue_procedure_tail(
                (uint32_t)result, (uint32_t)result << 4,
                LLCP_UNKNOWN_RESPONSE_TABLE, state_index);
            __builtin_unreachable();
        default:
            sdc_assertion_fail(0x32, 0x13b3);
            __builtin_unreachable();
        }

    }

    (void)sdc_llcp_apply_rx_transition(&decoded, opcode, 0);
    int result;
    switch (llcp_state->receive_state) {
    case 1:
        if (opcode == 6 || opcode <= 2) {
            result = sdc_llcp_handle_control_opcode(&decoded, opcode);
            return finish_receive(result);
        }
        /* fall through */
    case 2:
        result = 5;
        sdc_llcp_note_unsupported_pdu();
        return finish_receive(result);
    case 4:
    case 8:
        /* Opcode 7 was dispatched above, so these states reject other PDUs. */
        result = 5;
        sdc_llcp_note_unsupported_pdu();
        return finish_receive(result);
    default:
        sdc_assertion_fail(0x32, 0x13b3);
        __builtin_unreachable();
    }
}
