/* Reconstructed burial_point_record_info_init @ 0x4ab3c */
#include <stdint.h>

extern void DEBUG_PRINT(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);
extern uint8_t *FUN_000167a8(void);
extern void *FUN_00086c78(void *, int, uint32_t);

void burial_point_record_info_init(void)
{
  if (*(volatile int32_t *)0x2000230c > 2) {
    if (*(volatile uint32_t *)0x20007554 == 0) {
      DEBUG_PRINT(0x000f0416, 0x000f043b);
    } else {
      FUN_00019c70(0x000f0416, 0x000f043b);
    }
  }

  uint8_t *runtime = FUN_000167a8();
  FUN_00086c78(runtime + 0x1092, 0, 0x1a);
  runtime = FUN_000167a8();
  FUN_00086c78(runtime + 0x10ac, 0, 0x1a);
}
