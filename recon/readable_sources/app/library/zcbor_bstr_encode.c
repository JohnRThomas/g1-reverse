#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_zcbor_state_t__param_0174              [param_0174; library]
 * Raw function identity: 0x00086338.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00086338 @ 0x00086338
 * public-name: zcbor_bstr_encode
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   zcbor_str_encode                         <= FUN_00086228 @ 0x00086228
 *   zcbor_bstr_encode                        <= FUN_00086338 @ 0x00086338
 */
/* Two-mode wrapper FUN_00086338 @ 0x86338. */
extern int zcbor_str_encode(int,int,int,int); int zcbor_bstr_encode(int a,int b,int c,int d){return zcbor_str_encode(a,b,2,d);}
