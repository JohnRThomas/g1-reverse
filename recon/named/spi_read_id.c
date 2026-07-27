/* readable reconstruction; identity: FUN_00047724 @ 0x00047724
 * public-name: spi_read_id
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   projector_bus_lock                       <= FUN_00047698 @ 0x00047698
 *   projector_bus_unlock                     <= FUN_000476a8 @ 0x000476a8
 *   get_projector_controller                 <= FUN_0007d4ec @ 0x0007d4ec
 * address symbols (name @ address):
 *   rodata_d7459                             @ 0x000d7459   [INLINED -- G6 literal batch]
 *   rodata_d748d                             @ 0x000d748d   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Full reconstruction of spi_read_id @ 0x47724 (108-byte extent).
 * CFG_VERIFY_CALL_ARITIES=0,2,4,0,4
 * The caller-owned TX/RX locals are narrowly stack-pointer-normalized while
 * all four register arguments remain compared. */
#include <stdint.h>
#include "../headers/g1_log.h"

typedef void (*spi_transfer_47724_t)(void *device, const void *tx,
                                    uint32_t tx_length, void *rx,
                                    uint32_t rx_length, uint32_t options);
struct spi_api_47724 { uint32_t reserved[2]; spi_transfer_47724_t transfer; };
struct spi_state_47724 {
    uint8_t reserved[0x374];
    struct spi_api_47724 *device;
};

extern struct spi_state_47724 *get_projector_controller(void);
extern void projector_bus_lock(unsigned int, unsigned int);
extern void projector_bus_unlock(void);

uint32_t spi_read_id(uint32_t unused, uint32_t options, uint32_t ignored)
{
    uint32_t command = 0x9f;
    uint32_t response = 0;
    (void)unused;
    (void)ignored;

    struct spi_state_47724 *state = get_projector_controller();
    projector_bus_lock(UINT32_MAX, UINT32_MAX);
    state->device->transfer(state->device, &command, 4, &response, 4, options);
    projector_bus_unlock();

    if (*(volatile int32_t *)(uintptr_t)0x2000230cu > 2) {
        uint32_t b0 = (response >> 0) & 0xff;
        uint32_t b1 = (response >> 8) & 0xff;
        uint32_t b2 = (response >> 16) & 0xff;
        uint32_t b3 = (response >> 24) & 0xff;
        if (*(volatile uint32_t *)(uintptr_t)0x20007554u == 0)
            log_message(0x000d7459u, 0x000d748du, b0, b1, b2, b3);
        else
            debug_print(0x000d7459u, 0x000d748du, b0, b1, b2, b3);
    }

    return ((response >> 16) & 0xffu) << 8 | ((response >> 24) & 0xffu);
}
