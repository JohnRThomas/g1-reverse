#include "g1_net_symbols.h"
/* net-core FUN_01030a50 @ 0x1030a50  (parity 300 trials PROVEN) */
extern int FUN_0103494c(unsigned int, void*, unsigned int, unsigned int, int);
extern int FUN_01034a28(unsigned int);
extern void FUN_01034b64(unsigned int);
extern int FUN_010346d8(unsigned int, void*, void*, unsigned int);
extern int FUN_01034840(unsigned int, void*, int);
extern void FUN_01039bbe(int,int,int);
extern void FUN_01039bb0(int,int);

#define BAD 0x0bad0000u
#define STRA ((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/
#define STRB ((unsigned long)&rodata_103dfbc) /*=0x103dfbc*/

unsigned int FUN_01030a50(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    struct {
        unsigned int saved_param2;
        unsigned int local20;
        unsigned int saved_param4;
    } locals = { param_2, param_3, param_4 };
    unsigned char *local20_bytes = (unsigned char *)&locals.local20;
    unsigned int ret;

    int iVar9 = *(volatile int*)(param_1+4);
    unsigned int uVar8 = (param_2 & 0x1f) | ((unsigned int)(*(volatile unsigned char*)(iVar9+0xc)) << 5);

    int iVar2 = FUN_0103494c(uVar8,
                             (unsigned char *)&locals.saved_param2 + 3,
                             param_3,
                             *(volatile unsigned char *)(iVar9 + 0xc),
                             param_1);

    if ((param_3 & 0x30000) == 0) {
        FUN_01034b64(uVar8);
        if ((unsigned int)iVar2 == BAD) {
            int iVar9b = FUN_01034a28(((unsigned char *)&locals.saved_param2)[3]);
            if (iVar9b != iVar2) {
                FUN_01039bbe(STRA, STRB, 0x6c);
                FUN_01039bb0(STRB, 0x6c);
            }
        }
        ret = 0;
    } else {
        locals.local20 = 0;
        locals.saved_param4 = 0;
        int iVar3 = FUN_010346d8(uVar8, (void*)0, &locals.local20, 0);
        if ((unsigned int)iVar3 != BAD) {
            ret = 0xffffffea;
        } else {
            int invalid = 0;
            if (iVar2 == iVar3) {
                int iVar3b = FUN_01034a28(((unsigned char *)&locals.saved_param2)[3]);
                if (iVar3b != iVar2) {
                    FUN_01039bbe(STRA, STRB, 0x7f);
                    FUN_01039bb0(STRB, 0x7f);
                }
            }
            unsigned int uVar1 = locals.local20;
            int iVar2b;

            if ((int)(param_3 << 0xe) < 0) {
                unsigned int uVar5 = param_3 & 0x306;
                if (uVar5 == 0x106) uVar5 = 7;
                else if (uVar5 > 0x106) {
                    if (uVar5 == 0x202) uVar5 = 5;
                    else if (uVar5 == 0x300) uVar5 = 3;
                    else if (uVar5 == 0x200) uVar5 = 2;
                    else invalid = 1;
                } else if (uVar5 == 6) {
                    /* keep */
                } else if (uVar5 < 7) {
                    if (uVar5 != 0) {
                        if (uVar5 != 2) invalid = 1;
                        else uVar5 = 4;
                    }
                } else if (uVar5 == 0x100) {
                    uVar5 = 1;
                } else {
                    invalid = 1;
                }

                if (!invalid) {
                    unsigned int uVar6;
                    if ((int)(param_3 << 0x1b) < 0) uVar6 = 3;
                    else uVar6 = (unsigned int)((int)(param_3 << 0x1a) >> 0x1f);

                    unsigned char newb3 = (unsigned char)(uVar1 >> 24);
                    local20_bytes[0] = (unsigned char)uVar5;
                    local20_bytes[1] = (unsigned char)(((param_3 ^ 0x10000) >> 16) & 1u);
                    local20_bytes[2] = (unsigned char)uVar6;
                    local20_bytes[3] = newb3;

                    if ((int)(param_3 << 0xc) < 0) {
                        *(volatile unsigned int*)(*(volatile int*)(iVar9+4)+8) = 1u << (param_2 & 0xff);
                    } else if ((int)(param_3 << 0xd) < 0) {
                        *(volatile unsigned int*)(*(volatile int*)(iVar9+4)+0xc) = 1u << (param_2 & 0xff);
                    }

                    iVar2b = FUN_01034840(uVar8, &locals.local20, 0);
                    if ((unsigned int)iVar2b == BAD) ret = 0;
                    else invalid = 1;
                }
            } else {
                unsigned char bVar7;
                if ((int)(param_3 << 0x1b) < 0) bVar7 = 3;
                else bVar7 = (unsigned char)((unsigned int)((int)(param_3 << 0x1a) >> 0x1f));
                local20_bytes[0] = bVar7;
                iVar2b = FUN_010346d8(uVar8, &locals.local20, (void*)0, 0);
                if ((unsigned int)iVar2b == BAD) ret = 0;
                else invalid = 1;
            }

            if (invalid) ret = 0xffffffea;
        }
    }
    return ret;
}
