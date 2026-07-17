#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01013650 @ 0x01013650
 * public-name: FUN_01013650
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 *   sdc_work_submit                          <= FUN_0100ef88 @ 0x0100ef88
 *   sdc_radio_context_fixed_time_get         <= FUN_0100f0fc @ 0x0100f0fc
 *   sdc_conn_event_timing_prepare            <= FUN_01012f18 @ 0x01012f18
 *   radio_phy_airtime_base_get               <= FUN_010209f0 @ 0x010209f0
 *   controller_radio_transition_apply        <= FUN_01020d1c @ 0x01020d1c
 *   controller_time_now                      <= FUN_01022f08 @ 0x01022f08
 * address symbols (name @ address):
 *   rodata_10100a1                           @ 0x010100a1
 *   g_net_radio_ack_pending_flag             @ 0x21000f54
 */
/* net-core FUN_01013650 @ 0x1013650
 * True extent: 840 bytes code through 0x1013997, followed by a 12-byte
 * literal pool through 0x10139a3.  Ghidra's former 5332-byte body overlapped
 * later independent functions after failing to stop at noreturn panics. */
#include <stdint.h>

extern void sdc_assertion_fail(uint32_t, uint32_t);
extern uint64_t controller_time_now(void);
extern uint32_t sdc_conn_event_timing_prepare(void *, uint32_t, uint32_t, uint32_t, uint16_t *);
extern void sdc_work_submit(void *, uint32_t, uint32_t);
extern void FUN_01016170(void *);
extern void FUN_01022ebc(uint32_t);
extern void FUN_01015ecc(void *);
extern uint32_t FUN_01022ea8(void);
extern int32_t sdc_radio_context_fixed_time_get(void *);
extern uint64_t radio_phy_airtime_base_get(uint32_t);
extern uint32_t FUN_01023dec(uint32_t, uint32_t, uint32_t);
extern int32_t FUN_01023ea8(uint32_t, uint32_t);
extern uint32_t FUN_0100f368(void *, int32_t, uint32_t, int32_t);
extern void FUN_01023d38(int32_t, uint32_t, uint32_t);
extern void controller_radio_event1_dispatch(void *, uint32_t); /* FUN_01016144@0x01016144 */
extern void controller_radio_transition_apply(void *, uint32_t);
extern uint64_t FUN_01022a30(uint32_t);
extern void FUN_0100b5f8(uint64_t);

#define U8(p,o)  (*(volatile uint8_t *)((uintptr_t)(p) + (o)))
#define U16(p,o) (*(volatile uint16_t *)((uintptr_t)(p) + (o)))
#define S16(p,o) (*(volatile int16_t *)((uintptr_t)(p) + (o)))
#define U32(p,o) (*(volatile uint32_t *)((uintptr_t)(p) + (o)))
#define U64(p,o) (*(volatile uint64_t *)((uintptr_t)(p) + (o)))

/* Production panic is noreturn. Repeating the platform call if a test double
 * returns preserves that contract without executing bytes from the following
 * unrelated function. */
static __attribute__((always_inline, noreturn)) inline void
panic(uint32_t domain, uint32_t reason)
{
    for (;;) sdc_assertion_fail(domain, reason);
}

static __attribute__((always_inline)) inline void advance_receive_window(void *context)
{
    uint64_t elapsed = controller_time_now() - U64(context, 0x350);
    uint32_t low = (uint32_t)elapsed;
    int32_t high = (int32_t)(elapsed >> 32);
    uint32_t quotient = U32(context, 0x14) ? low / U32(context, 0x14) : 0;
    uint16_t base = U16(context, 0xbc);
    uint16_t next;
    uint16_t limit;

    if (high < (int32_t)(low == 0)) {
        panic(0x30, 0x64c);
    }
    if (high != 0 || low > 0xfffffffeu) {
        panic(0x30, 0x64d);
    }

    if (U8(context, 0xc6) == 0x0e) {
        next = (uint16_t)(U16(context, 0x32e) + 1u);
    } else {
        uint16_t candidate = U16(context, 0x32e);
        uint16_t predicted = (uint16_t)(base + quotient);
        if ((int16_t)(candidate - predicted) < 0)
            candidate = predicted;
        next = (uint16_t)(candidate + 1u);
        if (U8(context, 0x331) == 0 && U16(context, 0x2e4) == next)
            next = (uint16_t)(next + 1u);
    }
    U16(context, 0x32e) = next;
    limit = (uint16_t)(base + (uint16_t)(U16(context, 0xf8) - 1u - U16(context, 0xf6)));
    U16(context, 0x362) = (uint16_t)(U16(context, 0x362) + 1u);

    while ((int16_t)(limit - next) >= 0) {
        uint16_t consumed = 0;
        uint32_t result = sdc_conn_event_timing_prepare(context, next, 0, 0, &consumed);
        if (result == 0) {
            int16_t distance;
            uint16_t period;
            if (U32(context, 0x74) == 0)
                return;
            distance = (int16_t)(U16(context, 0x32e) - U16(context, 0xf2));
            if (distance < 1)
                return;
            period = U16(context, 0x78);
            U16(context, 0xf2) = (uint16_t)(U16(context, 0xf2) +
                ((distance + period - 1u) / period) * period);
            return;
        }
        if (result != 1) {
            panic(0x30, 0x68c);
        }
        next = (uint16_t)(U16(context, 0x32e) + consumed);
        if ((U16(context, 0x32e) - U16(context, 0x2e0)) & 0x8000u) {
            if ((int16_t)(limit - next) >= 0) {
                U16(context, 0x32e) = next;
                continue;
            }
            next = U16(context, 0x2e0);
        }
        U16(context, 0x32e) = next;
        if ((int16_t)(limit - next) < 0)
            break;
    }

    U8(context, 0xe5) = U8(context, 0xc9) == 0 ? 0x3e : 8;
    sdc_work_submit((uint8_t *)context + 0xdc, ((unsigned long)&rodata_10100a1) /*=0x10100a1*/, 2);
    FUN_01016170(context);
    U8(context, 0x31c) = 0;
    FUN_01022ebc(U8(context, 0x364));
    U8(context, 0x364) = 0x20;
}

static __attribute__((always_inline)) inline void finish_interval(void *context)
{
    uint32_t budget;
    int32_t fixed;
    uint8_t mode;
    uint64_t timing;
    uint64_t product;
    uint32_t available;
    uint32_t duration;

    U32(context, 0x36c) = 0;
    if (U8(context, 0x330) == 0) {
        uint16_t old = U16(context, 0xbc);
        U16(context, 0xbc) = U16(context, 0x32c);
        S16(context, 0x2e6) = (int16_t)(U16(context, 0x32c) - old);
    } else {
        uint16_t candidate = U16(context, 0x32e);
        uint16_t old = U16(context, 0xbc);
        if (candidate == old) {
            U16(context, 0xbc) = U16(context, 0x2e4);
            S16(context, 0x2e6) = (int16_t)(U16(context, 0x2e4) - candidate);
        } else {
            U16(context, 0xbc) = candidate;
            S16(context, 0x2e6) = (int16_t)(candidate - old);
        }
    }
    U64(context, 0x350) = U64(context, 0x348);
    FUN_01015ecc(context);
    if (U8(context, 0x2eb) == 0)
        return;

    mode = U8(context, 0x6f);
    budget = FUN_01022ea8();
    if (budget < 0x92) budget = 0x92;
    if (U32(context, 0x324) - 0x92u + budget < U32(context, 0x14))
        available = U32(context, 0x14) + 0x92u - U32(context, 0x324) - budget;
    else
        available = 0;
    if (U8((void *)((unsigned long)&g_net_radio_ack_pending_flag) /*=0x21000f54*/, 8) == 0 && U32(context, 0x30) <= available)
        available = U32(context, 0x30);

    fixed = sdc_radio_context_fixed_time_get((uint8_t *)context + 0x30);
    timing = radio_phy_airtime_base_get(mode);
    product = 0x10624dd3ull * ((uint32_t)timing + 0xdf41u);
    fixed += U32(context, 0x2f0) + 0xc5 + (uint32_t)(product >> 38);
    if ((mode & 0x0c) != 0) fixed += 0x28;
    duration = FUN_01023dec(2, (uint32_t)(timing >> 32), (uint32_t)product);
    available = available > (uint32_t)fixed ? available - fixed : 0;
    if (duration < available) available = duration;
    if (FUN_01023ea8(available, 2) == 0) fixed += available;
    U32((void *)((unsigned long)&g_net_radio_ack_pending_flag) /*=0x21000f54*/, 0x0c) = FUN_0100f368(
        context, fixed, (mode & 0x0c) ? 0x25e : 0x236, fixed - 0x28);

    timing = radio_phy_airtime_base_get(mode);
    product = 0x10624dd3ull * ((uint32_t)timing + 0xdf41u);
    FUN_01023d38(fixed - 0x17a - (int32_t)(product >> 38) -
                  ((mode & 0x0c) ? 0x28 : 0),
                  (uint32_t)(timing >> 32), (uint32_t)product);
}

void FUN_01013650(void *context, uint32_t event)
{
    uint64_t result;
    if (context == 0) {
        panic(0x30, 0x97);
    }
    switch (event) {
    case 0: finish_interval(context); return;
    case 1: controller_radio_event1_dispatch(context, event); return;
    case 2:
    case 3: advance_receive_window(context); return;
    case 4: controller_radio_transition_apply(context, event); return;
    case 6:
        result = FUN_01022a30(1);
        FUN_0100b5f8(result);
        return;
    case 7:
        if (U8(context, 0x31c) != 4) {
            panic(0x30, 0xbb);
        }
        U8(context, 0x31c) = 0;
        return;
    case 8:
        panic(0x30, 0xc1);
    default:
        panic(0x30, 0xc5);
    }
}
