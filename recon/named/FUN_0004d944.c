/* readable reconstruction; identity: FUN_0004d944 @ 0x0004d944
 * public-name: FUN_0004d944
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   ADDR_z_cbprintf_cpy_THUMB                @ 0x0007ee49
 *   rodata_881e0                             @ 0x000881e0
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f0dff                             @ 0x000f0dff
 *   rodata_f0e3e                             @ 0x000f0e3e
 *   rodata_f0e6a                             @ 0x000f0e6a
 */
/* Full reconstruction of FUN_0004d944 @ 0x4d944 (268 bytes). */
#include <stdint.h>

extern uintptr_t FUN_0004d55c(uint32_t words);
extern int32_t FUN_0004abc0(uintptr_t source, uint32_t count, uintptr_t callback,
                           void *state, uint32_t type, void *buffer, uint32_t width);
extern void FUN_0007ee74(uintptr_t, uintptr_t, uint32_t, uintptr_t);
extern void printk(uint32_t, ...);
extern void assert_post_action(uint32_t, uint32_t) __attribute__((noreturn));

struct format_state {
    uintptr_t destination;
    uint32_t used;
    uint32_t zero;
};

void FUN_0004d944(uintptr_t owner, uint32_t descriptor, uintptr_t source, uintptr_t arg4)
{
    uint32_t encoded = (descriptor >> 9) & 0x7ffu;
    uint32_t requested = encoded;
    uint32_t upper = descriptor >> 20;
    uintptr_t allocation;

    if (!encoded) {
        allocation = FUN_0004d55c(((upper + 0x17u) & ~7u) >> 2);
    } else {
        struct format_state state = {0, 0, 0};
        uint8_t scratch[8];
        int32_t length = FUN_0004abc0(source, encoded, 0, &state, 10, scratch, 4);
        if ((uint32_t)length >= 0x800u) {
            struct overflow_log {
                uint32_t type;
                uint32_t string;
                uint32_t value;
                uint32_t limit;
                uint16_t code;
            };
            struct overflow_log *log = __builtin_alloca(sizeof(*log));
            log->type = 0x01000004u;
            log->string = 0x000f0dffu;
            log->value = *(volatile uint32_t *)(source + 4);
            log->limit = 0x7ffu;
            log->code = 0x200u;
            FUN_0004d944(0x000881e0u, 0x2480u, (uintptr_t)log, 0);
            return;
        }
        encoded = (uint32_t)length & 0x7ffu;
        allocation = FUN_0004d55c(((upper + 0x17u + (uint32_t)length) & ~7u) >> 2);
        descriptor &= 0xfff001ffu;
        if (allocation) {
            state.destination = allocation + 0x10u;
            state.used = (uint32_t)length;
            state.zero = 0;
            int32_t rc = FUN_0004abc0(source, requested, 0x0007ee49u, &state,
                                      10, scratch, 4);
            if (rc < 0) {
                printk(0x00099cbdu, 0x000f0e6au, 0x000f0e3eu, 0x59u);
                assert_post_action(0x000f0e3eu, 0x59u);
            }
        }
    }
    descriptor = (descriptor & 0xfff001ffu) | (encoded << 9);
    FUN_0007ee74(allocation, owner, descriptor, arg4);
}
