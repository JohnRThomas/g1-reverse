/* Pinned NCS ESB transmission start @ 0x01033858.
 * Raw back-map: FUN_01033858@0x01033858; true extent 0x26.
 * Public identity: esb_start_tx.
 * CFG_VERIFY_CALL_ARITIES=1
 */
#include <stdint.h>

extern void FUN_01032c28(void);

#define esb_start_tx_transaction FUN_01032c28
#define esb_start_tx             FUN_01033858

int esb_start_tx(void)
{
    volatile uint8_t *const esb_state =
        (volatile uint8_t *)0x21006458u;
    volatile uint32_t *const tx_fifo =
        (volatile uint32_t *)0x21004a60u;

    if (*esb_state != 0)
        return -16;
    if (tx_fifo[0x28 / 4] == 0)
        return -61;
    esb_start_tx_transaction();
    return 0;
}
