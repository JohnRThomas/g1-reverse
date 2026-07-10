#include "g1_app_symbols.h"
/* named: FUN_00085a9c */
/* Reconstructed FUN_00085a9c @ 0x85a9c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int virtqueue_add_buffer(int,int,int,int,int);
extern int virtqueue_get_buffer_length(int,int);
extern int FUN_000857e0(int);
extern int mutex_lock_wait_forever_dup(int);
extern int thunk_FUN_00072880(int);
int FUN_00085a9c(char *param_1, char *param_2){
    uint32_t uVar2 = *(volatile uint32_t*)(param_2 - 8);
    mutex_lock_wait_forever_dup((int)(param_1+0x58));
    int uVar1 = virtqueue_get_buffer_length(*(volatile int*)(param_1+0xa4), uVar2 & ((uintptr_t)&tbl_ffc8) /*=0xffff*/);
    if(*(volatile int*)(*(volatile int*)(param_1+0xa0)+0x18)==0){
        virtqueue_add_buffer(*(volatile int*)(param_1+0xa4), (int)(param_2-0x10), 0, 1, uVar1);
    }
    FUN_000857e0(*(volatile int*)(param_1+0xa4));
    return thunk_FUN_00072880((int)(param_1+0x58));
}

