/* CPUNET ESB radio configuration @ 0x0102b31c.
 * Raw back-map: FUN_0102b31c@0x0102b31c; true extent 0xa2.
 * This is the private/product ESB setup called by FUN_0102b718, not an MPSL
 * timeslot function.  The "esb_start_rx fail" diagnostic at runtime address
 * 0x0103d14a anchors the ownership independently of proximity.
 * (parity 300 trials PROVEN)
 */

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

/* Readable source identity; preprocessing preserves the raw parity symbol. */
#define g1_esb_radio_configure FUN_0102b31c

extern int FUN_010333b4(void *);
extern void FUN_01033af8(int);
extern void FUN_01033acc(int);
extern int FUN_010339e4(int);
extern int FUN_01033a20(int);
extern int FUN_01033a60(int, int);
extern int FUN_01033aac(int);
extern int FUN_01033888(void);
extern void FUN_01039722(int);

int g1_esb_radio_configure(int param_1)
{
  volatile int * const p3d0 = (volatile int *)0x210005b4;
  volatile unsigned char * const p3d4 = (volatile unsigned char *)0x21004b9e;
  volatile unsigned char * const pE100 = (volatile unsigned char *)0xe000e100;
  volatile int * const p3e8 = (volatile int *)0x21000580;

  /* Five-word radio configuration assembled from the firmware template at
     RUNTIME address 0x0103c100, with its mode and runtime fields overridden
     below.  The shipped prologue is
         ldr r5,[pc] ; = 0x0103c100      <- a RUNTIME flash pointer
         ldm r5!,{r0,r1,r2,r3} ; stm r4!,{r0,r1,r2,r3}   (config[0..3])
         str  r3,[sp,#8]     -> config[1] = 0x0102bd0d
         strb r3,[sp,#5]     -> config[0] byte 1 = (param_1 != 0)
         strd r2,r3,[sp,#0x10] -> config[3] = 0x0005012c, config[4] = 0x0101fb02
     so only config[0] (bytes 0,2,3) and config[2] survive from the template.

     P4 iteration 24 - COORDINATE-SPACE DEFECT.  The template was previously
     read at ANALYSIS 0x0103c100 (= runtime 0x0103c900) instead of RUNTIME
     0x0103c100 (= analysis 0x0103b900), which yielded
     {0x21002388, .., 0x0103aac3, ..} instead of the real {1, .., 0x201, ..}.
     tools/net_extract.py read_runtime(0x0103c100, 0x10):
         01 00 00 00 | 00 00 00 00 | 01 02 00 00 | 58 02 03 00
     The corrected bytes are self-consistent with the nRF ESB config layout and
     with FUN_010333b4's own reads of the copy at 0x21004a94:
         +0x00 protocol          = 1     (ESB_PROTOCOL_ESB_DPL)
         +0x01 mode              = (param_1 != 0)
         +0x04 event_handler     = 0x0102bd0d
         +0x08 bitrate           = 1
         +0x09 crc               = 2     -> FUN_010333b4 programs CRCPOLY
                                            0x11021 / CRCCNF 2, the 16-bit CRC
         +0x0a tx_output_power   = 0
         +0x0c retransmit_delay  = 0x012c (300 us)
         +0x0e retransmit_count  = 5
         +0x10 tx_mode           = 2
         +0x11 payload_length    = 0xfb  (251, the DPL maximum)
         +0x12 selective_auto_ack= 1
         +0x13 use_fast_ramp_up  = 1     -> RADIO MODECNF0 |= 1
     The stale value made saved[0] = 0x88 and saved[9] = 0xaa, so
     FUN_010333b4 took NEITHER packet-configuration branch (measured in
     iteration 23: the callback slot was never written and the RADIO PCNF
     registers were never programmed) and no ESB frame could be keyed. */
  uint32_t config[5];
  int iVar2;
  int iVar1;

  config[0] = 0x00000001u | ((param_1 != 0) ? 0x100u : 0u);
  config[1] = 0x0102bd0du;
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
                FUN_01039722(0x103d14a);
              }
            }
          }
        }
      }
    }
  }
  return iVar2;
}
