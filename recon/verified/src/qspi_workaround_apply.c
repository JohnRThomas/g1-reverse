/* qspi_workaround_apply @ 0x000667e0; raw FUN_000667e0 */
#include <stdint.h>

struct qspi_pins {
    uint32_t sck;
    uint32_t csn;
    uint32_t io0;
    uint32_t io1;
    uint32_t io2;
    uint32_t io3;
};

extern void nrf_qspi_pins_set(const struct qspi_pins *pins); /*=0x00066784*/

void qspi_workaround_apply(void)
{
    volatile uint32_t *qspi = (volatile uint32_t *)0x5002b000u;
    struct qspi_pins saved;
    const struct qspi_pins disconnected = {
        0xffffffffu,
        0xffffffffu,
        0xffffffffu,
        0xffffffffu,
        0xffffffffu,
        0xffffffffu,
    };

    saved.sck = qspi[0x524 / 4] & 0xffu;
    saved.csn = qspi[0x528 / 4] & 0xffu;
    saved.io0 = qspi[0x530 / 4] & 0xffu;
    saved.io1 = qspi[0x534 / 4] & 0xffu;
    saved.io2 = qspi[0x538 / 4] & 0xffu;
    saved.io3 = qspi[0x53c / 4] & 0xffu;

    nrf_qspi_pins_set(&disconnected);
    qspi[0x100 / 4] = 0;
    qspi[0] = 1;
    while (qspi[0x100 / 4] == 0) {
    }
    nrf_qspi_pins_set(&saved);
}
