#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0102b31c @ 0x0102b31c
 * public-name: FUN_0102b31c
 * durable-map: recon/catalogs/function_names_net.json
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

#include <stdint.h>

extern int FUN_010333b4(void *);
extern void FUN_01033af8(int);
extern void FUN_01033acc(int);
extern int FUN_010339e4(int);
extern int FUN_01033a20(int);
extern int FUN_01033a60(int, int);
extern int FUN_01033aac(int);
extern int FUN_01033888(void);
extern void FUN_01039722(int);

int FUN_0102b31c(int param_1)
{
  volatile int * const p3d0 = (volatile int *)((unsigned long)&g_net_radio_op_state) /*=0x210005b4*/;
  volatile unsigned char * const p3d4 = (volatile unsigned char *)((unsigned long)&g_net_radio_temp_raw) /*=0x21004b9e*/;
  volatile unsigned char * const pE100 = (volatile unsigned char *)0xe000e100;
  volatile int * const p3e8 = (volatile int *)((unsigned long)&g_zephyr_log_level) /*=0x21000580*/;

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
  iVar2 = FUN_010339e4(((unsigned long)&g_net_radio_sched_param_c) /*=0x21000767*/);
  if (iVar2 == 0) {
    iVar2 = FUN_01033a20(((unsigned long)&g_net_radio_sched_param_b) /*=0x21000763*/);
    if (iVar2 == 0) {
      iVar2 = FUN_01033a60(((unsigned long)&g_net_radio_sched_param_a) /*=0x21000761*/, 2);
      if (iVar2 == 0) {
        iVar2 = FUN_01033aac(3);
        if (iVar2 == 0) {
          pE100[0x308] = (unsigned char)iVar2;
          if (param_1 == 1) {
            iVar1 = FUN_01033888();
            if (iVar1 != 0) {
              iVar2 = iVar1;
              if (*p3e8 > 0) {
                FUN_01039722(((unsigned long)&rodata_103d14a) /*=0x103d14a*/);
              }
            }
          }
        }
      }
    }
  }
  return iVar2;
}
