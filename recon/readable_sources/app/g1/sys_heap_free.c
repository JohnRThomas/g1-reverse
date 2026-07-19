#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0004b214 @ 0x0004b214
 * public-name: sys_heap_free
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   sys_heap_free                            <= FUN_0004b214 @ 0x0004b214
 *   chunk_field                              <= FUN_0007ddec @ 0x0007ddec
 *   chunk_size                               <= FUN_0007de18 @ 0x0007de18
 *   set_chunk_used                           <= FUN_0007de24 @ 0x0007de24
 *   mem_to_chunkid                           <= FUN_0007de5c @ 0x0007de5c
 *   free_chunk                               <= FUN_0007e0a6 @ 0x0007e0a6
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f0692                             @ 0x000f0692
 *   rodata_f06b3                             @ 0x000f06b3
 *   rodata_f06c4                             @ 0x000f06c4
 *   rodata_f06fc                             @ 0x000f06fc
 *   rodata_f0722                             @ 0x000f0722
 */
/* Full reconstruction of FUN_0004b214 @ 0x4b214 (130-byte extent). */
#include <stdint.h>

extern uint32_t mem_to_chunkid(uint32_t object, uint32_t length, uint32_t mode);
extern uint32_t chunk_field(uint32_t object, uint32_t offset, uint32_t mode);
extern uint32_t chunk_size(uint32_t object, uint32_t offset);
extern uint32_t set_chunk_used(uint32_t object, uint32_t offset);
extern void free_chunk(uint32_t value, uint32_t offset);
extern void printk(uintptr_t format, ...);
extern _Noreturn void assert_post_action(uintptr_t file, uint32_t line);

void sys_heap_free(const uint32_t *owner, uint32_t length,
                  uint32_t unused, uint32_t context)
{
    (void)unused;
    if (length == 0)
        return;

    uint32_t object = *owner;
    uint32_t start = mem_to_chunkid(object, length, 1);
    if ((chunk_field(object, start, 1) & 1u) == 0) {
        printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/, ((unsigned long)&rodata_f06b3) /*=0xf06b3*/, ((unsigned long)&rodata_f0692) /*=0xf0692*/, 0xafu,
                     context);
        printk(((unsigned long)&rodata_f06c4) /*=0xf06c4*/, length);
        assert_post_action(((unsigned long)&rodata_f0692) /*=0xf0692*/, 0xafu);
    }

    uint32_t end = start + chunk_size(object, start);
    if (start != end - chunk_field(object, end, 0)) {
        printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/, ((unsigned long)&rodata_f06fc) /*=0xf06fc*/, ((unsigned long)&rodata_f0692) /*=0xf0692*/, 0xb7u,
                     context);
        printk(((unsigned long)&rodata_f0722) /*=0xf0722*/, length);
        assert_post_action(((unsigned long)&rodata_f0692) /*=0xf0692*/, 0xb7u);
    }

    free_chunk(set_chunk_used(object, start), start);
}
