/* readable reconstruction; identity: FUN_00082712 @ 0x00082712
 * public-name: gatt_foreach_iter
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_uuid_cmp                              <= FUN_00080d3e @ 0x00080d3e
 *   gatt_foreach_iter                        <= FUN_00082712 @ 0x00082712
 */
/* Reconstructed FUN_00082712 @ 0x82712  (parity: 300/300 trials, PROVEN) */

typedef unsigned int (*fn8_82712)(void*, unsigned int, unsigned int);
extern int bt_uuid_cmp(int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);

unsigned int gatt_foreach_iter(unsigned int *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4, int param_5, int param_6, short *param_7, fn8_82712 param_8, unsigned int param_9)
{
  unsigned int uVar1;
  int iVar2;

  if (param_2 <= param_4) {
    if (((param_2 < param_3) ||
        ((param_5 != 0) &&
         (iVar2 = bt_uuid_cmp(param_5,*param_1,param_3,param_4,param_4), iVar2 != 0))) ||
       ((param_6 != 0) && ((int)param_1[3] != param_6))) {
      return 1;
    }
    *param_7 = *param_7 - 1;
    uVar1 = (*param_8)(param_1,param_2,param_9);
    if (*param_7 != 0) {
      return uVar1;
    }
  }
  return 0;
}
