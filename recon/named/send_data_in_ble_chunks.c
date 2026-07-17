/* readable reconstruction; identity: FUN_0003384c @ 0x0003384c
 * public-name: send_data_in_ble_chunks
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   strlen                                   <= FUN_0000ef12 @ 0x0000ef12
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   send_data_in_ble_chunks                  <= FUN_0003384c @ 0x0003384c
 * address symbols (name @ address):
 *   rodata_883c8                             @ 0x000883c8
 *   rodata_a7bf5                             @ 0x000a7bf5
 *   rodata_a833e                             @ 0x000a833e
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Full owned-CFG reconstruction FUN_0003384c @ 0x3384c. */
#include <stdint.h>

extern uint32_t log_message(uintptr_t format, ...);
extern uint32_t strlen(uint32_t command);
extern uintptr_t get_device_info(void);
extern uint32_t debug_print(uintptr_t format, ...);
extern uint32_t FUN_00033730(void *transport, const void *name,
                             const void *payload, uint32_t reserved);
extern int FUN_00087036(uint32_t command, const void *name, uint32_t value);

uint32_t send_data_in_ble_chunks(const uint8_t *request)
{
    const uint32_t *commands = (const uint32_t *)0x000883c8u;
    uint32_t command_copy[9];
    unsigned int i;

    if (request == 0)
        return 0;

    for (i = 0; i < 9; ++i)
        command_copy[i] = commands[i];

    for (i = 0; i < 9; ++i) {
        uint32_t value = strlen(command_copy[i]);
        if (FUN_00087036(command_copy[i], request + 0x10, value) == 0) {
            if (*(volatile int *)0x20007554u == 0)
                return log_message(0x000a7bf5u, 0x000a833eu,
                                   0x137, request + 0x10);
            return debug_print(0x000a7bf5u, 0x000a833eu,
                                0x137, request + 0x10);
        }
    }

    return FUN_00033730((void *)(get_device_info() + 0x77c),
                         request + 0x10, request + 0x30, 0);
}
