/* named: unix_timestamp_to_datetime */
/* Reconstructed unix_timestamp_to_datetime @ 0x4a1b8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int uint;
uint32_t unix_timestamp_to_datetime(uint param_1, int16_t* param_2){
    uint16_t* puVar7=(uint16_t*)0x99014;
    uint uVar3=param_1/0x15180;
    param_1=param_1-0x15180*uVar3;
    uint uVar2=0x7b2; uint uVar4;
    while(1){
        if(((uVar2&3)==0)&&(uVar2%100!=0)) uVar4=0x16e;
        else if(uVar2%400==0) uVar4=0x16e;
        else uVar4=0x16d;
        if(uVar3<uVar4) break;
        uVar3-=uVar4;
        uVar2=(uVar2+1)&0xffff;
    }
    int iVar5=0; int16_t sVar6;
    *(volatile int16_t*)param_2=(int16_t)uVar2;
    do{
        while(1){
            uVar4=*(volatile uint16_t*)puVar7;
            sVar6=(int16_t)iVar5;
            if(iVar5!=1) break;
            if((((uVar2&3)==0)&&(uVar2%100!=0))||(uVar2%400==0)){
                if(uVar3<0x1d) goto L26c;
                iVar5=-0x1d;
            } else {
                if(uVar3<uVar4) goto L26c;
                iVar5=-(int)uVar4;
            }
            uVar3=uVar3+iVar5;
            iVar5=2;
            puVar7=puVar7+1;
        }
        if(uVar2%400==0) uVar4=0x1d;
        if(uVar3<uVar4) goto L26c;
        iVar5=iVar5+1;
        uVar3=uVar3-uVar4;
        puVar7=puVar7+1;
    }while(iVar5!=0xc);
    sVar6=0xc;
L26c:
    *(volatile int16_t*)(param_2+2)=(int16_t)uVar3+1;
    uint u=param_1%0xe10;
    *(volatile int16_t*)(param_2+3)=(int16_t)(param_1/0xe10);
    int16_t sVar1=(int16_t)(u/0x3c);
    *(volatile int16_t*)(param_2+5)=(int16_t)u+sVar1*-0x3c;
    *(volatile int16_t*)(param_2+1)=sVar6+1;
    *(volatile int16_t*)(param_2+4)=sVar1;
    return 0;
}

