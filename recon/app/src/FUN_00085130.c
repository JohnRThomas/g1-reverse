/* Reconstructed FUN_00085130 @ 0x85130 */
#include <stdint.h>

extern uintptr_t FUN_00065584(uint32_t *);

void FUN_00085130(uint32_t channel,
                  const uint8_t *enable,
                  const uint8_t *polarity,
                  const uint8_t *drive,
                  const uint8_t *pull,
                  const uint8_t *sense)
{
  uint32_t index = channel;
  uintptr_t table = FUN_00065584(&index);
  volatile uint32_t *configuration =
      (volatile uint32_t *)(table + index * 4 + 0x200);

  uint32_t clear_mask = 0;
  if (enable != 0) {
    clear_mask |= 1;
  }
  if (polarity != 0) {
    clear_mask |= 2;
  }
  if (drive != 0) {
    clear_mask |= 0x0c;
  }
  if (pull != 0) {
    clear_mask |= 0x0f00;
  }
  if (sense != 0) {
    clear_mask |= 0x30000;
  }

  uint32_t value = *configuration & ~clear_mask;
  if (enable != 0) {
    value |= *enable;
  }
  if (polarity != 0) {
    value |= (uint32_t)*polarity << 1;
  }
  if (drive != 0) {
    value |= (uint32_t)*drive << 2;
  }
  if (pull != 0) {
    value |= (uint32_t)*pull << 8;
  }
  if (sense != 0) {
    value |= (uint32_t)*sense << 16;
  }
  *configuration = value;
}
