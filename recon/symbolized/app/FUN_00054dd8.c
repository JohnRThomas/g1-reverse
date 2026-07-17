#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00054dd8 @ 0x00054dd8
 * public-name: FUN_00054dd8
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   bt_addr_le_eq                            <= FUN_00080fa4 @ 0x00080fa4
 *   memcmp                                   <= FUN_00086be4 @ 0x00086be4
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f3509                             @ 0x000f3509
 *   rodata_f3537                             @ 0x000f3537
 *   rodata_f354f                             @ 0x000f354f
 *   rodata_f3572                             @ 0x000f3572
 *   rodata_f358a                             @ 0x000f358a
 */
/* Reconstructed FUN_00054dd8 @ 0x54dd8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void assert_post_action(unsigned,unsigned);
extern void printk(unsigned,...);
extern int bt_addr_le_eq(int,int);
extern int memcmp(int,void*,int);
extern void memset_bytes(void*,int,int);

void FUN_00054dd8(int param_1, int *param_2){
    unsigned char auStack_30[24];
    unsigned uVar3;
    if (param_2 == 0){
        printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/, ((unsigned long)&rodata_f3537) /*=0xf3537*/, ((unsigned long)&rodata_f3509) /*=0xf3509*/, 0x36c);
        uVar3=0x36c; assert_post_action(((unsigned long)&rodata_f3509) /*=0xf3509*/, uVar3); return;
    }
    int iVar4 = *param_2;
    if (iVar4 == 0){
        printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/, ((unsigned long)&rodata_f354f) /*=0xf354f*/, ((unsigned long)&rodata_f3509) /*=0xf3509*/, 0x36d);
        uVar3=0x36d; assert_post_action(((unsigned long)&rodata_f3509) /*=0xf3509*/, uVar3); return;
    } else if (param_1 == 0){
        printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/, ((unsigned long)&rodata_f3572) /*=0xf3572*/, ((unsigned long)&rodata_f3509) /*=0xf3509*/, 0x36e);
        uVar3=0x36e; assert_post_action(((unsigned long)&rodata_f3509) /*=0xf3509*/, uVar3); return;
    } else {
        if (-1 < (int)((unsigned)*(unsigned char*)(iVar4+8) << 0x1d)){
            if (param_2[1] == 0 && (int)((unsigned)*(unsigned char*)(param_1+8) << 0x1d) < 0){
                int iVar1 = bt_addr_le_eq(iVar4+1, param_1+1);
                memset_bytes(auStack_30, 0, 0x16);
                int iVar2 = memcmp(iVar4+0x2a, auStack_30, 0x10);
                if ((iVar2 != 0 && memcmp(iVar4+0x2a, (void*)(param_1+0x2a), 0x10) == 0) || iVar1 != 0){
                    param_2[1] = param_1;
                }
            }
            return;
        }
        printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/, ((unsigned long)&rodata_f358a) /*=0xf358a*/, ((unsigned long)&rodata_f3509) /*=0xf3509*/, 0x370);
        uVar3=0x370; assert_post_action(((unsigned long)&rodata_f3509) /*=0xf3509*/, uVar3); return;
    }
}
