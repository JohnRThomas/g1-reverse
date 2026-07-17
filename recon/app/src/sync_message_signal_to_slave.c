/* Reconstructed sync_message_signal_to_slave @ 0x2c224  (parity: 300/300 trials, PROVEN) */

extern unsigned long long FUN_0007ce40(void);
extern unsigned int FUN_000167a8(void);
extern unsigned int sync_to_slave(unsigned int, int, void*, int, unsigned int);
extern void DEBUG_PRINT(unsigned int, ...);
extern void FUN_00019c70(void);

unsigned int sync_message_signal_to_slave(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
    struct sync_message {
        unsigned int signal;
        unsigned int value;
    } message = { param_2, param_3 };
    unsigned int uVar2, uVar4;
    unsigned int iVar3;
    unsigned long long lVar7, uVar8;

    uVar4 = param_1;
    lVar7 = FUN_0007ce40();
    message.signal = (message.signal & 0xffff0000U) | (param_1 & 0xff);
    uVar2 = FUN_000167a8();
    uVar2 = sync_to_slave(uVar2, 7, &message.signal, 1, uVar4);
    iVar3 = FUN_000167a8();
    uVar4 = 0xa2690;
    if (*(volatile unsigned char*)(iVar3 + 0x105a) == 2) {
        uVar4 = 0xa269c;
    }
    if (*(volatile unsigned int*)0x20007554UL == 0) {
        DEBUG_PRINT(uVar4, 0xa3a24);
    } else {
        FUN_00019c70();
    }
    uVar8 = FUN_0007ce40();
    if ((long long)(lVar7 + 3000) < (long long)uVar8) {
        if (*(volatile unsigned int*)0x20007554UL == 0) {
            DEBUG_PRINT(0xa26ae);
        } else {
            FUN_00019c70();
        }
    }
    return uVar2;
}
