#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0102afbc @ 0x0102afbc
 * public-name: FUN_0102afbc
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   ipc_service_register_endpoint            <= FUN_0102d5b4 @ 0x0102d5b4
 *   printk                                   <= FUN_01039722 @ 0x01039722
 * address symbols (name @ address):
 *   rodata_102b4f5                           @ 0x0102b4f5
 *   rodata_102b5ad                           @ 0x0102b5ad
 *   rodata_103bfac                           @ 0x0103bfac
 *   rodata_103d088                           @ 0x0103d088
 *   rodata_103d095                           @ 0x0103d095
 *   rodata_103d0a2                           @ 0x0103d0a2
 *   rodata_103d0bf                           @ 0x0103d0bf
 *   g_zephyr_log_level                       @ 0x21000580
 */
/* net-core FUN_0102afbc @ 0x102afbc  (parity 300 trials PROVEN) */
extern void FUN_0102fcec(int);
extern void FUN_01035fa0(int, int, int, int, int, int, int, int, int);
extern void FUN_0103b156(int, int);
extern int FUN_0102d558(int);
extern int ipc_service_register_endpoint(int, int, int);
extern void printk(int, ...);

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
#define C_0102b05c ((unsigned long)&rodata_102b5ad) /*=0x102b5ad*/
#define C_0102b060 0x21006cc0
#define C_0102b064 0x21001da0
#define C_0102b068 ((unsigned long)&rodata_103d088) /*=0x103d088*/
#define C_0102b06c ((unsigned long)&rodata_102b4f5) /*=0x102b4f5*/
#define C_0102b070 0x21006480
#define C_0102b074 0x21001d08
#define C_0102b078 ((unsigned long)&rodata_103d095) /*=0x103d095*/
#define C_0102b07c ((unsigned long)&rodata_103bfac) /*=0x103bfac*/
#define P_0102b080 ((unsigned long)&g_zephyr_log_level) /*=0x21000580*/
#define C_0102b084 ((unsigned long)&rodata_103d0a2) /*=0x103d0a2*/
#define C_0102b088 0x21004608
#define C_0102b08c 0x2100059c
#define C_0102b090 ((unsigned long)&rodata_103d0bf) /*=0x103d0bf*/

int FUN_0102afbc(void)
{
  int iVar1;

  FUN_0102fcec(C_0102b058);
  FUN_01035fa0(C_0102b064, C_0102b060, 0x600, C_0102b05c, 0, 0, 0, 0xfffffff7, 0);
  FUN_0103b156(C_0102b064, C_0102b068);
  FUN_01035fa0(C_0102b074, C_0102b070, 0x800, C_0102b06c, 0, 0, 0, 0xfffffff7, 0);
  FUN_0103b156(C_0102b074, C_0102b078);
  iVar1 = FUN_0102d558(C_0102b07c);
  if (iVar1 < 0 && iVar1 != -0x78 && 0 < *(volatile int *)P_0102b080) {
    printk(C_0102b084, 0);
  }
  iVar1 = ipc_service_register_endpoint(C_0102b07c, C_0102b088, C_0102b08c);
  if (iVar1 != 0 && 0 < *(volatile int *)P_0102b080) {
    printk(C_0102b090, iVar1);
  }
  return 0;
}
