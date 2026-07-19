/* readable reconstruction; identity: FUN_00085c86 @ 0x00085c86
 * public-name: zcbor_process_backup
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   cbor_decoder_at_end                      <= FUN_00085c12 @ 0x00085c12
 *   cbor_finalize_backup_count               <= FUN_00085c26 @ 0x00085c26
 */
/* Reconstructed zcbor_process_backup @ 0x00085c86.
 * Raw/address back-map: FUN_00085c86 / 0x00085c86.
 */
#include <stdint.h>

struct zcbor_state_raw {
    uint8_t *payload;
    uint8_t *payload_end;
    uint32_t elem_count;
    uint32_t payload_bak;
    uint8_t indefinite_length_array;
    uint8_t payload_moved;
    uint8_t reserved[2];
    struct zcbor_constant_state_raw *constant_state;
};

struct zcbor_constant_state_raw {
    struct zcbor_state_raw *backup_list;
    uint32_t current_backup;
    uint32_t num_backups;
    uint32_t error;
};

#define zcbor_check_error cbor_decoder_at_end
#define zcbor_error cbor_finalize_backup_count
extern int zcbor_check_error(struct zcbor_constant_state_raw *constant_state);
extern void zcbor_error(struct zcbor_state_raw *state, uint32_t error);

int zcbor_process_backup(struct zcbor_state_raw *state, uint32_t flags,
                         uint32_t max_elem_count, uint32_t inherited_r3)
{
    (void)inherited_r3;
    struct zcbor_constant_state_raw *constant = state->constant_state;
    if (zcbor_check_error(constant) == 0) {
        return 0;
    }

    uint8_t *payload = state->payload;
    uint32_t elem_count = state->elem_count;
    uint32_t current = constant->current_backup;
    if (current == 0u) {
        zcbor_error(state, 2u);
        return 0;
    }

    if ((flags & 1u) != 0u) {
        struct zcbor_state_raw *backup = &constant->backup_list[current - 1u];
        if ((flags & 4u) == 0u && backup->payload_moved != 0u) {
            return 0;
        }
        *state = *backup;
    }
    if ((flags & 2u) != 0u) {
        constant->current_backup--;
    }
    if (elem_count > max_elem_count) {
        zcbor_error(state, 4u);
        return 0;
    }
    if ((flags & 4u) != 0u) {
        state->payload = payload;
    }
    return 1;
}
