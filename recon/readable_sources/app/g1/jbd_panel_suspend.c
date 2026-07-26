#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000475f0 @ 0x000475f0
 * public-name: jbd_panel_suspend
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   projector_send_command                   <= FUN_0007d82e @ 0x0007d82e
 * address symbols (name @ address):
 *   rodata_d73a1                             @ 0x000d73a1   [INLINED -- G6 literal batch]
 *   rodata_d7409                             @ 0x000d7409   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed jbd_panel_suspend @ 0x475f0  (parity: 300/300 trials, PROVEN) */

extern void log_message(unsigned int,unsigned int,unsigned int,unsigned int,
                        unsigned int,unsigned int);
extern void debug_print(unsigned int,unsigned int,unsigned int,unsigned int,
                         unsigned int,unsigned int);
extern void projector_send_command(unsigned int,const void *,unsigned int);

unsigned int jbd_panel_suspend(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
    if (*(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/ > 2) {
        unsigned int sink = *(volatile unsigned int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
        if (sink == 0) {
            log_message(((unsigned long)"%s(): SPI_DEEP_POWER_DOWN\n") /*=0xd73a1*/,((unsigned long)"jbd_panel_suspend") /*=0xd7409*/,param_3,sink,param_1,param_2);
        } else {
            debug_print(((unsigned long)"%s(): SPI_DEEP_POWER_DOWN\n") /*=0xd73a1*/,((unsigned long)"jbd_panel_suspend") /*=0xd7409*/,param_3,sink,param_1,param_2);
        }
    }
    const unsigned char command = 0xff;
    projector_send_command(0xb9,&command,1);
    return 0;
}
