#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00023400 @ 0x00023400
 * public-name: read_usr_settting_from_flash
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   flash_settings_read                      <= FUN_000225b4 @ 0x000225b4
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_9e60c                             @ 0x0009e60c
 *   rodata_9e708                             @ 0x0009e708
 *   rodata_9e72a                             @ 0x0009e72a
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed read_usr_settting_from_flash @ 0x23400  (parity: 300/300 trials, PROVEN) */
extern void memset_bytes(void *a0, unsigned int a1, unsigned int a2);
extern int flash_settings_read(unsigned int a0, void *a1, unsigned int a2);
extern void DEBUG_PRINT(unsigned int a0, unsigned int a1);
extern void debug_print(unsigned int, unsigned int);

unsigned int read_usr_settting_from_flash(unsigned char *param_1)
{
    unsigned char buf[32];
    int iVar1;
    unsigned int uVar2;
    memset_bytes(buf, 0, 0x20);
    iVar1 = flash_settings_read(0x134000UL, buf, 0x20UL);
    if (iVar1 == 0) {
        if (1 < *(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/) {
            if (*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0)
                DEBUG_PRINT(((unsigned long)&rodata_9e708) /*=0x9e708*/, ((unsigned long)&rodata_9e72a) /*=0x9e72a*/);
            else
                debug_print(((unsigned long)&rodata_9e708) /*=0x9e708*/, ((unsigned long)&rodata_9e72a) /*=0x9e72a*/);
        }
        param_1[0x15] = buf[0x15];
        *(unsigned short*)(param_1 + 0x16) = *(unsigned short*)(buf + 0x16);
        uVar2 = 0;
    } else {
        if (1 < *(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/) {
            if (*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0)
                DEBUG_PRINT(((unsigned long)&rodata_9e60c) /*=0x9e60c*/, ((unsigned long)&rodata_9e72a) /*=0x9e72a*/);
            else
                debug_print(((unsigned long)&rodata_9e60c) /*=0x9e60c*/, ((unsigned long)&rodata_9e72a) /*=0x9e72a*/);
        }
        uVar2 = 0xffffffffUL;
    }
    return uVar2;
}
