#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00010fc8 @ 0x00010fc8
 * public-name: get_lux_info
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   __floatunsidf                            <= FUN_0000d804 @ 0x0000d804
 *   __extendsfdf2                            <= FUN_0000d848 @ 0x0000d848
 *   __muldf3                                 <= FUN_0000d8f8 @ 0x0000d8f8
 *   __divdf3                                 <= FUN_0000db4c @ 0x0000db4c
 *   __fixunsdfsi                             <= FUN_0000dea8 @ 0x0000dea8
 *   get_lux_info                             <= FUN_00010fc8 @ 0x00010fc8
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   opt3001_read_lux_raw                     <= FUN_0002e648 @ 0x0002e648
 * address symbols (name @ address):
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed FUN_00010fc8 @ 0x10fc8 */
#include <stdint.h>
#include "../../headers/g1_log.h"

extern uint64_t __floatunsidf(uint32_t);
extern uint64_t __extendsfdf2(uint32_t);
extern void __muldf3(uint32_t, uint32_t, uint32_t, uint32_t);
extern uint64_t __divdf3(uint32_t, uint32_t, uint32_t, uint32_t);
extern uint32_t __fixunsdfsi(void);
extern int get_device_info(void);
extern uint32_t opt3001_read_lux_raw(uint32_t);

uint32_t get_lux_info(uint32_t request, uint32_t context,
                      uint32_t *buffer_slot, uint8_t *encoded_size)
{
    /* G7-B2 defect fix.  Both of these formats are argument-free:
     *   0xa6a28 = "###################################join in get_lux_info\n"
     *   0xa6a61 = "get_lux_info para is NULL\n"
     * and the shipped image loads ONLY r0 at 0x10fce and 0x10fda before each
     * `bl 0x7dda4`.  The four-argument spelling this body used to carry, and
     * in particular the `uint64_t debug_state` it assigned from the call and
     * then fed back as argument 2, were decompiler artefacts of r1..r3 being
     * live scratch across a `void` variadic callee.  log_message returns
     * nothing (see recon/headers/g1_log.h). */
    log_message(0x000a6a28u);
    if (buffer_slot == 0 || encoded_size == 0) {
        log_message(0x000a6a61u);
        return UINT32_MAX;
    }

    uint8_t *out = (uint8_t *)(uintptr_t)*buffer_slot;
    *(volatile uint8_t *)(out + 1) = 1;
    *(volatile uint8_t *)(out + 0) = 0x20;
    *(volatile uint8_t *)(out + 2) = 3;
    *(volatile uint8_t *)(out + 3) = 0x20;

    uint32_t ticks = opt3001_read_lux_raw(0);
    *(uint32_t *)(out + 4) = ticks;
    *(uint32_t *)(out + 8)  = *(volatile uint32_t *)(get_device_info() + 0xfa0);
    *(uint32_t *)(out + 12) = *(volatile uint32_t *)(get_device_info() + 0xfa4);
    *(uint32_t *)(out + 16) = *(volatile uint32_t *)(get_device_info() + 0xfa8);
    *(uint32_t *)(out + 20) = *(volatile uint32_t *)(get_device_info() + 0xf94);
    *(uint32_t *)(out + 24) = *(volatile uint32_t *)(get_device_info() + 0xfb0);
    *(uint32_t *)(out + 28) = *(volatile uint32_t *)(get_device_info() + 0xfb4);

    int32_t counter = *(volatile int32_t *)(get_device_info() + 0xfb0);
    union { float f; uint32_t u; } converted = { .f = (float)counter };
    uint64_t scaled = __extendsfdf2(converted.u);
    scaled = __divdf3((uint32_t)scaled, (uint32_t)(scaled >> 32),
                          0, 0x412e8480u);
    uint64_t tick_value = __floatunsidf(ticks);
    __muldf3((uint32_t)scaled, (uint32_t)(scaled >> 32),
                 (uint32_t)tick_value, (uint32_t)(tick_value >> 32));

    uint32_t value = __fixunsdfsi();
    *(uint32_t *)(out + 32) = value;
    if (*(volatile int32_t *)((unsigned long)&g_log_level) /*=0x2000230c*/ > 2) {
        /* 0xa6a7c = "%s(): curve_lux:0x%x\n\n" -- two specifiers, so three
         * arguments.  0x11086..0x1108c load exactly r0/r1/r2 and then branch
         * to either sink; the r3 the old spelling passed was the
         * g_log_use_alt_sink value the branch itself had just loaded. */
        if (*(volatile int32_t *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0)
            log_message(0x000a6a7cu, 0x000a76beu, value);
        else
            debug_print(0x000a6a7cu, 0x000a76beu, value);
    }
    *encoded_size = 0x24;
    (void)request;
    return 0;
}
