#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01008d7c @ 0x01008d7c
 * public-name: FUN_01008d7c
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 * address symbols (name @ address):
 *   g_net_layout_count_table                 @ 0x21000a30
 */
/* net-core FUN_01008d7c @ 0x1008d7c */
#include <stdint.h>

extern void sdc_assertion_fail(uint32_t group, uint32_t code);
extern int32_t FUN_0101f624(void *descriptor);
extern int32_t FUN_0101f668(uint32_t value);
extern int32_t FUN_0101f674(uint32_t value);
extern int32_t FUN_0102941c(void *control);

void FUN_01008d7c(uint32_t param_1, uint32_t param_2,
                  uint32_t param_3, uint32_t param_4)
{
    volatile uint8_t *const state = (volatile uint8_t *)((unsigned long)&g_net_layout_count_table) /*=0x21000a30*/;
    struct {
        uint8_t first;
        uint8_t second;
        uint8_t third;
        uint8_t reserved;
        uint16_t fourth;
    } descriptor;

    (void)param_1;
    (void)param_3;
    (void)param_4;

    descriptor.first = state[7];
    descriptor.second = state[8];
    descriptor.third = state[5];
    descriptor.reserved = 0;
    descriptor.fourth = state[6];
    if (FUN_0101f624(&descriptor) != 0) {
        sdc_assertion_fail(3, 0xb3);
        return;
    }

    param_2 = (param_2 & ~UINT32_C(0xff)) | 1u;
    if (FUN_0102941c(&param_2) != 0) {
        sdc_assertion_fail(3, 0xb7);
        return;
    }
    if (FUN_0101f674(state[0x12]) != 0) {
        sdc_assertion_fail(3, 0xba);
        return;
    }
    if (FUN_0101f668(state[0x11]) != 0) {
        sdc_assertion_fail(3, 0xbb);
    }
}
