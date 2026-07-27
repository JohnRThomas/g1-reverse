#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00056300 @ 0x00056300
 * public-name: bt_conn_tx_drain_and_reset
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   net_buf_destroy                          <= FUN_00056080 @ 0x00056080
 *   bt_conn_tx_drain_and_reset               <= FUN_00056300 @ 0x00056300
 *   net_buf_unref                            <= FUN_0005f24c @ 0x0005f24c
 *   k_work_reschedule                        <= FUN_0007350c @ 0x0007350c
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   bt_conn_reset_rx_state                   <= FUN_000813d6 @ 0x000813d6
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f3a5d                             @ 0x000f3a5d
 *   rodata_f3abe                             @ 0x000f3abe   [INLINED -- G6 literal batch]
 *   rodata_f3ae4                             @ 0x000f3ae4   [INLINED -- G6 literal batch]
 *   rodata_f3af9                             @ 0x000f3af9   [INLINED -- G6 literal batch]
 */
/* Full reconstruction FUN_00056300 @ 0x00056300 (128-byte exact extent). */
#include <stdint.h>
#include "../../headers/g1_log.h"

extern void *net_buf_get(void *, uint32_t, uint32_t, uint32_t);
extern void net_buf_unref(int);
extern void net_buf_destroy(void *, void *);
extern void assert_post_action(uintptr_t, uint32_t) __attribute__((noreturn));
extern uint64_t bt_conn_reset_rx_state(void *);
extern void k_work_reschedule(unsigned int, unsigned int, unsigned int, unsigned int);

void bt_conn_tx_drain_and_reset(void *context, uint32_t inherited_r1)
{
    uint8_t *base = context;
    for (;;) {
        void *item = net_buf_get(base + 0x38, inherited_r1, 0, 0);
        if (!item) {
            if (*(uint32_t *)(base + 0x14)) {
                printk(((unsigned long)"sys_slist_is_empty(&conn->tx_pending)") /*=0xf3abe*/, ((unsigned long)&rodata_f3a5d) /*=0xf3a5d*/, ((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, 0x313u);
                printk(((unsigned long)"\tPending TX packets\n") /*=0xf3ae4*/);
                assert_post_action(((unsigned long)&rodata_f3a5d) /*=0xf3a5d*/, 0x313u);
            }
            if (*(uint32_t *)(base + 0x1c)) {
                printk(((unsigned long)"sys_slist_is_empty(&conn->tx_pending)") /*=0xf3abe*/, ((unsigned long)"conn->pending_no_cb == 0") /*=0xf3af9*/, ((unsigned long)&rodata_f3a5d) /*=0xf3a5d*/, 0x314u);
                assert_post_action(((unsigned long)&rodata_f3a5d) /*=0xf3a5d*/, 0x314u);
            }
            uint64_t released = bt_conn_reset_rx_state(context);
            k_work_reschedule(base + 0x60, (uint32_t)(released >> 32), 0, 0);
            return;
        }
        void *fragment = *(void **)((uint8_t *)item + 0x18);
        *(void **)((uint8_t *)item + 0x18) = 0;
        net_buf_unref(item);
        if (fragment) net_buf_destroy(context, fragment);
    }
}
