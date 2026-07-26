/* readable reconstruction; identity: FUN_000503d8 @ 0x000503d8
 * public-name: arm_mem_manage_fault_helper
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   arm_mem_manage_fault_helper              <= FUN_000503d8 @ 0x000503d8
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   arm_fault_forward_handler                <= FUN_00080780 @ 0x00080780
 * address symbols (name @ address):
 *   rodata_88258                             @ 0x00088258
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f1c39                             @ 0x000f1c39
 *   rodata_f1c4f                             @ 0x000f1c4f
 *   rodata_f1c82                             @ 0x000f1c82
 *   rodata_f1c95                             @ 0x000f1c95
 *   rodata_f1cad                             @ 0x000f1cad
 *   rodata_f1cc3                             @ 0x000f1cc3
 *   rodata_f1ce2                             @ 0x000f1ce2
 *   rodata_f1d11                             @ 0x000f1d11
 *   rodata_f1d4b                             @ 0x000f1d4b
 *   rodata_f1d95                             @ 0x000f1d95
 */
/* Reconstructed FUN_000503d8 @ 0x503d8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "../headers/g1_nrf_regs.h"
extern int assert_post_action(int,...) __attribute__((noreturn));
extern int printk(int,...);
extern int arm_fault_forward_handler(int,...);
#define SCB28 (*(volatile int*)G1_SCB_CFSR)

unsigned arm_mem_manage_fault_helper(int param_1, unsigned char *param_2)
{
    int iVar1; unsigned uVar2, uVar3; int bVar4;
    struct { unsigned count, format; } log2;
    struct { unsigned count, format, value; } log3;
    log2.count = 2;
    log2.format = 0x000f1c39;
    arm_fault_forward_handler(0x00088258, 0x1040, &log2);
    if(SCB28 << 0x1b < 0){
        log2.count = 2; log2.format = 0x000f1c4f;
        arm_fault_forward_handler(0x00088258, 0x1040, &log2);
        uVar2 = 0x11;
    } else { uVar2 = 0x10; }
    if(SCB28 << 0x1c < 0){
        log2.format = 0x000f1c82; log2.count = 2;
        arm_fault_forward_handler(0x00088258, 0x1040, &log2);
        uVar2 = 0x12;
    }
    iVar1 = G1_SCB_CPUID;
    if(SCB28 << 0x1e < 0){
        log2.format = 0x000f1c95; log2.count = 2;
        arm_fault_forward_handler(0x00088258, 0x1040, &log2);
        if(*(volatile int*)(iVar1+0x28) << 0x18 < 0){
            log3.count = 3; log3.format = 0x000f1cad;
            log3.value = *(volatile unsigned*)(iVar1+0x34);
            arm_fault_forward_handler(0x00088258, 0x1840, &log3);
            if(param_1 != 0){
                *(volatile unsigned*)(iVar1+0x28) = *(volatile unsigned*)(iVar1+0x28) & 0xffffff7f;
            }
        }
        uVar2 = 0x13;
    }
    if(SCB28 << 0x1f < 0){
        log2.format = 0x000f1cc3; log2.count = 2;
        arm_fault_forward_handler(0x00088258, 0x1040, &log2);
        uVar2 = 0x14;
    }
    if(SCB28 << 0x1a < 0){
        log2.format = 0x000f1ce2; log2.count = 2;
        arm_fault_forward_handler(0x00088258, 0x1040, &log2);
        uVar2 = 0x15;
    }
    iVar1 = G1_SCB_CPUID;
    if(((SCB28 << 0x1b < 0) || (SCB28 << 0x1e < 0)) && (SCB28 << 0x1b < 0)){
        printk(0x00099cbd, 0x000f1d4b, 0x000f1d11, 0x163);
        printk(0x000f1d95);
        assert_post_action(0x000f1d11, 0x163);
    }
    uVar3 = SCB28 << 0x1a;
    bVar4 = (int)uVar3 < 0;
    if(bVar4){ uVar3 = *(volatile unsigned*)(iVar1+0x24) & 0xffffdfff; }
    if(bVar4){ *(volatile unsigned*)(iVar1+0x24) = uVar3; }
    *(volatile unsigned*)(iVar1+0x28) = *(volatile unsigned*)(iVar1+0x28) | 0xff;
    *param_2 = 0;
    return uVar2;
}
