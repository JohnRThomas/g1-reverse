/* Reconstructed FUN_00057cc4 @ 0x57cc4  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void FUN_00057b60(int);
extern void FUN_0005f200(int,int);
extern void FUN_0005f24c(int);
extern int  FUN_0005f594(int,int);
extern void FUN_00072fdc(int);
extern int  FUN_000816a2(int);
extern void FUN_00081746(int,int,void*);
extern int  FUN_00081aca(uint32_t,uint16_t);
extern void FUN_00081b30(void);
typedef void (*fp_t)(int,int);
void FUN_00057cc4(uint32_t param_1, int param_2, int param_3){
    uint32_t stackbuf[8];
    if (*(volatile uint16_t*)(param_2+0x10) < 4){
        FUN_00081746(0x88160, 0x1040, stackbuf);
        FUN_0005f24c(param_2); return;
    }
    int iVar1 = FUN_0005f594(param_2+0xc, 4);
    iVar1 = FUN_00081aca(param_1, *(volatile uint16_t*)(iVar1+2));
    if (iVar1 == 0){
        FUN_00081746(0x88160, 0x1880, stackbuf);
        FUN_0005f24c(param_2); return;
    }
    if ((uint16_t)(*(volatile uint16_t*)(iVar1+0x14) - 0x40) > 0x3f){
        (*(volatile fp_t*)(*(volatile int*)(iVar1+4)+0x14))(iVar1, param_2);
        FUN_0005f24c(param_2); return;
    }
    if (param_3 == 0){
        FUN_00081b30();
        FUN_0005f24c(param_2); return;
    }
    if (*(volatile uint8_t*)(iVar1+0xb4) != 4){
        int iVar2 = FUN_000816a2(iVar1+0x10);
        if ((iVar2 << 0x1e) >= 0){
            if ((uint16_t)(*(volatile uint16_t*)(iVar1+0xb6) - 0x80) <= 0x7f){
                FUN_0005f200(iVar1+0x98, param_2);
                FUN_00072fdc(iVar1+0x88); return;
            }
            FUN_00057b60(iVar1);
            FUN_0005f24c(param_2); return;
        }
    }
    FUN_00081746(0x88160, 0x1080, stackbuf);
    FUN_0005f24c(param_2); return;
}

