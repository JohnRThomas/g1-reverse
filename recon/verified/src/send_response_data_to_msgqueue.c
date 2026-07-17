/* Reconstructed send_response_data_to_msgqueue @ 0x47b1c  (parity: 300/300 trials, PROVEN) */

extern void *FUN_000167a8(void);
extern void FUN_00086c78(void*, int, int);
extern void FUN_00086c04(void*, void*, unsigned int);
extern int FUN_000720d0(unsigned int, void*, int, int);
extern void DEBUG_PRINT(unsigned int, unsigned int, ...);
extern void FUN_00019c70(unsigned int, unsigned int, ...);

unsigned int send_response_data_to_msgqueue(void *param_1, unsigned int param_2)
{
    unsigned char *pcVar1;
    unsigned int uVar2;
    int iVar3;
    unsigned char stackbuf[28];

    pcVar1 = (unsigned char*)FUN_000167a8();
    if (*pcVar1 == 2) {
        uVar2 = 0;
        return uVar2;
    }
    FUN_00086c78(stackbuf, 0, 0x18);
    if (param_2 < 0x15) {
        if (param_1 != 0) {
            FUN_00086c04(stackbuf + 4, param_1, param_2);
            *(unsigned short*)(stackbuf + 2) = (unsigned short)param_2;
        }
        iVar3 = FUN_000720d0(0x2000392cUL, stackbuf, 0, 0);
        if (iVar3 == 0) {
            return 0;
        }
        DEBUG_PRINT(0xef058, 0xef750);
    } else {
        if (0 < *(volatile int*)0x2000230cUL) {
            if (*(volatile unsigned int*)0x20007554UL == 0) {
                DEBUG_PRINT(0xef01c, 0xef750, 0x14);
            } else {
                FUN_00019c70(0xef01c, 0xef750, 0x14);
            }
        }
    }
    uVar2 = 0xffffffff;
    return uVar2;
}
