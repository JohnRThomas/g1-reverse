/* readable reconstruction; identity: FUN_00056908 @ 0x00056908
 * public-name: ble_conn_lookup_masked
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ble_conn_unref                           <= FUN_000566a4 @ 0x000566a4
 *   ble_conn_lookup_masked                   <= FUN_00056908 @ 0x00056908
 *   bt_conn_call_4arg_zero                   <= FUN_000813ca @ 0x000813ca
 *   conn_lookup_handle                       <= FUN_000813e8 @ 0x000813e8
 * address symbols (name @ address):
 *   log_module_bt_conn                       @ 0x00088108
 *   rodata_f3c7b                             @ 0x000f3c7b
 *   g_ble_conn_pool                          @ 0x20006138
 */
/* Reconstructed FUN_00056908 @ 0x56908  (parity: 300/300 trials, PROVEN) */

extern int conn_lookup_handle(unsigned int a, unsigned int b, unsigned int c);
extern void bt_conn_call_4arg_zero(unsigned int, unsigned int, unsigned int);
extern void ble_conn_unref(int a);

int ble_conn_lookup_masked(unsigned int param_1, unsigned char param_2, unsigned int param_3, unsigned int param_4)
{
  int iVar1;
  unsigned int local_28;
  unsigned int local_24;
  unsigned int uStack_20;
  unsigned int uStack_18;

  uStack_18 = param_4;
  iVar1 = conn_lookup_handle(0x20006138, 1, param_1);
  if (iVar1 != 0) {
    if ((param_2 & *(volatile unsigned char *)(iVar1 + 2)) != 0) {
      return iVar1;
    }
    local_24 = 0xf3c7b;
    local_28 = 3;
    uStack_20 = param_1;
    bt_conn_call_4arg_zero(0x88108, 0x1880, &local_28);
    ble_conn_unref(iVar1);
  }
  return 0;
}
