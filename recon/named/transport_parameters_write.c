/* readable reconstruction; identity: FUN_00025950 @ 0x00025950
 * public-name: transport_parameters_write
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ipc_ept_op_a_locked_retry                <= FUN_000256dc @ 0x000256dc
 *   ipc_send_len_prefixed_packet_locked_retry <= FUN_00025788 @ 0x00025788
 *   transport_parameters_write               <= FUN_00025950 @ 0x00025950
 */
/* Reconstructed FUN_00025950 @ 0x00025950, extent 0x0000007c.
 * Readable identity: transport_parameters_write.
 * Raw/address backmap: transport_parameters_write <= FUN_00025950 @ 0x00025950.
 */
#include <stdint.h>

extern int log_message(uintptr_t format, ...);
extern int ipc_send_len_prefixed_packet_locked_retry(uint32_t transport, uint32_t key,
                        void *value, uint32_t length);
extern int ipc_ept_op_a_locked_retry(uint32_t transport, uint32_t key,
                        const void *value, uint32_t length);

int transport_parameters_write(uint32_t transport, const void *value, uint32_t length)
{
    uint8_t status = 0U;
    int result;

    if (transport == 0U || value == 0 || length == 0U)
        return -1;
    result = ipc_send_len_prefixed_packet_locked_retry(transport, 0x2006U, &status, 1U);
    if (result != 0) {
        log_message(0x0009f2f8UL);
        return -2;
    }
    if ((status & 6U) != 0U) {
        log_message(0x0009f396UL);
        return -3;
    }
    result = ipc_ept_op_a_locked_retry(transport, 0x2008U, value, length);
    if (result != 0) {
        log_message(0x0009f3caUL);
        return -3;
    }
    status = 1U;
    result = ipc_send_len_prefixed_packet_locked_retry(transport, 0x2006U, &status, 1U);
    if (result != 0) {
        log_message(0x0009f2f8UL);
        return -2;
    }
    return 0;
}
