/* readable reconstruction; identity: FUN_0008661e @ 0x0008661e
 * public-name: k_work_delayable_busy_get
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   k_work_busy_get                          <= FUN_00072e9c @ 0x00072e9c
 */
/* Tail thunk @ 0x8661e. */
extern int k_work_busy_get(int,int,int,int); int k_work_delayable_busy_get(int a,int b,int c,int d){return k_work_busy_get(a,b,c,d);}
