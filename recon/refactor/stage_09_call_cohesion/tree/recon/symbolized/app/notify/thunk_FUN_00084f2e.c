#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00085042 @ 0x00085042
 * public-name: thunk_FUN_00084f2e
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   sllist_insert_after                      <= FUN_00084f2e @ 0x00084f2e
 */
/* Tail thunk @ 0x85042. */
extern int sllist_insert_after(int,int,int,int); int thunk_FUN_00084f2e(int a,int b,int c,int d){return sllist_insert_after(a,b,c,d);}
