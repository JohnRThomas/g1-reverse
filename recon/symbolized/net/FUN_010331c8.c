#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_010331c8 @ 0x010331c8
 * public-name: FUN_010331c8
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_010331c8 @ 0x10331c8  (P4 iteration 25; parity 400/400 directed+randomized trials, 0 mismatches) */
/* ESB RADIO STATE 2 - "ACK window elapsed" @ 0x010331c8 (Ghidra gap, extent
 * 0x146).  Reached from state 3 through the continuation slot 0x210049a0
 * (RUNTIME Thumb 0x010339c9 = analysis 0x010331c8 | 1).  Three outcomes:
 *   - RADIO EVENTS_END set and CRCSTATUS ok  -> the ACK arrived: raise the
 *     TX-success bit (1) in the pending bitmap 0x210049b0, record the attempt
 *     count, optionally push the ACK payload with FUN_01032a3c (bit 4), and
 *     either idle or re-enter FUN_01032c28 for the next queued frame;
 *   - the retransmit counter at 0x210049ac has run out -> raise the TX-failed
 *     bit (2) and idle;
 *   - otherwise -> re-key the same frame: SHORTS 0x11b, PACKETPTR at the TX
 *     staging buffer, continuation back to 0x010338b1 (= FUN_010330b0),
 *     state byte 2, and re-request the retransmission window.
 * Every exit raises NVIC ISPR bit 29 (IRQ 0x1d).
 */
extern void FUN_01033da0(void);
extern void controller_mode2_state_validate(void); /* FUN_010218e4 */
extern void FUN_010218b4(void);
extern void FUN_01032954(void);
extern unsigned int FUN_01032a3c(unsigned int, unsigned int);
extern void FUN_01032c28(void);
extern void FUN_01032ad8(void);
extern void FUN_01033168(void);
extern void FUN_01033cd0(void);
extern void FUN_010331a0(void);
extern void FUN_01033d20(void);
extern void FUN_01033b18(unsigned int, unsigned int);
extern void FUN_01032860(unsigned int);

void FUN_010331c8(void)
{
    volatile unsigned int *radio = (volatile unsigned int *)0x41008000u;
    volatile unsigned int *retries = (volatile unsigned int *)((unsigned long)&g_esb_pipe_cfg_field) /*=0x210049ac*/;
    volatile unsigned int *pending = (volatile unsigned int *)((unsigned long)&g_210049b0) /*=0x210049b0*/;
    volatile unsigned char *cfg = (volatile unsigned char *)((unsigned long)&g_esb_state) /*=0x21004a94*/;
    volatile unsigned int *q = (volatile unsigned int *)0x21004a60u;
    volatile unsigned char *hdr = (volatile unsigned char *)0x2100625eu;
    volatile unsigned int *fifo = (volatile unsigned int *)((unsigned long)&g_net_queue_stats_block_b) /*=0x21004a34*/;
    volatile unsigned int *volatile *inst =
        (volatile unsigned int *volatile *)((unsigned long)&g_net_log_msg_ctx) /*=0x21000698*/;
    volatile unsigned int *nvic = (volatile unsigned int *)0xe000e100u;
    volatile unsigned int *timer;
    void (*handler)(unsigned int);
    unsigned int n, b0, b1, cnt, txaddr, pid;

    FUN_01033da0();
    controller_mode2_state_validate();
    FUN_010218b4();

    if (radio[0x10cu / 4u] != 0u && (radio[0x400u / 4u] & 1u) != 0u) {
        *pending = *pending | 1u;
        *(volatile unsigned int *)((unsigned long)&g_esb_tx_busy_flag) /*=0x210049a8*/ =
            (unsigned int)(*(volatile unsigned short *)((unsigned long)&g_esb_state + 0xeu) /*=0x21004aa2*/)
            - *retries + 1u;
        if (q[0x28u / 4u] != 0u)
            FUN_01032954();
        if (cfg[0] != 0u) {
            b0 = hdr[0];
            if (b0 != 0u) {
                b1 = hdr[1];
                cnt = fifo[0x28u / 4u];
                txaddr = radio[0x52cu / 4u];
                pid = (b1 >> 1) & 3u;
                if (cnt <= 7u && FUN_01032a3c(txaddr & 7u, pid) != 0u)
                    *pending = *pending | 4u;
            }
        }
        if (q[0x28u / 4u] != 0u && cfg[0x10] != 1u) {
            nvic[0x100u / 4u] = 0x20000000u;
            FUN_01032c28();
            return;
        }
        *(volatile unsigned char *)((unsigned long)&g_net_radio_busy_flag) /*=0x21006458*/ = 0u;
        nvic[0x100u / 4u] = 0x20000000u;
        return;
    }

    n = *retries;
    *retries = n - 1u;
    if (n == 0u) {
        (*inst)[0x10u / 4u] = 1u;
        *(volatile unsigned int *)((unsigned long)&g_esb_tx_busy_flag) /*=0x210049a8*/ =
            (unsigned int)(*(volatile unsigned short *)((unsigned long)&g_esb_state + 0xeu) /*=0x21004aa2*/) + 1u;
        *pending = *pending | 2u;
        *(volatile unsigned char *)((unsigned long)&g_net_radio_busy_flag) /*=0x21006458*/ = 0u;
        nvic[0x100u / 4u] = 0x20000000u;
        return;
    }

    radio[0x100u / 4u] = 0u;
    (void)radio[0x100u / 4u];
    radio[0x200u / 4u] = 0x11bu;
    handler = *(void (*volatile *)(unsigned int))((unsigned long)&g_esb_event_handler_fn) /*=0x2100499c*/;
    handler(*(volatile unsigned char *)(*(volatile unsigned int *)((unsigned long)&g_net_rf_cur_frame_ptr) /*=0x21004a8c*/));
    radio[0x504u / 4u] = ((unsigned long)&g_net_rf_ack_hdr_buf) /*=0x2100635b*/;
    #ifdef G1_COHESIVE_BUILD
    /* P4 iteration 25 - CODE POINTER.  0x010338b1 is a RUNTIME Thumb pointer;
       runtime->analysis is -0x800, so it is (0x010330b0 | 1) = FUN_010330b0, an ESB
       radio state-machine entry recovered from the Ghidra gap this
       iteration.  Left as the shipped literal the relocated build stores
       an address inside unrelated code and FUN_010327d8's `bx r3`
       dispatches nowhere (measured, iteration 24 probeN:
       0x210049a0 = 0x010338B1, pending bitmap 0x210049b0 stuck at 0,
       IRQ 0x1d never raised, the announcement never re-armed). */
    *(volatile unsigned int *)((unsigned long)&g_net_radio_irq_continuation_ptr) /*=0x210049a0*/ = ADDR_FUN_010330b0_THUMB;
#else
    *(volatile unsigned int *)((unsigned long)&g_net_radio_irq_continuation_ptr) /*=0x210049a0*/ = 0x010338b1u;
#endif
    *(volatile unsigned char *)((unsigned long)&g_net_radio_busy_flag) /*=0x21006458*/ = 2u;
    FUN_01032ad8();
    FUN_01033168();
    FUN_01033cd0();
    timer = *inst;
    if (timer[0x144u / 4u] == 0u) {
        timer[0] = 1u;
        return;
    }
    if ((radio[0x550u / 4u] & 0xffu) == 9u)
        return;
    if (radio[0x100u / 4u] != 0u)
        return;
    FUN_010331a0();
    FUN_01033d20();
    FUN_01033b18(0u, 1u);
    FUN_01032860(1u);
    *(volatile unsigned int *)(0x41014000u + 0x18u) = 1u;
}
