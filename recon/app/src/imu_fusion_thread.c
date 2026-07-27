/* Reconstructed imu_fusion_thread @ 0xfe88.
 * CFG-directed parity: 8/8 reviewed entry, mode, sensor, fusion,
 * calibration, and event-transition cases. */
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
typedef long long i64; typedef unsigned long long u64;

#define I(a)  (*(volatile int*)(a))
#define U(a)  (*(volatile unsigned*)(a))
#define B(a)  (*(volatile signed char*)(a))
#define UB(a) (*(volatile unsigned char*)(a))
#define F(a)  (*(volatile float*)(a))

extern void DEBUG_PRINT(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);
extern int FUN_00086c78(int,int,int);
extern int FUN_0007ca72(int,int);
extern i64 thunk_FUN_00074f68(void);
extern int FUN_00032ee4(void);
extern int FUN_0007cbfe(void*,int);
extern int sync_to_slave(void*,int,int,int);
extern int FUN_00016940(void);
extern int change_work_mode_to(int);
extern int FUN_000265b8(void*);
typedef int  (*qfn_t)(int,int);
typedef void (*ffn_t)(int,int,void*);
extern u64 FUN_0000d824(int); extern u64 FUN_0000db4c(u32,u32,u32,u32); extern u64 FUN_0000d58c(u32,u32,u32,u32);
extern u64 FUN_0000d8f8(u32,u32,u32,u32); extern u64 FUN_0000d848(u32); extern u64 FUN_0000d588(u32,u32,u32,u32);
extern u32 FUN_0000dee8(u32,u32);
extern float FUN_000267ac(int);
extern void FUN_00026624(float,float,float,float,float,float,float,void*);
extern float FUN_00026828(void*); extern float FUN_00026808(void*); extern float FUN_000267e8(void*);
extern int FUN_00025ecc(void*); extern int FUN_00025e2c(void);
extern int FUN_0002be64(void*,int); extern int FUN_0003444c(void); extern int FUN_00023eec(void);
extern int FUN_0007cdb6(void*,int); extern int FUN_000276ec(int);
extern int FUN_000167a8(void); extern int FUN_0007ca4e(void*);
extern int FUN_00047b1c(int,int); extern int FUN_00047ba8(void);
extern int FUN_00042fb0(void*,void*);

static inline float as_f(u32 x){ float f; __builtin_memcpy(&f,&x,4); return f; }
#define LO64(v) ((u32)(v))
#define HI64(v) ((u32)((v) >> 32))

void imu_fusion_thread(char *p)
{
    char *q8 = p - 0xee4;
    unsigned local_a4 = 0;
    int iVar6, iVar27 = 0, cVar2, cnt, d, ad, k, sgn, prev;
    u32 d1,d2,d3,d4,d5,d6;
    u64 dv, part;
    float roll = 0.0f, pitch = 0.0f, yaw = 0.0f, dt;
    int uVar7;
    char buf1[24];
    char buf2[24];

    FUN_00086c78((int)buf1, 0, 0x18);
    FUN_00086c78((int)buf2, 0, 0x18);

    if (p[0x14] != 0) {
        if (1 < I(0x2000230c)) { if (I(0x20007554)==0) DEBUG_PRINT(((unsigned long)"%s(): error\n\n"),((unsigned long)"imu_fusion_thread")); else FUN_00019c70(((unsigned long)"%s(): error\n\n"),((unsigned long)"imu_fusion_thread")); }
        return;
    }
    if (1 < I(0x2000230c)) { if (I(0x20007554)==0) DEBUG_PRINT(((unsigned long)"%s(): start imu looper\n\n"),((unsigned long)"imu_fusion_thread")); else FUN_00019c70(((unsigned long)"%s(): start imu looper\n\n"),((unsigned long)"imu_fusion_thread")); }
    p[0] = 1;

    while (p[0x15] != 0) {
        while (p[-0xee3]==1 || p[-0xee3]==8) FUN_0007ca72(0x28000,0);

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

        dv = FUN_0000d824(I(buf1 + 4));
        dv = FUN_0000db4c(LO64(dv),HI64(dv),0,0x412e8480);
        part = FUN_0000d824(I(buf1));
        dv = FUN_0000d58c(LO64(dv),HI64(dv),LO64(part),HI64(part));
        dv = FUN_0000d8f8(LO64(dv),HI64(dv),0,0x40240000);
        d1 = FUN_0000dee8(LO64(dv),HI64(dv));

        dv = FUN_0000d824(I(buf1 + 12));
        dv = FUN_0000db4c(LO64(dv),HI64(dv),0,0x412e8480);
        part = FUN_0000d824(I(buf1 + 8));
        dv = FUN_0000d58c(LO64(dv),HI64(dv),LO64(part),HI64(part));
        dv = FUN_0000d8f8(LO64(dv),HI64(dv),0,0x40240000);
        d2 = FUN_0000dee8(LO64(dv),HI64(dv));

        dv = FUN_0000d824(I(buf1 + 20));
        dv = FUN_0000db4c(LO64(dv),HI64(dv),0,0x412e8480);
        part = FUN_0000d824(I(buf1 + 16));
        dv = FUN_0000d58c(LO64(dv),HI64(dv),LO64(part),HI64(part));
        dv = FUN_0000d8f8(LO64(dv),HI64(dv),0,0x40240000);
        d3 = FUN_0000dee8(LO64(dv),HI64(dv));

        dv = FUN_0000d824(I(buf2 + 4));
        dv = FUN_0000db4c(LO64(dv),HI64(dv),0,0x412e8480);
        part = FUN_0000d824(I(buf2));
        dv = FUN_0000d58c(LO64(dv),HI64(dv),LO64(part),HI64(part));
        d4 = FUN_0000dee8(LO64(dv),HI64(dv));

        dv = FUN_0000d824(I(buf2 + 12));
        dv = FUN_0000db4c(LO64(dv),HI64(dv),0,0x412e8480);
        part = FUN_0000d824(I(buf2 + 8));
        dv = FUN_0000d58c(LO64(dv),HI64(dv),LO64(part),HI64(part));
        d5 = FUN_0000dee8(LO64(dv),HI64(dv));

        dv = FUN_0000d824(I(buf2 + 20));
        dv = FUN_0000db4c(LO64(dv),HI64(dv),0,0x412e8480);
        part = FUN_0000d824(I(buf2 + 16));
        dv = FUN_0000d58c(LO64(dv),HI64(dv),LO64(part),HI64(part));
        d6 = FUN_0000dee8(LO64(dv),HI64(dv));

        I(p+0x198) = (int)as_f(d1);
        I(p+0x19c) = (int)as_f(d2);
        I(p+0x1a0) = (int)as_f(d3);

        dv = FUN_0000d848(d4);
        dv = FUN_0000d588(LO64(dv),HI64(dv),0x45a1cac1,0x3fadf3b6);
        d4 = FUN_0000dee8(LO64(dv),HI64(dv));
        dv = FUN_0000d848(d5);
        dv = FUN_0000d58c(LO64(dv),HI64(dv),0x0a3d70a4,0x3fa0a3d7);
        d5 = FUN_0000dee8(LO64(dv),HI64(dv));
        dv = FUN_0000d848(d6);
        dv = FUN_0000d588(LO64(dv),HI64(dv),0x47ae147b,0x3f847ae1);
        d6 = FUN_0000dee8(LO64(dv),HI64(dv));

        dt = FUN_000267ac(p+0x28);
        FUN_00026624(as_f(d4),as_f(d5),as_f(d6),
                     as_f(d1),as_f(d2),as_f(d3),dt,p+0x28);
        roll = FUN_00026828(p+0x28);
        pitch = FUN_00026808(p+0x28);
        yaw = FUN_000267e8(p+0x28);

        iVar27 = (int)(pitch * 100.0f);
        I(0x20007aac) = iVar27;
        I(0x20007aa8) = (int)(roll * 100.0f);
        I(0x20007aa4) = (int)(yaw * 100.0f);

        iVar6 = FUN_00032ee4();
        if (iVar6 == 1 && p[0x106] == 0x0b) { p[0] = 2; uVar7 = 0x148; goto Lff38; }

        I(0x20007a94) = (int)local_a4;
        cnt = I(0x20007ab4);
        I(0x20007ab4) = cnt + 1;
        if (UB(0x20007ab0) == 0) {
            if ((unsigned)(cnt + 1) < 0xc9) { uVar7 = 0x148; goto Lff38; }
            B(0x20007ab0) = 1;
            F(0x20007acc) = roll; F(0x20007ad0) = pitch; F(0x20007ad4) = yaw;
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
            *(float*)(p-0xdf5) = roll; *(float*)(p-0xdf1) = pitch; *(float*)(p-0xded) = yaw;
        }
        I(0x20007aac) = iVar27;
        I(0x20007aa8) = (int)(roll * 100.0f);
        I(0x20007aa4) = (int)(yaw * 100.0f);

        if (p[0] == 2) {
            if (iVar27 <= *(int*)(p+8) + 100 && *(int*)(p+0xc) <= iVar27) goto L10734;
            iVar6 = I(0x20007a8c) + 1;
            if (iVar6 < 2) goto L1064c;
            I(0x20007a8c) = -3;
            B(0x20018d96) = 1;
            if (I(0x20007554) == 0) DEBUG_PRINT(((unsigned long)"bow head################################################\n")); else FUN_00019c70(((unsigned long)"bow head################################################\n"));
            FUN_000276ec(3);
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
            if (I(0x20007554)==0) DEBUG_PRINT(((unsigned long)"look up################################################,screen_id is %d, pitch_y is %d, pitch_threshold_bow_head is %d, pitch_threshold_level is %d\n"),p[-0xe0f],iVar27,*(int*)(p+8),bv); else FUN_00019c70(((unsigned long)"look up################################################,screen_id is %d, pitch_y is %d, pitch_threshold_bow_head is %d, pitch_threshold_level is %d\n"),p[-0xe0f],iVar27,*(int*)(p+8),bv);
            k = 0x65;
            while (1) {
                int iv = FUN_000167a8();
                if (*(char*)(iv + 0x108f) != 0) break;
                if (UB(0x20018d98) == 0) break;
                if (--k == 0) break;
                FUN_0007ca72(0x148,0);
            }
            FUN_000276ec(2);
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
                        if (2 < I(0x2000230c)) { if (I(0x20007554)==0) DEBUG_PRINT(((unsigned long)"%s(): send dashboard lock info to app ,status = %d \n"),((unsigned long)"handle_attitude_trigger"),1); else FUN_00019c70(((unsigned long)"%s(): send dashboard lock info to app ,status = %d \n"),((unsigned long)"handle_attitude_trigger"),1); }
                        FUN_00047b1c(0,6);
                        FUN_00047ba8();
                        I(0x2000756c) |= 2;
                    }
                }
            } else {
                /* bit1 clear: enter work-mode-2 path */
                p[0] = 2; p[0x102] = 5; p[-0xe19] = p[-0xf];
                if (p[-0xee4] == 1) {
                    if (1 < I(0x2000230c)) { if (I(0x20007554)==0) DEBUG_PRINT(((unsigned long)"%s(): master sync canvas_distance_gear:%d,raster_height_gear:%d\n"),((unsigned long)"handle_attitude_trigger"),p[-0x23],p[-0x24]); else FUN_00019c70(((unsigned long)"%s(): master sync canvas_distance_gear:%d,raster_height_gear:%d\n"),((unsigned long)"handle_attitude_trigger"),p[-0x23],p[-0x24]); }
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
            float la0 = roll, la1 = pitch, la2 = yaw;
            float corrected[3] = {0.0f, 0.0f, 0.0f};
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
                    corrected[k] = F(0x20007ae4 + 4*k) + diff;
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
                        F(0x20007ae4) = corrected[0];
                        F(0x20007ae8) = corrected[1];
                        F(0x20007aec) = corrected[2];
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
        FUN_0007ca72(uVar7,0);
    }

    return;
}
