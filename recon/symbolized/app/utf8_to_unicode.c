#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000477a0 @ 0x000477a0
 * public-name: utf8_to_unicode
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   printf                                   <= FUN_000777f0 @ 0x000777f0
 * address symbols (name @ address):
 *   rodata_d7499                             @ 0x000d7499
 *   rodata_d74af                             @ 0x000d74af
 *   rodata_d74bd                             @ 0x000d74bd
 *   rodata_d752a                             @ 0x000d752a
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed utf8_to_unicode @ 0x477a0  (parity: 300/300 trials, PROVEN) */

typedef unsigned char byte;
typedef unsigned int uint;
extern void DEBUG_PRINT(unsigned int, unsigned int, ...);
extern void debug_print(unsigned int, unsigned int);
extern void printf(unsigned int);
extern void FUN_000778d4(unsigned int);

uint utf8_to_unicode(byte *param_1, int param_2)
{
    uint uVar1, uVar2;
    uVar2 = (uint)*param_1;
    if ((uVar2 & 0xf0) == 0xe0) {
        if (param_2 > 2) {
            uVar1 = (param_1[2] & 0x30) | ((param_1[1] & 3) << 6) | (param_1[2] & 0xf);
            uVar2 = ((param_1[1] >> 2) & 0xf) | ((uVar2 & 0xf) << 4);
            return uVar1 | (uVar2 << 8);
        }
        if (*(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/ > 3) {
            if (*(volatile unsigned int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                DEBUG_PRINT(((unsigned long)&rodata_d7499) /*=0xd7499*/, ((unsigned long)&rodata_d752a) /*=0xd752a*/);
            } else {
                debug_print(((unsigned long)&rodata_d7499) /*=0xd7499*/, ((unsigned long)&rodata_d752a) /*=0xd752a*/);
            }
        }
    } else if ((uVar2 & 0xe0) == 0xc0) {
        if (param_2 > 1) {
            uVar1 = (param_1[1] & 0x3f) | ((uVar2 & 3) << 6);
            uVar2 = (uVar2 >> 2) & 7;
            return uVar1 | (uVar2 << 8);
        }
        FUN_000778d4(((unsigned long)&rodata_d74af) /*=0xd74af*/);
    } else {
        printf(((unsigned long)&rodata_d74bd) /*=0xd74bd*/);
    }
    return 0;
}
