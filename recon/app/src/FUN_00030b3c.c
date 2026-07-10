/* Reconstructed FUN_00030b3c @ 0x30b3c  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int FUN_00030178(int,int);
extern int FUN_000301bc(void);
extern int FUN_00030224(void);
extern int FUN_000302f8(int,void*);
extern int FUN_000304f0(void);
extern int FUN_00030710(void);
extern int FUN_00030754(int);
extern int FUN_0007cf70(void);

int FUN_00030b3c(int *param_1){
    uint8_t auStack_1c[4], auStack_18[4], auStack_14[8];
    int iVar1;
    if (param_1 && *param_1 && param_1[1] && param_1[2] && param_1[3]){
        *(volatile int*)0x20007bc0UL = (int)param_1;
        *(volatile int*)0x20007bc8UL = 0;
        *(volatile int*)0x20007bc4UL = 0;
        *(volatile uint8_t*)0x20019dadUL = 0;
        *(volatile uint8_t*)0x20003030UL = 1;
        iVar1 = FUN_000304f0();
        if (iVar1 != -1 && (iVar1=FUN_000301bc())==0 && (iVar1=FUN_0007cf70())!=-1){
            if (iVar1 == -2){
                FUN_00030178(0xff20, 0x3c00f091);
                FUN_000302f8(0x1c00, auStack_1c);
                FUN_000302f8(0x4744, auStack_14);
                FUN_000302f8(0x4444, auStack_18);
                FUN_00030178(0xff20, 0x3c00f011);
            }
            iVar1 = FUN_00030754(iVar1 == -2);
            if (iVar1==0 || ((iVar1=FUN_00030710())==0 && (iVar1=FUN_000301bc())==0 && (iVar1=FUN_000304f0())==0 && (iVar1=FUN_0007cf70())==0)){
                iVar1 = FUN_00030224();
                if (iVar1 != 0) iVar1 = 1;
                return -iVar1;
            }
        }
    }
    return -1;
}

