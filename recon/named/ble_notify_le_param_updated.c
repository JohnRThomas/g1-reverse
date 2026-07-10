/* named: ble_notify_le_param_updated */
/* globals referenced:
//   0x2000ad1c  g_ble_conn_cb_list_head      
*/
/* Reconstructed ble_notify_le_param_updated @ 0x56ae0  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef uint32_t u32; typedef uint16_t u16;
typedef void (*fp)(int,u32,u32,u32);
extern void atomic_and_2(int*,u32,int,int,u32);
extern void printk(u32,...);
extern void assert_post_action(u32,u32);
void ble_notify_le_param_updated(int param_1, u32 p2, u32 p3, u32 p4){
    if( ((int)(*(volatile u32*)(param_1+4) << 0x16) < 0)
        && (*(u16*)(param_1+0xa8) <= *(u16*)(param_1+0xa6))
        && (*(u16*)(param_1+0xa6) <= *(u16*)(param_1+0xaa)) ){
        if(*(int*)(param_1+0xac) == *(int*)(param_1+0xb0)){
            atomic_and_2((int*)(param_1+4), 0xfffffdff, *(int*)(param_1+0xac), *(int*)(param_1+0xb0), p4);
        }
    }
    int iVar2 = *(volatile int*)0x2000ad1cUL;
    for(; iVar2 != 0; iVar2 = *(int*)(iVar2+0x20)){
        fp f = *(fp*)(iVar2+0xc);
        if(f != 0) f(param_1, *(u16*)(param_1+0xa6), *(u16*)(param_1+0xac), *(u16*)(param_1+0xae));
    }
    u32 uVar1 = 0x00088058;
    u32 uVar3 = 0x00087fec;
    while(1){
        if(uVar1 < uVar3){
            printk(0x00099cbd, 0x000f3a8d, 0x000f3a5d, 0x634);
            printk(0x000f0d20);
            assert_post_action(0x000f3a5d, 0x634);
        }
        if(uVar1 <= uVar3) break;
        fp f = *(fp*)(uVar3+0xc);
        if(f != 0) f(param_1, *(u16*)(param_1+0xa6), *(u16*)(param_1+0xac), *(u16*)(param_1+0xae));
        uVar3 += 0x24;
    }
}

