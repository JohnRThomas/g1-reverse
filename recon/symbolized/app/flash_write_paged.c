#include "g1_app_symbols.h"
/* named: flash_write_paged */
/* globals referenced:
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed flash_write_paged @ 0x227d0  (parity: 300/300 trials, PROVEN) */
extern void DEBUG_PRINT(unsigned a, unsigned b);
extern void debug_print(void);
extern int flash_settings_write_and_verify(int a, int b, int c);
int flash_write_paged(int param_1, int param_2, unsigned param_3){
    if (*(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0){
        DEBUG_PRINT("size is %d\n" /*=0x9e3db*/, param_3);
    } else {
        debug_print();
    }
    int iVar3 = 0;
    unsigned r6 = (((param_3 >> 12) + 1) & 0xff);
    int sl = (int)r6 - 1;
    int r4 = (short)(int)(param_3 - (sl << 12));
    unsigned uVar2 = 0;
    for(; (uVar2 & 0xff) < r6; uVar2++){
        int r2 = (sl <= (int)uVar2) ? r4 : 0x1000;
        int iVar1 = flash_settings_write_and_verify(param_1 + (int)(uVar2*0x1000), param_2 + (int)(uVar2*0x1000), r2);
        iVar3 += iVar1;
    }
    return iVar3;
}

