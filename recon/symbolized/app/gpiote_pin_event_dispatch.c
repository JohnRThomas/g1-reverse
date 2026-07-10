#include "g1_app_symbols.h"
/* named: gpiote_pin_event_dispatch */
/* globals referenced:
//   0x20002bc0  g_gpiote_cb                  
*/
/* Reconstructed gpiote_pin_event_dispatch @ 0x654c4  (parity: 300/300 trials, PROVEN) */

extern unsigned long long get_pin_idx(void);

void gpiote_pin_event_dispatch(unsigned int param_1)
{
    int iVar1;
    unsigned int uVar2;
    unsigned int uVar3;
    void (*UNRECOVERED_JUMPTABLE)(unsigned int, unsigned int, unsigned int);
    unsigned long long uVar4;

    uVar4 = get_pin_idx();
    iVar1 = ((uintptr_t)&g_gpiote_cb) /*=0x20002bc0*/;
    uVar2 = (unsigned int)(uVar4 >> 0x20);
    uVar3 = (unsigned int)*(volatile unsigned short *)(((uintptr_t)&g_gpiote_cb) /*=0x20002bc0*/ + ((int)uVar4 + 8) * 2);
    if ((int)(uVar3 << 0x17) < 0) {
        uVar3 = (uVar3 << 0x13) >> 0x1c;
        (*(void (**)(unsigned int, unsigned int, unsigned int))(((uintptr_t)&g_gpiote_cb) /*=0x20002bc0*/ + uVar3 * 8))
            (param_1, uVar2, *(volatile unsigned int *)(((uintptr_t)&g_gpiote_cb) /*=0x20002bc0*/ + uVar3 * 8 + 4));
    }
    UNRECOVERED_JUMPTABLE = *(void (**)(unsigned int, unsigned int, unsigned int))(iVar1 + 8);
    if (UNRECOVERED_JUMPTABLE != 0) {
        (*UNRECOVERED_JUMPTABLE)(param_1, uVar2, *(volatile unsigned int *)(iVar1 + 0xc));
        return;
    }
    return;
}

