/* readable reconstruction; identity: FUN_00046fc0 @ 0x00046fc0
 * public-name: jdb_panel_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   set_brightness_to_panel_reg              <= FUN_00046e3c @ 0x00046e3c
 *   panel_init                               <= FUN_00047538 @ 0x00047538
 *   spi_read_id                              <= FUN_00047724 @ 0x00047724
 * address symbols (name @ address):
 *   rodata_d728d                             @ 0x000d728d   [INLINED -- G6 literal batch]
 *   rodata_d72ac                             @ 0x000d72ac   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_panel_spi_id                           @ 0x2000a074
 */
#include "../headers/g1_log.h"
/* Reconstructed jdb_panel_init @ 0x46fc0  (parity: 300/300 trials, PROVEN) */

extern void panel_init(void);
extern void set_brightness_to_panel_reg(unsigned int);
extern int spi_read_id(void);

unsigned int jdb_panel_init(unsigned char *param_1)
{
    *(unsigned int*)(param_1+0x374) = (unsigned int)(param_1 - 0x5c);
    panel_init();
    set_brightness_to_panel_reg(param_1[0x369]);
    int iVar1 = spi_read_id();
    *(volatile unsigned int*)0x2000a074UL = iVar1;
    unsigned int uVar2;
    if (iVar1 == 0x4010) {
        uVar2 = 0;
        *(unsigned int*)(param_1+0x35c) = 1;
    } else {
        if (*(volatile int*)0x2000230cUL > 2) {
            if (*(volatile unsigned int*)0x20007554UL == 0) {
                log_message(((unsigned long)"%s(): JBD PANEL init failure!\n"),((unsigned long)"jdb_panel_init"));
            } else {
                debug_print(((unsigned long)"%s(): JBD PANEL init failure!\n"),((unsigned long)"jdb_panel_init"));
            }
        }
        uVar2 = 0xffffffffUL;
    }
    return uVar2;
}
