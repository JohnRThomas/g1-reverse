#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_smp_hdr__param_0552                    [param_0552; library]
 *   param_2          => struct g1_layout_smp_hdr__param_0553                    [param_0553; library]
 * Raw function identity: 0x000807f6.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_000807f6 @ 0x000807f6
 * public-name: smp_make_rsp_hdr
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   smp_make_rsp_hdr                         <= FUN_000807f6 @ 0x000807f6
 */
/* Reconstructed FUN_000807f6 @ 0x807f6  (parity: 300/300 trials, PROVEN) */
void smp_make_rsp_hdr(unsigned char *param_1, unsigned char *param_2, unsigned int param_3)
{
    unsigned short uVar1;
    unsigned short uVar2;
    unsigned int uVar3;
    unsigned char bVar4;

    uVar1 = *(volatile unsigned short *)(param_1 + 4);
    uVar2 = *(volatile unsigned short *)(param_1 + 6);
    uVar3 = ((unsigned int)*param_1 << 0x1b) >> 0x1e;
    if ((*param_1 & 7) == 0) {
        bVar4 = 1;
    } else {
        bVar4 = 3;
    }
    if (uVar3 != 0) {
        uVar3 = 1;
    }
    *(volatile unsigned int *)param_2 = 0;
    *(volatile unsigned char *)param_2 = bVar4 | (unsigned char)(uVar3 << 3) | (*param_2 & 0xe0);
    *(volatile unsigned short *)(param_2 + 2) = (unsigned short)((param_3 & 0xff) << 8) | (unsigned short)((param_3 >> 8) & 0xff);
    *(volatile unsigned short *)(param_2 + 4) = (unsigned short)((uVar1 & 0xff) << 8) | (uVar1 >> 8);
    *(volatile unsigned short *)(param_2 + 6) = uVar2;
}
