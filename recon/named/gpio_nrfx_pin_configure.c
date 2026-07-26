/* readable reconstruction; identity: FUN_00061624 @ 0x00061624
 * public-name: gpio_nrfx_pin_configure
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gpio_nrfx_pin_configure                  <= FUN_00061624 @ 0x00061624
 *   gpiote_in_init                           <= FUN_0006567c @ 0x0006567c
 *   gpiote_trigger_enable                    <= FUN_000657e4 @ 0x000657e4
 *   gpiote_pin_channel_get                   <= FUN_000658e8 @ 0x000658e8
 *   gpiote_lock_release                      <= FUN_000659cc @ 0x000659cc
 *   gpiote_in_uninit                         <= FUN_00065b18 @ 0x00065b18
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_10000                             @ 0x00010000
 *   rodata_30000                             @ 0x00030000
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f0ac7                             @ 0x000f0ac7   [INLINED -- G6 literal batch]
 *   rodata_f5e79                             @ 0x000f5e79
 */
/* Reconstructed FUN_00061624 @ 0x61624  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "../headers/g1_log.h"
extern int gpiote_in_init(int,...);
extern int gpiote_trigger_enable(int,...);
extern int gpiote_pin_channel_get(int,...);
extern int gpiote_lock_release(int,...);
extern int gpiote_in_uninit(int,...);
extern int assert_post_action(int,...) __attribute__((noreturn));

unsigned gpio_nrfx_pin_configure(int param_1, unsigned param_2, unsigned param_3, unsigned param_4)
{
    unsigned uVar1; int iVar2,iVar3; unsigned uVar4,uVar5,uVar6,uVar8; unsigned char bVar7; int iVar9; int bVar10;
    struct { unsigned param2, param3, param4; } record;
    iVar9 = *(int*)(param_1+4);
    uVar8 = (param_2 & 0x1f) | ((unsigned)*(unsigned char*)(iVar9+0xc) << 5);
    record.param2 = param_2;
    record.param3 = param_3;
    record.param4 = param_4;
    iVar2 = gpiote_pin_channel_get(uVar8, (int)&record.param2 + 3, param_3, (unsigned)*(unsigned char*)(iVar9+0xc), param_1);
    if((param_3 & 0x30000) == 0){
        gpiote_in_uninit(uVar8);
        if(iVar2 == 0x0bad0000){
            iVar9 = gpiote_lock_release((unsigned char)(record.param2>>24));
            if(iVar9 != iVar2){
                printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"), ((unsigned long)"err == NRFX_SUCCESS"), 0x000f5e79, 0x6c);
                uVar4 = 0x6c;
LAB_00061674:
                assert_post_action(0x000f5e79, uVar4);
            }
        }
LAB_00061734:
        uVar4 = 0;
    } else {
        record.param3 = 0; record.param4 = 0;
        iVar3 = gpiote_in_init(uVar8, 0, &record.param3);
        if(iVar3 != 0x0bad0000) goto LAB_000616ce;
        if(iVar2 == iVar3){
            iVar3 = gpiote_lock_release((unsigned char)(record.param2>>24));
            if(iVar3 != iVar2){
                printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"), ((unsigned long)"err == NRFX_SUCCESS"), 0x000f5e79, 0x7f);
                uVar4 = 0x7f;
                goto LAB_00061674;
            }
        }
        uVar1 = record.param3;
        if((int)(param_3 << 0xe) < 0){
            uVar5 = param_3 & 0x306;
            if(uVar5 == 0x106){
                uVar5 = 7;
LAB_000616f8:
                if((int)(param_3 << 0x1b) < 0){ uVar6 = 3; }
                else { uVar6 = (param_3 << 0x1a) >> 0x1f; }
                *((unsigned char*)&record.param3 + 3) = (unsigned char)(uVar1 >> 24);
                *((unsigned char*)&record.param3 + 0) = (unsigned char)uVar5;
                *((unsigned char*)&record.param3 + 1) = (unsigned char)(((param_3 ^ 0x10000) << 0xf) >> 0x1f);
                *((unsigned char*)&record.param3 + 2) = (unsigned char)uVar6;
                if((int)(param_3 << 0xc) < 0){
                    *(int*)(*(int*)(iVar9+4)+8) = 1 << (param_2 & 0xff);
                } else {
                    iVar2 = param_3 << 0xd;
                    bVar10 = iVar2 < 0;
                    if(bVar10){ iVar2 = *(int*)(iVar9+4); uVar6 = 1 << (param_2 & 0xff); }
                    if(bVar10){ *(unsigned*)(iVar2+0xc) = uVar6; }
                }
                iVar2 = gpiote_trigger_enable(uVar8, &record.param3, 0);
                goto LAB_0006172e;
            }
            if(0x106 < uVar5){
                if(uVar5 == 0x202){ uVar5 = 5; }
                else if(uVar5 == 0x300){ uVar5 = 3; }
                else { if(uVar5 != 0x200) goto LAB_000616ce; uVar5 = 2; }
                goto LAB_000616f8;
            }
            if(uVar5 == 6) goto LAB_000616f8;
            if(uVar5 < 7){
                if(uVar5 != 0){ if(uVar5 != 2) goto LAB_000616ce; uVar5 = 4; }
                goto LAB_000616f8;
            }
            if(uVar5 == 0x100){ uVar5 = 1; goto LAB_000616f8; }
        } else {
            if((int)(param_3 << 0x1b) < 0){ bVar7 = 3; }
            else { bVar7 = (unsigned char)((param_3 << 0x1a) >> 0x1f); }
            *((unsigned char*)&record.param3) = bVar7;
            iVar2 = gpiote_in_init(uVar8, &record.param3, 0);
LAB_0006172e:
            if(iVar2 == 0x0bad0000) goto LAB_00061734;
        }
LAB_000616ce:
        uVar4 = 0xffffffea;
    }
    return uVar4;
}
