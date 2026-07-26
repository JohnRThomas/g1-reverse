/* readable reconstruction; identity: FUN_00071df8 @ 0x00071df8
 * public-name: z_setup_new_thread
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   arch_new_thread                          <= FUN_000502c4 @ 0x000502c4
 *   z_setup_new_thread                       <= FUN_00071df8 @ 0x00071df8
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f7f4b                             @ 0x000f7f4b
 *   rodata_f7f6e                             @ 0x000f7f6e
 *   rodata_f7fee                             @ 0x000f7fee
 *   g_current_thread_ptr                     @ 0x2000b450
 */
/* FUN_00071df8 @ 0x00071df8 — complete 154-byte code reconstruction. */
#include <stdint.h>
#include "../headers/g1_log.h"

extern void arch_new_thread(uintptr_t, uintptr_t, uintptr_t, uintptr_t,
                         uintptr_t, uintptr_t, uintptr_t);
extern void assert_post_action(uintptr_t, uint32_t) __attribute__((noreturn));

uintptr_t z_setup_new_thread(uint8_t *object, uintptr_t buffer, uint32_t size,
                       uintptr_t operation, uintptr_t arg4, uintptr_t arg5,
                       uintptr_t arg6, int32_t offset, uint32_t tag)
{
    if (!((offset == 15 && operation == 0x00072089u) ||
          (offset != 15 && (uint32_t)(offset + 16) <= 30u))) {
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"), 0x000f7f6eu, 0x000f7f4bu, 0x21au,
                     object, buffer, size, operation);
        printk(0x000f7feeu, offset, 14u, 0xfffffff0u);
        assert_post_action(0x000f7f4bu, 0x21au);
    }

    uintptr_t list = (uintptr_t)(object + 0x58);
    *(uintptr_t *)(object + 0x58) = list;
    *(uintptr_t *)(object + 0x5c) = list;
    object[0x0c] = (uint8_t)tag;
    uint32_t aligned = (size + 7u) & ~7u;
    *(uintptr_t *)(object + 0x7c) = buffer;
    *(uint32_t *)(object + 0x80) = aligned;
    object[0x0e] = (uint8_t)offset;
    uintptr_t end = buffer + aligned;
    object[0x0d] = 4;
    *(uint32_t *)(object + 0x18) = 0;
    *(uint32_t *)(object + 0x1c) = 0;
    *(uint32_t *)(object + 8) = 0;
    object[0x0f] = 0;
    *(uint32_t *)(object + 0x84) = 0;
    arch_new_thread((uintptr_t)object, buffer, end, operation, arg4, arg5, arg6);
    *(uint32_t *)(object + 0x54) = 0;
    uintptr_t owner = *(uintptr_t *)0x2000b450u;
    *(uint32_t *)(object + 0x74) = 0;
    object[0x70] = 0;
    *(uintptr_t *)(object + 0x88) = owner ? *(uintptr_t *)(owner + 0x88) : 0;
    return end;
}
