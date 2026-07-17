#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0002af4c @ 0x0002af4c
 * public-name: master_process_audio_fw_load_req
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   imu_set_enabled                          <= FUN_0002bd4c @ 0x0002bd4c
 *   get_low_battery_flag_if_master           <= FUN_0002efa8 @ 0x0002efa8
 *   get_notification_counts_cmd_response     <= FUN_00033a5c @ 0x00033a5c
 *   post_notification_cmd_response           <= FUN_000340c4 @ 0x000340c4
 *   debug_print_hex_dump                     <= FUN_0004a424 @ 0x0004a424
 *   rate_limited_elapsed_seconds_tick        <= FUN_0004a46c @ 0x0004a46c
 *   get_boot_seconds                         <= FUN_0004a51c @ 0x0004a51c
 *   uint32_to_little_endian                  <= FUN_0004a568 @ 0x0004a568
 *   is_system_idle_ready                     <= FUN_0007ce00 @ 0x0007ce00
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_9b708                             @ 0x0009b708
 *   rodata_9b74b                             @ 0x0009b74b
 *   rodata_a1ca4                             @ 0x000a1ca4
 *   rodata_a1ce0                             @ 0x000a1ce0
 *   rodata_a1cfc                             @ 0x000a1cfc
 *   rodata_a1d06                             @ 0x000a1d06
 *   rodata_a1d31                             @ 0x000a1d31
 *   rodata_a1d59                             @ 0x000a1d59
 *   rodata_a1dbe                             @ 0x000a1dbe
 *   rodata_a1df5                             @ 0x000a1df5
 *   rodata_a1e3a                             @ 0x000a1e3a
 *   rodata_a1e66                             @ 0x000a1e66
 *   rodata_a1ead                             @ 0x000a1ead
 *   rodata_a1edb                             @ 0x000a1edb
 *   rodata_a1f1a                             @ 0x000a1f1a
 *   rodata_a1f24                             @ 0x000a1f24
 *   rodata_a1f35                             @ 0x000a1f35
 *   rodata_a1f49                             @ 0x000a1f49
 *   rodata_a1f4e                             @ 0x000a1f4e
 *   rodata_a1f7d                             @ 0x000a1f7d
 *   rodata_a1fc7                             @ 0x000a1fc7
 *   rodata_a1ff2                             @ 0x000a1ff2
 *   rodata_a201b                             @ 0x000a201b
 *   rodata_a2041                             @ 0x000a2041
 *   rodata_a2061                             @ 0x000a2061
 *   rodata_a20c2                             @ 0x000a20c2
 *   rodata_a20e9                             @ 0x000a20e9
 *   rodata_a211e                             @ 0x000a211e
 *   rodata_a2184                             @ 0x000a2184
 *   rodata_a21c4                             @ 0x000a21c4
 *   rodata_a21f9                             @ 0x000a21f9
 *   rodata_a2227                             @ 0x000a2227
 *   rodata_a22b8                             @ 0x000a22b8
 *   rodata_a2334                             @ 0x000a2334
 *   rodata_a2364                             @ 0x000a2364
 *   rodata_a2383                             @ 0x000a2383
 *   rodata_a23a0                             @ 0x000a23a0
 *   rodata_a23cd                             @ 0x000a23cd
 *   rodata_a23d0                             @ 0x000a23d0
 *   rodata_a23e8                             @ 0x000a23e8
 *   rodata_a23ff                             @ 0x000a23ff
 *   rodata_a2416                             @ 0x000a2416
 *   rodata_a243a                             @ 0x000a243a
 *   rodata_a245b                             @ 0x000a245b
 *   rodata_a7cd6                             @ 0x000a7cd6
 *   rodata_a7cf4                             @ 0x000a7cf4
 *   rodata_a829f                             @ 0x000a829f
 *   rodata_f680e                             @ 0x000f680e
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed master_process_audio_fw_load_req @ 0x2af4c  (parity: 750/750 trials, PROVEN) */
typedef unsigned char byte;
typedef unsigned char undefined1;
typedef unsigned short undefined2;
typedef unsigned int undefined4;
typedef unsigned int uint;
typedef void code;

extern int log_message(const char*, const char*, ...);
extern int debug_print(const char*, const char*, ...);
extern int get_device_info(void);
extern int FUN_00019ac0(uint);
extern int FUN_000232b0(void);
extern int FUN_000232b8(void);
extern int FUN_000269fc(void);
extern int imu_set_enabled(int, char*, uint);
extern int get_low_battery_flag_if_master(void);
extern int post_notification_cmd_response(char*, byte*, char*, byte*, byte*, byte*, undefined4);
extern int debug_print_hex_dump(int, byte*, int);
extern int rate_limited_elapsed_seconds_tick(int, int, int);
extern int get_boot_seconds(void);
extern int uint32_to_little_endian(byte*, int);
extern int FUN_0007c0e2(uint);
extern int is_system_idle_ready(void);
extern int FUN_0007d2f8(int);
extern int FUN_0007d968(byte*, int, byte*);
extern int memcpy(int, byte*, int);
extern int memset_bytes(void*, int, int);
extern int process_sync_buffer(void*);
extern int update_persist_task_status(char*, int, int);
extern int get_notification_counts_cmd_response(char*, byte*);

#define DAT_0002b208 ((volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)
#define DAT_0002b20c ((const char*)((unsigned long)&rodata_a243a) /*=0xa243a*/)
#define DAT_0002b210 ((const char*)((unsigned long)&rodata_a1ca4) /*=0xa1ca4*/)
#define DAT_0002b214 ((const char*)((unsigned long)&rodata_a2416) /*=0xa2416*/)
#define DAT_0002b218 ((const char*)((unsigned long)&rodata_a1ce0) /*=0xa1ce0*/)
#define DAT_0002b21c ((unsigned long)&rodata_a1cfc) /*=0xa1cfc*/
#define DAT_0002b220 ((int*)((unsigned long)&g_log_level) /*=0x2000230c*/)
#define DAT_0002b224 ((const char*)((unsigned long)&rodata_a23ff) /*=0xa23ff*/)
#define DAT_0002b228 ((const char*)((unsigned long)&rodata_a1d06) /*=0xa1d06*/)
#define DAT_0002b22c ((const char*)((unsigned long)&rodata_a1d31) /*=0xa1d31*/)
#define DAT_0002b230 ((const char*)((unsigned long)&rodata_a1d59) /*=0xa1d59*/)
#define DAT_0002b234 ((const char*)0x000a1d8d)
#define DAT_0002b238 ((const char*)((unsigned long)&rodata_a1dbe) /*=0xa1dbe*/)
#define DAT_0002b4d4 ((volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)
#define DAT_0002b4d8 ((const char*)((unsigned long)&rodata_a23ff) /*=0xa23ff*/)
#define DAT_0002b4dc ((const char*)((unsigned long)&rodata_a1df5) /*=0xa1df5*/)
#define DAT_0002b4e0 ((const char*)((unsigned long)&rodata_a1e66) /*=0xa1e66*/)
#define DAT_0002b4e4 ((const char*)((unsigned long)&rodata_a1e3a) /*=0xa1e3a*/)
#define DAT_0002b4e8 ((const char*)((unsigned long)&rodata_a1ead) /*=0xa1ead*/)
#define DAT_0002b4ec ((int*)((unsigned long)&g_log_level) /*=0x2000230c*/)
#define DAT_0002b4f0 ((const char*)((unsigned long)&rodata_a1edb) /*=0xa1edb*/)
#define DAT_0002b4f4 ((unsigned long)&rodata_a1f1a) /*=0xa1f1a*/
#define DAT_0002b4f8 ((unsigned long)&rodata_a1f49) /*=0xa1f49*/
#define DAT_0002b4fc ((const char*)((unsigned long)&rodata_a1f24) /*=0xa1f24*/)
#define DAT_0002b500 ((const char*)((unsigned long)&rodata_a1f35) /*=0xa1f35*/)
#define DAT_0002b504 ((const char*)((unsigned long)&rodata_a1f4e) /*=0xa1f4e*/)
#define DAT_0002b508 ((const char*)((unsigned long)&rodata_a1f7d) /*=0xa1f7d*/)
#define DAT_0002b50c ((const char*)((unsigned long)&rodata_a1fc7) /*=0xa1fc7*/)
#define DAT_0002b510 ((const char*)((unsigned long)&rodata_a1ff2) /*=0xa1ff2*/)
#define DAT_0002b7a8 ((int*)((unsigned long)&g_log_level) /*=0x2000230c*/)
#define DAT_0002b7ac ((volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)
#define DAT_0002b7b0 ((const char*)((unsigned long)&rodata_a23ff) /*=0xa23ff*/)
#define DAT_0002b7b4 ((const char*)((unsigned long)&rodata_a201b) /*=0xa201b*/)
#define DAT_0002b7b8 ((const char*)((unsigned long)&rodata_a2041) /*=0xa2041*/)
#define DAT_0002b7bc ((const char*)((unsigned long)&rodata_a2061) /*=0xa2061*/)
#define DAT_0002b7c0 ((const char*)0x000a2098)
#define DAT_0002b7c4 ((const char*)((unsigned long)&rodata_a20c2) /*=0xa20c2*/)
#define DAT_0002b7c8 ((const char*)((unsigned long)&rodata_a20e9) /*=0xa20e9*/)
#define DAT_0002b7cc ((const char*)((unsigned long)&rodata_a211e) /*=0xa211e*/)
#define DAT_0002b7d0 ((const char*)((unsigned long)&rodata_a23e8) /*=0xa23e8*/)
#define DAT_0002b7d4 ((const char*)((unsigned long)&rodata_a2184) /*=0xa2184*/)
#define DAT_0002b7d8 ((const char*)((unsigned long)&rodata_a21c4) /*=0xa21c4*/)
#define DAT_0002b7dc ((const char*)((unsigned long)&rodata_a21f9) /*=0xa21f9*/)
#define DAT_0002baa0 ((unsigned long)&rodata_a23cd) /*=0xa23cd*/
#define DAT_0002baa4 ((int*)((unsigned long)&g_log_level) /*=0x2000230c*/)
#define DAT_0002baa8 ((const char*)((unsigned long)&rodata_a23e8) /*=0xa23e8*/)
#define DAT_0002baac ((const char*)((unsigned long)&rodata_a2227) /*=0xa2227*/)
#define DAT_0002bab0 ((const char*)((unsigned long)&rodata_a22b8) /*=0xa22b8*/)
#define DAT_0002bab4 ((volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)
#define DAT_0002bab8 ((const char*)((unsigned long)&rodata_a2334) /*=0xa2334*/)
#define DAT_0002babc ((const char*)((unsigned long)&rodata_9b708) /*=0x9b708*/)
#define DAT_0002bac0 ((const char*)0x0009b729)
#define DAT_0002bac4 ((const char*)((unsigned long)&rodata_9b74b) /*=0x9b74b*/)
#define DAT_0002bc0c ((int*)((unsigned long)&g_log_level) /*=0x2000230c*/)
#define DAT_0002bc10 ((volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)
#define DAT_0002bc14 ((const char*)((unsigned long)&rodata_a23d0) /*=0xa23d0*/)
#define DAT_0002bc18 ((const char*)((unsigned long)&rodata_a2364) /*=0xa2364*/)
#define DAT_0002bc1c ((const char*)((unsigned long)&rodata_a2383) /*=0xa2383*/)
#define DAT_0002bc20 ((const char*)((unsigned long)&rodata_a245b) /*=0xa245b*/)
#define DAT_0002bc24 ((const char*)((unsigned long)&rodata_a23a0) /*=0xa23a0*/)
#define DAT_0002bc28 ((unsigned long)&rodata_f680e) /*=0xf680e*/
#define DAT_00033aa8 ((int*)((unsigned long)&g_log_level) /*=0x2000230c*/)
#define DAT_00033aac ((volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)
#define DAT_00033ab0 ((const char*)((unsigned long)&rodata_a829f) /*=0xa829f*/)
#define DAT_00033ab4 ((const char*)((unsigned long)&rodata_a7cd6) /*=0xa7cd6*/)
#define DAT_00033ab8 ((const char*)((unsigned long)&rodata_a7cf4) /*=0xa7cf4*/)

int master_process_audio_fw_load_req(char *param_1, byte *param_2, byte *param_3, undefined4 param_4)
{
  byte bVar1;
  undefined2 uVar2;
  byte bVar3;
  int *piVar4;
  uint *puVar5;
  int *piVar6;
  int *piVar7;
  int *piVar8;
  int *piVar9;
  undefined1 uVar10;
  int iVar11;
  undefined4 uVar12;
  int iVar13;
  char *pcVar14;
  byte *pbVar15;
  undefined4 *puVar16;
  undefined4 *puVar17;
  undefined4 *puVar18;
  char *pcVar19;
  uint uVar20;
  byte bVar21;
  code *pcVar22;
  byte *pbVar23;
  int iVar24;
  uint uVar25;
  int iVar26;
  uint uVar27;
  undefined4 uVar28;
  undefined1 local_124;
  undefined4 local_123;
  undefined4 local_11f;
  undefined2 local_11b;
  char local_119;
  undefined1 auStack_118 [244];

  piVar9 = DAT_00033aa8;
  piVar8 = DAT_0002bc0c;
  piVar7 = DAT_0002baa4;
  piVar6 = DAT_0002b7a8;
  puVar5 = (uint*)DAT_0002b4ec;
  piVar4 = DAT_0002b220;
  pbVar23 = param_2 + 4;
  if (param_2[1] == 3) {
    uVar28 = *(undefined4 *)(param_2 + 8);
    iVar24 = *(int *)(param_2 + 0xc);
    if (2 < *DAT_0002b220) {
      if (*DAT_0002b208 == 0) {
        log_message(DAT_0002b210,DAT_0002b20c,*(undefined4 *)(param_2 + 4),uVar28,iVar24);
      }
      else {
        debug_print(DAT_0002b210,DAT_0002b20c,*(undefined4 *)(param_2 + 4),uVar28,iVar24);
      }
    }
    if (iVar24 - 0x13U < 0x800d) {
      iVar11 = get_device_info();
      if (*(int *)(iVar11 + 0x1030) != 0) {
        iVar11 = get_device_info();
        iVar26 = iVar24 + -0x12;
        pcVar22 = *(code **)(iVar11 + 0x1030);
        uVar12 = get_device_info();
        iVar13 = (*(int(*)(int,undefined4,byte*,int))pcVar22)(uVar12,uVar28,param_3 + 0x12,iVar26);
        iVar11 = iVar26;
        if ((iVar13 != 0) && (iVar11 = iVar13, 0 < *piVar4)) {
          if (*DAT_0002b208 == 0) {
            log_message(DAT_0002b218,DAT_0002b214,iVar13);
          }
          else {
            debug_print(DAT_0002b218,DAT_0002b214,iVar13);
          }
        }
        if (iVar26 == iVar11) {
          *param_3 = 0x6f;
          param_3[1] = 0x6b;
          FUN_0007d968(param_3 + 0x12,iVar26,param_3 + 2);
          debug_print_hex_dump(DAT_0002b21c,param_3 + 2,0x10);
          return iVar24;
        }
      }
    }
    *param_3 = 0x6e;
    param_3[1] = 0x6f;
    return 0;
  }
  uVar20 = (uint)*param_2;
  if (0x26 < (uVar20 - 1 & 0xff)) {
    if (0x1c < (uVar20 - 0x29 & 0xff)) {
      if (9 < uVar20 - 0x47) {
        if (0 < *DAT_0002bc0c) {
          if (*DAT_0002bc10 == 0) {
            log_message(DAT_0002bc24,DAT_0002bc20);
          }
          else {
            debug_print(DAT_0002bc24,DAT_0002bc20);
          }
        }
        uVar2 = *(undefined2 *)(DAT_0002bc28 + 1);
        *(undefined4 *)param_3 = *(undefined4*)DAT_0002bc28;
        *(undefined2 *)(param_3 + 4) = uVar2;
        return 6;
      }
      switch(uVar20) {
      case 0x4a:
        uVar20 = (uint)param_2[4];
        if (2 < *DAT_0002bc0c) {
          if (*DAT_0002bc10 == 0) {
            log_message(DAT_0002bc18,DAT_0002bc14,uVar20);
          }
          else {
            debug_print(DAT_0002bc18,DAT_0002bc14,uVar20);
          }
        }
        if ((int)(uVar20 << 0x1e) < 0) {
          param_1[0xc9] = -0x7d;
          param_1[0xca] = '\x01';
          memset_bytes((char*)&local_123 + 3,0,0xf8);
          local_124 = 2;
          local_123 = *(undefined4 *)(param_1 + 0xc9);
          local_11f = *(undefined4 *)(param_1 + 0xcd);
          local_11b = *(undefined2 *)(param_1 + 0xd1);
          local_119 = param_1[0xd3];
          memset_bytes(auStack_118,0,0x15);
          (*(void(**)(void*,int))(param_1 + 0x774))(&local_124,0xfc);
        }
        if ((int)(uVar20 << 0x1f) < 0) {
          if (2 < *piVar8) {
            if (*DAT_0002bc10 == 0) {
              log_message(DAT_0002bc1c,DAT_0002bc14);
            }
            else {
              debug_print(DAT_0002bc1c,DAT_0002bc14);
            }
          }
          (*(void(**)(void*))(param_1 + 0x102c))(param_1 + 0x68);
        }
        break;
      case 0x4b:
        iVar24 = post_notification_cmd_response(param_1,param_2,param_1 + 0xd4,param_2,pbVar23,param_3,param_4);
        return iVar24;
      case 0x4c:
        uVar20 = *(uint *)(param_2 + 4);
        FUN_0007c0e2(uVar20 << 0x18 | (uVar20 >> 8 & 0xff) << 0x10 | (uVar20 >> 0x10 & 0xff) << 8 |
                     uVar20 >> 0x18);
        break;
      case 0x4d:
        iVar24 = get_device_info();
        param_1 = (char *)(iVar24 + 0x9ac);
        goto LAB_0002b188;
      case 0x4e:
        *(undefined1 *)(*(int *)(param_1 + 0x100c) + 0x196) = 0;
        if (*(char *)(*(int *)(param_1 + 0x100c) + 7) == '\0') {
          *(undefined1 *)(*(int *)(param_1 + 0x100c) + 7) = 10;
        }
        *param_3 = 0xc9;
        if (**(int **)(param_1 + 0x1054) == 0x10) {
          return 1;
        }
        uVar28 = 0x10;
        goto LAB_0002b404;
      case 0x4f:
        iVar24 = get_device_info();
        *(byte *)(iVar24 + 0x108f) = param_2[4];
        bVar21 = *param_2;
        iVar24 = get_device_info();
        *(uint *)(iVar24 + 0x104c) = (uint)bVar21;
        iVar24 = get_device_info();
        process_sync_buffer((void*)(iVar24 + 0x80));
        *param_3 = 0xc9;
        param_3[1] = param_2[4];
        return 2;
      default:
        goto switchD_0002b03a_caseD_3;
      }
      goto LAB_0002b1ac;
    }
    switch(uVar20 - 0x29) {
    case 0:
      *param_3 = param_1[0xed5];
      param_3[1] = param_1[0xf98];
      if (*piVar6 < 3) {
        return 2;
      }
      iVar24 = *DAT_0002b7ac;
      uVar28 = (undefined4)DAT_0002b7d0;
      uVar12 = (undefined4)DAT_0002b7dc;
      break;
    case 1:
      bVar21 = param_1[0xf60];
      *param_3 = bVar21;
      if (*piVar6 < 3) {
        return 1;
      }
      if (*DAT_0002b7ac != 0) {
        debug_print(DAT_0002b7d8,DAT_0002b7d0);
        return 1;
      }
      log_message(DAT_0002b7d8,DAT_0002b7d0,(uint)bVar21,(uint)param_3[1]);
      return 1;
    case 2:
      *param_3 = param_1[0xfea];
      uVar28 = FUN_000269fc();
      piVar4 = DAT_0002b7a8;
      param_3[1] = (byte)uVar28;
      if (*piVar4 < 3) {
        return 2;
      }
      if (*DAT_0002b7ac != 0) {
        debug_print(DAT_0002b7d4,DAT_0002b7d0,(uint)*param_3,uVar28,(uint)param_3[2],(uint)param_3[3]);
        return 2;
      }
      log_message(DAT_0002b7d4,DAT_0002b7d0,(uint)*param_3,uVar28,(uint)param_3[2],(uint)param_3[3]);
      return 2;
    case 3:
      uVar20 = (uint)(byte)param_1[0xfc0];
      uVar25 = (uint)(byte)param_1[0xfc1];
      if (uVar20 == 0x5d) {
        if (param_1[0xfc2] == '\0') {
          if (uVar25 == 0x5d) {
            uVar20 = 0x5e;
            uVar25 = uVar20;
            goto LAB_0002b7fe;
          }
          uVar20 = 0x5e;
          uVar27 = uVar25 - 0x5e & 0xff;
        }
        else {
          if (uVar25 == 0x5d) {
            uVar20 = 0x5f;
            goto LAB_0002b8ee;
          }
          uVar20 = 0x5f;
          uVar27 = uVar25 - 0x5e & 0xff;
        }
      }
      else if (uVar20 == 0x5e) {
        if (param_1[0xfc2] == '\0') {
          if (uVar25 == 0x5d) {
            uVar20 = 0x60;
            uVar25 = 0x5e;
            goto LAB_0002b7fe;
          }
          uVar20 = 0x60;
          uVar27 = uVar25 - 0x5e & 0xff;
        }
        else {
          if (uVar25 == 0x5d) {
            uVar20 = 0x61;
            uVar25 = 0x5e;
            goto LAB_0002b7fe;
          }
          uVar20 = 0x61;
          uVar27 = uVar25 - 0x5e & 0xff;
        }
      }
      else if (uVar20 == 0x5f) {
        if (uVar25 == 0x5d) {
          uVar20 = 0x62;
          goto LAB_0002b8ee;
        }
        uVar20 = 0x62;
        uVar27 = uVar25 - 0x5e & 0xff;
      }
      else if (uVar20 == 0x60) {
        if (uVar25 == 0x5d) {
          uVar20 = 99;
          goto LAB_0002b8ee;
        }
        uVar20 = 99;
        uVar27 = uVar25 - 0x5e & 0xff;
      }
      else if (uVar20 < 0x61) {
        if (uVar25 == 0x5d) goto LAB_0002b8ee;
        uVar27 = uVar25 - 0x5e & 0xff;
      }
      else {
        if (uVar25 == 0x5d) {
          uVar20 = 100;
LAB_0002b8ee:
          uVar25 = 0x5e;
          goto LAB_0002b7fe;
        }
        uVar27 = uVar25 - 0x5e & 0xff;
        uVar20 = 100;
        uVar25 = 100;
      }
      if (uVar27 < 3) {
        uVar25 = (int)*(char *)(DAT_0002baa0 + uVar27);
      }
LAB_0002b7fe:
      *param_3 = (byte)uVar20;
      param_3[1] = (byte)uVar25;
      bVar21 = param_1[0xfc4];
      param_3[2] = bVar21;
      bVar1 = param_1[0xfc5];
      param_3[3] = bVar1;
      bVar3 = param_1[0xfc6];
      param_3[4] = bVar3;
      pbVar23 = param_3 + 5;
      pcVar14 = param_1 + 0xfcc;
      do {
        pcVar19 = pcVar14 + 4;
        pbVar15 = pbVar23 + 4;
        *(undefined4 *)pbVar23 = *(undefined4 *)pcVar14;
        pbVar23 = pbVar15;
        pcVar14 = pcVar19;
      } while (pcVar19 != param_1 + 0xfd8);
      *(undefined2 *)pbVar15 = *(undefined2 *)pcVar19;
      if (2 < *DAT_0002baa4) {
        if (*DAT_0002bab4 == 0) {
          log_message(DAT_0002baac,DAT_0002baa8,uVar20,uVar25,(uint)bVar21,(uint)bVar1,(uint)bVar3,
                      (uint)param_3[5],(uint)param_3[6],(uint)param_3[7],(uint)param_3[8],
                      (uint)param_3[9],(uint)param_3[10],(uint)param_3[0xb],(uint)param_3[0xc],
                      (uint)param_3[0xd],(uint)param_3[0xe],(uint)param_3[0xf]);
        }
        else {
          debug_print(DAT_0002baac,DAT_0002baa8,uVar20,uVar25,(uint)bVar21,(uint)bVar1,(uint)bVar3,
                      (uint)param_3[5],(uint)param_3[6],(uint)param_3[7],(uint)param_3[8],
                      (uint)param_3[9],(uint)param_3[10],(uint)param_3[0xb],(uint)param_3[0xc],
                      (uint)param_3[0xd],(uint)param_3[0xe],(uint)param_3[0xf]);
        }
      }
      return 0x13;
    case 4:
      *(undefined4 *)param_3 = *(undefined4 *)(param_1 + 0xfda);
      *(undefined2 *)(param_3 + 4) = *(undefined2 *)(param_1 + 0xfde);
      *(undefined4 *)(param_3 + 6) = *(undefined4 *)(param_1 + 0xfe0);
      *(undefined2 *)(param_3 + 10) = *(undefined2 *)(param_1 + 0xfe4);
      if (2 < *DAT_0002baa4) {
        if (*DAT_0002bab4 == 0) {
          log_message(DAT_0002bab0,DAT_0002baa8,(uint)*param_3,(uint)param_3[1],(uint)param_3[2],
                      (uint)param_3[3],(uint)param_3[4],(uint)param_3[5],(uint)param_3[6],
                      (uint)param_3[7],(uint)param_3[8],(uint)param_3[9],(uint)param_3[10],
                      (uint)param_3[0xb]);
        }
        else {
          debug_print(DAT_0002bab0,DAT_0002baa8,(uint)*param_3,(uint)param_3[1],(uint)param_3[2],
                      (uint)param_3[3],(uint)param_3[4],(uint)param_3[5],(uint)param_3[6],
                      (uint)param_3[7],(uint)param_3[8],(uint)param_3[9],(uint)param_3[10],
                      (uint)param_3[0xb]);
        }
      }
      return 0xc;
    default:
      goto switchD_0002b03a_caseD_3;
    case 9:
      *param_3 = param_1[0xef4];
      param_3[1] = param_1[0xef5];
      if (*piVar7 < 3) {
        return 2;
      }
      iVar24 = *DAT_0002bab4;
      uVar28 = (undefined4)DAT_0002baa8;
      uVar12 = (undefined4)DAT_0002bab8;
      break;
    case 10:
      puVar16 = (undefined4 *)FUN_000232b8();
      puVar18 = puVar16;
      pbVar23 = param_3;
      do {
        puVar17 = puVar18 + 1;
        *(undefined4 *)pbVar23 = *puVar18;
        puVar18 = puVar17;
        pbVar23 = pbVar23 + 4;
      } while (puVar17 != puVar16 + 4);
      if (*DAT_0002baa4 < 3) {
        return 0x10;
      }
      iVar24 = *DAT_0002bab4;
      uVar28 = (undefined4)DAT_0002bac0;
      goto LAB_0002b9d8;
    case 0xb:
      puVar16 = (undefined4 *)FUN_000232b0();
      puVar18 = puVar16;
      pbVar23 = param_3;
      do {
        puVar17 = puVar18 + 1;
        *(undefined4 *)pbVar23 = *puVar18;
        puVar18 = puVar17;
        pbVar23 = pbVar23 + 4;
      } while (puVar17 != puVar16 + 4);
      if (*DAT_0002baa4 < 3) {
        return 0x10;
      }
      iVar24 = *DAT_0002bab4;
      uVar28 = (undefined4)DAT_0002babc;
LAB_0002b9d8:
      if (iVar24 == 0) {
        log_message((const char*)uVar28,DAT_0002baa8,param_3);
      }
      else {
        debug_print((const char*)uVar28,DAT_0002baa8,param_3);
      }
      return 0x10;
    case 0xc:
      *param_3 = param_1[2];
      if (*piVar7 < 3) {
        return 1;
      }
      if (*DAT_0002bab4 != 0) {
        debug_print(DAT_0002bac4,DAT_0002baa8);
        return 1;
      }
      log_message(DAT_0002bac4,DAT_0002baa8);
      return 1;
    case 0xd:
      return get_notification_counts_cmd_response(param_1, param_3);
    case 0xe:
      uVar28 = get_boot_seconds();
      uint32_to_little_endian(param_3,uVar28);
      if (param_1[0xae3] == '\0') {
        iVar24 = *(int *)(param_1 + 0x9b4);
        if (iVar24 != 0) {
          iVar24 = 1;
        }
        bVar21 = (byte)iVar24;
      }
      else {
        bVar21 = 0;
      }
      goto LAB_0002b31a;
    }
    if (iVar24 == 0) {
      log_message((const char*)uVar28,(const char*)uVar12,uVar20);
    }
    else {
      debug_print((const char*)uVar28,(const char*)uVar12,uVar20);
    }
    return 2;
  }
  switch(uVar20 - 1) {
  case 0:
    uVar20 = (uint)param_2[4];
    if (((byte)param_1[0xed5] == uVar20) && (param_1[0xf98] == param_2[5])) {
      if (2 < *DAT_0002b220) {
        if (*DAT_0002b208 == 0) {
          log_message(DAT_0002b22c,DAT_0002b224);
        }
        else {
          debug_print(DAT_0002b22c,DAT_0002b224);
        }
      }
    }
    else {
      if (2 < *DAT_0002b220) {
        if (*DAT_0002b208 == 0) {
          log_message(DAT_0002b228,DAT_0002b224,uVar20);
        }
        else {
          debug_print(DAT_0002b228,DAT_0002b224,uVar20);
        }
      }
      (*(void(**)(void*,uint))(param_1 + 0xb8c))(param_1 + 0xb6c,uVar20);
      param_1[0xf98] = param_2[5];
      *(uint *)(param_1 + 0x104c) = (uint)*param_2;
      process_sync_buffer(param_1 + 0x80);
    }
    *param_3 = param_2[4];
    param_3[1] = param_2[5];
    param_3[2] = 0xc9;
    return 3;
  case 1:
    bVar21 = param_2[4];
    uVar20 = (uint)(byte)param_1[0xf60];
    if (uVar20 != bVar21) {
      if (2 < *DAT_0002b220) {
        if (*DAT_0002b208 == 0) {
          log_message(DAT_0002b230,DAT_0002b224,(uint)bVar21);
        }
        else {
          debug_print(DAT_0002b230,DAT_0002b224,(uint)bVar21);
        }
      }
      param_1[0xf60] = bVar21;
      goto LAB_0002b17c;
    }
    if (2 < *DAT_0002b220) {
      iVar24 = *DAT_0002b208;
      uVar28 = (undefined4)DAT_0002b234;
      uVar12 = (undefined4)DAT_0002b224;
LAB_0002b1a0:
      if (iVar24 == 0) {
        log_message((const char*)uVar28,(const char*)uVar12,uVar20);
      }
      else {
        debug_print((const char*)uVar28,(const char*)uVar12,uVar20);
      }
    }
    goto LAB_0002b1ac;
  case 2:
    bVar21 = param_2[4];
    uVar20 = (uint)bVar21;
    uVar25 = (uint)param_2[5];
    if (2 < *DAT_0002b220) {
      if (*DAT_0002b208 == 0) {
        log_message(DAT_0002b238,DAT_0002b224,uVar20,uVar25);
      }
      else {
        debug_print(DAT_0002b238,DAT_0002b224,uVar20,uVar25);
      }
    }
    if (2 < uVar20 - 10) {
      if (2 < *piVar4) {
        if (*DAT_0002b4d4 == 0) {
          log_message(DAT_0002b4e8,DAT_0002b4d8,uVar20);
        }
        else {
          debug_print(DAT_0002b4e8,DAT_0002b4d8,uVar20);
        }
      }
      bVar21 = 0xca;
      goto LAB_0002b2d8;
    }
    if (uVar20 != (byte)param_1[0xfea]) {
      if (*param_1 == '\x01') {
        if ((byte)param_1[0xfea] == 0xc) {
          if ((uVar20 != 0xc) && (uVar10 = 1, uVar25 != 1)) goto LAB_0002b1f2;
        }
        else if (uVar20 == 0xc) {
          uVar10 = 0;
LAB_0002b1f2:
          FUN_0007d2f8(uVar10);
        }
      }
      param_1[0xfea] = bVar21;
      *(uint *)(param_1 + 0x104c) = (uint)*param_2;
      process_sync_buffer(param_1 + 0x80);
      if (param_1[0xb0c] == '\0') {
        iVar24 = *piVar4;
        if (uVar20 == 0xb) {
          if (2 < iVar24) {
            if (*DAT_0002b4d4 == 0) {
              log_message(DAT_0002b4dc,DAT_0002b4d8);
            }
            else {
              debug_print(DAT_0002b4dc,DAT_0002b4d8);
            }
          }
          pcVar14 = param_1 + 0xaf4;
          param_1[0xfe9] = '\x03';
LAB_0002b282:
          process_sync_buffer(pcVar14);
          return 0;
        }
      }
      else {
        iVar24 = *piVar4;
        if (uVar20 == 0xc) {
          if (2 < iVar24) {
            if (*DAT_0002b4d4 == 0) {
              log_message(DAT_0002b4e0,DAT_0002b4d8);
            }
            else {
              debug_print(DAT_0002b4e0,DAT_0002b4d8);
            }
          }
          goto LAB_0002b1ac;
        }
      }
      if (2 < iVar24) {
        iVar24 = *DAT_0002b4d4;
        uVar28 = (undefined4)DAT_0002b4e4;
        uVar12 = (undefined4)DAT_0002b4d8;
        goto LAB_0002b1a0;
      }
    }
    goto LAB_0002b1ac;
  default:
    goto switchD_0002b03a_caseD_3;
  case 4:
    uVar25 = (uint)param_2[4];
    bVar21 = param_2[5];
    uVar20 = (uint)bVar21;
    if (2 < (int)*DAT_0002b4ec) {
      if (*DAT_0002b4d4 == 0) {
        log_message(DAT_0002b4f0,DAT_0002b4d8,uVar25,uVar20);
      }
      else {
        debug_print(DAT_0002b4f0,DAT_0002b4d8,uVar25,uVar20);
      }
    }
    uVar28 = (undefined4)DAT_0002b4fc;
    if (uVar25 == 1) {
      if (uVar20 != 0) {
        uVar20 = 1;
      }
      imu_set_enabled(DAT_0002b4f4,param_1,uVar20);
    }
    else if (uVar25 == 2) {
      *puVar5 = uVar20;
      log_message((const char*)uVar28,(const char*)uVar20);
    }
    else if ((uVar25 == 3) && (uVar25 = *puVar5, param_1[0xd5] = bVar21, 2 < (int)uVar25)) {
      if (*DAT_0002b4d4 == 0) {
        log_message(DAT_0002b500,DAT_0002b4d8,uVar20);
      }
      else {
        debug_print(DAT_0002b500,DAT_0002b4d8,uVar20);
      }
    }
    bVar21 = *(byte *)(DAT_0002b4f8 + 1);
    *(undefined4 *)param_3 = *(undefined4*)DAT_0002b4f8;
LAB_0002b31a:
    param_3[4] = bVar21;
    return 5;
  case 6:
    bVar21 = param_2[8];
    if (2 < (int)*DAT_0002b4ec) {
      if (*DAT_0002b4d4 == 0) {
        log_message(DAT_0002b504,DAT_0002b4d8,(uint)param_2[4],(uint)param_2[5],(uint)param_2[6],
                    (uint)param_2[7],(uint)bVar21,(uint)param_2[9]);
      }
      else {
        debug_print(DAT_0002b504,DAT_0002b4d8,(uint)param_2[4],(uint)param_2[5],(uint)param_2[6],
                    (uint)param_2[7],(uint)bVar21,(uint)param_2[9]);
      }
    }
    uVar20 = *(uint *)(param_2 + 4);
    *(byte *)(*(int *)(param_1 + 0xff0) + 5) = bVar21;
    **(uint **)(param_1 + 0xff0) = uVar20;
    *(undefined1 *)(*(int *)(param_1 + 0xff0) + 6) = 1;
    if (2 < (int)*puVar5) {
      if (*DAT_0002b4d4 == 0) {
        log_message(DAT_0002b508,DAT_0002b4d8,**(undefined4 **)(param_1 + 0xff0),uVar20 / 0xe10,
                    (uVar20 % 0xe10) / 0x3c,(uVar20 % 0xe10) % 0x3c,(uint)bVar21);
      }
      else {
        debug_print(DAT_0002b508,DAT_0002b4d8,**(undefined4 **)(param_1 + 0xff0),uVar20 / 0xe10,
                    (uVar20 % 0xe10) / 0x3c,(uVar20 % 0xe10) % 0x3c,(uint)bVar21);
      }
    }
    *(uint *)(param_1 + 0x104c) = (uint)*param_2;
    process_sync_buffer(param_1 + 0x80);
    *param_3 = 0xc9;
    if (*(char *)(*(int *)(param_1 + 0xff0) + 5) == '\0') {
      return 1;
    }
    uVar28 = 2;
    goto LAB_0002b404;
  case 7:
    if (2 < *DAT_0002b7a8) {
      if (*DAT_0002b7ac == 0) {
        log_message(DAT_0002b7b4,DAT_0002b7b0);
      }
      else {
        debug_print(DAT_0002b7b4,DAT_0002b7b0);
      }
    }
    memcpy(*(undefined4 *)(param_1 + 0xff4),pbVar23,0x16a);
    **(undefined4 **)(param_1 + 0xfec) = *(undefined4 *)(*(int *)(param_1 + 0xff4) + 0x164);
    rate_limited_elapsed_seconds_tick(*(undefined4 *)(param_1 + 0xfec),0,1);
    if (2 < *piVar6) {
      if (*DAT_0002b7ac == 0) {
        log_message(DAT_0002b7b8,DAT_0002b7b0);
      }
      else {
        debug_print(DAT_0002b7b8,DAT_0002b7b0);
      }
    }
LAB_0002b17c:
    *(uint *)(param_1 + 0x104c) = (uint)*param_2;
    param_1 = param_1 + 0x80;
LAB_0002b188:
    process_sync_buffer(param_1);
    goto LAB_0002b1ac;
  case 8:
    if (2 < (int)*DAT_0002b4ec) {
      if (*DAT_0002b4d4 == 0) {
        log_message(DAT_0002b50c,DAT_0002b4d8);
      }
      else {
        debug_print(DAT_0002b50c,DAT_0002b4d8);
      }
    }
    memcpy(*(undefined4 *)(param_1 + 0xffc),pbVar23,0x217);
    if ((param_2[5] == 0) &&
       (memset_bytes(*(void**)(param_1 + 0xffc),0,0x217), param_2[5] == 0)) {
      return 0;
    }
    uVar28 = 9;
    goto LAB_0002b446;
  case 9:
    if ((int)*DAT_0002b4ec < 3) {
      return 0;
    }
    if (*DAT_0002b4d4 != 0) {
      debug_print(DAT_0002b510,DAT_0002b4d8);
      return 0;
    }
    log_message(DAT_0002b510,DAT_0002b4d8);
    return 0;
  case 10:
    bVar21 = param_2[4];
    uVar27 = (uint)bVar21;
    uVar20 = (uint)(byte)param_1[0xef4];
    bVar1 = param_2[5];
    uVar25 = (uint)bVar1;
    if ((uVar20 != uVar27) || ((byte)param_1[0xef5] != uVar25)) {
      if (2 < *DAT_0002b7a8) {
        if (*DAT_0002b7ac == 0) {
          log_message(DAT_0002b7bc,DAT_0002b7b0,uVar27,uVar25);
        }
        else {
          debug_print(DAT_0002b7bc,DAT_0002b7b0,uVar27,uVar25);
        }
      }
      param_1[0xef4] = bVar21;
      param_1[0xef5] = bVar1;
      goto LAB_0002b17c;
    }
    if (2 < *DAT_0002b7a8) {
      iVar24 = *DAT_0002b7ac;
      uVar28 = (undefined4)DAT_0002b7c0;
      uVar12 = (undefined4)DAT_0002b7b0;
      goto LAB_0002b1a0;
    }
    goto LAB_0002b1ac;
  case 0xc:
    iVar24 = get_low_battery_flag_if_master();
    if (iVar24 != 0) {
      return 0;
    }
    *(undefined1 *)(*(int *)(param_1 + 0x1004) + 0x195) = 0;
    iVar24 = *(int *)(param_1 + 0x1004);
    goto LAB_0002b4a0;
  case 0xe:
    iVar24 = get_low_battery_flag_if_master();
    if (iVar24 != 0) {
      return 0;
    }
    *(undefined1 *)(*(int *)(param_1 + 0x1008) + 0x195) = 0;
    iVar24 = *(int *)(param_1 + 0x1008);
LAB_0002b4a0:
    if (*(char *)(iVar24 + 6) == '\0') {
      *(undefined1 *)(iVar24 + 6) = 10;
    }
    *param_3 = 0xc9;
    if (**(int **)(param_1 + 0x1054) == 0xb) {
      return 1;
    }
    uVar28 = 0xb;
LAB_0002b404:
    update_persist_task_status(param_1,uVar28,2);
    return 1;
  case 0x10:
    *(undefined4 *)(param_1 + 0x104c) = 7;
    pcVar14 = param_1 + 0x80;
    goto LAB_0002b282;
  case 0x13:
    bVar21 = param_2[4];
    if (0 < *DAT_0002b7a8) {
      if (*DAT_0002b7ac == 0) {
        log_message(DAT_0002b7c4,DAT_0002b7b0,(uint)bVar21);
      }
      else {
        debug_print(DAT_0002b7c4,DAT_0002b7b0,(uint)bVar21);
      }
    }
    FUN_00019ac0((uint)bVar21);
    goto LAB_0002b1ac;
  case 0x25:
    if (2 < *DAT_0002b7a8) {
      if (*DAT_0002b7ac == 0) {
        log_message(DAT_0002b7c8,DAT_0002b7b0,(uint)param_2[8]);
      }
      else {
        debug_print(DAT_0002b7c8,DAT_0002b7b0,(uint)param_2[8]);
      }
    }
    if (param_2[8] != 2) {
      return 0;
    }
    if (1 < *piVar6) {
      if (*DAT_0002b7ac == 0) {
        log_message(DAT_0002b7cc,DAT_0002b7b0,(uint)param_2[9],(uint)param_2[10],(uint)param_2[0xb]);
      }
      else {
        debug_print(DAT_0002b7cc,DAT_0002b7b0,(uint)param_2[9],(uint)param_2[10],(uint)param_2[0xb]);
      }
    }
    if (param_2[9] != 1) {
      **(undefined1 **)(param_1 + 0x1018) = 0;
      return 0;
    }
    **(undefined1 **)(param_1 + 0x1018) = 1;
    param_1[0xec0] = param_2[10];
    param_1[0xec1] = param_2[0xb];
    iVar24 = is_system_idle_ready();
    if (iVar24 == 0) {
      return 0;
    }
    uVar28 = 0xf;
LAB_0002b446:
    update_persist_task_status(param_1,uVar28,2);
switchD_0002b03a_caseD_3:
    return 0;
  }
LAB_0002b1ac:
  bVar21 = 0xc9;
LAB_0002b2d8:
  *param_3 = bVar21;
  return 1;
}
