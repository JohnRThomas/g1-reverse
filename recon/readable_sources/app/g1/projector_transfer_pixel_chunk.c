#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000476b4 @ 0x000476b4
 * public-name: projector_transfer_pixel_chunk
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   projector_bus_lock                       <= FUN_00047698 @ 0x00047698
 *   projector_bus_unlock                     <= FUN_000476a8 @ 0x000476a8
 *   projector_transfer_pixel_chunk           <= FUN_000476b4 @ 0x000476b4
 *   get_projector_controller                 <= FUN_0007d4ec @ 0x0007d4ec
 */
/* Full reconstruction of FUN_000476b4 @ 0x476b4 (108-byte extent).
 * CFG_VERIFY_CALL_ARITIES=0,2,4,0
 * The caller-owned RX local is narrowly stack-pointer-normalized while all
 * four register arguments remain compared. */
#include <stdint.h>

typedef void (*spi_transfer_476b4_t)(void *device, const void *tx,
                                     uint32_t tx_length, void *rx,
                                     uint32_t rx_length, uint32_t y,
                                     uint32_t value);
struct spi_api_476b4 { uint32_t reserved[2]; spi_transfer_476b4_t transfer; };
struct spi_state_476b4 {
    uint8_t reserved0[0x344];
    uint8_t *cursor;
    uint8_t reserved1[0x2c];
    struct spi_api_476b4 *device;
};

extern struct spi_state_476b4 *get_projector_controller(void);
extern void projector_bus_lock(uint32_t a, uint32_t b);
extern void projector_bus_unlock(void);

void projector_transfer_pixel_chunk(uint32_t x, uint32_t y, uint32_t value, uint32_t length)
{
    uint32_t received = 0;
    struct spi_state_476b4 *state = get_projector_controller();
    volatile uint8_t *packet = state->cursor - 5;
    uint32_t packed = (x & 0x3ffu) | ((y << 10) & 0x0007fc00u);

    packet[0] = 2;
    packet[2] = (uint8_t)(packed >> 8);
    packet[1] = (uint8_t)(packed >> 16);
    packet[3] = (uint8_t)packed;
    packet[4] = 0xff;

    projector_bus_lock(UINT32_MAX, UINT32_MAX);
    state->device->transfer(state->device, (const void *)packet, length + 6, &received,
                            1, y, value);
    projector_bus_unlock();
}
