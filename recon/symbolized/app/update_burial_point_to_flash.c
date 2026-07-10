#include "g1_app_symbols.h"
/* named: update_burial_point_to_flash */
/* globals referenced:
//   0x00135000  FLASH_ADDR_SETTINGS_RECORD   
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed update_burial_point_to_flash @ 0x23014  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned int a, unsigned int b);
extern void debug_print(void);
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
    if (1 < *(volatile int *)((uintptr_t)&g_log_level) /*=0x2000230c*/) {
        if (*(volatile int *)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
            DEBUG_PRINT("%s(): update_burial_point_to_flash!!!\n" /*=0x9e655*/, "update_burial_point_to_flash" /*=0x9e789*/);
        } else {
            debug_print();
        }
    }
    iVar2 = flash_settings_read(FLASH_ADDR_SETTINGS_RECORD /*=0x135000*/, buf, 0xc0);
    if (iVar2 == 0) {
        char *p = param_1 + 0x10c6;
        iVar2 = memcmp(buf, p, 0xc0);
        if (iVar2 == 0) {
            return 0;
        }
        iVar2 = flash_settings_write_and_verify(FLASH_ADDR_SETTINGS_RECORD /*=0x135000*/, p, 0xc0);
        if (iVar2 == 0) {
            return 0;
        }
        if (*(volatile int *)((uintptr_t)&g_log_level) /*=0x2000230c*/ < 2) {
            return 0xffffffff;
        }
        iVar2 = *(volatile int *)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
        format_string = "%s(): burial_point flash_settings_write_and_verify error!\n" /*=0x9e69c*/;
    } else {
        if (*(volatile int *)((uintptr_t)&g_log_level) /*=0x2000230c*/ < 2) {
            return 0xffffffff;
        }
        iVar2 = *(volatile int *)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
        format_string = "%s(): burial_point read error!\n" /*=0x9e67c*/;
    }
    if (iVar2 == 0) {
        DEBUG_PRINT(format_string, "update_burial_point_to_flash" /*=0x9e789*/);
    } else {
        debug_print();
    }
    return 0xffffffff;
}

