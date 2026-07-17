/* Reconstructed key_event_thread @ 0x2955c (CFG parity: 7/7 cases, PROVEN) */
#include <stdint.h>
typedef unsigned char u8;

/* callees (opaque oracles; order-keyed) */
extern void FUN_0002953c(void);
extern u8  *get_device_info(void);
extern void wait_for_event(uint32_t timeout, uint32_t flags);
extern int  update_sync_buffer(void *object, uint64_t timeout);
extern void debug_print(void);
extern void log_message(void);
extern void send_event(unsigned int event);
extern int  onboarding_sync_data(void);
extern int  FUN_000370b0(void);
extern void FUN_00037060(void);
extern void getStocksIndex(void);
extern void getNewsIndex(void);
extern int  sync_to_slave(void);
extern void display_inputEvent(void);
extern void process_touch_event(void);
extern int  FUN_00033cdc(void);
extern void FUN_0007cb8e(void);
extern int  FUN_0002c3dc(void);
extern int  FUN_00023eec(void);
extern void change_work_mode_to(void);
extern int  FUN_00027448(void);
extern void FUN_0003441c(void);
extern void FUN_0003443c(void);
extern void FUN_0007cb54(void);
extern void set_shutdown_flag(void);
extern void update_persist_task_status_to_idle(void);
extern void display_DelayClose(void);
extern void FUN_0007d2f8(void);
extern void process_sync_buffer(void);
extern int  FUN_00026c28(void);
extern int  FUN_0007ce00(void);
extern void FUN_0007ce60(void);
extern void prepare_quick_note_mode(void);
extern void update_persist_task_status(void);

#define SINK  (*(volatile int*)0x20007554)
#define DBG   (*(volatile int*)0x2000230c)
#define ST    (*(volatile int*)0x20007b18)
#define G_D95 (*(volatile u8*)0x20018d95)
#define G_D96 (*(volatile u8*)0x20018d96)
#define G_D98 (*(volatile u8*)0x20018d98)
#define G_D89 (*(volatile u8*)0x20018d89)

#define LOG() do { if (SINK==0) log_message(); else debug_print(); } while (0)

void key_event_thread(u8 *p, unsigned int a2, unsigned int a3)
{
    int state, r8val = 0, r7 = 0, d, s;
    u8 *q, *A, *B, b;
    (void)a2; (void)a3;

    FUN_0002953c();

 L2956e:
    A = get_device_info();
    if (*(volatile u8*)(A+1) == 1) {
L29578:
        wait_for_event(0x28000, 0);
        goto L2956e;
    }
    B = get_device_info();
    if (*(volatile u8*)(B+1) == 8) goto L29578;
    if (update_sync_buffer((void *)(uintptr_t)0x20007b1c,
                           UINT64_MAX) != 0) goto L297ea;
    if (DBG > 0) LOG();
    state = ST;
    if (state != 1) goto L297f2;

    /* ---- state == 1 ---- */
    q = *(u8**)(p+0x1014);
    if (*(volatile u8*)q == 0) goto L2963e;
    send_event(1);
    q = *(u8**)(p+0x1014);
    b = *(volatile u8*)(q+2);
    if (b == 5) {
        A = get_device_info();
        if (*(volatile u8*)A != 2) goto L2956e;
        r8val = 0x13; goto L295f2;
    } else if (b == 0x13) {
        A = get_device_info();
        if (*(volatile u8*)A != 2) goto L2956e;
        r8val = 0x14; goto L295f2;
    } else if (b == 0x14) {
        A = get_device_info();
        if (*(volatile u8*)A != 1) goto L2956e;
        q = *(u8**)(p+0x1014);
        *(volatile u8*)(q+2) = 0x15;
        goto L2956e;
    } else {
        goto L2956e;
    }

 L295f2:
    if (onboarding_sync_data() == 0) {
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
        if (b != 0) send_event(1);
        goto L29668;
    }
 L29652:
    send_event(1);
    goto L2956e;

 L29668:
    if (*(volatile u8*)p != 1) goto L29796;
    if (*(volatile u8*)(p+0xd5) != 6) goto L297ea;
    if (DBG > 2) LOG();
    d = FUN_000370b0();
    if (d == 0) { if (DBG > 3) LOG(); FUN_00037060(); goto L296c8; }
    if (d == 1) { if (DBG > 3) LOG(); getStocksIndex(); goto L296c8; }
    if (d == 2) { if (DBG > 3) LOG(); getNewsIndex(); goto L296c8; }
    goto L296c8;
 L296c8:
    s = sync_to_slave();
    if (s <= 4999) goto L29766;
    if (DBG > 1) LOG();
    goto L297ea;
 L29766:
    if (DBG > 3) LOG();
    display_inputEvent();
 L29786:
    process_touch_event();
    goto L297ea;

 L29796:
    if (*(volatile u8*)p != 2) goto L297ea;
    if (FUN_00033cdc() == 0) goto L297ea;
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
    FUN_0007cb8e();
    r7 = r7 + 1;
 L297cc:
    if (*(volatile u8*)(p+0x108f) != 0) goto L297e2;
    if (G_D98 == 0) goto L297e2;
    if (r7 <= 0x63) goto L297c4;
    r7 = r7 + 1;
 L297e2:
    if (FUN_0002c3dc() < 0) goto L297cc;
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
    if (*(volatile u8*)(*(u8**)(p+0x1014)) != 0) { send_event(1); goto L2956e; }
    if (*(volatile u8*)(p+0xd5) == 7) goto L2956e;
    if (FUN_00023eec() != 1) goto L29912;
    if (*(volatile u8*)(p+0xd5) != 0) goto L29912;
    if (*(volatile u8*)p != 1) goto L298dc;
    A = (u8*)get_device_info(); *(volatile u8*)(A+0xfe6) = 5;
    B = (u8*)get_device_info();
    A = (u8*)get_device_info();
    b = *(volatile u8*)(B+0xed5);
    *(volatile u8*)(A+0xcb) = b;
    get_device_info();
    sync_to_slave();
    change_work_mode_to();
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
    FUN_0007cb54();
    goto L2956e;

 L298dc:
    {
        int r6 = 4;
        for (;;) {
            r6--;
            if (r6 == 0) goto L2956e;
            if ((unsigned)FUN_00027448() < 500u) { if (DBG > 0) LOG(); goto L2956e; }
        }
    }

 L29912:
    if (FUN_00023eec() == 1 && *(volatile u8*)(p+0xd5) == 6) goto L299b8;
 L29922:
    {
        int cnt = 0x65;
        while (*(volatile u8*)(p+0xfe6) > 1) {
            cnt--;
            if (cnt == 0) break;
            FUN_0007cb8e();
        }
    }
 L29936:
    if (*(volatile u8*)(p+0xd5) == 0xc) goto L29c1c;
    send_event(1);
    if (*(volatile u8*)p != 1) goto L29b30;
    if (*(volatile u8*)(p+0xd5) == 4) {
        FUN_0003441c();
        A = (u8*)get_device_info();
        (void)(*(volatile u8*)(A+0xdd));
        FUN_0003443c();
    }
 L2996a:
    if (*(volatile u8*)(p+0xd5) == 6) goto L29a8e;
    FUN_0007cb54();
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
    set_shutdown_flag();
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
            if ((unsigned)FUN_00027448() < 500u) { if (DBG > 0) LOG(); goto L2956e; }
        }
    }

 L29a8e:
    {
        int e = FUN_00023eec();
        if (e == 0 && *(volatile u8*)(p+0xd5) == 6) {
            sync_to_slave();
            goto L29aac;
        }
    }
    if (FUN_00023eec() != 2) goto L29a76;
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
    FUN_0007cb54();
    goto L29a76;

 L29aac:
    set_shutdown_flag();
    update_persist_task_status_to_idle();
    goto L29a76;

 L29b30:
    if (*(volatile u8*)(p+0xd5) == 6) goto L29b90;
    FUN_00027448();
    A = (u8*)get_device_info();
    if (*(volatile u8*)(A+0xd5) != 4) goto L29a6e;
    FUN_0003441c();
    B = (u8*)get_device_info();
    (void)(*(volatile u8*)(B+0xdd));
    FUN_0003443c();
    goto L29a6e;

 L29b90:
    {
        int e = FUN_00023eec();
        if (e == 0 && *(volatile u8*)(p+0xd5) == 6) {
            FUN_00027448();
            A = (u8*)get_device_info();
            if (*(volatile u8*)(A+0xd5) == 4) {
                FUN_0003441c();
                B = (u8*)get_device_info();
                (void)(*(volatile u8*)(B+0xdd));
                FUN_0003443c();
            }
            goto L29aac;
        }
    }
    if (FUN_00023eec() != 2) goto L29a76;
    if (*(volatile u8*)(p+0xd5) != 6) goto L29a76;
    {
        int r6 = 4;
        for (;;) {
            r6--;
            if (r6 == 0) goto L29a76;
            if ((unsigned)FUN_00027448() < 500u) {
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
    display_DelayClose();
    process_touch_event();
 L29c96:
    if (DBG > 1) LOG();
    goto L297ea;

    /* ================= case 1 : state == 3 ================= */
 L29cae:
    if (*(volatile u8*)(*(u8**)(p+0x1014)) != 0) goto L2956e;
    if (*(volatile u8*)(p+0xfea) != 0xc) goto L29d18;
    send_event(1);
    if (*(volatile u8*)p == 1) sync_to_slave();
    else FUN_00027448();
 L29cde:
    *(volatile u8*)(p+0xfea) = 0xa;
    FUN_0007d2f8();
    if (DBG > 0) LOG();
 L29cfe:
    *(volatile int*)(p+0x104c) = 3;
    process_sync_buffer();
    goto L297ea;

 L29d18:
    send_event(1);
    if (*(volatile u8*)p == 1) {
        sync_to_slave();
        set_shutdown_flag();
    } else {
        FUN_00027448();
    }
 L29d38:
    *(volatile u8*)(p+0xfea) = 0xc;
    set_shutdown_flag();
    FUN_0007d2f8();
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
    if (FUN_0007ce00() == 0 && *(volatile u8*)(p+0xd5) != 6) goto L29e62;
    s = sync_to_slave();
    if (s > 4999) {
        if (DBG <= 1) goto L297ea;
        LOG();
        goto L297ea;
    }
 L29e20:
    prepare_quick_note_mode();
    if (DBG > 2) LOG();
 L29e3e:
    *(volatile u8*)(p+0xec) = 0xc;
    *(volatile u8*)(*(u8**)(p+0x1020)) = 1;
    update_persist_task_status();
    q = *(u8**)(p+0x1020);
    b = *(volatile u8*)(q+2);
    *(volatile u8*)(q+2) = (u8)(b + 1);
    goto L297ea;

 L29e62:
    if (DBG > 1) LOG();
    goto L297ea;

 L29ec0:
    if (G_D96 != 0) goto L29efe;
    if (FUN_00026c28() == 0) goto L29efe;
    if (FUN_0007ce00() == 0 && *(volatile u8*)(p+0xd5) != 6 && *(volatile u8*)(p+0xd5) != 1) goto L29efe;
    FUN_0007ce60();
    A = (u8*)get_device_info();
    q = *(u8**)(A+0x100c);
    *(volatile u8*)q = 1;
    send_event(1);
    goto L297ea;

 L29efe:
    if (DBG <= 1) goto L297ea;
    FUN_0007ce00();
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
    display_DelayClose();
    goto L29786;

 L2a062:
    if (*(volatile u8*)p != 2) goto L297ea;
    if (*(volatile u8*)(p+0xd5) != 0x10) goto L297ea;
    A = (u8*)get_device_info();
    q = *(u8**)(A+0x100c);
    if (*(volatile u8*)q != 4) goto L297ea;
    B = (u8*)get_device_info();
    q = *(u8**)(B+0x100c);
    *(volatile u8*)q = 5;
    goto L297ea;
}
