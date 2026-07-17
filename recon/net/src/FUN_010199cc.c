/* net-core FUN_010199cc @ 0x010199cc */
#include <stdint.h>

extern uint32_t FUN_0100a5a0(void);
extern void FUN_0102714a(uint32_t controller, uint32_t *handle,
                         uint16_t *auxiliary);
extern uint8_t *FUN_010270d2(uint32_t handle);
#define sdc_buffer_descriptor_resolve FUN_0102714a
#define sdc_buffer_payload_get FUN_010270d2

int FUN_010199cc(void)
{
    uint32_t handle;
    uint16_t auxiliary;
    uint32_t controller = FUN_0100a5a0();

    sdc_buffer_descriptor_resolve(controller, &handle, &auxiliary);
    return sdc_buffer_payload_get(handle)[0x13] != 0xffu;
}
