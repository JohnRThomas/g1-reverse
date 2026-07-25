/* Cohesive ownership for the product MPSL timeslot dispatch closure.
 *
 * Original evidence: request VAs 0x210005b8/0x210005d8; queue VA
 * 0x210008e0 (msg_size=1, max_msgs=4); thread/stack VAs
 * 0x21001ed0/0x21007940; runtime Thumb entry 0x0102c011.
 */

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <mpsl_timeslot.h>

LOG_MODULE_REGISTER(timeslot, 3);

K_MSGQ_DEFINE(g1_timeslot_api_msgq, 1, 4, 4);

mpsl_timeslot_request_t g1_timeslot_request_normal = {
    .request_type = MPSL_TIMESLOT_REQ_TYPE_NORMAL,
    .params.normal = {
        .hfclk = MPSL_TIMESLOT_HFCLK_CFG_NO_GUARANTEE,
        .priority = MPSL_TIMESLOT_PRIORITY_HIGH,
        .distance_us = 50000,
        .length_us = 5000,
    },
};

mpsl_timeslot_request_t g1_timeslot_request_earliest = {
    .request_type = MPSL_TIMESLOT_REQ_TYPE_EARLIEST,
    .params.earliest = {
        .hfclk = MPSL_TIMESLOT_HFCLK_CFG_NO_GUARANTEE,
        .priority = MPSL_TIMESLOT_PRIORITY_HIGH,
        .length_us = 5000,
        .timeout_us = 1000000,
    },
};

/* P4 iteration 21 - the SECOND normal request.
 *
 * The shipped `.data` holds THREE 16-byte mpsl_timeslot_request_t objects
 * back to back, read with tools/net_extract.py at the net .data LMA
 * (analysis 0x0103e524 + VMA offset):
 *
 *   0x210005b8  01 00 00 00 01 00 00 00 50 c3 00 00 88 13 00 00  NORMAL role 0
 *   0x210005c8  01 00 00 00 01 00 00 00 50 c3 00 00 88 13 00 00  NORMAL role 1
 *   0x210005d8  00 00 00 00 01 00 00 00 88 13 00 00 40 42 0f 00  EARLIEST
 *
 * i.e. {NORMAL, hfclk=NO_GUARANTEE, priority=HIGH, distance=50000,
 * length=5000} twice and {EARLIEST, NO_GUARANTEE, HIGH, length=5000,
 * timeout=1000000}.  The signal callback FUN_0102b944 selects between the two
 * NORMAL ones on the ESB role (`select_role_request`), so both must exist as
 * distinct objects; only two were emitted before this iteration and the third
 * pointer was a raw original-image literal. */
mpsl_timeslot_request_t g1_timeslot_request_normal_role1 = {
    .request_type = MPSL_TIMESLOT_REQ_TYPE_NORMAL,
    .params.normal = {
        .hfclk = MPSL_TIMESLOT_HFCLK_CFG_NO_GUARANTEE,
        .priority = MPSL_TIMESLOT_PRIORITY_HIGH,
        .distance_us = 50000,
        .length_us = 5000,
    },
};

/* P4 iteration 21 - the ESB radio operating-state word, original VA
 * 0x210005b4, shipped initialiser `01 00 00 00` (same read as above).
 *
 * It was a LINKER PIN (`PROVIDE(g_net_radio_op_state = 0x210005b4)`) plus four
 * raw `0x210005b4` literals.  In the cohesive link 0x210005b4 is exactly where
 * the linker placed `g1_timeslot_request_earliest`, so the IPC sub-commands
 * 10/11/12 (FUN_0102b794/FUN_0102b7a0/FUN_0102b7ac) wrote 2/1/3 straight into
 * that request's `request_type` byte.  Measured (iteration 21): sub-command 11
 * arrives at t = 1.1 s and sets it to 1, so the FIRST timeslot request of the
 * session was submitted as MPSL_TIMESLOT_REQ_TYPE_NORMAL; mpsl_timeslot.h
 * requires the first request of a session to be EARLIEST, mpsl_timeslot_request
 * returned -NRF_EINVAL (-22) and the recovered worker's fatal `svc 2` reset the
 * SoC.  Give the word its own storage. */
volatile unsigned int g_net_radio_op_state = 1u;

/* P4 iteration 24 - the ESB radio owner's `nrfx_timer_t` INSTANCE, original VA
 * 0x21000698, shipped `.data` initialiser (tools/net_extract.py, .data LMA
 * 0x0103ed24 + 0x698):
 *
 *     00 90 01 41 | 00 08 00 00
 *       = { .p_reg = 0x41019000 (CPUNET TIMER2), .instance_id = 0,
 *           .cc_channel_count = 8 }
 *
 * It was a LINKER PIN (`PROVIDE(g_net_log_msg_ctx = 0x21000698)`) with no
 * storage and no initialiser, so `p_reg` read as whatever the cohesive link
 * placed there.  FUN_01034fa8 is nrfx_timer_init: it asserts
 * `p_instance->p_reg` is TIMER0 (0x4100c000) / TIMER1 (0x41018000) /
 * TIMER2 (0x41019000) at nrfx_timer.c:142 -- the exact string pair
 * ("ASSERTION FAIL @ %s:%d", ".../nrfx_timer.c", 0x8e) in its literal pool.
 * MEASURED (iteration 24 probeE): the assertion failed; Zephyr's default
 * `assert_post_action` RETURNS (the shipped FUN_01039bb0 is noreturn), so
 * control fell through into nrfx_timer_extended_compare (FUN_01034f24) with
 * r0 = 4 / r1 = 0x8e -- the assert's own leftovers -- which failed its
 * frequency check and returned 0x0BAD0004.  FUN_010333b4 requires 0x0BAD0000
 * and returned -EFAULT, so the ESB "enabled" flag at 0x21006459 stayed 0, the
 * announcement packet could not be published, and no ESB frame was keyed.
 * The name is the autonamer's; the object is the timer instance. */
volatile unsigned int g_net_log_msg_ctx[2] __attribute__((used, retain)) = {
    0x41019000u,   /* p_reg = NRF_TIMER2 (CPUNET) */
    0x00000800u,   /* instance_id = 0, cc_channel_count = 8 */
};

/* P4 iteration 24 - the two nrfx GPPI/DPPI allocator words, original VAs
 * 0x210006a0 and 0x210006a4, shipped `.data` initialisers (same read):
 *
 *     +0x6a0  3f 00 00 00   groups   0..5  free
 *     +0x6a4  00 c0 ff ff   channels 14..31 free (0..13 belong to the SDC)
 *
 * FUN_01034328 claims the highest set bit with an LDREX/STREX loop and returns
 * 0x0BAD0002 ("no resource") when the word is zero.  Both addresses were bare
 * linker pins with no storage, so the words read 0 and every
 * gppi_channel_alloc in FUN_01033df0 failed; it logged
 * "gppi_channel_alloc failed with: %d" and returned -EIO, and FUN_010333b4
 * returned that error WITHOUT setting the ESB enabled flag at 0x21006459.
 * MEASURED (iteration 24 probeF): with only the timer instance restored,
 * FUN_01033df0 was reached for the first time and still failed here. */
/* P4 iteration 25 - the ESB retransmission-window REQUEST record, original VA
 * 0x21000670, shipped `.data` initialiser (tools/net_extract.py read_runtime at
 * the net .data LMA 0x0103ed24 + 0x670):
 *
 *     00 00 00 00 | 00 90 01 41 | 00 00 00 00 | 00 00 00 00
 *       = { 0, 0x41019000 (CPUNET TIMER2), 0, length }
 *
 * FUN_01033168 (recovered this iteration from the Ghidra gap) fills word 3
 * with TIMER2 CC[1] + 0x81 us and submits the record through slot 8 of the
 * radio-arbitration vtable at 0x21000530 (FUN_010218c0); on rejection it falls
 * back to setting TIMER2 SHORTS 0x40004 directly.  The address had no owner in
 * the cohesive link: check_net_raw_literals.py places 0x21000670 INSIDE the
 * live `sdc_mempool`, so the write corrupted the SoftDevice Controller pool.
 * Emitting it is the same remedy iteration 24 applied to 0x21000698 /
 * 0x210006a0 / 0x210006a4. */
volatile unsigned int g1_esb_window_request[4] __attribute__((used, retain)) = {
    0x00000000u,
    0x41019000u,   /* NRF_TIMER2 (CPUNET) */
    0x00000000u,
    0x00000000u,
};

volatile unsigned int g_net_dppi_group_pool __attribute__((used, retain)) =
    0x0000003fu;
volatile unsigned int g_sdc_res_pool_free_bitmap __attribute__((used, retain)) =
    0xffffc000u;

/* Tiny address-owned leaves used by the recovered signal callback. */
uint32_t FUN_0102a4a4(void) /*=0x0102a4a4*/
{
    volatile uint32_t **owner = (volatile uint32_t **)0x210045f4u;
    return **owner;
}

uint32_t FUN_0102b7c4(void) /*=0x0102b7c4*/
{
    return *(volatile uint8_t *)0x21004fa3u;
}

/* P4 iteration 24 - MASK CORRECTION, disassembly evidence.  The shipped body
 * at analysis 0x010327d8 is
 *     ldr.w r2,[r3,#0x304]      ; RADIO INTENSET
 *     lsls  r2,r2,#27           ; N = bit (31-27) = bit 4
 *     bpl.n <return>
 * so the tested bit is 4 (0x10 = the DISABLED interrupt, which pairs with the
 * EVENTS_DISABLED register at 0x110 the very next instruction reads), NOT
 * bit 5 (0x20).  MEASURED with the wrong mask (iteration 24 probeK, after IRQ
 * 8 was finally connected to this handler): RADIO INTENSET reads 0x00000010,
 * `& 0x20` was always 0, EVENTS_DISABLED was never cleared and the handler
 * re-entered continuously -- 1,312 entries in one 6 s probe -- while the ESB
 * state-machine continuation at 0x210049a0 was never called. */
void FUN_010327d8(void) /*=0x010327d8*/
{
    volatile uint32_t *radio = (volatile uint32_t *)0x41008000u;
    if ((radio[0x304u / 4u] & 0x10u) != 0u && radio[0x110u / 4u] != 0u) {
        radio[0x110u / 4u] = 0;
        (void)radio[0x110u / 4u];
        void (*callback)(void) = *(void (**)(void))0x210049a0u;
        if (callback != NULL) {
            callback();
        }
    }
}

extern void FUN_0102b810(void *, void *, void *);

K_THREAD_DEFINE(mpsl_nonpreemptible_thread_id, 0x400,
                FUN_0102b810, NULL, NULL, NULL,
                -16, 0, 0);
