/* readable reconstruction; identity: FUN_0102b31c @ 0x0102b31c
 * public-name: FUN_0102b31c
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   printk                                   <= FUN_01039722 @ 0x01039722
 * address symbols (name @ address):
 *   rodata_103d14a                           @ 0x0103d14a
 *   g_zephyr_log_level                       @ 0x21000580
 *   g_net_radio_op_state                     @ 0x210005b4
 *   g_net_radio_sched_param_a                @ 0x21000761
 *   g_net_radio_sched_param_b                @ 0x21000763
 *   g_net_radio_sched_param_c                @ 0x21000767
 *   g_net_radio_temp_raw                     @ 0x21004b9e
 */
/* net-core FUN_0102b31c @ 0x102b31c  (parity 300 trials PROVEN) */

#ifdef G1_COHESIVE_BUILD
/* P4 iteration 20 - the recovered ESB pipe-address block at 0x21000760.
 * Twelve bytes, `.data` in the shipped image (initialiser
 * 01 e9 d3 a3 a3 a3 a3 c9 c9 c9 c9 ff, read with tools/net_extract.py), ending
 * exactly where the SHIPPED _sw_isr_table began (0x2100076c, established in
 * iteration 19).  In the cohesive link those twelve bytes land at
 * _sw_isr_table + 0x5c .. + 0x67, i.e. entries 11 and 12 of the LINKER's own
 * interrupt table.  Bind the emitted object in
 * recon/application/net/src/g1_product_endpoints.c instead.  Parity builds
 * keep the original literals. */
extern unsigned char g1_esb_pipe_addr_block[];
#define G1_NET_ESB_ADDR_BASE ((unsigned long)g1_esb_pipe_addr_block)
#else
#define G1_NET_ESB_ADDR_BASE 0x21000760ul
#endif
#define G1_NET_ESB_ADDR(off) (G1_NET_ESB_ADDR_BASE + (off))

#include <stdint.h>
#include "../../headers/g1_nrf_regs.h"

extern int FUN_010333b4(void *);
extern void FUN_01033af8(int);
extern void FUN_01033acc(int);
extern int FUN_010339e4(int);
extern int FUN_01033a20(int);
extern int FUN_01033a60(int, int);
extern int FUN_01033aac(int);
extern int FUN_01033888(void);
extern void printk(int);

int FUN_0102b31c(int param_1)
{
  volatile int * const p3d0 = (volatile int *)0x210005b4;
  volatile unsigned char * const p3d4 = (volatile unsigned char *)0x21004b9e;
  volatile unsigned char * const pE100 = (volatile unsigned char *)G1_NVIC_ISER0;
  volatile int * const p3e8 = (volatile int *)0x21000580;

  /* Five-word radio configuration assembled from the firmware template at
     0x0103c100, with its mode and runtime fields overridden below. */
  uint32_t config[5];
  int iVar2;
  int iVar1;

  config[0] = 0x21000088u | ((param_1 != 0) ? 0x100u : 0u);
  config[1] = 0x0102bd0du;
  config[2] = 0x0103aac3u;
  config[3] = 0x0005012cu;
  config[4] = 0x0101fb02u;

  iVar2 = FUN_010333b4(config);
  if (iVar2 != 0) {
    return iVar2;
  }

  FUN_01033af8(3);
  if (*p3d0 == 2) {
    unsigned char v = p3d4[0];
    FUN_01033acc((unsigned char)(v / 5) + 0x50);
  }
  iVar2 = FUN_010339e4(G1_NET_ESB_ADDR(0x7));
  if (iVar2 == 0) {
    iVar2 = FUN_01033a20(G1_NET_ESB_ADDR(0x3));
    if (iVar2 == 0) {
      iVar2 = FUN_01033a60(G1_NET_ESB_ADDR(0x1), 2);
      if (iVar2 == 0) {
        iVar2 = FUN_01033aac(3);
        if (iVar2 == 0) {
          pE100[0x308] = (unsigned char)iVar2;
          if (param_1 == 1) {
            iVar1 = FUN_01033888();
            if (iVar1 != 0) {
              iVar2 = iVar1;
              if (*p3e8 > 0) {
                printk(0x103d14a);
              }
            }
          }
        }
      }
    }
  }
  return iVar2;
}
