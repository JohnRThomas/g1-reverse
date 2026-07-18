#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_010231c8 @ 0x010231c8
 * public-name: sdc_conn_window_admit
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   controller_deferred_event_raise          <= FUN_0102583c @ 0x0102583c
 * address symbols (name @ address):
 *   g_libc_tz_calc_state                     @ 0x210016f0
 */
/* net-core FUN_010231c8 @ 0x010231c8 -- sdc_conn_window_admit; raw backmap retained. */
#include <stdint.h>

typedef struct {
    uint32_t start;
    uint32_t start_hi;
    uint32_t duration;
    uint32_t duration_hi;
    uint32_t opaque;
    uint32_t owner;
} timing_request_t;

extern uint64_t FUN_01025084(void);
extern void FUN_010225ac(uint32_t, uint32_t, const uint8_t *,
                         timing_request_t *, uint32_t);
extern uint32_t FUN_01021b7c(timing_request_t *, uint32_t,
                             uint8_t *, uint8_t *);
extern uint32_t FUN_0102286c(uint32_t, uint32_t);
extern uint32_t FUN_01024440(uint32_t);
extern __attribute__((noreturn)) void FUN_010256dc(uint32_t, uint32_t, ...);
extern void controller_deferred_event_raise(uint32_t);

static inline uint32_t irq_lock(void)
{
    uint32_t key;
    __asm__ volatile("mrs %0, primask\n\tcpsid i" : "=r" (key) :: "memory");
    return key;
}

static inline void irq_restore(uint32_t key)
{
    if (key == 0u)
        __asm__ volatile("cpsie i" ::: "memory");
}

static inline volatile uint8_t *slot(volatile uint8_t *state,
                                     uint32_t bank, uint32_t index)
{
    return state + 0x50u + ((bank * 32u + index) * 2u);
}

static inline volatile uint8_t *list_meta(volatile uint8_t *state,
                                          uint32_t bank)
{
    return state + 0x30u + bank * 3u;
}

static __attribute__((always_inline)) inline void
unlink_and_reject(volatile uint8_t *state, uint32_t bank, uint32_t index)
{
    volatile uint8_t *entry = slot(state, bank, index);
    volatile uint8_t *meta = list_meta(state, bank);
    uint8_t next = meta[2];

    entry[0] = 4u;
    if (next == 0x20u)
        meta[1] = (uint8_t)index;
    else
        slot(state, bank, next)[1] = (uint8_t)index;
    meta[2] = (uint8_t)index;
    entry[1] = 0x20u;
}

uint32_t sdc_conn_window_admit(uint32_t index, const uint8_t *request)
{
    volatile uint8_t *const state = (volatile uint8_t *)UINT32_C(0x210016f0);
    volatile uint32_t *const scb_icsr = (volatile uint32_t *)UINT32_C(0xe000ed04);
    volatile uint8_t *const scb_shp = (volatile uint8_t *)UINT32_C(0xe000ed14);
    volatile uint8_t *const nvic_ipr = (volatile uint8_t *)UINT32_C(0xe000e400);
    volatile uint32_t *const bank_image = (volatile uint32_t *)UINT32_C(0x21001740);
    uint32_t exception = *scb_icsr & 0x1ffu;
    uint32_t priority;

    if (exception == 0u) {
        priority = 8u;
    } else {
        int32_t irq = (int8_t)(exception - 16u);
        uint8_t raw_priority;
        if (irq < 0)
            raw_priority = scb_shp[(uint32_t)irq & 0x0fu];
        else
            raw_priority = nvic_ipr[(uint32_t)irq];
        priority = raw_priority >> 5;
        if (priority == 0u) {
            if (state[0x4a] == 0x20u)
                FUN_010256dc(0x70u, 0x71au);
            if (request[0] != 0u)
                FUN_010256dc(0x70u, 0x71du);
        }
    }
    if (priority != 0u && request[0] > 1u)
        FUN_010256dc(0x70u, 0x721u);

    uint32_t saved_primask = 1u;
    for (;;) {
        irq_restore(saved_primask);

        uint32_t bank = state[0x49];
        uint32_t accepted = 0u;
        uint32_t was_inserted_at_head = 0u;
        state[0x39] = 0u;

        if (priority != 0u) {
            uint32_t next_bank = (bank + 1u) & 1u;
            volatile uint32_t *source = bank_image + bank * 16u;
            volatile uint32_t *dest = bank_image + next_bank * 16u;
            for (uint32_t word = 0; word != 16u; ++word)
                dest[word] = source[word];

            volatile uint8_t *source_meta = list_meta(state, bank);
            volatile uint8_t *dest_meta = list_meta(state, next_bank);
            *(volatile uint16_t *)dest_meta =
                *(volatile uint16_t *)source_meta;
            dest_meta[2] = source_meta[2];
            if (state[0x39] != 0u)
                continue;
            bank = next_bank;
        }

        uint64_t now = FUN_01025084();
        timing_request_t timing;
        FUN_010225ac((uint32_t)now, (uint32_t)(now >> 32), request,
                     &timing, bank);

        volatile uint8_t *entry = slot(state, bank, index);
        uint32_t state_code = entry[0];
        if (state_code == 1u || state_code == 2u) {
            uint32_t now24 = (uint32_t)now & 0x00ffffffu;
            uint32_t delta = timing.start - now24;
            uint32_t end_delta = timing.start + timing.duration - now24;
            uint32_t in_window = ((delta & 0x00fffffeu) != 0u) &&
                                 ((delta & 0x00ffffffu) <= 0x00800000u) &&
                                 ((end_delta & 0x00ffffffu) <= 0x00800000u);

            if (in_window == 0u) {
                unlink_and_reject(state, bank, index);
                accepted = 1u;
            } else {
                uint8_t predecessor;
                uint8_t successor;
                uint32_t fit = FUN_01021b7c(&timing, bank,
                                             &predecessor, &successor);
                if (fit == 0u) {
                    unlink_and_reject(state, bank, index);
                    accepted = 1u;
                } else {
                    volatile uint8_t *meta = list_meta(state, bank);
                    if (predecessor == successor) {
                        if (predecessor == 0x20u) {
                            entry[1] = meta[0];
                            meta[0] = (uint8_t)index;
                        } else {
                            entry[1] = slot(state, bank, predecessor)[1];
                            slot(state, bank, predecessor)[1] = (uint8_t)index;
                        }
                    } else {
                        uint8_t successor_next = slot(state, bank, successor)[1];
                        uint8_t displaced;
                        if (predecessor == 0x20u) {
                            displaced = meta[0];
                            meta[0] = successor_next;
                        } else {
                            displaced = slot(state, bank, predecessor)[1];
                            slot(state, bank, predecessor)[1] = successor_next;
                        }

                        uint8_t cursor = displaced;
                        uint8_t removed_index;
                        uint8_t next;
                        do {
                            removed_index = cursor;
                            volatile uint8_t *removed =
                                slot(state, bank, removed_index);
                            next = removed[1];
                            removed[0] = 5u;
                            cursor = next;
                        } while (removed_index != successor);

                        uint8_t tail = meta[2];
                        if (tail == 0x20u)
                            meta[1] = displaced;
                        else
                            slot(state, bank, tail)[1] = displaced;
                        meta[2] = removed_index;
                        slot(state, bank, removed_index)[1] = 0x20u;
                        entry[1] = next;

                        if (predecessor == 0x20u)
                            meta[0] = (uint8_t)index;
                        else
                            slot(state, bank, predecessor)[1] = (uint8_t)index;
                    }
                    entry[0] = 3u;
                    accepted = fit;
                    was_inserted_at_head = predecessor == 0x20u ? fit : 0u;
                }
            }
        }

        saved_primask = irq_lock();
        if (state[0x39] != 0u)
            continue;

        volatile uint32_t *published = (volatile uint32_t *)(state + 0xd8u + index * 32u);
        const uint32_t *prepared = (const uint32_t *)&timing;
        for (uint32_t word = 0; word != 6u; ++word)
            published[word] = prepared[word];

        if (accepted != 0u) {
            uint32_t disposition = 0u;
            if (priority == 0u) {
                state[0x39] = 0xffu;
            } else {
                if (was_inserted_at_head != 0u && state[0x4a] == 0x20u) {
                    disposition = FUN_0102286c(2u, bank);
                    if (disposition == 0u) {
                        if (request[0] == 0u) {
                            unlink_and_reject(state, state[0x49], index);
                            timing.owner = index;
                        } else if (request[0] == 1u) {
                            continue;
                        }
                    }
                }

                state[0x49] = (uint8_t)(~state[0x49] & 1u);
                state[0x39] = 0xffu;
                if (disposition == 2u) {
                    uint32_t delay = FUN_01024440(
                        *(volatile uint32_t *)(state + 0x10u) - (uint32_t)now);
                    void (*callback)(uint32_t) =
                        (void (*)(uint32_t))*(volatile uint32_t *)(state + 0x4d0u);
                    if (callback != 0)
                        callback(delay);
                } else if (disposition == 1u) {
                    void (*callback)(uint32_t) =
                        (void (*)(uint32_t))*(volatile uint32_t *)(state + 0x4d0u);
                    if (callback != 0)
                        callback(UINT32_MAX);
                }
            }
        }

        irq_restore(saved_primask);
        if (accepted != 0u) {
            uint32_t active_bank = state[0x49];
            if (list_meta(state, active_bank)[1] != 0x20u)
                controller_deferred_event_raise(state[0x4d9]);
        }
        return accepted;
    }
}
