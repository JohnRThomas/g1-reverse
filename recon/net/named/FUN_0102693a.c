/* readable reconstruction; identity: FUN_0102693a @ 0x0102693a
 * public-name: FUN_0102693a
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 */
/* net-core FUN_0102693a @ 0x102693a  (CFG-directed candidate) */
#include <stdint.h>
extern uint16_t FUN_01026a7e(uint32_t,uint32_t,uint32_t);
extern uint16_t FUN_0102689c(uint32_t,uint32_t,uint32_t);
extern void FUN_01025a84(void *,uint32_t,uint32_t);
extern __attribute__((noreturn)) void sdc_assertion_fail(uint32_t,uint32_t);
#define sdc_assertion_fail sdc_assertion_fail
void FUN_0102693a(uint8_t *out,uint32_t capacity_arg,uint32_t value_arg,uint32_t kind_arg,uint32_t aux_arg) {
    uint16_t capacity=(uint16_t)capacity_arg, value=(uint16_t)value_arg, aux=(uint16_t)aux_arg; uint8_t kind=(uint8_t)kind_arg;
    if (capacity < FUN_01026a7e(value,kind,aux)) sdc_assertion_fail(0x14,0x9e);
    if (((uintptr_t)out & 3u) != 0) sdc_assertion_fail(0x14,0x9f);
    FUN_01025a84(out,0,0x18);
    out[0x13]=kind;
    *(uint16_t *)(out+2)=FUN_0102689c(value,kind,aux);
    if (*(uint16_t *)(out+2)>0x8000) sdc_assertion_fail(0x14,0xa4);
    *(uint16_t *)out=value;
}
