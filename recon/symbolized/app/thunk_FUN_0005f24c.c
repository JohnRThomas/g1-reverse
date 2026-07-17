#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00080ae2 @ 0x00080ae2
 * public-name: thunk_FUN_0005f24c
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   net_buf_unref                            <= FUN_0005f24c @ 0x0005f24c
 */
/* Tail thunk @ 0x80ae2. */
extern int net_buf_unref(int,int,int,int); int thunk_FUN_0005f24c(int a,int b,int c,int d){return net_buf_unref(a,b,c,d);}
