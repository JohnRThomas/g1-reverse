/* readable reconstruction; identity: FUN_00058b78 @ 0x00058b78
 * public-name: FUN_00058b78
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f4388                             @ 0x000f4388
 *   rodata_f457a                             @ 0x000f457a
 *   rodata_f457f                             @ 0x000f457f
 *   rodata_f4589                             @ 0x000f4589
 *   rodata_f4590                             @ 0x000f4590
 */
/* Full reconstruction FUN_00058b78 @ 0x58b78, exact extent 108 bytes. */
#include <stdint.h>

extern void printk(uintptr_t, ...);
extern void assert_post_action(uintptr_t, uint32_t) __attribute__((noreturn));
extern void FUN_00082030(void);

void FUN_00058b78(uint8_t *context, uint32_t *object,
                  uint32_t arg2, uint32_t arg3)
{
    uint32_t line;
    uintptr_t message;
    (void)arg2;
    if (context == 0) {
        line = 0x37c; message = 0x000f457au;
    } else if (object == 0) {
        line = 0x37d; message = 0x000f4590u;
    } else if (object[1] == 0) {
        line = 0x37e; message = 0x000f457fu;
    } else if (*(uint32_t *)(context + 0x124) != 0) {
        line = 0x37f; message = 0x000f4589u;
    } else {
        FUN_00082030();
        return;
    }
    printk(0x00099cbdu, message, 0x000f4388u, line, arg3);
    assert_post_action(0x000f4388u, line);
}
