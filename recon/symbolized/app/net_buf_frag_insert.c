#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0005f338 @ 0x0005f338
 * public-name: net_buf_frag_insert
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   net_buf_frag_last                        <= FUN_0005f304 @ 0x0005f304
 *   net_buf_frag_insert                      <= FUN_0005f338 @ 0x0005f338
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f539a                             @ 0x000f539a
 *   rodata_f5407                             @ 0x000f5407
 *   rodata_f542d                             @ 0x000f542d
 */
/* Full reconstruction FUN_0005f338 @ 0x5f338, exact extent 70 bytes. */
#include <stdint.h>
extern void *net_buf_frag_last(void *node);
extern void printk(uintptr_t, uintptr_t, uintptr_t, uint32_t);
extern __attribute__((noreturn)) void assert_post_action(uintptr_t, uint32_t);

void net_buf_frag_insert(void *owner, void *node)
{
    if (!owner) {
        printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/, ((unsigned long)&rodata_f5407) /*=0xf5407*/, ((unsigned long)&rodata_f539a) /*=0xf539a*/, 0x241);
        assert_post_action(((unsigned long)&rodata_f539a) /*=0xf539a*/, 0x241);
    }
    if (!node) {
        printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/, ((unsigned long)&rodata_f542d) /*=0xf542d*/, ((unsigned long)&rodata_f539a) /*=0xf539a*/, 0x242);
        assert_post_action(((unsigned long)&rodata_f539a) /*=0xf539a*/, 0x242);
    }
    void *previous = *(void **)((uint8_t *)owner + 4);
    if (previous)
        *(void **)((uint8_t *)net_buf_frag_last(node) + 4) = previous;
    *(void **)((uint8_t *)owner + 4) = node;
}
