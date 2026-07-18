/* Reconstructed FUN_0005a954 @ 0x0005a954 (bt_gatt_init).
 * Raw/address backmap: FUN_0005a954 @ 0x0005a954, extent 0x00000058.
 */
#include <stdint.h>
extern uint32_t FUN_000826e0(volatile uint32_t *, uint32_t); /* atomic_or */
extern void FUN_00059cb4(void);                              /* bt_gatt_service_init */
extern void FUN_000732d4(void *, void *);                    /* k_work_init_delayable */
/* k_work_schedule(dwork, k_timeout_t).  The 64-bit timeout is aligned to
 * r2/r3 by AAPCS, so retain the otherwise-unused r1 slot explicitly. */
extern void FUN_000531cc(void *, uint32_t, uint64_t);         /* k_work_schedule */
extern void FUN_00057330(void *);                            /* bt_conn_auth_info_cb_register */
extern void FUN_00056e24(void *);                            /* bt_conn_cb_register */

void FUN_0005a954(void)
{
    if ((FUN_000826e0((volatile uint32_t *)0x2000af04U, 1U) & 1U) != 0U)
        return;
    FUN_00059cb4();
    *(volatile uint32_t *)0x2000af10U = 0;
    *(volatile uint32_t *)0x2000af14U = 0;
    /* db_hash.work @ db_hash+0x20; handler db_hash_process @0x82cb2. */
    FUN_000732d4((void *)0x200063a0U, (void *)0x00082cb3U);
    FUN_000531cc((void *)0x200063a0U, 0U, 0x148ULL);
    /* gatt_sc.work @ gatt_sc+0x20; handler sc_process @0x5b4bc. */
    FUN_000732d4((void *)0x20006418U, (void *)0x0005b4bdU);
    /* gatt_sc.flags @ gatt_sc+0x50: atomic flags, not a k_work object. */
    (void)FUN_000826e0((volatile uint32_t *)0x20006448U, 2U);
    /* gatt_delayed_store.work @ gatt_delayed_store+0x28. */
    FUN_000732d4((void *)0x20006350U, (void *)0x00082fa7U);
    FUN_00057330((void *)0x200029f8U);
    FUN_00056e24((void *)0x200029d4U);
}
