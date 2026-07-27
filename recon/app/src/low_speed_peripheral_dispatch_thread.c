/* Full reconstruction low_speed_peripheral_dispatch_thread @ 0x2a8d8,
 * CFG-reviewed extent 1012 bytes (live tail through 0x2acca).
 * CFG_VERIFY_PREFIX_FIRST CFG_VERIFY_PREFIX_K=240
 */
#include <stdint.h>

extern void change_work_mode_to(uint32_t);
extern void FUN_0002c0e8(uint8_t *);
extern void DEBUG_PRINT(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);
extern int sync_to_slave(uint8_t *, uint32_t, uint32_t);
extern unsigned int FUN_00019b2c(void);
extern int FUN_0008149a(int, uint32_t);
extern void fuel_gauge_update(uintptr_t, uint32_t);
extern uint32_t FUN_0002eb40(void);
extern uint32_t FUN_0002eb78(void);
extern void FUN_00026b88(int, int, int);
extern void FUN_00016268(uint8_t *);
extern uint32_t FUN_00027448(uint8_t *, uint32_t, uint32_t);
extern void FUN_00033c5c(void);
extern void FUN_00025528(void);
extern void FUN_0002aeb4(void);
extern void FUN_0002ae84(void);
extern void FUN_0007d1d6(uint8_t *, uint32_t);
extern unsigned long long FUN_0007cb2c(void);
extern void FUN_0007cb8e(uint32_t);
extern uint32_t FUN_0004c0a8(uint32_t);
extern void thunk_FUN_00074844(uint32_t, uint32_t);
extern int FUN_00016580(void);
extern void FUN_000167b4(void);
extern void FUN_0001658c(uint32_t);
extern uint32_t FUN_00026c28(void);
extern void FUN_00026c8c(void);
extern void check_work_mode(uint32_t, uint32_t, uint32_t);
extern void FUN_00026a08(uint32_t);
extern void FUN_00056a68(int, uint32_t);
extern uintptr_t FUN_000167a8(void);
extern void FUN_0007cbfe(uintptr_t, uint32_t);
extern void FUN_0002316c(unsigned char *, int);
extern void FUN_0002a868(void);
extern void FUN_0007cbae(void);

static inline uint8_t rd8(uint8_t *p, unsigned o) { return *(volatile uint8_t *)(p + o); }
static inline void wr8(uint8_t *p, unsigned o, uint8_t v) { *(volatile uint8_t *)(p + o) = v; }
static inline uint32_t rd32(uint8_t *p, unsigned o) { return *(volatile uint32_t *)(p + o); }
static inline void wr32(uint8_t *p, unsigned o, uint32_t v) { *(volatile uint32_t *)(p + o) = v; }

void low_speed_peripheral_dispatch_thread(uint8_t *ctx)
{
    volatile int *const log_level = (volatile int *)0x2000230cu;
    volatile uint8_t *const phase_hold = (volatile uint8_t *)0x20018d91u;
    uint8_t tick = 0;
    int8_t connected_runs = 0;

    change_work_mode_to(3);
    FUN_0002c0e8(ctx);
    if (*log_level > 1) {
        if (*(volatile int *)0x20007554u == 0)
            DEBUG_PRINT(0x0009fc8bu, 0x000a19c0u);
        else
            FUN_00019c70(0x0009fc8bu, 0x000a19c0u);
    }
    *(volatile uint16_t *)(ctx + 0xfc4) = 0x8000;
    *(volatile uint16_t *)(ctx + 0xfc0) = 0;
    if (rd8(ctx, 0) == 1)
        sync_to_slave(ctx, rd8(ctx, 0xfea) == 12 ? 4 : 5, 0);

    for (;;) {
        tick = (uint8_t)(tick + 1);
        if (tick % 5 == 0) {
            int connection = FUN_00019b2c();
            if (connection == 0 || rd8(ctx, 0xae2) == 0 ||
                rd8(ctx, 0xae3) == 0 || rd32(ctx, 0x9b4) == 0) {
                connected_runs = 0;
            } else if (++connected_runs > 4) {
                int error = FUN_0008149a(connection, 2);
                if (error != 0 && *log_level > 2) {
                    if (*(volatile int *)0x20007554u == 0)
                        DEBUG_PRINT(0x000a1914u, 0x000a19c0u, error);
                    else
                        FUN_00019c70(0x000a1914u, 0x000a19c0u, error);
                }
                connected_runs = -5;
            }

            uint8_t a = rd8(ctx, 0xfc0), b = rd8(ctx, 0xfc1);
            wr8(ctx, 0xde, a <= b ? a : b);
            fuel_gauge_update(0x00087d70u, 0);
            uint32_t power = FUN_0002eb40();
            uint32_t thermal = FUN_0002eb78();
            uint32_t side = 0;

            FUN_00026b88(ctx, power, thermal);
            if (rd8(ctx, 0) == 1) {
                FUN_00016268(ctx);
                if (connection != 0 && rd8(ctx, 0xae3) == 0 && rd32(ctx, 0x9b4) != 0 &&
                    (rd8(ctx, 0x6de) & 1)) {
                    wr8(ctx, 0xe4, rd8(ctx, 0xe4) | 3);
                    *phase_hold = 3;
                    side = 1;
                } else if (*phase_hold != 0) {
                    --*phase_hold;
                } else {
                    wr8(ctx, 0xe4, rd8(ctx, 0xe4) & 0xfcu);
                }
                int elapsed = sync_to_slave(ctx, 12, 0);
                if (elapsed < 500 && (rd8(ctx, 0xe4) & 4)) {
                    FUN_00033c5c();
                    wr8(ctx, 0xe4, rd8(ctx, 0xe4) & 0xfbu);
                }
            } else {
                if (connection != 0 && rd8(ctx, 0xae3) == 0 && rd32(ctx, 0x9b4) != 0) {
                    *phase_hold = 3;
                    wr8(ctx, 0x6de, rd8(ctx, 0x6de) | 1);
                    side = 1;
                } else if (*phase_hold != 0) {
                    --*phase_hold;
                } else {
                    wr8(ctx, 0x6de, rd8(ctx, 0x6de) & 0xfeu);
                }
                if ((rd8(ctx, 0xe4) ^ rd8(ctx, 0x6de)) & 1)
                    wr8(ctx, 0x6df, (uint8_t)(rd8(ctx, 0x6df) + 1));
                uint32_t elapsed = FUN_00027448(ctx, 1, 0);
                if (elapsed < 500 && (rd8(ctx, 0x6de) & 4)) {
                    FUN_00033c5c();
                    wr8(ctx, 0x6de, rd8(ctx, 0x6de) & 0xfbu);
                    wr8(ctx, 0xe4, rd8(ctx, 0xe4) & 0xfbu);
                }
            }

            FUN_00025528();
            while (rd8(ctx, 1) == 1) {
                FUN_0002aeb4();
                if (rd8(ctx, 0) == 1)
                    FUN_0007d1d6(ctx, rd32(ctx, 0xfec));
                if ((int64_t)(FUN_0007cb2c() -
                              *(volatile uint64_t *)(ctx + 0x1060)) > 0x927bf) {
                    if (*log_level > 0) {
                        if (*(volatile int *)0x20007554u)
                            FUN_00019c70(0x000a193cu, 0x000a19c0u);
                        else
                            DEBUG_PRINT(0x000a193cu, 0x000a19c0u);
                    }
                    for (;;) {
                        FUN_0007cb8e(500);
                        uint32_t printed = FUN_0004c0a8(1);
                        DEBUG_PRINT(printed);
                    }
                }
                thunk_FUN_00074844(0x28000, 0);
            }
            if (*(volatile uint8_t *)0x2000302cu == 0)
                FUN_0002aeb4();
            else if (*(volatile uint8_t *)0x20018d90u == 0)
                FUN_0002ae84();
            if (rd8(ctx, 0) == 1)
                FUN_0007d1d6(ctx, rd32(ctx, 0xfec));
            if (FUN_00016580() != 0 && (int64_t)FUN_0007cb2c() >= 60000) {
                FUN_000167b4();
                FUN_0001658c(0);
            }
            if (*log_level > 1) {
                uint32_t mode = rd8(ctx, 0xfea);
                uint32_t value = FUN_00026c28();
                if (*(volatile int *)0x20007554u == 0)
                    DEBUG_PRINT(0x000a1962u, 0x000a19c0u, mode, value, side);
                else
                    FUN_00019c70(0x000a1962u, 0x000a19c0u, mode, value, side);
            }
            FUN_00026c8c();
            check_work_mode(power, thermal, side);
            FUN_00026a08(power);
            if (connection != 0 && rd8(ctx, 0x1068) == 0 &&
                (uint32_t)FUN_0007cb2c() - rd32(ctx, 0xae4) > 30000 && rd8(ctx, 1) != 1) {
                wr32(ctx, 0xae4, (uint32_t)FUN_0007cb2c());
                FUN_00056a68(connection, 0x13);
            }
            if (rd8(ctx, 0x108e) != 0) {
                wr8(ctx, 0x108e, 0);
                FUN_0007cbfe(FUN_000167a8(), 0);
                FUN_0002316c(ctx, 1);
            }
            FUN_0002a868();
            tick = 0;
        }
        FUN_0007cbae();
        if (*(volatile uint8_t *)0x20018d90u == 0)
            FUN_0002ae84();
        thunk_FUN_00074844(0x199a, 0);
    }
}
