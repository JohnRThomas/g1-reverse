/* net-core FUN_0102ac00 @ 0x0102ac00 (CFG-directed PASS) */
#include <stdint.h>

extern void FUN_01036824(void *sem);

/* hci_ept_bound for the custom "ipc0" endpoint.  The callback ABI supplies
 * an unused private pointer in r0; the firmware replaces it with this
 * endpoint's bound semaphore and tail-calls k_sem_give. */
void FUN_0102ac00(void *priv)
{
    (void)priv;
    FUN_01036824((void *)UINT32_C(0x21000914));
}
