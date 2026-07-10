#include "g1_app_symbols.h"
/* named: utf8_decode_to_utf16_buffer */
/* Reconstructed utf8_decode_to_utf16_buffer @ 0x47844  (parity: 300/300 trials, PROVEN) */

extern int utf8_to_unicode(int a, int b);
extern void printf(unsigned a, int b);
int utf8_decode_to_utf16_buffer(int param_1, int param_2, int param_3, int param_4){
    int iVar2 = 0, iVar3 = 0;
    for(;;){
        if (param_2 <= iVar2){
            *(volatile short*)(param_3 + iVar3*2) = 0;
            return iVar3;
        }
        unsigned uVar1 = *(volatile unsigned char*)(param_1 + iVar2);
        if (uVar1 == 0){
            *(volatile short*)(param_3 + iVar3*2) = 0;
            return iVar3;
        }
        if (uVar1 == 0xd || uVar1 == 10 || (uVar1 - 0x20) < 0x60){
            iVar2 = iVar2 + 1;
            goto store;
        }
        if ((uVar1 & 0xf0) == 0xe0){
            uVar1 = (unsigned)utf8_to_unicode(param_1 + iVar2, 3);
            iVar2 = iVar2 + 3;
            goto store;
        }
        if ((uVar1 & 0xe0) == 0xc0){
            uVar1 = (unsigned)utf8_to_unicode(param_1 + iVar2, 2);
            iVar2 = iVar2 + 2;
            goto store;
        }
        iVar2 = iVar2 + 1;
        continue;
    store:
        *(volatile short*)(param_3 + iVar3*2) = (short)uVar1;
        if (param_4 - 1 == iVar3){
            printf("maybe array overflow!(k=%d)\n" /*=0xd74d7*/, iVar3);
            *(volatile short*)(param_3 + iVar3*2) = 0;
            return iVar3;
        }
        iVar3 = iVar3 + 1;
    }
}

