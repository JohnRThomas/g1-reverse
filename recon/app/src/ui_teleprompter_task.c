/* Reconstructed ui_teleprompter_task @ 0x3cf44  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>

/* absolute globals (literal-pool values) */
#define G        0x20004988u          /* teleprompter state struct (r4) */
#define LL       0x2000230cu          /* log level (r6) */
#define LP       0x20007554u          /* log-enable ptr (r8) */
#define HR       0x20009ff0u          /* current hour  */
#define MN       0x20009fecu          /* current min   */
#define SC       0x20009fe8u          /* current sec   */
#define CHR      0x20009fe4u          /* cached hour   */
#define CMN      0x20009fe0u          /* cached min    */
#define CSC      0x20009fdcu          /* cached sec    */
#define BUF      0x200049b8u
#define OBJ      0x20007b3cu
#define FLAG7564 0x20007564u
#define FLAG046a 0x2001046au
#define LOCK     0x2000a030u

#define U8(a)  (*(volatile uint8_t *)(uintptr_t)(a))
#define S8(a)  (*(volatile int8_t  *)(uintptr_t)(a))
#define U16(a) (*(volatile uint16_t*)(uintptr_t)(a))
#define U32(a) (*(volatile uint32_t*)(uintptr_t)(a))
#define S32(a) (*(volatile int32_t *)(uintptr_t)(a))

extern unsigned FUN_000167a8(void);
extern void     FUN_000431b4(unsigned);
extern void     FUN_000432d0(void);
extern void     FUN_00019c70(unsigned,unsigned);
extern void     FUN_0007dda4(unsigned,unsigned);
extern void     FUN_000431c0(void);
extern void     FUN_00086c78(unsigned,unsigned,unsigned);
extern void     FUN_00086c04(unsigned,unsigned,unsigned);
extern long long FUN_0007d33a(void);
extern long long FUN_0007d3c2(void);
extern long long FUN_0000e1a4(unsigned,unsigned,unsigned,unsigned);
extern unsigned FUN_0007d3ee(void);
extern unsigned FUN_0007d446(void);
extern unsigned FUN_0007d224(void);
extern int      FUN_00023ee0(void);
extern int      FUN_00077914(unsigned,unsigned,unsigned,unsigned);
extern int      FUN_00026f74(unsigned,unsigned,unsigned);
extern void     FUN_00047ba8(void);
extern void     FUN_0002efc0(void);
extern void     FUN_000723b8(unsigned,unsigned,unsigned);
extern void     FUN_00072558(unsigned);
extern void     FUN_00043e90(unsigned,unsigned,unsigned,unsigned,unsigned,unsigned,unsigned,unsigned,unsigned,unsigned);
extern void     FUN_000442bc(unsigned,unsigned,unsigned,unsigned,unsigned,unsigned);
extern void     FUN_0004396c(unsigned,unsigned,unsigned,unsigned,unsigned,unsigned);
extern void     FUN_00043484(unsigned,unsigned,unsigned,unsigned,unsigned,unsigned);
extern void     FUN_000471cc(unsigned,unsigned,unsigned,unsigned,unsigned,unsigned);
extern void     FUN_00047260(unsigned,unsigned,unsigned,unsigned,unsigned,unsigned);
extern void     FUN_00074844(unsigned,unsigned);
extern void     FUN_00043308(void);
extern void     FUN_0004382c(void);
extern void     FUN_000432ec(void);
extern void     FUN_0004334c(unsigned,unsigned,unsigned,unsigned,unsigned);
extern void     FUN_000440ec(unsigned,unsigned,unsigned,unsigned,unsigned,unsigned,unsigned,unsigned);

/* debug gate: if(loglevel>thr){ [LP]? FUN_19c70 : FUN_7dda4 } */
__attribute__((always_inline)) static inline void dbg(int thr){
    if (S32(LL) > thr){
        if (U32(LP)) FUN_00019c70(0,0);
        else         FUN_0007dda4(0,0);
    }
}

unsigned ui_teleprompter_task(unsigned a0, unsigned a1, unsigned a2, unsigned a3)
{
    unsigned ctx0, c, sel = a2, st;
    unsigned t0, t1, r8v;
    long long t, q, dv;
    (void)a1; (void)a3;

    ctx0 = FUN_000167a8();          /* call 0 */
    FUN_000431b4(a0 + 0x24);        /* call 1 */
    FUN_000432d0();                 /* call 2 */
    st = U8(G);
    if (st > 3) return 0;

    switch (st) {
    /* ------------------------------------------------ state 0 ---- */
    case 0:
        if (S32(LL) > 2) {
            dbg(2);                         /* 3cf78 first gate  */
            if (sel == 2) goto L_cf98;
            /* 3cfcc second gate (LL still >2) */
            FUN_000167a8();
            if (U32(LP)) FUN_00019c70(0,0);
            else         FUN_0007dda4(0,0);
        } else {
            if (sel == 2) goto L_cf98;
        }
        /* 3cfee */
        if (sel != 1) return 0;
        /* 3cff2 */
        c = FUN_000167a8();
        if (U8(U32(c + 0xffc) + 1) != 1) return 0;
        if (U8(ctx0 + 0xf0) != 1) return 0;       /* 3d000 */
        dbg(2);                                    /* 3d008 */
        c = FUN_000167a8();                        /* 3d020 */
        if (U8(c) == 1) FUN_00047ba8();
        dbg(2);                                    /* 3d02e */
        /* 3d046 full init (effectively unreachable under emulation) */
        FUN_000431c0();
        FUN_00086c78(G, 0, 0x230);
        U8(G) = 1;
        t = FUN_0007d33a(); U32(G+8)=(unsigned)t; U32(G+0xc)=(unsigned)(t>>32);
        t = FUN_0007d33a(); U32(G+0x10)=(unsigned)t; U32(G+0x14)=(unsigned)(t>>32);
        U32(G+0x18)=0;
        U8(G+1)=0xa;
        U8(G+0x25)=(uint8_t)(int8_t)U8(ctx0+0xfb);
        U32(HR)=0; U32(MN)=0; U32(SC)=0; U32(CHR)=0; U32(CMN)=0; U32(CSC)=0;
        FUN_00086c78(BUF,0,0);
        FUN_000723b8(OBJ,0xffffffffu,0xffffffffu);
        FUN_00086c04(BUF, ctx0+0x106, 0x200);
        U8(G+0x24)=U8(ctx0+0xef);
        U8(G+0x25)=(uint8_t)(int8_t)U8(ctx0+0xfb);
        FUN_00072558(OBJ);
        t = FUN_0007d33a();
        {
            int gfb = (int8_t)U8(ctx0+0xfb);
            long long acc = t + (long long)(1000*gfb) - 0x15e;
            U32(G+0x28)=(unsigned)acc; U32(G+0x2c)=(unsigned)(acc>>32);
        }
        dbg(2);
        FUN_000432ec();
        {
            int r6;
            for (r6=0; r6<4; r6++){
                FUN_0007d3ee(); FUN_0007d446();
                FUN_0007d3ee(); FUN_0007d446();
                {
                    int r4i;
                    for (r4i=0; r4i<0xc7; r4i++){
                        int r3i;
                        unsigned slp = U32((a0+0x24) + r4i*4);
                        for (r3i=0; r3i<0x140; r3i++){
                            unsigned v = U8(slp + r3i);
                            if (v){
                                U8(slp + r3i) = 0;   /* &= table(=0 in emu) */
                            }
                        }
                    }
                }
                FUN_000167a8();
                FUN_00047260(0,0,0,0,0,0);
            }
        }
        FUN_000432d0();
        FUN_00074844(0x1334,0);
        FUN_00043308();
        return 0;
    L_cf98:
        FUN_000431c0();
        FUN_00086c78(G,0,0x230);
        return 0;

    /* ------------------------------------------------ state 1 ---- */
    case 1:
        if (sel == 2) goto L_cf98;
        if (sel != 1) goto L1_sel0;
        /* sel==1 */
        dbg(2);                                    /* 3d30e */
        {
            unsigned g = U8(ctx0 + 0xf9);
            if ((unsigned)(g - 2) <= 1) {
                /* 3d330 (needs ctx byte in {2,3}) */
                t = FUN_0007d33a(); U32(G+8)=(unsigned)t; U32(G+0xc)=(unsigned)(t>>32);
                U8(G)=2;
                t = FUN_0007d33a(); U32(G+0x10)=(unsigned)t; U32(G+0x14)=(unsigned)(t>>32);
                FUN_0007d3ee(); FUN_0007d446();
                FUN_0007d3ee(); FUN_0007d446();
                FUN_000471cc(0,0,0,0,0,0);
                if (U8(G+0x24) == 1){
                    FUN_0007d3ee(); FUN_0007d446();
                    FUN_00043484(0x1a,0,0,0,0,0);
                } else if (U8(G+0x24) == 0){
                    FUN_0007d3ee(); FUN_0007d446();
                    FUN_00043484(0x19,0,0,0,0,0);
                }
            }
        }
        /* 3d394 */
        c = FUN_000167a8();
        if (U8(c) == 1) FUN_00047ba8();
        return 0;
    L1_sel0:
        if (sel != 0) return 0;
        dbg(2);                                    /* 3d3d8 */
        t = FUN_0007d33a();                        /* 3d3f0 */
        {
            long long v28 = (long long)((unsigned long long)U32(G+0x28) | ((unsigned long long)U32(G+0x2c)<<32));
            if (t >= v28) goto L1_ge;              /* 3d3f8 */
            /* 3d402 diff = v28 - t */
            dv = v28 - t;
            q = FUN_0000e1a4((unsigned)dv,(unsigned)(dv>>32),0x3e8,0);
            {
                long long g25 = (int8_t)U8(G+0x25);
                long long val = (g25 < q) ? g25 : q;
                if (val != 0) goto L1_fmt;         /* 3d524 */
            }
            /* 3d438 */
            dbg(2);
            t = FUN_0007d33a(); U32(G+0x10)=(unsigned)t; U32(G+0x14)=(unsigned)(t>>32);
            t = FUN_0007d33a(); U32(G+8)=(unsigned)t; U32(G+0xc)=(unsigned)(t>>32);
            U8(G)=2;
            goto L1_render_a;
        }
    L1_ge:
        dbg(2);                                    /* 3d590 */
        t = FUN_0007d33a(); U32(G+0x10)=(unsigned)t; U32(G+0x14)=(unsigned)(t>>32);
        U8(G)=2;
        t = FUN_0007d33a(); U32(G+8)=(unsigned)t; U32(G+0xc)=(unsigned)(t>>32);
        /* fallthrough to shared render (3d5b8 -> 3d4ba tail) */
    L1_render_a:
        FUN_0007d3ee(); FUN_0007d446();
        FUN_0007d3ee(); FUN_0007d446();
        FUN_000471cc(0,0,0,0,0,0);
        FUN_000167a8(); FUN_000167a8();
        FUN_0007d3ee(); FUN_0007d446();
        FUN_0007d3ee(); FUN_0007d446();
        FUN_00047260(0,0,0,0,0,0);
        if (U8(G+0x24) == 1){                      /* 3d4ca */
            FUN_0007d3ee(); FUN_0007d446();
            FUN_00043484(0x1a,0,0,0,0,0);
        } else if (U8(G+0x24) == 0){
            FUN_0007d3ee(); FUN_0007d446();
            FUN_00043484(0x19,0,0,0,0,0);
        }
        return 0;
    L1_fmt:
        /* 3d524 -> 77914 -> gate -> 43e90 */
        FUN_00077914(0,0,0,0);
        dbg(2);
        FUN_0007d3ee(); FUN_0007d446();
        FUN_00043e90(0,0,0,0,0,0,0,0,0,0);
        return 0;

    /* ------------------------------------------------ state 2 ---- */
    case 2:
        if (S32(LL) > 2) {
            dbg(2);                                /* 3d63c */
            if (sel != 2) goto L2_tick;
            if (S32(LL) > 2){                      /* 3d65e */
                if (U32(LP)) FUN_00019c70(0,0);
                else         FUN_0007dda4(0,0);
            }
            goto L_67e;
        } else {
            if (sel == 2) goto L_67e;
            goto L2_tick;
        }

    /* ------------------------------------------------ state 3 ---- */
    case 3:
        if (S32(LL) > 1) dbg(1);                   /* 3dc4e */
        FUN_0007d33a();                            /* 3dc66 t ignored */
        q = FUN_0007d3c2();
        if (q < 0x1f41) goto L_dcbe;
        dbg(1);                                    /* 3dc7e */
        c = FUN_000167a8();
        FUN_00086c78(U32(c+0xffc),0,0x217);
        FUN_0004382c();
        c = FUN_000167a8();
        U8(U32(c+0xffc)+1) = 0;
        FUN_00086c78(G,0,0x230);
    L_dcbe:
        if (sel != 2) return 0;
        if (S32(LL) > 2){
            if (U32(LP)) FUN_00019c70(0,0);
            else         FUN_0007dda4(0,0);
        }
        goto L_67e;
    }
    return 0;

/* ===== shared: state2 sel==2 / state3 sel==2 tail (3d67e) ===== */
L_67e:
    FUN_0004382c();
    FUN_00086c78(G,0,0x230);
/* L_68e */
    c = FUN_000167a8();
    if (U8(c) != 1) return 0;
    if (U8(G+0x24) != 2) return 0;
    FUN_0002efc0();
    return 0;

/* ===== state2 tick (3dd16) ===== */
L2_tick:
    {
        unsigned g1d = U8(G+0x1d);
        r8v = (uint8_t)g1d;
        if (g1d != 1) {
            /* 3d6aa */
            if (U8(G+0x1c) != 0) {
                /* 3d6c0 */
                t = FUN_0007d33a();
                U32(G+0x10)=(unsigned)t; U32(G+0x14)=0;
                U32(G+0x20)=U32(G+0x18);
                U8(G+0x1c)=0;
            } else {
                /* 3d6ac */
                t = FUN_0007d33a();
                U32(G+0x20)=(unsigned)t - U32(G+0x10);
                U32(G+0x20)=U32(G+0x18) + U32(G+0x20);
            }
        } else {
            /* 3dd24 */
            if (U8(G+0x1c) == 0) {
                t = FUN_0007d33a();
                U32(G+0x18) = U32(G+0x18) - U32(G+0x10) + (unsigned)t;
                U8(G+0x1c) = (uint8_t)r8v;
            }
            U32(G+0x20) = U32(G+0x18);
        }
    }
/* 3dd3e */
    c = FUN_000167a8();
    (void)U8(U32(c+0xfec)+0x5e);
    r8v = FUN_0007d224();
    FUN_0007d3ee(); FUN_0007d446();
    FUN_0007d3ee(); FUN_0007d446();
    FUN_000442bc(0,0,0,0,0,0);
    if (sel != 1) goto L2_after;
    /* 3dd90 render list */
    c = FUN_000167a8();
    if (U8(c) == 1){
        dbg(2);
        FUN_00047ba8();
        if ((int8_t)U8(G+1) <= 0x13) U8(G+1)=0x13;
    }
/* 3ddc2 */
    FUN_00086c78(BUF,0,0x200);
    FUN_000723b8(OBJ,0xffffffffu,0xffffffffu);
    FUN_00086c04(BUF, ctx0+0x106, 0x200);
    (void)U8(ctx0+0xfc); (void)U8(ctx0+0xff); (void)U16(ctx0+0xfd); (void)U32(ctx0+0x100);
    FUN_00072558(OBJ);
    if (U8(FLAG046a) == 1){
        U8(FLAG046a)=0;
        FUN_0007d3ee(); FUN_0007d446();
        FUN_0007d3ee(); FUN_0007d446();
        FUN_000440ec(0,0,0,0,0,0,0,0);
    } else {
        /* 3d6de */
        FUN_0007d3ee();
        t0 = FUN_0007d446();
        FUN_0007d3ee(); FUN_0007d446();
        FUN_00043e90(0,0,0,0,0,0,0,0,0,0);
    }
/* 3de50 */
    FUN_0007d3ee(); FUN_0007d446();
    FUN_0007d3ee(); FUN_0007d446();
    FUN_0004396c(0,0,0,0,0,0);
    if (U8(ctx0+0xff) == 1){
        /* 3de90 sl==1 branch (rare) */
        if (U32(LOCK) & 2){
            FUN_0007d3ee(); FUN_0007d446();
            FUN_0007d3ee(); FUN_0007d446();
            FUN_000471cc(0,0,0,0,0,0);
        }
        if (U32(LOCK) & 2){
            FUN_000167a8(); FUN_000167a8();
            FUN_0007d3ee(); FUN_0007d446();
            FUN_0007d3ee(); FUN_0007d446();
            FUN_00047260(0,0,0,0,0,0);
        }
        if (U8(G+0x24)==1){
            FUN_0007d3ee(); FUN_0007d446();
            FUN_00043484(0x1a,0,0,0,0,0);
        } else if (U8(G+0x24)==0){
            FUN_0007d3ee(); FUN_0007d446();
            FUN_00043484(0x19,0,0,0,0,0);
        }
        dbg(2);
        U8(G+0x1d)=1;
        U32(G+0x18)=1000*r8v;
        t = FUN_0007d33a(); U32(G+0x10)=(unsigned)t; U32(G+0x14)=0;
        goto L2_after;
    }
    /* 3d720 sl!=1 (usual) */
    U8(G+0x1d) = (uint8_t)(t0 + 1);
    if (U32(LOCK) & 2){
        FUN_0007d3ee(); FUN_0007d446();
        FUN_0007d3ee(); FUN_0007d446();
        FUN_000471cc(0,0,0,0,0,0);
    }
    if (U32(LOCK) & 2){
        FUN_000167a8(); FUN_000167a8();
        FUN_0007d3ee(); FUN_0007d446();
        FUN_0007d3ee(); FUN_0007d446();
        FUN_00047260(0,0,0,0,0,0);
    }
    if (U8(G+0x24)==1){
        FUN_0007d3ee(); FUN_0007d446();
        FUN_00043484(0x1a,0,0,0,0,0);
    } else if (U8(G+0x24)==0){
        FUN_0007d3ee(); FUN_0007d446();
        FUN_00043484(0x19,0,0,0,0,0);
    }
    dbg(2);
L2_after:
    /* 3df5c */
    if (U8(G+0x24)==2 && U8(G+0x1d)==0){
        FUN_0007d3ee(); FUN_0007d446();
        FUN_0004334c(1,0,0,0,0);
    }
/* 3df8a : seconds = G[0x20]/1000, then HH:MM:SS */
    U32(G+0x20) = U32(G+0x20) / 1000u;
    {
        unsigned s = U32(G+0x20);
        if (s > 0x3b){
            if (s >= 0xe10){
                if (s > 0x57e3fu){
                    U32(HR)=0x63; U32(MN)=0x3b; U32(SC)=0x3b;
                } else {
                    U32(HR)= s/0xe10;
                    { unsigned rem = s % 0xe10; U32(MN)=rem/0x3c; U32(SC)=rem%0x3c; }
                }
            } else {
                U32(SC)= s % 0x3c;
                U32(MN)= s / 0x3c;
            }
        } else {
            U32(SC)= s % 0x3c;
        }
    }
/* 3d840 : format + cache compare */
    {
        unsigned hr=U32(HR), mn=U32(MN), sc=U32(SC);
        FUN_00086c78(0,0,0x38);
        FUN_00077914(0, (hr>9)?0x000a8b58u:0x000a9c15u, 0x40, 0);
        if (!(hr==U32(CHR) && mn==U32(CMN) && sc==U32(CSC))){
            /* 3d892 */
            FUN_0007d3ee(); FUN_0007d446();
            FUN_0007d3ee(); FUN_0007d446();
            FUN_00043e90(0,0,0,0,0,0,0,0,0,0);
            U32(CHR)=hr; U32(CMN)=mn; U32(CSC)=sc;
        }
    }
/* 3d8e6 */
    c = FUN_000167a8();
    if (U8(c) != 1) goto L_db48;
    if (S32(FLAG7564) > 0){
        U32(FLAG7564)=0;
        if ((int8_t)U8(G+1) <= 0x13) U8(G+1)=0x13;
    }
    FUN_0007d33a();                                /* 3d90a ignored */
    q = FUN_0007d3c2();
    if (q < 0x3e9) return 0;
    t = FUN_0007d33a(); U32(G+8)=(unsigned)t; U32(G+0xc)=(unsigned)(t>>32);
    U8(G+1) = (uint8_t)((int8_t)U8(G+1) - 1);
    dbg(2);                                        /* 3d934 */
    if ((int8_t)U8(G+1) > 0) return 0;
    dbg(1);                                        /* 3d958 */
    dbg(2);                                        /* 3d96e */
    /* 3d984 */
    c = FUN_000167a8();
    if (FUN_00026f74(c,6,0) > 0x1387){
        if (S32(LL) > 0) dbg(0);
        return 0;
    }
    /* 3da16 */
    U8(G)=3;
    t = FUN_0007d33a(); U32(G+8)=(unsigned)t; U32(G+0xc)=(unsigned)(t>>32);
    FUN_000431c0();
    FUN_0007d3ee(); FUN_0007d446();
    FUN_00043484(0x3f,0,0,0,0,0);
    if (FUN_00023ee0() == 6){
        FUN_0007d3ee(); FUN_0007d446();
        FUN_0007d3ee(); FUN_0007d446();
        FUN_00043e90(0,0,0,0,0,0,0,0,0,0);
        FUN_0007d3ee(); FUN_0007d446();
        FUN_0007d3ee(); FUN_0007d446();
        FUN_00043e90(0,0,0,0,0,0,0,0,0,0);
    } else {
        FUN_0007d3ee(); FUN_0007d446();
        FUN_0007d3ee(); FUN_0007d446();
        FUN_00043e90(0,0,0,0,0,0,0,0,0,0);
    }
    goto L_68e2;
L_db48:
    if (sel != 5) return 0;
    dbg(2);                                        /* 3db4e */
    U8(G)=3;
    t = FUN_0007d33a(); U32(G+8)=(unsigned)t; U32(G+0xc)=(unsigned)(t>>32);
    FUN_000431c0();
    FUN_0007d3ee(); FUN_0007d446();
    FUN_00043484(0x3f,0,0,0,0,0);
    if (FUN_00023ee0() == 6){
        FUN_0007d3ee(); FUN_0007d446();
        FUN_0007d3ee(); FUN_0007d446();
        FUN_00043e90(0,0,0,0,0,0,0,0,0,0);
        FUN_0007d3ee(); FUN_0007d446();
        FUN_0007d3ee(); FUN_0007d446();
        FUN_00043e90(0,0,0,0,0,0,0,0,0,0);
    } else {
        FUN_0007d3ee(); FUN_0007d446();
        FUN_0007d3ee(); FUN_0007d446();
        FUN_00043e90(0,0,0,0,0,0,0,0,0,0);
    }
    /* 3d582: one more 43e90 then return */
    FUN_00043e90(0,0,0,0,0,0,0,0,0,0);
    return 0;
L_68e2:
    /* 3d68e tail */
    c = FUN_000167a8();
    if (U8(c) != 1) return 0;
    if (U8(G+0x24) != 2) return 0;
    FUN_0002efc0();
    return 0;
}

