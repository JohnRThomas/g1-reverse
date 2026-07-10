#include "g1_net_symbols.h"
/* net-core FUN_010098d8 @ 0x10098d8  (parity 300 trials PROVEN) */
extern void FUN_01008d00(unsigned int a0, unsigned int a1);
extern void FUN_01009668(int *a0);
extern void FUN_01009708(unsigned int a0, void *a1);
extern void FUN_01009874(void);
extern int FUN_010098d8(int param_1, unsigned char *param_2);
extern unsigned short FUN_0101fba4(void);

typedef struct { unsigned int p0; unsigned short v4; unsigned char c6; unsigned char c7; unsigned char c8; unsigned char pad[3]; } Rec12;

int FUN_010098d8(int param_1, unsigned char *param_2)
{
    int iVar2;
    int *piVar3;
    Rec12 rec;
    int local_10;
    char local_9;

    if (0xff < (unsigned int)param_2[1] + (unsigned int)param_2[2]) {
        FUN_01008d00(0x17, 0x15b);
    }
    if (param_2[1] < *param_2) {
        FUN_01008d00(0x17, 0x15f);
    }
    iVar2 = param_1;
    if (param_1 == 0) iVar2 = 1;
    local_9 = (char)iVar2;
    if (param_1 != 0) local_9 = 0;
    local_10 = param_1;
    if ((local_9 != 1) && (*(volatile unsigned char *)((uintptr_t)&g_net_bump_alloc_state) /*=0x21000ba8*/ != 2)) {
        FUN_010098d8(0, param_2);
    }
    if (local_9 == 0) piVar3 = &local_10; else piVar3 = (int *)0;
    FUN_01009668(piVar3);

    rec.p0 = ((uintptr_t)&rodata_101e0e9) /*=0x101e0e9*/; rec.v4 = 0x360; rec.c6 = 8; rec.c7 = param_2[1]; rec.c8 = 0;
    FUN_01009708(0, &rec);
    rec.p0 = ((uintptr_t)&rodata_1016591) /*=0x1016591*/; rec.v4 = 0x3f0; rec.c6 = 8; rec.c7 = param_2[2]; rec.c8 = 0;
    FUN_01009708(1, &rec);
    rec.p0 = ((uintptr_t)&rodata_1012a5d) /*=0x1012a5d*/; rec.v4 = 0x150; rec.c6 = 8; rec.c7 = param_2[3]; rec.c8 = 0xff;
    FUN_01009708(2, &rec);
    rec.p0 = ((uintptr_t)&rodata_102a2c1) /*=0x102a2c1*/; rec.v4 = 0x90; rec.c6 = 8; rec.c7 = param_2[4]; rec.c8 = 0xff;
    FUN_01009708(3, &rec);
    rec.p0 = ((uintptr_t)&rodata_10203c9) /*=0x10203c9*/; rec.v4 = 0xa8; rec.c6 = 8; rec.c7 = param_2[5]; rec.c8 = 1;
    FUN_01009708(4, &rec);
    rec.p0 = ((uintptr_t)&rodata_102a3b5) /*=0x102a3b5*/; rec.v4 = 0; rec.c6 = 8; rec.c7 = param_2[6]; rec.c8 = 0xff;
    if (param_2[6] != 0) {
        rec.v4 = FUN_0101fba4();
    }
    FUN_01009708(5, &rec);
    rec.p0 = ((uintptr_t)&rodata_102a3b9) /*=0x102a3b9*/; rec.v4 = 0x80; rec.c6 = 8; rec.c7 = param_2[7]; rec.c8 = 0xff;
    FUN_01009708(6, &rec);
    rec.p0 = ((uintptr_t)&rodata_101e90d) /*=0x101e90d*/; rec.v4 = 0x78; rec.c6 = 8; rec.c7 = param_2[8]; rec.c8 = 2;
    FUN_01009708(7, &rec);
    rec.p0 = ((uintptr_t)&rodata_101e879) /*=0x101e879*/; rec.v4 = 0x1f0; rec.c6 = 8; rec.c7 = param_2[9]; rec.c8 = 0;
    FUN_01009708(8, &rec);
    rec.p0 = ((uintptr_t)&rodata_101e961) /*=0x101e961*/; rec.v4 = 0x120; rec.c6 = 8; rec.c7 = param_2[10]; rec.c8 = 0xff;
    FUN_01009708(9, &rec);
    rec.p0 = ((uintptr_t)&rodata_101e9e1) /*=0x101e9e1*/; rec.v4 = 0x100; rec.c6 = 8; rec.c7 = param_2[11]; rec.c8 = 0;
    FUN_01009708(10, &rec);

    FUN_01009874();
    return *(volatile int *)((uintptr_t)&g_net_bump_alloc_cursor) /*=0x21000bac*/ - param_1;
}

