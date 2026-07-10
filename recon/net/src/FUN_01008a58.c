/* net-core FUN_01008a58 @ 0x1008a58  (parity 200 trials PROVEN) */
/* net-core FUN_01008a58 @ 0x1008a58  (parity 300 trials PROVEN) */
extern int FUN_010098d8(int,int);
extern int FUN_01009ea4(int,int,int);
extern int FUN_0100a1e0(int,int,int,int);
extern int FUN_0100a50c(int,int,int);
extern int FUN_0100a5c8(int,int,int);
extern int FUN_0100a664(int,int,int,int);
extern int FUN_0101077c(int);
extern int FUN_010217ac(int,int,int);
extern int FUN_01021820(int);
extern int FUN_0102182c(int,int);
extern int FUN_01027846(int,int,int,int);
extern int FUN_010279e6(int,int,int);
extern int FUN_0102185c(int,int);

typedef int (*fp3_t)(int,int,int);
typedef int (*fp1_t)(int);
typedef int (*fp5_t)(int,int,int,int,int);

#define S ((volatile unsigned char*)0x21000a30)
#define FPA_RAW (*(volatile unsigned int*)0x21000044)
#define FPB_RAW (*(volatile unsigned int*)0x2100004c)
#define FPC_RAW (*(volatile unsigned int*)0x21000048)
#define A8(x) (((x)+7u)&~7u)
#define A4(x) (((x)+3u)&~3u)

int FUN_01008a58(int param_1, int param_2)
{
    unsigned int off = A8((unsigned int)param_1);
    int ret;

    ret = FUN_010098d8(0,0);
    off += (unsigned int)ret;

    {
        unsigned char b0 = S[0], b1 = S[1];
        unsigned char sb = (unsigned char)(b0 + b1);
        unsigned char i;
        int iVar10 = 0;
        for (i = 0; i < sb; i++) {
            iVar10 += FUN_01027846(0,0,0,0);
        }
        off = A4(off);
        ret = FUN_01009ea4(0, sb, iVar10);
        off += (unsigned int)ret;
    }

    {
        unsigned char f2 = S[2];
        unsigned char f9 = S[9];
        unsigned char f1f = S[0x1f];
        unsigned char fc = S[0xc];

        if (f2 != 0) {
            off = A4(off);
            ret = FUN_0100a1e0(0,0,0,0);
            off += (unsigned int)ret;
        }

        if (f1f != 0 && f9 != 0) {
            off = A4(off);
            ret = FUN_0100a50c(0,0,0);
            off += (unsigned int)ret;
        }

        if (fc != 0 && (f2 != 0 || (f1f != 0 && f9 != 0))) {
            off = A8(off);
            ret = FUN_0101077c(0);
            off += (unsigned int)ret;
        }
    }

    if (FPA_RAW != 0 && S[4] != 0) {
        off = A4(off);
        ret = ((fp3_t)FPA_RAW)(0,0,0);
        off += (unsigned int)ret;
    }

    if (FPB_RAW != 0 && S[0xe] != 0) {
        off = A4(off);
        ret = ((fp1_t)FPB_RAW)(0);
        off += (unsigned int)ret;
    }

    if (FPC_RAW != 0 && S[0xf] != 0) {
        off = A4(off);
        ret = ((fp5_t)FPC_RAW)(0,0,0,0,0);
        off += (unsigned int)ret;
    }

    if (S[0x1e] != 0 && S[4] != 0) {
        off = A4(off);
        ret = FUN_0100a5c8(0,0,0);
        off += (unsigned int)ret;
    }

    if (S[0x19] != 0) {
        unsigned int r8v = A8(off);
        ret = FUN_010279e6(0, 0, 0x10e);
        off = r8v + (unsigned int)ret;
    }

    if (S[0x1a] != 0) {
        unsigned int r9v = A8(off);
        ret = FUN_010279e6(0, 0, 0xfb);
        off = r9v + (unsigned int)ret;
    }

    if (param_2 == 0) {
        FUN_010217ac(0,0,0);
    }

    if (S[0x1b] == 0 || S[0x1c] == 0) {
        if (param_2 == 0) {
            FUN_01021820(0);
        }
    } else {
        off = A8(off);
        ret = FUN_010279e6(0,0,0x104);
        off += (unsigned int)ret;
        off = (A8(off + 3)) | 4u;
        ret = FUN_0100a664(0,0,0,0);
        off += (unsigned int)ret;
        if (param_2 == 0) {
            FUN_01021820(0);
            FUN_0102182c(0,0);
        }
    }

    if (*(volatile unsigned int*)0x21000a54 != 0) {
        if (param_2 == 0) {
            *(volatile unsigned int*)0x21000a54 = off;
        }
        off += 0x28u;
    }

    if (S[0x1d] != 0) {
        off = A8(off);
        ret = FUN_010279e6(0,0,10000);
        off += (unsigned int)ret;
        if (param_2 == 0) {
            FUN_0102185c(0,0);
        }
    }

    return (int)(off - (unsigned int)param_1);
}


