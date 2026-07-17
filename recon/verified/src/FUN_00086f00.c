/* Reconstructed FUN_00086f00 @ 0x86f00 */
#include <stdarg.h>
#include <stdint.h>

extern uint64_t FUN_00051164(void);
extern int FUN_00077c30(void *, int32_t, uint32_t, va_list);
extern void FUN_00077c78(void *, uint32_t, va_list);
extern int FUN_00079528(uint32_t, int);

void FUN_00086f00(void *context, uint32_t reserved, int32_t count, ...)
{
  (void)reserved;
  va_list arguments;
  va_start(arguments, count);
  uint32_t first = va_arg(arguments, uint32_t);

  if (count < 0) {
    FUN_00077c78(context, first, arguments);
    va_end(arguments);
    return;
  }

  int consumed = FUN_00077c30(context, count, first, arguments);
  va_end(arguments);
  if (consumed < 0 || (uint32_t)consumed < (uint32_t)count) {
    return;
  }

  uint64_t state_pair = FUN_00051164();
  uint32_t value = (uint32_t)state_pair;
  uint8_t *state = (uint8_t *)(uintptr_t)(uint32_t)(state_pair >> 32);
  int adjustment = FUN_00079528(value, *(int16_t *)(state + 0x0e));
  if (adjustment >= 0) {
    *(uint32_t *)(state + 0x54) += (uint32_t)adjustment;
  } else {
    *(uint16_t *)(state + 0x0c) &= (uint16_t)~0x1000u;
  }
}
