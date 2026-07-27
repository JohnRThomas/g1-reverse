/* readable reconstruction; identity: FUN_0007d02a @ 0x0007d02a
 * public-name: attr_configure_pair_with_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   attr_store_set                           <= FUN_00030178 @ 0x00030178
 *   attr_store_init_sequence                 <= FUN_00030288 @ 0x00030288
 *   attr_configure_pair                      <= FUN_0007cfdc @ 0x0007cfdc
 *   attr_configure_pair_with_init            <= FUN_0007d02a @ 0x0007d02a
 */
/* Reconstructed FUN_0007d02a @ 0x7d02a  (parity: 300/300 trials, PROVEN) */

extern int attr_store_init_sequence(int);
extern int attr_configure_pair(unsigned int, unsigned int);
extern int attr_store_set(unsigned int, unsigned int);

int attr_configure_pair_with_init(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
  int iVar1;
  iVar1 = attr_store_init_sequence(param_3);
  if (iVar1 == 0 && (iVar1 = attr_configure_pair(param_1, param_2)) == 0) {
    iVar1 = attr_store_set(0x4820, 4);
    if (iVar1 != 0) iVar1 = 1;
    iVar1 = -iVar1;
  } else {
    iVar1 = -1;
  }
  return iVar1;
}
