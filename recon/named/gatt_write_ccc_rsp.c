/* readable reconstruction; identity: FUN_0005a1b0 @ 0x0005a1b0
 * public-name: gatt_write_ccc_rsp
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gatt_find_conn_in_known_table            <= FUN_00059c70 @ 0x00059c70
 *   gatt_write_ccc_rsp                       <= FUN_0005a1b0 @ 0x0005a1b0
 *   atomic_and_4                             <= FUN_000826f6 @ 0x000826f6
 *   list_unlink_and_release                  <= FUN_000828e8 @ 0x000828e8
 *   log_msg_create_3arg                      <= FUN_00082a42 @ 0x00082a42
 * address symbols (name @ address):
 *   rodata_88128                             @ 0x00088128
 *   rodata_f4812                             @ 0x000f4812
 */
/* Reconstructed FUN_0005a1b0 @ 0x5a1b0  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef uint32_t u32;
typedef void (*fp)(u32,void*,int,int);
typedef void (*jp)(u32,int,u32*);
extern void atomic_and_4(u32*,u32);
extern int gatt_find_conn_in_known_table(u32);
extern void list_unlink_and_release(u32,int,u32*,u32*);
extern void log_msg_create_3arg(u32,int,void*);
void gatt_write_ccc_rsp(u32 param_1,int param_2,u32 param_3,u32 param_4,u32* param_5){
    atomic_and_4(param_5+5, 0xfffffffb);
    if(param_2 == 0){
        if(*(short*)((char*)param_5+0x10) == 0){
            (*(fp)(uintptr_t)*param_5)(param_1, param_5, param_2, param_2);
        }
    } else {
        int iVar1 = gatt_find_conn_in_known_table(param_1);
        if(iVar1 == 0) return;
        u32* puVar3 = *(u32**)(iVar1+8);
        if(puVar3 != 0){
            u32* puVar2 = (u32*)*puVar3;
            while(puVar3 != 0){
                if(puVar3 == param_5+6){
                    list_unlink_and_release(param_1, iVar1, puVar2, param_5);
                    break;
                }
                puVar3 = puVar2;
                if(puVar2 != 0) puVar2 = (u32*)*puVar2;
            }
        }
    }
    jp JUMP = (jp)(uintptr_t)param_5[1];
    if(JUMP == 0){
        if(param_5[2] == 0) return;
        u32 local[2]; local[0]=2; local[1]=0x000f4812;
        log_msg_create_3arg(0x00088128, 0x1080, local);
        JUMP = (jp)(uintptr_t)param_5[2];
        param_5 = 0;
    }
    JUMP(param_1, param_2, param_5);
}
