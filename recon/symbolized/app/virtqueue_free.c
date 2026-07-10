#include "g1_app_symbols.h"
/* named: virtqueue_free */
/* Reconstructed virtqueue_free @ 0x70ee4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void FUN_000868b4(int);

void virtqueue_free(int param_1){
    if (param_1 != 0){
        if (*(short*)(param_1+0x24) != *(short*)(param_1+0xa)
            && 3 < *(unsigned char*)((uintptr_t)&g_metal_generic_bus) /*=0x2000b424*/
            && *(void**)((uintptr_t)&metal_log_handler) /*=0x2000b428*/ != 0){
            ((void(*)(int,unsigned,int))*(void**)((uintptr_t)&metal_log_handler) /*=0x2000b428*/)(4, "%s: freeing non-empty virtqueue\r\n" /*=0xf7b84*/, *(int*)(param_1+4));
        }
        FUN_000868b4(param_1);
    }
}

