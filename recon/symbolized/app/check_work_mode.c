#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00027758 @ 0x00027758
 * public-name: check_work_mode
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   compute_lux_brightness_bucket            <= FUN_00010840 @ 0x00010840
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   get_current_work_mode                    <= FUN_00016940 @ 0x00016940
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   esb_send_command_and_wait_ack            <= FUN_00027448 @ 0x00027448
 *   display_panel_is_secondary               <= FUN_0002bed0 @ 0x0002bed0
 *   debounce_read_pending_flag_2             <= FUN_0002eba0 @ 0x0002eba0
 *   flash_get_ready_status_bit               <= FUN_000304f0 @ 0x000304f0
 *   pt_nfc_eeprom_link_start                 <= FUN_00030c90 @ 0x00030c90
 *   get_glassbox_charge_status               <= FUN_00032784 @ 0x00032784
 *   get_glassbox_charge_percent              <= FUN_000327c4 @ 0x000327c4
 *   enter_wear_burial_point                  <= FUN_0004a890 @ 0x0004a890
 *   k_uptime_get_1                           <= FUN_0007cb2c @ 0x0007cb2c
 *   set_shutdown_flag                        <= FUN_0007cbfe @ 0x0007cbfe
 *   clear_app_switch_pending_flag            <= FUN_0007dada @ 0x0007dada
 * address symbols (name @ address):
 *   rodata_27cf8                             @ 0x00027cf8
 *   rodata_a0132                             @ 0x000a0132
 *   rodata_a0169                             @ 0x000a0169
 *   rodata_a01c7                             @ 0x000a01c7
 *   rodata_a01ea                             @ 0x000a01ea
 *   rodata_a020e                             @ 0x000a020e
 *   rodata_a0231                             @ 0x000a0231
 *   rodata_a024a                             @ 0x000a024a
 *   rodata_a0266                             @ 0x000a0266
 *   rodata_a028c                             @ 0x000a028c
 *   rodata_a02ab                             @ 0x000a02ab
 *   rodata_a02cc                             @ 0x000a02cc
 *   rodata_a030d                             @ 0x000a030d
 *   rodata_a1b00                             @ 0x000a1b00
 *   g_log_level                              @ 0x2000230c
 *   g_check_work_mode_ed5_field_cache        @ 0x20003025
 *   g_glassbox_lid_debounced_state           @ 0x20003026
 *   g_last_reported_battery_pct              @ 0x20003027
 *   g_last_reported_box_charge_status        @ 0x20003028
 *   g_last_reported_box_charge_pct           @ 0x20003029
 *   g_charge_notify_state_init_flag          @ 0x2000302a
 *   g_last_standby_event_id                  @ 0x2000302d
 *   g_battery_percent                        @ 0x200069e8
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_box_state_debounce_cnt                 @ 0x20018d84
 *   g_glassbox_status_debounce_cnt           @ 0x20018d85
 *   g_nfc_link_retry_cnt                     @ 0x20018d86
 *   g_wear_state_debounce_cnt                @ 0x20018d87
 *   g_wear_off_confirm_cnt                   @ 0x20018d92
 *   onboarding_pending_flag                  @ 0x20018d93
 */
/* Reconstructed check_work_mode @ 0x27758  (parity: 30/30 trials, PROVEN) */
#pragma GCC diagnostic ignored "-Wint-conversion"
#pragma GCC diagnostic ignored "-Wpointer-to-int-cast"
#pragma GCC diagnostic ignored "-Wint-to-pointer-cast"
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
typedef unsigned char undefined,undefined1,byte,uchar,uint1;
typedef unsigned short undefined2,ushort,uint2,wchar_t;
typedef unsigned int undefined4,uint,uint3,code_t,undefined3,undefined5,undefined6,undefined7;
typedef unsigned long long undefined8,ulonglong;
typedef long long longlong; typedef unsigned long ulong; typedef signed char sbyte;
typedef long long(*code)();
#define bool int
#define false 0
#define true 1
#define NAN(x) __builtin_isnan((double)(x))
#define ABS(x) __builtin_fabs((double)(x))
#define SQRT(x) __builtin_sqrt((double)(x))
#define FPMaxNum(a,b) __builtin_fmaxf((a),(b))
#define FPMinNum(a,b) __builtin_fminf((a),(b))
#define FPMax(a,b) __builtin_fmaxf((a),(b))
#define FPMin(a,b) __builtin_fminf((a),(b))
static inline int CARRY4(unsigned a,unsigned b){return (a+b)<a;}
static inline int CARRY1(unsigned a,unsigned b){return ((a&0xff)+(b&0xff))>0xff;}
static inline int CARRY2(unsigned a,unsigned b){return ((a&0xffff)+(b&0xffff))>0xffff;}
static inline int SCARRY4(int a,int b){int r=(int)((unsigned)a+(unsigned)b);return (((a^r)&(b^r))<0);}
static inline int SBORROW4(int a,int b){int r=(int)((unsigned)a-(unsigned)b);return (((a^b)&(a^r))<0);}
static inline int SBORROW1(int a,int b){signed char r=(signed char)(a-b);return ((((signed char)a^(signed char)b)&((signed char)a^r))<0);}
static inline int SBORROW2(int a,int b){short r=(short)(a-b);return ((((short)a^(short)b)&((short)a^r))<0);}

#define CONCAT11(a,b) ((unsigned short)(((unsigned)(unsigned char)(a)<<8)|(unsigned char)(b)))
#define CONCAT21(a,b) (((unsigned)(unsigned short)(a)<<8)|(unsigned char)(b))
#define CONCAT12(a,b) (((unsigned)(unsigned char)(a)<<16)|(unsigned short)(b))
#define CONCAT31(a,b) (((unsigned)(a)<<8)|(unsigned char)(b))
#define CONCAT13(a,b) (((unsigned)(unsigned char)(a)<<24)|((unsigned)(b)&0xffffffu))
#define CONCAT22(a,b) (((unsigned)(unsigned short)(a)<<16)|(unsigned short)(b))
#define CONCAT41(a,b) (((unsigned long long)(unsigned)(a)<<8)|(unsigned char)(b))
#define CONCAT44(a,b) (((unsigned long long)(unsigned)(a)<<32)|(unsigned)(b))
#define CONCAT62(a,b) (((unsigned long long)(a)<<16)|(unsigned short)(b))
#define CONCAT71(a,b) (((unsigned long long)(a)<<8)|(unsigned char)(b))
#define CONCAT53(a,b) (((unsigned long long)(a)<<24)|((unsigned)(b)&0xffffffu))
#define CONCAT61(a,b) (((unsigned long long)(a)<<8)|(unsigned char)(b))
#define SUB41(x,n) ((unsigned char)((unsigned)(x)>>((n)*8)))
#define SUB42(x,n) ((unsigned short)((unsigned)(x)>>((n)*8)))
#define SUB84(x,n) ((unsigned)((unsigned long long)(x)>>((n)*8)))
#define SUB81(x,n) ((unsigned char)((unsigned long long)(x)>>((n)*8)))
#define SUB82(x,n) ((unsigned short)((unsigned long long)(x)>>((n)*8)))
#define SUB83(x,n) ((unsigned)(((unsigned long long)(x)>>((n)*8))&0xffffffu))
#define SUB168(x,n) ((unsigned long long)(x))
#define ZEXT14(a) ((unsigned)(unsigned char)(a))
#define ZEXT18(a) ((unsigned long long)(unsigned char)(a))
#define ZEXT24(a) ((unsigned)(unsigned short)(a))
#define ZEXT28(a) ((unsigned long long)(unsigned short)(a))
#define ZEXT48(a) ((unsigned long long)(unsigned)(a))
#define ZEXT12(a) ((unsigned short)(unsigned char)(a))
#define ZEXT816(a) ((unsigned long long)(a))
#define SEXT14(a) ((unsigned)(int)(signed char)(a))
#define SEXT18(a) ((unsigned long long)(long long)(signed char)(a))
#define SEXT24(a) ((unsigned)(int)(short)(a))
#define SEXT48(a) ((unsigned long long)(long long)(int)(a))
#define __ROL4(x,n) (((unsigned)(x)<<((n)&31))|((unsigned)(x)>>((32-((n)&31))&31)))
#define __ROR4(x,n) (((unsigned)(x)>>((n)&31))|((unsigned)(x)<<((32-((n)&31))&31)))
#define __ROL1(x,n) ((unsigned char)(((unsigned)(unsigned char)(x)<<((n)&7))|((unsigned)(unsigned char)(x)>>((8-((n)&7))&7))))

extern long long log_message(long long format, ...);
extern long long compute_lux_brightness_bucket(long long);
extern long long get_device_info(void);
extern long long get_current_work_mode(void);
extern long long debug_print(void);
extern long long esb_send_command_and_wait_ack(long long,long long,long long,long long);
extern long long display_panel_is_secondary(void);
extern long long debounce_read_pending_flag_2(void);
extern long long flash_get_ready_status_bit(void);
extern long long pt_nfc_eeprom_link_start(void);
extern long long get_glassbox_charge_status(void);
extern long long get_glassbox_charge_percent(void);
extern long long enter_wear_burial_point(void);
extern long long k_uptime_get_1(void);
extern long long set_shutdown_flag(long long,long long);
extern long long clear_app_switch_pending_flag(void);
extern long long change_work_mode_to(long long);
extern long long send_event(long long);
extern long long sync_to_slave(long long,long long,long long,long long);
extern long long k_sem_take(long long,long long,long long,long long);
typedef long long (*log2_fn)(long long,long long);
typedef long long (*log3_fn)(long long,long long,long long);
typedef long long (*log4_fn)(long long,long long,long long,long long);
#define DAT_00027a6c ((volatile int*)((unsigned long)&g_battery_percent) /*=0x200069e8*/)
#define DAT_00027a70 ((volatile int*)((unsigned long)&onboarding_pending_flag) /*=0x20018d93*/)
#define DAT_00027a74 ((volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/)
#define DAT_00027a78 ((volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)
#define DAT_00027a7c ((unsigned long)&rodata_a1b00) /*=0xa1b00*/
#define DAT_00027a80 ((unsigned long)&rodata_a0132) /*=0xa0132*/
#define DAT_00027a84 ((volatile int*)((unsigned long)&g_wear_state_debounce_cnt) /*=0x20018d87*/)
#define DAT_00027a88 ((volatile int*)((unsigned long)&g_wear_off_confirm_cnt) /*=0x20018d92*/)
#define DAT_00027a8c 0xa014fUL
#define DAT_00027a90 ((volatile int*)((unsigned long)&g_nfc_link_retry_cnt) /*=0x20018d86*/)
#define DAT_00027a94 ((unsigned long)&rodata_a01c7) /*=0xa01c7*/
#define DAT_00027a98 ((unsigned long)&rodata_a0169) /*=0xa0169*/
#define DAT_00027a9c 0xa018bUL
#define DAT_00027aa0 0xa01a7UL
#define DAT_00027aa4 ((unsigned long)&rodata_a01ea) /*=0xa01ea*/
#define DAT_00027aa8 ((volatile int*)((unsigned long)&g_last_standby_event_id) /*=0x2000302d*/)
#define DAT_00027aac ((unsigned long)&rodata_a020e) /*=0xa020e*/
#define DAT_00027ab0 ((unsigned long)&rodata_a0231) /*=0xa0231*/
#define DAT_00027ab4 ((unsigned long)&rodata_a024a) /*=0xa024a*/
#define DAT_00027ab8 ((volatile int*)((unsigned long)&g_last_reported_box_charge_pct) /*=0x20003029*/)
#define DAT_00027abc ((volatile int*)((unsigned long)&g_last_reported_box_charge_status) /*=0x20003028*/)
#define DAT_00027ac0 ((volatile int*)((unsigned long)&g_glassbox_status_debounce_cnt) /*=0x20018d85*/)
#define DAT_00027ac4 ((volatile int*)((unsigned long)&g_box_state_debounce_cnt) /*=0x20018d84*/)
#define DAT_00027ac8 ((volatile int*)((unsigned long)&g_charge_notify_state_init_flag) /*=0x2000302a*/)
#define DAT_00027cc0 ((volatile int*)((unsigned long)&g_last_reported_battery_pct) /*=0x20003027*/)
#define DAT_00027cc4 ((volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)
#define DAT_00027cc8 ((unsigned long)&rodata_a1b00) /*=0xa1b00*/
#define DAT_00027ccc ((unsigned long)&rodata_a0266) /*=0xa0266*/
#define DAT_00027cd0 ((volatile int*)((unsigned long)&g_box_state_debounce_cnt) /*=0x20018d84*/)
#define DAT_00027cd4 ((volatile int*)((unsigned long)&g_glassbox_lid_debounced_state) /*=0x20003026*/)
#define DAT_00027cd8 ((volatile int*)((unsigned long)&g_last_reported_box_charge_status) /*=0x20003028*/)
#define DAT_00027cdc ((volatile int*)((unsigned long)&g_glassbox_status_debounce_cnt) /*=0x20018d85*/)
#define DAT_00027ce0 ((volatile int*)((unsigned long)&g_last_reported_box_charge_pct) /*=0x20003029*/)
#define DAT_00027ce4 ((unsigned long)&rodata_a030d) /*=0xa030d*/
#define DAT_00027ce8 ((volatile int*)((unsigned long)&g_check_work_mode_ed5_field_cache) /*=0x20003025*/)
#define DAT_00027cec ((unsigned long)&rodata_a028c) /*=0xa028c*/
#define DAT_00027cf0 ((unsigned long)&rodata_a02ab) /*=0xa02ab*/
#define _DAT_00027cf4 ((unsigned long)&rodata_a02cc) /*=0xa02cc*/
#define _DAT_00027cf8 (*(volatile int*)((unsigned long)&rodata_27cf8) /*=0x27cf8*/)
#define _event_id2 event_id2


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void check_work_mode(int param_1,int param_2,int param_3)

{
  bool bVar1;
  int *piVar2;
  byte *pbVar3;
  byte event_id2;
  uint uVar4;
  int iVar5;
  char *pcVar6;
  uint new_box_charging_status;
  byte *pbVar7;
  byte bVar8;
  byte event_id;
  undefined8 uVar9;

  uVar4 = get_current_work_mode();
  uVar4 = uVar4 & 0xff;
  if (uVar4 < 2) {
    return;
  }
  if (uVar4 == 8) {
    return;
  }
  uVar9 = k_uptime_get_1();
  if ((int)((ulonglong)uVar9 >> 0x20) < (int)(uint)((uint)uVar9 < 10000)) {
    return;
  }
  iVar5 = get_device_info();
  if ((((*(byte *)(iVar5 + 0xfc4) < 0x83) &&
       (iVar5 = get_device_info(), 0x50 < *(byte *)(iVar5 + 0xfc4))) &&
      (iVar5 = get_device_info(), '\0' < *(char *)(iVar5 + 0xfc8))) &&
     ((iVar5 = get_device_info(), *(byte *)(iVar5 + 0xfc0) < 2 && (param_1 == 0)))) {
    pcVar6 = (char *)get_device_info();
    if (*pcVar6 == '\x01') {
      _event_id2 = get_device_info();
      sync_to_slave(_event_id2,3,0,0);
    }
    else {
      _event_id2 = get_device_info();
      esb_send_command_and_wait_ack(_event_id2,5,0,0);
    }
    _event_id2 = get_device_info();
    set_shutdown_flag(_event_id2,1);
    change_work_mode_to(7);
    return;
  }
  if (*DAT_00027a6c < 0x33) {
    if (*DAT_00027a6c < 0x28) {
      *DAT_00027a90 = 0;
      get_device_info();
      iVar5 = display_panel_is_secondary();
      if (iVar5 == 0) {
        bVar8 = 3;
      }
      else {
        iVar5 = get_device_info();
        if (**(char **)(iVar5 + 0x1014) == '\0') {
          bVar8 = 0x3c;
        }
        else {
          bVar8 = 10;
        }
      }
      if ((byte)(*DAT_00027a84 + 1) < bVar8) {
        *DAT_00027a84 = *DAT_00027a84 + 1;
      }
      else {
        *DAT_00027a84 = bVar8;
        *DAT_00027a70 = 0;
        *DAT_00027a88 = 0;
        clear_app_switch_pending_flag();
        piVar2 = DAT_00027a74;
        if (param_1 == 0) {
          if (uVar4 != 4) {
            _event_id2 = get_device_info();
            set_shutdown_flag(_event_id2,1);
            change_work_mode_to(4);
            if (0 < *DAT_00027a74) {
              iVar5 = *DAT_00027a78;
              _event_id2 = DAT_00027aa0;
              goto LAB_00027964;
            }
          }
        }
        else if (param_2 == 0) {
          _event_id2 = get_device_info();
          set_shutdown_flag(_event_id2,1);
          change_work_mode_to(5);
          if (0 < *piVar2) {
            iVar5 = *DAT_00027a78;
            _event_id2 = DAT_00027a9c;
            goto LAB_00027964;
          }
        }
        else {
          _event_id2 = get_device_info();
          set_shutdown_flag(_event_id2,1);
          change_work_mode_to(6);
          if (0 < *piVar2) {
            iVar5 = *DAT_00027a78;
            _event_id2 = DAT_00027a98;
LAB_00027964:
            if (iVar5 == 0) {
              log_message(_event_id2,DAT_00027a7c);
            }
            else {
              debug_print();
            }
          }
        }
      }
    }
    bVar1 = false;
  }
  else {
    *DAT_00027a70 = 1;
    enter_wear_burial_point();
    if (uVar4 - 2 < 2) {
      get_device_info();
      iVar5 = display_panel_is_secondary();
      if ((iVar5 != 0) && (change_work_mode_to(2), 0 < *DAT_00027a74)) {
        iVar5 = *DAT_00027a78;
        _event_id2 = DAT_00027a8c;
        goto LAB_0002782c;
      }
    }
    else {
      _event_id2 = get_device_info();
      set_shutdown_flag(_event_id2,0);
      change_work_mode_to(3);
      if (0 < *DAT_00027a74) {
        iVar5 = *DAT_00027a78;
        _event_id2 = DAT_00027a80;
LAB_0002782c:
        if (iVar5 == 0) {
          log_message(_event_id2,DAT_00027a7c);
        }
        else {
          debug_print();
        }
      }
    }
    pbVar7 = DAT_00027a88;
    *DAT_00027a84 = 0;
    bVar8 = *pbVar7 + 1;
    if (bVar8 < 2) {
LAB_00027844:
      *pbVar7 = bVar8;
    }
    else {
      *pbVar7 = 2;
      bVar8 = *DAT_00027a90 + 1;
      pbVar7 = DAT_00027a90;
      if (bVar8 < 10) goto LAB_00027844;
      *DAT_00027a90 = 0;
      iVar5 = flash_get_ready_status_bit();
      if (iVar5 != 0) {
        pt_nfc_eeprom_link_start();
      }
    }
    bVar1 = true;
  }
  pbVar7 = DAT_00027ce0;
  pcVar6 = DAT_00027ac8;
  piVar2 = DAT_00027a74;
  if (param_3 == 0) {
    *DAT_00027ac8 = -1;
    *pbVar7 = 0xff;
    *DAT_00027cd8 = 0xff;
    *DAT_00027cc0 = 0xff;
    *DAT_00027cd4 = 0xff;
    *DAT_00027ce8 = -1;
    *DAT_00027cdc = 4;
    *DAT_00027cd0 = 4;
    return;
  }
  if ((*DAT_00027ac8 == -1) || (iVar5 = get_device_info(), *(int *)(iVar5 + 0x9b4) == 2)) {
    iVar5 = get_device_info();
    if (*(int *)(iVar5 + 0x9b4) == 2) {
      uVar9 = get_device_info();
      k_sem_take((int)uVar9 + 0x9ac,(int)((ulonglong)uVar9 >> 0x20),0xffffffff,0xffffffff);
    }
    if (0 < *piVar2) {
      if (*DAT_00027a78 == 0) {
        log_message(DAT_00027a94,DAT_00027a7c);
      }
      else {
        debug_print();
      }
    }
    send_event(0x11);
    *pcVar6 = -2;
    return;
  }
  iVar5 = *piVar2;
  if (param_1 == 0) {
    if (bVar1) {
      if (0 < iVar5) {
        if (*DAT_00027a78 == 0) {
          log_message(DAT_00027ab0,DAT_00027a7c);
        }
        else {
          debug_print();
        }
      }
      event_id = 0x6;
    }
    else {
      if (0 < iVar5) {
        if (*DAT_00027a78 == 0) {
          log_message(DAT_00027ab4,DAT_00027a7c);
        }
        else {
          debug_print();
        }
      }
      event_id = 0x7;
    }
    *DAT_00027ab8 = 0xff;
    *DAT_00027abc = 0xff;
    *DAT_00027ac0 = 4;
    *DAT_00027ac4 = 4;
  }
  else if (param_2 == 0) {
    if (0 < iVar5) {
      if (*DAT_00027a78 == 0) {
        log_message(DAT_00027aac,DAT_00027a7c);
      }
      else {
        debug_print();
      }
    }
    event_id = 0x8;
  }
  else {
    if (0 < iVar5) {
      if (*DAT_00027a78 == 0) {
        log_message(DAT_00027aa4,DAT_00027a7c);
      }
      else {
        debug_print();
      }
    }
    event_id = 0xb;
  }
  pbVar7 = DAT_00027aa8;
  if (*DAT_00027aa8 != event_id) {
    send_event(event_id);
    *pbVar7 = event_id;
    return;
  }
  iVar5 = get_device_info();
  pbVar3 = DAT_00027cd4;
  pbVar7 = DAT_00027cd0;
  bVar8 = *(byte *)(iVar5 + 0xfc0);
  if ((*DAT_00027cc0 != bVar8) && (bVar8 < 0x65)) {
    *DAT_00027cc0 = bVar8;
    if (0 < *piVar2) {
      if (*DAT_00027cc4 == 0) {
        log_message(DAT_00027ccc,DAT_00027cc8);
      }
      else {
        debug_print();
      }
    }
    _event_id2 = 0xa;
    goto LAB_00027af8;
  }
  if (param_1 == 0) {
    if (*DAT_00027cd4 != 0) {
LAB_00027b70:
      uVar4 = 0;
LAB_00027b72:
      if ((byte)(*pbVar7 + 1) < 5) {
        *pbVar7 = *pbVar7 + 1;
        return;
      }
      *pbVar7 = 0;
      iVar5 = get_device_info();
      *(byte *)(iVar5 + 0x794) = (byte)uVar4;
      *pbVar3 = (byte)uVar4;
      send_event(9);
      if (*piVar2 < 1) {
        return;
      }
      if (*DAT_00027cc4 == 0) {
        log_message(DAT_00027cec,DAT_00027cc8,uVar4);
        return;
      }
      debug_print();
      return;
    }
    *DAT_00027cd0 = 0;
  }
  else {
    uVar4 = debounce_read_pending_flag_2();
    if (uVar4 == 0) {
      if (*pbVar3 != 0) goto LAB_00027b70;
    }
    else {
      *pbVar7 = 4;
      if (*pbVar3 != uVar4) goto LAB_00027b72;
    }
    *pbVar7 = 0;
    new_box_charging_status = get_glassbox_charge_status();
    pbVar3 = DAT_00027cdc;
    pbVar7 = DAT_00027cd8;
    if (*DAT_00027cd8 != new_box_charging_status) {
      bVar8 = *DAT_00027cdc;
      *DAT_00027cdc = bVar8 + 1;
      if (4 < (byte)(bVar8 + 1)) {
        iVar5 = *piVar2;
        *pbVar3 = 0;
        *pbVar7 = (byte)new_box_charging_status;
        if (0 < iVar5) {
          if (*DAT_00027cc4 == 0) {
            log_message(DAT_00027cf0,DAT_00027cc8,new_box_charging_status);
          }
          else {
            debug_print();
          }
        }
        send_event(0xe);
      }
      if (*piVar2 < 1) {
        return;
      }
      uVar4 = (uint)*pbVar7;
      if (*DAT_00027cc4 == 0) {
        log_message(_DAT_00027cf4,DAT_00027cc8,uVar4,new_box_charging_status);
        return;
      }
      ((log4_fn)debug_print)(_DAT_00027cf4,DAT_00027cc8,uVar4,new_box_charging_status);
      return;
    }
    *DAT_00027cdc = 0;
    uVar4 = get_glassbox_charge_percent();
    if ((*DAT_00027ce0 != uVar4) && (uVar4 < 0x65)) {
      iVar5 = *piVar2;
      *DAT_00027ce0 = (byte)uVar4;
      if (0 < iVar5) {
        if (*DAT_00027cc4 == 0) {
          log_message(DAT_00027ce4,DAT_00027cc8,uVar4,uVar4);
        }
        else {
          ((log3_fn)debug_print)(DAT_00027ce4,DAT_00027cc8,uVar4);
        }
      }
      _event_id2 = 0xf;
      goto LAB_00027af8;
    }
    if (0 < *piVar2) {
      if (*DAT_00027cc4 == 0) {
        log_message(_DAT_00027cf8,DAT_00027cc8,(uint)*DAT_00027ce0,uVar4);
      }
      else {
        ((log2_fn)debug_print)(_DAT_00027cf8,DAT_00027cc8);
      }
    }
  }
  pcVar6 = (char *)get_device_info();
  if ((*pcVar6 == '\x01') && (iVar5 = get_device_info(), *(int *)(iVar5 + 0xf90) != 0)) {
    iVar5 = get_device_info();
    iVar5 = compute_lux_brightness_bucket(iVar5 + 0xf80);
    if ((iVar5 != 0xff) &&
       (iVar5 = get_device_info(), pcVar6 = DAT_00027ce8, *(char *)(iVar5 + 0xed5) != *DAT_00027ce8)) {
      iVar5 = get_device_info();
      _event_id2 = 0x12;
      *pcVar6 = *(char *)(iVar5 + 0xed5);
LAB_00027af8:
      send_event(_event_id2);
      return;
    }
  }
  return;
}
