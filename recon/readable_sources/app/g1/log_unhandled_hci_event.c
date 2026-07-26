#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_2          => struct g1_layout_net_buf__param_0187                    [param_0187; library]
 * Raw function identity: 0x00053580.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00053580 @ 0x00053580
 * public-name: log_unhandled_hci_event
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   log_unhandled_hci_event                  <= FUN_00053580 @ 0x00053580
 * address symbols (name @ address):
 *   rodata_88138                             @ 0x00088138
 *   rodata_f2df8                             @ 0x000f2df8   [INLINED -- G6 literal batch]
 */
/* Reconstructed FUN_00053580 @ 0x00053580. */
#include <stdint.h>
#include "../../../headers/g1_log.h"

extern uint32_t bt_hex(uint32_t value, uint32_t length); /* FUN_00052c98 */
/* FUN_00080ea2 */

struct hci_command_log_record {
    uint32_t argument_count;
    uint32_t format;       /* =0x000f2df8 */
    uint32_t command;
    uint32_t payload_size;
    uint32_t payload_hex;
    uint16_t opcode;
};

void log_unhandled_hci_event(uint32_t command, const uint8_t *packet)
{
    uint16_t payload_size = *(const uint16_t *)(packet + 0x10);
    struct hci_command_log_record record = {
        .argument_count = 0x01000005u,
        .format = ((unsigned long)"Unhandled event 0x%02x len %u: %s") /*=0xf2df8*/,
        .command = command,
        .payload_size = payload_size,
        .payload_hex = bt_hex(*(const uint32_t *)(packet + 0x0c), payload_size),
        .opcode = 0x0402u,
    };

    log_message(((unsigned long)&rodata_88138) /*=0x88138*/, 0x2c80u, &record);
}
