/* readable reconstruction; identity: FUN_000839a6 @ 0x000839a6
 * public-name: qspi_rdsr
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Config-specialized NCS qspi_rdsr @ 0x000839a6 (FUN_000839a6). */
#include <stddef.h>
#include <stdint.h>

struct qspi_buf {
    uint8_t *buf;
    size_t len;
};
struct qspi_cmd {
    uint8_t opcode;
    uint8_t reserved[3];
    const struct qspi_buf *tx;
    struct qspi_buf *rx;
};

extern int qspi_nor_send_cinstr(const void *device,
                                const struct qspi_cmd *command,
                                uint32_t asynchronous); /* FUN_00060ab0 */

int qspi_rdsr(const void *device)
{
    uint8_t status = 0xffu;
    struct qspi_buf receive = { &status, 1u };
    struct qspi_cmd command = { 5u, {0u, 0u, 0u}, 0, &receive };
    int result = qspi_nor_send_cinstr(device, &command, 0u);
    return result >= 0 ? (int)status : result;
}
