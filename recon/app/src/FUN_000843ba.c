/* Reconstructed FUN_000843ba @ 0x843ba  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_00083dc8(unsigned a, int b, int c, int d);
extern int FUN_000841fc(int a, int b, int c, int d, int e, void* f, int g);
unsigned FUN_000843ba(int param_1, int* param_2, int param_3){
    if (*param_2 == 0) return 0;
    int iVar2 = *(int*)(param_1 + 4);
    unsigned char sel = *(unsigned char*)(iVar2 + 0x20);
    int r3bit = *(unsigned short*)((char*)param_2 + 6) & 1;
    int uVar3;
    switch(sel){
    case 0:
        return FUN_000841fc(iVar2, 0, (unsigned char)param_2[1], r3bit, param_3, param_2, param_3);
    case 1:
        return FUN_000841fc(iVar2, 1, (unsigned char)param_2[1], r3bit, param_3, param_2, param_3);
    case 2:
        if (param_3 != 0) return 0xffffff7a;
        uVar3 = 5;
        return FUN_00083dc8(*(unsigned*)(iVar2 + 0x1c), 8, uVar3, param_3);
    case 3:
        if (param_3 != 0) return 0xffffff7a;
        uVar3 = 6;
        return FUN_00083dc8(*(unsigned*)(iVar2 + 0x1c), 8, uVar3, param_3);
    default:
        return 0xffffffed;
    }
}

