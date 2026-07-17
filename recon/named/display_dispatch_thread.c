/* readable reconstruction; identity: FUN_00028bec @ 0x00028bec
 * public-name: display_dispatch_thread
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   __aeabi_uldivmod                         <= FUN_0000e244 @ 0x0000e244
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   get_current_work_mode                    <= FUN_00016940 @ 0x00016940
 *   prepare_system_suspend_state             <= FUN_000289b0 @ 0x000289b0
 *   check_battery_critical                   <= FUN_0002bed0 @ 0x0002bed0
 *   is_battery_critical                      <= FUN_00032ee4 @ 0x00032ee4
 *   get_message_entry                        <= FUN_00033c4c @ 0x00033c4c
 *   cal_panel_canvas_coord                   <= FUN_00042fb0 @ 0x00042fb0
 *   set_brightness_to_panel_reg_in_running   <= FUN_00047058 @ 0x00047058
 *   k_mutex_lock                             <= FUN_000723b8 @ 0x000723b8
 *   k_uptime_get_1                           <= FUN_0007cb2c @ 0x0007cb2c
 *   k_msleep_ticks32768_a                    <= FUN_0007cb8e @ 0x0007cb8e
 *   projector_reflash_and_release            <= FUN_0007d874 @ 0x0007d874
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_28000                             @ 0x00028000
 *   g_log_level                              @ 0x2000230c
 *   g_20007af4                               @ 0x20007af4
 *   g_20007af8                               @ 0x20007af8
 *   g_20007afc                               @ 0x20007afc
 *   g_ui_state_mutex                         @ 0x20007b3c
 *   g_2000a098                               @ 0x2000a098
 *   g_20018c6e                               @ 0x20018c6e
 *   g_20018d96                               @ 0x20018d96
 *   g_ble_dispatch_pending_marker            @ 0x20018d9b
 */
/* Reconstructed display_dispatch_thread @ 0x28bec  (parity: 300/300 trials, PROVEN) */
typedef unsigned char u8; typedef signed char s8;
typedef unsigned short u16; typedef short s16;
typedef unsigned int u32; typedef int s32;
typedef long long s64;

/* globals as fixed absolute-address volatile pointers */
#define G_DBG   (*(volatile s32*)0x2000230c)   /* DAT_00028f10 debug level */
#define G_F00   (*(volatile u8 *)0x20018d96)   /* DAT_00028f00 */
#define G_260   ((volatile s8 *)0x20018c6e)    /* DAT_00029260 pcVar10 */
#define G_270   (*(volatile s32*)0x2000a098)   /* DAT_00029270 */
#define G_504   (*(volatile s32*)0x20007afc)   /* DAT_00029504 */
#define G_508   (*(volatile s32*)0x20007af8)   /* DAT_00029508 */
#define G_50C   (*(volatile s32*)0x20007af4)   /* DAT_0002950c */
#define G_51C   (*(volatile u8 *)0x20018d9b)   /* DAT_0002951c */

/* callee oracles (keyed on call order by the harness) */
extern void dbg(void);
extern s32  get_device_info(void);
extern s64  get_current_work_mode(void);
extern void change_work_mode_to(int);
extern s32  is_battery_critical(void);
extern void prepare_system_suspend_state(void);
extern s32  check_battery_critical(void*);
extern void cal_panel_canvas_coord(int,int);
extern void thunk_74844(int,int);
extern void thunk_72908(void*,int,int,int);
extern s32  sync_to_slave(void*,int,int);
extern u32  FUN_00010840(void*);
extern void k_mutex_lock(int,int,int,int);
extern void FUN_0003629c(void*,int);
extern s64  k_uptime_get_1(void);
extern void k_msleep_ticks32768_a(int);
extern void FUN_00034390(void);
extern s32  get_message_entry(void);
extern s32  FUN_0002c214(void);
extern void FUN_00026850(void);
extern void memset_bytes(void*,int,int);
extern s32  FUN_00086be4(void*,void*,int);
extern void memcpy(void*,void*,int);
extern void set_brightness_to_panel_reg_in_running(void);
extern void projector_reflash_and_release(int);
extern void send_event_status(int);
extern s64  __aeabi_uldivmod(int,int,int,int);

#define B(o)  (*(volatile u8 *)(P+(o)))
#define SB(o) (*(volatile s8 *)(P+(o)))
#define H(o)  (*(volatile s16*)(P+(o)))
#define W(o)  (*(volatile s32*)(P+(o)))
#define PTR(o) ((u32)(*(volatile u32*)(P+(o))))

void display_dispatch_thread(char *P)
{
  s32 iVar5, iVar6, iVar11;
  u32 uVar7, uVar12;
  s64 uVar17, lVar18, lVar19;
  u8 bVar9;
  s8 cVar1, cVar13, cVar16;
  volatile s8 *pcVar10;
  u8 *pbVar14, *pbVar15;
  int iStack_34; u32 uStack_30;

  if (1 < G_DBG) dbg();
  *(volatile s32*)(P+0xecc) = 0x12;   /* str.w */
  B(0xfe8) = 0;
  if (0 < G_DBG) dbg();
  *(volatile s32*)(P+0xeb4) = 0;      /* str.w */
  iVar5 = get_device_info();
  iVar6 = get_device_info();
  cal_panel_canvas_coord(iVar5 + 0xec4, iVar6 + 0xeb8);
  H(0xd6) = (s16)(W(0xeb4)) + (s16)(*(volatile u16*)(P+0x1072));
  *(volatile s32*)(P+0xee8) = 0;      /* str.w */
  H(0xd8) = (s16)(W(0xeb8)) + (s16)(*(volatile u16*)(P+0x1074));
  B(0xfe7) = 1;
  B(0xd5) = 0;
  if (B(0xfea) == 0x0b) {
    change_work_mode_to(2);
    if (is_battery_critical() == 1) prepare_system_suspend_state();
  }
  iVar5 = 0;
  pbVar14 = (u8*)0;
  cVar16 = 0;
  iStack_34 = 0;
  uStack_30 = 1;

 LAB_28cc8:
  for (;;) {
    while (B(1) == 1 || (*(volatile u8*)(get_device_info()+1) == 8)) {
      thunk_74844(0x28000, 0);
    }
    if (B(0xfe8) == 0 && check_battery_critical(P) == 0) {
      if (1 < G_DBG) dbg();
      B(0xcb) = B(0xed5);
      uVar17 = get_current_work_mode();
      if ((s32)uVar17 != 3) {
        sync_to_slave(P, 1, 0);
        change_work_mode_to(3);
      }
      if (B(0) == 2) {
        while (W(0x40) != 0) thunk_72908(P+0x38, 0, -1, -1);
        while (W(0x58) != 0) thunk_72908(P+0x50, 0, -1, -1);
      }
      if (B(0xfe8) == 0) {
        uVar17 = check_battery_critical(P);
        if ((s32)uVar17 != 0) goto LAB_28d42;
        if (1 < G_DBG) dbg();
        G_F00 = 0;
        thunk_72908(P+0x50, 0, -1, -1);
        if (B(0) == 2) {
          while (W(0x40) != 0) thunk_72908(P+0x38, 0, -1, -1);
        }
        iStack_34 = 4;
      } else {
       LAB_28d42:
        while (W(0x58) != 0) thunk_72908(P+0x50, 0, -1, -1);
      }
      if (1 < G_DBG) {
        dbg();
        if (1 < G_DBG) dbg();
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
        uVar7 = FUN_00010840(P+0xf80);
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
      uVar17 = check_battery_critical(P);
      if ((s32)uVar17 == 0) {
        if (0 < G_DBG) dbg();
        goto LAB_290ca;
      }
      k_mutex_lock(0x20007b3c, (s32)(uVar17>>32), -1, -1);
      cVar1 = B(0xd5);
      pbVar15 = pbVar14;
      switch (B(0xd5)) {
      case 2:
        FUN_0003629c(P, W(0xff0));
        iVar5 = 7;
        pbVar15 = (u8*)PTR(0xff0);
        break;
      case 3: {
        volatile s32 *piVar2 = &G_504;
        iVar6 = (s32)k_uptime_get_1();
        if (*piVar2 == 0) { *piVar2 = iVar6; }
        else if (9999 < (u32)(iVar6 - *piVar2)) {
          G_508 = (G_508 + 1) % 7;
          *piVar2 = 0;
        }
        iVar11 = G_50C;
        G_50C = iVar11 + 1;
        iVar6 = G_508;
        B(0xe6) = (u8)(iVar11 + 1);
        B(0xe5) = (u8)iVar6;
        break;
      }
      case 4:
        cVar13 = 0x33;
        while (B(0xec) != B(0xd5) && (cVar13 = cVar13 - 1, cVar13 != 0)) {
          k_msleep_ticks32768_a(10);
        }
        FUN_00034390();
        pbVar15 = (u8*)get_message_entry();
        iVar5 = FUN_0002c214();
        pcVar10 = G_260;
        if (iVar5 == 0 && (iVar5 = get_device_info(), *(volatile s8*)(iVar5+0xdd) == *pcVar10)) {
          if (cVar16 == 0) {
            FUN_00026850();
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
        if (2 < G_DBG) dbg();
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
        FUN_00026850();
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
        iVar6 = FUN_00086be4(P+0xef, pbVar15, iVar5);
        if (iVar6 != 0 || cVar16 != 0 || (u32)(u8)B(0xd5) != (u32)G_270) {
          memcpy(P+0xef, pbVar15, iVar5);
          cVar13 = cVar16;
          goto LAB_2902a;
        }
        FUN_00026850();
        iVar6 = 0;
       LAB_29102:
        cVar16 = 0;
        pbVar14 = pbVar15;
        goto LAB_2933e;
      }
     LAB_2902a:
      memset_bytes(P + iVar5 + 0xef, 0, 0x5dc - iVar5);
      H(0xed) = (s16)iVar5;
      FUN_00026850();
      pbVar14 = pbVar15;
      if (B(0xfe6) == 0 || (cVar16 = cVar13, B(0xfe6) == 5)) {
        if (B(0) == 1) {
          if (B(0xcb) != B(0xed5)) { set_brightness_to_panel_reg_in_running(); B(0xcb) = B(0xed5); }
          iVar6 = sync_to_slave(P, 0, 0);
          cVar16 = 1;
          if (4999 < iVar6) {
            if (0 < G_DBG) dbg();
            goto LAB_290ca;
          }
          if (iVar6 < 3000) {
            if (iVar6 < 500) {
              uVar7 = (u32)(u8)B(0xec);
              if (uVar7 == (u8)B(0xd5) || (u8)B(0xd5) < 7 || uVar7 < 7)
                goto LAB_293fc;
              if (0 < G_DBG) dbg();
              iVar6 = 0x46;
            } else if (0 < G_DBG) dbg();
          } else if (0 < G_DBG) dbg();
        } else {
          iVar6 = 0;
         LAB_293fc:
          iVar11 = check_battery_critical(P);
          if (iVar11 == 0) {
            if (0 < G_DBG) dbg();
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
                    if (1 < G_DBG) dbg();
                  }
                }
              }
              uStack_30 = uVar7;
              projector_reflash_and_release(B(0xd5));
              if (0 < G_DBG) dbg();
              cVar16 = B(0xec);
              if (cVar16 != 6 && cVar16 == 0) goto LAB_2933e;
              goto LAB_29102;
            }
            if (0 < G_DBG) dbg();
          } else if (0 < G_DBG) dbg();
          cVar16 = 1;
        }
      } else {
       LAB_290ca:
        iVar6 = 0;
      }
     LAB_2933e:
      if (B(0) == 1) {
        cVar1 = G_51C;
        if (cVar1 == 0x0f) { send_event_status(0xf1); }
        else if (cVar1 == 0x4e) { send_event_status(0xf2); }
        else if (cVar1 == 0x0d) { send_event_status(0xf0); }
        G_51C = 0;
        if (B(0) != 1) goto LAB_294ea;
        if (0x45 < iVar6) goto LAB_28cc8;
        lVar18 = (s64)(0x46 - iVar6) * 0x8000 + 999;
        uVar17 = __aeabi_uldivmod((s32)lVar18, (s32)(lVar18>>32), 1000, 0);
      } else {
       LAB_294ea:
        if (B(0xfe6) == 0 || B(0xfe6) == 5) goto LAB_28cc8;
        uVar17 = 0x148;
      }
      thunk_74844((s32)uVar17, (s32)(uVar17>>32));
      goto LAB_28cc8;
    }
    if ((u8)(B(0xfe6) - 1) > 1 && B(0xfe6) != 4) {
      lVar18 = k_uptime_get_1();
      thunk_72908(P+0x38, (s32)(lVar18>>32), 0x4000, 0);
      lVar19 = k_uptime_get_1();
      if (lVar19 - lVar18 < 500) goto LAB_28eae;
      goto LAB_290ca;
    }
    k_msleep_ticks32768_a(0x32);
  }
}
