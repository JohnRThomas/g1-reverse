#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_lsm6dso_dev_ctx__param_0308            [param_0308; G1-original]
 * Raw function identity: 0x000622a0.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_000622a0 @ 0x000622a0
 * public-name: lsm6dso_init_chip
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   lsm6dso_init_chip                        <= FUN_000622a0 @ 0x000622a0
 *   audio_codec_set_reg10_field2             <= FUN_0007f998 @ 0x0007f998
 *   audio_codec_set_reg11_field1             <= FUN_0007f9c6 @ 0x0007f9c6
 *   audio_codec_set_reg12_bit6               <= FUN_0007f9f4 @ 0x0007f9f4
 *   audio_codec_set_dual_reg14_reg15         <= FUN_0007fa22 @ 0x0007fa22
 *   audio_codec_set_reg16_bit7               <= FUN_0007fa7a @ 0x0007fa7a
 *   audio_codec_select_page                  <= FUN_0007fb20 @ 0x0007fb20
 *   audio_codec_read_reg0x0f                 <= FUN_0007fb3e @ 0x0007fb3e
 *   audio_codec_set_reg12_bit0               <= FUN_0007fb4c @ 0x0007fb4c
 *   audio_codec_set_reg18_and_reg62          <= FUN_0007fb7a @ 0x0007fb7a
 *   audio_codec_set_reg0x0a_field0           <= FUN_0007fbd6 @ 0x0007fbd6
 *   audio_codec_set_gain_ch0                 <= FUN_0007fc72 @ 0x0007fc72
 *   audio_codec_set_gain_ch1                 <= FUN_0007fd4e @ 0x0007fd4e
 *   audio_codec_set_reg14_bit2               <= FUN_0007fe2a @ 0x0007fe2a
 *   audio_codec_get_reg14_bit2               <= FUN_0007fe72 @ 0x0007fe72
 *   delay_scaled_busy_wait                   <= FUN_00086384 @ 0x00086384
 * address symbols (name @ address):
 *   rodata_99042                             @ 0x00099042
 *   rodata_9905e                             @ 0x0009905e
 *   rodata_f6292                             @ 0x000f6292
 *   rodata_f62ac                             @ 0x000f62ac
 *   rodata_f62c5                             @ 0x000f62c5
 *   rodata_f62e6                             @ 0x000f62e6
 *   rodata_f62fd                             @ 0x000f62fd
 *   rodata_f6315                             @ 0x000f6315
 *   rodata_f6337                             @ 0x000f6337
 *   rodata_f6353                             @ 0x000f6353
 *   rodata_f6364                             @ 0x000f6364
 *   rodata_f6378                             @ 0x000f6378
 *   rodata_f639f                             @ 0x000f639f
 *   rodata_f63b1                             @ 0x000f63b1
 *   rodata_f63c1                             @ 0x000f63c1
 *   rodata_f63e6                             @ 0x000f63e6
 *   rodata_f63f9                             @ 0x000f63f9
 *   rodata_f641c                             @ 0x000f641c
 *   rodata_f642d                             @ 0x000f642d
 *   rodata_f644e                             @ 0x000f644e
 *   rodata_f6468                             @ 0x000f6468
 *   rodata_f6481                             @ 0x000f6481
 */
/* Reconstructed FUN_000622a0 @ 0x622a0  (parity: 300/300 trials, PROVEN) */
extern void log_message(int fmt, ...);
extern int audio_codec_set_reg10_field2(int a0,int a1);
extern int audio_codec_set_reg11_field1(int a0,int a1);
extern int audio_codec_set_reg12_bit6(int a0,int a1);
extern int audio_codec_set_dual_reg14_reg15(int a0,int a1);
extern int audio_codec_set_reg16_bit7(int a0,int a1);
extern int audio_codec_select_page(int a0,int a1,int a2,void *a3,int a4);
extern int audio_codec_read_reg0x0f(int a0,int a1);
extern int audio_codec_set_reg12_bit0(int a0,int a1);
extern int audio_codec_set_reg18_and_reg62(int a0,int a1);
extern int audio_codec_set_reg0x0a_field0(int a0,int a1);
extern int audio_codec_set_gain_ch0(int a0,int a1);
extern int audio_codec_set_gain_ch1(int a0,int a1);
extern int audio_codec_set_reg14_bit2(int a0,int a1);
extern int audio_codec_get_reg14_bit2(int a0,int a1);
extern void delay_scaled_busy_wait(int a0);

int lsm6dso_init_chip(int param_1, unsigned int param_2, int param_3)
{
    int *piVar6, iVar7, iVar8, iVar2, iVar10;
    unsigned int uVar3, uVar5;
    signed char cVar4;
    unsigned short uVar9;
    int bVar11;
    unsigned int uStack_24;

    piVar6 = *(int**)(param_1+0x10);
    *piVar6 = param_1;
    iVar7 = *(int*)(param_1+4);
    iVar8 = *(int*)(param_1+0x10);
    uStack_24 = param_2;

    iVar2 = audio_codec_select_page(iVar7, 0, param_3, piVar6, param_1);
    uVar3 = ((unsigned long)&rodata_f6292) /*=0xf6292*/;
    if (iVar2 < 0) goto control_label_622bc;
    iVar2 = audio_codec_read_reg0x0f(iVar7, ((int)&uStack_24) + 2);
    uVar3 = ((unsigned long)&rodata_f62ac) /*=0xf62ac*/;
    if (iVar2 < 0) goto control_label_622bc;

    log_message(((unsigned long)&rodata_f62c5) /*=0xf62c5*/, (uStack_24 >> 0x10) & 0xff);
    uVar5 = (uStack_24 >> 0x10) & 0xff;
    uVar3 = ((unsigned long)&rodata_f62e6) /*=0xf62e6*/;
    if (uVar5 == 0x6c) {
        iVar2 = audio_codec_set_reg18_and_reg62(iVar7, 0x80);
        uVar3 = ((unsigned long)&rodata_f62fd) /*=0xf62fd*/;
        if (iVar2 < 0) goto control_label_622bc;
        iVar2 = audio_codec_get_reg14_bit2(iVar7, ((int)&uStack_24) + 3);
        uVar3 = ((unsigned long)&rodata_f6315) /*=0xf6315*/;
        if (iVar2 < 0) goto control_label_622bc;
        if (((uStack_24 >> 0x18) & 0xff) != 0) {
            log_message(((unsigned long)&rodata_f6337) /*=0xf6337*/);
            audio_codec_set_reg14_bit2(iVar7, 0);
            delay_scaled_busy_wait(300);
        }
        iVar2 = audio_codec_set_reg12_bit0(iVar7, 1);
        if (iVar2 < 0) goto control_label_622ec;
        delay_scaled_busy_wait(100);
        log_message(((unsigned long)&rodata_f6353) /*=0xf6353*/, (unsigned int)(unsigned char)*(volatile unsigned char*)(iVar7+0x18));
        cVar4 = *(volatile signed char*)(iVar7+0x18);
        if ((cVar4 != 1) && (cVar4 != 2)) cVar4 = 0;
        audio_codec_set_dual_reg14_reg15(iVar7, cVar4);
        uVar5 = (*(volatile unsigned char*)(iVar7+0x1a)) & 0x3f;
        log_message(((unsigned long)&rodata_f6364) /*=0xf6364*/, uVar5);
        iVar10 = *(int*)(param_1+0x10);
        iVar2 = audio_codec_set_reg10_field2(*(int*)(param_1+4), uVar5);
        uVar3 = ((unsigned long)&rodata_f6378) /*=0xf6378*/;
        if (iVar2 >= 0) {
            *(volatile unsigned char*)(iVar10+0x1e) = (unsigned char)uVar5;
            uVar3 = ((unsigned long)&rodata_f639f) /*=0xf639f*/;
            bVar11 = (*(volatile signed char*)(iVar7+0x1a)) >= 0;
            {
                unsigned short tbl = *(volatile unsigned short*)(((unsigned long)&rodata_9905e) /*=0x9905e*/ + (unsigned int)uVar5*2);
                unsigned long long lVar1;
                unsigned int newv;
                if (bVar11) {
                    lVar1 = (unsigned long long)tbl * 0x3d;
                    newv = (unsigned int)(lVar1 >> 1);
                } else {
                    lVar1 = (((unsigned long long)0x3d) << 32) | (unsigned long long)tbl;
                    newv = (unsigned int)(lVar1 >> 32) * (unsigned int)lVar1;
                }
                *(volatile unsigned int*)(iVar8+0xc) = newv;
            }
            uVar5 = (unsigned int)(unsigned char)*(volatile unsigned char*)(iVar7+0x19);
            log_message(uVar3, uVar5);
            if (uVar5 > 10) {
                iVar10 = 0x1a04;
            }
            uVar9 = (unsigned short)iVar10;
            if (uVar5 < 0xb) {
                uVar9 = *(volatile unsigned short*)(0x00099066UL + (unsigned int)uVar5*2);
            }
            *(volatile unsigned short*)(iVar8+0x1c) = uVar9;
            iVar10 = *(int*)(param_1+0x10);
            iVar2 = audio_codec_set_gain_ch0(*(int*)(param_1+4), uVar5);
            uVar3 = ((unsigned long)&rodata_f63c1) /*=0xf63c1*/;
            if (iVar2 >= 0) {
                *(volatile unsigned short*)(iVar10+0x1c) = uVar9;
                log_message(((unsigned long)&rodata_f63b1) /*=0xf63b1*/, (unsigned int)(unsigned char)*(volatile unsigned char*)(iVar7+0x1b));
                cVar4 = *(volatile signed char*)(iVar7+0x1b);
                if (cVar4 != 1) cVar4 = 0;
                audio_codec_set_reg16_bit7(iVar7, cVar4);
                uVar5 = (unsigned int)(unsigned char)*(volatile unsigned char*)(iVar7+0x1d);
                log_message(((unsigned long)&rodata_f63e6) /*=0xf63e6*/, uVar5);
                iVar2 = audio_codec_set_reg11_field1(*(int*)(param_1+4), uVar5);
                uVar3 = ((unsigned long)&rodata_f63f9) /*=0xf63f9*/;
                if (iVar2 >= 0) {
                    *(volatile unsigned int*)(iVar8+0x18) = (unsigned int)(*(volatile unsigned short*)(((unsigned long)&rodata_99042) /*=0x99042*/ + (unsigned int)uVar5*2)) * 0x1117;
                    uVar5 = (unsigned int)(unsigned char)*(volatile unsigned char*)(iVar7+0x1c);
                    log_message(((unsigned long)&rodata_f641c) /*=0xf641c*/, uVar5);
                    if (uVar5 < 0xb) {
                        uVar9 = *(volatile unsigned short*)(0x00099066UL + (unsigned int)uVar5*2);
                    } else {
                        uVar9 = 0x1a04;
                    }
                    *(volatile unsigned short*)(iVar8+0x20) = uVar9;
                    iVar2 = audio_codec_set_gain_ch1(*(int*)(param_1+4), uVar5);
                    uVar3 = ((unsigned long)&rodata_f642d) /*=0xf642d*/;
                    if (iVar2 >= 0) {
                        iVar2 = audio_codec_set_reg0x0a_field0(iVar7, 0);
                        uVar3 = ((unsigned long)&rodata_f644e) /*=0xf644e*/;
                        if (iVar2 >= 0) {
                            iVar2 = audio_codec_set_reg12_bit6(iVar7, 1);
                            uVar3 = ((unsigned long)&rodata_f6468) /*=0xf6468*/;
                            if (iVar2 >= 0) {
                                return 0;
                            }
                        }
                        goto control_label_622bc;
                    }
                }
            }
        }
    } else {
        uVar3 = ((unsigned long)&rodata_f62e6) /*=0xf62e6*/;
    }
    log_message(uVar3, uVar5);
    goto control_label_622ec;
control_label_622bc:
    log_message(uVar3);
control_label_622ec:
    log_message(((unsigned long)&rodata_f6481) /*=0xf6481*/);
    return 0;
}
