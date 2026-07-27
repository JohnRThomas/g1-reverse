/* Reconstructed FUN_000507d4 @ 0x507d4 */
#include <stdint.h>

extern void FUN_0004ff6c(int, void *);
extern int FUN_000503d8(int, uint8_t *);
extern int FUN_00050558(int, uint8_t *);
extern int FUN_000506ac(void);
extern void FUN_0007e2ec(uint32_t, uint32_t);
extern void FUN_0007e2fa(unsigned long, ...);
extern void FUN_00080780(uint32_t, uint32_t, void *);
extern void FUN_00086c04(void *, const void *, uint32_t);

struct log2 { uint32_t count, message; };

static __attribute__((always_inline)) inline void log_message(uint32_t message)
{
    struct log2 log = { 2, message };
    FUN_00080780(UINT32_C(0x00088258), 0x1040, &log);
}

void FUN_000507d4(int first, int frame, uint32_t exc_return)
{
    volatile uint32_t *const scb = (volatile uint32_t *)UINT32_C(0xe000ed00);
    uint32_t exception = scb[1] & 0x1ffu;
    uint8_t handled = 0;
    uint8_t saved_frame[0x68];
    uint32_t stacked_xpsr;
    int result = 0;
    int use_supplied_frame;

    __atomic_signal_fence(__ATOMIC_SEQ_CST);
    if ((exc_return & 0xff000000u) != 0xff000000u)
        goto invalid;
    if ((exc_return & 0x0cu) == 8u) {
        log_message(UINT32_C(0x000f1fa6));
        goto invalid;
    }

    use_supplied_frame = (int32_t)(exc_return << 28) < 0;
    if (!use_supplied_frame)
        frame = first;
    if (frame == 0)
        goto invalid;

    if ((uint32_t)(exception - 3u) > 9u) {
        struct {
            uint32_t type;
            uint32_t message;
            uint16_t flags;
            uint16_t pad;
            int32_t exception;
            uint32_t context;
            uint32_t count;
        } detail;
        detail.type = UINT32_C(0x01000004);
        detail.message = UINT32_C(0x000f211b);
        detail.flags = 0x200;
        detail.pad = 0;
        detail.exception = (int32_t)exception - 0x10;
        detail.context = (scb[1] & 0x1f0u) ? UINT32_C(0x000f1f8d)
                                           : UINT32_C(0x000f1f78);
        detail.count = 0;
        FUN_00080780(UINT32_C(0x00088258), 0x2440, &detail);
        goto deliver;
    }

    switch (exception) {
    case 3:
        log_message(UINT32_C(0x000f2022));
        handled = 0;
        if ((int32_t)(scb[0x2c / 4] << 2) < 0) {
            log_message(UINT32_C(0x000f2039));
            result = 0;
            break;
        }
        if ((int32_t)scb[0x2c / 4] < 0) {
            log_message(UINT32_C(0x000f205a));
            result = 0;
            break;
        }
        if ((int32_t)(scb[0x2c / 4] << 1) >= 0) {
            FUN_0007e2fa(UINT32_C(0x00099cbd), UINT32_C(0x000f20a3),
                         UINT32_C(0x000f1d11), 0x32e);
            FUN_0007e2fa(UINT32_C(0x000f20c7));
            FUN_0007e2ec(UINT32_C(0x000f1d11), 0x32e);
        }
        log_message(UINT32_C(0x000f2068));
        scb[0x14 / 4] |= 0x100u;
        __atomic_thread_fence(__ATOMIC_SEQ_CST);
        {
            uint16_t opcode = *(const uint16_t *)(uintptr_t)
                              (*(const uint32_t *)(frame + 0x18) - 2u);
            scb[0x14 / 4] &= ~0x100u;
            __atomic_thread_fence(__ATOMIC_SEQ_CST);
            if (opcode == 0xdf02u) {
                struct { uint32_t type, message, value; } detail =
                    { 3, UINT32_C(0x000f2087), *(const uint32_t *)frame };
                FUN_00080780(UINT32_C(0x00088258), 0x1840, &detail);
                result = *(const int *)frame;
            } else if ((scb[0x28 / 4] & 0xffu) != 0) {
                result = FUN_000503d8(1, &handled);
            } else if ((scb[0x28 / 4] & 0xff00u) != 0) {
                result = FUN_00050558(1, &handled);
            } else if (scb[0x28 / 4] >= 0x10000u) {
                result = FUN_000506ac();
            } else {
                FUN_0007e2fa(UINT32_C(0x00099cbd), UINT32_C(0x000f20f7),
                             UINT32_C(0x000f1d11), 0x32a);
                FUN_0007e2fa(UINT32_C(0x000f20c7));
                FUN_0007e2ec(UINT32_C(0x000f1d11), 0x32a);
            }
        }
        break;
    case 4:
        result = FUN_000503d8(0, &handled);
        break;
    case 5:
        result = FUN_00050558(0, &handled);
        break;
    case 6:
        result = FUN_000506ac();
        break;
    case 12:
        log_message(UINT32_C(0x000f20f7));
        log_message(UINT32_C(0x000f2068));
        result = 0;
        break;
    default:
        {
            struct {
                uint32_t type, message;
                int32_t exception;
                uint16_t flags, pad;
                uint32_t context;
            } detail = {
                UINT32_C(0x01000004), UINT32_C(0x000f211b),
                (int32_t)exception - 0x10, 0x200, 0,
                (scb[1] & 0x1f0u) ? UINT32_C(0x000f1f8d)
                                   : UINT32_C(0x000f1f78)
            };
            FUN_00080780(UINT32_C(0x00088258), 0x2440, &detail);
        }
        result = 0;
        break;
    }

deliver:
    if (!handled) {
        FUN_00086c04(saved_frame, (const void *)(uintptr_t)frame, 0x68);
        stacked_xpsr = *(uint32_t *)(saved_frame + 0x60);
        if (use_supplied_frame)
            stacked_xpsr &= 0xfffffe00u;
        else if ((stacked_xpsr & 0x1ffu) == 0)
            stacked_xpsr = ~(~(stacked_xpsr >> 9) << 9);
        *(uint32_t *)(saved_frame + 0x60) = stacked_xpsr;
        FUN_0004ff6c(result, saved_frame);
    }
    return;

invalid:
    FUN_0007e2fa(UINT32_C(0x00099cbd), UINT32_C(0x000f1fd1),
                 UINT32_C(0x000f1d11), 0x458);
    FUN_0007e2fa(UINT32_C(0x000f1fe4));
    FUN_0007e2ec(UINT32_C(0x000f1d11), 0x458);
    /* Production never returns from the fatal handler.  Preserve the raw
       continuation for differential execution, where callees are oracles. */
    {
        struct {
            uint32_t type, message;
            int32_t exception;
            uint16_t flags, pad;
            uint32_t context;
        } detail = {
            UINT32_C(0x01000004), UINT32_C(0x000f211b),
            0x448, 0x200, 0, UINT32_C(0x000f1f78)
        };
        FUN_00080780(UINT32_C(0x00088258), 0x2440, &detail);
    }
    result = 0;
    handled = 0;
    use_supplied_frame = 0;
    frame = first;
    goto deliver;
}
