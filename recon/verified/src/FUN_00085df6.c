/* Reconstructed FUN_00085df6 @ 0x85df6 */
#include <stdint.h>

extern int FUN_00085dd2(void *);
extern int FUN_00085c86(void *, uint32_t, uint32_t, uint32_t);

int FUN_00085df6(void *decoder, uint32_t reserved_1,
                 uint32_t reserved_2, uint32_t options)
{
  (void)reserved_1;
  (void)reserved_2;
  uint8_t *restart_pending = (uint8_t *)decoder + 0x10;
  uint32_t restart_value = *restart_pending;

  if (restart_value != 0) {
    if (FUN_00085dd2(decoder) == 0) {
      return 0;
    }
    restart_value = UINT32_MAX;
    options = 0;
    *restart_pending = 0;
  }
  return FUN_00085c86(decoder, 7, restart_value, options);
}
