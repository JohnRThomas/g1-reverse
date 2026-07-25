#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01032de4 @ 0x01032de4
 * public-name: FUN_01032de4
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_01032de4 @ 0x1032de4  (P4 iteration 25; parity 300/300 directed+randomized trials, 0 mismatches) */
/* ESB RADIO STATE - "TX slot finished" @ 0x01032de4 (Ghidra gap, extent 0x5a).
 * FUN_01032c28 loads the continuation slot 0x210049a0 with the RUNTIME Thumb
 * pointer 0x010335e5 (= analysis 0x01032de4 | 1), so this runs from
 * FUN_010327d8's `bx r3` on the RADIO DISABLED interrupt.  It clears the
 * timeslot wiring, raises the TX-completed bit in the pending-event bitmap
 * 0x210049b0, and either idles (state byte 0) or pops the TX FIFO
 * (FUN_01032954) and re-enters FUN_01032c28 to key the next frame.  Both exits
 * set NVIC ISPR bit 29 (IRQ 0x1d, the ESB event dispatch FUN_0103289c).
 */
extern void controller_mode1_state_validate(void); /* FUN_010218d8 */
extern void FUN_01033ca4(void);
extern void FUN_010218b4(void);
extern void FUN_01033bf0(unsigned int, unsigned int);
extern void FUN_01032954(void);
extern void FUN_01032c28(void);

void FUN_01032de4(void)
{
    volatile unsigned int *q = (volatile unsigned int *)0x21004a60u;
    volatile unsigned int *nvic = (volatile unsigned int *)0xe000e100u;

    controller_mode1_state_validate();
    (*(volatile unsigned int *volatile *)((unsigned long)&g_net_log_msg_ctx) /*=0x21000698*/)[0x10u / 4u] = 1u;
    FUN_01033ca4();
    FUN_010218b4();
    FUN_01033bf0(0u, 0u);
    *(volatile unsigned int *)((unsigned long)&g_210049b0) /*=0x210049b0*/ =
        *(volatile unsigned int *)((unsigned long)&g_210049b0) /*=0x210049b0*/ | 1u;
    if (q[0x28u / 4u] != 0u) {
        FUN_01032954();
        if (q[0x28u / 4u] != 0u) {
            nvic[0x100u / 4u] = 0x20000000u;
            FUN_01032c28();
            return;
        }
    }
    *(volatile unsigned char *)((unsigned long)&g_net_radio_busy_flag) /*=0x21006458*/ = 0u;
    nvic[0x100u / 4u] = 0x20000000u;
}
