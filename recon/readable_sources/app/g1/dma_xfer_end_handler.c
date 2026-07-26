#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_dma_xfer_desc__param_0705              [param_0705; G1-original]
 * Raw function identity: 0x000857e0.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_000857e0 @ 0x000857e0
 * public-name: dma_xfer_end_handler
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   dma_xfer_end_handler                     <= FUN_000857e0 @ 0x000857e0
 * address symbols (name @ address):
 *   g_sram_base_word                         @ 0x20000000
 */
/* Reconstructed FUN_000857e0 @ 0x857e0  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
typedef void (*fn_t)(int *);
#include <cmsis_gcc.h>

void dma_xfer_end_handler(int *param_1)
{
    int iVar1;

    __DMB();
    iVar1 = *(int *)(*param_1 + 0x18);
    if ((*(unsigned int *)(*param_1 + 0x10) & ((unsigned long)&g_sram_base_word) /*=0x20000000*/) == 0) {
        if ((iVar1 != 0) || ((int)((unsigned int)*(unsigned short *)param_1[8] << 0x1f) < 0)) goto control_label_00085810;
    } else {
        if (iVar1 != 0) goto control_label_00085810;
        if (*(unsigned short *)((int)param_1 + 0x26) <=
            (unsigned short)((*(short *)(param_1[7] + 2) + -1) - *(short *)(param_1[8] + param_1[5] * 8 + 4)))
            goto control_label_00085810;
    }
    if ((fn_t)param_1[4] != (fn_t)0) {
        ((fn_t)param_1[4])(param_1);
    }
control_label_00085810:
    *(unsigned short *)((int)param_1 + 0x26) = 0;
}
