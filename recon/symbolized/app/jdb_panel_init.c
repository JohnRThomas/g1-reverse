#include "g1_app_symbols.h"
/* named: jdb_panel_init */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed jdb_panel_init @ 0x46fc0  (parity: 300/300 trials, PROVEN) */

extern void panel_init(void);
extern void set_brightness_to_panel_reg(void);
extern int spi_read_id(void);
extern void DEBUG_PRINT(void);
extern void debug_print(void);

unsigned int jdb_panel_init(unsigned char *param_1)
{
    *(unsigned int*)(param_1+0x374) = (unsigned int)(param_1 - 0x5c);
    panel_init();
    set_brightness_to_panel_reg();
    int iVar1 = spi_read_id();
    *(volatile unsigned int*)((uintptr_t)&g_panel_spi_id) /*=0x2000a074*/ = iVar1;
    unsigned int uVar2;
    if (iVar1 == 0x4010) {
        uVar2 = 0;
        *(unsigned int*)(param_1+0x35c) = 1;
    } else {
        if (*(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/ > 2) {
            if (*(volatile unsigned int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                DEBUG_PRINT();
            } else {
                debug_print();
            }
        }
        uVar2 = 0xffffffffUL;
    }
    return uVar2;
}

