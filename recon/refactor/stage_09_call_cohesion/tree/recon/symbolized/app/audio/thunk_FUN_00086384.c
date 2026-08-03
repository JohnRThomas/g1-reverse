#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000850d8 @ 0x000850d8
 * public-name: thunk_FUN_00086384
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   delay_scaled_busy_wait                   <= FUN_00086384 @ 0x00086384
 */
/* Tail thunk @ 0x850d8. */
extern int delay_scaled_busy_wait(int,int,int,int); int thunk_FUN_00086384(int a,int b,int c,int d){return delay_scaled_busy_wait(a,b,c,d);}
