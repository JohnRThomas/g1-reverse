#include "g1_app_symbols.h"
/* named: check_bind_status */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed check_bind_status @ 0x26b88  (parity: 300/300 trials, PROVEN) */

typedef unsigned char u8;
typedef unsigned int u32;
extern void DEBUG_PRINT(unsigned int, unsigned int, ...);
extern void debug_print(unsigned int, unsigned int);

void check_bind_status(int param_1, int param_2, int param_3)
{
    volatile char *pcVar2 = (volatile char*)((uintptr_t)&g_bind_status_log_debounce_cnt) /*=0x20018d83*/;
    char cVar1;
    char *base;

    if (param_2 == 0) {
        cVar1 = *pcVar2;
        if (cVar1 != 0) {
            char nv = (char)(cVar1 - 1);
            *pcVar2 = nv;
            if (nv != 0) return;
        }
        base = (char*)(param_1 + 0x1000);
        if (base[0x71] != 1) return;
        base[0x71] = 0;
        if (*(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/ <= 0) return;
        if (*(volatile u32*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
            DEBUG_PRINT("%s(): disable allow bind mode\n" /*=0x9fd02*/, "check_bind_status" /*=0xa1ad8*/);
        } else {
            debug_print("%s(): disable allow bind mode\n" /*=0x9fd02*/, "check_bind_status" /*=0xa1ad8*/);
        }
        return;
    } else {
        base = (char*)(param_1 + 0x1000);
        if (param_3 == 0) {
            if (base[0x71] == 0) {
                base[0x71] = 1;
                if (*(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/ > 0) {
                    if (*(volatile u32*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                        DEBUG_PRINT("%s(): enable allow bind mode\n" /*=0x9fce4*/, "check_bind_status" /*=0xa1ad8*/);
                    } else {
                        debug_print("%s(): enable allow bind mode\n" /*=0x9fce4*/, "check_bind_status" /*=0xa1ad8*/);
                    }
                }
            }
        } else {
            base[0x71] = 0;
        }
        *pcVar2 = 3;
    }
}

