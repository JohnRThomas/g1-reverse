#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00084fd4 @ 0x00084fd4
 * public-name: alloc_zeroed_node
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   alloc_zeroed_node                        <= FUN_00084fd4 @ 0x00084fd4
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 */
/* Reconstructed FUN_00084fd4 @ 0x84fd4  (parity: 300/300 trials, PROVEN) */

extern void memset_bytes(int a, int b, int c);
typedef int (*fnptr)(int);
int alloc_zeroed_node(fnptr param_1) {
    int iVar1 = param_1(0x28);
    if (iVar1 != 0) {
        memset_bytes(iVar1, 0, 0x28);
    }
    return iVar1;
}
