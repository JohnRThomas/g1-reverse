#include "g1_net_symbols.h"
/* net-core FUN_01008e74 @ 0x1008e74  (parity 300 trials PROVEN) */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int i32;

extern i32 FUN_01008a58(u32 a, u32 b);
extern void FUN_0101fbbc(void);

#define DAT ((uintptr_t)&g_net_layout_count_table) /*=0x21000a30*/
#define DAT2 ((uintptr_t)&g_net_mac_pib_ext) /*=0x21000a40*/

i32 FUN_01008e74(i32 param_1, i32 param_2, u16 *param_3)
{
    u8 *pbVar2 = (u8*)DAT;
    i32 iVar3;
    u16 uVar1;

    if (param_1 != 0) {
        return -0x2d;
    }
    if (*(volatile u8*)(DAT+0x2c) != 0) {
        return -1;
    }
    if (param_2 == 0) goto tail;
    if (param_3 == 0) {
        iVar3 = -0x16;
        return iVar3;
    }
    switch (param_2) {
    case 1:
        *(volatile u8*)(DAT+0) = (u8)*param_3;
        break;
    case 2:
        *(volatile u8*)(DAT+1) = (u8)*param_3;
        break;
    case 3:
        if ( (((u8)((u8*)param_3)[2] == 0) || (((u8*)param_3)[3] == 0)) ||
             ((u8)*param_3 < 0x1b) || (((u8*)param_3)[1] < 0x1b) ) {
            iVar3 = -0x16; return iVar3;
        }
        *(volatile u32*)(DAT+5) = *(volatile u32*)param_3;
        break;
    case 4:
        if ((u8)*param_3 < *(volatile u8*)(DAT+3)) { iVar3=-0x16; return iVar3; }
        *(volatile u8*)(DAT+2) = (u8)*param_3;
        break;
    case 5:
        if ((*(volatile u8*)(DAT+0x1f) != 0) && ((u8)*param_3 < 2)) { iVar3=-0x16; return iVar3; }
        *(volatile u8*)(DAT+9) = (u8)*param_3;
        break;
    case 6:
        *(volatile u16*)(DAT+10) = *param_3;
        break;
    case 7:
        if (0xff < *param_3) { iVar3=-0x16; return iVar3; }
        *(volatile u8*)(DAT+0xc) = (u8)*param_3;
        break;
    case 8:
        if (*(volatile u8*)(DAT+2) < (u8)*param_3) { iVar3=-0x16; return iVar3; }
        *(volatile u8*)(DAT+3) = (u8)*param_3;
        break;
    case 9:
        *(volatile u8*)(DAT+4) = (u8)*param_3;
        break;
    case 10:
        if (*(volatile u8*)(DAT+0x1e) == 0) {
            if (1 < (u8)*param_3) {
                *(volatile u8*)(DAT+0xd) = (u8)*param_3;
                break;
            }
        } else if ((u8)*param_3 != 0) {
            *(volatile u8*)(DAT+0xd) = (u8)*param_3;
            break;
        }
        iVar3 = -0x16; return iVar3;
    case 0xb:
        if (8 < (u8)*param_3) { iVar3=-0x16; return iVar3; }
        *(volatile u8*)(DAT+0xe) = (u8)*param_3;
        break;
    case 0xc:
        if (*(volatile u8*)(DAT+2) < (u8)*param_3) { iVar3=-0x16; return iVar3; }
        *(volatile u8*)(DAT+0xf) = (u8)*param_3;
        break;
    case 0xd:
        if (((u8)*param_3 == 0) || (0xf8 < (u8)(((u8*)param_3)[1] - 1))) { iVar3=-0x16; return iVar3; }
        uVar1 = param_3[1];
        *(volatile u16*)(DAT+0x10) = *param_3;
        *(volatile u8*)(DAT2+2) = (u8)uVar1;
        break;
    case 0xe:
        *(volatile u8*)(DAT+0x13) = (u8)*param_3;
        FUN_0101fbbc();
        break;
    case 0xf:
        if ((u8)*param_3 == 0) { iVar3=-0x16; return iVar3; }
        *(volatile u8*)(DAT+0x14) = (u8)*param_3;
        break;
    case 0x10:
        *(volatile u8*)(DAT+0x15) = (u8)*param_3;
        break;
    case 0x11:
        if (0xe < (u8)*param_3) { iVar3=-0x16; return iVar3; }
        *(volatile u8*)(DAT+0x16) = (u8)*param_3;
        break;
    case 0x12:
        *(volatile u8*)(DAT+0x17) = (u8)*param_3;
        break;
    case 0x13:
        *(volatile u8*)(DAT+0x18) = (u8)*param_3;
        break;
    case 0x14:
        *(volatile u8*)(DAT+0x19) = (u8)*param_3;
        break;
    case 0x15:
        *(volatile u8*)(DAT+0x1a) = (u8)*param_3;
        break;
    case 0x16:
        *(volatile u16*)(DAT+0x1b) = *param_3;
        break;
    default:
        return -0x2d;
    }
tail:
    iVar3 = FUN_01008a58(0, 1);
    if (iVar3 < 0x10000) {
        pbVar2[0x2d] = 1;
    } else {
        iVar3 = -0xc;
    }
    return iVar3;
}


