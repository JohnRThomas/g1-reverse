/* readable reconstruction; identity: FUN_0004f518 @ 0x0004f518
 * public-name: gatt_notify_config_change
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gatt_notify_config_change                <= FUN_0004f518 @ 0x0004f518
 *   gatt_find_ccc_for_conn                   <= FUN_0005b0dc @ 0x0005b0dc
 *   bt_gatt_notify_cb                        <= FUN_0005b754 @ 0x0005b754
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_4f4f1                             @ 0x0004f4f1
 *   rodata_8ad40                             @ 0x0008ad40
 */
/* Reconstructed FUN_0004f518 @ 0x4f518  (parity: 300/300 trials, PROVEN) */

extern void memset_bytes(void*,int,int);
extern int gatt_find_ccc_for_conn(int,int,int);
extern int bt_gatt_notify_cb(int, int*);

int gatt_notify_config_change(int param_1, int param_2, short param_3)
{
    unsigned char buf[24];
    int iVar2;
    memset_bytes(buf, 0, 0x18);
    *(int*)(buf+4) = 0x0008ad40;
    *(int*)(buf+8) = param_2;
    *(short*)(buf+0xc) = param_3;
    *(int*)(buf+0x10) = 0x0004f4f1;
    if (param_1 == 0 || ((iVar2 = gatt_find_ccc_for_conn(param_1, 0x0008ad40, 1)), iVar2 != 0)) {
        return bt_gatt_notify_cb(param_1, buf);
    } else {
        return 0xffffffea;
    }
}
