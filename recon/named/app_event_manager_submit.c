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
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f08c7                             @ 0x000f08c7
 *   rodata_f08f4                             @ 0x000f08f4   [INLINED -- G6 literal batch]
 *   rodata_f090b                             @ 0x000f090b   [INLINED -- G6 literal batch]
 *   rodata_f0920                             @ 0x000f0920   [INLINED -- G6 literal batch]
 *   rodata_f0935                             @ 0x000f0935   [INLINED -- G6 literal batch]
 *   rodata_f1681                             @ 0x000f1681
 *   rodata_f16be                             @ 0x000f16be   [INLINED -- G6 literal batch]
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
#include "../headers/g1_log.h"

extern int z_spin_lock_valid(unsigned int*);
extern int z_spin_unlock_valid(uintptr_t lock);
extern int z_spin_lock_set_owner(unsigned int*);
extern void k_work_submit(int);
extern void assert_post_action(uintptr_t file, uint32_t line) __attribute__((noreturn));

void app_event_manager_submit(uint32_t *item)
{
    if (item == 0) {
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"), 0x000f1754u, 0x000f1681u, 0xd1u);
        assert_post_action(0x000f1681u, 0xd1u);
    }
    if (item[1] < 0x000fa9b4u || item[1] >= 0x000faa14u) {
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"), ((unsigned long)"(aeh->type_id >= _event_type_list_start) && (aeh->type_id < _event_type_list_end)"), 0x000f1681u, 0xd2u);
        assert_post_action(0x000f1681u, 0xd2u);
    }

    uint32_t saved_basepri = __get_BASEPRI();
    __set_BASEPRI_MAX(0x20u);
    __ISB();

    if (z_spin_lock_valid(0x2000a2c4u) == 0) {
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"), ((unsigned long)"z_spin_lock_valid(l)"), 0x000f08c7u, 0x72u);
        printk(((unsigned long)"\tInvalid spinlock %p\n"), 0x2000a2c4u);
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
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"), ((unsigned long)"z_spin_unlock_valid(l)"), 0x000f08c7u, 0xf0u);
        printk(((unsigned long)"\tNot my spinlock %p\n"), 0x2000a2c4u);
        assert_post_action(0x000f08c7u, 0xf0u);
    }

    __set_BASEPRI(saved_basepri);
    __ISB();
    k_work_submit(0x20002838u);
}
