#include "g1_net_symbols.h"
/* net-core FUN_01031a68 @ 0x1031a68  (parity 300 trials PROVEN) */
#include <stdint.h>

extern void FUN_01036bec(unsigned int a, unsigned int b);
extern void FUN_01032680(void);
extern void FUN_01009054(void *a);
extern void FUN_0102e284(unsigned int a, unsigned int b, void *c, void *d);
extern int FUN_0103b0f0(unsigned int a);
extern int FUN_010091e8(void *a);
extern int FUN_01031804(unsigned int a, unsigned int b);
extern int FUN_010091cc(unsigned int a);
extern int FUN_01008fd4(unsigned int a, unsigned int b);
extern int thunk_FUN_0101f650(void *a);
extern void FUN_01031814(void);

#define DAT_b50 ((uintptr_t)&rodata_103af63) /*=0x103af63*/
#define DAT_b54 ((uintptr_t)&g_net_config_record_copy_dst) /*=0x21004974*/
#define DAT_b58 "andom@41009000" /*=0x103d73e*/
#define DAT_b5c "l/kheap.c" /*=0x103e216*/
#define DAT_b60 0x01000003u
#define DAT_b64 0x01401cc0u
#define DAT_b68 ((uintptr_t)&rodata_103c044) /*=0x103c044*/
#define DAT_b6c ((uintptr_t)&rodata_103bf70) /*=0x103bf70*/
#define DAT_b70 "_slab.c" /*=0x103e23d*/
#define DAT_b74 ((uintptr_t)&rodata_103c11c) /*=0x103c11c*/
#define DAT_b78 "l/thread.c" /*=0x103e25d*/
#define DAT_b7c ((uintptr_t)&g_net_sdc_mempool_buf) /*=0x21002b90*/
#define DAT_b80 ((uintptr_t)&rodata_10320d9) /*=0x10320d9*/
#define DAT_b84 0x003d0900u

int FUN_01031a68(void)
{
    int iVar1, iVar2;
    unsigned int local_50, local_4c;
    int local_48;
    unsigned short local_44;
    unsigned int local_40;
    unsigned char auStack_3c[20];
    unsigned int local_28[3];

    FUN_01036bec(DAT_b54, DAT_b50);
    FUN_01032680();
    FUN_01009054(auStack_3c);

    local_4c = DAT_b58;
    local_48 = (int)DAT_b5c;
    local_44 = 0x200;
    local_50 = DAT_b60;
    FUN_0102e284(DAT_b68, DAT_b64, &local_50, auStack_3c);

    iVar1 = FUN_0103b0f0(DAT_b6c);
    if (iVar1 == 0) {
        unsigned int loc18 = 2;
        unsigned int loc14 = DAT_b70;
        struct { unsigned int a; unsigned int b; } s = { loc18, loc14 };
        FUN_0102e284(DAT_b68, 0x1040, &s, 0);
        return -0x13;
    }

    {
        unsigned int *src = (unsigned int *)DAT_b74;
        local_28[0] = src[0];
        local_28[1] = src[1];
        local_28[2] = src[2];
    }
    iVar1 = FUN_010091e8(local_28);
    if (iVar1 != 0) {
        struct { unsigned int a; int b; unsigned int c; } s;
        s.a = 3;
        s.b = iVar1;
        s.c = DAT_b78;
        FUN_0102e284(DAT_b68, 0x1840, &s, 0);
        return -0x16;
    }

    iVar1 = FUN_01031804(0xffffffffu, 0xffffffffu);
    if (iVar1 != 0) {
        return iVar1;
    }

    iVar1 = FUN_010091cc(3);
    if (iVar1 == 0) {
        iVar1 = FUN_01008fd4(DAT_b80, DAT_b7c);
        if (iVar1 == 0) {
            local_40 = DAT_b84;
            iVar2 = thunk_FUN_0101f650(&local_40);
            if (iVar2 != 0) {
                goto LAB_b24;
            }
        }
        FUN_01031814();
    } else {
    LAB_b24:
        FUN_01031814();
        iVar1 = -0x86;
    }
    return iVar1;
}

