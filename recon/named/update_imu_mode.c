/* readable reconstruction; identity: FUN_00026100 @ 0x00026100
 * public-name: update_imu_mode
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_type                          <= FUN_00016568 @ 0x00016568
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   dev_api_call_slot0                       <= FUN_0007ca54 @ 0x0007ca54
 * address symbols (name @ address):
 *   rodata_87d58                             @ 0x00087d58
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* CPUAPP update_imu_mode @ 0x00026100.
 * Raw/back-map identity: FUN_00026100, exact extent 0x150 bytes. */
#include <stdint.h>
#include "../headers/g1_log.h"

extern int get_device_type(void);
extern unsigned int dev_api_call_slot0(int, unsigned int, unsigned int);
extern void wait_for_event(uint32_t ticks, uint32_t unused);

#define LOG_LEVEL (*(volatile int32_t *)0x2000230cu)
#define LOG_ROUTE (*(volatile uint32_t *)0x20007554u)

#define IMU_LOG(format, arg0, arg1) do { \
    if (LOG_ROUTE == 0u) \
        log_message((format), 0x0009f773u, (arg0), (arg1)); \
    else \
        debug_print((format), 0x0009f773u, (arg0), (arg1)); \
} while (0)

uint32_t update_imu_mode(uint8_t *fusion, uint32_t mode,
                      uint32_t unused2, uint32_t retry_context)
{
    uint32_t attempt;
    int32_t result;
    uint32_t frequency = 0u;

    (void)unused2;
    if (get_device_type() != 1)
        return 0u;

    if (fusion[0x14] != 0u) {
        if (LOG_LEVEL > 1)
            IMU_LOG(0x0009fb32u, 0u, 0u);
        return 0xffffffffu;
    }

    (void)get_device_type();
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
        result = dev_api_call_slot0(*(volatile uint32_t *)(fusion + 0x1c),
                              3u, fusion + 0x20);
        if (result >= 0)
            break;
        if (LOG_LEVEL > 1)
            IMU_LOG(0x0009f9d9u, (uint32_t)result, retry_context);
        wait_for_event(0xa4u, 0u);
    }
    if (result < 0)
        return 0xfffffffdu;

    if (mode < 3u) {
        *(volatile uint32_t *)(fusion + 0x20) = 0u;
        *(volatile uint32_t *)(fusion + 0x24) = 0u;
    }
    for (attempt = 1u; attempt != 0x15u; ++attempt) {
        result = dev_api_call_slot0(*(volatile uint32_t *)(fusion + 0x1c),
                              7u, fusion + 0x20);
        if (result >= 0)
            break;
        if (LOG_LEVEL > 1)
            IMU_LOG(0x0009fa36u, attempt, 0u);
        wait_for_event(0xa4u, 0u);
    }
    if (result < 0)
        return 0xfffffffcu;

    if (LOG_LEVEL > 1)
        IMU_LOG(((unsigned long)"%s(): imu sensor update to mode %d\n") /*=0x9fa78*/, mode, 0u);
    return 0u;
}
