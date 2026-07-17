/* Reconstructed enqueue_uid @ 0x18e48  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned a, ...);
extern void FUN_00019c70(unsigned a, ...);
extern void FUN_00072240(unsigned a, void*b, int c, int d);
extern int  FUN_000720d0(unsigned a, void*b, int c, int d);
int enqueue_uid(unsigned *param_1, unsigned param_2, unsigned param_3){
    unsigned local[3];
    local[0]=0; local[1]=0; local[2]=param_3;
    volatile int *g = (volatile int*)0x20006a38;
    if (g[0x10/4] == 0) return 1;
    int iVar2;
    if (g[0x24/4] == 10){
        FUN_00072240(0x20006a38, local, 0, 0);
        if (*(volatile int*)0x20007554 == 0) DEBUG_PRINT(0x0009aa2f);
        else FUN_00019c70(0x0009aa2f);
    }
    local[0] = param_1[0];
    local[1] = param_1[1];
    if (*(volatile int*)0x2000230c > 0){
        if (*(volatile int*)0x20007554 == 0) DEBUG_PRINT(0x0009aa4b,0x0009b176,local[0]);
        else FUN_00019c70(0x0009aa4b,0x0009b176,local[0]);
    }
    iVar2 = FUN_000720d0(0x20006a38, local, 0, 0);
    if (iVar2 != 0 && *(volatile int*)0x2000230c > 0){
        if (*(volatile int*)0x20007554 == 0) DEBUG_PRINT(0x0009aa64,0x0009b176);
        else FUN_00019c70(0x0009aa64,0x0009b176);
    }
    return iVar2;
}
