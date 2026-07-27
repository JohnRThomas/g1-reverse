/* readable reconstruction; identity: FUN_00056ae0 @ 0x00056ae0
 * public-name: ble_notify_le_param_updated
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ble_notify_le_param_updated              <= FUN_00056ae0 @ 0x00056ae0
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   atomic_and_2                             <= FUN_000813b4 @ 0x000813b4
 * address symbols (name @ address):
 *   rodata_87fec                             @ 0x00087fec
 *   rodata_88058                             @ 0x00088058
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f0d20                             @ 0x000f0d20   [INLINED -- G6 literal batch]
 *   rodata_f3a5d                             @ 0x000f3a5d
 *   rodata_f3a8d                             @ 0x000f3a8d   [INLINED -- G6 literal batch]
 *   g_ble_conn_cb_list_head                  @ 0x2000ad1c
 */
/* Reconstructed FUN_00056ae0 @ 0x56ae0  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "../headers/g1_log.h"
typedef uint32_t u32; typedef uint16_t u16;
typedef void (*fp)(int,u32,u32,u32);
extern void atomic_and_2(int*,u32,int,int,u32);
extern void assert_post_action(const char *, unsigned int);
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
            printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"), ((unsigned long)"cb <= _bt_conn_cb_list_end"), 0x000f3a5d, 0x634);
            printk(((unsigned long)"\tunexpected list end location\n"));
            assert_post_action(0x000f3a5d, 0x634);
        }
        if(uVar1 <= uVar3) break;
        fp f = *(fp*)(uVar3+0xc);
        if(f != 0) f(param_1, *(u16*)(param_1+0xa6), *(u16*)(param_1+0xac), *(u16*)(param_1+0xae));
        uVar3 += 0x24;
    }
}
