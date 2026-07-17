/* readable reconstruction; identity: FUN_00064f48 @ 0x00064f48
 * public-name: FUN_00064f48
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f6a09                             @ 0x000f6a09
 *   rodata_f6a46                             @ 0x000f6a46
 */
/* Reconstructed FUN_00064f48 @ 0x64f48 */
#include <stdint.h>

extern void printk(uint32_t subsystem, uint32_t message,
                         uint32_t source, uint32_t line);
/* The real routine is noreturn.  The return type models unreachable r0 only. */
extern uint32_t assert_post_action(uint32_t source, uint32_t line);

void FUN_00064f48(uint32_t value, volatile uint8_t *object)
{
    if (object == 0) {
        printk(0x00099cbd, 0x000f6a46, 0x000f6a09, 0x44);
        value = assert_post_action(0x000f6a09, 0x44);
        /* The original loaded r1 with the diagnostic line before the noreturn
         * call, so this is its continuation address if that call returns. */
        object = (volatile uint8_t *)(uintptr_t)0x44u;
    }

    *(volatile uint32_t *)(object + 0x80) = value | UINT32_C(0x80000000);
}
