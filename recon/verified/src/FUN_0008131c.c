/* Reconstructed FUN_0008131c @ 0x0008131c.
 * Exact branch veneer to bt_le_adv_set_enable_legacy @ 0x000812d2.
 */
#include <stdint.h>
extern int bt_le_adv_set_enable_legacy(void *, unsigned int);
int FUN_0008131c(void *advertising_set, uint32_t enable)
{
    return bt_le_adv_set_enable_legacy(advertising_set, enable);
}
