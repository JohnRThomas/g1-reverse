#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_cjson_printbuffer__param_0321          [param_0321; library]
 * Raw function identity: 0x00084f16.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00084f16 @ 0x00084f16
 * public-name: cursor_advance_past_cstring
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   strlen                                   <= FUN_0000ef12 @ 0x0000ef12
 *   cursor_advance_past_cstring              <= FUN_00084f16 @ 0x00084f16
 */
/* Reconstructed FUN_00084f16 @ 0x84f16  (parity: 300/300 trials, PROVEN) */

extern int strlen(int a);
void cursor_advance_past_cstring(int *param_1) {
    if (param_1 != (int*)0 && *param_1 != 0) {
        int iVar2 = param_1[2];
        int iVar1 = strlen(*param_1 + iVar2);
        param_1[2] = iVar2 + iVar1;
    }
}
