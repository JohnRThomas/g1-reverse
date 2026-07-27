/* Reconstructed cleanDashBoardStartUpModeInfo @ 0x23c88 */
#include <stdint.h>

extern void DEBUG_PRINT(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);
extern int FUN_000720d0(uint32_t, const void *, uint32_t, uint32_t);
extern void FUN_00072880(uint32_t);

struct startup_request {
  uint8_t opcode;
  uint8_t reserved[5];
};

int cleanDashBoardStartUpModeInfo(void)
{
  const struct startup_request request = { .opcode = 4 };
  if (FUN_000720d0(0x20003994, &request, 0, 0) != 0) {
    if (*(volatile int32_t *)0x2000230c > 0) {
      if (*(volatile uint32_t *)0x20007554 == 0) {
        DEBUG_PRINT(0x0009e903, 0x0009ed4a);
      } else {
        FUN_00019c70(0x0009e903, 0x0009ed4a);
      }
    }
    return -1;
  }

  if (*(volatile int32_t *)0x2000230c > 2) {
    if (*(volatile uint32_t *)0x20007554 == 0) {
      DEBUG_PRINT(0x0009e968, 0x0009ed4a);
    } else {
      FUN_00019c70(0x0009e968, 0x0009ed4a);
    }
  }
  FUN_00072880(0x200079e4);
  return 0;
}
