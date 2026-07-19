#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_dev_channel_desc__param_0663           [param_0663; G1-original]
 * Raw function identity: 0x00084068.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00084068 @ 0x00084068
 * public-name: dev_channel_dispatch_range
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   dev_channel_dispatch_range               <= FUN_00084068 @ 0x00084068
 */
/* Reconstructed FUN_00084068 @ 0x84068  (parity: 300/300 trials, PROVEN) */

int dev_channel_dispatch_range(int *param_1, int param_2, int param_3)
{
    int *r6 = *(int**)((char*)param_1 + 4);
    unsigned int fptr = *(volatile unsigned int*)((char*)(*(volatile int*)((char*)param_1 + 8)) + 0x10);
    if (fptr == 0) {
        return 0xffffffa8;
    }
    if (param_2 <= r6[1] && r6[0] <= param_3) {
        return ((int(*)(int*,int,int))fptr)(param_1, param_2, param_3);
    }
    return 0xffffffea;
}
