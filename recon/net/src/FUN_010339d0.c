/* Pinned NCS ESB TX FIFO capacity query @ 0x010339d0.
 * Raw back-map: FUN_010339d0@0x010339d0; true extent 0x0e.
 * Public identity: esb_tx_full.
 */
#include <stdbool.h>
#include <stdint.h>

#define esb_tx_full FUN_010339d0

bool esb_tx_full(void)
{
    volatile uint32_t *const tx_fifo =
        (volatile uint32_t *)0x21004a60u;
    return tx_fifo[0x28 / 4] > 7u;
}
