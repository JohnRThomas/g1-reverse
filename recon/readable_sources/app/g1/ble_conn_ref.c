#include "g1_app_symbols.h"
#include "../../../headers/g1_log.h"
/* readable reconstruction; identity: FUN_00056654 @ 0x00056654
 * public-name: ble_conn_ref
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ble_conn_ref                             <= FUN_00056654 @ 0x00056654
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f3a5d                             @ 0x000f3a5d
 *   rodata_f3ebd                             @ 0x000f3ebd
 */
/* Reconstructed FUN_00056654 @ 0x56654  (parity: 300/300 trials, PROVEN) */

extern void assert_post_action(const char *, unsigned int);

int ble_conn_ref(int param_1)
{
    int *counter;
    int old_value;
    if (param_1 == 0) {
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)&rodata_f3ebd) /*=0xf3ebd*/, ((unsigned long)&rodata_f3a5d) /*=0xf3a5d*/, 0x509);
        assert_post_action(((unsigned long)&rodata_f3a5d) /*=0xf3a5d*/, 0x509);
        return 0x509;
    }
    counter = (int *)(param_1 + 0xd0);
    for (;;) {
        old_value = __atomic_load_n(counter, __ATOMIC_ACQUIRE);
        if (old_value == 0)
            return 0;
        {
            int expected = old_value;
            if (__atomic_compare_exchange_n(counter, &expected, old_value + 1,
                                            1, __ATOMIC_ACQ_REL,
                                            __ATOMIC_ACQUIRE))
                return param_1;
        }
    }
}
