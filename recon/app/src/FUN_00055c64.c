/* Reconstructed FUN_00055c64 @ 0x55c64  (parity: 300/300 trials, PROVEN) */

extern int FUN_0004d944(int,int,void*,int);
extern int FUN_00053e74(void*,int);
extern int FUN_00055bf8(void);
extern int FUN_00080652(int,void*,int);

int FUN_00055c64(void)
{
    unsigned char buf[24];
    int iVar1 = FUN_00053e74(buf, 8);
    if (iVar1 == 0) {
        iVar1 = FUN_00080652(0x20006000, buf, 8);
        if (iVar1 == 0) {
            struct { int f0; int f4; } s;
            s.f0 = 2;
            s.f4 = 0x000f3966;
            iVar1 = -5;
            FUN_0004d944(0x00088148, 0x1040, &s, 0);
        } else {
            iVar1 = FUN_00055bf8();
        }
    }
    return iVar1;
}

