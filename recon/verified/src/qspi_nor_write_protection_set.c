/* Reconstructed qspi_nor_write_protection_set @ 0x00083954 (FUN_00083954; CFG-verified). */
/* Pinned Zephyr 3.4.99 owner: drivers/flash/nrf_qspi_nor.c. */
#include <stdbool.h>
#include <stdint.h>
extern int FUN_00060ab0(void *dev, void *cmd, bool lock);
struct qspi_cmd { uint8_t op_code; uint8_t pad[3]; const void *tx; const void *rx; };
int qspi_nor_write_protection_set(void *dev, bool write_protect)
{
    struct qspi_cmd cmd = { .op_code = write_protect ? 4u : 6u, .tx = 0, .rx = 0 };
    return FUN_00060ab0(dev, &cmd, false) == 0 ? 0 : -5;
}
