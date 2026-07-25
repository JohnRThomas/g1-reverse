#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_010331a0 @ 0x010331a0
 * public-name: FUN_010331a0
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_010331a0 @ 0x10331a0  (P4 iteration 25; parity 300/300 directed+randomized trials, 0 mismatches) */
/* ESB retransmission-window release @ 0x010331a0 (Ghidra-gap, extent 0x22). */
extern void FUN_01033ca4(void);
extern void controller_mode1_state_validate(void); /* FUN_010218d8 */
extern void FUN_010218f0(unsigned int);

void FUN_010331a0(void)
{
    volatile unsigned int *reg;
    FUN_01033ca4();
    controller_mode1_state_validate();
    FUN_010218f0(3u);
    reg = *(volatile unsigned int *volatile *)((unsigned long)&g_net_log_msg_ctx) /*=0x21000698*/;
    reg[0x200u / 4u] = reg[0x200u / 4u] & ~0x40004u;
}
