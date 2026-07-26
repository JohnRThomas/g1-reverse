/* readable reconstruction; identity: FUN_0003af78 @ 0x0003af78
 * public-name: ui_DashBoard_task
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   set_dashboard_startup_default_language   <= FUN_0001672c @ 0x0001672c
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   msg_content_recalc_unread                <= FUN_00033cf8 @ 0x00033cf8
 *   sync_dashboard_default_language          <= FUN_00037060 @ 0x00037060
 *   getStocksIndex                           <= FUN_000370bc @ 0x000370bc
 *   getNewsIndex                             <= FUN_0003719c @ 0x0003719c
 *   DashBoard_Reflash                        <= FUN_0003727c @ 0x0003727c
 *   send_dashboard_status_sync               <= FUN_0003ae6c @ 0x0003ae6c
 *   send_dashboard_status_sync_compact       <= FUN_0003af04 @ 0x0003af04
 *   gui_set_active_canvas                    <= FUN_000431b4 @ 0x000431b4
 *   gui_screen_clear                         <= FUN_000431c0 @ 0x000431c0
 *   gui_canvas_flags_set_bit1                <= FUN_000432d0 @ 0x000432d0
 *   gui_canvas_flags_clear_bit1              <= FUN_000432ec @ 0x000432ec
 *   gui_screen_fade_out_transition           <= FUN_0004382c @ 0x0004382c
 *   reflash_fb_data_to_lcd                   <= FUN_00047260 @ 0x00047260
 *   send_response_data_to_msgqueue           <= FUN_00047b1c @ 0x00047b1c
 *   send_response_data_to_ble                <= FUN_00047ba8 @ 0x00047ba8
 *   SendPowerInfoToSlave                     <= FUN_000488bc @ 0x000488bc
 *   set_dashboard_display_level_clamped      <= FUN_00048b44 @ 0x00048b44
 *   enter_dashboard_burial_point             <= FUN_0004a9ec @ 0x0004a9ec
 *   exit_dashboard_burial_point              <= FUN_0004aab0 @ 0x0004aab0
 *   dashboard_read_word                      <= FUN_0007d1d0 @ 0x0007d1d0
 *   get_timestamp                            <= FUN_0007d224 @ 0x0007d224
 *   check_dashboard_device_status_range      <= FUN_0007d248 @ 0x0007d248
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_9f929                             @ 0x0009f929   [INLINED -- G6 literal batch]
 *   rodata_a0fad                             @ 0x000a0fad   [INLINED -- G6 literal batch]
 *   rodata_a0fe5                             @ 0x000a0fe5   [INLINED -- G6 literal batch]
 *   rodata_a8c57                             @ 0x000a8c57
 *   rodata_a9127                             @ 0x000a9127   [INLINED -- G6 literal batch]
 *   rodata_a9243                             @ 0x000a9243   [INLINED -- G6 literal batch]
 *   rodata_a926f                             @ 0x000a926f   [INLINED -- G6 literal batch]
 *   rodata_a9292                             @ 0x000a9292   [INLINED -- G6 literal batch]
 *   rodata_a92b0                             @ 0x000a92b0   [INLINED -- G6 literal batch]
 *   rodata_a92ee                             @ 0x000a92ee   [INLINED -- G6 literal batch]
 *   rodata_a9318                             @ 0x000a9318   [INLINED -- G6 literal batch]
 *   rodata_a933c                             @ 0x000a933c   [INLINED -- G6 literal batch]
 *   rodata_a93da                             @ 0x000a93da   [INLINED -- G6 literal batch]
 *   rodata_a9437                             @ 0x000a9437   [INLINED -- G6 literal batch]
 *   rodata_a9465                             @ 0x000a9465   [INLINED -- G6 literal batch]
 *   rodata_a947f                             @ 0x000a947f   [INLINED -- G6 literal batch]
 *   rodata_a94c5                             @ 0x000a94c5   [INLINED -- G6 literal batch]
 *   rodata_a9529                             @ 0x000a9529   [INLINED -- G6 literal batch]
 *   rodata_a9551                             @ 0x000a9551   [INLINED -- G6 literal batch]
 *   rodata_a957d                             @ 0x000a957d   [INLINED -- G6 literal batch]
 *   rodata_aae20                             @ 0x000aae20
 *   g_log_level                              @ 0x2000230c
 *   g_dashboard_widget_state                 @ 0x20004950
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_dashboard_lock_sent_flags              @ 0x2000756c
 *   g_dashboard_lock_ready_flags             @ 0x20007570
 *   g_dashboard_reset_pending_flags          @ 0x20007aa0
 *   g_dashboard_reflash_frame_idx            @ 0x20009fd0
 *   g_news_widget_index_raw                  @ 0x2001b814
 *   g_stocks_widget_index_raw                @ 0x2001b815
 *   g_widget0_index_raw                      @ 0x2001b816
 */
/* Reconstructed ui_DashBoard_task @ 0x3af78  (parity: 100/100 trials, PROVEN) */
#include <stdint.h>
#include "../headers/g1_log.h"
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
static inline int CARRY2(uint a, uint b){return ((a&0xffff)+(b&0xffff))>0xffff;}
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

extern int set_dashboard_startup_default_language(void);
extern uintptr_t get_device_info(void);
extern uint32_t msg_content_recalc_unread(void);
extern uint32_t sync_dashboard_default_language(void);
extern uint32_t getStocksIndex(void);
extern uint32_t getNewsIndex(void);
extern int DashBoard_Reflash(uintptr_t, uintptr_t, uint32_t, uint32_t);
extern int send_dashboard_status_sync(void);
extern int send_dashboard_status_sync_compact(void);
extern int gui_set_active_canvas(uintptr_t);
extern int gui_screen_clear(void);
extern int gui_canvas_flags_set_bit1(void);
extern int gui_canvas_flags_clear_bit1(void);
extern int gui_screen_fade_out_transition(void);
extern int reflash_fb_data_to_lcd(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t);
extern int send_response_data_to_msgqueue(const void *, uint32_t);
extern int send_response_data_to_ble(void);
extern int SendPowerInfoToSlave(uint32_t);
extern int set_dashboard_display_level_clamped(uint32_t);
extern int enter_dashboard_burial_point(void);
extern int exit_dashboard_burial_point(void);
extern uint32_t dashboard_read_word(uintptr_t);
extern uint32_t get_timestamp(void);
extern uint32_t check_dashboard_device_status_range(void);
extern void *memset_bytes(void *, int, uint32_t);
extern int send_event(uint32_t);
extern int sync_to_slave(uintptr_t, uint32_t, const void *, uint32_t);
extern uint64_t thunk_FUN_00074f68(void);

#define DAT_0003b254 ((volatile char*)0x20004950UL)
#define DAT_0003b258 ((volatile int*)0x2000230cUL)
#define DAT_0003b25c ((volatile int*)0x20007554UL)
#define DAT_0003b260 (0xa957dUL)
#define DAT_0003b264 (0xa9243UL)
#define DAT_0003b268 (0xa926fUL)
#define DAT_0003b26c ((volatile int*)0x20007aa0UL)
#define DAT_0003b270 (0xa9292UL)
#define DAT_0003b274 ((volatile byte*)0x2001b816UL)
#define DAT_0003b278 ((volatile byte*)0x2001b814UL)
#define DAT_0003b27c ((volatile byte*)0x2001b815UL)
#define DAT_0003b280 (0xa92b0UL)
#define DAT_0003b284 (0xa92eeUL)
#define DAT_0003b288 (0xa9127UL)
#define DAT_0003b28c (0xa9318UL)
#define DAT_0003b290 (0xa933cUL)
#define DAT_0003b294 (0xa0fadUL)
#define DAT_0003b298 ((volatile int*)0x20009fd0UL)
#define DAT_0003b29c (0x20007570UL)
#define DAT_0003b2a0 ((volatile int*)0x2000756cUL)
#define DAT_0003b2a4 (0x9f929UL)
#define DAT_0003b2a8 (0xa9374UL)
#define DAT_0003b584 ((volatile int*)0x20007554UL)
#define DAT_0003b588 (0xa957dUL)
#define DAT_0003b58c (0xa93a8UL)
#define DAT_0003b590 (0xa0fe5UL)
#define DAT_0003b594 (0xaae20UL)
#define DAT_0003b598 (0x20007570UL)
#define DAT_0003b59c ((volatile int*)0x2000230cUL)
#define DAT_0003b5a0 ((volatile int*)0x2000756cUL)
#define DAT_0003b5a4 (0x9f929UL)
#define DAT_0003b5a8 (0xa93daUL)
#define DAT_0003b5ac (0xa9437UL)
#define DAT_0003b5b0 (0xa926fUL)
#define DAT_0003b5b4 (0x20004950UL)
#define DAT_0003b5b8 ((volatile int*)0x20007aa0UL)
#define DAT_0003b5bc (0xa9465UL)
#define DAT_0003b5c0 ((volatile undefined4*)0xa8c57UL)
#define DAT_0003b760 ((volatile int*)0x20007554UL)
#define DAT_0003b764 (0xa957dUL)
#define DAT_0003b768 (0xa947fUL)
#define DAT_0003b76c ((volatile byte*)0x2001b816UL)
#define DAT_0003b770 (0xa94c5UL)
#define DAT_0003b774 ((volatile byte*)0x2001b815UL)
#define DAT_0003b778 (0xa94e9UL)
#define DAT_0003b77c ((volatile byte*)0x2001b814UL)
#define DAT_0003b780 (0xa950aUL)
#define DAT_0003b784 (0xa9529UL)
#define DAT_0003b788 (0xa9551UL)


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
        log_message(DAT_0003b264,DAT_0003b260);
      }
      else {
        debug_print(DAT_0003b264,DAT_0003b260);
      }
    }
    enter_dashboard_burial_point();
    if (param_3 == 2) {
      if (2 < *piVar5) {
        if (*DAT_0003b25c == 0) {
          log_message(DAT_0003b268,DAT_0003b260);
        }
        else {
          debug_print(DAT_0003b268,DAT_0003b260);
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
        log_message(DAT_0003b270,DAT_0003b260);
      }
      else {
        debug_print(DAT_0003b270,DAT_0003b260);
      }
    }
    send_event(0x1e);
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
        log_message(DAT_0003b280,DAT_0003b260,(uint)bVar11,(uint)bVar1,uVar13);
      }
      else {
        debug_print(DAT_0003b280,DAT_0003b260,(uint)bVar11,(uint)bVar1,uVar13);
      }
      if (2 < *piVar5) {
        if (*piVar6 == 0) {
          log_message(DAT_0003b284,DAT_0003b260,(uint)*(byte *)(iVar12 + 0x155),0,uVar13);
        }
        else {
          debug_print(DAT_0003b284,DAT_0003b260,(uint)*(byte *)(iVar12 + 0x155),0,uVar13);
        }
        if (2 < *piVar5) {
          if (*piVar6 == 0) {
            log_message(DAT_0003b288,DAT_0003b260,(uint)*(byte *)(iVar12 + 0x157),0,uVar13);
          }
          else {
            debug_print(DAT_0003b288,DAT_0003b260,(uint)*(byte *)(iVar12 + 0x157),0,uVar13);
          }
          if (2 < *piVar5) {
            if (*piVar6 == 0) {
              log_message(DAT_0003b28c,DAT_0003b260,(uint)*(byte *)(iVar12 + 0x158));
            }
            else {
              debug_print(DAT_0003b28c,DAT_0003b260,(uint)*(byte *)(iVar12 + 0x158));
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
            log_message(uVar16,uVar17);
          }
          else {
            debug_print(uVar16,uVar17);
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
            log_message(DAT_0003b590,DAT_0003b588,iVar14,uVar16);
          }
          else {
            uVar16 = get_timestamp();
            debug_print(DAT_0003b590,DAT_0003b588,iVar14,uVar16);
          }
        }
      }
      else if (1 < *piVar5) {
        if (*DAT_0003b25c == 0) {
          log_message(DAT_0003b294,DAT_0003b260);
        }
        else {
          debug_print(DAT_0003b294,DAT_0003b260);
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
    *(uint *)(pcVar4 + 0x10) = (uint)(lVar23 * 1000) >> 0xf | uVar13 * 0x20000;
    *(uint *)(pcVar4 + 0x14) = uVar13 >> 0xf;
    *pcVar4 = '\x01';
    set_dashboard_display_level_clamped(0x42);
    send_dashboard_status_sync();
LAB_0003b198:
    iVar12 = dashboard_read_word(DAT_0003b29c);
    if (-1 < iVar12 << 0x1e) {
      return 0;
    }
    iVar12 = dashboard_read_word(DAT_0003b2a0);
    if (iVar12 << 0x1e < 0) {
      return 0;
    }
    local_30 = 0x650;
    local_2c = CONCAT22((*(volatile uint16_t*)((char*)&local_2c + 2)),0x201);
    if (2 < *DAT_0003b258) {
      if (*DAT_0003b25c == 0) {
        log_message(DAT_0003b2a4,DAT_0003b260,2);
      }
      else {
        debug_print(DAT_0003b2a4,DAT_0003b260,2);
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
  uVar13 = dashboard_read_word(DAT_0003b598);
  piVar5 = DAT_0003b59c;
  if (((uVar13 & 2) != 0) && (iVar14 = dashboard_read_word(DAT_0003b5a0), -1 < iVar14 << 0x1e)) {
    local_30 = 0x650;
    local_2c = CONCAT22((*(volatile uint16_t*)((char*)&local_2c + 2)),0x201);
    if (2 < *piVar5) {
      if (*DAT_0003b584 == 0) {
        log_message(DAT_0003b5a4,DAT_0003b588,2);
      }
      else {
        debug_print(DAT_0003b5a4,DAT_0003b588,2);
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
        log_message(DAT_0003b5a8,DAT_0003b588,(uint)bVar11);
      }
      else {
        debug_print(DAT_0003b5a8,DAT_0003b588,(uint)bVar11);
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
      log_message(DAT_0003b5ac,DAT_0003b588);
    }
    else {
      debug_print(DAT_0003b5ac,DAT_0003b588);
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
            log_message(DAT_0003b5bc,DAT_0003b588,(uint)*(byte *)(iVar12 + 0x153));
          }
          else {
            debug_print(DAT_0003b5bc,DAT_0003b588,(uint)*(byte *)(iVar12 + 0x153));
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
              log_message(DAT_0003b784,DAT_0003b764);
            }
            else {
              debug_print(DAT_0003b784,DAT_0003b764);
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
              log_message(DAT_0003b788,DAT_0003b764);
            }
            else {
              debug_print(DAT_0003b788,DAT_0003b764);
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
          log_message(DAT_0003b768,DAT_0003b764,(uint)(byte)pcVar4[0x19]);
        }
        else {
          debug_print(DAT_0003b768,DAT_0003b764,(uint)(byte)pcVar4[0x19]);
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
              log_message(uVar16,DAT_0003b764,uVar13);
            }
            else {
              debug_print(uVar16,DAT_0003b764,uVar13);
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
      uVar13 = (uint)(lVar23 * 1000) >> 0xf | uVar20 * 0x20000;
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
        log_message(DAT_0003b5b0,DAT_0003b588);
      }
      else {
        debug_print(DAT_0003b5b0,DAT_0003b588);
      }
    }
  }
  send_event(0x1f);
  gui_screen_fade_out_transition();
  memset_bytes(DAT_0003b5b4,0,0x28);
  *DAT_0003b5b8 = *DAT_0003b5b8 & 0xfffffffd;
LAB_0003affc:
  exit_dashboard_burial_point();
  return 0;
}
