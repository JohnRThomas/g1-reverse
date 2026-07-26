#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_utf8_decode_cursor__param_0121         [param_0121; G1-original]
 * Raw function identity: 0x000477a0.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_000477a0 @ 0x000477a0
 * public-name: utf8_to_unicode
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   printf                                   <= FUN_000777f0 @ 0x000777f0
 *   puts                                     <= FUN_000778d4 @ 0x000778d4
 * address symbols (name @ address):
 *   rodata_d7499                             @ 0x000d7499   [INLINED -- G6 literal batch]
 *   rodata_d74af                             @ 0x000d74af   [INLINED -- G6 literal batch]
 *   rodata_d74bd                             @ 0x000d74bd   [INLINED -- G6 literal batch]
 *   rodata_d752a                             @ 0x000d752a   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed utf8_to_unicode @ 0x477a0  (parity: 300/300 trials, PROVEN) */

typedef unsigned char byte;
typedef unsigned int uint;
extern void log_message(unsigned int, unsigned int, ...);
extern void debug_print(unsigned int, unsigned int);
extern void printf(unsigned int);
extern void puts(unsigned int);

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
                log_message(((unsigned long)"%s(): length error!\n\n") /*=0xd7499*/, ((unsigned long)"utf8_to_unicode") /*=0xd752a*/);
            } else {
                debug_print(((unsigned long)"%s(): length error!\n\n") /*=0xd7499*/, ((unsigned long)"utf8_to_unicode") /*=0xd752a*/);
            }
        }
    } else if ((uVar2 & 0xe0) == 0xc0) {
        if (param_2 > 1) {
            uVar1 = (param_1[1] & 0x3f) | ((uVar2 & 3) << 6);
            uVar2 = (uVar2 >> 2) & 7;
            return uVar1 | (uVar2 << 8);
        }
        puts(((unsigned long)"length error!") /*=0xd74af*/);
    } else {
        printf(((unsigned long)"maybe [%x] not unicode \?\n") /*=0xd74bd*/);
    }
    return 0;
}
