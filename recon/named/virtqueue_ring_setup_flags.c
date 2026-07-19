/* readable reconstruction; identity: FUN_000857b2 @ 0x000857b2
 * public-name: virtqueue_ring_setup_flags
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   virtqueue_ring_setup_flags               <= FUN_000857b2 @ 0x000857b2
 */
/* Reconstructed FUN_000857b2 @ 0x857b2  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
void virtqueue_ring_setup_flags(int32_t *param_1)
{
  int32_t iVar1;
  iVar1 = *(int32_t*)(*param_1 + 0x18);
  if ((*(int32_t*)(*param_1+0x10) << 2) < 0) {
    if (iVar1==0) {
      *(int16_t*)(param_1[7] + param_1[5]*2 + 4) =
        (int16_t)((*(int16_t*)((char*)param_1+0x2e) - 1) - *(int16_t*)((char*)param_1+10));
      return;
    }
  } else if (iVar1==0) {
    *(uint16_t*)param_1[7] |= 1;
  }
}
