/* readable reconstruction; identity: FUN_00082cb6 @ 0x00082cb6
 * public-name: thunk_FUN_000823fa
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_att_get_mtu                           <= FUN_000823fa @ 0x000823fa
 */
/* Tail thunk @ 0x82cb6. */
extern int bt_att_get_mtu(int,int,int,int); int thunk_FUN_000823fa(int a,int b,int c,int d){return bt_att_get_mtu(a,b,c,d);}
