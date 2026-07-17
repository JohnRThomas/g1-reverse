#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00034b34 @ 0x00034b34
 * public-name: load_whitelist
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   flash_settings_read                      <= FUN_000225b4 @ 0x000225b4
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_a8400                             @ 0x000a8400
 *   rodata_a842e                             @ 0x000a842e
 *   rodata_a8aa8                             @ 0x000a8aa8
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_app_whitelist_buffer                   @ 0x2001a22c
 */
/* Reconstructed load_whitelist @ 0x34b34  (parity: 300/300 trials, PROVEN) */

extern void memset_bytes(void*, int, int);
extern unsigned int flash_settings_read(unsigned int, void*, int);
extern void memcpy(unsigned int, void*, int);
extern void DEBUG_PRINT(unsigned int, unsigned int, unsigned int, unsigned int);
extern void debug_print(unsigned int, unsigned int, unsigned int, unsigned int);

unsigned int load_whitelist(void)
{
    unsigned int uVar1;
    unsigned int uVar2, uVar3;
    unsigned char buf[0x15e2];

    memset_bytes(buf, 0, 0x15e2);
    uVar1 = flash_settings_read(0x131000, buf, 0x15e2);
    if (uVar1 == 0) {
        uVar1 = (unsigned int)buf[1];
        if (uVar1 < 0x65) {
            memcpy(((unsigned long)g_app_whitelist_buffer) /*=0x2001a22c*/, buf, 0x15e2);
            return 0;
        }
        if (*(volatile unsigned int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ != 0) {
            uVar3 = 0x36;
            uVar2 = ((unsigned long)&rodata_a842e) /*=0xa842e*/;
            debug_print(uVar2, ((unsigned long)&rodata_a8aa8) /*=0xa8aa8*/, uVar3, uVar1);
            return 0xffffffff;
        }
        uVar3 = 0x36;
        uVar2 = ((unsigned long)&rodata_a842e) /*=0xa842e*/;
    } else {
        if (*(volatile unsigned int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ != 0) {
            uVar3 = 0x30;
            uVar2 = ((unsigned long)&rodata_a8400) /*=0xa8400*/;
            debug_print(uVar2, ((unsigned long)&rodata_a8aa8) /*=0xa8aa8*/, uVar3, uVar1);
            return 0xffffffff;
        }
        uVar3 = 0x30;
        uVar2 = ((unsigned long)&rodata_a8400) /*=0xa8400*/;
    }
    DEBUG_PRINT(uVar2, ((unsigned long)&rodata_a8aa8) /*=0xa8aa8*/, uVar3, uVar1);
    return 0xffffffff;
}
