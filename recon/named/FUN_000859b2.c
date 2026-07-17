/* readable reconstruction; identity: FUN_000859b2 @ 0x000859b2
 * public-name: FUN_000859b2
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   k_sem_give                               <= FUN_00072880 @ 0x00072880
 */
/* Tail thunk @ 0x859b2. */
extern int k_sem_give(int,int,int,int); int thunk_FUN_00072880(int a,int b,int c,int d){return k_sem_give(a,b,c,d);}
