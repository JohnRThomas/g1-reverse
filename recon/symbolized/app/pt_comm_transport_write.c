#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00030cd0 @ 0x00030cd0
 * public-name: pt_comm_transport_write
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   pt_comm_transport_write                  <= FUN_00030cd0 @ 0x00030cd0
 * address symbols (name @ address):
 *   rodata_a6589                             @ 0x000a6589
 */
/* Reconstructed FUN_00030cd0 @ 0x30cd0  true code extent: 0x3a bytes */
#include <stdint.h>

extern int log_message(uint32_t, ...);
extern uint32_t FUN_00025950(int, uint8_t *, int, int);
extern uint32_t FUN_0003364c(int, uint8_t *, int, int);

uint32_t pt_comm_transport_write(int operation, int context, uint8_t *buffer, int length)
{
    if (context == 0 || buffer == 0 || length == 0 || operation == 2) {
        log_message(((unsigned long)&rodata_a6589) /*=0xa6589*/);
        return UINT32_MAX;
    }

    if (operation == 0)
        return FUN_00025950(context, buffer, length, length);
    if (operation == 1)
        return FUN_0003364c(context, buffer, length, length);
    return 0;
}
