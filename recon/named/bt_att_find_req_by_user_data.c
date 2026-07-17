/* readable reconstruction; identity: FUN_0008253a @ 0x0008253a
 * public-name: bt_att_find_req_by_user_data
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   att_get                                  <= FUN_0005858c @ 0x0005858c
 *   bt_att_find_req_by_user_data             <= FUN_0008253a @ 0x0008253a
 */
/* Reconstructed FUN_0008253a @ 0x8253a  (parity: 300/300 trials, PROVEN) */

extern int *att_get(void);

int *bt_att_find_req_by_user_data(unsigned int param_1, int param_2)
{
  int *piVar1;
  int *piVar2;
  piVar1 = att_get();
  if (piVar1 != 0) {
    for (piVar2 = *(int **)((char *)piVar1 + 0x30); piVar2 != 0; piVar2 = (int *)*piVar2) {
      if (*(int *)(piVar2[-0x1b] + 0x18) == param_2) {
        return (int *)piVar2[-0x1b];
      }
    }
    for (piVar1 = *(int **)((char *)piVar1 + 4); piVar1 != 0 && piVar1[6] != param_2; piVar1 = (int *)*piVar1) {}
  }
  return piVar1;
}
