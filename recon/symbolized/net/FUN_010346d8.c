#include "g1_net_symbols.h"
#include "../../headers/g1_nrf_regs.h"
/* readable reconstruction; identity: FUN_010346d8 @ 0x010346d8
 * public-name: FUN_010346d8
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_sdc_res_pool_slot_tbl                  @ 0x210006a8
 *   g_net_conn_teardown_ctx_b                @ 0x2100071c
 */
/* net-core FUN_010346d8 @ 0x10346d8  (parity 300 trials PROVEN) */
typedef unsigned char byte;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long long ulonglong;
typedef unsigned char undefined1;
typedef unsigned short undefined2;
typedef unsigned int undefined4;
typedef unsigned long long undefined8;

extern undefined8 FUN_01034328(int,int,int,int);
extern undefined8 FUN_010344a8(void);
extern undefined8 FUN_01034508(uint,undefined4);
extern void FUN_01034578(uint);
extern uint FUN_0103a90e(uint);
extern void FUN_0103a924(uint,int,int,int,int,int,byte*);

#define TBL   ((volatile int*)((unsigned long)&g_sdc_res_pool_slot_tbl) /*=0x210006a8*/)
#define TBLH  ((volatile ushort*)((unsigned long)&g_sdc_res_pool_slot_tbl) /*=0x210006a8*/)
#define BASE2 ((unsigned long)&g_net_conn_teardown_ctx_b) /*=0x2100071c*/
#define ERR4  0x0bad0004u
#define OKV   0x0bad0000u

int FUN_010346d8(uint param_1, uint param_2, byte *param_3, int *param_4)
{
    uint uVar6 = param_1;
    byte *pbVar13 = param_3;
    undefined4 uStack_1c = (undefined4)(unsigned long)param_4;
    int iVar5, iVar9, iVar11, iVar7;
    undefined8 uVar12;
    ushort uVar8;
    byte bVar1, bVar2;
    unsigned char sb[4]; /* stack scratch mirroring &uStack_1c bytes, LE bytes of param_4 ptr */
    {
        unsigned int p4 = (unsigned int)(unsigned long)param_4;
        sb[0] = (unsigned char)p4; sb[1] = (unsigned char)(p4>>8);
        sb[2] = (unsigned char)(p4>>16); sb[3] = (unsigned char)(p4>>24);
    }

    uVar12 = FUN_010344a8();
    iVar9 = (int)(uVar12 >> 32);
    iVar5 = (int)uVar12;
    if (iVar9 != 0) {
        uVar6 = FUN_0103a90e(param_1);
        if (uVar6 != 0) {
            return (int)ERR4;
        }
        sb[2] = 0; sb[3] = 0;
        param_2 = uVar6;
        FUN_0103a924(param_1, (int)(unsigned long)(sb+2), (int)(unsigned long)(sb+3), iVar9, 0, 0, pbVar13);
        TBLH[iVar5+8] = (TBLH[iVar5+8] & 0xfffd) | 1;
    }
    if (param_3 != (byte*)0) {
        bVar1 = *param_3;
        uint uVar10 = (uint)bVar1;
        uVar12 = FUN_01034508(param_1, *(undefined4*)(param_3+4));
        iVar9 = (int)(uVar12 >> 32);
        if ((int)uVar12 == 0) {
            iVar11 = iVar5 + 8;
            uVar8 = TBLH[iVar11] & 0x1fdf;
            TBLH[iVar11] = uVar8;
            if (iVar9 != 0) {
                if (3 < uVar10) {
                    return (int)ERR4;
                }
                bVar2 = **(byte**)(param_3+4);
                iVar9 = (uint)bVar2 * 4;
                if (uVar10 == 0) {
                    *(volatile undefined4*)(iVar9 + (G1_NRF_GPIOTE_NS_BASE + 0x510)) = 0;
                    *(volatile undefined4*)(iVar9 + (G1_NRF_GPIOTE_NS_BASE + 0x510)) = 0;
                } else {
                    volatile uint *reg = (volatile uint*)(iVar9 + (G1_NRF_GPIOTE_NS_BASE + 0x510));
                    *reg = *reg & 0xfffffffc;
                    *reg = *reg & 0xfffcc0ff;
                    *reg = (param_1 & 0x3f) << 8 | *reg | uVar10 << 0x10;
                    TBLH[iVar11] = uVar8 | (ushort)bVar2 << 0xd | 0x20;
                }
            }
        } else if (iVar9 != 0) {
            return (int)ERR4;
        }
        TBLH[iVar5+8] = (TBLH[iVar5+8] & 0xffe3) | (ushort)bVar1 << 2;
    }
    if (param_4 != (int*)0) {
        iVar11 = param_4[0];
        iVar9 = param_4[1];
        FUN_01034578(param_1);
        if (iVar11 != 0) {
            if (iVar11 == TBL[0] && iVar9 == TBL[1]) {
                uVar6 = 0;
            } else {
                iVar7 = (int)FUN_01034328(BASE2, (int)(unsigned long)(sb+3), TBL[0], TBL[1]);
                if ((uint)iVar7 != OKV) {
                    return iVar7;
                }
                uVar6 = (uint)sb[3];
            }
            TBL[uVar6*2+1] = iVar9;
            uVar8 = TBLH[iVar5+8];
            TBL[uVar6*2] = iVar11;
            TBLH[iVar5+8] = uVar8 | (ushort)(uVar6 << 9) | 0x100;
        }
    }
    return (int)OKV;
}
