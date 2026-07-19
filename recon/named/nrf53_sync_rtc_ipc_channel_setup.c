/* readable reconstruction; identity: FUN_0004c418 @ 0x0004c418
 * public-name: nrf53_sync_rtc_ipc_channel_setup
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   nrf53_ipc_channel_configure              <= FUN_0004c278 @ 0x0004c278
 *   nrf53_sync_rtc_ipc_channel_setup         <= FUN_0004c418 @ 0x0004c418
 *   rtc_cc_reg_addr_get                      <= FUN_00063570 @ 0x00063570
 *   rtc_channel_cc_read                      <= FUN_000635d8 @ 0x000635d8
 *   nrf_rtc_set_alarm_channel                <= FUN_00063778 @ 0x00063778
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_4c38d                             @ 0x0004c38d
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_a7a10                             @ 0x000a7a10
 *   rodata_f0a2b                             @ 0x000f0a2b
 *   rodata_f0a5d                             @ 0x000f0a5d
 *   rodata_f0a90                             @ 0x000f0a90
 */
/* Full reconstruction of FUN_0004c418 @ 0x4c418 (184 bytes). */
#include <stdint.h>

typedef int (*prepare_fn)(void *object, uint32_t context, uint32_t zero);

extern int32_t rtc_channel_cc_read(uint32_t channel);
extern uint32_t rtc_cc_reg_addr_get(uint32_t channel);
extern void nrf53_ipc_channel_configure(uint32_t id, uint32_t channel, uint32_t priority,
                        uint32_t zero);
extern void nrfx_gppi_event_endpoint_setup(uint32_t id,
                                                    uint32_t state);
extern void nrf_rtc_set_alarm_channel(uint32_t channel, uint32_t state, uint32_t length,
                        uint32_t zero, uintptr_t callback, uint32_t descriptor);
extern void printk(uintptr_t domain, uintptr_t message,
                        uintptr_t file, uint32_t line);
extern void assert_post_action(uintptr_t file, uint32_t line) __attribute__((noreturn));

void nrf53_sync_rtc_ipc_channel_setup(void *object, uint32_t context, uint32_t descriptor)
{
    uintptr_t vtable = *(uintptr_t *)((uint8_t *)object + 8);
    prepare_fn prepare = *(prepare_fn *)(vtable + 0x10);

    if (prepare == 0 || prepare(object, context, 0) != 0) {
        printk(0x00099cbdu, 0x000a7a10u, 0x000f0a90u, 0xcbu);
        assert_post_action(0x000f0a90u, 0xcbu);
    }

    uint32_t channel = (descriptor >> 8) & 0xffu;
    int32_t timing = rtc_channel_cc_read(channel);
    uint32_t id = descriptor & 0xffu;
    nrf53_ipc_channel_configure(id, channel, descriptor >> 24, 0);
    uint32_t state = rtc_cc_reg_addr_get(channel);
    uint32_t slot = (descriptor >> 16) & 0xffu;

    if (slot >= 16) {
        printk(0x00099cbdu, 0x000f0a5du, 0x000f0a2bu, 0x1e1u);
        assert_post_action(0x000f0a2bu, 0x1e1u);
    }

    *(volatile uint32_t *)(0x5002a080u + ((slot << 2) & 0xffu)) =
        id | 0x80000000u;
    nrfx_gppi_event_endpoint_setup(id, state);
    nrf_rtc_set_alarm_channel(channel, state, (uint32_t)(timing + 0x32) << 1,
                  0, 0x0004c38du, descriptor);
}
