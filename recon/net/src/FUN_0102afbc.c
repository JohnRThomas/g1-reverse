/* P4 iteration 26 - structural CPUNET RAM relocation.  Self-contained
   so tools/parity keeps compiling this canonical body unchanged: the
   #else arm is the shipped literal.  See recon/application/
   gen_net_ram_relocs.py and recon/symbols/g1_net_ram_reloc.h. */
#ifdef G1_COHESIVE_BUILD
extern unsigned char g1_net_ram_blk_21000570[];
#define G1N_21000580 ((unsigned long)(g1_net_ram_blk_21000570 + 0x10))
#else
#define G1N_21000580 0x21000580ul
#endif
/* net-core FUN_0102afbc @ 0x102afbc  (parity 300 trials PROVEN) */
#include <stdint.h>
extern void FUN_0102fcec(int);
/* P4 iteration 18 — the 64-bit `k_timeout_t delay` was DROPPED here.
 * FUN_01035fa0 is z_impl_k_thread_create; the shipped call sites at
 * 0x0102afd4 and 0x0102aff8 both execute `strd r6, r7, [sp, #24]` with
 * r6 = r7 = 0 (a `sub sp, #36` frame), i.e. they pass K_NO_WAIT in the
 * outgoing-argument words at sp+24/sp+28.  This declaration named only nine
 * parameters, so GCC emitted a `sub sp, #28` frame and never wrote them: the
 * callee read an UNINITIALISED delay, took its `z_add_timeout` branch instead
 * of `z_sched_start`, and the "HCI rpmsg TX"/"HCI rpmsg RX" threads never
 * started.  Same class as app-core iteration 12 (`k_thread_create` stack
 * args); the differential harness cannot see it because it never compares a
 * callee's incoming stack frame. */
extern void FUN_01035fa0(int, int, int, int, int, int, int, int, int,
                         int, int, int);
extern void FUN_0103b156(int, int);
extern int FUN_0102d558(int);
#ifdef G1_COHESIVE_BUILD
#include <zephyr/device.h>
#include <zephyr/ipc/ipc_service.h>
#define FUN_0102d5b4(instance, endpoint, config) \
  ipc_service_register_endpoint((const struct device *)(uintptr_t)(instance), \
                                (struct ipc_ept *)(uintptr_t)(endpoint), \
                                (const struct ipc_ept_cfg *)(uintptr_t)(config))
#else
extern int FUN_0102d5b4(int, int, int);
#endif
extern void FUN_01039722(int, ...);

/* P4 iteration 19: 0x2100095c is hci_rpmsg.c's controller->host k_fifo
 * (the argument bt_enable_raw stores in `raw_rx`).  In the cohesive link it
 * is 0x14 bytes into the stock hci_raw.c `hci_cmd_pool`; real storage is
 * g1_hci_rx_queue in recon/application/net/src/g1_product_endpoints.c.
 * See recon/net/src/FUN_0102acf4.c for the measured consequence. */
#ifdef G1_COHESIVE_BUILD
#include <zephyr/kernel.h>
extern struct k_fifo g1_hci_rx_queue;
#define C_0102b058 ((int)(uintptr_t)&g1_hci_rx_queue) /*=0x2100095c*/
#else
#define C_0102b058 0x2100095c
#endif
#ifdef G1_COHESIVE_BUILD
extern void FUN_0102adac(void);
extern void FUN_0102acf4(void);
extern unsigned char g1_hci_endpoint_config;
#define C_0102b05c ((int)(uintptr_t)&FUN_0102adac) /*=0x0102b5ad*/
#define C_0102b06c ((int)(uintptr_t)&FUN_0102acf4) /*=0x0102b4f5*/
#define C_0102b08c ((int)(uintptr_t)&g1_hci_endpoint_config) /*=0x2100059c*/
/* see recon/net/src/FUN_0102ac0c.c: 0x0103bfac is the shipped `struct device`
 * "ipc0"; unrelocated it makes instance->api read 0 and every ipc_service call
 * fail with -EIO.  Parity builds keep the literal (C_0102b07c below). */
#include <zephyr/devicetree.h>
#define C_0102b07c_DEV ((int)(uintptr_t)DEVICE_DT_GET(DT_NODELABEL(ipc0)))
/* Iteration 18: the shipped thread objects, thread stacks and `struct ipc_ept`
 * all land inside live linker-allocated objects in the cohesive link
 * (backend_data_0 and sdc_mempool) -- see
 * recon/application/net/src/g1_product_endpoints.c for the measurement and the
 * replacement storage.  The two name pointers are runtime-space rodata
 * addresses (analysis 0x0103c888 / 0x0103c895 = "HCI rpmsg TX"/"RX"). */
#include <zephyr/kernel.h>
extern struct k_thread g1_hci_rpmsg_tx_thread;
extern struct k_thread g1_hci_rpmsg_rx_thread;
extern k_thread_stack_t g1_hci_rpmsg_tx_stack[];
extern k_thread_stack_t g1_hci_rpmsg_rx_stack[];
extern unsigned char g1_hci_ept;
extern const char g1_hci_rpmsg_tx_name[];
extern const char g1_hci_rpmsg_rx_name[];
#define C_0102b060 ((int)(uintptr_t)g1_hci_rpmsg_tx_stack)  /*=0x21006cc0*/
#define C_0102b064 ((int)(uintptr_t)&g1_hci_rpmsg_tx_thread) /*=0x21001da0*/
#define C_0102b068 ((int)(uintptr_t)g1_hci_rpmsg_tx_name)   /*=0x0103d088*/
#define C_0102b070 ((int)(uintptr_t)g1_hci_rpmsg_rx_stack)  /*=0x21006480*/
#define C_0102b074 ((int)(uintptr_t)&g1_hci_rpmsg_rx_thread) /*=0x21001d08*/
#define C_0102b078 ((int)(uintptr_t)g1_hci_rpmsg_rx_name)   /*=0x0103d095*/
#define C_0102b088 ((int)(uintptr_t)&g1_hci_ept)            /*=0x21004608*/
#else
#define C_0102b07c_DEV 0x0103bfac
#define C_0102b05c 0x0102b5ad
#define C_0102b06c 0x0102b4f5
#define C_0102b08c 0x2100059c
#define C_0102b060 0x21006cc0
#define C_0102b064 0x21001da0
#define C_0102b068 0x0103d088
#define C_0102b070 0x21006480
#define C_0102b074 0x21001d08
#define C_0102b078 0x0103d095
#define C_0102b088 0x21004608
#endif
#define C_0102b07c 0x0103bfac
#define P_0102b080 G1N_21000580
#define C_0102b084 0x0103d0a2
#define C_0102b090 0x0103d0bf

int FUN_0102afbc(void)
{
  int iVar1;

  FUN_0102fcec(C_0102b058);
  /* trailing (0, 0, 0) = the outgoing-argument padding word at sp+20 and the
     64-bit K_NO_WAIT delay at sp+24/sp+28 that the shipped `strd r6, r7,
     [sp, #24]` writes. */
  FUN_01035fa0(C_0102b064, C_0102b060, 0x600, C_0102b05c, 0, 0, 0, 0xfffffff7, 0,
               0, 0, 0);
  FUN_0103b156(C_0102b064, C_0102b068);
  FUN_01035fa0(C_0102b074, C_0102b070, 0x800, C_0102b06c, 0, 0, 0, 0xfffffff7, 0,
               0, 0, 0);
  FUN_0103b156(C_0102b074, C_0102b078);
  iVar1 = FUN_0102d558(C_0102b07c_DEV);
  if (iVar1 < 0 && iVar1 != -0x78 && 0 < *(volatile int *)P_0102b080) {
    FUN_01039722(C_0102b084, 0);
  }
  iVar1 = FUN_0102d5b4(C_0102b07c_DEV, C_0102b088, C_0102b08c);
  if (iVar1 != 0 && 0 < *(volatile int *)P_0102b080) {
    FUN_01039722(C_0102b090, iVar1);
  }
  return 0;
}
