#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00086380 @ 0x00086380
 * public-name: FUN_00086380
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   buffer_pool_freelist_init                <= FUN_00085cf2 @ 0x00085cf2
 */
/* Tail thunk @ 0x86380. */
extern int buffer_pool_freelist_init(int,int,int,int); int thunk_FUN_00085cf2_b(int a,int b,int c,int d){return buffer_pool_freelist_init(a,b,c,d);}
