/* readable reconstruction; identity: FUN_0004d944 @ 0x0004d944
 * public-name: z_log_msg_runtime_create
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   cbprintf_package_convert                 <= FUN_0004abc0 @ 0x0004abc0
 *   g1_recon_z_log_msg_alloc                 <= FUN_0004d55c @ 0x0004d55c
 *   z_log_msg_runtime_create                 <= FUN_0004d944 @ 0x0004d944
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   log_msg_finalize_commit                  <= FUN_0007ee74 @ 0x0007ee74
 * address symbols (name @ address):
 *   ADDR_z_cbprintf_cpy_THUMB                @ 0x0007ee49
 *   rodata_881e0                             @ 0x000881e0
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f0dff                             @ 0x000f0dff   [INLINED -- G6 literal batch]
 *   rodata_f0e3e                             @ 0x000f0e3e   [INLINED -- G6 literal batch]
 *   rodata_f0e6a                             @ 0x000f0e6a   [INLINED -- G6 literal batch]
 */
/* Full reconstruction of FUN_0004d944 @ 0x4d944 (268 bytes). */
#include <stdint.h>
#include "../headers/g1_log.h"

extern uintptr_t g1_recon_z_log_msg_alloc(uint32_t words);
extern int32_t cbprintf_package_convert(uintptr_t source, uint32_t count, uintptr_t callback,
                           void *state, uint32_t type, void *buffer, uint32_t width);
extern void log_msg_finalize_commit(uintptr_t, uintptr_t, uint32_t, uintptr_t);
extern void assert_post_action(uint32_t, uint32_t) __attribute__((noreturn));

struct format_state {
    uintptr_t destination;
    uint32_t used;
    uint32_t zero;
};

void z_log_msg_runtime_create(unsigned int owner, unsigned int descriptor, unsigned int source, unsigned int arg4) {
    uint32_t encoded = (descriptor >> 9) & 0x7ffu;
    uint32_t requested = encoded;
    uint32_t upper = descriptor >> 20;
    uintptr_t allocation;

    if (!encoded) {
        allocation = g1_recon_z_log_msg_alloc(((upper + 0x17u) & ~7u) >> 2);
    } else {
        struct format_state state = {0, 0, 0};
        uint8_t scratch[8];
        int32_t length = cbprintf_package_convert(source, encoded, 0, &state, 10, scratch, 4);
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
            z_log_msg_runtime_create(0x000881e0u, 0x2480u, (uintptr_t)log, 0);
            return;
        }
        encoded = (uint32_t)length & 0x7ffu;
        allocation = g1_recon_z_log_msg_alloc(((upper + 0x17u + (uint32_t)length) & ~7u) >> 2);
        descriptor &= 0xfff001ffu;
        if (allocation) {
            state.destination = allocation + 0x10u;
            state.used = (uint32_t)length;
            state.zero = 0;
            int32_t rc = cbprintf_package_convert(source, requested, 0x0007ee49u, &state,
                                      10, scratch, 4);
            if (rc < 0) {
                printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"), 0x000f0e6au, 0x000f0e3eu, 0x59u);
                assert_post_action(0x000f0e3eu, 0x59u);
            }
        }
    }
    descriptor = (descriptor & 0xfff001ffu) | (encoded << 9);
    log_msg_finalize_commit(allocation, owner, descriptor, arg4);
}
