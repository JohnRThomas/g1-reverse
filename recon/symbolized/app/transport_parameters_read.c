#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000258b4 @ 0x000258b4
 * public-name: transport_parameters_read
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ipc_send_len_prefixed_packet_locked_retry <= FUN_00025788 @ 0x00025788
 *   transport_parameters_read                <= FUN_000258b4 @ 0x000258b4
 * address symbols (name @ address):
 *   rodata_9f2f8                             @ 0x0009f2f8
 *   rodata_9f32d                             @ 0x0009f32d
 *   rodata_9f361                             @ 0x0009f361
 */
/* Reconstructed FUN_000258b4 @ 0x000258b4, extent 0x000000a0.
 * Readable identity: transport_parameters_read.
 * Raw/address backmap: transport_parameters_read <= FUN_000258b4 @ 0x000258b4.
 */
#include <stdint.h>

extern int log_message(uintptr_t format, ...);
extern int ipc_send_len_prefixed_packet_locked_retry(uint32_t transport, uint32_t key,
                        void *value, uint32_t length);

int transport_parameters_read(uint32_t transport, uint32_t *value, uint32_t *result_value)
{
    uint8_t status = 0U;
    uint32_t received = 0U;
    int result;

    if (transport == 0U || value == 0 || result_value == 0)
        return -1;
    result = ipc_send_len_prefixed_packet_locked_retry(transport, 0x2006U, &status, 1U);
    if (result != 0) {
        log_message(((unsigned long)&rodata_9f2f8) /*=0x9f2f8*/);
        return -2;
    }
    if ((status & 5U) != 5U)
        return -3;
    result = ipc_send_len_prefixed_packet_locked_retry(transport, 0x2007U, &received, 1U);
    if (result != 0) {
        log_message(((unsigned long)&rodata_9f32d) /*=0x9f32d*/);
        return -4;
    }
    *result_value = received;
    result = ipc_send_len_prefixed_packet_locked_retry(transport, 0x2008U, value, 0xffU);
    if (result != 0) {
        log_message(((unsigned long)&rodata_9f361) /*=0x9f361*/);
        return -5;
    }
    return 0;
}
