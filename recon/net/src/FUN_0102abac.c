/* P4 iteration 26/27 - structural CPUNET RAM relocation.  Self-contained
   so tools/parity keeps compiling this canonical body unchanged: the
   #else arm is the shipped literal.  See recon/application/
   gen_net_ram_relocs.py and recon/symbols/g1_net_ram_reloc.h. */
#ifdef G1_COHESIVE_BUILD
extern unsigned char g1_net_ram_blk_21000570[];
#define G1N_21000580 ((unsigned long)(g1_net_ram_blk_21000570 + 0x10))
#else
#define G1N_21000580 0x21000580ul
#endif
/* net-core FUN_0102abac @ 0x0102abac
 * Readable identity: g1_ipc_endpoint_send.
 * Raw back-map: FUN_0102acb4 stores runtime Thumb pointer 0x0102b3ad.
 */
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

#define g1_ipc_endpoint_send FUN_0102abac

#ifdef G1_COHESIVE_BUILD
#include <zephyr/ipc/ipc_service.h>
#define FUN_0102d618(endpoint, data, size) \
    ipc_service_send((struct ipc_ept *)(endpoint), (data), (size))
#else
extern int FUN_0102d618(void *queue, const void *data, uint32_t size);
#endif
extern void FUN_01039722(const char *format, ...);

int g1_ipc_endpoint_send(const void *data, uint32_t size)
{
    if (G1_IPC0_EPT_READY == 1) {
        int status = FUN_0102d618(G1_IPC0_EPT, data, size);
        if (status < 0 && *(volatile int32_t *)G1N_21000580 > 0)
            FUN_01039722((const char *)0x0103ce65u, status);
        return status;
    }

    if (*(volatile int32_t *)G1N_21000580 > 0)
        FUN_01039722((const char *)0x0103ce7au);
    return -1;
}
