/* net-core FUN_01026a7e @ 0x1026a7e  (CFG-directed candidate) */
#include <stdint.h>
extern uint16_t FUN_0102689c(uint32_t,uint32_t,uint32_t);
uint16_t FUN_01026a7e(uint32_t value_arg,uint32_t kind_arg,uint32_t aux_arg) {
    uint16_t value=(uint16_t)value_arg, aux=(uint16_t)aux_arg; uint8_t kind=(uint8_t)kind_arg;
    uint16_t base=FUN_0102689c(value,kind,aux);
    uint16_t padding = value < 0x45 ? (uint16_t)(0x45-value) : 0;
    return (uint16_t)(base + 0x18u + padding);
}
