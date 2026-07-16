/* Reconstructed FUN_00051e9c @ 0x51e9c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_0005160c(int,int,uint32_t);
extern int FUN_00051c98(int);
extern int FUN_00051d8c(int,int);
extern int FUN_00080872(int,void*,int,void*);
extern void FUN_00080a42(void);
extern void FUN_00080a44(void);
int FUN_00051e9c(int param_1){
    uint8_t request[0x28];
    uint32_t result = 0;
    int iVar7=*(volatile int*)(param_1+8);
    int r4=*(volatile int*)(param_1+4);
    int iVar1=FUN_00080872(r4+4,request,2,&result);
    if(iVar1!=0) return 3;
    FUN_00080a42();
    iVar1=FUN_0005160c(iVar7+4,1,0x18);
    FUN_00080a44();
    if(iVar1!=0) return 0;
    return 7;
}
