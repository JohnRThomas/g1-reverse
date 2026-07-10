/* Reconstructed imu_fusion_thread @ 0xfe88  (parity: 1000/1000 trials, PROVEN) */
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
typedef long long i64; typedef unsigned long long u64;

#define I(a)  (*(volatile int*)(a))
#define U(a)  (*(volatile unsigned*)(a))
#define B(a)  (*(volatile signed char*)(a))
#define UB(a) (*(volatile unsigned char*)(a))
#define F(a)  (*(volatile float*)(a))

extern int DEBUG_PRINT(void);
extern int FUN_00019c70(void);
extern int FUN_00086c78(int,int,int);
extern int thunk_FUN_00074844(int,int);
extern i64 thunk_FUN_00074f68(void);
extern int FUN_00032ee4(void);
extern int FUN_0007cbfe(void*,int);
extern int sync_to_slave(void*,int,int,int);
extern int FUN_00016940(void);
extern int change_work_mode_to(int);
extern int FUN_000265b8(void*);
typedef int  (*qfn_t)(int,int);
typedef void (*ffn_t)(int,int,void*);
extern i64 FUN_0000d824(int); extern i64 FUN_0000db4c(int,int,int,int); extern i64 FUN_0000d58c(int,int,int,int);
extern i64 FUN_0000d8f8(int,int,int,int); extern i64 FUN_0000d848(int); extern i64 FUN_0000d588(int,int,int,int);
extern int FUN_0000dee8(void);
extern int FUN_000267ac(void*); extern int FUN_00026624(int,int,int,int,int,int,int,void*);
extern int FUN_00026828(void*); extern int FUN_00026808(void*); extern int FUN_000267e8(void*);
extern int FUN_00025ecc(void*); extern int FUN_00025e2c(void);
extern int FUN_0002be64(void*,int); extern int FUN_0003444c(void); extern int FUN_00023eec(void);
extern int FUN_0007cdb6(void*,int); extern int send_event_status(int);
extern int FUN_000167a8(void); extern int FUN_0007ca4e(void*);
extern int FUN_00047b1c(int,int); extern int FUN_00047ba8(void);
extern int FUN_00042fb0(void*,void*);

static inline float as_f(int x){ float f; __builtin_memcpy(&f,&x,4); return f; }

void imu_fusion_thread(char *p)
{
    char *q8 = p - 0xee4;
    unsigned local_a4 = 0;
    int iVar6, iVar27 = 0, cVar2, cnt, d, ad, k, sgn, prev;
    int d1,d2,d3,d7;
    float f7 = 0.0f;
    int uVar7;

    FUN_00086c78(0,0,0x18);
    FUN_00086c78(0,0,0x18);

    if (p[0x14] != 0) {
        if (1 < I(0x2000230c)) { if (I(0x20007554)==0) DEBUG_PRINT(); else FUN_00019c70(); }
        return;
    }
    if (1 < I(0x2000230c)) { if (I(0x20007554)==0) DEBUG_PRINT(); else FUN_00019c70(); }
    p[0] = 1;

    while (p[0x15] != 0) {
        while (p[-0xee3]==1 || p[-0xee3]==8) thunk_FUN_00074844(0x28000,0);

        iVar6 = FUN_00032ee4();
        if (iVar6 == 0) {
            if (p[0x106] == 0x0b) { p[0] = 2; }
            else if (p[0x106] != 0x0c) {
                if ((int)((unsigned)(u16)(*(u16*)(p+0x178)) << 0x1a) < 0) {
                    i64 v = thunk_FUN_00074f68();
                    local_a4 = (unsigned)(((u64)v * 1000ULL) >> 15);
                    if (1000u < (unsigned)(local_a4 - U(0x20007a94))) FUN_000265b8(p+0x28);
                    goto Lffb4;
                }
                p[0] = 1; uVar7 = 0xccd; goto Lff38;
            } else {
                p[0] = 1; FUN_0007cbfe(q8,1);
                if (p[-0xe0f] != 7) {
                    sync_to_slave(q8,1,0,0);
                    if (FUN_00016940() == 2) change_work_mode_to(3);
                }
            }
            uVar7 = 0x8000;
            goto Lff38;
        }

    Lffb4:
        {
            char buf1[24], buf2[24];
            int vobj = *(volatile int*)(p+0x1c);
            int mt   = *(volatile int*)(vobj+8);
            qfn_t qfn = *(qfn_t volatile*)(mt+0xc);
            iVar6 = qfn(vobj, 0x3a);
            if (iVar6 < 0) { uVar7 = 0x290; goto Lff38; }
            vobj = *(volatile int*)(p+0x1c);
            mt   = *(volatile int*)(vobj+8);
            { ffn_t ffn = *(ffn_t volatile*)(mt+0x10); ffn(vobj, 3, buf1); }
            vobj = *(volatile int*)(p+0x1c);
            mt   = *(volatile int*)(vobj+8);
            { ffn_t ffn = *(ffn_t volatile*)(mt+0x10); ffn(vobj, 7, buf2); }
        }

        /* group1 */ FUN_0000d824(0);FUN_0000db4c(0,0,0,0);FUN_0000d824(0);FUN_0000d58c(0,0,0,0);FUN_0000d8f8(0,0,0,0); d1=FUN_0000dee8();
        /* group2 */ FUN_0000d824(0);FUN_0000db4c(0,0,0,0);FUN_0000d824(0);FUN_0000d58c(0,0,0,0);FUN_0000d8f8(0,0,0,0); d2=FUN_0000dee8();
        /* group3 */ FUN_0000d824(0);FUN_0000db4c(0,0,0,0);FUN_0000d824(0);FUN_0000d58c(0,0,0,0);FUN_0000d8f8(0,0,0,0); d3=FUN_0000dee8();
        /* group4 */ FUN_0000d824(0);FUN_0000db4c(0,0,0,0);FUN_0000d824(0);FUN_0000d58c(0,0,0,0); FUN_0000dee8();
        /* group5 */ FUN_0000d824(0);FUN_0000db4c(0,0,0,0);FUN_0000d824(0);FUN_0000d58c(0,0,0,0); FUN_0000dee8();
        /* group6 */ FUN_0000d824(0);FUN_0000db4c(0,0,0,0);FUN_0000d824(0);FUN_0000d58c(0,0,0,0); FUN_0000dee8();

        I(p+0x198) = (int)as_f(d1);
        I(p+0x19c) = (int)as_f(d2);
        I(p+0x1a0) = (int)as_f(d3);

        /* group7 */ FUN_0000d848(0);FUN_0000d588(0,0,0,0); d7=FUN_0000dee8();
        /* group8 */ FUN_0000d848(0);FUN_0000d58c(0,0,0,0); FUN_0000dee8();
        /* group9 */ FUN_0000d848(0);FUN_0000d588(0,0,0,0); FUN_0000dee8();
        FUN_000267ac(p+0x28);
        FUN_00026624(0,0,0,0,0,0,0,p+0x28);
        FUN_00026828(p+0x28); FUN_00026808(p+0x28); FUN_000267e8(p+0x28);

        f7 = as_f(d7);
        iVar27 = (int)(f7 * 100.0f);
        I(0x20007aac) = iVar27;
        I(0x20007aa8) = iVar27;
        I(0x20007aa4) = iVar27;

        iVar6 = FUN_00032ee4();
        if (iVar6 == 1 && p[0x106] == 0x0b) { p[0] = 2; uVar7 = 0x148; goto Lff38; }

        I(0x20007a94) = (int)local_a4;
        cnt = I(0x20007ab4);
        I(0x20007ab4) = cnt + 1;
        if (UB(0x20007ab0) == 0) {
            if ((unsigned)(cnt + 1) < 0xc9) { uVar7 = 0x148; goto Lff38; }
            B(0x20007ab0) = 1;
            F(0x20007acc) = f7; F(0x20007ad0) = f7; F(0x20007ad4) = f7;
        }
        FUN_00025ecc(p);

        if (p[-0xe0f] == 0) {
            d = I(0x20007a90);
            ad = (iVar27 < d) ? d - iVar27 : iVar27 - d;
            if (0x31 < ad) goto L102e0;
            I(0x20007a90) = iVar27;
            I(0x20007a8c) = 0;
            FUN_00025e2c();
            goto L1027a;
        }

    L102e0:
        cVar2 = p[-0xe0f];
        I(0x20007a90) = iVar27;
        if (cVar2 == 0x0d) {
            p[-0xdf7] = 0x0c; p[-0xdf6] = 0;
            *(float*)(p-0xdf5) = f7; *(float*)(p-0xdf1) = f7; *(float*)(p-0xded) = f7;
        }
        I(0x20007aac) = iVar27;
        I(0x20007aa8) = iVar27;
        I(0x20007aa4) = iVar27;

        if (p[0] == 2) {
            if (iVar27 <= *(int*)(p+8) + 100 && *(int*)(p+0xc) <= iVar27) goto L10734;
            iVar6 = I(0x20007a8c) + 1;
            if (iVar6 < 2) goto L1064c;
            I(0x20007a8c) = -3;
            B(0x20018d96) = 1;
            if (I(0x20007554) == 0) DEBUG_PRINT(); else FUN_00019c70();
            send_event_status(3);
            p[0] = 1;
            {
                int e = p[-0xe0f];
                if (e==9||e==0x0c||e==0x0a||e==0x0b||e==7||e==0x0e||e==0x0f||e==0x10||e==0x11
                    || FUN_0002be64(q8, p[-0xe0f]) != 0) {
                    B(0x20018d96) = 0;
                    goto L103ea;
                }
            }
            p[-0xe19] = p[-0xf];
            if (p[-0xe0f] == 1) {
                sync_to_slave(q8,8,0,0);
            } else if (((p[0x1ab]==0) || FUN_0003444c()!=1) && FUN_00023eec()==0) {
                sync_to_slave(q8,1,0,0);
            }
            if (p[0x1ab]==0 && FUN_00023eec()==0) FUN_0007cdb6(q8,0);
            goto L10544;
        }

        if (*(int*)(p+8) < iVar27 || iVar27 < *(int*)(p+0xc)) goto L10734;
        thunk_FUN_00074f68();
        iVar6 = I(0x20007a8c) + 1;
        if (iVar6 < 2) { I(0x20007a8c) = iVar6; goto L1027a; }
        I(0x20007a8c) = -3;
        {
            u8 bv = (u8)p[0x10];
            if (p[-0xe0f]==0 && I(0x20007a88) <= iVar27) goto L1027a;
            B(0x20018d96) = 1;
            if (I(0x20007554)==0) DEBUG_PRINT(); else FUN_00019c70();
            k = 0x65;
            while (1) {
                int iv = FUN_000167a8();
                if (*(char*)(iv + 0x108f) != 0) break;
                if (UB(0x20018d98) == 0) break;
                if (--k == 0) break;
                thunk_FUN_00074844(0x148,0);
            }
            send_event_status(2);
            (void)bv;
        }
        {
            int e = p[-0xe0f];
            if (e==9||e==0x0c||e==0x0a||e==0x0b||e==5||e==4||e==7||e==0x0e||e==0x0f||e==0x10||e==0x11) {
                p[0] = 2; B(0x20018d96)=0; goto L103ea;
            }
        }
        if (FUN_00023eec() == 0) {
            iVar6 = FUN_0007ca4e((void*)0x20007570);
            if ((iVar6 << 0x1e) < 0) {
                /* bit1 set: DAT_00010580/00010584 path */
                iVar6 = FUN_0007ca4e((void*)0x20007aa0);
                if (-1 < (iVar6 << 0x1e)) {
                    iVar6 = FUN_0007ca4e((void*)0x2000756c);
                    if (-1 < (iVar6 << 0x1e) && (FUN_0007ca4e((void*)0x20007570) << 0x1e) < 0) {
                        if (2 < I(0x2000230c)) { if (I(0x20007554)==0) DEBUG_PRINT(); else FUN_00019c70(); }
                        FUN_00047b1c(0,6);
                        FUN_00047ba8();
                        I(0x2000756c) |= 2;
                    }
                }
            } else {
                /* bit1 clear: enter work-mode-2 path */
                p[0] = 2; p[0x102] = 5; p[-0xe19] = p[-0xf];
                if (p[-0xee4] == 1) {
                    if (1 < I(0x2000230c)) { if (I(0x20007554)==0) DEBUG_PRINT(); else FUN_00019c70(); }
                    sync_to_slave(q8,2,0,3);
                    FUN_00042fb0(p-0x20, p-0x2c);
                }
                change_work_mode_to(2);
                iVar6 = FUN_0007ca4e((void*)0x20007aa0);
                if (-1 < (iVar6 << 0x1e)) I(0x20007aa0) |= 2;
            }
        } else {
            p[0] = 2;
        }
        goto L10544;

    L10734:
        {
            int cur = I(0x20007a8c);
            I(0x20007a8c) = (cur < 0) ? cur + 1 : 0;
        }
        goto L103ea;

    L1064c:
        I(0x20007a8c) = iVar6;
        goto L1027a;

    L10544:
        B(0x20018d96) = 0;
        /* fallthrough */
    L1027a:
        if (p[0] == 1 && I(0x20007a8c) <= 0) {
            thunk_FUN_00074f68();
            I(0x20007a88) = iVar27;
        }
        /* fallthrough */
    L103ea:
        {
            float la0 = f7, la1 = f7, la2 = f7;
            float d3f = la0 - F(0x20007acc);
            float d4f = la1 - F(0x20007ad0);
            float d5f = la2 - F(0x20007ad4);
            char c2 = *(char*)0x20007ab1;
            if (c2 == 1) {
                float in[3]; in[0]=la0; in[1]=la1; in[2]=la2;
                for (k = 0; k < 3; k++) {
                    float diff = in[k] - F(0x20007ad8 + 4*k);
                    if (!(__builtin_fabsf(diff) < 180.0f)) {
                        if (diff > 0.0f) diff -= 360.0f; else diff += 360.0f;
                    }
                    /* results are stack-only */
                    (void)diff;
                }
                if (!(__builtin_fabsf(d3f) <= 0.1f) ||
                    !(__builtin_fabsf(d4f) <= 0.1f) ||
                    !(__builtin_fabsf(d5f) <= 0.1f)) {
                    I(0x20007abc) = 0;
                } else {
                    int t = I(0x20007abc);
                    I(0x20007abc) = t + 1;
                    if (4 < t + 1) {
                        B(0x20007ab1) = 2;
                        /* copy local_a0[6..8] (all 0) */
                        I(0x20007ae4) = 0; I(0x20007ae8) = 0; I(0x20007aec) = 0;
                    }
                }
            } else if (c2 == 2) {
                I(0x20007ab8) = 0; I(0x20007abc) = 0;
                I(0x20007ac0) = 0; I(0x20007ac4) = 0; I(0x20007ac8) = 0;
                B(0x20007ab1) = 0;
            } else if (c2 == 0) {
                float in[3]; in[0]=d3f; in[1]=d4f; in[2]=d5f;
                int matched = 0;
                for (k = 0; k < 3; k++) {
                    float x = in[k];
                    float thr = F(0x88a44 + 4*k);
                    if (!(__builtin_fabsf(x) < thr)) {
                        sgn = (x < 0.0f) ? -1 : 1;
                        prev = I(0x20007ac0 + 4*k);
                        I(0x20007ac0 + 4*k) = sgn;
                        if (prev == sgn) matched++;
                    }
                }
                if (matched != 0) {
                    if (I(0x20007ab8) == 0) {
                        F(0x20007ad8) = la0; F(0x20007adc) = la1; F(0x20007ae0) = la2;
                        I(0x20007ab8) = 1;
                    } else {
                        int c = I(0x20007ab8) + 1;
                        I(0x20007ab8) = c;
                        if (4 < c) B(0x20007ab1) = 1;
                    }
                }
            }
            F(0x20007acc) = la0; F(0x20007ad0) = la1; F(0x20007ad4) = la2;
            uVar7 = (p[0] == 2) ? 0x4de : 0xa3e;
        }
    Lff38:
        thunk_FUN_00074844(uVar7,0);
    }

    return;
}

