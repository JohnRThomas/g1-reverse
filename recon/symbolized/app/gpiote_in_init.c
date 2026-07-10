#include "g1_app_symbols.h"
/* named: gpiote_in_init */
/* globals referenced:
//   0x20002bc0  g_gpiote_cb                  
*/
/* Reconstructed gpiote_in_init @ 0x6567c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned uint; typedef unsigned char byte; typedef unsigned short ushort; typedef unsigned long long u64;
extern long long nrfx_flag32_alloc(int,...);
extern long long get_pin_idx(int,...);
extern long long pin_is_output(int,...);
extern int gpiote_channel_release_if_unshared(int,...);
extern int gpio_pin_check_output_available(int,...);
extern int gpio_pin_cnf_build_fields(int,...);

int gpiote_in_init(uint param_1, uint param_2, byte *param_3, int *param_4)
{
    byte bVar1,bVar2; uint uVar3; int iVar5; uint uVar6; int iVar7; ushort uVar8; int iVar9; uint uVar10; int iVar11;
    long long uVar12; byte *pbVar13; unsigned uStack_1c;
    uVar6 = param_1;
    pbVar13 = param_3;
    uStack_1c = (unsigned)param_4;
    uVar12 = get_pin_idx(0);
    iVar9 = (int)((u64)uVar12 >> 0x20);
    iVar5 = (int)uVar12;
    if(iVar9 != 0){
        uVar6 = gpio_pin_check_output_available(param_1);
        if(uVar6 != 0) return 0x0bad0004;
        uVar3 = uStack_1c & 0xffffff;
        uStack_1c = uVar3 & ((uintptr_t)&tbl_ffc8) /*=0xffff*/;
        param_2 = uVar6;
        gpio_pin_cnf_build_fields(param_1, (int)&uStack_1c + 2, (int)&uStack_1c + 3, iVar9, 0, 0, pbVar13);
        *(volatile ushort*)(((uintptr_t)&g_gpiote_cb) /*=0x20002bc0*/ + (iVar5+8)*2) = (*(volatile ushort*)(((uintptr_t)&g_gpiote_cb) /*=0x20002bc0*/ + (iVar5+8)*2) & ((uintptr_t)&tbl_ffc8) /*=0xfffd*/) | 1;
    }
    if(param_3 != 0){
        bVar1 = *param_3;
        uVar10 = (uint)bVar1;
        uVar12 = pin_is_output(param_1, *(unsigned*)(param_3+4));
        iVar9 = (int)((u64)uVar12 >> 0x20);
        if((int)uVar12 == 0){
            iVar11 = iVar5 + 8;
            uVar8 = *(volatile ushort*)(((uintptr_t)&g_gpiote_cb) /*=0x20002bc0*/ + iVar11*2) & 0x1fdf;
            *(volatile ushort*)(((uintptr_t)&g_gpiote_cb) /*=0x20002bc0*/ + iVar11*2) = uVar8;
            if(iVar9 != 0){
                if(3 < uVar10) return 0x0bad0004;
                bVar2 = **(byte**)(param_3+4);
                iVar9 = (uint)bVar2 * 4;
                if(uVar10 == 0){
                    *(unsigned*)(iVar9 + REG_5000d510 /*=0x5000d510*/) = 0;
                    *(unsigned*)(iVar9 + REG_5000d510 /*=0x5000d510*/) = 0;
                } else {
                    *(uint*)(iVar9+REG_5000d510 /*=0x5000d510*/) = *(uint*)(iVar9+REG_5000d510 /*=0x5000d510*/) & 0xfffffffc;
                    *(uint*)(iVar9+REG_5000d510 /*=0x5000d510*/) = *(uint*)(iVar9+REG_5000d510 /*=0x5000d510*/) & 0xfffcc0ff;
                    *(uint*)(iVar9+REG_5000d510 /*=0x5000d510*/) = ((param_1 & 0x3f) << 8) | *(uint*)(iVar9+REG_5000d510 /*=0x5000d510*/) | (uVar10 << 0x10);
                    *(volatile ushort*)(((uintptr_t)&g_gpiote_cb) /*=0x20002bc0*/ + iVar11*2) = uVar8 | ((ushort)bVar2 << 0xd) | 0x20;
                }
            }
        } else if(iVar9 != 0){
            return 0x0bad0004;
        }
        *(volatile ushort*)(((uintptr_t)&g_gpiote_cb) /*=0x20002bc0*/ + (iVar5+8)*2) = (*(volatile ushort*)(((uintptr_t)&g_gpiote_cb) /*=0x20002bc0*/ + (iVar5+8)*2) & ((uintptr_t)&tbl_ffc8) /*=0xffe3*/) | ((ushort)bVar1 << 2);
    }
    if(param_4 != 0){
        iVar11 = *param_4;
        iVar9 = param_4[1];
        gpiote_channel_release_if_unshared(param_1);
        if(iVar11 != 0){
            if(iVar11 == *(volatile int*)((uintptr_t)&g_gpiote_cb) /*=0x20002bc0*/ && iVar9 == *(volatile int*)((uintptr_t)&g_gpiote_cb_evt) /*=0x20002bc4*/){
                uVar6 = 0;
            } else {
                iVar7 = nrfx_flag32_alloc(((uintptr_t)&g_nrfx_gpiote_channels_mask) /*=0x20002c34*/, (int)&uStack_1c + 3, *(volatile int*)((uintptr_t)&g_gpiote_cb) /*=0x20002bc0*/, *(volatile int*)((uintptr_t)&g_gpiote_cb_evt) /*=0x20002bc4*/, uVar6, param_2);
                if(iVar7 != 0x0bad0000) return iVar7;
                uVar6 = (uint)uStack_1c >> 0x18;
            }
            *(volatile int*)(((uintptr_t)&g_gpiote_cb) /*=0x20002bc0*/ + (uVar6*2 + 1)*4) = iVar9;
            uVar8 = *(volatile ushort*)(((uintptr_t)&g_gpiote_cb) /*=0x20002bc0*/ + (iVar5+8)*2);
            *(volatile int*)(((uintptr_t)&g_gpiote_cb) /*=0x20002bc0*/ + (uVar6*2)*4) = iVar11;
            *(volatile ushort*)(((uintptr_t)&g_gpiote_cb) /*=0x20002bc0*/ + (iVar5+8)*2) = uVar8 | ((ushort)(uVar6 << 9)) | 0x100;
        }
    }
    return 0x0bad0000;
}

