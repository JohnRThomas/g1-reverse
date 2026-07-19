#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0002955c @ 0x0002955c
 * public-name: key_event_thread
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_ui_mode_flag2                        <= FUN_00023eec @ 0x00023eec
 *   check_charging_and_touch_flags           <= FUN_00026c28 @ 0x00026c28
 *   esb_send_command_and_wait_ack            <= FUN_00027448 @ 0x00027448
 *   some_module_sem_init                     <= FUN_0002953c @ 0x0002953c
 *   handle_touch_key_press_event             <= FUN_0002c3dc @ 0x0002c3dc
 *   msg_content_used_count                   <= FUN_00033cdc @ 0x00033cdc
 *   msg_content_decrement_timer              <= FUN_0003441c @ 0x0003441c
 *   set_message_pending_state                <= FUN_0003443c @ 0x0003443c
 *   sync_dashboard_default_language          <= FUN_00037060 @ 0x00037060
 *   get_dashboard_disp_mode                  <= FUN_000370b0 @ 0x000370b0
 *   atomic_or_bit1                           <= FUN_0007cb54 @ 0x0007cb54
 *   k_msleep                                 <= FUN_0007cb8e @ 0x0007cb8e
 *   is_system_idle_ready                     <= FUN_0007ce00 @ 0x0007ce00
 *   reset_esb_sync_state                     <= FUN_0007ce60 @ 0x0007ce60
 *   device_info_set_mode                     <= FUN_0007d2f8 @ 0x0007d2f8
 * address symbols (name @ address):
 *   rodata_28000                             @ 0x00028000
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_touch_key_reset_reason                 @ 0x20007b18
 *   g_some_module_sem                        @ 0x20007b1c
 *   g_touch_key_press_active                 @ 0x20018d89
 *   g_20018d95                               @ 0x20018d95
 *   g_20018d96                               @ 0x20018d96
 *   g_esb_notify_sync_substate               @ 0x20018d98
 */
/* Reconstructed key_event_thread @ 0x2955c (CFG parity: 7/7 cases, PROVEN) */
#include <stdint.h>
typedef unsigned char u8;

/* callees (opaque oracles; order-keyed) */
extern void some_module_sem_init(void);
extern u8  *get_device_info(void);
extern void wait_for_event(uint32_t timeout, uint32_t flags);
extern int  k_sem_take(void *object, uint64_t timeout);
extern void debug_print(void);
extern void log_message(void);
extern void send_event(unsigned int event);
extern int  onboarding_sync_data(void);
extern int  get_dashboard_disp_mode(void);
extern void sync_dashboard_default_language(void);
extern void getStocksIndex(void);
extern void getNewsIndex(void);
extern int  sync_to_slave(void);
extern void display_inputEvent(void);
extern void process_touch_event(void);
extern int  msg_content_used_count(void);
extern void k_msleep(void);
extern int  handle_touch_key_press_event(void);
extern int  get_ui_mode_flag2(void);
extern void change_work_mode_to(void);
extern int  esb_send_command_and_wait_ack(void);
extern void msg_content_decrement_timer(void);
extern void set_message_pending_state(void);
extern void atomic_or_bit1(void);
extern void set_shutdown_flag(void);
extern void update_persist_task_status_to_idle(void);
extern void display_DelayClose(void);
extern void device_info_set_mode(void);
extern void process_sync_buffer(void);
extern int  check_charging_and_touch_flags(void);
extern int  is_system_idle_ready(void);
extern void reset_esb_sync_state(void);
extern void prepare_quick_note_mode(void);
extern void update_persist_task_status(void);

#define SINK  (*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)
#define DBG   (*(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/)
#define ST    (*(volatile int*)((unsigned long)&g_touch_key_reset_reason) /*=0x20007b18*/)
#define G_D95 (*(volatile u8*)((unsigned long)&g_20018d95) /*=0x20018d95*/)
#define G_D96 (*(volatile u8*)((unsigned long)&g_20018d96) /*=0x20018d96*/)
#define G_D98 (*(volatile u8*)((unsigned long)&g_esb_notify_sync_substate) /*=0x20018d98*/)
#define G_D89 (*(volatile u8*)((unsigned long)&g_touch_key_press_active) /*=0x20018d89*/)

#define LOG() do { if (SINK==0) log_message(); else debug_print(); } while (0)

void key_event_thread(u8 *p, unsigned int a2, unsigned int a3)
{
    int state, r8val = 0, r7 = 0, d, s;
    u8 *q, *A, *B, b;
    (void)a2; (void)a3;

    some_module_sem_init();

 L2956e:
    A = get_device_info();
    if (*(volatile u8*)(A+1) == 1) {
L29578:
        wait_for_event(((unsigned long)&rodata_28000) /*=0x28000*/, 0);
        goto L2956e;
    }
    B = get_device_info();
    if (*(volatile u8*)(B+1) == 8) goto L29578;
    if (k_sem_take((void *)(uintptr_t)((unsigned long)&g_some_module_sem) /*=0x20007b1c*/,
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
    d = get_dashboard_disp_mode();
    if (d == 0) { if (DBG > 3) LOG(); sync_dashboard_default_language(); goto L296c8; }
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
    if (msg_content_used_count() == 0) goto L297ea;
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
    k_msleep();
    r7 = r7 + 1;
 L297cc:
    if (*(volatile u8*)(p+0x108f) != 0) goto L297e2;
    if (G_D98 == 0) goto L297e2;
    if (r7 <= 0x63) goto L297c4;
    r7 = r7 + 1;
 L297e2:
    if (handle_touch_key_press_event() < 0) goto L297cc;
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
    if (get_ui_mode_flag2() != 1) goto L29912;
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
    atomic_or_bit1();
    goto L2956e;

 L298dc:
    {
        int r6 = 4;
        for (;;) {
            r6--;
            if (r6 == 0) goto L2956e;
            if ((unsigned)esb_send_command_and_wait_ack() < 500u) { if (DBG > 0) LOG(); goto L2956e; }
        }
    }

 L29912:
    if (get_ui_mode_flag2() == 1 && *(volatile u8*)(p+0xd5) == 6) goto L299b8;
 L29922:
    {
        int cnt = 0x65;
        while (*(volatile u8*)(p+0xfe6) > 1) {
            cnt--;
            if (cnt == 0) break;
            k_msleep();
        }
    }
 L29936:
    if (*(volatile u8*)(p+0xd5) == 0xc) goto L29c1c;
    send_event(1);
    if (*(volatile u8*)p != 1) goto L29b30;
    if (*(volatile u8*)(p+0xd5) == 4) {
        msg_content_decrement_timer();
        A = (u8*)get_device_info();
        (void)(*(volatile u8*)(A+0xdd));
        set_message_pending_state();
    }
 L2996a:
    if (*(volatile u8*)(p+0xd5) == 6) goto L29a8e;
    atomic_or_bit1();
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
            if ((unsigned)esb_send_command_and_wait_ack() < 500u) { if (DBG > 0) LOG(); goto L2956e; }
        }
    }

 L29a8e:
    {
        int e = get_ui_mode_flag2();
        if (e == 0 && *(volatile u8*)(p+0xd5) == 6) {
            sync_to_slave();
            goto L29aac;
        }
    }
    if (get_ui_mode_flag2() != 2) goto L29a76;
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
    atomic_or_bit1();
    goto L29a76;

 L29aac:
    set_shutdown_flag();
    update_persist_task_status_to_idle();
    goto L29a76;

 L29b30:
    if (*(volatile u8*)(p+0xd5) == 6) goto L29b90;
    esb_send_command_and_wait_ack();
    A = (u8*)get_device_info();
    if (*(volatile u8*)(A+0xd5) != 4) goto L29a6e;
    msg_content_decrement_timer();
    B = (u8*)get_device_info();
    (void)(*(volatile u8*)(B+0xdd));
    set_message_pending_state();
    goto L29a6e;

 L29b90:
    {
        int e = get_ui_mode_flag2();
        if (e == 0 && *(volatile u8*)(p+0xd5) == 6) {
            esb_send_command_and_wait_ack();
            A = (u8*)get_device_info();
            if (*(volatile u8*)(A+0xd5) == 4) {
                msg_content_decrement_timer();
                B = (u8*)get_device_info();
                (void)(*(volatile u8*)(B+0xdd));
                set_message_pending_state();
            }
            goto L29aac;
        }
    }
    if (get_ui_mode_flag2() != 2) goto L29a76;
    if (*(volatile u8*)(p+0xd5) != 6) goto L29a76;
    {
        int r6 = 4;
        for (;;) {
            r6--;
            if (r6 == 0) goto L29a76;
            if ((unsigned)esb_send_command_and_wait_ack() < 500u) {
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
    else esb_send_command_and_wait_ack();
 L29cde:
    *(volatile u8*)(p+0xfea) = 0xa;
    device_info_set_mode();
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
        esb_send_command_and_wait_ack();
    }
 L29d38:
    *(volatile u8*)(p+0xfea) = 0xc;
    set_shutdown_flag();
    device_info_set_mode();
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
    if (is_system_idle_ready() == 0 && *(volatile u8*)(p+0xd5) != 6) goto L29e62;
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
    if (check_charging_and_touch_flags() == 0) goto L29efe;
    if (is_system_idle_ready() == 0 && *(volatile u8*)(p+0xd5) != 6 && *(volatile u8*)(p+0xd5) != 1) goto L29efe;
    reset_esb_sync_state();
    A = (u8*)get_device_info();
    q = *(u8**)(A+0x100c);
    *(volatile u8*)q = 1;
    send_event(1);
    goto L297ea;

 L29efe:
    if (DBG <= 1) goto L297ea;
    is_system_idle_ready();
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
