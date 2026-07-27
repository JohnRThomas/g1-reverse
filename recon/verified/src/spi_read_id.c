/* Full reconstruction of spi_read_id @ 0x47724 (108-byte extent).
 * CFG_VERIFY_CALL_ARITIES=0,2,4,0,4
 * The caller-owned TX/RX locals are narrowly stack-pointer-normalized while
 * all four register arguments remain compared. */
#include <stdint.h>

typedef void (*spi_transfer_47724_t)(void *device, const void *tx,
                                    uint32_t tx_length, void *rx,
                                    uint32_t rx_length, uint32_t options);
struct spi_api_47724 { uint32_t reserved[2]; spi_transfer_47724_t transfer; };
struct spi_state_47724 {
    uint8_t reserved[0x374];
    struct spi_api_47724 *device;
};

extern struct spi_state_47724 *FUN_0007d4ec(void);
extern void FUN_00047698(uint32_t a, uint32_t b);
extern void FUN_000476a8(void);
extern void DEBUG_PRINT(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);

uint32_t spi_read_id(uint32_t unused, uint32_t options, uint32_t ignored)
{
    uint32_t command = 0x9f;
    uint32_t response = 0;
    (void)unused;
    (void)ignored;

    struct spi_state_47724 *state = FUN_0007d4ec();
    FUN_00047698(UINT32_MAX, UINT32_MAX);
    state->device->transfer(state->device, &command, 4, &response, 4, options);
    FUN_000476a8();

    if (*(volatile int32_t *)(uintptr_t)0x2000230cu > 2) {
        uint32_t b0 = (response >> 0) & 0xff;
        uint32_t b1 = (response >> 8) & 0xff;
        uint32_t b2 = (response >> 16) & 0xff;
        uint32_t b3 = (response >> 24) & 0xff;
        if (*(volatile uint32_t *)(uintptr_t)0x20007554u == 0)
            DEBUG_PRINT(0x000d7459u, 0x000d748du, b0, b1, b2, b3);
        else
            FUN_00019c70(0x000d7459u, 0x000d748du, b0, b1, b2, b3);
    }

    return ((response >> 16) & 0xffu) << 8 | ((response >> 24) & 0xffu);
}
