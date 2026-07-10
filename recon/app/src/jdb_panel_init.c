/* Reconstructed jdb_panel_init @ 0x46fc0  (parity: 300/300 trials, PROVEN) */

extern void FUN_00047538(void);
extern void FUN_00046e3c(void);
extern int FUN_00047724(void);
extern void DEBUG_PRINT(void);
extern void FUN_00019c70(void);

unsigned int jdb_panel_init(unsigned char *param_1)
{
    *(unsigned int*)(param_1+0x374) = (unsigned int)(param_1 - 0x5c);
    FUN_00047538();
    FUN_00046e3c();
    int iVar1 = FUN_00047724();
    *(volatile unsigned int*)0x2000a074UL = iVar1;
    unsigned int uVar2;
    if (iVar1 == 0x4010) {
        uVar2 = 0;
        *(unsigned int*)(param_1+0x35c) = 1;
    } else {
        if (*(volatile int*)0x2000230cUL > 2) {
            if (*(volatile unsigned int*)0x20007554UL == 0) {
                DEBUG_PRINT();
            } else {
                FUN_00019c70();
            }
        }
        uVar2 = 0xffffffffUL;
    }
    return uVar2;
}

