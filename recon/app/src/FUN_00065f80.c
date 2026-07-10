/* Reconstructed FUN_00065f80 @ 0x65f80  (parity: 300/300 trials, PROVEN) */
extern void FUN_0007e2fa(unsigned,unsigned,unsigned,unsigned,unsigned);
extern long long FUN_0007e2ec(unsigned,unsigned);
extern void FUN_00065f04(void);
extern void FUN_00065ef0(void);
void FUN_00065f80(unsigned param_1, unsigned param_2, unsigned param_3, unsigned param_4){
    unsigned r0v = param_1;
    if (param_1 < 0x100000) goto L_fae;
    if ((param_1 - 0xff8000) < 0x1000) goto L_fae;
    FUN_0007e2fa(0x99cbd,0xf6ca8,0xf6c32,0x195,param_4);
    { long long r = FUN_0007e2ec(0xf6c32,0x195); r0v=(unsigned)r; }
L_fae:
    if ((r0v & 3) == 0) goto L_fc6;
    FUN_0007e2fa(0x99cbd,0xf6cc2,0xf6c32,0x196,param_4);
    { long long r = FUN_0007e2ec(0xf6c32,0x196); r0v=(unsigned)r; }
    goto L_fae;
L_fc6:
    *(volatile unsigned*)(0x50039000UL + 0x584) = 1;
    *(volatile unsigned*)(0x50039000UL + 0x504) = 1;
    FUN_00065f04();
    FUN_00065ef0();
}

