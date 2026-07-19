/* readable reconstruction; identity: FUN_000861aa @ 0x000861aa
 * public-name: FUN_000861aa
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   buffer_pool_freelist_init                <= FUN_00085cf2 @ 0x00085cf2
 */
/* Tail thunk @ 0x861aa. */
extern int buffer_pool_freelist_init(int,int,int,int); int thunk_FUN_00085cf2_a(int a,int b,int c,int d){return buffer_pool_freelist_init(a,b,c,d);}
