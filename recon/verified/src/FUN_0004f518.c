/* Reconstructed FUN_0004f518 @ 0x4f518  (parity: 300/300 trials, PROVEN) */

extern void FUN_00086c78(void*,int,int);
extern int FUN_0005b0dc(int,int,int);
extern int FUN_0005b754(int,void*);

int FUN_0004f518(int param_1, int param_2, short param_3)
{
    unsigned char buf[24];
    int iVar2;
    FUN_00086c78(buf, 0, 0x18);
    *(int*)(buf+4) = 0x0008ad40;
    *(int*)(buf+8) = param_2;
    *(short*)(buf+0xc) = param_3;
    *(int*)(buf+0x10) = 0x0004f4f1;
    if (param_1 == 0 || ((iVar2 = FUN_0005b0dc(param_1, 0x0008ad40, 1)), iVar2 != 0)) {
        return FUN_0005b754(param_1, buf);
    } else {
        return 0xffffffea;
    }
}

