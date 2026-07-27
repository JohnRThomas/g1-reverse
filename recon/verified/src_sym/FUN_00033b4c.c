/* Reconstructed FUN_00033b4c @ 0x33b4c  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void DEBUG_PRINT(unsigned long, ...);
extern void debug_print(unsigned long, ...);

void FUN_00033b4c(void)
{
  uint32_t format_string = 0xa7d55UL;
  volatile int32_t *piVar1 = (volatile int32_t*)0x20007554UL /* device_info.is_debug  (device_info_t+0xB58) */;
  int32_t iVar2 = 10;
  volatile uint32_t *puVar3 = (volatile uint32_t*)0x20008eb4UL;
  do {
    if (*piVar1 == 0) {
      DEBUG_PRINT(format_string, (uint32_t)iVar2, puVar3[2], puVar3[0]);
    } else {
      debug_print(format_string, (uint32_t)iVar2, puVar3[2], puVar3[0]);
    }
    iVar2 = iVar2 + 1;
    puVar3 = puVar3 + 0x6d;
  } while (iVar2 != 0x14);
}

