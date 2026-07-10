#include "g1_app_symbols.h"
/* named: display_close */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed display_close @ 0x497b0  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned int a, unsigned int b);
extern void debug_print(void);
extern int k_msgq_put(unsigned int a, void *b, int c, int d);
extern void memcpy(void *dst, void *src, unsigned int n);
extern void memset_bytes(void *dst, int val, int n);

unsigned int display_close(void *param_1, unsigned int param_2)
{
    unsigned char buf[24 + 4];
    int iVar1;

    memset_bytes(buf, 0, 0x18);
    if (param_2 < 0xb) {
        buf[0] = 3;
        if (param_1 != (void*)0) {
            memcpy(buf + 4, param_1, param_2);
            *(volatile unsigned short *)(buf + 2) = (unsigned short)param_2;
        }
        iVar1 = k_msgq_put(((uintptr_t)&g_display_msgq) /*=0x200038c4*/, buf, 0, 0);
        if (iVar1 == 0) {
            if (*(volatile int *)((uintptr_t)&g_log_level) /*=0x2000230c*/ < 1) {
                return 0;
            }
            if (*(volatile int *)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ != 0) {
                debug_print();
                return 0;
            }
            DEBUG_PRINT("%s(): send display close command.......\n" /*=0xf0044*/, "display_close" /*=0xf018c*/);
            return 0;
        }
        DEBUG_PRINT("message queue send failed %s\r\n" /*=0xef058*/, "display_close" /*=0xf018c*/);
    } else if (0 < *(volatile int *)((uintptr_t)&g_log_level) /*=0x2000230c*/) {
        if (*(volatile int *)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
            DEBUG_PRINT("%s(): send data length more than %d,can't load it,exit ...\n" /*=0xef01c*/, "display_close" /*=0xf018c*/);
        } else {
            debug_print();
        }
    }
    return 0xffffffff;
}

