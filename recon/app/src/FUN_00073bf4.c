/* Reconstructed FUN_00073bf4 @ 0x73bf4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_00072040(void*);
extern int FUN_0007205c(void*);
extern void FUN_00072078(void*);
extern void FUN_000737d8(void);
extern void FUN_0007e2ec(unsigned,unsigned);
extern void FUN_0007e2fa(unsigned long, ...);
extern void FUN_00086634(unsigned);

void FUN_00073bf4(void){
    int iVar3 = FUN_00072040((void*)0x2000b490);
    if (iVar3 == 0){
        FUN_0007e2fa(0x99cbd, 0x000f0920, 0x000f08c7, 0x72);
        FUN_0007e2fa(0x000f0935, 0x2000b490);
        FUN_0007e2ec(0x000f08c7, 0x72);
        return;
    }
    FUN_00072078((void*)0x2000b490);
    char cVar1 = *(char*)(*(int*)(0x2000b448+8)+0xf);
    unsigned r2 = (unsigned)*(int*)(0x2000b448+8);
    unsigned r3 = (unsigned char)cVar1;
    if (cVar1 == 0){
        FUN_0007e2fa(0x99cbd, 0x000f8553, 0x000f82f4, 0x3f8);
        FUN_0007e2fa(0x000f53ff);
        FUN_0007e2ec(0x000f82f4, 0x3f8);
        r2 = 0x000f82f4;
        r3 = 0x3f8;
        /* fall through in emulation (ipsr==0) */
    }
    *(char*)(r2 + 0xf) = (char)(r3 + 1);
    FUN_000737d8();
    iVar3 = FUN_0007205c((void*)0x2000b490);
    if (iVar3 != 0){
        FUN_00086634(0);
        return;
    }
    FUN_0007e2fa(0x99cbd, 0x000f08f4, 0x000f08c7, 0xf0);
    FUN_0007e2fa(0x000f090b, 0x2000b490);
    FUN_0007e2ec(0x000f08c7, 0xf0);
}

