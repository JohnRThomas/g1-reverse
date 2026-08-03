#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0100d14c @ 0x0100d14c
 * public-name: FUN_0100d14c
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0100d14c @ 0x100d14c  (parity 300 trials PROVEN) */

typedef unsigned char u8;
typedef unsigned short u16;
typedef short i16;
typedef unsigned int u32;
typedef int i32;

extern void FUN_0100d840(u32 a, u32 b, u32 c, u32 d);
extern void FUN_01025a84(u32 a, u32 b, u32 c);

void FUN_0100d14c(i32 param_1, i32 param_2, u32 param_3, u32 param_4)
{
    if (param_2 == 0) {
        FUN_01025a84((u32)param_1, 0, 0x360);
        *(volatile u8 *)(param_1+0x117) = 0x49;
        *(volatile u8 *)(param_1+0xcd) = 1;
        *(volatile u8 *)(param_1+0x119) = 0xc4;
        *(volatile u8 *)(param_1+0x118) = 4;
        *(volatile u8 *)(param_1+0x11a) = 7;
        *(volatile u8 *)(param_1+0x14e) = 0xfe;
        *(volatile u8 *)(param_1+0x11b) = 0;
        *(volatile u8 *)(param_1+0x11c) = 0;
        *(volatile u8 *)(param_1+0x11d) = 0;
        *(volatile u8 *)(param_1+0x116) = 0x2b;
        *(volatile u8 *)(param_1+0xc1) = 0x7f;
        *(volatile u32 *)(param_1+0xb0) = 0xfffce000u;
        *(volatile u8 *)(param_1+0x301) = 0x20;
        return;
    }
    if (param_2 == 1) {
        u32 uVar2 = *(volatile u32 *)(param_1+0x14);
        i32 iVar3;
        *(volatile u32 *)(param_1+0xec) = (0x01c9c37fu + uVar2) / uVar2;
        *(volatile i16 *)(param_1+0xfa) = (i16)((uVar2 * (u32)(*(volatile u16 *)(param_1+0xfa))) / uVar2);
        *(volatile u16 *)(param_1+0xf0) = 3000;
        iVar3 = 0x02625a00 / (i32)uVar2 + 1;
        *(volatile i16 *)(param_1+0xf8) = (i16)(((u32)(*(volatile u16 *)(param_1+0x1e)) * 10000 + (uVar2-1)) / uVar2);
        *(volatile u32 *)(param_1+0xe8) = (uVar2 * (u32)(*(volatile i32 *)(param_1+0xe8))) / uVar2;
        *(volatile i16 *)(param_1+0xfe) = (i16)iVar3;
        *(volatile u16 *)(param_1+0xf6) = 0;
        FUN_0100d840((u32)(param_1+0xcd), (u32)(param_1+0xce), (u32)iVar3, param_4);
        return;
    }
    if (param_2 == 2) {
        u32 uVar2 = *(volatile u32 *)(param_1+0x328);
        *(volatile u16 *)(param_1+0xf6) = 0;
        *(volatile i16 *)(param_1+0xfa) = (i16)(((u32)(*(volatile i32 *)(param_1+0x14)) * (u32)(*(volatile u16 *)(param_1+0xfa))) / uVar2);
        *(volatile i16 *)(param_1+0xf8) = (i16)(((u32)(*(volatile u16 *)(param_1+0x32e)) * 10000 + (uVar2-1)) / uVar2);
        *(volatile u32 *)(param_1+0xe8) = (u32)((*(volatile i32 *)(param_1+0xe8)) * (*(volatile i32 *)(param_1+0x14))) / uVar2;
        *(volatile i16 *)(param_1+0xfe) = (i16)(0x02625a00 / (i32)uVar2) + 1;
        *(volatile u32 *)(param_1+0xec) = ((u32)(*(volatile u16 *)(param_1+0xf0)) * 10000 + (uVar2-1)) / uVar2;
        return;
    }
    if (param_2 != 3) {
        return;
    }
    FUN_0100d840((u32)(param_1+0xcd), (u32)(param_1+0xce), param_3, param_4);
    return;
}
