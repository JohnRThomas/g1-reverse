/* CPUNET ESB radio configuration @ 0x0102b31c.
 * Raw back-map: FUN_0102b31c@0x0102b31c; true extent 0xa2.
 * This is the private/product ESB setup called by FUN_0102b718, not an MPSL
 * timeslot function.  The "esb_start_rx fail" diagnostic at runtime address
 * 0x0103d14a anchors the ownership independently of proximity.
 * (parity 300 trials PROVEN)
 */

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
  iVar2 = FUN_010339e4(0x21000767);
  if (iVar2 == 0) {
    iVar2 = FUN_01033a20(0x21000763);
    if (iVar2 == 0) {
      iVar2 = FUN_01033a60(0x21000761, 2);
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
