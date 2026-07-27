#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007d70a @ 0x0007d70a
 * public-name: projector_write_pixel_data
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Reconstructed projector_write_pixel_data @ 0x7d70a (raw FUN_0007d70a).
 * Reviewed executable extent: 0x44 bytes, ending before FUN_0007d74e. */
#include <stdint.h>

/* Custom projector transport, not an SDK routine.  Raw identity:
 * FUN_000476b4 @ 0x000476b4. */
extern void projector_transfer_pixel_chunk(uint16_t x, uint16_t y,
                                           uint32_t transfer_value,
                                           int32_t byte_count);
extern void projector_send_cmd_immediate(uint8_t command);
extern void delay_ms(int);

enum {
    PROJECTOR_MAX_TRANSFER_BYTES = (0xf0u << 8),
    PROJECTOR_ROWS_PER_TRANSFER = 0xc0,
    PROJECTOR_DISPLAY_UPDATE_COMMAND = 0x97,
};

void projector_write_pixel_data(uint32_t x_argument, uint32_t first_row,
                                uint32_t transfer_value, int32_t byte_count)
{
    uint16_t x = (uint16_t)x_argument;
    uint16_t row = first_row;

    /* The signed comparison is intentional.  Zero and negative counts still
     * reach the transport once, exactly as in the firmware. */
    while (byte_count > PROJECTOR_MAX_TRANSFER_BYTES) {
        projector_transfer_pixel_chunk(x, row, transfer_value,
                                       PROJECTOR_MAX_TRANSFER_BYTES);
        row = (uint16_t)(row + PROJECTOR_ROWS_PER_TRANSFER);
        byte_count -= PROJECTOR_MAX_TRANSFER_BYTES;
    }

    projector_transfer_pixel_chunk(x, row, transfer_value, byte_count);
    projector_send_cmd_immediate(PROJECTOR_DISPLAY_UPDATE_COMMAND);
    delay_ms(1);
}
