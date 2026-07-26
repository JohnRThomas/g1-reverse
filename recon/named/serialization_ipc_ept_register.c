/* readable reconstruction; identity: FUN_000259d4 @ 0x000259d4
 * public-name: serialization_ipc_ept_register
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   serialization_ipc_ept_register           <= FUN_000259d4 @ 0x000259d4
 *   z_device_is_ready                        <= FUN_0008638c @ 0x0008638c
 *   kmutex_dlist_init                        <= FUN_000864c2 @ 0x000864c2
 * address symbols (name @ address):
 *   rodata_88a38                             @ 0x00088a38
 *   rodata_9f3fa                             @ 0x0009f3fa   [INLINED -- G6 literal batch]
 *   rodata_9f418                             @ 0x0009f418   [INLINED -- G6 literal batch]
 *   rodata_9f433                             @ 0x0009f433   [INLINED -- G6 literal batch]
 *   rodata_9f487                             @ 0x0009f487   [INLINED -- G6 literal batch]
 *   g_st25dv_i2c_dev                         @ 0x200023cc
 *   g_st25dv_i2c_cfg                         @ 0x20007a48
 *   g_eeprom_comm_mutex                      @ 0x20007a60
 */
/* Reconstructed FUN_000259d4 @ 0x259d4 */
#include <stdint.h>
#include "../headers/g1_log.h"

extern uint64_t z_device_is_ready(uint32_t);
extern void kmutex_dlist_init(uint32_t);

int serialization_ipc_ept_register(void)
{
    volatile uint8_t *descriptor = (volatile uint8_t *)0x20007a48u;
    volatile uint8_t *config = (volatile uint8_t *)0x200023ccu;

    *(volatile uint32_t *)(descriptor + 8) = 0x00088a38u;
    *(volatile uint16_t *)(config + 4) = 0x53;
    *(volatile uint16_t *)(config + 8) = 0x53;
    *(volatile uint32_t *)(config + 12) = 0x1000;
    *(volatile uint32_t *)(descriptor + 16) = 0x20007a60u;
    *(volatile uint32_t *)(descriptor + 4) = 0x200023ccu;

    kmutex_dlist_init(0x20007a60u);
    uint64_t status = z_device_is_ready(*(volatile uint32_t *)config);
    uint32_t format = (int32_t)status == 0 ? 0x0009f3fau : 0x0009f418u;
    log_message(format, (uint32_t)(status >> 32), 0x1000u, 0x20007a48u);

    status = z_device_is_ready(*(volatile uint32_t *)config);
    if ((int32_t)status == 0) {
        uint32_t base = *(volatile uint32_t *)config;
        log_message(0x0009f433u, *(volatile uint32_t *)(uintptr_t)base,
                    0x1000u, 0x20007a48u);
        return 0;
    }
    log_message(0x0009f487u, (uint32_t)(status >> 32),
                0x1000u, 0x20007a48u);
    return 0x20007a48;
}
