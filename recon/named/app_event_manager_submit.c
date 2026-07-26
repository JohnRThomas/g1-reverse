/* readable reconstruction; identity: FUN_0004f770 @ 0x0004f770
 * public-name: app_event_manager_submit
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   app_event_manager_submit                 <= FUN_0004f770 @ 0x0004f770
 *   z_spin_lock_valid                        <= FUN_00072040 @ 0x00072040
 *   z_spin_unlock_valid                      <= FUN_0007205c @ 0x0007205c
 *   z_spin_lock_set_owner                    <= FUN_00072078 @ 0x00072078
 *   k_work_submit                            <= FUN_00072fdc @ 0x00072fdc
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f08c7                             @ 0x000f08c7
 *   rodata_f08f4                             @ 0x000f08f4
 *   rodata_f090b                             @ 0x000f090b
 *   rodata_f0920                             @ 0x000f0920
 *   rodata_f0935                             @ 0x000f0935
 *   rodata_f1681                             @ 0x000f1681
 *   rodata_f16be                             @ 0x000f16be
 *   rodata_f1754                             @ 0x000f1754
 *   rodata_fa9b4                             @ 0x000fa9b4
 *   rodata_faa14                             @ 0x000faa14
 *   g_20002838                               @ 0x20002838
 *   g_notify_pending_lock                    @ 0x2000a2c4
 *   g_notify_pending_slist                   @ 0x2000a2c8
 */
/* Full reconstruction of FUN_0004f770 @ 0x4f770 (182 bytes). */
#include <stdint.h>
#include <cmsis_gcc.h>

extern int z_spin_lock_valid(uintptr_t lock);
extern int z_spin_unlock_valid(uintptr_t lock);
extern void z_spin_lock_set_owner(uintptr_t lock);
extern void k_work_submit(uintptr_t object);
extern void printk(uintptr_t domain, uintptr_t message, ...);
extern void assert_post_action(uintptr_t file, uint32_t line) __attribute__((noreturn));

void app_event_manager_submit(uint32_t *item)
{
    if (item == 0) {
        printk(0x00099cbdu, 0x000f1754u, 0x000f1681u, 0xd1u);
        assert_post_action(0x000f1681u, 0xd1u);
    }
    if (item[1] < 0x000fa9b4u || item[1] >= 0x000faa14u) {
        printk(0x00099cbdu, 0x000f16beu, 0x000f1681u, 0xd2u);
        assert_post_action(0x000f1681u, 0xd2u);
    }

    uint32_t saved_basepri = __get_BASEPRI();
    __set_BASEPRI_MAX(0x20u);
    __ISB();

    if (z_spin_lock_valid(0x2000a2c4u) == 0) {
        printk(0x00099cbdu, 0x000f0920u, 0x000f08c7u, 0x72u);
        printk(0x000f0935u, 0x2000a2c4u);
        assert_post_action(0x000f08c7u, 0x72u);
    }

    z_spin_lock_set_owner(0x2000a2c4u);
    *item = 0;
    volatile uint32_t **queue = (volatile uint32_t **)0x2000a2c8u;
    if (queue[1] == 0) {
        queue[0] = item;
        queue[1] = item;
    } else {
        *queue[1] = (uint32_t)(uintptr_t)item;
        queue[1] = item;
    }

    if (z_spin_unlock_valid(0x2000a2c4u) == 0) {
        printk(0x00099cbdu, 0x000f08f4u, 0x000f08c7u, 0xf0u);
        printk(0x000f090bu, 0x2000a2c4u);
        assert_post_action(0x000f08c7u, 0xf0u);
    }

    __set_BASEPRI(saved_basepri);
    __ISB();
    k_work_submit(0x20002838u);
}
