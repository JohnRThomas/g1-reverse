/* readable reconstruction; identity: FUN_0004d6ec @ 0x0004d6ec
 * public-name: log_process_thread
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   activate_foreach_backend                 <= FUN_0004d2d0 @ 0x0004d2d0
 *   log_msg_process                          <= FUN_0004d334 @ 0x0004d334
 *   log_process                              <= FUN_0004d594 @ 0x0004d594
 *   log_process_thread                       <= FUN_0004d6ec @ 0x0004d6ec
 *   k_sem_give                               <= FUN_00072880 @ 0x00072880
 *   z_impl_k_sem_take                        <= FUN_00072908 @ 0x00072908
 *   k_current_get                            <= FUN_000748ac @ 0x000748ac
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_882a0                             @ 0x000882a0
 *   __settings_handler_static_list_start     @ 0x000882b0
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f0cae                             @ 0x000f0cae
 *   rodata_f0d3f                             @ 0x000f0d3f   [INLINED -- G6 literal batch]
 *   g_200039f8                               @ 0x200039f8
 *   g_2000a0d0                               @ 0x2000a0d0
 *   log_buffered_cnt                         @ 0x2000a0d8
 */
/* Full reconstruction of FUN_0004d6ec @ 0x4d6ec (194 bytes).
 * CFG_VERIFY_CALL_ARITIES=2,0,1,1,0,4
 */
#include <stdint.h>

extern void printk(uint32_t, ...);
extern void assert_post_action(uint32_t, uint32_t) __attribute__((noreturn));
extern uintptr_t log_msg_process(uint32_t, uint32_t);
extern uintptr_t activate_foreach_backend(uintptr_t);
extern uintptr_t k_current_get(void);
extern void k_sem_give(uintptr_t);
extern uint64_t log_process(void);
extern void z_impl_k_sem_take(uintptr_t, uint32_t, uint32_t, uint32_t);

void log_process_thread(void)
{
    uintptr_t const begin = 0x000882a0u;
    uintptr_t const end = 0x000882b0u;
    if ((end - begin) / 16u == 0) {
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"), 0x000f0d3fu, 0x000f0caeu, 0x35cu);
        assert_post_action(0x000f0caeu, 0x35cu);
    }

    uintptr_t iterator = log_msg_process(0, 0);
    uint32_t event = iterator ? 0x667u : UINT32_MAX;
    uint32_t status = iterator ? 0u : UINT32_MAX;
    uintptr_t timer = k_current_get();
    *(volatile uintptr_t *)0x2000a0d0u = timer;
    if (timer && *(volatile int32_t *)0x2000a0d8u > 9)
        k_sem_give(0x200039f8u);

    uint32_t previous = 0;
    for (;;) {
        if (iterator) {
            iterator = activate_foreach_backend(iterator);
            if (!iterator)
                event = status = UINT32_MAX;
        }
        uint64_t result = log_process();
        uint32_t current = (uint32_t)result;
        uint32_t aux = (uint32_t)(result >> 32);
        if (!current) {
            if (previous) {
                for (uintptr_t item = begin; item < end; item += 16) {
                    uintptr_t ops = *(volatile uintptr_t *)item;
                    uintptr_t callback = *(volatile uintptr_t *)(ops + 0x18);
                    if (callback)
                        ((void (*)(uintptr_t, uint32_t))callback)(item, 0);
                }
            }
            z_impl_k_sem_take(0x200039f8u, aux, event, status);
        }
        previous = current;
    }
}
