#include "g1_app_symbols.h"
/* named: log_output_process */
/* Reconstructed log_output_process @ 0x4def8  (parity: 300/300 trials, PROVEN) */

extern int audio_hw_lock_get_status_byte(unsigned int, void*, unsigned int, unsigned int, unsigned int);
extern void FUN_0004dfb8(unsigned int);
extern void log_output_flush(unsigned int);

void log_output_process(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    int iVar2;
    unsigned int uStack_c = param_2;
    unsigned int uStack_8 = param_3;
    iVar2 = audio_hw_lock_get_status_byte(((uintptr_t)&tbl_87b30) /*=0x87bc0*/, (char*)&uStack_c + 3, param_3, param_4, param_1);
    if (iVar2 == 0 && *((unsigned char*)&uStack_c + 3) == 1) {
        FUN_0004dfb8(((uintptr_t)&tbl_87b30) /*=0x87bc0*/);
    }
    unsigned int uVar1 = ((uintptr_t)&tbl_8ac20) /*=0x8ad08*/;
    *(volatile unsigned char*)((uintptr_t)&log_output_flush_done) /*=0x2001d44e*/ = 1;
    log_output_flush(uVar1);
    return;
}

