/* net-core FUN_0101132c @ 0x101132c  (parity 200 trials PROVEN) */
/* net-core FUN_0101132c @ 0x101132c  (parity 300 trials PROVEN) */
extern int FUN_01020738(int);
extern int FUN_010203d0(void);
extern int FUN_010208b0(void);
extern int FUN_0101fca8(void);
extern int FUN_010204e0(int);
extern int FUN_0102072c(int);
extern int FUN_01025c44(int);
extern int FUN_010129e8(int);
extern int FUN_010129f4(int);
extern int FUN_010204f4(void);
extern int FUN_010202fc(int,int);
extern int FUN_010204d4(int);
extern int FUN_010212ec(int,int);
extern int FUN_01027ed4(int,int);
extern int FUN_01027ef2(int,int);
extern unsigned long long thunk_FUN_01025034(void);
extern unsigned int FUN_0100c738(void);
extern int FUN_0101124c(int,int);
extern int FUN_0100cb4c(int);
extern int FUN_01009dd8(int*);
extern int FUN_0100aa3c(int,int,int,int);
extern unsigned int FUN_0100f63c(void);

#define PB ((volatile unsigned char*)0x21000f20)
#define PW(off) (*(volatile unsigned int*)(0x21000f20+(off)))
#define PH(off) (*(volatile unsigned short*)(0x21000f20+(off)))

int FUN_0101132c(int param_1)
{
    int r6, r7, r8;

    PB[5] = 0;
    *(volatile unsigned char*)(param_1+0x79) = 0;
    PH(0x10) = 0;
    PW(8) = 0;
    PB[6] = 0;

    FUN_01020738(0);
    FUN_010203d0();
    FUN_010208b0();
    FUN_0101fca8();
    FUN_010204e0(0);
    FUN_0102072c(0);
    FUN_01025c44(0);
    FUN_010129e8(param_1+0x28);
    FUN_010129f4(param_1+0x28);
    FUN_010204f4();
    FUN_010202fc(0x25, *(volatile unsigned char*)(param_1+4));
    FUN_010204d4((int)*(volatile signed char*)(param_1+0x10));
    {
        int iVar5 = FUN_010212ec(0, *(volatile unsigned char*)(param_1+4));
        PW(0xc) = (unsigned int)iVar5;
        if (iVar5 == 0) {
            PB[4] = 1;
            return 0;
        }
    }

    r6 = FUN_01027ed4((int)*(volatile unsigned int*)(param_1+0x44), param_1+0x48);
    r7 = FUN_01027ef2((int)*(volatile unsigned int*)(param_1+0x44), param_1+0x50);

    if (r6 != 0 && *(volatile unsigned char*)(param_1+0x20) != 0) {
        r8 = 1;
    } else if (r7 != 0) {
        r8 = *(volatile unsigned char*)(param_1+0x21);
    } else {
        r8 = 0;
    }

    if ((*(volatile unsigned char*)(param_1+0x1a) != 0) ||
        ((int)((unsigned int)(*(volatile unsigned short*)(param_1+2)) << 0x1d) < 0)) {
        int special;
        if (*(volatile int*)(param_1+0x5c)==0x7fffffff && *(volatile int*)(param_1+0x58)==-1) {
            special = 1;
        } else {
            unsigned long long cur = thunk_FUN_01025034();
            unsigned long long stored = (((unsigned long long)(unsigned int)*(volatile int*)(param_1+0x5c))<<32) |
                                          (unsigned int)*(volatile int*)(param_1+0x58);
            special = (cur < stored) ? 1 : 0;
        }
        if (!(special && r8 == 0)) {
            unsigned int uVar8 = FUN_0100c738();
            unsigned long long lVar13 = thunk_FUN_01025034();
            unsigned long long sum = (unsigned long long)uVar8 * 1000000ULL + lVar13;
            *(volatile unsigned int*)(param_1+0x58) = (unsigned int)(sum & 0xffffffffu);
            *(volatile unsigned int*)(param_1+0x5c) = (unsigned int)(sum >> 32);
            FUN_0101124c(param_1, 1);
        }
        r8 = *(volatile unsigned char*)(param_1+0x7b);
    } else {
        r8 = *(volatile unsigned char*)(param_1+0x7b);
    }

    if (((((r6 | r7) & 0xff) != 0) || (r8 != 0)) &&
        (0 <= (int)((unsigned int)(*(volatile unsigned short*)(param_1+2)) << 0x1b))) {
        int iVar5b = *(volatile int*)(param_1+0x3c);
        unsigned int target = (((unsigned int)iVar5b) << 0xc) >> 0x14;
        unsigned int uVar6b;
        do {
            uVar6b = FUN_0100f63c();
        } while (target == (uVar6b & 0xfff));
        *(volatile unsigned char*)(param_1+0x3d) = (unsigned char)uVar6b;
        *(volatile unsigned char*)(param_1+0x3e) =
            (unsigned char)((*(volatile unsigned char*)(param_1+0x3e) & 0xf0) | (unsigned char)((uVar6b << 0x14) >> 0x1c));
        *(volatile unsigned char*)(param_1+0x7b) = 0;
    }

    {
        unsigned int uVar4 = (unsigned int)FUN_0100cb4c((int)(PW(0) + 3));
        unsigned short uVar1 = *(volatile unsigned short*)(param_1+2);
        PB[0x12] = (unsigned char)uVar4;
        if ((int)((unsigned int)uVar1 << 0x1f) < 0) {
            int iVar5c, local0 = 0, local1 = 0x10000;
            int iVar9, iVar3;
            PB[0x20] = 0xff;
            iVar5c = *(volatile int*)(param_1+0x1c);
            (void)local1;
            for (;;) {
                iVar9 = FUN_01009dd8(&local0);
                iVar3 = local0;
                if (iVar9 != 0) return 0;
                if (iVar5c == local0) continue;
                {
                    int r = FUN_0100aa3c((int)*(volatile unsigned char*)(iVar3+9), iVar3+10,
                                          (int)*(volatile unsigned char*)(iVar5c+9), iVar5c+10);
                    if (r != 0) break;
                }
            }
            PB[0x20] = *(volatile unsigned char*)(iVar3+2);
            *(volatile unsigned int*)(0x21000f41) = *(volatile unsigned int*)(iVar3+3);
            *(volatile unsigned short*)(0x21000f45) = *(volatile unsigned short*)(iVar3+7);
        }
    }
    return 0;
}


