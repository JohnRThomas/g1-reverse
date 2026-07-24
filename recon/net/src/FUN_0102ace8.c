/* net-core FUN_0102ace8 @ 0x0102ace8 (CFG-directed PASS) */
#include <stdint.h>

#ifdef G1_COHESIVE_BUILD
/* P4 iteration 7 — relocated net-core IPC objects.  See
 * recon/application/net/src/g1_product_endpoints.c for the decode of the two
 * K_SEM_DEFINE(...,0,1) bind semaphores (original 0x21000914 / 0x2100092c) and
 * of the `struct ipc_ept` + ready flag (original 0x210045f8 / 0x21004600),
 * plus the measured sched.c:722 kernel panic they caused.  Parity builds keep
 * the original literals. */
#include <zephyr/kernel.h>
#include <zephyr/ipc/ipc_service.h>
extern struct k_sem g1_ipc0_bound_sem;
extern struct k_sem g1_hci_bound_sem;
extern struct ipc_ept g1_ipc0_ept;
extern volatile uint32_t g1_ipc0_ept_ready;
#define G1_IPC0_BOUND_SEM ((void *)&g1_ipc0_bound_sem)
#define G1_HCI_BOUND_SEM  ((void *)&g1_hci_bound_sem)
#define G1_IPC0_EPT       ((void *)&g1_ipc0_ept)
#define G1_IPC0_EPT_READY (g1_ipc0_ept_ready)
#else
#define G1_IPC0_BOUND_SEM ((void *)UINT32_C(0x21000914))
#define G1_HCI_BOUND_SEM  ((void *)UINT32_C(0x2100092c))
#define G1_IPC0_EPT       ((void *)UINT32_C(0x210045f8))
#define G1_IPC0_EPT_READY (*(volatile uint32_t *)UINT32_C(0x21004600))
#endif

extern void FUN_01036824(void *sem);

/* hci_ept_bound for the stock "nrf_bt_hci" endpoint. */
void FUN_0102ace8(void *priv)
{
    (void)priv;
    FUN_01036824(G1_HCI_BOUND_SEM);
}
