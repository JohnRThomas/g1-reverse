/* readable reconstruction; identity: FUN_0004ed3c @ 0x0004ed3c
 * public-name: gatt_dm_char_by_uuid
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gatt_dm_char_by_uuid                     <= FUN_0004ed3c @ 0x0004ed3c
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   bt_gatt_dm_attr_chrc_val                 <= FUN_0007f4a0 @ 0x0007f4a0
 *   bt_gatt_dm_char_next                     <= FUN_0007f4d6 @ 0x0007f4d6
 *   bt_uuid_cmp                              <= FUN_00080d3e @ 0x00080d3e
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f11bc                             @ 0x000f11bc
 *   rodata_f154a                             @ 0x000f154a
 */
/* Full reconstruction of FUN_0004ed3c @ 0x4ed3c (66-byte extent). */
#include <stdint.h>

extern uint32_t bt_gatt_dm_char_next(uint32_t collection, uint32_t previous);
extern const uint32_t *bt_gatt_dm_attr_chrc_val(void);
extern int bt_uuid_cmp(const void *key, uint32_t candidate);
extern void printk(uintptr_t format, ...);
extern _Noreturn void assert_post_action(uintptr_t file, uint32_t line);

uint32_t gatt_dm_char_by_uuid(uint32_t collection, const void *key)
{
    uint32_t current = 0;
    for (;;) {
        current = bt_gatt_dm_char_next(collection, current);
        if (current == 0)
            return 0;

        const uint32_t *candidate = bt_gatt_dm_attr_chrc_val();
        if (candidate == 0) {
            printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"), 0x000f154au, 0x000f11bcu, 0x21cu);
            assert_post_action(0x000f11bcu, 0x21cu);
        }
        if (bt_uuid_cmp(key, *candidate) == 0)
            return current;
    }
}
