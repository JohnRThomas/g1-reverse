#include "g1_net_symbols.h"
/* net-core FUN_0100a790 @ 0x100a790  (parity 300 trials PROVEN) */

extern void FUN_0100a718(void);
extern void FUN_0100a760(void);
extern void FUN_0100a7cc(void);
void FUN_0100a790(void) {
  FUN_0100a718();
  FUN_0100a760();
  FUN_0100a7cc();
  *(volatile unsigned int *)(0x4100f000 + 0x508) = 0x1ff8;
}
