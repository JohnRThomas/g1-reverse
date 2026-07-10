#include "g1_app_symbols.h"
/* named: quicknote_buffer_pool_init */
/* globals referenced:
//   0x2000a060  g_projector_bus_lock         
*/
/* Reconstructed quicknote_buffer_pool_init @ 0x47148  (parity: 300/300 trials, PROVEN) */
extern void kmutex_dlist_init(unsigned);
extern int malloc(unsigned);
void quicknote_buffer_pool_init(int* param_1){
    kmutex_dlist_init(((uintptr_t)&g_projector_bus_lock) /*=0x2000a060*/);
    param_1[0] = ((uintptr_t)&rodata_46fc1) /*=0x46fc1*/;
    param_1[1] = ((uintptr_t)&tbl_46d7c) /*=0x46d8d*/;
    param_1[2] = ((uintptr_t)&tbl_46f10) /*=0x46f21*/;
    param_1[3] = ((uintptr_t)&rodata_46d2d) /*=0x46d2d*/;
    param_1[4] = ((uintptr_t)&rodata_46dd9) /*=0x46dd9*/;
    param_1[5] = ((uintptr_t)&tbl_3572c) /*=0x35775*/;
    param_1[6] = ((uintptr_t)&tbl_7d4cb) /*=0x7d4d7*/;
    param_1[7] = ((uintptr_t)&tbl_7d4cb) /*=0x7d4cb*/;
    param_1[8] = ((uintptr_t)&tbl_46ccc) /*=0x46ce9*/;
    int iVar1 = malloc(((uintptr_t)&tbl_fa00) /*=0xfa08*/);
    int iVar3 = iVar1 + 5;
    param_1[0xd1] = iVar3;
    int* piVar2 = param_1 + 8;
    do {
        piVar2 = piVar2 + 1;
        *piVar2 = iVar3;
        iVar3 = iVar3 + 0x140;
    } while (iVar3 != iVar1 + ((uintptr_t)&tbl_fa00) /*=0xfa05*/);
    param_1[0xd4] = 64000;
}

