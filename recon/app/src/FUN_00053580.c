/* Reconstructed FUN_00053580 @ 0x00053580. */
#include <stdint.h>

extern uint32_t bt_hex(uint32_t value, uint32_t length); /* FUN_00052c98 */
extern void log_message(unsigned long, ...); /* FUN_00080ea2 */

struct hci_command_log_record {
    uint32_t argument_count;
    uint32_t format;       /* =0x000f2df8 */
    uint32_t command;
    uint32_t payload_size;
    uint32_t payload_hex;
    uint16_t opcode;
};

void FUN_00053580(uint32_t command, const uint8_t *packet)
{
    uint16_t payload_size = *(const uint16_t *)(packet + 0x10);
    struct hci_command_log_record record = {
        .argument_count = 0x01000005u,
        .format = 0x000f2df8u,
        .command = command,
        .payload_size = payload_size,
        .payload_hex = bt_hex(*(const uint32_t *)(packet + 0x0c), payload_size),
        .opcode = 0x0402u,
    };

    log_message(0x00088138u, 0x2c80u, &record);
}
