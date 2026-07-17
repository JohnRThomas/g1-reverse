/* nrf_qspi_cinstrdata_get @ 0x000666e0; raw FUN_000666e0 */
#include <stdint.h>

void nrf_qspi_cinstrdata_get(uint32_t length, uint8_t *data)
{
    volatile uint32_t *qspi = (volatile uint32_t *)0x5002b000u;
    uint32_t reg1 = qspi[0x63c / 4];
    uint32_t reg0 = qspi[0x638 / 4];

    switch (length) {
    case 9:
        data[7] = (uint8_t)(reg1 >> 24);
    case 8:
        data[6] = (uint8_t)(reg1 >> 16);
    case 7:
        data[5] = (uint8_t)(reg1 >> 8);
    case 6:
        data[4] = (uint8_t)reg1;
    case 5:
        data[3] = (uint8_t)(reg0 >> 24);
    case 4:
        data[2] = (uint8_t)(reg0 >> 16);
    case 3:
        data[1] = (uint8_t)(reg0 >> 8);
    case 2:
        data[0] = (uint8_t)reg0;
    default:
        return;
    }
}
