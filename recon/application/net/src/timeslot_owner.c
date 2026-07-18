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
