/* Reconstructed SlaveDoubleClickEventInject @ 0x48ad4 */
#include <stdint.h>

extern void *FUN_00086c78(void *, int, uint32_t);
extern int FUN_000720d0(uint32_t, const void *, uint32_t, uint32_t);
extern void DEBUG_PRINT(uint32_t, uint32_t);
extern void FUN_00019c70(uint32_t, uint32_t);

int SlaveDoubleClickEventInject(void)
{
  uint8_t event[24];
  FUN_00086c78(event + 1, 0, 23);
  event[0] = 7;

  if (FUN_000720d0(0x2000392c, event, 0, 0) != 0) {
    DEBUG_PRINT(0x000ef058, 0x000ef694);
    return -1;
  }
  if (*(volatile int32_t *)0x2000230c > 2) {
    if (*(volatile uint32_t *)0x20007554 == 0) {
      DEBUG_PRINT(0x000ef644, 0x000ef694);
    } else {
      FUN_00019c70(0x000ef644, 0x000ef694);
    }
  }
  return 0;
}
