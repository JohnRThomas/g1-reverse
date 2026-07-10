#include "g1_app_symbols.h"
/* named: upgradeQuickNoteDataToFlash */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20003960  g_quicknote_flash_msgq       
//   0x20007554  g_log_use_alt_sink           
//   0x200079e4  g_app_language_msgq          
*/
/* Reconstructed upgradeQuickNoteDataToFlash @ 0x24420  (parity: 300/300 trials, PROVEN) */

extern int k_msgq_put(unsigned int, void*, int, int);
extern void DEBUG_PRINT(unsigned int, unsigned int, ...);
extern void debug_print(void);
extern void FUN_00072880(unsigned int);

int upgradeQuickNoteDataToFlash(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
    unsigned int local_18;
    unsigned int local_14;
    unsigned int uStack_10;
    int iVar1;
    int uVar2;

    local_18 = ((uintptr_t)&tbl_ffc8) /*=0x10001*/;
    local_14 = (((param_1 & 0xff)) | ((param_2 & ((uintptr_t)&rodata_ff00) /*=0xff00*/))) & 0xffff00ff;
    uStack_10 = param_3;
    iVar1 = k_msgq_put(*(volatile unsigned int*)((uintptr_t)&g_quicknote_flash_msgq) /*=0x20003960*/, &local_18, 0, 0);
    if (iVar1 == 0) {
        if (2 < *(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/) {
            if (*(volatile unsigned int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                DEBUG_PRINT("%s(): SEND QUICKNOTE TEXT Store(%d) Command...\n" /*=0x9edf3*/, "upgradeQuickNoteDataToFlash" /*=0x9f094*/, param_1);
            } else {
                debug_print();
            }
        }
        FUN_00072880(*(volatile unsigned int*)((uintptr_t)&g_app_language_msgq) /*=0x200079e4*/);
        uVar2 = 0;
    } else {
        if (0 < *(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/) {
            if (*(volatile unsigned int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                DEBUG_PRINT("%s(): quicknote flash store queue fill failed\r\n\n" /*=0x9edc2*/, "upgradeQuickNoteDataToFlash" /*=0x9f094*/);
            } else {
                debug_print();
            }
        }
        uVar2 = -1;
    }
    return uVar2;
}

