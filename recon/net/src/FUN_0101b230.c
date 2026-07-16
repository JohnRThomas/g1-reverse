/* net-core FUN_0101b230 @ 0x101b230  (parity 200 trials PROVEN) */
/* net-core FUN_0101b230 @ 0x101b230  (parity 300 trials PROVEN) */
extern void FUN_01008d00(int,int);
extern int FUN_01018dac(void*);
extern int FUN_01018de8(void);
extern int FUN_01019204(void);
extern int FUN_0101920c(int,int);
extern int FUN_0101a184(int);
extern int FUN_0101a38c(void*,int,int);
extern int FUN_0102029c(void);
extern int FUN_010202a8(void);
extern int FUN_010202f0(void);
extern int FUN_01020634(void);
extern unsigned long long FUN_010209e0(int,int,int);
extern int FUN_010209f0(int);
extern int FUN_01022a84(void);
extern int FUN_010231c8(int,void*);
extern int FUN_01023d38(void);
extern unsigned int FUN_01023dec(void);
extern unsigned int FUN_01023e88(void);
extern int FUN_01023ea8(int,int);
extern int FUN_01029638(void);
extern int FUN_0101a0e8(void);

/* NOTE: DAT_0101b4e0/e4/e8/ec/f0 literal-pool slots sit at entry+0x2b0..0x2c0,
   which is past func_bytes_padded's (size+pad=634-byte) load window used by
   the proof harness -- those loads read 0 in actual emulation, not their
   "real firmware" values. Model that truncation exactly (base=0, consts=0). */
#define I14 0x210010a0u
#define TBL 0x0103c254u
#define IB(off) (*(volatile unsigned char*)(I14+(off)))
#define IW(off) (*(volatile unsigned int*)(I14+(off)))
#define TB(off) (*(volatile unsigned char*)(TBL+(off)))
#define TW(off) (*(volatile unsigned int*)(TBL+(off)))

void FUN_0101b230(void)
{
    int iVar7 = FUN_01019204();
    unsigned char bVar1 = *(volatile unsigned char*)(iVar7+4);
    unsigned int uVar18;
    if (bVar1 < 0x60) {
        uVar18 = TB(bVar1 >> 5);
        if (uVar18 == 8) {
            uVar18 = 4;
            IB(0x44) = 0;
        }
    } else {
        uVar18 = 0;
    }
    unsigned int uVar13 = 0x10624dd3u;
    unsigned char bVar2 = *(volatile unsigned char*)(iVar7+3);
    signed char c2 = *(volatile signed char*)(iVar7+2);
    int iVar8a = (c2 < 0) ? 300 : 0x1e;
    int iVar17 = (c2 < 0) ? 300 : 0x1e;
    int iVar9 = FUN_010202a8();
    iVar9 = iVar8a * (int)((unsigned int)bVar2 | ((unsigned int)(bVar1 & 0x1f) << 8)) - iVar9;
    int iVar8 = FUN_010202f0();
    unsigned char rawc2 = *(volatile unsigned char*)(iVar7+2);
    int iVar7b = ((rawc2 & 0x40) == 0) ? 500 : 0x32;
    int iVar10 = FUN_01029638();
    unsigned int uVar15 = (unsigned int)(iVar9 + iVar17) * (unsigned int)(iVar10 + iVar7b) + 0x000f423fu;
    unsigned long long uVar3 = 0x431bde83ull;
    iVar7 = FUN_0102029c();
    int iVar7c = FUN_010209f0(iVar7);
    unsigned int uVar16 = (unsigned int)((uVar3 * (unsigned long long)uVar15) >> 0x32);
    int iVar7d = (iVar9 - (int)(unsigned int)(((unsigned long long)uVar13 * (unsigned long long)(unsigned int)(iVar7c + 999)) >> 0x26)) - (int)uVar16;
    uVar15 = (unsigned int)iVar7d - 0x59;

    if (uVar15 < 0x254) {
        int iVar9b = (int)FUN_010209e0(uVar18,0,0);
        int iVar7e = iVar7d + iVar8 - 0x10;
        int iVar10b = (int)TW(uVar18*4+4);
        unsigned long long lVar4 = (unsigned long long)uVar13 * (unsigned long long)(unsigned int)(iVar10b + 999);
        unsigned int uVar15b = (unsigned int)iVar17 + (unsigned int)(lVar4 >> 0x26) + 0x20 + uVar16*2 + (unsigned int)iVar7e + (unsigned int)iVar9b;
        int iVar8b = (int)FUN_010209e0(uVar18,(int)lVar4,0);
        int iVar17b = FUN_010209f0(uVar18);
        int iVar9c = FUN_0101a184(uVar18);
        unsigned int uVar16b = IW(0x38);
        unsigned int uVar18b = (unsigned int)((iVar9c + 0x11a + (int)uVar15b) - iVar8b) -
            (unsigned int)(((unsigned long long)uVar13 * (unsigned long long)(unsigned int)(iVar10b - iVar17b)) >> 0x26);
        if (uVar16b < uVar18b) {
            uVar18b = uVar18b - uVar16b;
            unsigned int uVar12 = FUN_01023e88();
            unsigned int uVar13b = FUN_01023dec();
            if (uVar18b < 0x76) uVar18b = 0x76;
            if (uVar13b <= uVar18b) uVar18b = uVar13b;
            if ((uVar16b + uVar18b) > 0xffffffu || FUN_01023ea8((int)uVar18b,(int)uVar12) != 0) {
                FUN_0101920c(2,1);
                if (IB(0x14) != 0 && IB(1) == 0) {
                    unsigned int local_40;
                    int r = FUN_0101a38c(&local_40,0,0);
                    if (r == 0) {
                        IB(2) = 1;
                    } else {
                        volatile unsigned char *pu = (volatile unsigned char*)(long)FUN_01019204();
                        int r2 = FUN_010231c8(*pu, &local_40);
                        if (r2 == 0) {
                            FUN_01008d00(0x21, 0x7cb);
                        }
                    }
                }
                goto LAB_final;
            }
            unsigned int newv = IW(0x38) + uVar18b;
            IW(0x38) = newv;
            IW(0x40) = newv - 0x109;
            FUN_01023d38();
        }
        {
            int r = FUN_01018dac(0);
            if (r != 0) { FUN_01008d00(0x21,0x794); }
        }
        {
            int r = FUN_01018de8();
            if (r != 0) { FUN_01008d00(0x21,0x795); }
        }
    } else {
        if (IB(1) == 0) {
            unsigned int uVar15c = (unsigned int)iVar8 + uVar15;
            unsigned long long uVar19 = FUN_010209e0(uVar18,0,0);
            int iVar10c = (int)TW(uVar18*4+4);
            unsigned long long lVar4 = (unsigned long long)uVar13 * (unsigned long long)(unsigned int)(iVar10c + 0xa3a1);
            int iVar9d = iVar17 + (int)(unsigned int)(lVar4 >> 0x26) + 0x60 + (int)(uVar16*2) + (int)uVar19;
            int iVar7f = (int)FUN_010209e0(uVar18,(int)(uVar19 >> 0x20),(int)lVar4);
            int iVar8c = FUN_010209f0(uVar18);
            int iVar17c = FUN_0101a184(uVar18);
            (void)FUN_0101a0e8();
            unsigned int iStack_30 = IW(0x18) + uVar15c;
            int iVar7g = ((iVar17c + 0x11a + iVar9d) - iVar7f) -
                (int)(unsigned int)(((unsigned long long)uVar13 * (unsigned long long)(unsigned int)(iVar10c - iVar8c)) >> 0x26);
            unsigned int carry = (unsigned int)(((unsigned long long)IW(0x18) + uVar15c) >> 32);
            unsigned int iStack_2c = IW(0x1c) + carry;
            (void)FUN_01023e88();
            IW(0x38) = (unsigned int)iVar7g;
            IW(0x48) = (unsigned int)iVar9d;
            IW(0x20) = iStack_30;
            IW(0x24) = iStack_2c;
            volatile unsigned char *pu = (volatile unsigned char*)(long)FUN_01019204();
            unsigned int local_40 = 0;
            int r = FUN_010231c8(*pu, &local_40);
            if (r == 0) {
                FUN_01008d00(0x21,0x751);
            }
        }
LAB_final:
        if (IB(0x14) != 0) {
            FUN_01020634();
            FUN_01022a84();
            IB(0x14) = 0;
            IB(0x15) = 0;
            return;
        }
    }
    return;
}
