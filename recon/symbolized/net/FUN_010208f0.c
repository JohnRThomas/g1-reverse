#include "g1_net_symbols.h"
/* net-core FUN_010208f0 @ 0x10208f0  (parity 300 trials PROVEN) */

typedef unsigned int uint;
extern void FUN_01008d00(unsigned int,unsigned int) __attribute__((noreturn));
extern void FUN_010215a8(int);
extern void FUN_010216d4(unsigned int,unsigned int,int,void*);
extern int FUN_010218fc(void*);
extern void FUN_01025c9c(void*);

typedef struct {
    signed char b0;
    unsigned char b1;
    unsigned char b2;
    unsigned char b3;
    unsigned int w2;
    unsigned int reserved[3];
} callblk_t;

void FUN_010208f0(unsigned char param_1, int param_2, unsigned int param_3_raw)
{
    unsigned char param_3 = (unsigned char)param_3_raw;
    volatile unsigned char * const iVar1 = (volatile unsigned char *)0x210015f0; /* DAT_010209a8 */
    iVar1[7] = param_1;
    iVar1[10] = param_3;
    unsigned int uVar3;
    callblk_t blk;

    if (param_2 == 0) {
        iVar1[8] = 1;
        if (iVar1[9] == 2) {
            FUN_010216d4((unsigned int)param_3, iVar1[0x1a],
                         (int)(signed char)iVar1[0x19], &blk.b0);
            FUN_010215a8((int)blk.b0);
            int iVar2 = FUN_010218fc(&blk.b1);
            if (iVar2 != 0) {
                FUN_01008d00(0x3e, 0x57e);
            }
            volatile unsigned int * const p9b4 = (volatile unsigned int *)REG_41008000 /*=0x41008000*/; /* DAT_010209b4 */
            p9b4[0x200/4] = p9b4[0x200/4] | 0x110;
            goto lab_948;
        }
        uVar3 = iVar1[0x18];
    } else {
        iVar1[8] = 2;
lab_948:
        uVar3 = iVar1[0x18];
        if (iVar1[9] == 2) {
            volatile unsigned int * const p9ac = (volatile unsigned int *)((unsigned long)&rodata_103c4d0) /*=0x103c4d0*/; /* DAT_010209ac */
            const unsigned long long dat9b0 = 0x10624dd3ull; /* DAT_010209b0 */
            unsigned short u16v = *(volatile unsigned short*)(iVar1 + 0x1c);
            int base = *(volatile int*)((unsigned char*)p9ac + uVar3 * 4 + 0x70) + 999;
            blk.w2 = (unsigned int)((int)u16v - (int)(unsigned int)((dat9b0 * (unsigned long long)(unsigned int)base) >> 0x26));
            goto lab_926;
        }
    }
    {
        volatile unsigned short * const p9ac2 = (volatile unsigned short *)((unsigned long)&rodata_103c4d0) /*=0x103c4d0*/; /* DAT_010209ac halfword view */
        const unsigned long long dat9b0 = 0x10624dd3ull;
        unsigned short u16v = *(volatile unsigned short*)(iVar1 + 0x1c);
        unsigned short base = *(volatile unsigned short*)((unsigned char*)p9ac2 + uVar3 * 2 + 0x94) + 999;
        blk.w2 = (unsigned int)((int)u16v + (int)(unsigned int)((dat9b0 * (unsigned long long)base) >> 0x26));
    }
lab_926:
    ;
    blk.b1 = (param_2 == 0);
    blk.b0 = 1;
    FUN_01025c9c(&blk);
}
