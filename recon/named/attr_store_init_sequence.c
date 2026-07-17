/* readable reconstruction; identity: FUN_00030288 @ 0x00030288
 * public-name: attr_store_init_sequence
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   attr_store_set                           <= FUN_00030178 @ 0x00030178
 *   attr_store_init_sequence                 <= FUN_00030288 @ 0x00030288
 * address symbols (name @ address):
 *   rodata_ff20                              @ 0x0000ff20
 */
/* Reconstructed FUN_00030288 @ 0x30288  (parity: 300/300 trials, PROVEN) */

extern int attr_store_set(int a, int b);
int attr_store_init_sequence(int param_1)
{
  int iVar1;
  iVar1 = attr_store_set(0xff20, 0x3c00f091);
  if (iVar1 == 0 && (iVar1 = attr_store_set(0x4820, 6), iVar1 == 0)) {
    iVar1 = 0;
    if (param_1 == 0) {
      iVar1 = attr_store_set(0x4794, 0x5a637955);
      if (iVar1 != 0) {
        iVar1 = 1;
      }
      iVar1 = -iVar1;
    }
  } else {
    iVar1 = -1;
  }
  return iVar1;
}
