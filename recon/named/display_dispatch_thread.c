/* readable reconstruction; identity: FUN_00028bec @ 0x00028bec
 * public-name: display_dispatch_thread
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   __aeabi_uldivmod                         <= FUN_0000e244 @ 0x0000e244
 *   compute_lux_brightness_bucket            <= FUN_00010840 @ 0x00010840
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   get_current_work_mode                    <= FUN_00016940 @ 0x00016940
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   ui_state_mutex_unlock                    <= FUN_00026850 @ 0x00026850
 *   send_event                               <= FUN_000276ec @ 0x000276ec
 *   prepare_system_suspend_state             <= FUN_000289b0 @ 0x000289b0
 *   display_panel_is_secondary               <= FUN_0002bed0 @ 0x0002bed0
 *   clear_pending_message_flag               <= FUN_0002c214 @ 0x0002c214
 *   is_battery_critical                      <= FUN_00032ee4 @ 0x00032ee4
 *   get_message_entry                        <= FUN_00033c4c @ 0x00033c4c
 *   get_message_pool_index                   <= FUN_00034390 @ 0x00034390
 *   display_idle_countdown_tick              <= FUN_0003629c @ 0x0003629c
 *   cal_panel_canvas_coord                   <= FUN_00042fb0 @ 0x00042fb0
 *   set_brightness_to_panel_reg_in_running   <= FUN_00047058 @ 0x00047058
 *   k_mutex_lock                             <= FUN_000723b8 @ 0x000723b8
 *   z_impl_k_sem_take                        <= FUN_00072908 @ 0x00072908
 *   k_uptime_get_1                           <= FUN_0007cb2c @ 0x0007cb2c
 *   wait_for_event                           <= FUN_0007cb8a @ 0x0007cb8a
 *   k_msleep                                 <= FUN_0007cb8e @ 0x0007cb8e
 *   projector_reflash_and_release            <= FUN_0007d874 @ 0x0007d874
 *   log_message                              <= FUN_0007dda4 @ 0x0007dda4
 *   memcmp                                   <= FUN_00086be4 @ 0x00086be4
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_28000                             @ 0x00028000
 *   rodata_99969                             @ 0x00099969
 *   rodata_a0ca9                             @ 0x000a0ca9   [INLINED -- G6 literal batch]
 *   rodata_a0cdf                             @ 0x000a0cdf   [INLINED -- G6 literal batch]
 *   rodata_a0d03                             @ 0x000a0d03   [INLINED -- G6 literal batch]
 *   rodata_a0d1d                             @ 0x000a0d1d   [INLINED -- G6 literal batch]
 *   rodata_a0d34                             @ 0x000a0d34   [INLINED -- G6 literal batch]
 *   rodata_a0d50                             @ 0x000a0d50   [INLINED -- G6 literal batch]
 *   rodata_a0d77                             @ 0x000a0d77   [INLINED -- G6 literal batch]
 *   rodata_a0d92                             @ 0x000a0d92   [INLINED -- G6 literal batch]
 *   rodata_a0dcb                             @ 0x000a0dcb   [INLINED -- G6 literal batch]
 *   rodata_a0e3d                             @ 0x000a0e3d   [INLINED -- G6 literal batch]
 *   rodata_a0e91                             @ 0x000a0e91   [INLINED -- G6 literal batch]
 *   rodata_a0ee6                             @ 0x000a0ee6   [INLINED -- G6 literal batch]
 *   rodata_a0f08                             @ 0x000a0f08   [INLINED -- G6 literal batch]
 *   rodata_a1a13                             @ 0x000a1a13   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_20007af4                               @ 0x20007af4
 *   g_20007af8                               @ 0x20007af8
 *   g_20007afc                               @ 0x20007afc
 *   g_ui_state_mutex                         @ 0x20007b3c
 *   g_2000a098                               @ 0x2000a098
 *   g_20018c6e                               @ 0x20018c6e
 *   g_20018d96                               @ 0x20018d96
 *   g_ble_dispatch_pending_marker            @ 0x20018d9b
 */
#include "../headers/g1_log.h"
/* Reconstructed display_dispatch_thread @ 0x00028bec.
 *
 * Readable identities retain reversible raw provenance:
 *   display_target_level_get          <= FUN_00010840 @ 0x00010840
 *   get_device_info                   <= FUN_000167a8 @ 0x000167a8
 *   get_current_work_mode             <= FUN_00016940 @ 0x00016940
 *   display_mutex_unlock              <= FUN_00026850 @ 0x00026850
 *   enter_critical_battery_display    <= FUN_000289b0 @ 0x000289b0
 *   display_panel_is_secondary        <= FUN_0002bed0 @ 0x0002bed0
 *   clear_display_refresh_request     <= FUN_0002c214 @ 0x0002c214
 *   is_battery_critical               <= FUN_00032ee4 @ 0x00032ee4
 *   display_language_buffer_get       <= FUN_00033c4c @ 0x00033c4c
 *   display_language_get              <= FUN_00034390 @ 0x00034390
 *   display_mode_two_update_timer     <= FUN_0003629c @ 0x0003629c
 *   cal_panel_canvas_coord            <= FUN_00042fb0 @ 0x00042fb0
 *   set_brightness_to_panel_reg_in_running <= FUN_00047058 @ 0x00047058
 *   display_mutex_lock                <= FUN_000723b8 @ 0x000723b8
 *   k_sem_take                        <= FUN_00072908 @ 0x00072908
 *   wait_for_event                    <= FUN_0007cb8a @ 0x0007cb8a
 *   k_uptime_get                      <= FUN_0007cb2c @ 0x0007cb2c
 *   k_msleep                          <= FUN_0007cb8e @ 0x0007cb8e
 *   notify_display_mode               <= FUN_0007d874 @ 0x0007d874
 *   memory_compare_bytes              <= FUN_00086be4 @ 0x00086be4
 *   memory_copy_bytes                 <= FUN_00086c04 @ 0x00086c04
 *   memset_bytes                      <= FUN_00086c78 @ 0x00086c78
 *   unsigned_divide_64                <= FUN_0000e244 @ 0x0000e244
 *   change_work_mode_to               <= FUN_0001694c @ 0x0001694c
 *   sync_to_slave                     <= FUN_00026f74 @ 0x00026f74
 *   send_event                        <= FUN_000276ec @ 0x000276ec
 *   debug_print                       <= FUN_00019c70 @ 0x00019c70
 *   log_message                       <= FUN_0007dda4 @ 0x0007dda4
 *
 * Exact executable ownership is [0x00028bec, 0x00029502).  The halfword at
 * 0x29502 is alignment; literals occupy 0x29504..0x2953b and FUN_0002953c is
 * the next independent function.
 */
typedef unsigned char u8; typedef signed char s8;
typedef unsigned short u16; typedef short s16;
typedef unsigned int u32; typedef int s32;
typedef long long s64;

#define display_target_level_get       compute_lux_brightness_bucket
#define get_device_info                get_device_info
#define get_current_work_mode          get_current_work_mode
#define display_mutex_unlock           ui_state_mutex_unlock
#define enter_critical_battery_display prepare_system_suspend_state
#define display_panel_is_secondary     display_panel_is_secondary
#define clear_display_refresh_request  clear_pending_message_flag
#define is_battery_critical            is_battery_critical
#define display_language_buffer_get    get_message_entry
#define display_language_get           get_message_pool_index
#define display_mode_two_update_timer  display_idle_countdown_tick
#define cal_panel_canvas_coord         cal_panel_canvas_coord
#define set_brightness_to_panel_reg_in_running set_brightness_to_panel_reg_in_running
#define display_mutex_lock             k_mutex_lock
#define k_sem_take                     z_impl_k_sem_take
#define wait_for_event                 wait_for_event
#define k_uptime_get                   k_uptime_get_1
#define k_msleep                       k_msleep
#define notify_display_mode            projector_reflash_and_release
#define memory_compare_bytes           memcmp
#define memory_copy_bytes              memcpy
#define memset_bytes                   memset_bytes
#define unsigned_divide_64             __aeabi_uldivmod
#define send_event                     send_event
#define debug_print                    debug_print
#define log_message                    log_message

/* globals as fixed absolute-address volatile pointers */
#define g_log_level   (*(volatile s32*)0x2000230c)   /* DAT_00028f10 debug level */
#define g_log_use_alt_sink   (*(volatile u32*)0x20007554)
#define g_display_refresh_latch   (*(volatile u8 *)0x20018d96)   /* DAT_00028f00 */
#define g_display_device_marker   ((volatile s8 *)0x20018c6e)    /* DAT_00029260 pcVar10 */
#define g_display_last_mode   (*(volatile s32*)0x2000a098)   /* DAT_00029270 */
#define g_display_rotation_started_ms   (*(volatile s32*)0x20007afc)   /* DAT_00029504 */
#define g_display_rotation_index   (*(volatile s32*)0x20007af8)   /* DAT_00029508 */
#define g_display_rotation_counter   (*(volatile s32*)0x20007af4)   /* DAT_0002950c */
#define g_ble_dispatch_pending_marker   (*(volatile u8 *)0x20018d9b)   /* DAT_0002951c */

/* callee oracles (keyed on call order by the harness) */
extern int get_device_info(void);
extern s32  get_current_work_mode(void);
extern void change_work_mode_to(int);
extern int is_battery_critical(void);
extern void enter_critical_battery_display(void);
/* The shipped caller forwards the otherwise-unused r1 return lane into the
 * four-register mutex boundary; retain that pair-shaped ABI for trace parity. */
extern s64  display_panel_is_secondary(void*);
extern void cal_panel_canvas_coord(int,int);
extern void wait_for_event(unsigned long, unsigned long);
extern void k_sem_take(void*,int,int,int);
extern s32  sync_to_slave(void*,int,int);
extern u32  display_target_level_get(void*);
extern void display_mutex_lock(int,int,int,int);
extern void display_mode_two_update_timer(void*,int);
extern int64_t k_uptime_get(void);
extern int32_t k_msleep(int32_t);
extern u32  display_language_get(void);
extern s32  display_language_buffer_get(u32 language);
extern s32  clear_display_refresh_request(void);
extern void display_mutex_unlock(void);
extern void memset_bytes(void*,int,int);
extern s32  memory_compare_bytes(void*,void*,int);
extern void memory_copy_bytes(void*,void*,int);
extern void set_brightness_to_panel_reg_in_running(void);
extern void notify_display_mode(int);
extern void send_event(int);
extern s64  unsigned_divide_64(int,int,int,int);

#define B(o)  (*(volatile u8 *)(display+(o)))
#define SB(o) (*(volatile s8 *)(display+(o)))
#define H(o)  (*(volatile s16*)(display+(o)))
#define W(o)  (*(volatile s32*)(display+(o)))
#define PTR(o) ((u32)(*(volatile u32*)(display+(o))))

#define DISPLAY_LOG_MODULE 0x000a1a13u
#define DISPLAY_LOG_2(format) do {                                      \
  if (g_log_use_alt_sink == 0)                                          \
    log_message((format), DISPLAY_LOG_MODULE);                          \
  else                                                                  \
    debug_print((format), DISPLAY_LOG_MODULE);                          \
} while (0)
#define DISPLAY_LOG_3(format, value) do {                               \
  if (g_log_use_alt_sink == 0)                                          \
    log_message((format), DISPLAY_LOG_MODULE, (value));                 \
  else                                                                  \
    debug_print((format), DISPLAY_LOG_MODULE, (value));                 \
} while (0)
#define DISPLAY_LOG_4(format, value0, value1) do {                       \
  if (g_log_use_alt_sink == 0)                                          \
    log_message((format), DISPLAY_LOG_MODULE, (value0), (value1));      \
  else                                                                  \
    debug_print((format), DISPLAY_LOG_MODULE, (value0), (value1));      \
} while (0)

void display_dispatch_thread(char *display)
{
  s32 iVar5, iVar6, iVar11;
  u32 uVar7, uVar12;
  s64 uVar17, lVar18, lVar19;
  u8 bVar9;
  s8 cVar1, cVar13, cVar16;
  volatile s8 *pcVar10;
  u8 *pbVar14, *pbVar15;
  int iStack_34; u32 uStack_30;

  if (1 < g_log_level) DISPLAY_LOG_2(0x00099969u);
  *(volatile s32*)(display+0xecc) = 0x12;   /* str.w */
  B(0xfe8) = 0;
  if (0 < g_log_level)
    DISPLAY_LOG_4(0x000a0ca9u, B(0xec0), B(0xec1));
  *(volatile s32*)(display+0xeb4) = 0;      /* str.w */
  iVar5 = get_device_info();
  iVar6 = get_device_info();
  cal_panel_canvas_coord(iVar5 + 0xec4, iVar6 + 0xeb8);
  H(0xd6) = (s16)(W(0xeb4)) + (s16)(*(volatile u16*)(display+0x1072));
  *(volatile s32*)(display+0xee8) = 0;      /* str.w */
  H(0xd8) = (s16)(W(0xeb8)) + (s16)(*(volatile u16*)(display+0x1074));
  B(0xfe7) = 1;
  B(0xd5) = 0;
  if (B(0xfea) == 0x0b) {
    change_work_mode_to(2);
    if (is_battery_critical() == 1) enter_critical_battery_display();
  }
  iVar5 = 0;
  pbVar14 = (u8*)0;
  cVar16 = 0;
  iStack_34 = 0;
  uStack_30 = 1;

 LAB_28cc8:
  for (;;) {
    while (B(1) == 1 || (*(volatile u8*)(get_device_info()+1) == 8)) {
      wait_for_event(0x28000, 0);
    }
    if (B(0xfe8) == 0 && display_panel_is_secondary(display) == 0) {
      if (1 < g_log_level) DISPLAY_LOG_2(0x000a0cdfu);
      B(0xcb) = B(0xed5);
      uVar17 = get_current_work_mode();
      if ((s32)uVar17 != 3) {
        sync_to_slave(display, 1, 0);
        change_work_mode_to(3);
      }
      if (B(0) == 2) {
        while (W(0x40) != 0) k_sem_take(display+0x38, 0, -1, -1);
        while (W(0x58) != 0) k_sem_take(display+0x50, 0, -1, -1);
      }
      if (B(0xfe8) == 0) {
        uVar17 = display_panel_is_secondary(display);
        if ((s32)uVar17 != 0) goto LAB_28d42;
        if (1 < g_log_level) DISPLAY_LOG_2(0x000a0d03u);
        g_display_refresh_latch = 0;
        k_sem_take(display+0x50, 0, -1, -1);
        if (B(0) == 2) {
          while (W(0x40) != 0) k_sem_take(display+0x38, 0, -1, -1);
        }
        iStack_34 = 4;
      } else {
       LAB_28d42:
        while (W(0x58) != 0) k_sem_take(display+0x50, 0, -1, -1);
      }
      if (1 < g_log_level) {
        DISPLAY_LOG_2(0x000a0d1du);
        if (1 < g_log_level) DISPLAY_LOG_2(0x000a0d34u);
      }
      B(0xcb) = B(0xed5);
      change_work_mode_to(2);
      cVar16 = 1;
    }
    if (B(0xfe7) == 0) { iVar6 = 0; goto LAB_2933e; }
    if (B(0) == 1 && (++iStack_34 == 5)) {
      if (B(0xf98) == 0 || W(0xf90) == 0 || W(0xec8) == 0) {
        iStack_34 = 4;
      } else {
        uVar7 = display_target_level_get(display+0xf80);
        if (uVar7 == 0xff) {
          iStack_34 = 0;
        } else {
          bVar9 = B(0xed5);
          if (bVar9 < uVar7) { cVar1 = 1; B(0xed5) = bVar9 + cVar1; }
          else if (uVar7 < bVar9) { cVar1 = -1; B(0xed5) = bVar9 + cVar1; }
          iStack_34 = (u8)B(0xed5) - uVar7;
          if (iStack_34 != 0) iStack_34 = 1;
          iStack_34 = iStack_34 << 2;
        }
      }
      if (B(0xed6) != B(0xed5)) { cVar16 = 1; B(0xed6) = B(0xed5); }
    }
    W(0xdf) = *(volatile s32*)(PTR(0x1054));
    B(0xe3) = *(volatile u8*)(PTR(0x1054)+4);
    if (B(0) == 1) {
      B(0xe9) = B(0xcc);
      B(0xea) = B(0xcd);
      B(0xeb) = B(0xee4);
      B(0xec) = B(0xd5);
     LAB_28eae:
      if (B(0xfea) == 0x0c && B(0xd5) != 7) goto LAB_290ca;
      uVar17 = display_panel_is_secondary(display);
      if ((s32)uVar17 == 0) {
        if (0 < g_log_level) DISPLAY_LOG_2(0x000a0d50u);
        goto LAB_290ca;
      }
      display_mutex_lock(0x20007b3c, (s32)(uVar17>>32), -1, -1);
      cVar1 = B(0xd5);
      pbVar15 = pbVar14;
      switch (B(0xd5)) {
      case 2:
        display_mode_two_update_timer(display, W(0xff0));
        iVar5 = 7;
        pbVar15 = (u8*)PTR(0xff0);
        break;
      case 3: {
        volatile s32 *piVar2 = &g_display_rotation_started_ms;
        iVar6 = (s32)k_uptime_get();
        if (*piVar2 == 0) { *piVar2 = iVar6; }
        else if (9999 < (u32)(iVar6 - *piVar2)) {
          g_display_rotation_index = (g_display_rotation_index + 1) % 7;
          *piVar2 = 0;
        }
        iVar11 = g_display_rotation_counter;
        g_display_rotation_counter = iVar11 + 1;
        iVar6 = g_display_rotation_index;
        B(0xe6) = (u8)(iVar11 + 1);
        B(0xe5) = (u8)iVar6;
        break;
      }
      case 4:
        cVar13 = 0x33;
        while (B(0xec) != B(0xd5) && (cVar13 = cVar13 - 1, cVar13 != 0)) {
          k_msleep(10);
        }
        uVar7 = display_language_get();
        pbVar15 = (u8*)display_language_buffer_get(uVar7);
        iVar5 = clear_display_refresh_request();
        pcVar10 = g_display_device_marker;
        if (iVar5 == 0 && (iVar5 = get_device_info(), *(volatile s8*)(iVar5+0xdd) == *pcVar10)) {
          if (cVar16 == 0) {
            display_mutex_unlock();
            iVar5 = 0x1b4;
            pbVar14 = pbVar15;
            goto LAB_290ca;
          }
        } else {
          iVar5 = get_device_info();
          *pcVar10 = *(volatile s8*)(iVar5+0xdd);
        }
        iVar5 = 0x1b4;
        if (pbVar15 != (u8*)0) { cVar16 = 1; goto LAB_290d2; }
        pbVar15 = (u8*)0; cVar13 = 1; goto LAB_2902a;
      case 5:
        iVar5 = 0x6a;
        pbVar15 = (u8*)PTR(0xfec);
        break;
      case 6:
        if (2 < g_log_level) DISPLAY_LOG_2(0x000a0d77u);
        /* fallthrough */
      case 15:
        pbVar15 = (u8*)PTR(0xfec);
        iVar5 = 0x6a;
        if (pbVar15 != (u8*)0) goto LAB_290d2;
       LAB_29134:
        pbVar15 = (u8*)0; cVar13 = cVar16; goto LAB_2902a;
      case 7:
        iVar5 = 0x0b;
        pbVar15 = (u8*)PTR(0x1010);
        break;
      case 8:
        iVar5 = 0x16a;
        pbVar15 = (u8*)PTR(0xff4);
        break;
      case 9:
        iVar5 = 0x217;
        pbVar15 = (u8*)PTR(0xffc);
        break;
      case 10: {
        bVar9 = B(0xee4);
        volatile u8 *q = (volatile u8*)PTR(0x1000);
        if (bVar9 == 2) {
          if (uStack_30 != 2 || q[7] != 2) { cVar16 = 1; q[7] = bVar9; }
        } else if (bVar9 != uStack_30) {
          bVar9 = 1; cVar16 = 1; q[7] = bVar9;
        }
        iVar5 = 0xf5;
        pbVar15 = (u8*)PTR(0x1000);
        break;
      }
      case 11: {
        bVar9 = B(0xee4);
        uVar7 = (u32)bVar9;
        volatile s8 *r = (volatile s8*)PTR(0x1008);
        if (uVar7 != 2) {
          if (r[1] == r[0]) { r[3] = 2; }
          else {
            uVar12 = uStack_30;
            if (uVar7 != uStack_30) { bVar9 = 4; uVar12 = (u32)PTR(0x1004); }
            if (uVar7 != uStack_30) { *(volatile u8*)(uVar12+3) = bVar9; }
            if (B(0) != 2 || B(0xcd) == B(0xea) ||
                (pbVar15 = (u8*)PTR(0x1028), pbVar15[0x200] != B(0xea))) {
              pbVar15 = (u8*)PTR(0x1004);
              if (pbVar15 != (u8*)0) { iVar5 = 0x198; goto LAB_290d2; }
              iVar5 = 0x198; goto LAB_29134;
            }
            iVar5 = 0x198; goto LAB_290d2;
          }
          if (B(0) == 2 && B(0xcc) != B(0xe9) &&
              (pbVar15 = (u8*)PTR(0x1024), pbVar15[0x200] == B(0xe9))) {
            iVar5 = 0x198; goto LAB_290d2;
          }
          pbVar15 = (u8*)PTR(0x1008);
          if (pbVar15 != (u8*)0) { iVar5 = 0x198; goto LAB_290d2; }
          iVar5 = 0x198; goto LAB_29134;
        }
        if (uStack_30 != 2 || r[1] == r[0]) { r[3] = 2; }
        if (B(0) == 2 && B(0xcc) != B(0xe9) &&
            (pbVar15 = (u8*)PTR(0x1024), pbVar15[0x200] == B(0xe9))) {
          iVar5 = 0x198; goto LAB_290d2;
        }
        pbVar15 = (u8*)PTR(0x1008);
        if (pbVar15 != (u8*)0) { iVar5 = 0x198; goto LAB_290d2; }
        iVar5 = 0x198; goto LAB_29134;
      }
      case 12:
        iVar5 = 0x50f;
        pbVar15 = (u8*)PTR(0x1020);
        break;
      case 14:
        iVar5 = get_device_info();
        *(volatile u8*)(iVar5+0xed5) = 0x2a;
        iVar5 = 0x21;
        pbVar15 = (u8*)PTR(0x1014);
        break;
      case 16: {
        volatile u8 *s = (volatile u8*)PTR(0x100c);
        pbVar15 = (u8*)s;
        if (*s < 0x0c || (*s & 0xfd) != 0x0d) {
          if (B(0) == 2 &&
              (bVar9 = B(0xe9), B(0xcc) != bVar9 &&
               (pbVar14 = (u8*)PTR(0x1024), bVar9 == pbVar14[0x200]))) {
            s[6] = bVar9;
            pbVar15 = pbVar14;
          } else {
            iVar5 = get_device_info();
            *(volatile u8*)(PTR(0x100c)+6) = *(volatile u8*)(iVar5+0xcc);
          }
          if (*(volatile s8*)(PTR(0x100c)) == 7) {
            *(volatile s8*)(PTR(0x100c)+1) = 3;
          }
          iVar5 = 0x199; goto LAB_290d2;
        }
        display_mutex_unlock();
        goto LAB_290ca;
      }
      case 17:
        iVar5 = 2;
        pbVar15 = (u8*)PTR(0x101c);
        break;
      default:
        goto LAB_2910e;
      }
     LAB_2910e:
      cVar13 = cVar16;
      if (pbVar15 != (u8*)0) {
       LAB_290d2:
        iVar6 = memory_compare_bytes(display+0xef, pbVar15, iVar5);
        if (iVar6 != 0 || cVar16 != 0 || (u32)(u8)B(0xd5) != (u32)g_display_last_mode) {
          memory_copy_bytes(display+0xef, pbVar15, iVar5);
          cVar13 = cVar16;
          goto LAB_2902a;
        }
        display_mutex_unlock();
        iVar6 = 0;
       LAB_29102:
        cVar16 = 0;
        pbVar14 = pbVar15;
        goto LAB_2933e;
      }
     LAB_2902a:
      memset_bytes(display + iVar5 + 0xef, 0, 0x5dc - iVar5);
      H(0xed) = (s16)iVar5;
      display_mutex_unlock();
      pbVar14 = pbVar15;
      if (B(0xfe6) == 0 || (cVar16 = cVar13, B(0xfe6) == 5)) {
        if (B(0) == 1) {
          if (B(0xcb) != B(0xed5)) {
            set_brightness_to_panel_reg_in_running();
            B(0xcb) = B(0xed5);
          }
          iVar6 = sync_to_slave(display, 0, 0);
          cVar16 = 1;
          if (4999 < iVar6) {
            if (0 < g_log_level) DISPLAY_LOG_3(0x000a0d92u, iVar6);
            goto LAB_290ca;
          }
          if (iVar6 < 3000) {
            if (iVar6 < 500) {
              uVar7 = (u32)(u8)B(0xec);
              if (uVar7 == (u8)B(0xd5) || (u8)B(0xd5) < 7 || uVar7 < 7)
                goto LAB_293fc;
              if (0 < g_log_level)
                DISPLAY_LOG_4(0x000a0e3du, uVar7, B(0xd5));
              iVar6 = 0x46;
            } else if (0 < g_log_level)
              DISPLAY_LOG_3(0x000a0e04u, iVar6);
          } else if (0 < g_log_level)
            DISPLAY_LOG_3(0x000a0dcbu, iVar6);
        } else {
          iVar6 = 0;
         LAB_293fc:
          iVar11 = display_panel_is_secondary(display);
          if (iVar11 == 0) {
            if (0 < g_log_level) DISPLAY_LOG_2(0x000a0e91u);
          } else if (B(0xd5) == cVar1) {
            if (B(0xfe8) != 0) {
              uVar12 = (u32)(u8)B(0xee4);
              uVar7 = uVar12;
              if (B(0xd5) == 10) {
                uVar7 = uStack_30;
                if (uStack_30 != uVar12) {
                  uVar7 = uVar12;
                  if (cVar13 != 1) {
                    uVar7 = uStack_30;
                    if (1 < g_log_level) DISPLAY_LOG_2(0x000a0ee6u);
                  }
                }
              }
              uStack_30 = uVar7;
              notify_display_mode(B(0xd5));
              if (0 < g_log_level)
                DISPLAY_LOG_3(0x000a0f08u, B(0xd5));
              cVar16 = B(0xec);
              if (cVar16 != 6 && cVar16 == 0) goto LAB_2933e;
              goto LAB_29102;
            }
            if (0 < g_log_level) DISPLAY_LOG_2(0x000a0ec3u);
          } else if (0 < g_log_level) DISPLAY_LOG_2(0x000a0eabu);
          cVar16 = 1;
        }
      } else {
       LAB_290ca:
        iVar6 = 0;
      }
     LAB_2933e:
      if (B(0) == 1) {
        cVar1 = g_ble_dispatch_pending_marker;
        if (cVar1 == 0x0f) { send_event(0xf1); }
        else if (cVar1 == 0x4e) { send_event(0xf2); }
        else if (cVar1 == 0x0d) { send_event(0xf0); }
        g_ble_dispatch_pending_marker = 0;
        if (B(0) != 1) goto LAB_294ea;
        if (0x45 < iVar6) goto LAB_28cc8;
        lVar18 = (s64)(0x46 - iVar6) * 0x8000 + 999;
        uVar17 = unsigned_divide_64((s32)lVar18, (s32)(lVar18>>32), 1000, 0);
      } else {
       LAB_294ea:
        if (B(0xfe6) == 0 || B(0xfe6) == 5) goto LAB_28cc8;
        uVar17 = 0x148;
      }
      wait_for_event((s32)uVar17, (s32)(uVar17>>32));
      goto LAB_28cc8;
    }
    if ((u8)(B(0xfe6) - 1) > 1 && B(0xfe6) != 4) {
      lVar18 = k_uptime_get();
      k_sem_take(display+0x38, (s32)(lVar18>>32), 0x4000, 0);
      lVar19 = k_uptime_get();
      if (lVar19 - lVar18 < 500) goto LAB_28eae;
      goto LAB_290ca;
    }
    k_msleep(0x32);
  }
}
