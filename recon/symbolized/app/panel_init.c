#include "g1_app_symbols.h"
/* named: panel_init */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed panel_init @ 0x47538  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(uint32_t a, uint32_t b, uint32_t c);
extern void debug_print(void);
extern void projector_send_cmd1(uint32_t a, uint32_t b);
extern void projector_send_cmd_c0(uint32_t a, uint32_t b);
extern void projector_send_cmd_0x46(uint32_t a);
extern void projector_fill_framebuffer(uint32_t a);
extern void projector_reset_sequence(void);
extern void delay_ms(uint32_t a);
extern void projector_send_cmd_immediate(uint32_t a);

void panel_init(uint32_t param_1, uint32_t param_2, uint32_t param_3, uint32_t param_4)
{
    if (*(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/ > 3) {
        if (*(volatile uint32_t*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
            DEBUG_PRINT("%s(): enter\n" /*=0x99969*/, "panel_init" /*=0xd741b*/, 0);
        } else {
            debug_print();
        }
    }
    projector_reset_sequence();
    projector_send_cmd_immediate(6);
    projector_send_cmd1(1,0x10);
    projector_fill_framebuffer(0);
    projector_send_cmd_c0(0,0);
    projector_send_cmd_c0(0,0x14);
    projector_send_cmd_c0(0x18,0);
    projector_send_cmd_c0(0x18,0x14);
    projector_send_cmd_c0(0xc,10);
    projector_send_cmd_immediate(0x71);
    projector_send_cmd_immediate(0x97);
    delay_ms(1);
    projector_send_cmd_immediate(0x73);
    projector_send_cmd_immediate(0x97);
    delay_ms(1);
    projector_send_cmd_0x46(0xf);
    projector_send_cmd1(0x31,4);
    projector_send_cmd_immediate(0xa3);
    projector_send_cmd_immediate(0x97);
    delay_ms(1);
}

