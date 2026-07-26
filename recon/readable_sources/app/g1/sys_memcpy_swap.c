#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0005ec84 @ 0x0005ec84
 * public-name: sys_memcpy_swap
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   sys_memcpy_swap                          <= FUN_0005ec84 @ 0x0005ec84
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f3894                             @ 0x000f3894   [INLINED -- G6 literal batch]
 *   rodata_f38c6                             @ 0x000f38c6   [INLINED -- G6 literal batch]
 *   rodata_f391d                             @ 0x000f391d   [INLINED -- G6 literal batch]
 */
/* Reconstructed FUN_0005ec84 @ 0x5ec84, exact extent 70 bytes. */
#include <stdint.h>
#include "../../../headers/g1_log.h"

extern void assert_post_action(uintptr_t file, uint32_t line);

void sys_memcpy_swap(uint8_t *destination, const uint8_t *source, uint32_t length)
{
    uintptr_t dst = (uintptr_t)destination;
    uintptr_t src = (uintptr_t)source;
    if (dst == src || (src < dst ? src + length > dst : dst + length > src)) {
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)"((psrc < pdst && (psrc + length) <= pdst) || (psrc > pdst && (pdst + length) <= psrc))") /*=0xf38c6*/, ((unsigned long)"WEST_TOPDIR/zephyr/include/zephyr/sys/byteorder.h") /*=0xf3894*/, 0x215u);
        printk(((unsigned long)"\tSource and destination buffers must not overlap\n") /*=0xf391d*/);
        assert_post_action(((unsigned long)"WEST_TOPDIR/zephyr/include/zephyr/sys/byteorder.h") /*=0xf3894*/, 0x215u);
        return;
    }

    const uint8_t *read = source + length;
    uint8_t *write = destination;
    while (write != destination + length)
        *write++ = *--read;
}
