/* named: FUN_00055350 */
/* globals referenced:
//   0x20002000  g_ble_dev_state              
*/
/* Reconstructed FUN_00055350 @ 0x55350  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef uint32_t u32; typedef uint8_t u8; typedef uint16_t u16;
extern int FUN_00053d70(int,int,void*);
extern void net_buf_unref(void);
extern void FUN_0008104a(u32,int,void*);
unsigned FUN_00055350(int param_1, unsigned param_2){
    u32 local_34[8];
    u32 local_20[2];
    volatile u32 local_1c;
    int iVar1;
    local_1c = 0x000f376a;
    if( ((int)((u32)(*(volatile u8*)(0x20002000UL+0xc2)) << 0x1f) < 0)
        && (iVar1 = FUN_00053d70(0xfc09, 0, local_34), local_1c = 0x000f3796, iVar1 == 0) ){
        unsigned uVar5 = *(u8*)(*(int*)(local_34[0]+0xc)+1);
        u32* puVar4 = (u32*)(*(int*)(local_34[0]+0xc)+2);
        iVar1 = 0;
        if(param_2 <= uVar5) uVar5 = param_2;
        for(; iVar1 < (int)uVar5; iVar1++){
            u32* puVar2 = puVar4;
            u32* puVar6 = (u32*)(iVar1*0x16 + param_1);
            u32 *puVar3, *puVar7;
            do {
                puVar3 = puVar2+1;
                puVar7 = puVar6+1;
                *puVar6 = *puVar2;
                puVar2 = puVar3;
                puVar6 = puVar7;
            } while(puVar3 != puVar4+5);
            *(u16*)puVar7 = *(u16*)puVar3;
            puVar4 = (u32*)((int)puVar4 + 0x16);
        }
        net_buf_unref();
        if(uVar5 == 0){
            local_1c = 0x000f37b6;
            local_20[0] = 2;
            FUN_0008104a(0x00088150, 0x1080, local_20);
        }
        return uVar5;
    } else {
        local_20[0] = 2;
        FUN_0008104a(0x00088150, 0x1080, local_20);
        return 0;
    }
}

