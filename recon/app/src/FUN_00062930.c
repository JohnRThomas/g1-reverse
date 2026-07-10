/* Reconstructed FUN_00062930 @ 0x62930  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_0004d944(int,int,void*,...);
extern int FUN_000847d8(int,int,void*,int);
extern int FUN_0008638c(int);
typedef int (*fpv)(int,void*,int,int16_t);
uint32_t FUN_00062930(int param_1){
    uint16_t local_30, local_2e;
    uint8_t buf[0x28];
    int iVar1=FUN_0008638c(**(int* volatile*)(param_1+4));
    if(iVar1==0){ FUN_0004d944(0x88250,0x1040,buf,0); return 0xffffffea; }
    iVar1=FUN_000847d8(*(volatile int*)(param_1+4),0x7e,&local_30,iVar1);
    if(iVar1!=0) return 0xffffffea;
    if(local_30==0x5449){
        iVar1=FUN_000847d8(*(volatile int*)(param_1+4),0x7f,&local_30,0);
        if(iVar1!=0) return 0xffffffea;
        if(local_30==0x3001){
            iVar1=FUN_000847d8(*(volatile int*)(param_1+4),1,&local_2e,0);
            if(iVar1==0){
                int iv=**(int* volatile*)(param_1+4);
                int16_t arg=(int16_t)((*(int* volatile*)(param_1+4))[1]);
                int r=(*(volatile fpv*)(*(volatile int*)(iv+8)+8))(iv,buf,1,arg);
                if(r==0) return 0;
            }
            FUN_0004d944(0x88250,0x1040,buf,0);
            return 0xffffffea;
        }
    }
    FUN_0004d944(0x88250,0x1840,buf);
    return 0xffffffea;
}

