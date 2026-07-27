/* readable reconstruction; identity: FUN_0007f5ee @ 0x0007f5ee
 * public-name: bt_ancs_cp_write_callback
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   atomic_clear_bit                         <= FUN_0007f5d8 @ 0x0007f5d8
 *   bt_ancs_cp_write_callback                <= FUN_0007f5ee @ 0x0007f5ee
 */
/* Reconstructed FUN_0007f5ee @ 0x7f5ee  (parity: 300/300 trials, PROVEN) */

typedef void (*fn_t)(int, unsigned int);
extern void atomic_clear_bit(volatile int *, int);

void bt_ancs_cp_write_callback(unsigned int param_1, unsigned int param_2, int param_3)
{
  fn_t UNRECOVERED_JUMPTABLE = *(fn_t volatile *)(param_3 + 0x10);
  atomic_clear_bit(param_3 - 0x10, 2);
  if (UNRECOVERED_JUMPTABLE != 0) {
    UNRECOVERED_JUMPTABLE(param_3 - 0x14, param_2);
  }
}
