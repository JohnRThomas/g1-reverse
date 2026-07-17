/* Reconstructed ext_flash_api_init @ 0x2e4e8  (parity: 300/300 trials, PROVEN) */

extern void FUN_000864c2(unsigned int);
extern unsigned int FUN_0008638c(unsigned int);
extern unsigned short FUN_00083a9a(unsigned int);
extern unsigned int FUN_000167a8(void);
extern void DEBUG_PRINT(unsigned int, unsigned int, ...);
extern void FUN_00019c70(unsigned int, ...);

unsigned int ext_flash_api_init(unsigned int *param_1, unsigned int *param_2, unsigned int *param_3, unsigned int param_4)
{
    int iVar4;
    unsigned int uVar5;
    unsigned short uVar3;

    FUN_000864c2(0x20007b54UL);
    uVar5 = 0x87bf0;
    iVar4 = FUN_0008638c(0x87bf0);
    if (iVar4 == 0) {
        if (0 < *(volatile int*)0x2000230cUL) {
            if (*(volatile unsigned int*)0x20007554UL == 0) {
                DEBUG_PRINT(0xa3aa6, 0xa3ae5);
            } else {
                FUN_00019c70(0xa3aa6, 0xa3ae5);
            }
        }
        uVar5 = 0xffffffff;
    } else {
        *param_1 = 0x2e399;
        *param_2 = 0x2e441;
        *param_3 = 0x2e301;
        iVar4 = *(volatile int*)0x2000230cUL;
        *(volatile unsigned int*)0x20007b68UL = uVar5;
        if (2 < iVar4) {
            if (*(volatile unsigned int*)0x20007554UL == 0) {
                DEBUG_PRINT(0xa3a8b, 0xa3ae5, 0x20007b68, 0, param_4);
            } else {
                FUN_00019c70(0xa3a8b, 0xa3ae5, 0x20007b68, 0, param_4);
            }
        }
        uVar3 = FUN_00083a9a(0x87bf0);
        iVar4 = FUN_000167a8();
        uVar5 = 0;
        *(volatile unsigned short*)(iVar4 + 0x108a) = uVar3;
    }
    return uVar5;
}
