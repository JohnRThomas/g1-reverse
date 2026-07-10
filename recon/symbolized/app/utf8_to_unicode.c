#include "g1_app_symbols.h"
/* named: utf8_to_unicode */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
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
        if (*(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/ > 3) {
            if (*(volatile unsigned int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                DEBUG_PRINT("%s(): length error!\n\n" /*=0xd7499*/, "utf8_to_unicode" /*=0xd752a*/);
            } else {
                debug_print("%s(): length error!\n\n" /*=0xd7499*/, "utf8_to_unicode" /*=0xd752a*/);
            }
        }
    } else if ((uVar2 & 0xe0) == 0xc0) {
        if (param_2 > 1) {
            uVar1 = (param_1[1] & 0x3f) | ((uVar2 & 3) << 6);
            uVar2 = (uVar2 >> 2) & 7;
            return uVar1 | (uVar2 << 8);
        }
        FUN_000778d4("length error!" /*=0xd74af*/);
    } else {
        printf("maybe [%x] not unicode ?\n" /*=0xd74bd*/);
    }
    return 0;
}

