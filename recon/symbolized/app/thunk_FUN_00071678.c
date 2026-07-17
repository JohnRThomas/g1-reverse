#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000807f2 @ 0x000807f2
 * public-name: thunk_FUN_00071678
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   __errno_location                         <= FUN_00071678 @ 0x00071678
 */
/* Tail thunk @ 0x807f2. */
extern int __errno_location(int,int,int,int); int thunk_FUN_00071678(int a,int b,int c,int d){return __errno_location(a,b,c,d);}
