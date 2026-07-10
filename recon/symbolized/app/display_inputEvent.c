#include "g1_app_symbols.h"
/* named: display_inputEvent */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed display_inputEvent @ 0x49938  (parity: 300/300 trials, PROVEN) */
extern void memset_bytes(void *a0, unsigned int a1, unsigned int a2);
extern void DEBUG_PRINT(unsigned int a0, unsigned int a1);
extern void debug_print(void);
extern int k_msgq_put(unsigned int a0, void *a1, unsigned int a2, unsigned int a3);

unsigned int display_inputEvent(unsigned char param_1, unsigned char param_2)
{
    unsigned char buf[6];
    int iVar1;
    unsigned int uVar2;
    memset_bytes(buf + 1, 0, 0x17);
    buf[0] = 5;
    *(unsigned short*)(buf + 2) = 2;
    buf[4] = param_1;
    buf[5] = param_2;
    iVar1 = k_msgq_put(((uintptr_t)&g_display_msgq) /*=0x200038c4*/, buf, 0UL, 0UL);
    if (iVar1 == 0) {
        uVar2 = 0;
        if (2 < *(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/) {
            if (*(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0)
                DEBUG_PRINT("%s(): send display input event command.......\n" /*=0xf00bb*/, "display_inputEvent" /*=0xf0151*/);
            else
                debug_print();
        }
    } else {
        DEBUG_PRINT("message queue send failed %s\r\n" /*=0xef058*/, "display_inputEvent" /*=0xf0151*/);
        uVar2 = 0xffffffffUL;
    }
    return uVar2;
}

