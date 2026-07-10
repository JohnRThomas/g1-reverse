/* Reconstructed FUN_00064a88 @ 0x64a88  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int FUN_000646c0(int,void*);
extern void FUN_00084f16(void*);
extern void FUN_00086c04(int,uint32_t,unsigned);
extern void FUN_00086c78(void*,int,int);
typedef int (*fp)(int,int);
int FUN_00064a88(int param_1, int param_2){
    volatile uint32_t *puVar1 = (volatile uint32_t*)0x20002bacUL;
    uint32_t s[9];
    int iVar2; unsigned uVar3;
    FUN_00086c78(s, 0, 0x24);
    s[0] = ((fp)puVar1[0])(0x100,0);
    s[1] = 0x100;
    s[6] = puVar1[0];
    s[7] = puVar1[1];
    s[8] = puVar1[2];
    s[5] = param_2;
    int local_34 = (int)s[0];
    if(local_34 != 0 && (iVar2 = FUN_000646c0(param_1, s)) != 0){
        FUN_00084f16(s);
        int local_2c = (int)s[2];
        if(puVar1[2]==0){
            iVar2 = ((fp)puVar1[0])(local_2c+1,0);
            if(iVar2!=0){
                uVar3 = local_2c+1U;
                if(s[1] <= (unsigned)(local_2c+1U)) uVar3 = s[1];
                FUN_00086c04(iVar2, s[0], uVar3);
                *(volatile uint8_t*)(iVar2+local_2c)=0;
                ((fp)puVar1[1])(s[0],0);
                return iVar2;
            }
        } else {
            iVar2 = ((fp)puVar1[2])(s[0], local_2c+1);
            if(iVar2!=0) return iVar2;
        }
    }
    if((int)s[0]!=0){
        ((fp)puVar1[1])(0,0);
    }
    return 0;
}

