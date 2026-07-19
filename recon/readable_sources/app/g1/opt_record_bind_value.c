#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_2          => struct g1_layout_opt_record__param_0466                 [param_0466; G1-original]
 * Raw function identity: 0x0007c61e.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0007c61e @ 0x0007c61e
 * public-name: opt_record_bind_value
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   opt_node_value_len                       <= FUN_0007c408 @ 0x0007c408
 *   opt_record_bind_value                    <= FUN_0007c61e @ 0x0007c61e
 */
/* Reconstructed FUN_0007c61e @ 0x7c61e  (parity: 300/300 trials, PROVEN) */
extern unsigned int opt_node_value_len(void);

unsigned int opt_record_bind_value(unsigned char *param_1, unsigned char *param_2)
{
    unsigned int uVar1;
    unsigned int uVar2;

    if (param_1 == 0 || param_2 == 0 || (unsigned char)(*param_2 - 1) > 0x15 ||
        *(unsigned int*)(param_2 + 4) == 0 || *(unsigned int*)(param_2 + 8) == 0 ||
        *(unsigned int*)(param_2 + 0xc) == 0) {
        uVar2 = 7;
    } else {
        *(unsigned char **)(param_1 + 0x14) = param_2;
        uVar1 = opt_node_value_len();
        uVar2 = 0;
        *param_1 = (*param_1 & 0xef) | ((uVar1 < 0x100) << 4);
    }
    return uVar2;
}
