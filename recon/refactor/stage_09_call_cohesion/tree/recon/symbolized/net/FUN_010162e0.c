#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_010162e0 @ 0x010162e0
 * public-name: FUN_010162e0
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_sdc_ll_ctx_param                       @ 0x21001019
 */
/* net-core FUN_010162e0 @ 0x10162e0  (parity 300 trials PROVEN) */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int i32;

struct packed_u32 { u32 value; } __attribute__((packed));
_Static_assert(sizeof(struct packed_u32) == 4, "packed u32 layout");

static inline u32 load_packed_u32(const volatile void *address)
{
    return ((const volatile struct packed_u32 *)address)->value;
}

static inline void store_packed_u32(volatile void *address, u32 value)
{
    ((volatile struct packed_u32 *)address)->value = value;
}

extern void* FUN_0100cbbc(u32 a);
extern u32 FUN_0100d5d0(u32 a);
extern u32 FUN_0100d64c(u32 a, u32 b);
extern u32 FUN_0100d688(u32 a, u32 b);
extern void FUN_0100dfbc(u32 a, u32 b, u32 c, u32 d, u32 e);
extern void FUN_0100e008(u32 a, u32 *b);
extern void FUN_0100e028(u32 a, u32 b);
extern void FUN_0100e038(u32 a, u32 b);
extern void FUN_0100e054(u32 a, u32 b);
extern u32 FUN_0101f924(void);
extern void FUN_01020764(u32 a);

#define DAT G1N_21000f90
#define DAT2 ((unsigned long)&g_sdc_ll_ctx_param) /*=0x21001019*/
#define DAT3 G1N_21000fd6

void FUN_010162e0(i32 param_1, u32 param_2, u32 param_3, u32 param_4)
{
    i32 iVar2 = DAT;
    u16 *puVar5 = *(volatile u16**)(DAT+0xc0);
    u32 uVar3;
    u32 *puVar9;
    *puVar5 = 0;
    if (param_1 == 3) {
        FUN_0100dfbc((u32)puVar5, 3, param_3, 0, param_4);
        puVar5 = *(volatile u16**)(iVar2+0xc0);
    } else if (param_1 == 5) {
        i32 iVar10, iVar7;
        u32 uVar8, uVar4;
        FUN_0100dfbc((u32)puVar5, 5, param_3, 0, param_4);
        iVar10 = *(volatile i32 *)(iVar2+0xc0);
        store_packed_u32((volatile void *)(iVar10 + 0xf),
                         *(volatile u32 *)(*(volatile i32 *)(iVar2+0x50)+0x18));
        iVar7 = *(volatile i32 *)(iVar2+0x50);
        uVar8 = *(volatile u32 *)(iVar7+0x20);
        *(volatile u8 *)(iVar10+0x13) = (u8)uVar8;
        *(volatile u8 *)(iVar10+0x14) = (u8)(uVar8 >> 8);
        *(volatile u8 *)(iVar10+0x15) = (u8)(uVar8 >> 0x10);
        uVar3 = FUN_0100d64c(*(volatile u16 *)(iVar7+0x28), *(volatile u32 *)(iVar7+0x14));
        *(volatile u8 *)(iVar10+0x16) = (u8)uVar3;
        iVar10 = *(volatile i32 *)(iVar2+0xc0);
        uVar4 = FUN_0100d688(*(volatile u32 *)(*(volatile i32 *)(iVar2+0x50)+0x24), *(volatile u32 *)(*(volatile i32 *)(iVar2+0x50)+0x14));
        *(volatile u8 *)(iVar10+0x17) = (u8)uVar4;
        iVar7 = *(volatile i32 *)(iVar2+0xc0);
        *(volatile u8 *)(iVar7+0x18) = (u8)(uVar4 >> 8);
        uVar4 = FUN_0100d5d0(*(volatile u32 *)(*(volatile i32 *)(iVar2+0x50)+0x14));
        *(volatile u8 *)(iVar7+0x19) = (u8)uVar4;
        *(volatile u8 *)(iVar7+0x1a) = (u8)(uVar4 >> 8);
        iVar7 = *(volatile i32 *)(iVar2+0x50);
        iVar10 = *(volatile i32 *)(iVar2+0xc0);
        uVar4 = *(volatile u16 *)(iVar7+0x1c);
        *(volatile u8 *)(iVar10+0x1b) = (u8)uVar4;
        *(volatile u8 *)(iVar10+0x1c) = (u8)(uVar4 >> 8);
        uVar4 = *(volatile u16 *)(iVar7+0x1e);
        *(volatile u8 *)(iVar10+0x1d) = (u8)uVar4;
        *(volatile u8 *)(iVar10+0x1e) = (u8)(uVar4 >> 8);
        store_packed_u32((volatile void *)(iVar10 + 0x1f),
                         load_packed_u32((volatile void *)(iVar7 + 0xce)));
        *(volatile u8 *)(iVar10+0x23) = *(volatile u8 *)(iVar7+0xd2);
        *(volatile u8 *)(iVar10+0x24) = (*(volatile u8 *)(*(volatile i32 *)(iVar2+0x50)+0xd9) & 0x1f) | (*(volatile u8 *)(iVar10+0x24) & 0xe0);
        {
            u32 r0v = FUN_0101f924();
            puVar5 = *(volatile u16**)(iVar2+0xc0);
            *(volatile u8 *)(iVar10+0x24) = (*(volatile u8 *)(iVar10+0x24) & 0x1f) | (u8)(r0v << 5);
        }
    }
    FUN_0100e028((u32)puVar5, DAT2);
    FUN_0100e054(*(volatile u32 *)(iVar2+0xc0), *(volatile u8 *)(iVar2+0x90));
    uVar3 = *(volatile u8 *)(iVar2+0x45);
    puVar9 = (u32 *)DAT3;
    if (*(volatile char *)(iVar2+0x7d) != 0) {
        u8 uVar1;
        void *puVar6;
        if ((*(volatile char *)(iVar2+0x54) == 3) && (*(volatile char *)(iVar2+0x4d) != 0)) {
            uVar1 = *(volatile u8 *)(iVar2+0x7b);
        } else {
            uVar1 = *(volatile u8 *)(iVar2+0x78);
        }
        puVar6 = FUN_0100cbbc(uVar1);
        puVar9 = (u32 *)DAT3;
        if (puVar6 != 0) {
            uVar3 = 1;
            puVar9 = (u32*)puVar6;
        }
    }
    FUN_0100e008(*(volatile u32 *)(iVar2+0xc0), puVar9);
    FUN_0100e038(*(volatile u32 *)(iVar2+0xc0), uVar3);
    FUN_01020764(*(volatile u32 *)(iVar2+0xc0));
    if (param_1 == 5) {
        i32 iVar7 = *(volatile i32 *)(iVar2+0x50);
        store_packed_u32((volatile void *)(iVar7 + 10),
                         load_packed_u32((volatile void *)puVar9));
        *(volatile u16 *)(iVar7+0xe) = *(volatile u16 *)((u8*)puVar9+4);
        *(volatile u8 *)(*(volatile i32 *)(iVar2+0x50)+9) = (u8)uVar3;
        return;
    }
    return;
}
