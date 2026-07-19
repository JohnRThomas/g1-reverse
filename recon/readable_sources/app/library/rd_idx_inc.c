#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_mpsc_pbuf_buffer__param_0133           [param_0133; library]
 * Raw function identity: 0x0007e378.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0007e378 @ 0x0007e378
 * public-name: rd_idx_inc
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   idx_inc                                  <= FUN_0007e35c @ 0x0007e35c
 *   rd_idx_inc                               <= FUN_0007e378 @ 0x0007e378
 */
/* Reconstructed FUN_0007e378 @ 0x7e378  (parity: 300/300 trials, PROVEN) */

extern int idx_inc(int a,int b,int c);
void rd_idx_inc(int *param_1, int param_2) {
    char *base = (char*)param_1;
    int v = *(int*)(base + 0xc);
    int r = idx_inc((int)param_1, v, param_2);
    *(int*)(base + 0xc) = r;
    unsigned int u = *(unsigned int*)(base + 0x10);
    *(unsigned int*)(base + 0x10) = u & 0xfffffff7u;
}
