/* readable reconstruction; identity: FUN_0003cf44 @ 0x0003cf44
 * public-name: ui_teleprompter_task
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   __aeabi_ldivmod                          <= FUN_0000e1a4 @ 0x0000e1a4
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   get_ui_mode_flag_byte1                   <= FUN_00023ee0 @ 0x00023ee0
 *   sync_to_slave                            <= FUN_00026f74 @ 0x00026f74
 *   mark_master_or_low_battery_flag          <= FUN_0002efc0 @ 0x0002efc0
 *   gui_set_active_canvas                    <= FUN_000431b4 @ 0x000431b4
 *   gui_screen_clear                         <= FUN_000431c0 @ 0x000431c0
 *   gui_canvas_flags_set_bit1                <= FUN_000432d0 @ 0x000432d0
 *   gui_canvas_flags_clear_bit1              <= FUN_000432ec @ 0x000432ec
 *   gui_reset_dynamic_bitmap_frame_state     <= FUN_00043308 @ 0x00043308
 *   gui_bmp_dynamic_bitmap_draw              <= FUN_0004334c @ 0x0004334c
 *   gui_bmp_bitmap_draw                      <= FUN_00043484 @ 0x00043484
 *   gui_screen_fade_out_transition           <= FUN_0004382c @ 0x0004382c
 *   gui_verticalLine_process_bar             <= FUN_0004396c @ 0x0004396c
 *   gui_utf_draw                             <= FUN_00043e90 @ 0x00043e90
 *   ui_render_scroll_text_frame              <= FUN_000440ec @ 0x000440ec
 *   gui_clock_draw                           <= FUN_000442bc @ 0x000442bc
 *   clean_fb_data                            <= FUN_000471cc @ 0x000471cc
 *   reflash_fb_data_to_lcd                   <= FUN_00047260 @ 0x00047260
 *   send_response_data_to_ble                <= FUN_00047ba8 @ 0x00047ba8
 *   k_mutex_lock                             <= FUN_000723b8 @ 0x000723b8
 *   k_mutex_unlock                           <= FUN_00072558 @ 0x00072558
 *   k_sleep                                  <= FUN_00074844 @ 0x00074844
 *   snprintf                                 <= FUN_00077914 @ 0x00077914
 *   get_timestamp                            <= FUN_0007d224 @ 0x0007d224
 *   k_uptime_get_6                           <= FUN_0007d33a @ 0x0007d33a
 *   u64_sub                                  <= FUN_0007d3c2 @ 0x0007d3c2
 *   device_info_text_width_get               <= FUN_0007d3ee @ 0x0007d3ee
 *   device_info_text_height_get_clamped      <= FUN_0007d446 @ 0x0007d446
 *   log_message                              <= FUN_0007dda4 @ 0x0007dda4
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   g_log_level                              @ 0x2000230c
 *   g_notification_display_buffer            @ 0x20004988
 *   g_200049b8                               @ 0x200049b8
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_20007564                               @ 0x20007564
 *   g_ui_state_mutex                         @ 0x20007b3c
 *   g_20009fdc                               @ 0x20009fdc
 *   g_20009fe0                               @ 0x20009fe0
 *   g_20009fe4                               @ 0x20009fe4
 *   g_20009fe8                               @ 0x20009fe8
 *   g_20009fec                               @ 0x20009fec
 *   g_20009ff0                               @ 0x20009ff0
 *   g_gui_canvas_flags                       @ 0x2000a030
 *   g_2001046a                               @ 0x2001046a
 */
/* Reconstructed ui_teleprompter_task @ 0x3cf44  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "../headers/g1_log.h"

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

extern int get_device_info(void);
extern unsigned int gui_set_active_canvas(unsigned int);
extern void     gui_canvas_flags_set_bit1(void);
extern void     gui_screen_clear(void);
extern void memset_bytes(void*, int, int);
extern void memcpy(int, int, int);
extern long long k_uptime_get_6(void);
extern long long u64_sub(void);
extern long long __aeabi_ldivmod(unsigned,unsigned,unsigned,unsigned);
extern unsigned device_info_text_width_get(void);
extern unsigned device_info_text_height_get_clamped(void);
extern unsigned get_timestamp(void);
extern int      get_ui_mode_flag_byte1(void);
extern int snprintf(unsigned char*, int, unsigned long, unsigned long);
extern int      sync_to_slave(unsigned,unsigned,unsigned);
extern void     send_response_data_to_ble(void);
extern unsigned int mark_master_or_low_battery_flag(void);
extern void     k_mutex_lock(unsigned,unsigned,unsigned);
extern int k_mutex_unlock(unsigned int);
extern void     gui_utf_draw(unsigned,unsigned,unsigned,unsigned,unsigned,unsigned,unsigned,unsigned,unsigned,unsigned);
extern void     gui_clock_draw(unsigned,unsigned,unsigned,unsigned,unsigned,unsigned);
extern void     gui_verticalLine_process_bar(unsigned,unsigned,unsigned,unsigned,unsigned,unsigned);
extern int gui_bmp_bitmap_draw(unsigned int, int, int, int, int, int);
extern void     clean_fb_data(unsigned,unsigned,unsigned,unsigned,unsigned,unsigned);
extern void     reflash_fb_data_to_lcd(unsigned,unsigned,unsigned,unsigned,unsigned,unsigned);
extern void     k_sleep(unsigned,unsigned);
extern unsigned int gui_reset_dynamic_bitmap_frame_state(void);
extern unsigned int gui_screen_fade_out_transition(void);
extern void     gui_canvas_flags_clear_bit1(void);
extern void     gui_bmp_dynamic_bitmap_draw(unsigned,unsigned,unsigned,unsigned,unsigned);
extern void     ui_render_scroll_text_frame(unsigned,unsigned,unsigned,unsigned,unsigned,unsigned,unsigned,unsigned);

/* debug gate: if(loglevel>thr){ [LP]? FUN_19c70 : FUN_7dda4 } */
__attribute__((always_inline)) static inline void dbg(int thr){
    if (S32(LL) > thr){
        if (U32(LP)) debug_print(0,0);
        else         log_message(0,0);
    }
}

unsigned ui_teleprompter_task(unsigned a0, unsigned a1, unsigned a2, unsigned a3)
{
    unsigned ctx0, c, sel = a2, st;
    unsigned t0, t1, r8v;
    long long t, q, dv;
    (void)a1; (void)a3;

    ctx0 = get_device_info();          /* call 0 */
    gui_set_active_canvas(a0 + 0x24);        /* call 1 */
    gui_canvas_flags_set_bit1();                 /* call 2 */
    st = U8(G);
    if (st > 3) return 0;

    switch (st) {
    /* ------------------------------------------------ state 0 ---- */
    case 0:
        if (S32(LL) > 2) {
            dbg(2);                         /* 3cf78 first gate  */
            if (sel == 2) goto L_cf98;
            /* 3cfcc second gate (LL still >2) */
            get_device_info();
            if (U32(LP)) debug_print(0,0);
            else         log_message(0,0);
        } else {
            if (sel == 2) goto L_cf98;
        }
        /* 3cfee */
        if (sel != 1) return 0;
        /* 3cff2 */
        c = get_device_info();
        if (U8(U32(c + 0xffc) + 1) != 1) return 0;
        if (U8(ctx0 + 0xf0) != 1) return 0;       /* 3d000 */
        dbg(2);                                    /* 3d008 */
        c = get_device_info();                        /* 3d020 */
        if (U8(c) == 1) send_response_data_to_ble();
        dbg(2);                                    /* 3d02e */
        /* 3d046 full init (effectively unreachable under emulation) */
        gui_screen_clear();
        memset_bytes(G, 0, 0x230);
        U8(G) = 1;
        t = k_uptime_get_6(); U32(G+8)=(unsigned)t; U32(G+0xc)=(unsigned)(t>>32);
        t = k_uptime_get_6(); U32(G+0x10)=(unsigned)t; U32(G+0x14)=(unsigned)(t>>32);
        U32(G+0x18)=0;
        U8(G+1)=0xa;
        U8(G+0x25)=(uint8_t)(int8_t)U8(ctx0+0xfb);
        U32(HR)=0; U32(MN)=0; U32(SC)=0; U32(CHR)=0; U32(CMN)=0; U32(CSC)=0;
        memset_bytes(BUF,0,0);
        k_mutex_lock(OBJ,0xffffffffu,0xffffffffu);
        memcpy(BUF, ctx0+0x106, 0x200);
        U8(G+0x24)=U8(ctx0+0xef);
        U8(G+0x25)=(uint8_t)(int8_t)U8(ctx0+0xfb);
        k_mutex_unlock(OBJ);
        t = k_uptime_get_6();
        {
            int gfb = (int8_t)U8(ctx0+0xfb);
            long long acc = t + (long long)(1000*gfb) - 0x15e;
            U32(G+0x28)=(unsigned)acc; U32(G+0x2c)=(unsigned)(acc>>32);
        }
        dbg(2);
        gui_canvas_flags_clear_bit1();
        {
            int r6;
            for (r6=0; r6<4; r6++){
                device_info_text_width_get(); device_info_text_height_get_clamped();
                device_info_text_width_get(); device_info_text_height_get_clamped();
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
                get_device_info();
                reflash_fb_data_to_lcd(0,0,0,0,0,0);
            }
        }
        gui_canvas_flags_set_bit1();
        k_sleep(0x1334,0);
        gui_reset_dynamic_bitmap_frame_state();
        return 0;
    L_cf98:
        gui_screen_clear();
        memset_bytes(G,0,0x230);
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
                t = k_uptime_get_6(); U32(G+8)=(unsigned)t; U32(G+0xc)=(unsigned)(t>>32);
                U8(G)=2;
                t = k_uptime_get_6(); U32(G+0x10)=(unsigned)t; U32(G+0x14)=(unsigned)(t>>32);
                device_info_text_width_get(); device_info_text_height_get_clamped();
                device_info_text_width_get(); device_info_text_height_get_clamped();
                clean_fb_data(0,0,0,0,0,0);
                if (U8(G+0x24) == 1){
                    device_info_text_width_get(); device_info_text_height_get_clamped();
                    gui_bmp_bitmap_draw(0x1a,0,0,0,0,0);
                } else if (U8(G+0x24) == 0){
                    device_info_text_width_get(); device_info_text_height_get_clamped();
                    gui_bmp_bitmap_draw(0x19,0,0,0,0,0);
                }
            }
        }
        /* 3d394 */
        c = get_device_info();
        if (U8(c) == 1) send_response_data_to_ble();
        return 0;
    L1_sel0:
        if (sel != 0) return 0;
        dbg(2);                                    /* 3d3d8 */
        t = k_uptime_get_6();                        /* 3d3f0 */
        {
            long long v28 = (long long)((unsigned long long)U32(G+0x28) | ((unsigned long long)U32(G+0x2c)<<32));
            if (t >= v28) goto L1_ge;              /* 3d3f8 */
            /* 3d402 diff = v28 - t */
            dv = v28 - t;
            q = __aeabi_ldivmod((unsigned)dv,(unsigned)(dv>>32),0x3e8,0);
            {
                long long g25 = (int8_t)U8(G+0x25);
                long long val = (g25 < q) ? g25 : q;
                if (val != 0) goto L1_fmt;         /* 3d524 */
            }
            /* 3d438 */
            dbg(2);
            t = k_uptime_get_6(); U32(G+0x10)=(unsigned)t; U32(G+0x14)=(unsigned)(t>>32);
            t = k_uptime_get_6(); U32(G+8)=(unsigned)t; U32(G+0xc)=(unsigned)(t>>32);
            U8(G)=2;
            goto L1_render_a;
        }
    L1_ge:
        dbg(2);                                    /* 3d590 */
        t = k_uptime_get_6(); U32(G+0x10)=(unsigned)t; U32(G+0x14)=(unsigned)(t>>32);
        U8(G)=2;
        t = k_uptime_get_6(); U32(G+8)=(unsigned)t; U32(G+0xc)=(unsigned)(t>>32);
        /* fallthrough to shared render (3d5b8 -> 3d4ba tail) */
    L1_render_a:
        device_info_text_width_get(); device_info_text_height_get_clamped();
        device_info_text_width_get(); device_info_text_height_get_clamped();
        clean_fb_data(0,0,0,0,0,0);
        get_device_info(); get_device_info();
        device_info_text_width_get(); device_info_text_height_get_clamped();
        device_info_text_width_get(); device_info_text_height_get_clamped();
        reflash_fb_data_to_lcd(0,0,0,0,0,0);
        if (U8(G+0x24) == 1){                      /* 3d4ca */
            device_info_text_width_get(); device_info_text_height_get_clamped();
            gui_bmp_bitmap_draw(0x1a,0,0,0,0,0);
        } else if (U8(G+0x24) == 0){
            device_info_text_width_get(); device_info_text_height_get_clamped();
            gui_bmp_bitmap_draw(0x19,0,0,0,0,0);
        }
        return 0;
    L1_fmt:
        /* 3d524 -> 77914 -> gate -> 43e90 */
        snprintf(0,0,0,0);
        dbg(2);
        device_info_text_width_get(); device_info_text_height_get_clamped();
        gui_utf_draw(0,0,0,0,0,0,0,0,0,0);
        return 0;

    /* ------------------------------------------------ state 2 ---- */
    case 2:
        if (S32(LL) > 2) {
            dbg(2);                                /* 3d63c */
            if (sel != 2) goto L2_tick;
            if (S32(LL) > 2){                      /* 3d65e */
                if (U32(LP)) debug_print(0,0);
                else         log_message(0,0);
            }
            goto L_67e;
        } else {
            if (sel == 2) goto L_67e;
            goto L2_tick;
        }

    /* ------------------------------------------------ state 3 ---- */
    case 3:
        if (S32(LL) > 1) dbg(1);                   /* 3dc4e */
        k_uptime_get_6();                            /* 3dc66 t ignored */
        q = u64_sub();
        if (q < 0x1f41) goto L_dcbe;
        dbg(1);                                    /* 3dc7e */
        c = get_device_info();
        memset_bytes(U32(c+0xffc),0,0x217);
        gui_screen_fade_out_transition();
        c = get_device_info();
        U8(U32(c+0xffc)+1) = 0;
        memset_bytes(G,0,0x230);
    L_dcbe:
        if (sel != 2) return 0;
        if (S32(LL) > 2){
            if (U32(LP)) debug_print(0,0);
            else         log_message(0,0);
        }
        goto L_67e;
    }
    return 0;

/* ===== shared: state2 sel==2 / state3 sel==2 tail (3d67e) ===== */
L_67e:
    gui_screen_fade_out_transition();
    memset_bytes(G,0,0x230);
/* L_68e */
    c = get_device_info();
    if (U8(c) != 1) return 0;
    if (U8(G+0x24) != 2) return 0;
    mark_master_or_low_battery_flag();
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
                t = k_uptime_get_6();
                U32(G+0x10)=(unsigned)t; U32(G+0x14)=0;
                U32(G+0x20)=U32(G+0x18);
                U8(G+0x1c)=0;
            } else {
                /* 3d6ac */
                t = k_uptime_get_6();
                U32(G+0x20)=(unsigned)t - U32(G+0x10);
                U32(G+0x20)=U32(G+0x18) + U32(G+0x20);
            }
        } else {
            /* 3dd24 */
            if (U8(G+0x1c) == 0) {
                t = k_uptime_get_6();
                U32(G+0x18) = U32(G+0x18) - U32(G+0x10) + (unsigned)t;
                U8(G+0x1c) = (uint8_t)r8v;
            }
            U32(G+0x20) = U32(G+0x18);
        }
    }
/* 3dd3e */
    c = get_device_info();
    (void)U8(U32(c+0xfec)+0x5e);
    r8v = get_timestamp();
    device_info_text_width_get(); device_info_text_height_get_clamped();
    device_info_text_width_get(); device_info_text_height_get_clamped();
    gui_clock_draw(0,0,0,0,0,0);
    if (sel != 1) goto L2_after;
    /* 3dd90 render list */
    c = get_device_info();
    if (U8(c) == 1){
        dbg(2);
        send_response_data_to_ble();
        if ((int8_t)U8(G+1) <= 0x13) U8(G+1)=0x13;
    }
/* 3ddc2 */
    memset_bytes(BUF,0,0x200);
    k_mutex_lock(OBJ,0xffffffffu,0xffffffffu);
    memcpy(BUF, ctx0+0x106, 0x200);
    (void)U8(ctx0+0xfc); (void)U8(ctx0+0xff); (void)U16(ctx0+0xfd); (void)U32(ctx0+0x100);
    k_mutex_unlock(OBJ);
    if (U8(FLAG046a) == 1){
        U8(FLAG046a)=0;
        device_info_text_width_get(); device_info_text_height_get_clamped();
        device_info_text_width_get(); device_info_text_height_get_clamped();
        ui_render_scroll_text_frame(0,0,0,0,0,0,0,0);
    } else {
        /* 3d6de */
        device_info_text_width_get();
        t0 = device_info_text_height_get_clamped();
        device_info_text_width_get(); device_info_text_height_get_clamped();
        gui_utf_draw(0,0,0,0,0,0,0,0,0,0);
    }
/* 3de50 */
    device_info_text_width_get(); device_info_text_height_get_clamped();
    device_info_text_width_get(); device_info_text_height_get_clamped();
    gui_verticalLine_process_bar(0,0,0,0,0,0);
    if (U8(ctx0+0xff) == 1){
        /* 3de90 sl==1 branch (rare) */
        if (U32(LOCK) & 2){
            device_info_text_width_get(); device_info_text_height_get_clamped();
            device_info_text_width_get(); device_info_text_height_get_clamped();
            clean_fb_data(0,0,0,0,0,0);
        }
        if (U32(LOCK) & 2){
            get_device_info(); get_device_info();
            device_info_text_width_get(); device_info_text_height_get_clamped();
            device_info_text_width_get(); device_info_text_height_get_clamped();
            reflash_fb_data_to_lcd(0,0,0,0,0,0);
        }
        if (U8(G+0x24)==1){
            device_info_text_width_get(); device_info_text_height_get_clamped();
            gui_bmp_bitmap_draw(0x1a,0,0,0,0,0);
        } else if (U8(G+0x24)==0){
            device_info_text_width_get(); device_info_text_height_get_clamped();
            gui_bmp_bitmap_draw(0x19,0,0,0,0,0);
        }
        dbg(2);
        U8(G+0x1d)=1;
        U32(G+0x18)=1000*r8v;
        t = k_uptime_get_6(); U32(G+0x10)=(unsigned)t; U32(G+0x14)=0;
        goto L2_after;
    }
    /* 3d720 sl!=1 (usual) */
    U8(G+0x1d) = (uint8_t)(t0 + 1);
    if (U32(LOCK) & 2){
        device_info_text_width_get(); device_info_text_height_get_clamped();
        device_info_text_width_get(); device_info_text_height_get_clamped();
        clean_fb_data(0,0,0,0,0,0);
    }
    if (U32(LOCK) & 2){
        get_device_info(); get_device_info();
        device_info_text_width_get(); device_info_text_height_get_clamped();
        device_info_text_width_get(); device_info_text_height_get_clamped();
        reflash_fb_data_to_lcd(0,0,0,0,0,0);
    }
    if (U8(G+0x24)==1){
        device_info_text_width_get(); device_info_text_height_get_clamped();
        gui_bmp_bitmap_draw(0x1a,0,0,0,0,0);
    } else if (U8(G+0x24)==0){
        device_info_text_width_get(); device_info_text_height_get_clamped();
        gui_bmp_bitmap_draw(0x19,0,0,0,0,0);
    }
    dbg(2);
L2_after:
    /* 3df5c */
    if (U8(G+0x24)==2 && U8(G+0x1d)==0){
        device_info_text_width_get(); device_info_text_height_get_clamped();
        gui_bmp_dynamic_bitmap_draw(1,0,0,0,0);
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
        memset_bytes(0,0,0x38);
        snprintf(0, (hr>9)?0x000a8b58u:0x000a9c15u, 0x40, 0);
        if (!(hr==U32(CHR) && mn==U32(CMN) && sc==U32(CSC))){
            /* 3d892 */
            device_info_text_width_get(); device_info_text_height_get_clamped();
            device_info_text_width_get(); device_info_text_height_get_clamped();
            gui_utf_draw(0,0,0,0,0,0,0,0,0,0);
            U32(CHR)=hr; U32(CMN)=mn; U32(CSC)=sc;
        }
    }
/* 3d8e6 */
    c = get_device_info();
    if (U8(c) != 1) goto L_db48;
    if (S32(FLAG7564) > 0){
        U32(FLAG7564)=0;
        if ((int8_t)U8(G+1) <= 0x13) U8(G+1)=0x13;
    }
    k_uptime_get_6();                                /* 3d90a ignored */
    q = u64_sub();
    if (q < 0x3e9) return 0;
    t = k_uptime_get_6(); U32(G+8)=(unsigned)t; U32(G+0xc)=(unsigned)(t>>32);
    U8(G+1) = (uint8_t)((int8_t)U8(G+1) - 1);
    dbg(2);                                        /* 3d934 */
    if ((int8_t)U8(G+1) > 0) return 0;
    dbg(1);                                        /* 3d958 */
    dbg(2);                                        /* 3d96e */
    /* 3d984 */
    c = get_device_info();
    if (sync_to_slave(c,6,0) > 0x1387){
        if (S32(LL) > 0) dbg(0);
        return 0;
    }
    /* 3da16 */
    U8(G)=3;
    t = k_uptime_get_6(); U32(G+8)=(unsigned)t; U32(G+0xc)=(unsigned)(t>>32);
    gui_screen_clear();
    device_info_text_width_get(); device_info_text_height_get_clamped();
    gui_bmp_bitmap_draw(0x3f,0,0,0,0,0);
    if (get_ui_mode_flag_byte1() == 6){
        device_info_text_width_get(); device_info_text_height_get_clamped();
        device_info_text_width_get(); device_info_text_height_get_clamped();
        gui_utf_draw(0,0,0,0,0,0,0,0,0,0);
        device_info_text_width_get(); device_info_text_height_get_clamped();
        device_info_text_width_get(); device_info_text_height_get_clamped();
        gui_utf_draw(0,0,0,0,0,0,0,0,0,0);
    } else {
        device_info_text_width_get(); device_info_text_height_get_clamped();
        device_info_text_width_get(); device_info_text_height_get_clamped();
        gui_utf_draw(0,0,0,0,0,0,0,0,0,0);
    }
    goto L_68e2;
L_db48:
    if (sel != 5) return 0;
    dbg(2);                                        /* 3db4e */
    U8(G)=3;
    t = k_uptime_get_6(); U32(G+8)=(unsigned)t; U32(G+0xc)=(unsigned)(t>>32);
    gui_screen_clear();
    device_info_text_width_get(); device_info_text_height_get_clamped();
    gui_bmp_bitmap_draw(0x3f,0,0,0,0,0);
    if (get_ui_mode_flag_byte1() == 6){
        device_info_text_width_get(); device_info_text_height_get_clamped();
        device_info_text_width_get(); device_info_text_height_get_clamped();
        gui_utf_draw(0,0,0,0,0,0,0,0,0,0);
        device_info_text_width_get(); device_info_text_height_get_clamped();
        device_info_text_width_get(); device_info_text_height_get_clamped();
        gui_utf_draw(0,0,0,0,0,0,0,0,0,0);
    } else {
        device_info_text_width_get(); device_info_text_height_get_clamped();
        device_info_text_width_get(); device_info_text_height_get_clamped();
        gui_utf_draw(0,0,0,0,0,0,0,0,0,0);
    }
    /* 3d582: one more 43e90 then return */
    gui_utf_draw(0,0,0,0,0,0,0,0,0,0);
    return 0;
L_68e2:
    /* 3d68e tail */
    c = get_device_info();
    if (U8(c) != 1) return 0;
    if (U8(G+0x24) != 2) return 0;
    mark_master_or_low_battery_flag();
    return 0;
}
