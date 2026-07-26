#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00023014 @ 0x00023014
 * public-name: update_burial_point_to_flash
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   flash_settings_read                      <= FUN_000225b4 @ 0x000225b4
 *   flash_settings_write_and_verify          <= FUN_00022658 @ 0x00022658
 *   memcmp                                   <= FUN_00086be4 @ 0x00086be4
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_9e655                             @ 0x0009e655   [INLINED -- G6 literal batch]
 *   rodata_9e67c                             @ 0x0009e67c   [INLINED -- G6 literal batch]
 *   rodata_9e789                             @ 0x0009e789   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed update_burial_point_to_flash @ 0x23014  (parity: 300/300 trials, PROVEN) */

extern void log_message(unsigned int a, unsigned int b);
extern void debug_print(unsigned int,unsigned int);
extern int flash_settings_read(unsigned int a, void *b, unsigned int n);
extern int flash_settings_write_and_verify(unsigned int a, void *b, unsigned int n);
extern int memcmp(void *a, void *b, unsigned int n);
extern void memset_bytes(void *dst, int val, int n);

unsigned int update_burial_point_to_flash(char *param_1)
{
    unsigned char buf[196];
    int iVar2;
    unsigned int format_string;

    memset_bytes(buf, 0, 0xc0);
    if (1 < *(volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/) {
        if (*(volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
            log_message(((unsigned long)"%s(): update_burial_point_to_flash!!!\n") /*=0x9e655*/, ((unsigned long)"update_burial_point_to_flash") /*=0x9e789*/);
        } else {
            debug_print(((unsigned long)"%s(): update_burial_point_to_flash!!!\n") /*=0x9e655*/, ((unsigned long)"update_burial_point_to_flash") /*=0x9e789*/);
        }
    }
    iVar2 = flash_settings_read(0x135000U, buf, 0xc0);
    if (iVar2 == 0) {
        char *p = param_1 + 0x10c6;
        iVar2 = memcmp(buf, p, 0xc0);
        if (iVar2 == 0) {
            return 0;
        }
        iVar2 = flash_settings_write_and_verify(0x135000U, p, 0xc0);
        if (iVar2 == 0) {
            return 0;
        }
        if (*(volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/ < 2) {
            return 0xffffffff;
        }
        iVar2 = *(volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
        format_string = 0x9e69cU;
    } else {
        if (*(volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/ < 2) {
            return 0xffffffff;
        }
        iVar2 = *(volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
        format_string = ((unsigned long)"%s(): burial_point read error!\n") /*=0x9e67c*/;
    }
    if (iVar2 == 0) {
        log_message(format_string, ((unsigned long)"update_burial_point_to_flash") /*=0x9e789*/);
    } else {
        debug_print(format_string, ((unsigned long)"update_burial_point_to_flash") /*=0x9e789*/);
    }
    return 0xffffffff;
}
