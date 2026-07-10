/* named: FUN_00080ab4 */
/* Reconstructed FUN_00080ab4 @ 0x80ab4  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern uint32_t thunk_FUN_000727ac(int, uint32_t, uint32_t, uint32_t);
extern void smp_process_request_packet(void*, uint32_t);

void FUN_00080ab4(int param_1, uint32_t param_2)
{
  uint32_t iVar1;
  uint8_t stackA[56];
  uint8_t stackB[100];
  while ((iVar1 = thunk_FUN_000727ac(param_1+0x10, param_2, 0, 0)) != 0) {
    uint32_t local[3];
    local[0] = (uint32_t)param_1;
    local[1] = (uint32_t)(uintptr_t)stackB;
    local[2] = (uint32_t)(uintptr_t)stackA;
    smp_process_request_packet(local, iVar1);
    param_2 = iVar1;
  }
}

