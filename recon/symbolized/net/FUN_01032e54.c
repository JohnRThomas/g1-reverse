#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01032e54 @ 0x01032e54
 * public-name: FUN_01032e54
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_01032e54 @ 0x1032e54  (P4 iteration 25; parity 500/500 directed+randomized trials, 0 mismatches) */
/* ESB RADIO STATE 5 - "frame received" @ 0x01032e54 (Ghidra gap, extent
 * 0x1e8).  Two publishers load the continuation slot 0x210049a0 with the
 * RUNTIME Thumb pointer 0x01033655 (= analysis 0x01032e54 | 1): FUN_01032804
 * and FUN_01033888 (the RX start).  It validates CRC, RX-FIFO room, CRC/PID
 * duplicate suppression per pipe (table at 0x21004b7c), honours
 * selective_auto_ack, then either publishes the ACK payload for the DPL
 * protocol (dequeuing one entry from the per-pipe ACK list at 0x210049b4 and
 * copying it into the ACK staging buffer with __memcpy_chk) or the plain
 * protocol header, and finally re-arms the ACK transmission with continuation
 * 0x01033005 (= FUN_01032804) and state byte 5.  When the frame is fresh it
 * pushes it into the RX FIFO with FUN_01032a3c and raises the RX bit (4) in
 * the pending bitmap plus NVIC ISPR bit 29.
 */
extern void FUN_010329b4(void);
extern void controller_mode2_state_validate(void); /* FUN_010218e4 */
extern void FUN_010218c0(unsigned int, unsigned int);
extern void FUN_0103b53a(unsigned int, unsigned int, unsigned int, unsigned int);
extern void FUN_01032ad8(void);
extern unsigned int FUN_01032a3c(unsigned int, unsigned int);

void FUN_01032e54(void)
{
    volatile unsigned int *radio = (volatile unsigned int *)0x41008000u;
    volatile unsigned int *fifo = (volatile unsigned int *)((unsigned long)&g_net_queue_stats_block_b) /*=0x21004a34*/;
    volatile unsigned char *pids = (volatile unsigned char *)0x21004b7cu;
    volatile unsigned char *hdr = (volatile unsigned char *)0x2100625eu;
    volatile unsigned char *cfg = (volatile unsigned char *)((unsigned long)&g_esb_state) /*=0x21004a94*/;
    volatile unsigned char *stage = (volatile unsigned char *)((unsigned long)&g_net_rf_ack_hdr_buf) /*=0x2100635b*/;
    volatile unsigned int *q = (volatile unsigned int *)0x21004a60u;
    volatile unsigned int *slot = (volatile unsigned int *)((unsigned long)&g_net_rf_cur_frame_ptr) /*=0x21004a8c*/;
    volatile unsigned int *pending = (volatile unsigned int *)((unsigned long)&g_210049b0) /*=0x210049b0*/;
    void (*handler)(unsigned int);
    unsigned int fresh, pipe, off, pid, dup, crc, cnt, proto, entry, nxt, cur, len;
    volatile unsigned int *head;

    fresh = radio[0x400u / 4u] & 1u;
    if (fresh == 0u || fifo[0x28u / 4u] > 7u) {
        FUN_010329b4();
        return;
    }
    pipe = radio[0x408u / 4u] & 0xffu;
    crc = radio[0x40cu / 4u];
    off = pipe * 4u;
    pid = (hdr[1] >> 1) & 3u;
    if (crc == (unsigned int)*(volatile unsigned short *)(pids + off) &&
            pid == (unsigned int)pids[off + 2u]) {
        dup = fresh;
        fresh = 0u;
    } else {
        dup = 0u;
    }
    pids[off + 2u] = (unsigned char)pid;
    *(volatile unsigned short *)(pids + off) =
        (unsigned short)radio[0x40cu / 4u];

    if (cfg[0x12] != 0u && (hdr[1] & 1u) == 0u) {
        FUN_010329b4();
        goto tail;
    }

    controller_mode2_state_validate();
    FUN_010218c0(0x0103cae8u, 0x2100065cu);
    radio[0x200u / 4u] = 0x11bu;
    proto = cfg[0];
    if (proto == 0u) {
        handler = *(void (*volatile *)(unsigned int))((unsigned long)&g_esb_event_handler_fn) /*=0x2100499c*/;
        handler(0u);
        stage[0] = (unsigned char)((stage[0] & ~3u) | (hdr[0] & 3u));
        stage[1] = 0u;
        goto publish;
    }
    if (proto != 1u)
        goto publish;

    cnt = radio[0x408u / 4u];
    entry = 0u;
    head = (volatile unsigned int *)(0x210049b4u + (cnt & 0xffu) * 4u);
    cnt = q[0x28u / 4u];
    if (cnt != 0u) {
        entry = *head;
    }
    if (cnt == 0u || entry == 0u) {
        pids[off + 3u] = 0u;
        handler = *(void (*volatile *)(unsigned int))((unsigned long)&g_esb_event_handler_fn) /*=0x2100499c*/;
        handler(0u);
        stage[0] = 0u;
        goto merge;
    }
    *slot = *(volatile unsigned int *)entry;
    if (pids[off + 3u] != 0u && dup == 0u) {
        *(volatile unsigned char *)(entry + 4u) = 0u;
        nxt = *(volatile unsigned int *)((*head) + 8u);
        q[0x28u / 4u] = cnt - 1u;
        *head = nxt;
        if (cnt - 1u == 0u)
            nxt = 0u;
        else if (nxt != 0u)
            nxt = *(volatile unsigned int *)nxt;
        *slot = nxt;
        *pending = *pending | 1u;
    }
    handler = *(void (*volatile *)(unsigned int))((unsigned long)&g_esb_event_handler_fn) /*=0x2100499c*/;
    cur = *slot;
    if (cur != 0u) {
        pids[off + 3u] = 1u;
        handler(*(volatile unsigned char *)cur);
        cur = *slot;
        len = *(volatile unsigned char *)cur;
        stage[0] = (unsigned char)len;
        FUN_0103b53a(((unsigned long)&g_net_rf_ack_hdr_buf + 2u) /*=0x2100635d*/, cur + 5u, len, 0xfbu);
    } else {
        pids[off + 3u] = 0u;
        handler(0u);
        stage[0] = 0u;
    }
merge:
    stage[1] = (unsigned char)((stage[1] & ~7u) | (hdr[1] & 7u));
publish:
    *(volatile unsigned char *)((unsigned long)&g_net_radio_busy_flag) /*=0x21006458*/ = 5u;
    FUN_01032ad8();
    radio[0x52cu / 4u] = radio[0x408u / 4u] & 0xffu;
    radio[0x504u / 4u] = ((unsigned long)&g_net_rf_ack_hdr_buf) /*=0x2100635b*/;
    #ifdef G1_COHESIVE_BUILD
    /* P4 iteration 25 - CODE POINTER.  0x01033005 is a RUNTIME Thumb pointer;
       runtime->analysis is -0x800, so it is (0x01032804 | 1) = FUN_01032804, an ESB
       radio state-machine entry recovered from the Ghidra gap this
       iteration.  Left as the shipped literal the relocated build stores
       an address inside unrelated code and FUN_010327d8's `bx r3`
       dispatches nowhere (measured, iteration 24 probeN:
       0x210049a0 = 0x010338B1, pending bitmap 0x210049b0 stuck at 0,
       IRQ 0x1d never raised, the announcement never re-armed). */
    *(volatile unsigned int *)((unsigned long)&g_net_radio_irq_continuation_ptr) /*=0x210049a0*/ = ADDR_FUN_01032804_THUMB;
#else
    *(volatile unsigned int *)((unsigned long)&g_net_radio_irq_continuation_ptr) /*=0x210049a0*/ = 0x01033005u;
#endif
tail:
    if (fresh != 0u) {
        unsigned int rxm = radio[0x408u / 4u];
        unsigned int n = fifo[0x28u / 4u];
        unsigned int p2 = pids[off + 2u];
        if (n <= 7u && FUN_01032a3c(rxm & 0xffu, p2) != 0u) {
            *pending = *pending | 4u;
            *(volatile unsigned int *)(0xe000e100u + 0x100u) = 0x20000000u;
        }
    }
}
