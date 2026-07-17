/* Reconstructed main @ 0x00016eb8 (raw: FUN_00016eb8).
 * Exact extent 0x7ac: live code [16eb8,17200), [17264,1750c),
 * [1756c,17664); jumped-over literal islands [17200,17264) and
 * [1750c,1756c); trailing literals begin at 0x17664. */
#include <stdint.h>

/* Readable callee <- raw identity @ address. */
extern uintptr_t boot_uptime_seconds_capture(void);             /* FUN_0004a500 @ 0x4a500 */
extern uintptr_t FUN_0004f564(unsigned, ...);                    /* @ 0x4f564 */
extern uintptr_t FUN_0004f770(void *, ...);                      /* @ 0x4f770 */
extern uintptr_t log_message(uintptr_t, ...);                    /* DEBUG_PRINT/FUN_0007dda4 */
extern uintptr_t debug_print(uintptr_t, ...);                    /* FUN_00019c70 @ 0x19c70 */
extern uintptr_t k_timer_start(void *, uint64_t, uint64_t);      /* FUN_00075174 @ 0x75174 */
extern uintptr_t serialization_init(void);                       /* FUN_00025c54 @ 0x25c54 */
extern void *malloc(unsigned);                                   /* FUN_00076d6c @ 0x76d6c */
extern uintptr_t memset_bytes(void *, int, unsigned);            /* FUN_00086c78 @ 0x86c78 */
extern uintptr_t FUN_0007c030(void *, unsigned);                 /* @ 0x7c030 */
extern uintptr_t change_work_mode_to(unsigned);                  /* @ mapped raw target */
extern uintptr_t set_device_sync_timestamp(uint32_t);            /* FUN_0007d230 @ 0x7d230 */
extern uintptr_t FUN_000406e4(void);                             /* @ 0x406e4 */
extern uintptr_t register_ipc_service_context(void *);           /* FUN_00025d40 @ 0x25d40 */
extern uintptr_t spi_master_install_ops(void *);                 /* FUN_0002659c @ 0x2659c */
extern int button_init(void);                                    /* FUN_00017a40 @ 0x17a40 */
extern int ext_flash_api_init(void *, void *, void *);           /* FUN_0002e4e8 @ 0x2e4e8 */
extern uintptr_t sett_init(void *);                              /* FUN_00022518 @ 0x22518 */
extern uintptr_t init_analytics_settings(void *);                /* FUN_0007c360 @ 0x7c360 */
extern uint64_t runtime_info_sync(void *);                       /* FUN_00016268 @ 0x16268 */
extern uintptr_t mutex_lock_syscall_handler(void *, ...);        /* FUN_00072908 @ 0x72908 */
extern uintptr_t ancs_ctx_init(void *);                          /* FUN_00018208 @ 0x18208 */
extern uintptr_t power_for_panel(void);                          /* FUN_00015df4 @ 0x15df4 */
extern uintptr_t burial_point_record_info_init(void);            /* FUN_0004ab3c @ 0x4ab3c */
extern uintptr_t power_for_imu_and_mic(void);                    /* FUN_00015f80 @ 0x15f80 */
extern uintptr_t lsm6dso_init_chip(uintptr_t);                   /* FUN_000622a0 @ 0x622a0 */
extern uintptr_t register_imu_funsion_context(void *);           /* FUN_00026250 @ 0x26250 */
extern uintptr_t FUN_0002e8fc(void *);                           /* @ 0x2e8fc */
extern uintptr_t quicknote_buffer_pool_init(void *);             /* FUN_00047148 @ 0x47148 */
extern uintptr_t st25dv_read_chip_ids(void);                     /* FUN_00025290 @ 0x25290 */
extern uintptr_t init_dashboard_info(void *);                   /* FUN_00036ed8 @ 0x36ed8 */
extern uintptr_t getDashboardStartUpModeInfofromFlash(void);     /* FUN_00023df4 @ 0x23df4 */
extern uintptr_t getAppLanguageInfofromFlash(void);              /* FUN_00023d0c @ 0x23d0c */
extern uintptr_t drain_setting_storage_queue(void);              /* FUN_00023acc @ 0x23acc */
extern uintptr_t drain_quick_note_data_queue(void);              /* FUN_000243fc @ 0x243fc */
extern uintptr_t device_info_register_persistent_fields(void *); /* FUN_00023230 @ 0x23230 */
extern int z_device_is_ready(const void *);                      /* FUN_0008638c @ 0x8638c */
extern int fuel_gauge_sample_init_timestamp(const void *);       /* FUN_0002ea28 @ 0x2ea28 */
extern int FUN_00062644(const void *);                           /* @ 0x62644 */
extern uintptr_t FUN_00016110(void);                             /* @ 0x16110 */
extern int product_code_is_supported_egp_family(void);           /* FUN_0007cefc @ 0x7cefc */
extern uintptr_t FUN_0002ea78(void);                             /* @ 0x2ea78 */
extern uintptr_t pt_nfc_eeprom_link_start(void);                 /* FUN_00030c90 @ 0x30c90 */
extern uintptr_t notification_system_init(void);                 /* FUN_00034944 @ 0x34944 */
extern uintptr_t read_rtc_counter_ms(void *);                    /* FUN_0007d0aa @ 0x7d0aa */
extern uintptr_t FUN_00032808(unsigned);                         /* @ 0x32808 */
extern uintptr_t run_main_dispatch_thread(void *);               /* FUN_0002a65c @ 0x2a65c */
extern uint64_t FUN_0002eaa8(void);                              /* @ 0x2eaa8 */
extern uintptr_t switch_to_dfu_mode(void *);                     /* FUN_000158bc @ 0x158bc */
extern uint64_t app_msleep_thunk_a(unsigned);                    /* FUN_0007c038 @ 0x7c038 */
extern uintptr_t rproc_virtio_negotiate_features(void *, unsigned); /* FUN_0007c34a @ 0x7c34a */
extern uintptr_t dmic_stream_start(void);                        /* FUN_0002f080 @ 0x2f080 */
extern uintptr_t check_device_readiness(void);                   /* FUN_000167b4 @ 0x167b4 */

#define log_record_alloc                  FUN_0004f564
#define log_record_submit                 FUN_0004f770
#define semaphore_init                    FUN_0007c030
#define clear_even_ai_line_state          FUN_000406e4
#define imu_fusion_context_init           FUN_0002e8fc
#define fuel_gauge_configure              FUN_00062644
#define fuel_gauge_program_defaults       FUN_00016110
#define fuel_gauge_enable_measurements    FUN_0002ea78
#define dashboard_mode_publish            FUN_00032808
#define fuel_gauge_enable_current         FUN_0002eaa8

#define g_log_level                    (*(volatile int32_t *)0x2000230cUL)
#define g_log_use_alt_sink             (*(volatile int32_t *)0x20007554UL)
#define g_ambient_light_sensor_ready   (*(volatile int32_t *)0x200069f8UL)
#define device_info                    (*(volatile uintptr_t *)0x200069fcUL)
#define g_runtime_mode_flag            (*(volatile uint8_t *)0x2000ff6eUL)

#define B8(base, off)      (*(volatile uint8_t *)((base) + (off)))
#define H16(base, off)     (*(volatile uint16_t *)((base) + (off)))
#define W32(base, off)     (*(volatile uint32_t *)((base) + (off)))

typedef uintptr_t (*hook0_t)(void);
typedef uintptr_t (*hook1_t)(void *);

static __attribute__((always_inline)) inline uintptr_t call_hook(uintptr_t context,
                                                                 unsigned slot,
                                                                 unsigned owner)
{
    return ((hook1_t)(uintptr_t)W32(context, slot))((void *)(context + owner));
}

void main(void)
{
    boot_uptime_seconds_capture();

    /* Register the initial runtime log item.  The firmware assumes allocation
     * succeeds: only the optional link write is guarded before fixed fields. */
    uintptr_t log_record = log_record_alloc(0x10);
    if (log_record != 0)
        W32(log_record, 4) = 0x000fa9b4;
    W32(log_record, 8) = 0x000faa2c;
    B8(log_record, 0x0c) = 0;
    log_record_submit((void *)log_record);
    if (g_log_level > 0) {
        if (g_log_use_alt_sink == 0)
            log_message(0x00099835, 0x00099bb2, 0x00099830);
        else
            debug_print(0x00099835, 0x00099bb2, 0x00099830);
    }

    k_timer_start((void *)0x20003700UL, 0x667ULL, 0x667ULL);
    serialization_init();
    if (g_log_level > 1) {
        if (g_log_use_alt_sink == 0)
            log_message(0x0009985c, 0x00099bb2, 1, 4, 5,
                        0x000998ad, 0x00099899);
        else
            debug_print(0x0009985c, 0x00099bb2, 1, 4, 5,
                        0x000998ad, 0x00099899);
        if (g_log_use_alt_sink == 0)
            log_message(0x000998b5, 0x00099ba5);
        else
            debug_print(0x000998b5, 0x00099ba5);
    }

    uintptr_t context = (uintptr_t)malloc(0x1188);
    memset_bytes((void *)context, 0, 0x1188);
    W32(context, 0xfda) = 0xffffffff;
    H16(context, 0xfde) = 0xffff;
    W32(context, 0xfe0) = 0xffffffff;
    H16(context, 0xfe4) = 0xffff;
    B8(context, 0) = 1;
    device_info = context;

    semaphore_init((void *)(context + 0x08), 1);
    semaphore_init((void *)(context + 0x20), 10);
    semaphore_init((void *)(context + 0x38), 1);
    semaphore_init((void *)(context + 0x50), 1);
    uintptr_t loop_lock = context + 0x68;
    semaphore_init((void *)(context + 0xaf4), 1);
    semaphore_init((void *)loop_lock, 1);
    semaphore_init((void *)(context + 0x80), 1);
    semaphore_init((void *)(context + 0x98), 1);
    semaphore_init((void *)(context + 0xb0), 1);
    B8(context, 1) = 0xff;
    H16(context, 0x105c) = 0;
    change_work_mode_to(0);

    uintptr_t allocation = (uintptr_t)malloc(0x6a);
    W32(context, 0xfec) = allocation;
    if (allocation) memset_bytes((void *)allocation, 0, 0x6a);
    set_device_sync_timestamp(0x65920080);
    W32(context, 0xff0) = (uintptr_t)malloc(7);
    allocation = (uintptr_t)malloc(5);
    W32(context, 0x1054) = allocation;
    if (allocation) {
        W32(allocation, 0) = 0;
        B8(allocation, 4) = 0;
    }
    allocation = (uintptr_t)malloc(0x217);
    W32(context, 0xffc) = allocation;
    if (allocation) memset_bytes((void *)allocation, 0, 0x217);
    W32(context, 0x1000) = (uintptr_t)malloc(0xf5);
    W32(context, 0x1004) = (uintptr_t)malloc(0x198);
    W32(context, 0x1008) = (uintptr_t)malloc(0x198);
    W32(context, 0x100c) = (uintptr_t)malloc(0x199);
    allocation = (uintptr_t)malloc(0x50f);
    W32(context, 0x1020) = allocation;
    if (allocation) memset_bytes((void *)allocation, 0, 0x50f);
    allocation = (uintptr_t)malloc(0x201);
    W32(context, 0x1024) = allocation;
    if (allocation) memset_bytes((void *)allocation, 0, 0x201);
    allocation = (uintptr_t)malloc(0x201);
    W32(context, 0x1028) = allocation;
    if (allocation) memset_bytes((void *)allocation, 0, 0x201);
    allocation = (uintptr_t)malloc(0x16a);
    W32(context, 0xff4) = allocation;
    if (allocation) {
        B8(allocation, 0x168) = 0;
        W32(allocation, 0x164) = 0;
    }
    W32(context, 0xff8) = (uintptr_t)malloc(0xaf);
    allocation = (uintptr_t)malloc(0x0b);
    W32(context, 0x1010) = allocation;
    if (allocation) {
        W32(allocation, 0) = 0;
        W32(allocation, 4) = 0;
        W32(allocation, 7) = 0;
    }
    W32(context, 0x1014) = (uintptr_t)malloc(0x21);
    clear_even_ai_line_state();
    allocation = (uintptr_t)malloc(1);
    W32(context, 0x1018) = allocation;
    if (allocation) B8(allocation, 0) = 0;
    allocation = (uintptr_t)malloc(2);
    W32(context, 0x101c) = allocation;
    if (allocation) H16(allocation, 0) = 0;

    W32(context, 0x1069) = 0xffffffff;
    W32(context, 0x106c) = 0xffffffff;
    H16(context, 0x1070) = 0;
    register_ipc_service_context((void *)(context + 0x714));

    /* Four named IPC services share the registrar installed at +0x778. */
    B8(context, 0x6e4) = 1;
    W32(context, 0x6e8) = 0x000998da;
    W32(context, 0x6ec) = 0x000162ed;
    call_hook(context, 0x778, 0x6e4);
    B8(context, 0x6f0) = 6;
    W32(context, 0x6f4) = 0x000998e7;
    W32(context, 0x6f8) = 0x00016bf1;
    B8(context, 0x6fc) = 4;
    W32(context, 0x700) = 0x000998fc;
    W32(context, 0x704) = 0x00015961;
    B8(context, 0x708) = 5;
    W32(context, 0x70c) = 0x00099908;
    W32(context, 0x710) = 0x0007c00d;
    call_hook(context, 0x778, 0x6f0);
    call_hook(context, 0x778, 0x6fc);
    call_hook(context, 0x778, 0x708);

    W32(context, 0xb24) = 0;
    W32(context, 0xb28) = 0x0a090804;
    H16(context, 0xb2c) = 0x200b;
    spi_master_install_ops((void *)(context + 0xb10));
    /* The durable catalog retains this RAM cell's historical sensor name;
     * button_init publishes the boot-button mode consumed below. */
    g_ambient_light_sensor_ready = button_init();
    B8(context, 0x1089) = (uint8_t)ext_flash_api_init(
        (void *)(context + 0x1030), (void *)(context + 0x1034),
        (void *)(context + 0x1038));
    B8(context, 1) = 0;
    sett_init((void *)(context + 0x103c));
    init_analytics_settings((void *)context);

    if (g_ambient_light_sensor_ready == 0) {
        B8(context, 0) = 1;
        if (g_log_level > 0) {
            if (g_log_use_alt_sink == 0) log_message(0x00099919, 0x00099b4c);
            else debug_print(0x00099919, 0x00099b4c);
        }
    } else if (g_ambient_light_sensor_ready == 1) {
        B8(context, 0) = 2;
        if (g_log_level > 0) {
            if (g_log_use_alt_sink == 0) log_message(0x0009992e, 0x00099b4c);
            else debug_print(0x0009992e, 0x00099b4c);
        }
    } else if (g_log_level > 0) {
        if (g_log_use_alt_sink == 0) log_message(0x00099942, 0x00099b4c);
        else debug_print(0x00099942, 0x00099b4c);
    }

    uint64_t sync_result = runtime_info_sync((void *)context);
    if (B8(context, 0) == 1) {
        H16(context, 0xfcc) = 0x0401;
        B8(context, 0xfce) = 5;
        B8(context, 0xe4) |= 4;
    } else if (B8(context, 0) == 2) {
        B8(context, 0xfcf) = 1;
        H16(context, 0xfd0) = 0x0504;
        B8(context, 0x6de) |= 4;
    }
    mutex_lock_syscall_handler((void *)(context + 8),
                               (uint32_t)(sync_result >> 32), -1, -1);

    if (B8(context, 1) != 1) {
        ancs_ctx_init((void *)(context + 0x77c));
        power_for_panel();
        if (B8(context, 0) == 1) {
            burial_point_record_info_init();
            k_timer_start((void *)0x200036c8UL, 0x1e0000ULL,
                          0x1e0000ULL);
            power_for_imu_and_mic();
            W32(context, 0xf00) = 0x00087d58;
            lsm6dso_init_chip(0x00087d58);
            register_imu_funsion_context((void *)(context + 0xee4));
            imu_fusion_context_init((void *)(context + 0xf80));
        } else if (B8(context, 0) == 2) {
            power_for_imu_and_mic();
            W32(context, 0xf00) = 0x00087d58;
            lsm6dso_init_chip(0x00087d58);
        }
        quicknote_buffer_pool_init((void *)(context + 0xb6c));
        st25dv_read_chip_ids();
        init_dashboard_info((void *)W32(device_info, 0xfec));
        getDashboardStartUpModeInfofromFlash();
        getAppLanguageInfofromFlash();
        drain_setting_storage_queue();
        drain_quick_note_data_queue();
        B8(context, 0x108e) = 0;
        H16(context, 0xed8) = H16(context, 0xede);
        B8(context, 0x108c) = 0;
    }

    if (g_log_level > 1) {
        if (g_log_use_alt_sink == 0) log_message(0x0009995c, 0x00099ba5);
        else debug_print(0x0009995c, 0x00099ba5);
        if (g_log_use_alt_sink == 0) log_message(0x00099969, 0x00099b3d);
        else debug_print(0x00099969, 0x00099b3d);
    }

    device_info_register_persistent_fields((void *)context);
    int result = (int)call_hook(context, 0x77c, 0x77c);
    if (result != 0 && g_log_level > 1) {
        if (g_log_use_alt_sink == 0) log_message(0x00099976, 0x00099b3d, result);
        else debug_print(0x00099976, 0x00099b3d, result);
    }
    if (B8(context, 0) == 1) {
        result = (int)call_hook(context, 0xf70, 0xee4);
        if (result != 0 && g_log_level > 1) {
            if (g_log_use_alt_sink == 0) log_message(0x0009999c, 0x00099b3d, result);
            else debug_print(0x0009999c, 0x00099b3d, result);
        }
        result = (int)call_hook(context, 0xf80, 0xf80);
        if (result != 0 && g_log_level > 1) {
            if (g_log_use_alt_sink == 0) log_message(0x000999c2, 0x00099b3d, result);
            else debug_print(0x000999c2, 0x00099b3d, result);
        }
    }

    const void *fuel_gauge = (const void *)0x00087cb0UL;
    uintptr_t failure_message = 0x000999e4;
    if (z_device_is_ready(fuel_gauge)) {
        log_message(0x000999ff, *(const uint32_t *)fuel_gauge);
        const void *fuel_config = (const void *)0x00087d70UL;
        failure_message = 0x00099a23;
        if (z_device_is_ready(fuel_config)) {
            failure_message = 0x00099a3e;
            if (fuel_gauge_sample_init_timestamp(fuel_config) >= 0) {
                failure_message = 0x00099a60;
                if (fuel_gauge_configure(fuel_config) >= 0) {
                    log_message(0x00099a7f);
                    log_message(0x00099a94);
                    fuel_gauge_program_defaults();
                    if (product_code_is_supported_egp_family()) {
                        log_message(0x00099aa4);
                        fuel_gauge_enable_measurements();
                    }
                    result = (int)call_hook(context, 0xb10, 0xb10);
                    if (result != 0 && g_log_level > 1) {
                        if (g_log_use_alt_sink == 0) log_message(0x00099acf, 0x00099b3d, result);
                        else debug_print(0x00099acf, 0x00099b3d, result);
                    }
                    result = (int)call_hook(context, 0xb6c, 0xb6c);
                    if (result != 0 && g_log_level > 1) {
                        if (g_log_use_alt_sink == 0) log_message(0x00099af4, 0x00099b3d, result);
                        else debug_print(0x00099af4, 0x00099b3d, result);
                    }
                    pt_nfc_eeprom_link_start();
                    notification_system_init();
                    if (g_log_level > 1) {
                        if (g_log_use_alt_sink == 0) log_message(0x00099b1e, 0x00099b3d);
                        else debug_print(0x00099b1e, 0x00099b3d);
                    }
                    W32(context, 0x1078) = 0;
                    read_rtc_counter_ms((void *)(context + 0x1078));
                    dashboard_mode_publish(*(volatile uint8_t *)0x2007fc70UL);
                    goto startup_complete;
                }
            }
        }
    }
    log_message(failure_message);

startup_complete:
    run_main_dispatch_thread((void *)context);
    uint64_t loop_state = fuel_gauge_enable_current();
    for (;;) {
        mutex_lock_syscall_handler((void *)loop_lock,
                                   (uint32_t)(loop_state >> 32), -1, -1);
        if (g_runtime_mode_flag == 1)
            switch_to_dfu_mode((void *)loop_lock);
        for (;;) {
            uint8_t pending = B8(context, 0x1059);
            if (pending == 0) break;
            if (pending & 1) {
                rproc_virtio_negotiate_features((void *)context, 0);
                B8(context, 0x1059) &= (uint8_t)~1u;
            } else if (pending & 2) {
                B8(context, 0xfea) = 11;
                B8(context, 0x1059) &= (uint8_t)~2u;
            } else if (pending & 4) {
                dmic_stream_start();
                B8(context, 0x1059) &= (uint8_t)~4u;
            } else if (pending & 8) {
                check_device_readiness();
                B8(context, 0x1059) &= (uint8_t)~8u;
            }
        }
        loop_state = app_msleep_thunk_a(1);
    }
}
