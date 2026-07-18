/* Reconstructed FUN_0005a954 @ 0x0005a954 (bt_gatt_init).
 * Raw/address backmap: FUN_0005a954 @ 0x0005a954, extent 0x00000058.
 */
#include <stdint.h>
extern uint32_t FUN_000826e0(volatile uint32_t *, uint32_t); /* atomic_or */
extern void FUN_00059cb4(void);                              /* bt_gatt_service_init */
extern void FUN_000732d4(void *, void *);                    /* k_work_init_delayable */
extern void FUN_000531cc(void *, uint32_t, uint32_t);        /* memset */
extern void FUN_00057330(void *);                            /* bt_conn_auth_info_cb_register */
extern void FUN_00056e24(void *);                            /* bt_conn_cb_register */

void FUN_0005a954(void)
{
    if ((FUN_000826e0((volatile uint32_t *)0x2000af04U, 1U) & 1U) != 0U)
        return;
    FUN_00059cb4();
    *(volatile uint32_t *)0x2000af10U = 0;
    *(volatile uint32_t *)0x2000af14U = 0;
    FUN_000732d4((void *)0x20006418U, (void *)0x00082cb3U);
    FUN_000531cc((void *)0x200063a0U, 0U, 0x148U);
    FUN_000732d4((void *)0x20006448U, (void *)0x00082fb5U);
    (void)FUN_000826e0((volatile uint32_t *)0x20006448U, 2U);
    FUN_000732d4((void *)0x200064b8U, (void *)0x00082ff9U);
    FUN_00057330((void *)0x200029f8U);
    FUN_00056e24((void *)0x200029d4U);
}
