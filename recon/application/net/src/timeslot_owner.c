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

void FUN_010327d8(void) /*=0x010327d8*/
{
    volatile uint32_t *radio = (volatile uint32_t *)0x41008000u;
    if ((radio[0x304u / 4u] & 0x20u) != 0u && radio[0x110u / 4u] != 0u) {
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
