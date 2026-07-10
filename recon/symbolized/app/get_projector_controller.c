#include "g1_app_symbols.h"
/* named: get_projector_controller */
/* Reconstructed get_projector_controller @ 0x7d4ec  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int get_device_info(void);
int get_projector_controller(void)
{
  int iVar1;
  iVar1 = get_device_info();
  return iVar1 + 0xb6c;
}

