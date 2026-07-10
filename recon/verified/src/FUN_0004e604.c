/* Reconstructed FUN_0004e604 @ 0x4e604  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef uint32_t u32;
typedef u32 (*fp)(u32,u32,u32,u32,u32);
extern int FUN_0007f1a0(u32,int,void*);
extern int FUN_0004e540(u32,void*);
extern void FUN_0004d944(u32,int,void*,int);
u32 FUN_0004e604(u32 param_1,u32 param_2,u32 param_3,u32 param_4,int* param_5){
    u32 local_24 = param_1;
    if(param_5 != 0){
        if(*param_5 != 0){
            int iVar1 = FUN_0007f1a0(param_1, *param_5, &local_24);
            if(iVar1 == 0) return 0;
        }
        if(param_5[1] != 0){
            return ((fp)(uintptr_t)param_5[1])(local_24, param_2, param_3, param_4, (u32)param_5[2]);
        }
    }
    int iVar1 = FUN_0004e540(param_1, &local_24);
    if(iVar1 != 0){
        u32 local_34 = (*(fp*)(iVar1+8))(local_24, param_2, param_3, param_4, 0);
        if(local_34 != 0){
            u32 buf[8];
            FUN_0004d944(0x00088278, 0x2440, buf, 0);
        }
    }
    return 0;
}

