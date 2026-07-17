/* Reconstructed startAudioStreamRecord @ 0x2f764  (parity: 300/300 trials, PROVEN) */

extern void FUN_0007dda4(unsigned int message, unsigned int function);
extern void FUN_00019c70(unsigned int message, unsigned int function);
extern unsigned int FUN_000167a8(void);
extern void FUN_000498c0(unsigned int ms);
extern int FUN_000720d0(int a, void *b, int c, int d);
extern void FUN_00072880(void *a);
extern void FUN_00086c78(void *dst, int val, int n);
extern void sync_to_slave(unsigned int a, unsigned int b, void *c, unsigned int d);

unsigned int startAudioStreamRecord(void)
{
    unsigned char buf[208];
    int iVar2;
    unsigned int uVar3;

    FUN_00086c78(buf + 5, 0, 0xcb);
    buf[4] = 1;
    iVar2 = FUN_000720d0(0x20003890, buf + 4, 0, 0);
    if (iVar2 == 0) {
        FUN_00072880((void*)0x200079e4UL);
        uVar3 = 0;
    } else {
        if (0 < *(int *)0x2000230cUL) {
            if (*(int *)0x20007554UL == 0) {
                FUN_0007dda4(0xa4304U, 0xa496fU);
            } else {
                FUN_00019c70(0xa4304U, 0xa496fU);
            }
        }
        *(unsigned short *)buf = 1;
        uVar3 = FUN_000167a8();
        sync_to_slave(uVar3, 6, buf, 2);
        FUN_000498c0(10000);
        if (0 < *(int *)0x2000230cUL) {
            if (*(int *)0x20007554UL == 0) {
                FUN_0007dda4(0xa432aU, 0xa496fU);
            } else {
                FUN_00019c70(0xa432aU, 0xa496fU);
            }
        }
        uVar3 = 0xffffffff;
    }
    return uVar3;
}
