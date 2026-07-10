/* named: settings_call_set_handler */
/* Reconstructed settings_call_set_handler @ 0x4e604  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef uint32_t u32;
typedef u32 (*fp)(u32,u32,u32,u32,u32);
extern int settings_name_steq(u32,int,void*);
extern int settings_parse_and_lookup(u32,void*);
extern void FUN_0004d944(u32,int,void*,int);
u32 settings_call_set_handler(u32 param_1,u32 param_2,u32 param_3,u32 param_4,int* param_5){
    u32 local_24 = param_1;
    if(param_5 != 0){
        if(*param_5 != 0){
            int iVar1 = settings_name_steq(param_1, *param_5, &local_24);
            if(iVar1 == 0) return 0;
        }
        if(param_5[1] != 0){
            return ((fp)(uintptr_t)param_5[1])(local_24, param_2, param_3, param_4, (u32)param_5[2]);
        }
    }
    int iVar1 = settings_parse_and_lookup(param_1, &local_24);
    if(iVar1 != 0){
        u32 local_34 = (*(fp*)(iVar1+8))(local_24, param_2, param_3, param_4, 0);
        if(local_34 != 0){
            u32 buf[8];
            FUN_0004d944(0x00088278, 0x2440, buf, 0);
        }
    }
    return 0;
}

