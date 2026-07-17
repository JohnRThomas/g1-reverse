/* nrf_qspi_pins_set @ 0x00066784; raw FUN_00066784 */
#include <stdint.h>

struct qspi_pins {
    uint32_t sck;
    uint32_t csn;
    uint32_t io0;
    uint32_t io1;
    uint32_t io2;
    uint32_t io3;
};

static uint32_t qspi_pin_value(uint32_t pin)
{
    return pin == 0xffu ? 0xffffffffu : pin;
}

void nrf_qspi_pins_set(const struct qspi_pins *pins)
{
    volatile uint32_t *qspi = (volatile uint32_t *)0x5002b000u;

    qspi[0x524 / 4] = qspi_pin_value(pins->sck);
    qspi[0x528 / 4] = qspi_pin_value(pins->csn);
    qspi[0x530 / 4] = qspi_pin_value(pins->io0);
    qspi[0x534 / 4] = qspi_pin_value(pins->io1);
    qspi[0x538 / 4] = qspi_pin_value(pins->io2);
    qspi[0x53c / 4] = qspi_pin_value(pins->io3);
}
