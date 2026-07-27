#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007d6f4 @ 0x0007d6f4
 * public-name: projector_fill_and_sync
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   projector_fill_framebuffer               <= FUN_0007d6ae @ 0x0007d6ae
 *   projector_fill_and_sync                  <= FUN_0007d6f4 @ 0x0007d6f4
 *   delay_ms                                 <= FUN_0007d772 @ 0x0007d772
 *   projector_send_cmd_immediate             <= FUN_0007d77c @ 0x0007d77c
 */
/* Reconstructed FUN_0007d6f4 @ 0x7d6f4  (parity: 300/300 trials, PROVEN) */

extern void projector_fill_framebuffer(unsigned long);
extern unsigned long long projector_send_cmd_immediate(unsigned int);
extern void delay_ms(unsigned int, unsigned int, unsigned int, unsigned int);

void projector_fill_and_sync(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned long long ret;
    projector_fill_framebuffer(param_1);
    ret = projector_send_cmd_immediate(0x97);
    delay_ms(1, (unsigned int)(ret >> 32), param_3, param_4);
}
