#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_imu_fusion_state__param_0019           [param_0019; G1-original]
 *   local_a0         => struct g1_layout_imu_fusion_state_vector__stack_0782    [stack_0782; G1-original]
 * Raw function identity: 0x0000fe88.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0000fe88 @ 0x0000fe88
 * public-name: imu_fusion_thread
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   dcmp_negate_rhs                          <= FUN_0000d588 @ 0x0000d588
 *   __aeabi_dadd                             <= FUN_0000d58c @ 0x0000d58c
 *   __floatsidf                              <= FUN_0000d824 @ 0x0000d824
 *   __extendsfdf2                            <= FUN_0000d848 @ 0x0000d848
 *   __muldf3                                 <= FUN_0000d8f8 @ 0x0000d8f8
 *   __divdf3                                 <= FUN_0000db4c @ 0x0000db4c
 *   __truncdfsf2                             <= FUN_0000dee8 @ 0x0000dee8
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   get_current_work_mode                    <= FUN_00016940 @ 0x00016940
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   get_ui_mode_flag2                        <= FUN_00023eec @ 0x00023eec
 *   SendDashboardLockInfoToApp               <= FUN_00025e2c @ 0x00025e2c
 *   panel_level_calc_cached                  <= FUN_00025ecc @ 0x00025ecc
 *   imu_fusion_state_init                    <= FUN_000265b8 @ 0x000265b8
 *   imu_mahony_ahrs_update                   <= FUN_00026624 @ 0x00026624
 *   orientation_filter_update_dt             <= FUN_000267ac @ 0x000267ac
 *   orientation_get_yaw_deg                  <= FUN_000267e8 @ 0x000267e8
 *   orientation_get_pitch_deg                <= FUN_00026808 @ 0x00026808
 *   orientation_get_heading_deg              <= FUN_00026828 @ 0x00026828
 *   send_event                               <= FUN_000276ec @ 0x000276ec
 *   now_has_persist_task                     <= FUN_0002be64 @ 0x0002be64
 *   is_battery_critical                      <= FUN_00032ee4 @ 0x00032ee4
 *   is_msg_expiration                        <= FUN_0003444c @ 0x0003444c
 *   cal_panel_canvas_coord                   <= FUN_00042fb0 @ 0x00042fb0
 *   send_response_data_to_msgqueue           <= FUN_00047b1c @ 0x00047b1c
 *   send_response_data_to_ble                <= FUN_00047ba8 @ 0x00047ba8
 *   read_volatile_u32_a                      <= FUN_0007ca4e @ 0x0007ca4e
 *   set_shutdown_flag                        <= FUN_0007cbfe @ 0x0007cbfe
 *   prepare_quick_note_mode                  <= FUN_0007cdb6 @ 0x0007cdb6
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_28000                             @ 0x00028000
 *   rodata_88a44                             @ 0x00088a44
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_dashboard_lock_sent_flags              @ 0x2000756c
 *   g_dashboard_lock_ready_flags             @ 0x20007570
 *   g_20007a88                               @ 0x20007a88
 *   g_20007a8c                               @ 0x20007a8c
 *   g_20007a90                               @ 0x20007a90
 *   g_20007a94                               @ 0x20007a94
 *   g_dashboard_reset_pending_flags          @ 0x20007aa0
 *   g_dashboard_lock_pending_flag            @ 0x20007aa4
 *   g_app_switch_pending_flag                @ 0x20007aa8
 *   g_ble_switch_status_reason               @ 0x20007aac
 *   g_20007ab0                               @ 0x20007ab0
 *   g_20007ab1                               @ 0x20007ab1
 *   g_20007ab4                               @ 0x20007ab4
 *   g_20007ab8                               @ 0x20007ab8
 *   g_20007abc                               @ 0x20007abc
 *   g_20007ac0                               @ 0x20007ac0
 *   g_20007ac4                               @ 0x20007ac4
 *   g_20007ac8                               @ 0x20007ac8
 *   g_20007acc                               @ 0x20007acc
 *   g_20007ad0                               @ 0x20007ad0
 *   g_20007ad4                               @ 0x20007ad4
 *   g_20007ad8                               @ 0x20007ad8
 *   g_20007adc                               @ 0x20007adc
 *   g_20007ae0                               @ 0x20007ae0
 *   g_20007ae4                               @ 0x20007ae4
 *   g_20007ae8                               @ 0x20007ae8
 *   g_20007aec                               @ 0x20007aec
 *   g_20018d96                               @ 0x20018d96
 *   g_esb_notify_sync_substate               @ 0x20018d98
 */
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

extern void log_message(unsigned long, ...);
extern void debug_print(unsigned long, ...);
extern int memset_bytes(int,int,int);
extern int firmware_function_0007ca72(int,int);
extern i64 thunk_FUN_00074f68(void);
extern int is_battery_critical(void);
extern int set_shutdown_flag(void*,int);
extern int sync_to_slave(void*,int,int,int);
extern int get_current_work_mode(void);
extern int change_work_mode_to(int);
extern int imu_fusion_state_init(void*);
typedef int  (*qfn_t)(int,int);
typedef void (*ffn_t)(int,int,void*);
extern u64 __floatsidf(int); extern u64 __divdf3(u32,u32,u32,u32); extern u64 __aeabi_dadd(u32,u32,u32,u32);
extern u64 __muldf3(u32,u32,u32,u32); extern u64 __extendsfdf2(u32); extern u64 dcmp_negate_rhs(u32,u32,u32,u32);
extern u32 __truncdfsf2(u32,u32);
extern float orientation_filter_update_dt(int);
extern void imu_mahony_ahrs_update(float,float,float,float,float,float,float,void*);
extern float orientation_get_heading_deg(void*); extern float orientation_get_pitch_deg(void*); extern float orientation_get_yaw_deg(void*);
extern int panel_level_calc_cached(void*); extern int SendDashboardLockInfoToApp(void);
extern int now_has_persist_task(void*,int); extern int is_msg_expiration(void); extern int get_ui_mode_flag2(void);
extern int prepare_quick_note_mode(void*,int); extern int send_event(int);
extern int get_device_info(void); extern int read_volatile_u32_a(void*);
extern int send_response_data_to_msgqueue(int,int); extern int send_response_data_to_ble(void);
extern int cal_panel_canvas_coord(void*,void*);

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

    memset_bytes((int)buf1, 0, 0x18);
    memset_bytes((int)buf2, 0, 0x18);

    if (p[0x14] != 0) {
        if (1 < I(((unsigned long)&g_log_level) /*=0x2000230c*/)) { if (I(((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)==0) log_message(((unsigned long)"%s(): error\n\n"),((unsigned long)"imu_fusion_thread")); else debug_print(((unsigned long)"%s(): error\n\n"),((unsigned long)"imu_fusion_thread")); }
        return;
    }
    if (1 < I(((unsigned long)&g_log_level) /*=0x2000230c*/)) { if (I(((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)==0) log_message(((unsigned long)"%s(): start imu looper\n\n"),((unsigned long)"imu_fusion_thread")); else debug_print(((unsigned long)"%s(): start imu looper\n\n"),((unsigned long)"imu_fusion_thread")); }
    p[0] = 1;

    while (p[0x15] != 0) {
        while (p[-0xee3]==1 || p[-0xee3]==8) firmware_function_0007ca72(((unsigned long)&rodata_28000) /*=0x28000*/,0);

        iVar6 = is_battery_critical();
        if (iVar6 == 0) {
            if (p[0x106] == 0x0b) { p[0] = 2; }
            else if (p[0x106] != 0x0c) {
                if ((int)((unsigned)(u16)(*(u16*)(p+0x178)) << 0x1a) < 0) {
                    i64 v = thunk_FUN_00074f68();
                    local_a4 = (unsigned)(((u64)v * 1000ULL) >> 15);
                    if (1000u < (unsigned)(local_a4 - U(((unsigned long)&g_20007a94) /*=0x20007a94*/))) imu_fusion_state_init(p+0x28);
                    goto Lffb4;
                }
                p[0] = 1; uVar7 = 0xccd; goto Lff38;
            } else {
                p[0] = 1; set_shutdown_flag(q8,1);
                if (p[-0xe0f] != 7) {
                    sync_to_slave(q8,1,0,0);
                    if (get_current_work_mode() == 2) change_work_mode_to(3);
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

        dv = __floatsidf(I(buf1 + 4));
        dv = __divdf3(LO64(dv),HI64(dv),0,0x412e8480);
        part = __floatsidf(I(buf1));
        dv = __aeabi_dadd(LO64(dv),HI64(dv),LO64(part),HI64(part));
        dv = __muldf3(LO64(dv),HI64(dv),0,0x40240000);
        d1 = __truncdfsf2(LO64(dv),HI64(dv));

        dv = __floatsidf(I(buf1 + 12));
        dv = __divdf3(LO64(dv),HI64(dv),0,0x412e8480);
        part = __floatsidf(I(buf1 + 8));
        dv = __aeabi_dadd(LO64(dv),HI64(dv),LO64(part),HI64(part));
        dv = __muldf3(LO64(dv),HI64(dv),0,0x40240000);
        d2 = __truncdfsf2(LO64(dv),HI64(dv));

        dv = __floatsidf(I(buf1 + 20));
        dv = __divdf3(LO64(dv),HI64(dv),0,0x412e8480);
        part = __floatsidf(I(buf1 + 16));
        dv = __aeabi_dadd(LO64(dv),HI64(dv),LO64(part),HI64(part));
        dv = __muldf3(LO64(dv),HI64(dv),0,0x40240000);
        d3 = __truncdfsf2(LO64(dv),HI64(dv));

        dv = __floatsidf(I(buf2 + 4));
        dv = __divdf3(LO64(dv),HI64(dv),0,0x412e8480);
        part = __floatsidf(I(buf2));
        dv = __aeabi_dadd(LO64(dv),HI64(dv),LO64(part),HI64(part));
        d4 = __truncdfsf2(LO64(dv),HI64(dv));

        dv = __floatsidf(I(buf2 + 12));
        dv = __divdf3(LO64(dv),HI64(dv),0,0x412e8480);
        part = __floatsidf(I(buf2 + 8));
        dv = __aeabi_dadd(LO64(dv),HI64(dv),LO64(part),HI64(part));
        d5 = __truncdfsf2(LO64(dv),HI64(dv));

        dv = __floatsidf(I(buf2 + 20));
        dv = __divdf3(LO64(dv),HI64(dv),0,0x412e8480);
        part = __floatsidf(I(buf2 + 16));
        dv = __aeabi_dadd(LO64(dv),HI64(dv),LO64(part),HI64(part));
        d6 = __truncdfsf2(LO64(dv),HI64(dv));

        I(p+0x198) = (int)as_f(d1);
        I(p+0x19c) = (int)as_f(d2);
        I(p+0x1a0) = (int)as_f(d3);

        dv = __extendsfdf2(d4);
        dv = dcmp_negate_rhs(LO64(dv),HI64(dv),0x45a1cac1,0x3fadf3b6);
        d4 = __truncdfsf2(LO64(dv),HI64(dv));
        dv = __extendsfdf2(d5);
        dv = __aeabi_dadd(LO64(dv),HI64(dv),0x0a3d70a4,0x3fa0a3d7);
        d5 = __truncdfsf2(LO64(dv),HI64(dv));
        dv = __extendsfdf2(d6);
        dv = dcmp_negate_rhs(LO64(dv),HI64(dv),0x47ae147b,0x3f847ae1);
        d6 = __truncdfsf2(LO64(dv),HI64(dv));

        dt = orientation_filter_update_dt(p+0x28);
        imu_mahony_ahrs_update(as_f(d4),as_f(d5),as_f(d6),
                     as_f(d1),as_f(d2),as_f(d3),dt,p+0x28);
        roll = orientation_get_heading_deg(p+0x28);
        pitch = orientation_get_pitch_deg(p+0x28);
        yaw = orientation_get_yaw_deg(p+0x28);

        iVar27 = (int)(pitch * 100.0f);
        I(((unsigned long)&g_ble_switch_status_reason) /*=0x20007aac*/) = iVar27;
        I(((unsigned long)&g_app_switch_pending_flag) /*=0x20007aa8*/) = (int)(roll * 100.0f);
        I(((unsigned long)&g_dashboard_lock_pending_flag) /*=0x20007aa4*/) = (int)(yaw * 100.0f);

        iVar6 = is_battery_critical();
        if (iVar6 == 1 && p[0x106] == 0x0b) { p[0] = 2; uVar7 = 0x148; goto Lff38; }

        I(((unsigned long)&g_20007a94) /*=0x20007a94*/) = (int)local_a4;
        cnt = I(((unsigned long)&g_20007ab4) /*=0x20007ab4*/);
        I(((unsigned long)&g_20007ab4) /*=0x20007ab4*/) = cnt + 1;
        if (UB(((unsigned long)&g_20007ab0) /*=0x20007ab0*/) == 0) {
            if ((unsigned)(cnt + 1) < 0xc9) { uVar7 = 0x148; goto Lff38; }
            B(((unsigned long)&g_20007ab0) /*=0x20007ab0*/) = 1;
            F(((unsigned long)&g_20007acc) /*=0x20007acc*/) = roll; F(((unsigned long)&g_20007ad0) /*=0x20007ad0*/) = pitch; F(((unsigned long)&g_20007ad4) /*=0x20007ad4*/) = yaw;
        }
        panel_level_calc_cached(p);

        if (p[-0xe0f] == 0) {
            d = I(((unsigned long)&g_20007a90) /*=0x20007a90*/);
            ad = (iVar27 < d) ? d - iVar27 : iVar27 - d;
            if (0x31 < ad) goto L102e0;
            I(((unsigned long)&g_20007a90) /*=0x20007a90*/) = iVar27;
            I(((unsigned long)&g_20007a8c) /*=0x20007a8c*/) = 0;
            SendDashboardLockInfoToApp();
            goto L1027a;
        }

    L102e0:
        cVar2 = p[-0xe0f];
        I(((unsigned long)&g_20007a90) /*=0x20007a90*/) = iVar27;
        if (cVar2 == 0x0d) {
            p[-0xdf7] = 0x0c; p[-0xdf6] = 0;
            *(float*)(p-0xdf5) = roll; *(float*)(p-0xdf1) = pitch; *(float*)(p-0xded) = yaw;
        }
        I(((unsigned long)&g_ble_switch_status_reason) /*=0x20007aac*/) = iVar27;
        I(((unsigned long)&g_app_switch_pending_flag) /*=0x20007aa8*/) = (int)(roll * 100.0f);
        I(((unsigned long)&g_dashboard_lock_pending_flag) /*=0x20007aa4*/) = (int)(yaw * 100.0f);

        if (p[0] == 2) {
            if (iVar27 <= *(int*)(p+8) + 100 && *(int*)(p+0xc) <= iVar27) goto L10734;
            iVar6 = I(((unsigned long)&g_20007a8c) /*=0x20007a8c*/) + 1;
            if (iVar6 < 2) goto L1064c;
            I(((unsigned long)&g_20007a8c) /*=0x20007a8c*/) = -3;
            B(((unsigned long)&g_20018d96) /*=0x20018d96*/) = 1;
            if (I(((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/) == 0) log_message(((unsigned long)"bow head################################################\n")); else debug_print(((unsigned long)"bow head################################################\n"));
            send_event(3);
            p[0] = 1;
            {
                int e = p[-0xe0f];
                if (e==9||e==0x0c||e==0x0a||e==0x0b||e==7||e==0x0e||e==0x0f||e==0x10||e==0x11
                    || now_has_persist_task(q8, p[-0xe0f]) != 0) {
                    B(((unsigned long)&g_20018d96) /*=0x20018d96*/) = 0;
                    goto L103ea;
                }
            }
            p[-0xe19] = p[-0xf];
            if (p[-0xe0f] == 1) {
                sync_to_slave(q8,8,0,0);
            } else if (((p[0x1ab]==0) || is_msg_expiration()!=1) && get_ui_mode_flag2()==0) {
                sync_to_slave(q8,1,0,0);
            }
            if (p[0x1ab]==0 && get_ui_mode_flag2()==0) prepare_quick_note_mode(q8,0);
            goto L10544;
        }

        if (*(int*)(p+8) < iVar27 || iVar27 < *(int*)(p+0xc)) goto L10734;
        thunk_FUN_00074f68();
        iVar6 = I(((unsigned long)&g_20007a8c) /*=0x20007a8c*/) + 1;
        if (iVar6 < 2) { I(((unsigned long)&g_20007a8c) /*=0x20007a8c*/) = iVar6; goto L1027a; }
        I(((unsigned long)&g_20007a8c) /*=0x20007a8c*/) = -3;
        {
            u8 bv = (u8)p[0x10];
            if (p[-0xe0f]==0 && I(((unsigned long)&g_20007a88) /*=0x20007a88*/) <= iVar27) goto L1027a;
            B(((unsigned long)&g_20018d96) /*=0x20018d96*/) = 1;
            if (I(((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)==0) log_message(((unsigned long)"look up################################################,screen_id is %d, pitch_y is %d, pitch_threshold_bow_head is %d, pitch_threshold_level is %d\n"),p[-0xe0f],iVar27,*(int*)(p+8),bv); else debug_print(((unsigned long)"look up################################################,screen_id is %d, pitch_y is %d, pitch_threshold_bow_head is %d, pitch_threshold_level is %d\n"),p[-0xe0f],iVar27,*(int*)(p+8),bv);
            k = 0x65;
            while (1) {
                int iv = get_device_info();
                if (*(char*)(iv + 0x108f) != 0) break;
                if (UB(((unsigned long)&g_esb_notify_sync_substate) /*=0x20018d98*/) == 0) break;
                if (--k == 0) break;
                firmware_function_0007ca72(0x148,0);
            }
            send_event(2);
            (void)bv;
        }
        {
            int e = p[-0xe0f];
            if (e==9||e==0x0c||e==0x0a||e==0x0b||e==5||e==4||e==7||e==0x0e||e==0x0f||e==0x10||e==0x11) {
                p[0] = 2; B(((unsigned long)&g_20018d96) /*=0x20018d96*/)=0; goto L103ea;
            }
        }
        if (get_ui_mode_flag2() == 0) {
            iVar6 = read_volatile_u32_a((void*)((unsigned long)&g_dashboard_lock_ready_flags) /*=0x20007570*/);
            if ((iVar6 << 0x1e) < 0) {
                /* bit1 set: DAT_00010580/00010584 path */
                iVar6 = read_volatile_u32_a((void*)((unsigned long)&g_dashboard_reset_pending_flags) /*=0x20007aa0*/);
                if (-1 < (iVar6 << 0x1e)) {
                    iVar6 = read_volatile_u32_a((void*)((unsigned long)&g_dashboard_lock_sent_flags) /*=0x2000756c*/);
                    if (-1 < (iVar6 << 0x1e) && (read_volatile_u32_a((void*)((unsigned long)&g_dashboard_lock_ready_flags) /*=0x20007570*/) << 0x1e) < 0) {
                        if (2 < I(((unsigned long)&g_log_level) /*=0x2000230c*/)) { if (I(((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)==0) log_message(((unsigned long)"%s(): send dashboard lock info to app ,status = %d \n"),((unsigned long)"handle_attitude_trigger"),1); else debug_print(((unsigned long)"%s(): send dashboard lock info to app ,status = %d \n"),((unsigned long)"handle_attitude_trigger"),1); }
                        send_response_data_to_msgqueue(0,6);
                        send_response_data_to_ble();
                        I(((unsigned long)&g_dashboard_lock_sent_flags) /*=0x2000756c*/) |= 2;
                    }
                }
            } else {
                /* bit1 clear: enter work-mode-2 path */
                p[0] = 2; p[0x102] = 5; p[-0xe19] = p[-0xf];
                if (p[-0xee4] == 1) {
                    if (1 < I(((unsigned long)&g_log_level) /*=0x2000230c*/)) { if (I(((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)==0) log_message(((unsigned long)"%s(): master sync canvas_distance_gear:%d,raster_height_gear:%d\n"),((unsigned long)"handle_attitude_trigger"),p[-0x23],p[-0x24]); else debug_print(((unsigned long)"%s(): master sync canvas_distance_gear:%d,raster_height_gear:%d\n"),((unsigned long)"handle_attitude_trigger"),p[-0x23],p[-0x24]); }
                    sync_to_slave(q8,2,0,3);
                    cal_panel_canvas_coord(p-0x20, p-0x2c);
                }
                change_work_mode_to(2);
                iVar6 = read_volatile_u32_a((void*)((unsigned long)&g_dashboard_reset_pending_flags) /*=0x20007aa0*/);
                if (-1 < (iVar6 << 0x1e)) I(((unsigned long)&g_dashboard_reset_pending_flags) /*=0x20007aa0*/) |= 2;
            }
        } else {
            p[0] = 2;
        }
        goto L10544;

    L10734:
        {
            int cur = I(((unsigned long)&g_20007a8c) /*=0x20007a8c*/);
            I(((unsigned long)&g_20007a8c) /*=0x20007a8c*/) = (cur < 0) ? cur + 1 : 0;
        }
        goto L103ea;

    L1064c:
        I(((unsigned long)&g_20007a8c) /*=0x20007a8c*/) = iVar6;
        goto L1027a;

    L10544:
        B(((unsigned long)&g_20018d96) /*=0x20018d96*/) = 0;
        /* fallthrough */
    L1027a:
        if (p[0] == 1 && I(((unsigned long)&g_20007a8c) /*=0x20007a8c*/) <= 0) {
            thunk_FUN_00074f68();
            I(((unsigned long)&g_20007a88) /*=0x20007a88*/) = iVar27;
        }
        /* fallthrough */
    L103ea:
        {
            float la0 = roll, la1 = pitch, la2 = yaw;
            float corrected[3] = {0.0f, 0.0f, 0.0f};
            float d3f = la0 - F(((unsigned long)&g_20007acc) /*=0x20007acc*/);
            float d4f = la1 - F(((unsigned long)&g_20007ad0) /*=0x20007ad0*/);
            float d5f = la2 - F(((unsigned long)&g_20007ad4) /*=0x20007ad4*/);
            char c2 = *(char*)((unsigned long)&g_20007ab1) /*=0x20007ab1*/;
            if (c2 == 1) {
                float in[3]; in[0]=la0; in[1]=la1; in[2]=la2;
                for (k = 0; k < 3; k++) {
                    float diff = in[k] - F(((unsigned long)&g_20007ad8) /*=0x20007ad8*/ + 4*k);
                    if (!(__builtin_fabsf(diff) < 180.0f)) {
                        if (diff > 0.0f) diff -= 360.0f; else diff += 360.0f;
                    }
                    corrected[k] = F(((unsigned long)&g_20007ae4) /*=0x20007ae4*/ + 4*k) + diff;
                }
                if (!(__builtin_fabsf(d3f) <= 0.1f) ||
                    !(__builtin_fabsf(d4f) <= 0.1f) ||
                    !(__builtin_fabsf(d5f) <= 0.1f)) {
                    I(((unsigned long)&g_20007abc) /*=0x20007abc*/) = 0;
                } else {
                    int t = I(((unsigned long)&g_20007abc) /*=0x20007abc*/);
                    I(((unsigned long)&g_20007abc) /*=0x20007abc*/) = t + 1;
                    if (4 < t + 1) {
                        B(((unsigned long)&g_20007ab1) /*=0x20007ab1*/) = 2;
                        F(((unsigned long)&g_20007ae4) /*=0x20007ae4*/) = corrected[0];
                        F(((unsigned long)&g_20007ae8) /*=0x20007ae8*/) = corrected[1];
                        F(((unsigned long)&g_20007aec) /*=0x20007aec*/) = corrected[2];
                    }
                }
            } else if (c2 == 2) {
                I(((unsigned long)&g_20007ab8) /*=0x20007ab8*/) = 0; I(((unsigned long)&g_20007abc) /*=0x20007abc*/) = 0;
                I(((unsigned long)&g_20007ac0) /*=0x20007ac0*/) = 0; I(((unsigned long)&g_20007ac4) /*=0x20007ac4*/) = 0; I(((unsigned long)&g_20007ac8) /*=0x20007ac8*/) = 0;
                B(((unsigned long)&g_20007ab1) /*=0x20007ab1*/) = 0;
            } else if (c2 == 0) {
                float in[3]; in[0]=d3f; in[1]=d4f; in[2]=d5f;
                int matched = 0;
                for (k = 0; k < 3; k++) {
                    float x = in[k];
                    float thr = F(((unsigned long)&rodata_88a44) /*=0x88a44*/ + 4*k);
                    if (!(__builtin_fabsf(x) < thr)) {
                        sgn = (x < 0.0f) ? -1 : 1;
                        prev = I(((unsigned long)&g_20007ac0) /*=0x20007ac0*/ + 4*k);
                        I(((unsigned long)&g_20007ac0) /*=0x20007ac0*/ + 4*k) = sgn;
                        if (prev == sgn) matched++;
                    }
                }
                if (matched != 0) {
                    if (I(((unsigned long)&g_20007ab8) /*=0x20007ab8*/) == 0) {
                        F(((unsigned long)&g_20007ad8) /*=0x20007ad8*/) = la0; F(((unsigned long)&g_20007adc) /*=0x20007adc*/) = la1; F(((unsigned long)&g_20007ae0) /*=0x20007ae0*/) = la2;
                        I(((unsigned long)&g_20007ab8) /*=0x20007ab8*/) = 1;
                    } else {
                        int c = I(((unsigned long)&g_20007ab8) /*=0x20007ab8*/) + 1;
                        I(((unsigned long)&g_20007ab8) /*=0x20007ab8*/) = c;
                        if (4 < c) B(((unsigned long)&g_20007ab1) /*=0x20007ab1*/) = 1;
                    }
                }
            }
            F(((unsigned long)&g_20007acc) /*=0x20007acc*/) = la0; F(((unsigned long)&g_20007ad0) /*=0x20007ad0*/) = la1; F(((unsigned long)&g_20007ad4) /*=0x20007ad4*/) = la2;
            uVar7 = (p[0] == 2) ? 0x4de : 0xa3e;
        }
    Lff38:
        firmware_function_0007ca72(uVar7,0);
    }

    return;
}
