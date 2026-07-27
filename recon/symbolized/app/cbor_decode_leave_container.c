#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00085df6 @ 0x00085df6
 * public-name: cbor_decode_leave_container
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   zcbor_process_backup                     <= FUN_00085c86 @ 0x00085c86
 *   cbor_decode_expect_break                 <= FUN_00085dd2 @ 0x00085dd2
 *   cbor_decode_leave_container              <= FUN_00085df6 @ 0x00085df6
 */
/* Reconstructed FUN_00085df6 @ 0x85df6 */
#include <stdint.h>

extern int cbor_decode_expect_break(unsigned int*);
extern int zcbor_process_backup(void *, uint32_t, uint32_t, uint32_t);

int cbor_decode_leave_container(void *decoder, uint32_t reserved_1,
                 uint32_t reserved_2, uint32_t options)
{
  (void)reserved_1;
  (void)reserved_2;
  uint8_t *restart_pending = (uint8_t *)decoder + 0x10;
  uint32_t restart_value = *restart_pending;

  if (restart_value != 0) {
    if (cbor_decode_expect_break(decoder) == 0) {
      return 0;
    }
    restart_value = UINT32_MAX;
    options = 0;
    *restart_pending = 0;
  }
  return zcbor_process_backup(decoder, 7, restart_value, options);
}
