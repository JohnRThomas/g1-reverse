/* readable reconstruction; identity: FUN_00080c46 @ 0x00080c46
 * public-name: conn_le_param_update_submit
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   active_transfer_conn_match               <= FUN_000527dc @ 0x000527dc
 *   k_work_reschedule                        <= FUN_0007350c @ 0x0007350c
 *   k_work_cancel_delayable                  <= FUN_00073518 @ 0x00073518
 *   conn_le_param_update_submit              <= FUN_00080c46 @ 0x00080c46
 *   bt_conn_le_param_update                  <= FUN_0008157a @ 0x0008157a
 */
/* Reconstructed FUN_00080c46 @ 0x80c46  (parity: 300/300 trials, PROVEN) */

extern int active_transfer_conn_match(void);
extern long long bt_conn_le_param_update(unsigned int);
extern void k_work_reschedule(int, int, unsigned int, unsigned int);
extern void k_work_cancel_delayable(int);

void conn_le_param_update_submit(unsigned int param_1)
{
  int iVar1;
  long long uVar2;
  iVar1 = active_transfer_conn_match();
  if (iVar1 == 0) return;
  uVar2 = bt_conn_le_param_update(param_1);
  if ((int)uVar2 != 0 && (int)uVar2 != -0x78) {
    k_work_reschedule(iVar1 + 0x38, (int)(uVar2 >> 32), 0x8000, 0);
    return;
  }
  k_work_cancel_delayable(iVar1 + 0x38);
}
