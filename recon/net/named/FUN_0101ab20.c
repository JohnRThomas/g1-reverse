/* readable reconstruction; identity: FUN_0101ab20 @ 0x0101ab20
 * public-name: FUN_0101ab20
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_session_state_block                @ 0x210010a0
 */
/* net-core FUN_0101ab20 @ 0x101ab20 — true extent 532 bytes */
#include <stdint.h>

extern uint8_t *FUN_01019204(void);
extern uint64_t FUN_01022f0c(uint32_t);
extern uint32_t FUN_0101a130(void);
extern int FUN_01018dac(void *);
extern void FUN_01023d38(void);
extern int FUN_01018de8(void);
extern void FUN_010190d0(void);
extern void FUN_01020634(void);
extern void FUN_01022a84(void);
extern void FUN_0101920c(uint32_t, uint32_t);
extern int FUN_0101a38c(void *, uint32_t, uint32_t);
extern int FUN_010231c8(uint32_t, void *);
extern void FUN_0101a2e0(void);
extern int FUN_0101a218(void);
extern int FUN_01023ea8(uint32_t);
extern void FUN_01018df8(void);
extern void FUN_01020d1c(void);
extern void FUN_01008d00(uint32_t, uint32_t);

void FUN_0101ab20(uint32_t unused, uint32_t event)
{
    volatile uint8_t *const state = (volatile uint8_t *)0x210010a0U;
    uint8_t *packet = FUN_01019204();
    (void)unused;

    switch (event) {
    case 0: {
        uint8_t pending = state[1];
        state[0x14] = 1;
        if (pending == 0) {
            uint64_t now = FUN_01022f0c(packet[0]);
            uint32_t low = (uint32_t)now;
            uint32_t elapsed = low - *(volatile uint32_t *)(state + 0x50);
            uint32_t period = *(volatile uint32_t *)(state + 4);
            /* Original STM order is high word first, then low word. */
            *(volatile uint32_t *)(state + 0x1c) = (uint32_t)(now >> 32);
            *(volatile uint32_t *)(state + 0x18) = low;

            uint8_t slot = 0;
            uint32_t remainder = elapsed;
            if (state[0x2f] != 0) {
                uint32_t overhead = FUN_0101a130();
                period = *(volatile uint32_t *)(state + 4);
                elapsed = low - *(volatile uint32_t *)(state + 0x50);
                remainder = low - (period * (elapsed / period) +
                                   *(volatile uint32_t *)(state + 0x50));
                uint8_t index = 0;
                uint8_t count = 0;
                do {
                    uint32_t width = *(volatile uint32_t *)(state + (index + 2U) * 4U) + overhead;
                    if (width <= remainder) {
                        remainder -= width;
                        ++slot;
                    }
                    ++count;
                    index = count;
                } while (index <= state[0x2f]);
            }
            state[0x2e] = slot;

            struct {
                uint32_t timestamp;
                uint8_t mode;
                uint8_t reserved[8];
                uint8_t exact_period;
            } request;
            if (packet[3] == 0 && (packet[4] & 0x1fU) == 0) {
                request.mode = elapsed < period;
                request.exact_period = remainder == period * (remainder / period);
            } else {
                request.timestamp = *(volatile uint32_t *)(state + 0x48);
                request.mode = 3;
            }
            if (FUN_01018dac(&request) != 0)
                goto fatal_1ce;
            *(volatile uint32_t *)(state + 0x40) =
                *(volatile uint32_t *)(state + 0x38) - 0x109U;
            FUN_01023d38();
        }
        return;
    }

    case 1:
        if (state[1] == 0) {
            state[0x15] = 1;
            if (FUN_01018de8() != 0)
                goto fatal_1e1;
        } else {
            FUN_010190d0();
            if (state[0x14] != 0) {
                FUN_01020634();
                FUN_01022a84();
                state[0x14] = 0;
                state[0x15] = 0;
            }
        }
        return;

    case 2:
    case 3: {
        uint32_t channel = packet[0];
        uint8_t current[32];
        packet = FUN_01019204();
        if (packet[3] != 0 || (packet[4] & 0x1fU) != 0)
            FUN_0101920c(3, 1);
        if (FUN_0101a38c(current, 0, 1) == 0) {
            state[2] = 1;
            FUN_0101a2e0();
            return;
        }
        if (FUN_010231c8(channel, current) == 0)
            goto fatal_7e6;
        return;
    }

    case 4:
        FUN_01020d1c();
        return;

    case 5:
        FUN_01008d00(0x21, 0x217);
        return;

    case 6:
        if (packet[3] == 0 && (packet[4] & 0x1fU) == 0) {
            if (FUN_0101a218() != 0)
                return;
        } else if ((packet[1] & 0x0cU) != 0 && state[0x44] == 0) {
            state[0x44] = 1;
            if (FUN_01023ea8(0x4536) == 0) {
                *(volatile uint32_t *)(state + 0x40) += 0x4536U;
                *(volatile uint32_t *)(state + 0x38) += 0x4536U;
                FUN_01023d38();
                return;
            }
        }
        FUN_01018df8();
        return;

    case 7:
        FUN_0101a2e0();
        return;

    case 8:
        FUN_01008d00(0x21, 0x213);
        return;
    default:
        FUN_01008d00(0x21, 0x217);
        return;
    }

fatal_1e1:
    FUN_01008d00(0x21, 0x1e1);
    state[2] = 1;
    FUN_0101a2e0();
    return;
fatal_1ce:
    FUN_01008d00(0x21, 0x1ce);
    return;
fatal_7e6:
    FUN_01008d00(0x21, 0x7e6);
    return;
}
