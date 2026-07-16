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

extern struct spi_state_476b4 *FUN_0007d4ec(void);
extern void FUN_00047698(uint32_t a, uint32_t b);
extern void FUN_000476a8(void);

void FUN_000476b4(uint32_t x, uint32_t y, uint32_t value, uint32_t length)
{
    uint32_t received = 0;
    struct spi_state_476b4 *state = FUN_0007d4ec();
    volatile uint8_t *packet = state->cursor - 5;
    uint32_t packed = (x & 0x3ffu) | ((y << 10) & 0x0007fc00u);

    packet[0] = 2;
    packet[2] = (uint8_t)(packed >> 8);
    packet[1] = (uint8_t)(packed >> 16);
    packet[3] = (uint8_t)packed;
    packet[4] = 0xff;

    FUN_00047698(UINT32_MAX, UINT32_MAX);
    state->device->transfer(state->device, (const void *)packet, length + 6, &received,
                            1, y, value);
    FUN_000476a8();
}
