/* readable reconstruction; identity: FUN_00082258 @ 0x00082258
 * public-name: att_write_cmd
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gatt_notify_or_indicate                  <= FUN_00058c34 @ 0x00058c34
 *   att_write_cmd                            <= FUN_00082258 @ 0x00082258
 *   net_buf_simple_pull_le16                 <= FUN_00083718 @ 0x00083718
 */
/* Reconstructed FUN_00082258 @ 0x82258  (parity: 300/300 trials, PROVEN) */

extern void gatt_notify_or_indicate(int,int,int,int,int,int,short);
extern int net_buf_simple_pull_le16(int);
void att_write_cmd(int param_1,int param_2)
{
    int uVar1 = net_buf_simple_pull_le16(param_2 + 0xc);
    gatt_notify_or_indicate(param_1,0,0,uVar1,0,*(int*)(param_2+0xc),*(short*)(param_2+0x10));
}
