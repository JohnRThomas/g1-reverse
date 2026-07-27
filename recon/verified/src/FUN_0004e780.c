/* Reconstructed FUN_0004e780 @ 0x4e780  (parity: 100/100 trials, PROVEN) */
#include <stdint.h>
extern int FUN_0007e9dc(int,int,void*,int);
extern void FUN_0007e9d4(unsigned int, unsigned int);
extern void FUN_0004c8f8(int,int,void*,int);
extern int FUN_0004e604(void*,int,unsigned,void*,unsigned);

int FUN_0004e780(int param_1, unsigned param_2){
    int iVar7 = param_1 + 8;
    struct {
        unsigned char reserved[11];
        unsigned char marker;
        int owner;
        short key;
        unsigned char alignment[2];
        unsigned char data[76];
    } frame;
    unsigned short r4v = (unsigned short)(*(unsigned short*)(param_1+0x38) + 1);
    int iVar2, iVar3;
    unsigned short sVar4, sVar6, sVar5;
  LOOP:
    sVar4 = r4v;
    sVar6 = (unsigned short)(sVar4 - 1);
    if (sVar6 == 0x8000) return 0;
    iVar2 = FUN_0007e9dc(iVar7, sVar6, frame.data, 0x4a);
    sVar5 = (unsigned short)(sVar4 + 0x3fff);
    iVar3 = FUN_0007e9dc(iVar7, sVar5, &frame.marker, 1);
    if (iVar2 > 0){
        if (iVar3 > 0) goto L806;
        goto L7d8;
    }
    if (iVar3 > 0) goto L7d8;
    r4v = sVar6;
    goto LOOP;
  L7d8:
    if (*(unsigned short*)(param_1+0x38) == sVar6){
        *(unsigned short*)(param_1+0x38) = (unsigned short)(sVar4 - 2);
        FUN_0004c8f8(iVar7, 0x8000, (void*)(param_1+0x38), 2);
    }
    FUN_0007e9d4(iVar7, sVar6);
    FUN_0007e9d4(iVar7, sVar5);
    r4v = sVar6;
    goto LOOP;
  L806:
    frame.data[iVar2] = 0;
    frame.owner = iVar7;
    frame.key = (short)sVar5;
    iVar2 = FUN_0004e604(frame.data, iVar3, 0x0007f211,
                         &frame.owner, param_2);
    if (iVar2 != 0) return iVar2;
    r4v = sVar6;
    goto LOOP;
}
