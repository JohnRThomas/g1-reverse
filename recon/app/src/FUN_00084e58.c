/* Reconstructed FUN_00084e58 @ 0x84e58 */
#include <stdint.h>

extern void FUN_00084e44(uintptr_t, uint32_t, uint32_t);

void FUN_00084e58(uintptr_t peripheral)
{
  uint32_t buffer =
      (*(volatile uint32_t *)(peripheral + 8) - 0x18u) & ~7u;
  FUN_00084e44(peripheral, buffer, 1);
}
