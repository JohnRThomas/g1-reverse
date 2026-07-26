#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_mpsc_pbuf_buffer__param_0133           [param_0133; library]
 * Raw function identity: 0x0004be0c.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0004be0c @ 0x0004be0c
 * public-name: mpsc_pbuf_commit
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   mpsc_pbuf_commit                         <= FUN_0004be0c @ 0x0004be0c
 *   z_spin_lock_valid                        <= FUN_00072040 @ 0x00072040
 *   z_spin_unlock_valid                      <= FUN_0007205c @ 0x0007205c
 *   z_spin_lock_set_owner                    <= FUN_00072078 @ 0x00072078
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   idx_inc                                  <= FUN_0007e35c @ 0x0007e35c
 *   max_utilization_update                   <= FUN_0007e4f2 @ 0x0007e4f2
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f08c7                             @ 0x000f08c7
 *   rodata_f08f4                             @ 0x000f08f4
 *   rodata_f090b                             @ 0x000f090b
 *   rodata_f0920                             @ 0x000f0920
 *   rodata_f0935                             @ 0x000f0935
 */
/* Reconstructed FUN_0004be0c @ 0x4be0c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include <cmsis_gcc.h>
typedef uint32_t u32; typedef uint8_t u8;
typedef u32 (*fp)(u8*);
extern void printk(u32,u32,...);
extern void assert_post_action(u32,u32);
extern int z_spin_lock_valid(int);
extern void z_spin_lock_set_owner(int);
extern int z_spin_unlock_valid(int);
extern u32 idx_inc(int,u32,u32);
extern void max_utilization_update(int);
void mpsc_pbuf_commit(int param_1, u8* param_2){
    u32 uVar3 = (*(fp*)(param_1+0x1c))(param_2);
    int iVar5 = param_1+0x14;
    u32 uVar6 = __get_BASEPRI();
    __set_BASEPRI_MAX(0x20);
    __ISB();
    int iVar4 = z_spin_lock_valid(iVar5);
    if(iVar4==0){
        printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/, ((unsigned long)&rodata_f0920) /*=0xf0920*/, ((unsigned long)&rodata_f08c7) /*=0xf08c7*/, 0x72);
        printk(((unsigned long)&rodata_f0935) /*=0xf0935*/, iVar5);
        uVar3=0x72;
    } else {
        z_spin_lock_set_owner(iVar5);
        *param_2 = *param_2 | 1;
        uVar3 = idx_inc(param_1, *(u32*)(param_1+4), uVar3);
        *(u32*)(param_1+4) = uVar3;
        max_utilization_update(param_1);
        iVar4 = z_spin_unlock_valid(iVar5);
        if(iVar4!=0){
            __set_BASEPRI(uVar6);
            __ISB();
            return;
        }
        printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/, ((unsigned long)&rodata_f08f4) /*=0xf08f4*/, ((unsigned long)&rodata_f08c7) /*=0xf08c7*/, 0xf0);
        printk(((unsigned long)&rodata_f090b) /*=0xf090b*/, iVar5);
        uVar3=0xf0;
    }
    assert_post_action(((unsigned long)&rodata_f08c7) /*=0xf08c7*/, uVar3);
}
