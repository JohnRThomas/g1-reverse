#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0004c418 @ 0x0004c418
 * public-name: FUN_0004c418
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   nrf53_ipc_channel_configure              <= FUN_0004c278 @ 0x0004c278
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

extern int32_t FUN_000635d8(uint32_t channel);
extern uint32_t FUN_00063570(uint32_t channel);
extern void nrf53_ipc_channel_configure(uint32_t id, uint32_t channel, uint32_t priority,
                        uint32_t zero);
extern void FUN_00064f48(uint32_t id, uint32_t state);
extern void FUN_00063778(uint32_t channel, uint32_t state, uint32_t length,
                        uint32_t zero, uintptr_t callback, uint32_t descriptor);
extern void printk(uintptr_t domain, uintptr_t message,
                        uintptr_t file, uint32_t line);
extern void assert_post_action(uintptr_t file, uint32_t line) __attribute__((noreturn));

void FUN_0004c418(void *object, uint32_t context, uint32_t descriptor)
{
    uintptr_t vtable = *(uintptr_t *)((uint8_t *)object + 8);
    prepare_fn prepare = *(prepare_fn *)(vtable + 0x10);

    if (prepare == 0 || prepare(object, context, 0) != 0) {
        printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/, ((unsigned long)&rodata_a7a10) /*=0xa7a10*/, ((unsigned long)&rodata_f0a90) /*=0xf0a90*/, 0xcbu);
        assert_post_action(((unsigned long)&rodata_f0a90) /*=0xf0a90*/, 0xcbu);
    }

    uint32_t channel = (descriptor >> 8) & 0xffu;
    int32_t timing = FUN_000635d8(channel);
    uint32_t id = descriptor & 0xffu;
    nrf53_ipc_channel_configure(id, channel, descriptor >> 24, 0);
    uint32_t state = FUN_00063570(channel);
    uint32_t slot = (descriptor >> 16) & 0xffu;

    if (slot >= 16) {
        printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/, ((unsigned long)&rodata_f0a5d) /*=0xf0a5d*/, ((unsigned long)&rodata_f0a2b) /*=0xf0a2b*/, 0x1e1u);
        assert_post_action(((unsigned long)&rodata_f0a2b) /*=0xf0a2b*/, 0x1e1u);
    }

    *(volatile uint32_t *)(0x5002a080u + ((slot << 2) & 0xffu)) =
        id | 0x80000000u;
    FUN_00064f48(id, state);
    FUN_00063778(channel, state, (uint32_t)(timing + 0x32) << 1,
                  0, ((unsigned long)&rodata_4c38d) /*=0x4c38d*/, descriptor);
}
