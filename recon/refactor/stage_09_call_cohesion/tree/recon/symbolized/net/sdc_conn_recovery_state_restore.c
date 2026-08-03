#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0101618c @ 0x0101618c
 * public-name: sdc_conn_recovery_state_restore
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_conn_recovery_state_restore          <= FUN_0101618c @ 0x0101618c
 * address symbols (name @ address):
 *   rodata_10101cd                           @ 0x010101cd
 */
/* net-core FUN_0101618c @ 0x101618c  (CFG-directed candidate) */

#include <stdint.h>
extern void FUN_0100cff4(void *, uint32_t);
extern uint16_t FUN_0100d5d0(uint32_t);
extern void controller_work_update_or_enqueue(void *, uintptr_t, uint32_t) __asm__("FUN_0100efc8");
/* Raw identity/back-map: FUN_0101618c @ 0x0101618c. */
void sdc_conn_recovery_state_restore(uint8_t *connection)
{
    uint32_t saved_state = *(uint32_t *)(connection + 0x3c4);
    if (saved_state != *(uint32_t *)(connection + 0x14) ||
        *(uint32_t *)(connection + 0x3c8) != *(uint32_t *)(connection + 0x1c)) {
        *(uint16_t *)(connection + 0x22e) = *(uint16_t *)connection;
        *(uint16_t *)(connection + 0x230) = FUN_0100d5d0(saved_state);
        *(uint16_t *)(connection + 0x232) = *(uint16_t *)(connection + 0x3c8);
        *(uint16_t *)(connection + 0x234) = *(uint16_t *)(connection + 0x3ca);
        controller_work_update_or_enqueue(connection + 0x224, ((unsigned long)&rodata_10101cd) /*=0x10101cd*/, 2);
    }
    FUN_0100cff4(connection, 2);
    connection[0xc6] = 0;
    connection[0xc9] = 3;
}
extern __typeof(sdc_conn_recovery_state_restore) FUN_0101618c
    __attribute__((alias("sdc_conn_recovery_state_restore")));
