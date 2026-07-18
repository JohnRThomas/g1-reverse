/* CPUAPP update_imu_mode @ 0x00026100.
 * Raw/back-map identity: FUN_00026100, exact extent 0x150 bytes. */
#include <stdint.h>

#define update_imu_mode FUN_00026100

extern int32_t FUN_00016568(void);
extern int32_t FUN_0007ca54(uintptr_t device, uint32_t attribute,
                            void *configuration);
extern void thunk_FUN_00074844(uint32_t ticks, uint32_t unused);
extern void DEBUG_PRINT(uintptr_t format, ...);
extern void FUN_00019c70(uintptr_t format, ...);

#define LOG_LEVEL (*(volatile int32_t *)0x2000230cu)
#define LOG_ROUTE (*(volatile uint32_t *)0x20007554u)

#define IMU_LOG(format, arg0, arg1) do { \
    if (LOG_ROUTE == 0u) \
        DEBUG_PRINT((format), 0x0009f773u, (arg0), (arg1)); \
    else \
        FUN_00019c70((format), 0x0009f773u, (arg0), (arg1)); \
} while (0)

uint32_t update_imu_mode(uint8_t *fusion, uint32_t mode,
                      uint32_t unused2, uint32_t retry_context)
{
    uint32_t attempt;
    int32_t result;
    uint32_t frequency = 0u;

    (void)unused2;
    if (FUN_00016568() != 1)
        return 0u;

    if (fusion[0x14] != 0u) {
        if (LOG_LEVEL > 1)
            IMU_LOG(0x0009fb32u, 0u, 0u);
        return 0xffffffffu;
    }

    (void)FUN_00016568();
    *(volatile uint32_t *)(fusion + 0x1c) = 0x00087d58u;
    if (mode == 1u)
        frequency = 0x0cu;
    else if (mode == 2u)
        frequency = 0x1au;
    else if (mode != 0u)
        frequency = *(volatile uint32_t *)(fusion + 0x20);
    *(volatile uint32_t *)(fusion + 0x20) = frequency;
    *(volatile uint32_t *)(fusion + 0x24) = 0u;

    for (attempt = 1u; attempt != 0x15u; ++attempt) {
        result = FUN_0007ca54(*(volatile uint32_t *)(fusion + 0x1c),
                              3u, fusion + 0x20);
        if (result >= 0)
            break;
        if (LOG_LEVEL > 1)
            IMU_LOG(0x0009f9d9u, (uint32_t)result, retry_context);
        thunk_FUN_00074844(0xa4u, 0u);
    }
    if (result < 0)
        return 0xfffffffdu;

    if (mode < 3u) {
        *(volatile uint32_t *)(fusion + 0x20) = 0u;
        *(volatile uint32_t *)(fusion + 0x24) = 0u;
    }
    for (attempt = 1u; attempt != 0x15u; ++attempt) {
        result = FUN_0007ca54(*(volatile uint32_t *)(fusion + 0x1c),
                              7u, fusion + 0x20);
        if (result >= 0)
            break;
        if (LOG_LEVEL > 1)
            IMU_LOG(0x0009fa36u, attempt, 0u);
        thunk_FUN_00074844(0xa4u, 0u);
    }
    if (result < 0)
        return 0xfffffffcu;

    if (LOG_LEVEL > 1)
        IMU_LOG(0x0009fa78u, mode, 0u);
    return 0u;
}
