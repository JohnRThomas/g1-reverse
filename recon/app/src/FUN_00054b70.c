/* Reconstructed FUN_00054b70 @ 0x54b70  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int FUN_00050b8c(int);
extern int FUN_0005571c(void);
extern int FUN_00055e1c(void);
extern int FUN_00056990(void);
extern int FUN_00080e6a(int,int);
extern int FUN_00080e94(int,int);
extern int FUN_00080ea2(int,int,void*);
extern int FUN_00080ea8(int,int);
extern int FUN_00086c78(int,int,int);

int FUN_00054b70(void)
{
    int base = 0x20002000;
    int iVar2;
    if (*(volatile int*)(base + 0x168) == 0) {
        unsigned local_20, local_1c;
        iVar2 = -0x13;
        local_1c = 0x000f3376;
        local_20 = 2;
        FUN_00080ea2(0x00088138, 0x1040, &local_20);
    } else if (*(volatile int*)(*(volatile int*)(base + 0x168) + 0x10) == 0) {
        iVar2 = -0x86;
    } else {
        iVar2 = FUN_00080e6a(base + 0xd4, 2);
        if (iVar2 << 0x1e < 0) {
            iVar2 = -0x78;
        } else {
            FUN_00080ea8(base + 0xd4, 0xfffffffb);
            iVar2 = (*(int(**)(void))(*(volatile int*)(base + 0x168) + 0x10))();
            if (iVar2 == 0) {
                FUN_00086c78(base + 0x80, 0, 0x40);
                FUN_00080e94(base + 0x68, 0x000f2b3a);
                FUN_0005571c();
                FUN_00055e1c();
                FUN_00056990();
                *(volatile uint16_t*)0x2000ff06UL = 0;
                FUN_00050b8c(0x20005e30);
                FUN_00050b8c(0x20005f08);
                FUN_00080ea8(base + 0xd4, 0xfffffffe);
            } else {
                unsigned local_40, local_3c; int iStack_38;
                local_3c = 0x000f33b7;
                local_40 = 3;
                iStack_38 = iVar2;
                FUN_00080ea2(0x00088138, 0x1840, &local_40);
                FUN_00080e6a(base + 0xd4, 4);
            }
        }
    }
    return iVar2;
}

