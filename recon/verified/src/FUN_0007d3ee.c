/* Reconstructed FUN_0007d3ee @ 0x7d3ee  (parity: 300/300 trials, PROVEN) */

extern int FUN_000167a8(void);
int FUN_0007d3ee(void){
    int iVar2;
    unsigned short uVar1;
    iVar2 = FUN_000167a8();
    if (*(unsigned short*)(iVar2 + 0x1072) == 0) goto L_426;
L_3fe:
    iVar2 = FUN_000167a8();
    if (*(unsigned short*)(iVar2 + 0x1072) > 0x40) goto L_436;
    goto L_40e;
L_426:
    iVar2 = FUN_000167a8();
    if (*(unsigned short*)(iVar2 + 0x1074) != 0) goto L_3fe;
L_436:
    iVar2 = FUN_000167a8();
    *(unsigned short*)(iVar2 + 0x1072) = 0x20;
L_40e:
    iVar2 = FUN_000167a8();
    uVar1 = *(unsigned short*)(iVar2 + 0x1072);
    iVar2 = FUN_000167a8();
    return *(int*)(iVar2 + 0xec4) + (unsigned int)uVar1;
}

