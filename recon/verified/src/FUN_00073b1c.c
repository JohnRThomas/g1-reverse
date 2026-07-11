/* Reconstructed FUN_00073b1c @ 0x73b1c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"

extern int FUN_00072040(unsigned a);
extern int FUN_0007205c(unsigned a);
extern void FUN_00072078(unsigned a);
extern void FUN_0007e2ec(unsigned a, unsigned b);
extern void FUN_0007e2fa(unsigned a, unsigned b, unsigned c, unsigned d);
void FUN_00073b1c(void){
    unsigned r4;
    r4 = __get_BASEPRI();
    unsigned tmp = 0x20;
    __set_BASEPRI_MAX(tmp);
    __ISB();
    int iVar3 = FUN_00072040(0x2000b490);
    if (iVar3 == 0){
        FUN_0007e2fa(0x00099cbd,0x000f0920,0x000f08c7,0x72);
        FUN_0007e2fa(0x000f0935,0x2000b490,0,0);
        FUN_0007e2ec(0x000f08c7,0x72);
        return;
    }
    FUN_00072078(0x2000b490);
    unsigned ipsr;
    ipsr = __get_IPSR();
    if (ipsr != 0){
        FUN_0007e2fa(0x00099cbd,0x000f801f,0x000f84f7,0xfd);
        FUN_0007e2fa(0x000f53ff,0,0,0);
        FUN_0007e2ec(0x000f84f7,0xfd);
        return;
    }
    int r2 = *(volatile int*)(0x2000b448 + 8);
    unsigned char cVar1 = *(volatile unsigned char*)(r2 + 0xf);
    if (cVar1 == 1){
        FUN_0007e2fa(0x00099cbd,0x000f8522,0x000f84f7,0xfe);
        FUN_0007e2fa(0x000f53ff,0,0,0);
        FUN_0007e2ec(0x000f84f7,0xfe);
        return;
    }
    *(volatile unsigned char*)(r2 + 0xf) = (unsigned char)(cVar1 - 1);
    int iv = FUN_0007205c(0x2000b490);
    if (iv == 0){
        FUN_0007e2fa(0x00099cbd,0x000f08f4,0x000f08c7,0xf0);
        FUN_0007e2fa(0x000f090b,0x2000b490,0,0);
        FUN_0007e2ec(0x000f08c7,0xf0);
        return;
    }
    __set_BASEPRI(r4);
    __ISB();
    return;
}
