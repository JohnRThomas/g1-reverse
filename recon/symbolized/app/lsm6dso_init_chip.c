#include "g1_app_symbols.h"
/* named: lsm6dso_init_chip */
/* Reconstructed lsm6dso_init_chip @ 0x622a0  (parity: 300/300 trials, PROVEN) */
extern void DEBUG_PRINT(int fmt, ...);
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
    uVar3 = "Failed to set user bank\r\n" /*=0xf6292*/;
    if (iVar2 < 0) goto LAB_622bc;
    iVar2 = audio_codec_read_reg0x0f(iVar7, ((int)&uStack_24) + 2);
    uVar3 = "Failed reading chip id\r\n" /*=0xf62ac*/;
    if (iVar2 < 0) goto LAB_622bc;

    DEBUG_PRINT("lsm6dso_init_chip chip id 0x%x\r\n" /*=0xf62c5*/, (param_2 >> 0x10) & 0xff);
    uVar5 = (param_2 >> 0x10) & 0xff;
    uVar3 = "Invalid chip id 0x%x\r\n" /*=0xf62e6*/;
    if (uVar5 == 0x6c) {
        iVar2 = audio_codec_set_reg18_and_reg62(iVar7, 0x80);
        uVar3 = "Failed to disable I3C\r\n" /*=0xf62fd*/;
        if (iVar2 < 0) goto LAB_622bc;
        iVar2 = audio_codec_get_reg14_bit2(iVar7, ((int)&uStack_24) + 3);
        uVar3 = "Failed to get I2C_MASTER status\r\n" /*=0xf6315*/;
        if (iVar2 < 0) goto LAB_622bc;
        if (((param_2 >> 0x18) & 0xff) != 0) {
            DEBUG_PRINT("Disable shub before reset\r\n" /*=0xf6337*/);
            audio_codec_set_reg14_bit2(iVar7, 0);
            delay_scaled_busy_wait(300);
        }
        iVar2 = audio_codec_set_reg12_bit0(iVar7, 1);
        if (iVar2 < 0) goto LAB_622ec;
        delay_scaled_busy_wait(100);
        DEBUG_PRINT("accel pm is %d\r\n" /*=0xf6353*/, (unsigned int)(unsigned char)*(volatile unsigned char*)(iVar7+0x18));
        cVar4 = *(volatile signed char*)(iVar7+0x18);
        if ((cVar4 != 1) && (cVar4 != 2)) cVar4 = 0;
        audio_codec_set_dual_reg14_reg15(iVar7, cVar4);
        uVar5 = (*(volatile unsigned char*)(iVar7+0x1a)) & 0x3f;
        DEBUG_PRINT("accel range is %d\r\n" /*=0xf6364*/, uVar5);
        iVar10 = *(int*)(param_1+0x10);
        iVar2 = audio_codec_set_reg10_field2(*(int*)(param_1+4), uVar5);
        uVar3 = "failed to set accelerometer range %d\r\n" /*=0xf6378*/;
        if (iVar2 >= 0) {
            *(volatile unsigned char*)(iVar10+0x1e) = (unsigned char)uVar5;
            uVar3 = "accel odr is %d\r\n" /*=0xf639f*/;
            bVar11 = (*(volatile signed char*)(iVar7+0x1a)) >= 0;
            {
                unsigned short tbl = *(volatile unsigned short*)(((uintptr_t)&tbl_98fbc) /*=0x9905e*/ + (unsigned int)uVar5*2);
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
            DEBUG_PRINT(uVar3, uVar5);
            if (uVar5 > 10) {
                iVar10 = 0x1a04;
            }
            uVar9 = (unsigned short)iVar10;
            if (uVar5 < 0xb) {
                uVar9 = *(volatile unsigned short*)(((uintptr_t)&tbl_98fbc) /*=0x99066*/ + (unsigned int)uVar5*2);
            }
            *(volatile unsigned short*)(iVar8+0x1c) = uVar9;
            iVar10 = *(int*)(param_1+0x10);
            iVar2 = audio_codec_set_gain_ch0(*(int*)(param_1+4), uVar5);
            uVar3 = "failed to set accelerometer odr %d\r\n" /*=0xf63c1*/;
            if (iVar2 >= 0) {
                *(volatile unsigned short*)(iVar10+0x1c) = uVar9;
                DEBUG_PRINT("gyro pm is %d\r\n" /*=0xf63b1*/, (unsigned int)(unsigned char)*(volatile unsigned char*)(iVar7+0x1b));
                cVar4 = *(volatile signed char*)(iVar7+0x1b);
                if (cVar4 != 1) cVar4 = 0;
                audio_codec_set_reg16_bit7(iVar7, cVar4);
                uVar5 = (unsigned int)(unsigned char)*(volatile unsigned char*)(iVar7+0x1d);
                DEBUG_PRINT("gyro range is %d\r\n" /*=0xf63e6*/, uVar5);
                iVar2 = audio_codec_set_reg11_field1(*(int*)(param_1+4), uVar5);
                uVar3 = "failed to set gyroscope range %d\r\n" /*=0xf63f9*/;
                if (iVar2 >= 0) {
                    *(volatile unsigned int*)(iVar8+0x18) = (unsigned int)(*(volatile unsigned short*)(((uintptr_t)&tbl_98fbc) /*=0x99042*/ + (unsigned int)uVar5*2)) * 0x1117;
                    uVar5 = (unsigned int)(unsigned char)*(volatile unsigned char*)(iVar7+0x1c);
                    DEBUG_PRINT("gyro odr is %d\r\n" /*=0xf641c*/, uVar5);
                    if (uVar5 < 0xb) {
                        uVar9 = *(volatile unsigned short*)(((uintptr_t)&tbl_98fbc) /*=0x99066*/ + (unsigned int)uVar5*2);
                    } else {
                        uVar9 = 0x1a04;
                    }
                    *(volatile unsigned short*)(iVar8+0x20) = uVar9;
                    iVar2 = audio_codec_set_gain_ch1(*(int*)(param_1+4), uVar5);
                    uVar3 = "failed to set gyroscope odr %d\r\n" /*=0xf642d*/;
                    if (iVar2 >= 0) {
                        iVar2 = audio_codec_set_reg0x0a_field0(iVar7, 0);
                        uVar3 = "failed to set FIFO mode\r\n" /*=0xf644e*/;
                        if (iVar2 >= 0) {
                            iVar2 = audio_codec_set_reg12_bit6(iVar7, 1);
                            uVar3 = "failed to set BDU mode\r\n" /*=0xf6468*/;
                            if (iVar2 >= 0) {
                                return 0;
                            }
                        }
                        goto LAB_622bc;
                    }
                }
            }
        }
    } else {
        uVar3 = "Invalid chip id 0x%x\r\n" /*=0xf62e6*/;
    }
    DEBUG_PRINT(uVar3, uVar5);
    goto LAB_622ec;
LAB_622bc:
    DEBUG_PRINT(uVar3);
LAB_622ec:
    DEBUG_PRINT("failed to initialize chip\r\n" /*=0xf6481*/);
    return 0;
}

