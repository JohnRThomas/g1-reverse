/* Reconstructed FUN_00074bf4 @ 0x74bf4. */
#include <stdint.h>
#include <cmsis_gcc.h>

extern int FUN_00072040(uintptr_t);
extern void FUN_00072078(uintptr_t);
extern int FUN_0007205c(uintptr_t);
extern uint32_t FUN_00074b68(void);
extern uint32_t FUN_00074b7c(void);
extern void FUN_000638dc(uint32_t, uint32_t);
extern void FUN_0007e2fa(unsigned long, ...);
extern void FUN_0007e2ec(uintptr_t, uintptr_t);

void FUN_00074bf4(uint32_t *timer, uintptr_t source, uint32_t lo, int32_t hi)
{
    int64_t delay = ((int64_t)hi << 32) | lo;
    if (delay == -1) return;
    if (timer[0] != 0) {
        FUN_0007e2fa(0x99cbd, 0xf86fd, 0xf86d9, 0x6e);
        FUN_0007e2fa(0xf53ff);
        FUN_0007e2ec(0xf86d9, 0x6e);
    }
    timer[2] = (uint32_t)source;
    uint32_t key = __get_BASEPRI();
    __set_BASEPRI_MAX(0x20);
    __ISB();
    if (FUN_00072040(0x2000b498) == 0) {
        FUN_0007e2fa(0x99cbd, 0xf0920, 0xf08c7, 0x72);
        FUN_0007e2fa(0xf0935, 0x2000b498);
        FUN_0007e2ec(0xf08c7, 0x72);
    }
    FUN_00072078(0x2000b498);

    uint64_t ticks;
    if (delay >= -1) {
        ticks = (uint64_t)delay + 1U + (int32_t)FUN_00074b68();
    } else {
        int64_t limit = -(int64_t)*(uint64_t *)(uintptr_t)0x200069e0 - 2;
        int64_t remaining = limit - delay;
        ticks = remaining < 1 ? 1 : (uint64_t)remaining;
    }
    timer[4] = (uint32_t)ticks;
    timer[5] = (uint32_t)(ticks >> 32);

    uint32_t *head = (uint32_t *)(uintptr_t)0x20002cfc;
    uint32_t *tail = (uint32_t *)(uintptr_t)head[1];
    uint32_t *it = head[0] == (uint32_t)(uintptr_t)head ? 0 : (uint32_t *)(uintptr_t)head[0];
    while (it != 0) {
        uint64_t span = ((uint64_t)it[5] << 32) | it[4];
        uint64_t wanted = ((uint64_t)timer[5] << 32) | timer[4];
        if (wanted < span) {
            tail = (uint32_t *)(uintptr_t)it[1];
            span -= wanted;
            it[4] = (uint32_t)span;
            it[5] = (uint32_t)(span >> 32);
            timer[0] = (uint32_t)(uintptr_t)it;
            timer[1] = (uint32_t)(uintptr_t)tail;
            tail[0] = (uint32_t)(uintptr_t)timer;
            it[1] = (uint32_t)(uintptr_t)timer;
            goto inserted;
        }
        wanted -= span;
        timer[4] = (uint32_t)wanted;
        timer[5] = (uint32_t)(wanted >> 32);
        if (it == tail) break;
        it = (uint32_t *)(uintptr_t)it[0];
    }
    timer[0] = (uint32_t)(uintptr_t)head;
    timer[1] = (uint32_t)(uintptr_t)tail;
    tail[0] = (uint32_t)(uintptr_t)timer;
    head[1] = (uint32_t)(uintptr_t)timer;
inserted:
    if (head[0] != (uint32_t)(uintptr_t)head && timer == (uint32_t *)(uintptr_t)head[0])
        FUN_000638dc(FUN_00074b7c(), 0);
    if (FUN_0007205c(0x2000b498) != 0) {
        __set_BASEPRI(key);
        __ISB();
        return;
    }
    FUN_0007e2fa(0x99cbd, 0xf08f4, 0xf08c7, 0xf0);
    FUN_0007e2fa(0xf090b, 0x2000b498);
    FUN_0007e2ec(0xf08c7, 0xf0);
}
