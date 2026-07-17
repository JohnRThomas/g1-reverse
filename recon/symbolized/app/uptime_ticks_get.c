#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00086698 @ 0x00086698
 * public-name: uptime_ticks_get
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   k_uptime_ticks_impl                      <= FUN_00074f68 @ 0x00074f68
 */
/* Tail thunk @ 0x86698. */
extern int k_uptime_ticks_impl(int,int,int,int); int thunk_FUN_00074f68(int a,int b,int c,int d){return k_uptime_ticks_impl(a,b,c,d);}
