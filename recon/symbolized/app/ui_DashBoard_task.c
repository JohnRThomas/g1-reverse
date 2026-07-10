#include "g1_app_symbols.h"
/* named: ui_DashBoard_task */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20004950  g_dashboard_widget_state     
//   0x20007554  g_log_use_alt_sink           
//   0x2001b814  g_news_widget_index_raw      
//   0x2001b815  g_stocks_widget_index_raw    
//   0x2001b816  g_widget0_index_raw          
*/
/* Reconstructed ui_DashBoard_task @ 0x3af78  (parity: 100/100 trials, PROVEN) */
#include <stdint.h>
#pragma GCC diagnostic warning "-Wint-conversion"
#pragma GCC diagnostic warning "-Wimplicit-int"
#pragma GCC diagnostic warning "-Wimplicit-function-declaration"
#pragma GCC diagnostic warning "-Wint-to-pointer-cast"
#pragma GCC diagnostic warning "-Wpointer-to-int-cast"
#pragma GCC diagnostic warning "-Wincompatible-pointer-types"
#pragma GCC diagnostic warning "-Wdiscarded-qualifiers"
typedef uint8_t undefined1; typedef uint8_t byte; typedef uint8_t undefined; typedef uint8_t uchar;
typedef uint16_t undefined2; typedef uint16_t ushort; typedef uint16_t wchar_t;
typedef uint32_t undefined4; typedef uint32_t uint;
typedef long long code(int,...);
typedef uint64_t undefined8; typedef uint64_t ulonglong;
typedef int64_t longlong; typedef int32_t int32; typedef unsigned int uint3;
static inline int CARRY4(uint a, uint b){return (a+b)<a;}
static inline int CARRY1(uint a, uint b){return ((a&0xff)+(b&0xff))>0xff;}
static inline int CARRY2(uint a, uint b){return ((a&((uintptr_t)&tbl_ffc8) /*=0xffff*/)+(b&((uintptr_t)&tbl_ffc8) /*=0xffff*/))>((uintptr_t)&tbl_ffc8) /*=0xffff*/;}
static inline int SBORROW4(int a,int b){int r=(int)((uint)a-(uint)b);return (((a^b)&(a^r))<0);}
static inline int SBORROW1(int a,int b){signed char r=(signed char)(a-b);return ((((signed char)a^(signed char)b)&((signed char)a^r))<0);}
static inline int SBORROW2(int a,int b){short r=(short)(a-b);return ((((short)a^(short)b)&((short)a^r))<0);}
#define CONCAT11(a,b) ((ushort)(((ushort)(uint8_t)(a)<<8)|(uint8_t)(b)))
#define CONCAT22(a,b) ((uint)(((uint)(ushort)(a)<<16)|(ushort)(b)))
#define CONCAT44(a,b) ((ulonglong)(((ulonglong)(uint)(a)<<32)|(uint)(b)))
#define CONCAT13(a,b) ((uint)(((uint)(uint8_t)(a)<<24)|((uint)(b)&0xffffff)))
#define CONCAT31(a,b) ((uint)(((uint)(a)<<8)|(uint8_t)(b)))
#define CONCAT12(a,b) ((uint)(((uint)(uint8_t)(a)<<16)|(ushort)(b)))
#define CONCAT21(a,b) ((uint)(((uint)(ushort)(a)<<8)|(uint8_t)(b)))
#define CONCAT111(a,b,c) ((uint)(((uint)(uint8_t)(a)<<16)|((uint)(uint8_t)(b)<<8)|(uint8_t)(c)))
#define CONCAT411(a,b,c) ((ulonglong)(((ulonglong)(uint)(a)<<16)|((uint)(uint8_t)(b)<<8)|(uint8_t)(c)))
#define SUB84(x,o) ((uint)((ulonglong)(x)>>((o)*8)))
#define SUB82(x,o) ((ushort)((ulonglong)(x)>>((o)*8)))
#define SUB81(x,o) ((uint8_t)((ulonglong)(x)>>((o)*8)))
#define SUB41(x,o) ((uint8_t)((uint)(x)>>((o)*8)))
#define SUB42(x,o) ((ushort)((uint)(x)>>((o)*8)))
#define SUB21(x,o) ((uint8_t)((ushort)(x)>>((o)*8)))
#define SUBF(v,o,s) ((ulonglong)((ulonglong)(v)>>((o)*8)) & ((s)>=8?~0ULL:((1ULL<<((s)*8))-1)))
#define NAN (__builtin_nanf(""))
#define INFINITY (__builtin_inff())

extern long long DEBUG_PRINT__impl(int, ...);
#define DEBUG_PRINT(...) DEBUG_PRINT__impl(0, ##__VA_ARGS__)
extern long long FUN_0001672c__impl(int, ...);
#define set_dashboard_startup_default_language(...) FUN_0001672c__impl(0, ##__VA_ARGS__)
extern long long FUN_000167a8__impl(int, ...);
#define get_device_info(...) FUN_000167a8__impl(0, ##__VA_ARGS__)
extern long long FUN_00019c70__impl(int, ...);
#define debug_print(...) FUN_00019c70__impl(0, ##__VA_ARGS__)
extern long long FUN_00033cf8__impl(int, ...);
#define msg_content_recalc_unread(...) FUN_00033cf8__impl(0, ##__VA_ARGS__)
extern long long FUN_00037060__impl(int, ...);
#define sync_dashboard_default_language(...) FUN_00037060__impl(0, ##__VA_ARGS__)
extern long long FUN_000370bc__impl(int, ...);
#define getStocksIndex(...) FUN_000370bc__impl(0, ##__VA_ARGS__)
extern long long FUN_0003719c__impl(int, ...);
#define getNewsIndex(...) FUN_0003719c__impl(0, ##__VA_ARGS__)
extern long long FUN_0003727c__impl(int, ...);
#define DashBoard_Reflash(...) FUN_0003727c__impl(0, ##__VA_ARGS__)
extern long long FUN_0003ae6c__impl(int, ...);
#define send_dashboard_status_sync(...) FUN_0003ae6c__impl(0, ##__VA_ARGS__)
extern long long FUN_0003af04__impl(int, ...);
#define send_dashboard_status_sync_compact(...) FUN_0003af04__impl(0, ##__VA_ARGS__)
extern long long FUN_000431b4__impl(int, ...);
#define gui_set_active_canvas(...) FUN_000431b4__impl(0, ##__VA_ARGS__)
extern long long FUN_000431c0__impl(int, ...);
#define gui_screen_clear(...) FUN_000431c0__impl(0, ##__VA_ARGS__)
extern long long FUN_000432d0__impl(int, ...);
#define gui_canvas_flags_set_bit1(...) FUN_000432d0__impl(0, ##__VA_ARGS__)
extern long long FUN_000432ec__impl(int, ...);
#define gui_canvas_flags_clear_bit1(...) FUN_000432ec__impl(0, ##__VA_ARGS__)
extern long long FUN_0004382c__impl(int, ...);
#define FUN_0004382c(...) FUN_0004382c__impl(0, ##__VA_ARGS__)
extern long long FUN_00047260__impl(int, ...);
#define reflash_fb_data_to_lcd(...) FUN_00047260__impl(0, ##__VA_ARGS__)
extern long long FUN_00047b1c__impl(int, ...);
#define send_response_data_to_msgqueue(...) FUN_00047b1c__impl(0, ##__VA_ARGS__)
extern long long FUN_00047ba8__impl(int, ...);
#define send_response_data_to_ble(...) FUN_00047ba8__impl(0, ##__VA_ARGS__)
extern long long FUN_000488bc__impl(int, ...);
#define SendPowerInfoToSlave(...) FUN_000488bc__impl(0, ##__VA_ARGS__)
extern long long FUN_00048b44__impl(int, ...);
#define FUN_00048b44(...) FUN_00048b44__impl(0, ##__VA_ARGS__)
extern long long FUN_0004a9ec__impl(int, ...);
#define enter_dashboard_burial_point(...) FUN_0004a9ec__impl(0, ##__VA_ARGS__)
extern long long FUN_0004aab0__impl(int, ...);
#define exit_dashboard_burial_point(...) FUN_0004aab0__impl(0, ##__VA_ARGS__)
extern long long FUN_0007d1d0__impl(int, ...);
#define FUN_0007d1d0(...) FUN_0007d1d0__impl(0, ##__VA_ARGS__)
extern long long FUN_0007d224__impl(int, ...);
#define get_timestamp(...) FUN_0007d224__impl(0, ##__VA_ARGS__)
extern long long FUN_0007d248__impl(int, ...);
#define check_dashboard_device_status_range(...) FUN_0007d248__impl(0, ##__VA_ARGS__)
extern long long FUN_00086c78__impl(int, ...);
#define memset_bytes(...) FUN_00086c78__impl(0, ##__VA_ARGS__)
extern long long block__impl(int, ...);
#define block(...) block__impl(0, ##__VA_ARGS__)
extern long long send_event_status__impl(int, ...);
#define send_event_status(...) send_event_status__impl(0, ##__VA_ARGS__)
extern long long sync_to_slave__impl(int, ...);
#define sync_to_slave(...) sync_to_slave__impl(0, ##__VA_ARGS__)
extern long long thunk_FUN_00074f68__impl(int, ...);
#define thunk_FUN_00074f68(...) thunk_FUN_00074f68__impl(0, ##__VA_ARGS__)

#define DAT_0003b254 ((volatile char*)((uintptr_t)&g_dashboard_widget_state) /*=0x20004950*/)
#define DAT_0003b258 ((volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/)
#define DAT_0003b25c ((volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/)
#define DAT_0003b260 ("ui_DashBoard_task" /*=0xa957d*/)
#define DAT_0003b264 ("%s(): Enter DASHBOARD_INIT_STATUS task....\n" /*=0xa9243*/)
#define DAT_0003b268 ("%s(): dashboard function exit ...\n" /*=0xa926f*/)
#define DAT_0003b26c ((volatile int*)((uintptr_t)&g_dashboard_reset_pending_flags) /*=0x20007aa0*/)
#define DAT_0003b270 ("%s(): DASHBOARD INIT .......\n" /*=0xa9292*/)
#define DAT_0003b274 ((volatile byte*)((uintptr_t)&g_widget0_index_raw) /*=0x2001b816*/)
#define DAT_0003b278 ((volatile byte*)((uintptr_t)&g_news_widget_index_raw) /*=0x2001b814*/)
#define DAT_0003b27c ((volatile byte*)((uintptr_t)&g_stocks_widget_index_raw) /*=0x2001b815*/)
#define DAT_0003b280 ("%s(): quicknote index = %d,stocks index = %d,news index = %d\n" /*=0xa92b0*/)
#define DAT_0003b284 ("%s(): db_info->schedule_disp_status = %d\n" /*=0xa92ee*/)
#define DAT_0003b288 ("%s(): db_info->stocks_disp_mode = %d\n" /*=0xa9127*/)
#define DAT_0003b28c ("%s(): db_info->news_disp_mode = %d\n" /*=0xa9318*/)
#define DAT_0003b290 ("%s(): master sync quicknote index to slave ,index = %d\n" /*=0xa933c*/)
#define DAT_0003b294 ("%s(): SYNC TO Slave failed...,don't exec key function.\n" /*=0xa0fad*/)
#define DAT_0003b298 ((volatile int*)((uintptr_t)&g_dashboard_reflash_frame_idx) /*=0x20009fd0*/)
#define DAT_0003b29c (((uintptr_t)&g_dashboard_lock_ready_flags) /*=0x20007570*/)
#define DAT_0003b2a0 ((volatile int*)((uintptr_t)&g_dashboard_lock_sent_flags) /*=0x2000756c*/)
#define DAT_0003b2a4 ("%s(): send dashboard lock info to app ,status = %d \n" /*=0x9f929*/)
#define DAT_0003b2a8 ("%s(): master sync stocks index to slave,index = %d\n" /*=0xa9374*/)
#define DAT_0003b584 ((volatile int*)0x0UL)
#define DAT_0003b588 (0x0UL) /* unknown lit */
#define DAT_0003b58c (0x0UL) /* unknown lit */
#define DAT_0003b590 (0x0UL) /* unknown lit */
#define DAT_0003b594 (0x0UL) /* unknown lit */
#define DAT_0003b598 (0x0UL) /* unknown lit */
#define DAT_0003b59c ((volatile int*)0x0UL)
#define DAT_0003b5a0 ((volatile int*)0x0UL)
#define DAT_0003b5a4 (0x0UL) /* unknown lit */
#define DAT_0003b5a8 (0x0UL) /* unknown lit */
#define DAT_0003b5ac (0x0UL) /* unknown lit */
#define DAT_0003b5b0 (0x0UL) /* unknown lit */
#define DAT_0003b5b4 (0x0UL) /* unknown lit */
#define DAT_0003b5b8 ((volatile int*)0x0UL)
#define DAT_0003b5bc (0x0UL) /* unknown lit */
#define DAT_0003b5c0 ((volatile undefined4*)0x0UL)
#define DAT_0003b760 ((volatile int*)0x0UL)
#define DAT_0003b764 (0x0UL) /* unknown lit */
#define DAT_0003b768 (0x0UL) /* unknown lit */
#define DAT_0003b76c ((volatile int*)0x0UL)
#define DAT_0003b770 (0x0UL) /* unknown lit */
#define DAT_0003b774 ((volatile int*)0x0UL)
#define DAT_0003b778 (0x0UL) /* unknown lit */
#define DAT_0003b77c ((volatile int*)0x0UL)
#define DAT_0003b780 (0x0UL) /* unknown lit */
#define DAT_0003b784 (0x0UL) /* unknown lit */
#define DAT_0003b788 (0x0UL) /* unknown lit */


/* WARNING: Removing unreachable block (ram,0x0003b4c6) */
/* WARNING: Removing unreachable block (ram,0x0003b202) */

undefined4 ui_DashBoard_task(int param_1,undefined4 param_2,int param_3)

{
  byte bVar1;
  byte bVar2;
  char cVar3;
  char *pcVar4;
  int *piVar5;
  int *piVar6;
  byte *pbVar7;
  byte *pbVar8;
  byte *pbVar9;
  undefined4 *puVar10;
  byte bVar11;
  int iVar12;
  uint uVar13;
  int iVar14;
  char *pcVar15;
  undefined4 uVar16;
  undefined4 uVar17;
  undefined1 uVar18;
  int iVar19;
  uint uVar20;
  int iVar21;
  int iVar22;
  longlong lVar23;
  undefined4 local_30;
  undefined4 local_2c;
  
  iVar12 = get_device_info();
  pcVar4 = DAT_0003b254;
  iVar21 = iVar12 + 0xef;
  gui_set_active_canvas(param_1 + 0x24);
  piVar5 = DAT_0003b258;
  if (*pcVar4 == '\0') {
    if (2 < *DAT_0003b258) {
      if (*DAT_0003b25c == 0) {
        DEBUG_PRINT(DAT_0003b264,DAT_0003b260);
      }
      else {
        debug_print();
      }
    }
    enter_dashboard_burial_point();
    if (param_3 == 2) {
      if (2 < *piVar5) {
        if (*DAT_0003b25c == 0) {
          DEBUG_PRINT(DAT_0003b268,DAT_0003b260);
        }
        else {
          debug_print();
        }
      }
      gui_screen_clear();
      memset_bytes(DAT_0003b254,0,0x28);
      *DAT_0003b26c = *DAT_0003b26c & 0xfffffffd;
      goto LAB_0003affc;
    }
    if ((param_3 != 1) || (pcVar4[9] != '\0')) goto LAB_0003b198;
    if (2 < *piVar5) {
      if (*DAT_0003b25c == 0) {
        DEBUG_PRINT(DAT_0003b270,DAT_0003b260);
      }
      else {
        debug_print();
      }
    }
    send_event_status(0x1e);
    memset_bytes(DAT_0003b254,0,0x28);
    gui_screen_clear();
    pbVar7 = DAT_0003b274;
    pcVar4[9] = '\x01';
    pbVar9 = DAT_0003b27c;
    pbVar8 = DAT_0003b278;
    bVar11 = *pbVar7;
    pcVar4[0x20] = *(char *)(iVar12 + 0x155);
    iVar14 = *piVar5;
    bVar1 = *pbVar9;
    bVar2 = *pbVar8;
    uVar13 = (uint)bVar2;
    pcVar4[1] = bVar11;
    pcVar4[3] = bVar1;
    pcVar4[5] = bVar2;
    piVar6 = DAT_0003b25c;
    if (2 < iVar14) {
      if (*DAT_0003b25c == 0) {
        DEBUG_PRINT(DAT_0003b280,DAT_0003b260,(uint)bVar11,(uint)bVar1,uVar13);
      }
      else {
        debug_print(DAT_0003b280);
      }
      if (2 < *piVar5) {
        if (*piVar6 == 0) {
          DEBUG_PRINT(DAT_0003b284,DAT_0003b260,(uint)*(byte *)(iVar12 + 0x155),0,uVar13);
        }
        else {
          debug_print();
        }
        if (2 < *piVar5) {
          if (*piVar6 == 0) {
            DEBUG_PRINT(DAT_0003b288,DAT_0003b260,(uint)*(byte *)(iVar12 + 0x157),0,uVar13);
          }
          else {
            debug_print();
          }
          if (2 < *piVar5) {
            if (*piVar6 == 0) {
              DEBUG_PRINT(DAT_0003b28c,DAT_0003b260,(uint)*(byte *)(iVar12 + 0x158));
            }
            else {
              debug_print();
            }
          }
        }
      }
    }
    pcVar15 = (char *)get_device_info();
    if (*pcVar15 == '\x01') {
      local_30 = CONCAT22((*(volatile uint16_t*)((char*)&local_30 + 2)),0x202);
      cVar3 = pcVar4[0x1a];
      if (cVar3 == '\0') {
        uVar13 = sync_dashboard_default_language();
        (*(volatile uint16_t*)((char*)&local_30 + 0)) = CONCAT11((byte)((uVar13 & 0xf) << 4) | (*(volatile uint8_t*)((char*)&local_30 + 1)),(undefined1)local_30)
        ;
        if (2 < *piVar5) {
          iVar14 = *DAT_0003b25c;
          uVar16 = DAT_0003b290;
          uVar17 = DAT_0003b260;
LAB_0003b116:
          if (iVar14 == 0) {
            DEBUG_PRINT(uVar16,uVar17);
          }
          else {
            debug_print();
          }
        }
      }
      else if (cVar3 == '\x01') {
        local_30 = CONCAT22((*(volatile uint16_t*)((char*)&local_30 + 2)),0x402);
        uVar13 = getStocksIndex();
        (*(volatile uint16_t*)((char*)&local_30 + 0)) = CONCAT11((byte)((uVar13 & 0xf) << 4) | (*(volatile uint8_t*)((char*)&local_30 + 1)),(undefined1)local_30)
        ;
        if (2 < *piVar5) {
          iVar14 = *DAT_0003b25c;
          uVar16 = DAT_0003b2a8;
          uVar17 = DAT_0003b260;
          goto LAB_0003b116;
        }
      }
      else if (cVar3 == '\x02') {
        local_30 = CONCAT22((*(volatile uint16_t*)((char*)&local_30 + 2)),0x602);
        uVar13 = getNewsIndex();
        (*(volatile uint16_t*)((char*)&local_30 + 0)) = CONCAT11((byte)((uVar13 & 0xf) << 4) | (*(volatile uint8_t*)((char*)&local_30 + 1)),(undefined1)local_30)
        ;
        if (2 < *piVar5) {
          iVar14 = *DAT_0003b584;
          uVar16 = DAT_0003b58c;
          uVar17 = DAT_0003b588;
          goto LAB_0003b116;
        }
      }
      uVar16 = get_device_info();
      iVar14 = sync_to_slave(uVar16,6,&local_30,2);
      if (iVar14 < 5000) {
        if (2 < *piVar5) {
          if (*DAT_0003b584 == 0) {
            uVar16 = get_timestamp();
            DEBUG_PRINT(DAT_0003b590,DAT_0003b588,iVar14,uVar16);
          }
          else {
            uVar16 = get_timestamp();
            debug_print(DAT_0003b590,DAT_0003b588,iVar14,uVar16);
          }
        }
      }
      else if (1 < *piVar5) {
        if (*DAT_0003b25c == 0) {
          DEBUG_PRINT(DAT_0003b294,DAT_0003b260);
        }
        else {
          debug_print();
        }
      }
    }
    gui_canvas_flags_clear_bit1();
    piVar5 = DAT_0003b298;
    *DAT_0003b298 = 0;
    while (piVar6 = DAT_0003b298, *DAT_0003b298 < 4) {
      uVar16 = get_device_info();
      DashBoard_Reflash(iVar21,uVar16,1,*(undefined1 *)(iVar12 + 0x153));
      puVar10 = DAT_0003b5c0;
      iVar14 = *piVar6;
      uVar13 = 0;
      local_30 = *DAT_0003b5c0;
      do {
        local_2c = puVar10[1];
        iVar19 = 0;
        do {
          iVar22 = *(int *)(param_1 + 0x24 + uVar13 * 4);
          bVar11 = *(byte *)(iVar22 + iVar19);
          if (bVar11 != 0) {
            *(byte *)(iVar22 + iVar19) =
                 bVar11 & *(byte *)((uint)*(byte *)((int)&local_30 + iVar14) * 0x140 +
                                    (uVar13 % 0x1a) * 0xa00 + DAT_0003b594 + iVar19);
          }
          iVar19 = iVar19 + 1;
        } while (iVar19 != 0x140);
        uVar13 = uVar13 + 1;
      } while (uVar13 != 199);
      *piVar5 = iVar14 + 1;
      iVar14 = get_device_info();
      uVar16 = *(undefined4 *)(iVar14 + 0xeb4);
      iVar14 = get_device_info();
      reflash_fb_data_to_lcd(uVar16,*(undefined4 *)(iVar14 + 0xeb8),0,0,0x280,199);
    }
    gui_canvas_flags_set_bit1();
    lVar23 = thunk_FUN_00074f68();
    uVar13 = (uint)((ulonglong)(lVar23 * 1000) >> 0x20);
    *(uint *)(pcVar4 + 0x10) = (uint)(lVar23 * 1000) >> 0xf | uVar13 * ((uintptr_t)&rodata_20000) /*=0x20000*/;
    *(uint *)(pcVar4 + 0x14) = uVar13 >> 0xf;
    *pcVar4 = '\x01';
    FUN_00048b44(0x42);
    send_dashboard_status_sync();
LAB_0003b198:
    iVar12 = FUN_0007d1d0(DAT_0003b29c);
    if (-1 < iVar12 << 0x1e) {
      return 0;
    }
    iVar12 = FUN_0007d1d0(DAT_0003b2a0);
    if (iVar12 << 0x1e < 0) {
      return 0;
    }
    local_30 = 0x650;
    local_2c = CONCAT22((*(volatile uint16_t*)((char*)&local_2c + 2)),0x201);
    if (2 < *DAT_0003b258) {
      if (*DAT_0003b25c == 0) {
        DEBUG_PRINT(DAT_0003b2a4,DAT_0003b260,2);
      }
      else {
        debug_print();
      }
    }
    send_response_data_to_msgqueue(&local_30,6);
    send_response_data_to_ble();
    *DAT_0003b2a0 = *DAT_0003b2a0 | 2;
    return 0;
  }
  if (*pcVar4 != '\x01') {
    return 0;
  }
  uVar13 = FUN_0007d1d0(DAT_0003b598);
  piVar5 = DAT_0003b59c;
  if (((uVar13 & 2) != 0) && (iVar14 = FUN_0007d1d0(DAT_0003b5a0), -1 < iVar14 << 0x1e)) {
    local_30 = 0x650;
    local_2c = CONCAT22((*(volatile uint16_t*)((char*)&local_2c + 2)),0x201);
    if (2 < *piVar5) {
      if (*DAT_0003b584 == 0) {
        DEBUG_PRINT(DAT_0003b5a4,DAT_0003b588,2);
      }
      else {
        debug_print();
      }
    }
    send_response_data_to_msgqueue(&local_30,6);
    send_response_data_to_ble();
    *DAT_0003b5a0 = *DAT_0003b5a0 | 2;
  }
  uVar13 = msg_content_recalc_unread();
  if (uVar13 != (byte)pcVar4[0x23]) {
    bVar11 = msg_content_recalc_unread();
    iVar14 = *piVar5;
    pcVar4[0x23] = bVar11;
    if (2 < iVar14) {
      if (*DAT_0003b584 == 0) {
        DEBUG_PRINT(DAT_0003b5a8,DAT_0003b588,(uint)bVar11);
      }
      else {
        debug_print();
      }
    }
    send_dashboard_status_sync();
  }
  gui_canvas_flags_set_bit1();
  piVar6 = DAT_0003b584;
  if (*piVar5 < 3) {
    if (param_3 != 2) goto LAB_0003b742;
  }
  else {
    if (*DAT_0003b584 == 0) {
      DEBUG_PRINT(DAT_0003b5ac,DAT_0003b588);
    }
    else {
      debug_print();
    }
    if (param_3 != 2) {
LAB_0003b742:
      if (param_3 == 1) {
        uVar16 = get_device_info();
        DashBoard_Reflash(iVar21,uVar16,1,*(undefined1 *)(iVar12 + 0x153));
        return 0;
      }
      if (param_3 == 0) {
        if (2 < *piVar5) {
          if (*DAT_0003b584 == 0) {
            DEBUG_PRINT(DAT_0003b5bc,DAT_0003b588,(uint)*(byte *)(iVar12 + 0x153));
          }
          else {
            debug_print();
          }
        }
        uVar16 = get_device_info();
        DashBoard_Reflash(iVar21,uVar16,0,*(undefined1 *)(iVar12 + 0x153));
        goto LAB_0003b512;
      }
      if (param_3 != 4) {
        if (param_3 == 6) {
          if (2 < *piVar5) {
            if (*DAT_0003b760 == 0) {
              DEBUG_PRINT(DAT_0003b784,DAT_0003b764);
            }
            else {
              debug_print();
            }
          }
          iVar12 = get_device_info();
          uVar18 = 1;
          iVar12 = *(int *)(iVar12 + 0xfec);
        }
        else {
          if (param_3 != 7) goto LAB_0003b512;
          if (2 < *piVar5) {
            if (*DAT_0003b760 == 0) {
              DEBUG_PRINT(DAT_0003b788,DAT_0003b764);
            }
            else {
              debug_print();
            }
          }
          iVar12 = get_device_info();
          uVar18 = 0;
          iVar12 = *(int *)(iVar12 + 0xfec);
        }
        *(undefined1 *)(iVar12 + 0x5f) = uVar18;
        send_dashboard_status_sync();
        goto LAB_0003b512;
      }
      if (2 < *piVar5) {
        if (*DAT_0003b760 == 0) {
          DEBUG_PRINT(DAT_0003b768,DAT_0003b764,(uint)(byte)pcVar4[0x19]);
        }
        else {
          debug_print();
        }
      }
      cVar3 = pcVar4[0x1a];
      if (cVar3 == '\0') {
        bVar11 = pcVar4[2];
        if (1 < bVar11) {
          cVar3 = (pcVar4[1] + 1U) - bVar11 * ((byte)(pcVar4[1] + 1U) / bVar11);
          *DAT_0003b76c = cVar3;
          pcVar4[1] = cVar3;
          set_dashboard_startup_default_language();
          if (2 < *piVar5) {
            uVar13 = (uint)(byte)pcVar4[1];
            iVar14 = *DAT_0003b760;
            uVar16 = DAT_0003b770;
            goto LAB_0003b614;
          }
        }
      }
      else if (cVar3 == '\x01') {
        uVar13 = (uint)(byte)pcVar4[4];
        if (1 < uVar13) {
          uVar20 = (uint)(byte)(pcVar4[3] + 1) - uVar13 * ((byte)(pcVar4[3] + 1) / uVar13);
          uVar13 = uVar20 & 0xff;
          cVar3 = (char)uVar20;
          *DAT_0003b774 = cVar3;
          iVar14 = *piVar5;
          pcVar4[3] = cVar3;
          if (2 < iVar14) {
            iVar14 = *DAT_0003b760;
            uVar16 = DAT_0003b778;
LAB_0003b614:
            if (iVar14 == 0) {
              DEBUG_PRINT(uVar16,DAT_0003b764,uVar13);
            }
            else {
              debug_print();
            }
          }
        }
      }
      else if (((cVar3 == '\x02') && (uVar13 = (uint)(byte)pcVar4[6], 1 < uVar13)) &&
              (pcVar4[5] != '\x03')) {
        uVar20 = (uint)(byte)(pcVar4[5] + 1);
        uVar20 = uVar20 - uVar13 * (uVar20 / uVar13);
        uVar13 = uVar20 & 0xff;
        cVar3 = (char)uVar20;
        *DAT_0003b77c = cVar3;
        iVar14 = *piVar5;
        pcVar4[5] = cVar3;
        if (2 < iVar14) {
          iVar14 = *DAT_0003b760;
          uVar16 = DAT_0003b780;
          goto LAB_0003b614;
        }
      }
      uVar16 = get_device_info();
      DashBoard_Reflash(iVar21,uVar16,4,*(undefined1 *)(iVar12 + 0x153));
      send_dashboard_status_sync_compact();
LAB_0003b512:
      pcVar15 = (char *)get_device_info();
      if (*pcVar15 != '\x01') {
        return 0;
      }
      iVar12 = check_dashboard_device_status_range();
      lVar23 = thunk_FUN_00074f68();
      uVar20 = (uint)((ulonglong)(lVar23 * 1000) >> 0x20);
      uVar13 = (uint)(lVar23 * 1000) >> 0xf | uVar20 * ((uintptr_t)&rodata_20000) /*=0x20000*/;
      uVar20 = uVar20 >> 0xf;
      if (iVar12 == 0) {
        iVar12 = get_device_info();
        if (*(char *)(*(int *)(iVar12 + 0xfec) + 0x5f) != '\0') {
          if (pcVar4[0xb] != '\0') {
            return 0;
          }
          if ((int)((uVar20 - *(int *)(pcVar4 + 0x14)) - (uint)(uVar13 < *(uint *)(pcVar4 + 0x10)))
              < (int)(uint)(uVar13 - *(uint *)(pcVar4 + 0x10) < 0x5dd)) {
            return 0;
          }
        }
        uVar16 = 1;
      }
      else {
        iVar12 = get_device_info();
        if (*(char *)(*(int *)(iVar12 + 0xfec) + 0x5f) != '\x01') {
          if (pcVar4[0xb] != '\0') {
            return 0;
          }
          if ((int)((uVar20 - *(int *)(pcVar4 + 0x14)) - (uint)(uVar13 < *(uint *)(pcVar4 + 0x10)))
              < (int)(uint)(uVar13 - *(uint *)(pcVar4 + 0x10) < 0x5dd)) {
            return 0;
          }
        }
        uVar16 = 0;
      }
      SendPowerInfoToSlave(uVar16);
      pcVar4[0xb] = '\x01';
      return 0;
    }
    if (2 < *piVar5) {
      if (*piVar6 == 0) {
        DEBUG_PRINT(DAT_0003b5b0,DAT_0003b588);
      }
      else {
        debug_print();
      }
    }
  }
  send_event_status(0x1f);
  FUN_0004382c();
  memset_bytes(DAT_0003b5b4,0,0x28);
  *DAT_0003b5b8 = *DAT_0003b5b8 & 0xfffffffd;
LAB_0003affc:
  exit_dashboard_burial_point();
  return 0;
}


