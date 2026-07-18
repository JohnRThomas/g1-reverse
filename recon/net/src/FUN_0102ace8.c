/* net-core FUN_0102ace8 @ 0x0102ace8 (CFG-directed PASS) */
#include <stdint.h>

extern void FUN_01036824(void *sem);

/* hci_ept_bound for the stock "nrf_bt_hci" endpoint. */
void FUN_0102ace8(void *priv)
{
    (void)priv;
    FUN_01036824((void *)UINT32_C(0x2100092c));
}
