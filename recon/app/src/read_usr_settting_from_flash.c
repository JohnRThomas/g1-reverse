/* Reconstructed read_usr_settting_from_flash @ 0x23400  (parity: 300/300 trials, PROVEN) */
extern void FUN_00086c78(void *a0, unsigned int a1, unsigned int a2);
extern int FUN_000225b4(unsigned int a0, void *a1, unsigned int a2);
extern void DEBUG_PRINT(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);

unsigned int read_usr_settting_from_flash(unsigned char *param_1)
{
    unsigned char buf[32];
    int iVar1;
    unsigned int uVar2;
    FUN_00086c78(buf, 0, 0x20);
    iVar1 = FUN_000225b4(0x134000UL, buf, 0x20UL);
    if (iVar1 == 0) {
        if (1 < *(volatile int*)0x2000230cUL) {
            if (*(volatile int*)0x20007554UL == 0)
                DEBUG_PRINT(0x9e708UL, 0x9e72aUL);
            else
                FUN_00019c70(0x9e708UL, 0x9e72aUL);
        }
        param_1[0x15] = buf[0x15];
        *(unsigned short*)(param_1 + 0x16) = *(unsigned short*)(buf + 0x16);
        uVar2 = 0;
    } else {
        if (1 < *(volatile int*)0x2000230cUL) {
            if (*(volatile int*)0x20007554UL == 0)
                DEBUG_PRINT(0x9e60cUL, 0x9e72aUL);
            else
                FUN_00019c70(0x9e60cUL, 0x9e72aUL);
        }
        uVar2 = 0xffffffffUL;
    }
    return uVar2;
}
