#include "g1_net_symbols.h"
/* net-core FUN_0101fd8c @ 0x0101fd8c
 * Readable role: report the current CCM operation result.
 *
 * Raw/address provenance:
 *   g_net_ccm_op_status @ 0x210014d8
 *   NRF_CCM_NS          @ 0x4100e000
 *   code [0x0101fd8c, 0x0101fdb8), literals [0x0101fdb8, 0x0101fdc0)
 *   sole code owner: FUN_0100cb10 tail branch @ 0x0100cb20
 */
#include <stdint.h>

#define CCM_OPERATION_STATUS ((volatile uint8_t *)((unsigned long)&g_net_ccm_op_status) /*=0x210014d8*/)
#define CCM_REGISTER(offset) \
    (*(volatile uint32_t *)(REG_4100e000 /*=0x4100e000*/ + (uint32_t)(offset)))

typedef struct {
    uint8_t active;
    uint8_t phase;
    uint8_t saved_result;
} ccm_operation_status_t;

#define CCM_OPERATION ((volatile ccm_operation_status_t *)CCM_OPERATION_STATUS)

enum {
    CCM_EVENT_END_KEYSTREAM = 0x100,
    CCM_EVENT_END_CRYPT = 0x104,
    CCM_EVENT_ERROR = 0x108,
    CCM_MIC_STATUS = 0x400,
    CCM_RESULT_PENDING = 0x10
};

unsigned FUN_0101fd8c(void)
{
    if (CCM_OPERATION->active == 0)
        return CCM_OPERATION->saved_result;

    if (CCM_REGISTER(CCM_EVENT_END_KEYSTREAM) != 0 &&
        CCM_REGISTER(CCM_EVENT_END_CRYPT) != 0 &&
        CCM_REGISTER(CCM_EVENT_ERROR) == 0)
        return (uint8_t)CCM_REGISTER(CCM_MIC_STATUS);

    return CCM_RESULT_PENDING;
}
