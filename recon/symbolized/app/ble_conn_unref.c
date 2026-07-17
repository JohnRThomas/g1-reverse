#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000566a4 @ 0x000566a4
 * public-name: ble_conn_unref
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ble_conn_unref                           <= FUN_000566a4 @ 0x000566a4
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f3a5d                             @ 0x000f3a5d
 *   rodata_f3c07                             @ 0x000f3c07
 *   rodata_f3c0f                             @ 0x000f3c0f
 */
/* Reconstructed FUN_000566a4 @ 0x566a4  true code extent: 0x50 bytes */
#include <stdint.h>

extern void printk(uint32_t module, ...);
extern void assert_post_action(uint32_t source, uint32_t line);
extern void FUN_00055aac(void *object);

void ble_conn_unref(uint8_t *object)
{
    uint32_t *references = (uint32_t *)(object + 0xd0);
    uint32_t previous = __atomic_fetch_sub(references, 1, __ATOMIC_ACQ_REL);

    if ((int32_t)previous <= 0) {
        printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/, ((unsigned long)&rodata_f3c07) /*=0xf3c07*/, ((unsigned long)&rodata_f3a5d) /*=0xf3a5d*/, 0x525);
        printk(((unsigned long)&rodata_f3c0f) /*=0xf3c0f*/);
        assert_post_action(((unsigned long)&rodata_f3a5d) /*=0xf3a5d*/, 0x525);
    }

    if (*(volatile uint16_t *)(object + 2) == 0x101 &&
        __atomic_load_n(references, __ATOMIC_ACQUIRE) == 0)
        FUN_00055aac(object);
}
