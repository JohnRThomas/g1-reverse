/* Reconstructed qspi_activate @ 0x664f0  (CFG-directed candidate) */
#include <stdint.h>
extern uint32_t qspi_ready_wait(void);
int qspi_activate(uint32_t wait)
{
    volatile uint32_t *qspi = (volatile uint32_t *)0x5002b000u;
    qspi[0x140] = 1u;
    qspi[0x40] = 0u;
    qspi[0] = 1u;
    if (wait) {
        uint32_t result = qspi_ready_wait();
        if (result != 0x0bad0000u) {
            return (int)result;
        }
        *(volatile uint8_t *)0x2000b380u = 1u;
    }
    return (int)0x0bad0000u;
}
