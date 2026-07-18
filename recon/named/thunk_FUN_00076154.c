/* readable reconstruction; identity: FUN_000869c2 @ 0x000869c2
 * public-name: thunk_FUN_00076154
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   __ieee754_atan2f                         <= FUN_00076154 @ 0x00076154
 */
/* Tail thunk @ 0x869c2. */
extern int __ieee754_atan2f(int,int,int,int); int thunk_FUN_00076154(int a,int b,int c,int d){return __ieee754_atan2f(a,b,c,d);}
