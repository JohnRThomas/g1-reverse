/* readable reconstruction; identity: FUN_0002953c @ 0x0002953c
 * public-name: some_module_sem_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   some_module_sem_init                     <= FUN_0002953c @ 0x0002953c
 *   z_impl_k_sem_init                        <= FUN_00086534 @ 0x00086534
 * address symbols (name @ address):
 *   g_some_module_sem                        @ 0x20007b1c
 *   g_some_module_init_done_flag             @ 0x20018d8a
 */
/* Reconstructed FUN_0002953c @ 0x2953c  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int z_impl_k_sem_init(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);

void some_module_sem_init(void)
{
    int iVar1 = z_impl_k_sem_init(0x20007b1cU, 0, 5, 0, 0);
    if (iVar1 == 0) {
        *(volatile uint8_t *)0x20018d8aUL = 1;
    }
}
