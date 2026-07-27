#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00047538 @ 0x00047538
 * public-name: panel_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   projector_send_cmd1                      <= FUN_0007d642 @ 0x0007d642
 *   projector_send_cmd_c0                    <= FUN_0007d658 @ 0x0007d658
 *   projector_send_cmd_0x46                  <= FUN_0007d67e @ 0x0007d67e
 *   projector_fill_framebuffer               <= FUN_0007d6ae @ 0x0007d6ae
 *   projector_reset_sequence                 <= FUN_0007d74e @ 0x0007d74e
 *   delay_ms                                 <= FUN_0007d772 @ 0x0007d772
 *   projector_send_cmd_immediate             <= FUN_0007d77c @ 0x0007d77c
 * address symbols (name @ address):
 *   rodata_99969                             @ 0x00099969
 *   rodata_d741b                             @ 0x000d741b   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed panel_init @ 0x47538. */
#include <stdint.h>
#include "../../headers/g1_log.h"

extern void projector_send_cmd1(uint32_t a, uint32_t b);
extern void projector_send_cmd_c0(uint32_t a, uint32_t b);
extern void projector_send_cmd_0x46(uint32_t a);
extern void projector_fill_framebuffer(unsigned int);
extern void projector_reset_sequence(void);
extern void delay_ms(int);
extern void projector_send_cmd_immediate(uint32_t a);

void panel_init(void)
{
    if (*(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/ > 3) {
        if (*(volatile uint32_t*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
            log_message(((unsigned long)&rodata_99969) /*=0x99969*/, ((unsigned long)"panel_init") /*=0xd741b*/);
        } else {
            debug_print(((unsigned long)&rodata_99969) /*=0x99969*/, ((unsigned long)"panel_init") /*=0xd741b*/);
        }
    }
    projector_reset_sequence();
    projector_send_cmd_immediate(6);
    projector_send_cmd1(1, 0x10);
    projector_fill_framebuffer(0);
    projector_send_cmd_c0(0, 0);
    projector_send_cmd_c0(0, 0x14);
    projector_send_cmd_c0(0x18, 0);
    projector_send_cmd_c0(0x18, 0x14);
    projector_send_cmd_c0(0xc, 10);
    projector_send_cmd_immediate(0x71);
    projector_send_cmd_immediate(0x97);
    delay_ms(1);
    projector_send_cmd_immediate(0x73);
    projector_send_cmd_immediate(0x97);
    delay_ms(1);
    projector_send_cmd_0x46(0xf);
    projector_send_cmd1(0x31, 4);
    projector_send_cmd_immediate(0xa3);
    projector_send_cmd_immediate(0x97);
    delay_ms(1);
}
