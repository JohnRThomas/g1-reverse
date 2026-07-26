/* readable reconstruction; identity: FUN_00030cd0 @ 0x00030cd0
 * public-name: pt_comm_transport_write
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   transport_parameters_write               <= FUN_00025950 @ 0x00025950
 *   pt_comm_transport_write                  <= FUN_00030cd0 @ 0x00030cd0
 *   packet_transport_send_byte               <= FUN_0003364c @ 0x0003364c
 * address symbols (name @ address):
 *   rodata_a6589                             @ 0x000a6589
 */
/* Reconstructed FUN_00030cd0 @ 0x30cd0  true code extent: 0x3a bytes */
#include <stdint.h>
#include "../headers/g1_log.h"

extern uint32_t transport_parameters_write(int, uint8_t *, int, int);
extern uint32_t packet_transport_send_byte(int, uint8_t *, int, int);

uint32_t pt_comm_transport_write(int operation, int context, uint8_t *buffer, int length)
{
    if (context == 0 || buffer == 0 || length == 0 || operation == 2) {
        log_message(0x000a6589);
        return UINT32_MAX;
    }

    if (operation == 0)
        return transport_parameters_write(context, buffer, length, length);
    if (operation == 1)
        return packet_transport_send_byte(context, buffer, length, length);
    return 0;
}
