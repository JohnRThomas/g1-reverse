/* Reconstructed SendPowerInfoToSlave @ 0x488bc  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(unsigned long, ...);
extern void *FUN_000167a8(void);
extern void FUN_00019c70(unsigned long, ...);
extern int FUN_000720d0(uint32_t, void*, int, int);
extern void FUN_00086c78(void*, int, int);

unsigned int SendPowerInfoToSlave(int param_1)
{
    unsigned char uVar1;
    unsigned char bVar2;
    volatile int *piVar3;
    volatile int *piVar4;
    int iVar5;
    unsigned int uVar6;
    unsigned int uVar7;
    unsigned char request[24];

    FUN_00086c78(&request[1], 0, 0x17);
    request[0] = 4;
    request[4] = (unsigned char)param_1;
    *(unsigned short *)&request[2] = 1;
    iVar5 = FUN_000720d0(0x2000392cUL, request, 0, 0);
    piVar4 = (volatile int*)0x20007554UL;
    piVar3 = (volatile int*)0x2000230cUL;
    if (iVar5 == 0) {
        uVar7 = 0;
        if (2 < *piVar3) {
            if (*piVar4 == 0) {
                uVar6 = 0x000ef506UL;
                if (param_1 == 1) {
                    uVar6 = 0x000ef4faUL;
                }
                DEBUG_PRINT(0x000ef519UL, 0x000ef6f2UL, uVar6);
            } else {
                uVar6 = 0x000ef506UL;
                if (param_1 == 1) {
                    uVar6 = 0x000ef4faUL;
                }
                FUN_00019c70(0x000ef519UL, 0x000ef6f2UL, uVar6);
            }
            if (2 < *piVar3) {
                if (*piVar4 == 0) {
                    iVar5 = (int)FUN_000167a8();
                    bVar2 = *(unsigned char*)(iVar5 + 0xfc0);
                    iVar5 = (int)FUN_000167a8();
                    DEBUG_PRINT(0x000ef553UL, 0x000ef6f2UL, (unsigned int)bVar2, (unsigned int)*(unsigned char*)(iVar5 + 0xfc1));
                } else {
                    iVar5 = (int)FUN_000167a8();
                    uVar1 = *(unsigned char*)(iVar5 + 0xfc0);
                    iVar5 = (int)FUN_000167a8();
                    FUN_00019c70(0x000ef553UL, 0x000ef6f2UL, uVar1, *(unsigned char*)(iVar5 + 0xfc1));
                }
            }
        }
    } else {
        DEBUG_PRINT(0x000ef058UL, 0x000ef6f2UL);
        uVar7 = 0xffffffffUL;
    }
    return uVar7;
}
