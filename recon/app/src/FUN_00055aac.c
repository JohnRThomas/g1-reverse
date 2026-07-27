/* Reconstructed FUN_00055aac @ 0x55aac
 * Readable identity: legacy_advertising_connection_restart.
 * Raw/address backmap: FUN_00055aac @ 0x00055aac.
 */
#include <stdint.h>

extern uint32_t FUN_0008117a(volatile uint32_t *); /* atomic_get */
extern unsigned int FUN_000556b0(unsigned char*, int*); /* connection lookup/create */
extern uint32_t FUN_00055698(void *); /* adv_is_directed */
extern int FUN_00055454(void *, uint32_t, uint32_t, void *); /* legacy advertising configure */
extern void FUN_0004d944(uint32_t, uint32_t, const void *, uint32_t);
extern int FUN_000812d2(void *, unsigned int); /* bt_le_adv_set_enable_legacy */
extern void FUN_000566a4(void *); /* bt_conn_unref */
extern void FUN_00056704(void *, uint32_t); /* bt_conn_set_state */
extern uint32_t FUN_00081180(volatile uint32_t *, uint32_t); /* atomic_and */

void FUN_00055aac(void)
{
    volatile uint32_t *const flags = (volatile uint32_t *)0x20002028UL;
    void *connection = 0;
    uint8_t option = 0;

    if ((FUN_0008117a(flags) & 0x4000U) == 0U) return;
    if ((FUN_0008117a(flags) & 0x80U) != 0U) return;
    if ((FUN_0008117a(flags) & 0x400U) == 0U) return;

    if (FUN_000556b0((void *)0x20002018UL, &connection) != 0) return;
    {
        uint32_t directed = FUN_00055698((void *)0x20002018UL);
        uint32_t mode = ((((FUN_0008117a(flags) >> 14) & 1U) ^ 1U) << 1);
        if ((FUN_0008117a(flags) & 0x400U) != 0U) mode |= 1U;
        if ((FUN_0008117a(flags) & 0x2000U) != 0U) mode |= 4U;

        {
            int error = FUN_00055454((void *)0x20002018UL, mode,
                                      directed, &option);
            if (error != 0) {
                uint32_t package[3] = { 3U, 0x000f3857UL, (uint32_t)error };
                FUN_0004d944(0x000880f8UL, 0x1840U, package, 0U);
                return;
            }
        }

        if (FUN_000812d2((void *)0x20002018UL, 1U) == 0) {
            FUN_000566a4(connection);
            return;
        }
        FUN_00056704(connection, directed);
        {
            uint32_t old = FUN_00081180(flags, 0xffffbfffU);
            FUN_000566a4(connection);
            if ((old & 0x4000U) != 0U) {
                (void)__atomic_fetch_or((uint32_t *)flags, 0x4000U,
                                        __ATOMIC_SEQ_CST);
            }
        }
    }
}
