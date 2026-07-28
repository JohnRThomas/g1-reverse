struct device;
/* readable reconstruction; identity: FUN_00016eb8 @ 0x00016eb8
 * public-name: main
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   dev_page3_config_and_readback_dump       <= FUN_00016110 @ 0x00016110
 *   opt3007_init_ctx_setup                   <= FUN_0002e8fc @ 0x0002e8fc
 *   device_reg3_init_config                  <= FUN_0002ea78 @ 0x0002ea78
 *   display_dev_reg_config                   <= FUN_0002eaa8 @ 0x0002eaa8
 *   set_glassbox_charge_percent              <= FUN_00032808 @ 0x00032808
 *   arm_onboarding_watchdog                  <= FUN_000406e4 @ 0x000406e4
 *   app_event_alloc                          <= FUN_0004f564 @ 0x0004f564
 *   app_event_manager_submit                 <= FUN_0004f770 @ 0x0004f770
 *   panel_temp_calibration_init              <= FUN_00062644 @ 0x00062644
 *   sem_init_zero                            <= FUN_0007c030 @ 0x0007c030
 * address symbols (name @ address):
 *   ADDR_local_esbs_ipc_service_recv_THUMB   @ 0x00015961
 *   rodata_162ed                             @ 0x000162ed
 *   rodata_16bf1                             @ 0x00016bf1
 *   rodata_7c00d                             @ 0x0007c00d
 *   rodata_87cb0                             @ 0x00087cb0
 *   rodata_87d58                             @ 0x00087d58
 *   rodata_87d70                             @ 0x00087d70
 *   rodata_99830                             @ 0x00099830   [INLINED -- G6 literal batch]
 *   rodata_99835                             @ 0x00099835   [INLINED -- G6 literal batch]
 *   rodata_9985c                             @ 0x0009985c   [INLINED -- G6 literal batch]
 *   rodata_99899                             @ 0x00099899   [INLINED -- G6 literal batch]
 *   rodata_998ad                             @ 0x000998ad   [INLINED -- G6 literal batch]
 *   rodata_998b5                             @ 0x000998b5   [INLINED -- G6 literal batch]
 *   rodata_998da                             @ 0x000998da
 *   rodata_998e7                             @ 0x000998e7
 *   rodata_998fc                             @ 0x000998fc
 *   rodata_99908                             @ 0x00099908
 *   rodata_9992e                             @ 0x0009992e   [INLINED -- G6 literal batch]
 *   rodata_99942                             @ 0x00099942   [INLINED -- G6 literal batch]
 *   rodata_9995c                             @ 0x0009995c   [INLINED -- G6 literal batch]
 *   rodata_99969                             @ 0x00099969
 *   rodata_99976                             @ 0x00099976   [INLINED -- G6 literal batch]
 *   rodata_9999c                             @ 0x0009999c   [INLINED -- G6 literal batch]
 *   rodata_999c2                             @ 0x000999c2   [INLINED -- G6 literal batch]
 *   rodata_999e4                             @ 0x000999e4
 *   rodata_999ff                             @ 0x000999ff   [INLINED -- G6 literal batch]
 *   rodata_99a23                             @ 0x00099a23
 *   rodata_99a3e                             @ 0x00099a3e
 *   rodata_99a60                             @ 0x00099a60
 *   rodata_99a7f                             @ 0x00099a7f   [INLINED -- G6 literal batch]
 *   rodata_99a94                             @ 0x00099a94   [INLINED -- G6 literal batch]
 *   rodata_99aa4                             @ 0x00099aa4   [INLINED -- G6 literal batch]
 *   rodata_99acf                             @ 0x00099acf   [INLINED -- G6 literal batch]
 *   rodata_99af4                             @ 0x00099af4   [INLINED -- G6 literal batch]
 *   rodata_99b1e                             @ 0x00099b1e   [INLINED -- G6 literal batch]
 *   rodata_99b3d                             @ 0x00099b3d   [INLINED -- G6 literal batch]
 *   rodata_99b4c                             @ 0x00099b4c   [INLINED -- G6 literal batch]
 *   rodata_99ba5                             @ 0x00099ba5   [INLINED -- G6 literal batch]
 *   rodata_99bb2                             @ 0x00099bb2   [INLINED -- G6 literal batch]
 *   rodata_fa9b4                             @ 0x000fa9b4
 *   rodata_faa2c                             @ 0x000faa2c
 *   g_log_level                              @ 0x2000230c
 *   g_200036c8                               @ 0x200036c8
 *   g_20003700                               @ 0x20003700
 *   g_ambient_light_sensor_ready             @ 0x200069f8
 *   device_info                              @ 0x200069fc
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_runtime_mode_flag                      @ 0x2000ff6e
 *   g_2007fc70                               @ 0x2007fc70
 */
/* Reconstructed main @ 0x00016eb8 (raw: FUN_00016eb8).
 * Exact extent 0x7ac: live code [16eb8,17200), [17264,1750c),
 * [1756c,17664); jumped-over literal islands [17200,17264) and
 * [1750c,1756c); trailing literals begin at 0x17664. */
#include <stdint.h>
#include "../headers/g1_log.h"

/* Readable callee <- raw identity @ address. */
extern uintptr_t boot_uptime_seconds_capture(void);             /* FUN_0004a500 @ 0x4a500 */
extern uintptr_t app_event_alloc(unsigned, ...);                    /* @ 0x4f564 */
extern uintptr_t app_event_manager_submit(void *, ...);                      /* @ 0x4f770 */
/* DEBUG_PRINT/FUN_0007dda4 */
/* FUN_00019c70 @ 0x19c70 */
extern uintptr_t k_timer_start(void *, uint64_t, uint64_t);      /* FUN_00075174 @ 0x75174 */
extern uintptr_t serialization_init(void);                       /* FUN_00025c54 @ 0x25c54 */
extern void *malloc(unsigned);                                   /* FUN_00076d6c @ 0x76d6c */
extern uintptr_t memset_bytes(void *, int, unsigned);            /* FUN_00086c78 @ 0x86c78 */
extern uintptr_t sem_init_zero(void *, unsigned);                 /* @ 0x7c030 */
extern uintptr_t change_work_mode_to(unsigned);                  /* @ mapped raw target */
extern uintptr_t set_device_sync_timestamp(uint32_t);            /* FUN_0007d230 @ 0x7d230 */
extern uintptr_t arm_onboarding_watchdog(void);                             /* @ 0x406e4 */
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
extern uintptr_t opt3007_init_ctx_setup(void *);                           /* @ 0x2e8fc */
extern uintptr_t quicknote_buffer_pool_init(void *);             /* FUN_00047148 @ 0x47148 */
extern uintptr_t st25dv_read_chip_ids(void);                     /* FUN_00025290 @ 0x25290 */
extern uintptr_t init_dashboard_info(void *);                   /* FUN_00036ed8 @ 0x36ed8 */
extern uintptr_t getDashboardStartUpModeInfofromFlash(void);     /* FUN_00023df4 @ 0x23df4 */
extern uintptr_t getAppLanguageInfofromFlash(void);              /* FUN_00023d0c @ 0x23d0c */
extern uintptr_t drain_setting_storage_queue(void);              /* FUN_00023acc @ 0x23acc */
extern uintptr_t drain_quick_note_data_queue(void);              /* FUN_000243fc @ 0x243fc */
extern uintptr_t device_info_register_persistent_fields(void *); /* FUN_00023230 @ 0x23230 */
extern _Bool z_device_is_ready(const struct device *);                      /* FUN_0008638c @ 0x8638c */
extern int fuel_gauge_sample_init_timestamp(const void *);       /* FUN_0002ea28 @ 0x2ea28 */
extern int panel_temp_calibration_init(const void *);                           /* @ 0x62644 */
extern uintptr_t dev_page3_config_and_readback_dump(void);                             /* @ 0x16110 */
extern int product_code_is_supported_egp_family(void);           /* FUN_0007cefc @ 0x7cefc */
extern uintptr_t device_reg3_init_config(void);                             /* @ 0x2ea78 */
extern uintptr_t pt_nfc_eeprom_link_start(void);                 /* FUN_00030c90 @ 0x30c90 */
extern uintptr_t notification_system_init(void);                 /* FUN_00034944 @ 0x34944 */
extern uintptr_t read_rtc_counter_ms(void *);                    /* FUN_0007d0aa @ 0x7d0aa */
extern uintptr_t set_glassbox_charge_percent(unsigned);                         /* @ 0x32808 */
extern uintptr_t run_main_dispatch_thread(void *);               /* FUN_0002a65c @ 0x2a65c */
extern uint64_t display_dev_reg_config(void);                              /* @ 0x2eaa8 */
extern uintptr_t switch_to_dfu_mode(void *);                     /* FUN_000158bc @ 0x158bc */
extern uint64_t app_msleep_thunk_a(unsigned);                    /* FUN_0007c038 @ 0x7c038 */
extern uintptr_t rproc_virtio_negotiate_features(void *, unsigned); /* FUN_0007c34a @ 0x7c34a */
extern uintptr_t dmic_stream_start(void);                        /* FUN_0002f080 @ 0x2f080 */
extern uintptr_t check_device_readiness(void);                   /* FUN_000167b4 @ 0x167b4 */

#define log_record_alloc                  app_event_alloc
#define log_record_submit                 app_event_manager_submit
#define semaphore_init                    sem_init_zero
#define clear_even_ai_line_state          arm_onboarding_watchdog
#define imu_fusion_context_init           opt3007_init_ctx_setup
#define fuel_gauge_configure              panel_temp_calibration_init
#define fuel_gauge_program_defaults       dev_page3_config_and_readback_dump
#define fuel_gauge_enable_measurements    device_reg3_init_config
#define dashboard_mode_publish            set_glassbox_charge_percent
#define fuel_gauge_enable_current         display_dev_reg_config

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
            log_message(((unsigned long)"%s(): Synchronization using %s driver\n"), ((unsigned long)"main"), ((unsigned long)"mbox"));
        else
            debug_print(((unsigned long)"%s(): Synchronization using %s driver\n"), ((unsigned long)"main"), ((unsigned long)"mbox"));
    }

    k_timer_start((void *)0x20003700UL, 0x667ULL, 0x667ULL);
    serialization_init();
    if (g_log_level > 1) {
        if (g_log_use_alt_sink == 0)
            log_message(((unsigned long)"%s(): [Build Info: Ver:v%d.%d.%d Commit:%s] [Build Time:%s]\n"), ((unsigned long)"main"), 1, 4, 5,
                        ((unsigned long)"1b85815"), ((unsigned long)"2024-12-28 20:20:45"));
        else
            debug_print(((unsigned long)"%s(): [Build Info: Ver:v%d.%d.%d Commit:%s] [Build Time:%s]\n"), ((unsigned long)"main"), 1, 4, 5,
                        ((unsigned long)"1b85815"), ((unsigned long)"2024-12-28 20:20:45"));
        if (g_log_use_alt_sink == 0)
            log_message(((unsigned long)"%s(): [cpuapp] global context init\n\n"), ((unsigned long)"init_context"));
        else
            debug_print(((unsigned long)"%s(): [cpuapp] global context init\n\n"), ((unsigned long)"init_context"));
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
            if (g_log_use_alt_sink == 0) log_message(((unsigned long)"%s(): Master!------\n") /*=0x99919*/, ((unsigned long)"role_init"));
            else debug_print(((unsigned long)"%s(): Master!------\n") /*=0x99919*/, ((unsigned long)"role_init"));
        }
    } else if (g_ambient_light_sensor_ready == 1) {
        B8(context, 0) = 2;
        if (g_log_level > 0) {
            if (g_log_use_alt_sink == 0) log_message(((unsigned long)"%s(): Slave!------\n"), ((unsigned long)"role_init"));
            else debug_print(((unsigned long)"%s(): Slave!------\n"), ((unsigned long)"role_init"));
        }
    } else if (g_log_level > 0) {
        if (g_log_use_alt_sink == 0) log_message(((unsigned long)"%s(): error --hw_id:0x%x\n"), ((unsigned long)"role_init"));
        else debug_print(((unsigned long)"%s(): error --hw_id:0x%x\n"), ((unsigned long)"role_init"));
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
        if (g_log_use_alt_sink == 0) log_message(((unsigned long)"%s(): exit!\n"), ((unsigned long)"init_context"));
        else debug_print(((unsigned long)"%s(): exit!\n"), ((unsigned long)"init_context"));
        if (g_log_use_alt_sink == 0) log_message(0x00099969, ((unsigned long)"component_init"));
        else debug_print(0x00099969, ((unsigned long)"component_init"));
    }

    device_info_register_persistent_fields((void *)context);
    int result = (int)call_hook(context, 0x77c, 0x77c);
    if (result != 0 && g_log_level > 1) {
        if (g_log_use_alt_sink == 0) log_message(((unsigned long)"%s(): [ble_context init] fail: 0x%x\n\n"), ((unsigned long)"component_init"), result);
        else debug_print(((unsigned long)"%s(): [ble_context init] fail: 0x%x\n\n"), ((unsigned long)"component_init"), result);
    }
    if (B8(context, 0) == 1) {
        result = (int)call_hook(context, 0xf70, 0xee4);
        if (result != 0 && g_log_level > 1) {
            if (g_log_use_alt_sink == 0) log_message(((unsigned long)"%s(): [imu_context init] fail: 0x%x\n\n"), ((unsigned long)"component_init"), result);
            else debug_print(((unsigned long)"%s(): [imu_context init] fail: 0x%x\n\n"), ((unsigned long)"component_init"), result);
        }
        result = (int)call_hook(context, 0xf80, 0xf80);
        if (result != 0 && g_log_level > 1) {
            if (g_log_use_alt_sink == 0) log_message(((unsigned long)"%s(): [opt3007 init] fail: 0x%x\n\n"), ((unsigned long)"component_init"), result);
            else debug_print(((unsigned long)"%s(): [opt3007 init] fail: 0x%x\n\n"), ((unsigned long)"component_init"), result);
        }
    }

    const void *fuel_gauge = (const void *)0x00087cb0UL;
    uintptr_t failure_message = 0x000999e4;
    if (z_device_is_ready(fuel_gauge)) {
        log_message(((unsigned long)"pmic regulator %s is ready to use.\n"), *(const uint32_t *)fuel_gauge);
        const void *fuel_config = (const void *)0x00087d70UL;
        failure_message = 0x00099a23;
        if (z_device_is_ready(fuel_config)) {
            failure_message = 0x00099a3e;
            if (fuel_gauge_sample_init_timestamp(fuel_config) >= 0) {
                failure_message = 0x00099a60;
                if (fuel_gauge_configure(fuel_config) >= 0) {
                    log_message(((unsigned long)"Initialise charger.\n"));
                    log_message(((unsigned long)"PMIC device ok\n"));
                    fuel_gauge_program_defaults();
                    if (product_code_is_supported_egp_family()) {
                        log_message(((unsigned long)"Old board, need to restrain Vterm to 4.2V\n"));
                        fuel_gauge_enable_measurements();
                    }
                    result = (int)call_hook(context, 0xb10, 0xb10);
                    if (result != 0 && g_log_level > 1) {
                        if (g_log_use_alt_sink == 0) log_message(((unsigned long)"%s(): [spi_master init] fail: 0x%x\n\n"), ((unsigned long)"component_init"), result);
                        else debug_print(((unsigned long)"%s(): [spi_master init] fail: 0x%x\n\n"), ((unsigned long)"component_init"), result);
                    }
                    result = (int)call_hook(context, 0xb6c, 0xb6c);
                    if (result != 0 && g_log_level > 1) {
                        if (g_log_use_alt_sink == 0) log_message(((unsigned long)"%s(): [panel_controler init] fail: 0x%x\n\n"), ((unsigned long)"component_init"), result);
                        else debug_print(((unsigned long)"%s(): [panel_controler init] fail: 0x%x\n\n"), ((unsigned long)"component_init"), result);
                    }
                    pt_nfc_eeprom_link_start();
                    notification_system_init();
                    if (g_log_level > 1) {
                        if (g_log_use_alt_sink == 0) log_message(((unsigned long)"%s(): exit\n"), ((unsigned long)"component_init"));
                        else debug_print(((unsigned long)"%s(): exit\n"), ((unsigned long)"component_init"));
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
