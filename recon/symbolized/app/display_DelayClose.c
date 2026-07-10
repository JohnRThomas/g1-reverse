#include "g1_app_symbols.h"
/* named: display_DelayClose */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed display_DelayClose @ 0x498c0  (parity: 300/300 trials, PROVEN) */

extern void memset_bytes(void *dst, int val, unsigned int len);
extern int k_msgq_put(void *obj, void *msg, unsigned int a, unsigned int b);
extern void DEBUG_PRINT(unsigned int fmt, unsigned int arg);
extern void debug_print(void);

unsigned int display_DelayClose(unsigned int param_1)
{
    unsigned char buf[0x18];
    memset_bytes(buf + 1, 0, 0x17);
    buf[0] = 4;
    *(unsigned short *)(buf + 2) = 4;
    *(unsigned int *)(buf + 4) = param_1;

    void *obj = (void *)((uintptr_t)&g_display_msgq) /*=0x200038c4*/;
    int iVar1 = k_msgq_put(obj, buf, 0, 0);
    unsigned int uVar2;

    if (iVar1 == 0) {
        uVar2 = 0;
        if (*(volatile int *)((uintptr_t)&g_log_level) /*=0x2000230c*/ > 2) {
            if (*(volatile int *)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                DEBUG_PRINT("%s(): send display delay close command.......\n" /*=0xf008c*/, "display_DelayClose" /*=0xf0164*/);
            } else {
                debug_print();
            }
        }
    } else {
        DEBUG_PRINT("message queue send failed %s\r\n" /*=0xef058*/, "display_DelayClose" /*=0xf0164*/);
        uVar2 = 0xffffffffU;
    }
    return uVar2;
}

