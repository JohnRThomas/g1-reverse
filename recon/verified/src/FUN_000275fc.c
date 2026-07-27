/* Reconstructed FUN_000275fc @ 0x275fc  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int uint;
extern int FUN_000167a8(void);
extern void FUN_00027448(int,int,int,int);
extern unsigned int FUN_00033b88(void);
extern void FUN_00033bf0(int,int);
extern void FUN_00034524(int);
extern int sync_to_slave(int,int,int,int);
void FUN_000275fc(void){
    int iVar3=FUN_000167a8();
    if(((uint)*(volatile uint8_t*)(iVar3+0xe4)<<0x1d)&0x80000000u) return;
    iVar3=FUN_000167a8();
    uint8_t r5=*(volatile uint8_t*)(iVar3+0x6de)&4;
    if(r5!=0) return;
    int r4=FUN_00033b88();
    if(r4==0) return;
    char* pcVar4=(char*)FUN_000167a8();
    if(*(volatile char*)pcVar4==1){
        int8_t d=*(volatile int8_t*)(r4+0xd);
        if(d==1){
            *(volatile uint8_t*)0x20018d98=(uint8_t)d;
            int u=FUN_000167a8();
            int r6=sync_to_slave(u,0xa,r4+8,4);
            if(r6>2999) return;
            FUN_00033bf0(*(volatile uint8_t*)(r4+0xc),2);
            return;
        }
        if(d!=3) return;
        int u=FUN_000167a8();
        int r6=sync_to_slave(u,0xb,r4+8,4);
        if(r6>2999) return;
        FUN_00033bf0(*(volatile uint8_t*)(r4+0xc),4);
        FUN_00034524(*(volatile int*)(r4+8));
        *(volatile uint8_t*)0x20018d98=r5;
        return;
    } else {
        uint8_t r5b=*(volatile uint8_t*)0x20018d9f;
        if(r5b!=0) return;
        int8_t r6b=*(volatile int8_t*)(r4+0xd);
        if(r6b==0){
            *(volatile uint8_t*)0x20018d98=1;
            int u=FUN_000167a8();
            FUN_00027448(u,0xb,r4,0xda);
            *(volatile uint8_t*)0x20018d82=(uint8_t)r6b;
            return;
        }
        if(r6b!=2) return;
        uint8_t r3c=(uint8_t)(*(volatile uint8_t*)0x20018d82+1);
        *(volatile uint8_t*)0x20018d82=r3c;
        if(r3c<=9){
            int u=FUN_000167a8();
            FUN_00027448(u,0xc,r4+0xda,0xda);
            return;
        }
        int c=*(volatile uint8_t*)(r4+0xc);
        *(volatile uint8_t*)0x20018d82=r5b;
        FUN_00033bf0(c,r5b);
        *(volatile uint8_t*)0x20018d98=r5b;
        return;
    }
}

