#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0002955c @ 0x0002955c
 * public-name: key_event_thread
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_touch_key_reset_reason                 @ 0x20007b18
 *   g_touch_key_press_active                 @ 0x20018d89
 *   g_20018d95                               @ 0x20018d95
 *   g_20018d96                               @ 0x20018d96
 *   g_esb_notify_sync_substate               @ 0x20018d98
 */
/* Reconstructed key_event_thread @ 0x2955c  (parity: 2/2 trials, PROVEN) */
typedef unsigned char u8;

/* callees (opaque oracles; order-keyed) */
extern void f2953c(void);
extern int  f167a8(void);
extern void thunk74844(void);
extern int  thunk72908(void);
extern void fun19c70(void);
extern void dbg_print(void);
extern void f276ec(void);
extern int  f42c8c(void);
extern int  f370b0(void);
extern void f37060(void);
extern void f370bc(void);
extern void f3719c(void);
extern int  sync_to_slave(void);
extern void f49938(void);
extern void thunk745c8(void);
extern int  f33cdc(void);
extern void f7cb8e(void);
extern int  f2c3dc(void);
extern int  f23eec(void);
extern void f1694c(void);
extern int  f27448(void);
extern void f3441c(void);
extern void f3443c(void);
extern void f7cb54(void);
extern void f7cbfe(void);
extern void f2c0e8(void);
extern void f498c0(void);
extern void f7d2f8(void);
extern void f7cb4c(void);
extern int  f26c28(void);
extern int  f7ce00(void);
extern void f7ce60(void);
extern void f7cdb6(void);
extern void f2bef4(void);

#define SINK  (*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)
#define DBG   (*(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/)
#define ST    (*(volatile int*)((unsigned long)&g_touch_key_reset_reason) /*=0x20007b18*/)
#define G_D95 (*(volatile u8*)((unsigned long)&g_20018d95) /*=0x20018d95*/)
#define G_D96 (*(volatile u8*)((unsigned long)&g_20018d96) /*=0x20018d96*/)
#define G_D98 (*(volatile u8*)((unsigned long)&g_esb_notify_sync_substate) /*=0x20018d98*/)
#define G_D89 (*(volatile u8*)((unsigned long)&g_touch_key_press_active) /*=0x20018d89*/)

#define LOG() do { if (SINK==0) dbg_print(); else fun19c70(); } while (0)

void key_event_thread(u8 *p, unsigned int a2, unsigned int a3)
{
    int state, r8val = 0, r7 = 0, d, s;
    u8 *q, *A, *B, b;
    (void)a2; (void)a3;

    f2953c();

 L2956e:
    A = (u8*)f167a8();
    if (*(volatile u8*)(A+1) == 1) { L29578: thunk74844(); goto L2956e; }
    B = (u8*)f167a8();
    if (*(volatile u8*)(B+1) == 8) goto L29578;
    if (thunk72908() != 0) goto L297ea;
    if (DBG > 0) LOG();
    state = ST;
    if (state != 1) goto L297f2;

    /* ---- state == 1 ---- */
    q = *(u8**)(p+0x1014);
    if (*(volatile u8*)q == 0) goto L2963e;
    f276ec();
    q = *(u8**)(p+0x1014);
    b = *(volatile u8*)(q+2);
    if (b == 5) {
        A = (u8*)f167a8();
        if (*(volatile u8*)A != 2) goto L2956e;
        r8val = 0x13; goto L295f2;
    } else if (b == 0x13) {
        A = (u8*)f167a8();
        if (*(volatile u8*)A != 2) goto L2956e;
        r8val = 0x14; goto L295f2;
    } else if (b == 0x14) {
        A = (u8*)f167a8();
        if (*(volatile u8*)A != 1) goto L2956e;
        q = *(u8**)(p+0x1014);
        *(volatile u8*)(q+2) = 0x15;
        goto L2956e;
    } else {
        goto L2956e;
    }

 L295f2:
    if (f42c8c() == 0) {
        q = *(u8**)(p+0x1014);
        *(volatile u8*)(q+2) = (u8)r8val;
    }
    goto L2956e;

 L2963e:
    b = *(volatile u8*)(*(u8**)(p+0x100c));
    if ((unsigned)b - 7u <= 4u) goto L29652;
    b = *(volatile u8*)(*(u8**)(p+0x101c));
    if (b == 0) {
        b = *(volatile u8*)(*(u8**)(p+0xffc) + 1);
        if (b != 0) f276ec();
        goto L29668;
    }
 L29652:
    f276ec();
    goto L2956e;

 L29668:
    if (*(volatile u8*)p != 1) goto L29796;
    if (*(volatile u8*)(p+0xd5) != 6) goto L297ea;
    if (DBG > 2) LOG();
    d = f370b0();
    if (d == 0) { if (DBG > 3) LOG(); f37060(); goto L296c8; }
    if (d == 1) { if (DBG > 3) LOG(); f370bc(); goto L296c8; }
    if (d == 2) { if (DBG > 3) LOG(); f3719c(); goto L296c8; }
    goto L296c8;
 L296c8:
    s = sync_to_slave();
    if (s <= 4999) goto L29766;
    if (DBG > 1) LOG();
    goto L297ea;
 L29766:
    if (DBG > 3) LOG();
    f49938();
 L29786:
    thunk745c8();
    goto L297ea;

 L29796:
    if (*(volatile u8*)p != 2) goto L297ea;
    if (f33cdc() == 0) goto L297ea;
    {
        u8 pf = *(volatile u8*)(p+0x108f);
        u8 dd = *(volatile u8*)(p+0xd5);
        if (pf != 0 && dd <= 1) { /* ->loop */ }
        else if (dd == 6 || dd == 4) { /* ->loop */ }
        else goto L297ea;
    }
    /* L297be wait-loop */
    goto L297cc;
 L297c4:
    f7cb8e();
    r7 = r7 + 1;
 L297cc:
    if (*(volatile u8*)(p+0x108f) != 0) goto L297e2;
    if (G_D98 == 0) goto L297e2;
    if (r7 <= 0x63) goto L297c4;
    r7 = r7 + 1;
 L297e2:
    if (f2c3dc() < 0) goto L297cc;
    goto L297ea;

 L297ea:
    ST = 0;
    goto L2956e;

 L297f2:
    switch ((unsigned)(state - 2)) {
        case 0: goto L29834;
        case 1: goto L29cae;
        case 2: goto L29d6e;
        case 3: goto L29fd8;
        case 4: goto L29f36;
        default: goto L297ea;
    }

    /* ================= case 0 : state == 2 ================= */
 L29834:
    if (*(volatile u8*)(*(u8**)(p+0x1014)) != 0) { f276ec(); goto L2956e; }
    if (*(volatile u8*)(p+0xd5) == 7) goto L2956e;
    if (f23eec() != 1) goto L29912;
    if (*(volatile u8*)(p+0xd5) != 0) goto L29912;
    if (*(volatile u8*)p != 1) goto L298dc;
    A = (u8*)f167a8(); *(volatile u8*)(A+0xfe6) = 5;
    B = (u8*)f167a8();
    A = (u8*)f167a8();
    b = *(volatile u8*)(B+0xed5);
    *(volatile u8*)(A+0xcb) = b;
    f167a8();
    sync_to_slave();
    f1694c();
    {
        int r6 = *(volatile u8*)p;   /* == 1 */
        for (;;) {
            s = sync_to_slave();
            if (s <= 4999) goto L29a02;
            if (DBG > 0) LOG();
            r6++;
            if (r6 == 4) break;
        }
        goto L2956e;
    }
 L29a02:
    if (DBG > 0) LOG();
    f7cb54();
    goto L2956e;

 L298dc:
    {
        int r6 = 4;
        for (;;) {
            r6--;
            if (r6 == 0) goto L2956e;
            if ((unsigned)f27448() < 500u) { if (DBG > 0) LOG(); goto L2956e; }
        }
    }

 L29912:
    if (f23eec() == 1 && *(volatile u8*)(p+0xd5) == 6) goto L299b8;
 L29922:
    {
        int cnt = 0x65;
        while (*(volatile u8*)(p+0xfe6) > 1) {
            cnt--;
            if (cnt == 0) break;
            f7cb8e();
        }
    }
 L29936:
    if (*(volatile u8*)(p+0xd5) == 0xc) goto L29c1c;
    f276ec();
    if (*(volatile u8*)p != 1) goto L29b30;
    if (*(volatile u8*)(p+0xd5) == 4) {
        f3441c();
        A = (u8*)f167a8();
        (void)(*(volatile u8*)(A+0xdd));
        f3443c();
    }
 L2996a:
    if (*(volatile u8*)(p+0xd5) == 6) goto L29a8e;
    f7cb54();
    {
        int r6 = 1;
        for (;;) {
            s = sync_to_slave();
            if (s <= 4999) goto L29a5c;
            if (DBG > 0) LOG();
            r6++;
            if (r6 == 4) goto L29a76;
        }
    }
 L29a5c:
    if (DBG > 0) LOG();
 L29a6e:
    f7cbfe();
 L29a76:
    if (DBG > 2) LOG();
    goto L297ea;

 L299b8:
    if (*(volatile u8*)p != 1) goto L29a22;
    {
        int r6 = *(volatile u8*)p;   /* == 1 */
        for (;;) {
            s = sync_to_slave();
            if (s <= 4999) goto L29a02;
            if (DBG > 0) LOG();
            r6++;
            if (r6 == 4) goto L2956e;
        }
    }

 L29a22:
    {
        int r6 = 4;
        for (;;) {
            r6--;
            if (r6 == 0) goto L2956e;
            if ((unsigned)f27448() < 500u) { if (DBG > 0) LOG(); goto L2956e; }
        }
    }

 L29a8e:
    {
        int e = f23eec();
        if (e == 0 && *(volatile u8*)(p+0xd5) == 6) {
            sync_to_slave();
            goto L29aac;
        }
    }
    if (f23eec() != 2) goto L29a76;
    if (*(volatile u8*)(p+0xd5) != 6) goto L29a76;
    {
        int r6 = 1;
        for (;;) {
            s = sync_to_slave();
            if (s <= 4999) goto L29b10;
            if (DBG > 1) LOG();
            r6++;
            if (r6 == 4) goto L29a76;
        }
    }
 L29b10:
    if (DBG > 2) LOG();
    f7cb54();
    goto L29a76;

 L29aac:
    f7cbfe();
    f2c0e8();
    goto L29a76;

 L29b30:
    if (*(volatile u8*)(p+0xd5) == 6) goto L29b90;
    f27448();
    A = (u8*)f167a8();
    if (*(volatile u8*)(A+0xd5) != 4) goto L29a6e;
    f3441c();
    B = (u8*)f167a8();
    (void)(*(volatile u8*)(B+0xdd));
    f3443c();
    goto L29a6e;

 L29b90:
    {
        int e = f23eec();
        if (e == 0 && *(volatile u8*)(p+0xd5) == 6) {
            f27448();
            A = (u8*)f167a8();
            if (*(volatile u8*)(A+0xd5) == 4) {
                f3441c();
                B = (u8*)f167a8();
                (void)(*(volatile u8*)(B+0xdd));
                f3443c();
            }
            goto L29aac;
        }
    }
    if (f23eec() != 2) goto L29a76;
    if (*(volatile u8*)(p+0xd5) != 6) goto L29a76;
    {
        int r6 = 4;
        for (;;) {
            r6--;
            if (r6 == 0) goto L29a76;
            if ((unsigned)f27448() < 500u) {
                if (DBG <= 2) goto L297ea;
                LOG();
                goto L29a76;
            }
        }
    }

 L29c1c:
    if (DBG > 2) LOG();
    {
        int r6 = 1;
        for (;;) {
            s = sync_to_slave();
            if (s <= 4999) goto L29c78;
            if (DBG > 1) LOG();
            r6++;
            if (r6 == 4) goto L29c96;
        }
    }
 L29c78:
    if (DBG > 2) LOG();
 L29c8a:
    f498c0();
    thunk745c8();
 L29c96:
    if (DBG > 1) LOG();
    goto L297ea;

    /* ================= case 1 : state == 3 ================= */
 L29cae:
    if (*(volatile u8*)(*(u8**)(p+0x1014)) != 0) goto L2956e;
    if (*(volatile u8*)(p+0xfea) != 0xc) goto L29d18;
    f276ec();
    if (*(volatile u8*)p == 1) sync_to_slave();
    else f27448();
 L29cde:
    *(volatile u8*)(p+0xfea) = 0xa;
    f7d2f8();
    if (DBG > 0) LOG();
 L29cfe:
    *(volatile int*)(p+0x104c) = 3;
    f7cb4c();
    goto L297ea;

 L29d18:
    f276ec();
    if (*(volatile u8*)p == 1) {
        sync_to_slave();
        f7cbfe();
    } else {
        f27448();
    }
 L29d38:
    *(volatile u8*)(p+0xfea) = 0xc;
    f7cbfe();
    f7d2f8();
    if (DBG > 0) LOG();
    goto L29cfe;

    /* ================= case 2 : state == 4 ================= */
 L29d6e:
    if (*(volatile u8*)(*(u8**)(p+0x1014)) != 0) {
        if (DBG > 0) LOG();
        goto L2956e;
    }
    G_D95 = 1;
    if (*(volatile u8*)p != 1) goto L29ec0;
    if (DBG > 2) LOG();
 L29db2:
    if (*(volatile u8*)(p+0xd5) == 0xc) {
        if (DBG > 0) LOG();
        goto L2956e;
    }
    /* L29dda */
    if (G_D96 != 0) goto L29e62;
    if (f7ce00() == 0 && *(volatile u8*)(p+0xd5) != 6) goto L29e62;
    s = sync_to_slave();
    if (s > 4999) {
        if (DBG <= 1) goto L297ea;
        LOG();
        goto L297ea;
    }
 L29e20:
    f7cdb6();
    if (DBG > 2) LOG();
 L29e3e:
    *(volatile u8*)(p+0xec) = 0xc;
    *(volatile u8*)(*(u8**)(p+0x1020)) = 1;
    f2bef4();
    q = *(u8**)(p+0x1020);
    b = *(volatile u8*)(q+2);
    *(volatile u8*)(q+2) = (u8)(b + 1);
    goto L297ea;

 L29e62:
    if (DBG > 1) LOG();
    goto L297ea;

 L29ec0:
    if (G_D96 != 0) goto L29efe;
    if (f26c28() == 0) goto L29efe;
    if (f7ce00() == 0 && *(volatile u8*)(p+0xd5) != 6 && *(volatile u8*)(p+0xd5) != 1) goto L29efe;
    f7ce60();
    A = (u8*)f167a8();
    q = *(u8**)(A+0x100c);
    *(volatile u8*)q = 1;
    f276ec();
    goto L297ea;

 L29efe:
    if (DBG <= 1) goto L297ea;
    f7ce00();
    LOG();
    goto L297ea;

    /* ================= case 4 : state == 6 ================= */
 L29f36:
    G_D95 = 0;
    if (G_D89 != 0) goto L2a062;
    if (*(volatile u8*)p != 1) goto L2a062;
    if (*(volatile u8*)(p+0xd5) != 0xc) goto L297ea;
    if (DBG > 2) LOG();
 L29f76:
    G_D89 = 1;
    {
        int r6 = 1;
        for (;;) {
            s = sync_to_slave();
            if (s <= 4999) goto L2a04c;
            if (DBG > 1) LOG();
            r6++;
            if (r6 == 4) goto L297ea;
        }
    }

    /* ================= case 3 : state == 5 ================= */
 L29fd8:
    G_D95 = 0;
    if (*(volatile u8*)p != 1) goto L2a062;
    if (*(volatile u8*)(p+0xd5) != 0xc) goto L297ea;
    if (DBG > 2) LOG();
    {
        int r6 = 1;
        for (;;) {
            s = sync_to_slave();
            if (s <= 4999) goto L2a04c;
            if (DBG > 1) LOG();
            r6++;
            if (r6 == 4) goto L297ea;
        }
    }

 L2a04c:
    if (DBG > 2) LOG();
 L29fcc:
    f498c0();
    goto L29786;

 L2a062:
    if (*(volatile u8*)p != 2) goto L297ea;
    if (*(volatile u8*)(p+0xd5) != 0x10) goto L297ea;
    A = (u8*)f167a8();
    q = *(u8**)(A+0x100c);
    if (*(volatile u8*)q != 4) goto L297ea;
    B = (u8*)f167a8();
    q = *(u8**)(B+0x100c);
    *(volatile u8*)q = 5;
    goto L297ea;
}
