/* Reconstructed opt3007_chip_init @ 0x2e67c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef uint32_t u32; typedef unsigned char byte;
extern void DEBUG_PRINT(unsigned long, ...);
extern int FUN_000167a8(void);
extern void FUN_00019c70(unsigned long, ...);
extern int FUN_0002e594(int a, void* b);
extern int FUN_0008638c(u32 a);
#define FLAG (*(volatile int*)0x20007554UL)

struct opt3007_transfer {
    byte *data;
    u32 length;
    byte type;
};

struct opt3007_init_frame {
    unsigned short chip_id;
    unsigned short configuration;
    byte payload[3];
    byte reserved;
    struct opt3007_transfer transfer;
};

u32 opt3007_chip_init(int param_1){
    struct opt3007_init_frame frame;
    int iVar5; u32 uVar6=0; u32 uVar4;
    volatile int *piVar1 = (volatile int*)0x2000230cUL;
    volatile int *piVar2 = (volatile int*)0x20007b6cUL;
    volatile int *piVar3;

    frame.chip_id = 0;
    if (param_1 == 0) { param_1 = FUN_000167a8(); param_1 = param_1 + 0xf80; }
    iVar5 = *piVar1;
    *piVar2 = param_1;
    if (2 < iVar5) {
        if (FLAG == 0) DEBUG_PRINT(0xa3b3f, 0xa3d00);
        else FUN_00019c70(0xa3b3f, 0xa3d00);
    }
    iVar5 = FUN_0002e594(0x7e, &frame.chip_id);
    if (iVar5 == 0) {
        uVar6 = frame.chip_id;
        if (1 < *piVar1) {
            if (FLAG == 0) DEBUG_PRINT(0xa3b7a, 0xa3d00, uVar6);
            else FUN_00019c70(0xa3b7a, 0xa3d00, uVar6);
        }
        if (uVar6 == 0x5449) {
            iVar5 = FUN_0002e594(0x7f, &frame.chip_id);
            if (iVar5 != 0) {
                if (*piVar1 < 1) return 0xfffffffbUL;
                iVar5 = FLAG; uVar4 = 0xa3bb6; goto LAB_0002e6c8;
            }
            uVar6 = frame.chip_id;
            if (1 < *piVar1) {
                if (FLAG == 0) DEBUG_PRINT(0xa3bd6, 0xa3d00, uVar6);
                else FUN_00019c70(0xa3bd6, 0xa3d00, uVar6);
            }
            if (uVar6 == 0x3001) {
                iVar5 = FUN_0002e594(1, &frame.configuration);
                piVar3 = (volatile int*)0x200023fcUL;
                if (iVar5 == 0) {
                    unsigned short configuration = frame.configuration & 63999;
                    frame.payload[0] = 1;
                    frame.payload[1] = (byte)((configuration >> 8) | 6);
                    frame.payload[2] = (byte)configuration;
                    iVar5 = FUN_0008638c((u32)*piVar3);
                    if (iVar5 == 0) {
                        if (*piVar1 < 1) return 0xfffffffbUL;
                        if (FLAG == 0) DEBUG_PRINT(0xa3af8, 0xa3cee);
                        else FUN_00019c70(0xa3af8, 0xa3cee);
                    } else {
                        int obj, vt; int (*f)(int,void*,int,int);
                        frame.transfer.data = frame.payload;
                        frame.transfer.length = 3;
                        frame.transfer.type = 2;
                        obj = *piVar3;
                        vt = *(int*)(uintptr_t)(obj + 8);
                        f = *(int(**)(int,void*,int,int))(uintptr_t)(vt + 8);
                        iVar5 = f(obj, &frame.transfer, 1, 0x45);
                        if (-1 < iVar5) {
                            if (*piVar2 != 0) *(volatile u32*)(uintptr_t)(*piVar2 + 0x10) = 1;
                            if (2 < *piVar1) {
                                if (FLAG == 0) DEBUG_PRINT(0xa3c68, 0xa3d00);
                                else FUN_00019c70(0xa3c68, 0xa3d00);
                            }
                            *(volatile byte*)0x20018da1UL = 1;
                            return 0;
                        }
                        if (*piVar1 < 1) return 0xfffffffbUL;
                        if (FLAG == 0) DEBUG_PRINT(0xa3c0c, 0xa3cee);
                        else FUN_00019c70(0xa3c0c, 0xa3cee);
                    }
                }
                if (*piVar1 < 1) return 0xfffffffbUL;
                if (FLAG != 0) { FUN_00019c70(0xa3c2d, 0xa3d00); return 0xfffffffbUL; }
                DEBUG_PRINT(0xa3c2d, 0xa3d00);
                return 0xfffffffbUL;
            }
            if (*piVar1 < 1) return 0xffffff7aUL;
            iVar5 = FLAG; uVar4 = 0xa3bea;
        } else {
            if (*piVar1 < 1) return 0xffffff7aUL;
            iVar5 = FLAG; uVar4 = 0xa3b8e;
        }
        if (iVar5 == 0) DEBUG_PRINT(uVar4, 0xa3d00, uVar6);
        else FUN_00019c70(uVar4, 0xa3d00, uVar6);
        return 0xffffff7aUL;
    }
    if (*piVar1 < 1) return 0xfffffffbUL;
    iVar5 = FLAG; uVar4 = 0xa3b5a;
LAB_0002e6c8:
    if (iVar5 == 0) DEBUG_PRINT(uVar4, 0xa3d00, (u32)frame.chip_id);
    else FUN_00019c70(uVar4, 0xa3d00, (u32)frame.chip_id);
    return 0xfffffffbUL;
}
