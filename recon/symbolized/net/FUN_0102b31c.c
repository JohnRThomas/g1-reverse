#include "g1_net_symbols.h"
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

#include <stdint.h>
#include "../../headers/g1_nrf_regs.h"
#include "../../headers/g1_log.h"

extern int FUN_010333b4(void *);
extern void FUN_01033af8(int);
extern void FUN_01033acc(int);
extern int FUN_010339e4(int);
extern int FUN_01033a20(int);
extern int FUN_01033a60(int, int);
extern int FUN_01033aac(int);
extern int FUN_01033888(void);

int FUN_0102b31c(int param_1)
{
  volatile int * const p3d0 = (volatile int *)((unsigned long)&g_net_radio_op_state) /*=0x210005b4*/;
  volatile unsigned char * const p3d4 = (volatile unsigned char *)((unsigned long)&g_net_radio_temp_raw) /*=0x21004b9e*/;
  volatile unsigned char * const pE100 = (volatile unsigned char *)G1_NVIC_ISER0;
  volatile int * const p3e8 = (volatile int *)((unsigned long)&g_zephyr_log_level) /*=0x21000580*/;

  /* Five-word radio configuration assembled from the firmware template at
     RUNTIME address 0x0103c100 (= analysis 0x0103b900), with its mode and
     runtime fields overridden below.  Shipped prologue:
         ldr r5,[pc] ; = 0x0103c100  (a RUNTIME flash pointer)
         ldm r5!,{r0,r1,r2,r3} ; stm r4!,{r0,r1,r2,r3}    -> config[0..3]
         str  r3,[sp,#8]       -> config[1] = 0x0102bd0d  (event handler)
         strb r3,[sp,#5]       -> config[0] byte 1 = (param_1 != 0)  (mode)
         strd r2,r3,[sp,#0x10] -> config[3] = 0x0005012c, config[4] = 0x0101fb02
     Only config[0] bytes 0/2/3 and config[2] survive from the template.

     P4 iteration 24 - COORDINATE-SPACE DEFECT (the class tools/NET_PLAYBOOK.md
     warns about).  The template had been read at ANALYSIS 0x0103c100 instead of
     RUNTIME 0x0103c100, giving {0x21002388, _, 0x0103aac3, _} in place of the
     real {0x00000001, _, 0x00000201, _}
     (net_extract.read_runtime(0x0103c100,0x10) = 01 00 00 00 00 00 00 00
      01 02 00 00 58 02 03 00).  Consequence, measured in iteration 23:
     FUN_010333b4 saw saved[0] = 0x88 (not the ESB protocol 1 = DPL) and
     saved[9] = 0xaa (not the CRC selector 2), so it took NEITHER packet-config
     branch, never wrote the RADIO packet-configuration callback slot, never
     programmed CRCCNF/CRCPOLY, and no ESB frame was ever keyed.
     The corrected bytes reproduce the nRF ESB `struct esb_config` exactly:
       +0x00 protocol=1(DPL) +0x01 mode +0x04 event_handler +0x08 bitrate=1
       +0x09 crc=2(16-bit, matches the 0x11021 poly FUN_010333b4 programs)
       +0x0a tx_output_power=0 +0x0c retransmit_delay=300us +0x0e count=5
       +0x10 tx_mode=2 +0x11 payload_length=0xfb(251, DPL max)
       +0x12 selective_auto_ack=1 +0x13 use_fast_ramp_up=1 */
  uint32_t config[5];
  int iVar2;
  int iVar1;

  config[0] = 0x00000001u | ((param_1 != 0) ? 0x100u : 0u);
#ifdef G1_COHESIVE_BUILD
  /* P4 iteration 24 - CODE POINTER.  0x0102bd0d is a RUNTIME Thumb pointer;
     runtime->analysis is -0x800, so it is (0x0102b50c | 1) = FUN_0102b50c, the
     ESB event handler, recovered this iteration from the Ghidra gap
     0x0102b488..0x0102b50c and proven at 400/400 directed trials.  Left as the
     shipped literal the relocated build hands the ESB driver an address inside
     unrelated code: measured, the announcement was transmitted ONCE and never
     re-armed, because event id 1 (TX success) is what calls
     FUN_0102b3f0(0) -> esb_start_tx again.  Parity keeps the literal. */
  extern void FUN_0102b50c(const void *event);
  config[1] = (uint32_t)(unsigned long)&FUN_0102b50c;
#else
  config[1] = 0x0102bd0du;
#endif
  config[2] = 0x00000201u;
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
                printk(((unsigned long)&rodata_103d14a) /*=0x103d14a*/);
              }
            }
          }
        }
      }
    }
  }
  return iVar2;
}
