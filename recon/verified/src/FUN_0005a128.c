/* Reconstructed FUN_0005a128 @ 0x5a128  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void* FUN_00059bcc(int,int);
extern void FUN_000828da(void*,unsigned);
extern void FUN_00082a42(int,int,void*);
extern int FUN_00080f92(int,void*);
extern void sub_5a0e8(void*);

void FUN_0005a128(unsigned char param_1, unsigned param_2, unsigned param_3, unsigned param_4){
    unsigned char *puVar1 = (unsigned char*)FUN_00059bcc(0,0);
    volatile int loc[4];
    if (puVar1 == 0){
        puVar1 = (unsigned char*)FUN_00059bcc(0, 0x000f2b3a);
        if (puVar1 == 0){
            loc[0]=2; loc[1]=0x000f47f3;
            FUN_00082a42(0x00088128, 0x1040, (void*)&loc[0]);
            return;
        }
        *puVar1 = param_1;
        FUN_000828da(puVar1+1, param_2);
    }
    unsigned a = *(unsigned short*)(puVar1+8);
    unsigned uVar3 = *(unsigned short*)(puVar1+0xa);
    if (a != 0){
        if (param_3 < a) goto L19c;
        goto L196;
    }
    if (uVar3 != 0) goto L196;
    *(unsigned short*)(puVar1+8) = (unsigned short)param_3;
  L176:
    *(unsigned short*)(puVar1+0xa) = (unsigned short)param_4;
  L178:
    {
        int iVar2 = FUN_00080f92(*puVar1, puVar1+1);
        if (iVar2 == 0) return;
        sub_5a0e8(puVar1);
        return;
    }
  L196:
    if (param_4 > uVar3) goto L176;
    return;
  L19c:
    *(unsigned short*)(puVar1+8) = (unsigned short)param_3;
    if (param_4 <= uVar3) goto L178;
    goto L176;
}

