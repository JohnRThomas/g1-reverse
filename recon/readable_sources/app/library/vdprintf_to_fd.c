#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00086f00 @ 0x00086f00
 * public-name: vdprintf_to_fd
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   fortify_chk_fail                         <= FUN_00051164 @ 0x00051164
 *   vsnprintf_impl                           <= FUN_00077c30 @ 0x00077c30
 *   vsprintf_impl                            <= FUN_00077c78 @ 0x00077c78
 *   write_r_capture_errno                    <= FUN_00079528 @ 0x00079528
 *   vdprintf_to_fd                           <= FUN_00086f00 @ 0x00086f00
 */
/* Reconstructed FUN_00086f00 @ 0x86f00 */
#include <stdarg.h>
#include <stdint.h>

extern uint64_t fortify_chk_fail(void);
extern int vsnprintf_impl(void *, int32_t, uint32_t, va_list);
extern void vsprintf_impl(void *, uint32_t, va_list);
extern int write_r_capture_errno(uint32_t, int);

void vdprintf_to_fd(void *context, uint32_t reserved, int32_t count, ...)
{
  (void)reserved;
  va_list arguments;
  va_start(arguments, count);
  uint32_t first = va_arg(arguments, uint32_t);

  if (count < 0) {
    vsprintf_impl(context, first, arguments);
    va_end(arguments);
    return;
  }

  int consumed = vsnprintf_impl(context, count, first, arguments);
  va_end(arguments);
  if (consumed < 0 || (uint32_t)consumed < (uint32_t)count) {
    return;
  }

  uint64_t state_pair = fortify_chk_fail();
  uint32_t value = (uint32_t)state_pair;
  uint8_t *state = (uint8_t *)(uintptr_t)(uint32_t)(state_pair >> 32);
  int adjustment = write_r_capture_errno(value, *(int16_t *)(state + 0x0e));
  if (adjustment >= 0) {
    *(uint32_t *)(state + 0x54) += (uint32_t)adjustment;
  } else {
    *(uint16_t *)(state + 0x0c) &= (uint16_t)~0x1000u;
  }
}
