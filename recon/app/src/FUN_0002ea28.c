/* Reconstructed FUN_0002ea28 @ 0x2ea28  (parity: 300/300 trials, PROVEN) */

extern int FUN_0000e2b4(void*, int);
extern int FUN_0002e988(int, void*, void*, void*);
extern unsigned long long FUN_0007ceda(void);
extern void FUN_0007cef6(int, int, void*);

int FUN_0002ea28(int param_1)
{
    struct {
        unsigned char event[8];
        int first;
        int second;
        int third;
    } frame;
    int iVar1;

    frame.first = 0;
    frame.second = 0;
    frame.third = 0;
    iVar1 = FUN_0002e988(param_1, &frame.first, &frame.second, &frame.third);
    if (iVar1 >= 0) {
        FUN_0007cef6(param_1, 0x39, frame.event);
        iVar1 = FUN_0000e2b4(&frame.first, 0);
        if (iVar1 >= 0) {
            unsigned long long uVar2 = FUN_0007ceda();
            *(volatile unsigned long long*)0x20004790UL = uVar2;
            iVar1 = 0;
        }
    }
    return iVar1;
}
