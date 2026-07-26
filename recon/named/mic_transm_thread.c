/* readable reconstruction; identity: FUN_000324bc @ 0x000324bc
 * public-name: mic_transm_thread
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   mic_transm_thread                        <= FUN_000324bc @ 0x000324bc
 *   z_impl_k_sem_take                        <= FUN_00072908 @ 0x00072908
 *   device_api_call_slot0                    <= FUN_0007d120 @ 0x0007d120
 *   k_msleep_ticks32768_b                    <= FUN_0007d14a @ 0x0007d14a
 *   z_device_is_ready                        <= FUN_0008638c @ 0x0008638c
 *   z_impl_k_sem_init                        <= FUN_00086534 @ 0x00086534
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_87bf0                             @ 0x00087bf0
 *   rodata_9b45e                             @ 0x0009b45e   [INLINED -- G6 literal batch]
 *   rodata_9e2da                             @ 0x0009e2da   [INLINED -- G6 literal batch]
 *   rodata_a40e6                             @ 0x000a40e6   [INLINED -- G6 literal batch]
 *   rodata_a73e2                             @ 0x000a73e2   [INLINED -- G6 literal batch]
 *   rodata_a759e                             @ 0x000a759e   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_20002420                               @ 0x20002420
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_20007bd4                               @ 0x20007bd4
 */
/* Full reconstruction FUN_000324bc @ 0x000324bc (320-byte exact extent). CFG_VERIFY_PREFIX_FIRST */
#include <stdint.h>

extern void memset_bytes(void *, uint32_t, uint32_t);
extern uint64_t z_impl_k_sem_init(void *, uint32_t, uint32_t);
extern uint64_t z_impl_k_sem_take(void *, uint32_t, uint32_t, uint32_t);
extern int z_device_is_ready(void *);
extern void log_message(uintptr_t, ...);
extern void debug_print(uintptr_t, ...);
extern uint8_t *get_device_info(void);
extern int device_api_call_slot0(void *, uint32_t, void *, uint32_t);
extern void k_msleep_ticks32768_b(uint32_t);

struct message { uint32_t tag; uint16_t code; uint8_t data[204]; };

void mic_transm_thread(void)
{
    struct message message;
    uint8_t *gate = (uint8_t *)0x20007bd4u;
    uint8_t *object = (uint8_t *)0x00087bf0u;
    uint32_t failures = 0;
    message.tag = 0;
    memset_bytes(&message.code, 0, 0xca);
    uint64_t inherited = z_impl_k_sem_init(gate, 0, 1);
    for (;;) {
        inherited = z_impl_k_sem_take(gate, (uint32_t)(inherited >> 32),
                                 0xffffffffu, 0xffffffffu);
        message.tag = 0x01f1a55au;
        if (!z_device_is_ready(object)) {
            if (*(volatile int *)0x2000230cu > 0) {
                if (!*(volatile int *)0x20007554u)
                    log_message(((unsigned long)"%s():  [%s] device not ready.\n"), 0x000a759eu, *(uint32_t *)object);
                else debug_print(((unsigned long)"%s():  [%s] device not ready.\n"), 0x000a759eu, *(uint32_t *)object);
            }
            message.code = 0xca00u;
            uint8_t *state = get_device_info();
            ((void (*)(void *, uint32_t))*(uintptr_t *)(state + 0x788))(&message, 10);
        } else {
            uint8_t *state = get_device_info();
            if (*(uint32_t *)(state + 0x1030)) {
                uint32_t page = 0;
                for (;;) {
                    uint32_t address = *(volatile uint32_t *)0x20002420u + page * 200u;
                    log_message(0x000a73e2u, address, page);
                    if (device_api_call_slot0(object, address, message.data, 200)) {
                        log_message(((unsigned long)"Flash read failed! %d\n"));
                        message.code = (uint16_t)(0xca00u | (uint8_t)page);
                        state = get_device_info();
                        ((void (*)(void *, uint32_t))*(uintptr_t *)(state + 0x788))(&message, 10);
                        break;
                    }
                    message.code = (uint8_t)page;
                    uint32_t erased = 0;
                    for (uint32_t i = 0; i < 20; ++i) erased += message.data[i] == 0xffu;
                    if (erased == 20 || address > 0x410000u) {
                        message.code = 0x0100u;
                        state = get_device_info();
                        ((void (*)(void *, uint32_t))*(uintptr_t *)(state + 0x788))(&message, 10);
                        break;
                    }
                    state = get_device_info();
                    int sent = ((int (*)(void *, uint32_t))*(uintptr_t *)(state + 0x788))(&message, 0xce);
                    if (sent < 0) {
                        failures = (failures + 1u) & 0xffu;
                        if (failures > 9) {
                            if (*(volatile int *)0x2000230cu > 0) {
                                if (!*(volatile int *)0x20007554u)
                                    log_message(0x0009b45eu, 0x000a759eu, failures);
                                else debug_print(0x0009b45eu, 0x000a759eu, failures);
                            }
                            failures = 0;
                            break;
                        }
                    } else page = (page + 1u) & 0xffffu;
                    k_msleep_ticks32768_b(20);
                }
            }
        }
        memset_bytes(&message, 0, 0xce);
    }
}
