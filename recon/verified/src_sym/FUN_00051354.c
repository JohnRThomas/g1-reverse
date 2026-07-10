/* Reconstructed FUN_00051354 @ 0x51354  (parity: 300/300 trials, PROVEN) */

int FUN_00051354(unsigned int param_1, unsigned int param_2)
{
    int *piVar1 = *(int * volatile *)0x2000a94cUL;
    int *piVar2 = piVar1;
    int iVar4 = param_2 * 8;
    if (piVar1 != 0) {
        piVar2 = *(int**)piVar1;
    }
    while (1) {
        if (piVar1 == 0) return 0;
        if (*(volatile unsigned short*)((char*)piVar1+10) == param_1) {
            if (*(volatile unsigned short*)((char*)piVar1+8) <= param_2) {
                return 0;
            }
            int iVar3 = *(volatile int*)((char*)piVar1+4);
            if (*(volatile int*)(iVar3+iVar4) != 0 || *(volatile int*)(iVar3+iVar4+4) != 0) {
                return iVar3+iVar4;
            }
        }
        piVar1 = piVar2;
        if (piVar2 != 0) piVar2 = *(int**)piVar2;
    }
}

