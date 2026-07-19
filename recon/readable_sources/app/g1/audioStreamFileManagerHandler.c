#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   local_f8         => struct g1_layout_audio_file_mgr_locals__stack_0939      [stack_0939; G1-original]
 *   local_f4         => struct g1_layout_audio_file_mgr_flags__stack_0940       [stack_0940; G1-original]
 *   local_f0         => struct g1_layout_audio_stream_file_locals__stack_0941   [stack_0941; G1-original]
 * Raw function identity: 0x0002f94c.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0002f94c @ 0x0002f94c
 * public-name: audioStreamFileManagerHandler
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   crc32_update                             <= FUN_0002360c @ 0x0002360c
 *   getAudioMessageQueueCacheData            <= FUN_0002f460 @ 0x0002f460
 *   delVoiceBlock                            <= FUN_0002f4a8 @ 0x0002f4a8
 *   drain_audio_msgq                         <= FUN_0002f688 @ 0x0002f688
 *   atomic_get_3                             <= FUN_0002f940 @ 0x0002f940
 *   requestAudioInfoToApp                    <= FUN_00048840 @ 0x00048840
 *   display_DelayClose                       <= FUN_000498c0 @ 0x000498c0
 *   get_timestamp                            <= FUN_0007d224 @ 0x0007d224
 *   z_device_is_ready                        <= FUN_0008638c @ 0x0008638c
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_87bf0                             @ 0x00087bf0
 *   rodata_8a050                             @ 0x0008a050
 *   rodata_9e9ea                             @ 0x0009e9ea
 *   rodata_9ea0a                             @ 0x0009ea0a
 *   rodata_9eba7                             @ 0x0009eba7
 *   rodata_9ebc6                             @ 0x0009ebc6
 *   rodata_a4395                             @ 0x000a4395
 *   rodata_a43b9                             @ 0x000a43b9
 *   rodata_a43f3                             @ 0x000a43f3
 *   rodata_a4413                             @ 0x000a4413
 *   rodata_a4439                             @ 0x000a4439
 *   rodata_a447d                             @ 0x000a447d
 *   rodata_a44bf                             @ 0x000a44bf
 *   rodata_a4511                             @ 0x000a4511
 *   rodata_a4558                             @ 0x000a4558
 *   rodata_a457d                             @ 0x000a457d
 *   rodata_a45c1                             @ 0x000a45c1
 *   rodata_a461a                             @ 0x000a461a
 *   rodata_a4675                             @ 0x000a4675
 *   rodata_a4690                             @ 0x000a4690
 *   rodata_a46cb                             @ 0x000a46cb
 *   rodata_a46fd                             @ 0x000a46fd
 *   rodata_a4739                             @ 0x000a4739
 *   rodata_a47a2                             @ 0x000a47a2
 *   rodata_a486b                             @ 0x000a486b
 *   rodata_a4926                             @ 0x000a4926
 *   g_log_level                              @ 0x2000230c
 *   g_audio_msgq                             @ 0x20003890
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_20007bb4                               @ 0x20007bb4
 *   g_20007bb8                               @ 0x20007bb8
 *   g_20007bbc                               @ 0x20007bbc
 *   g_voice_block_dir_buf                    @ 0x20018daa
 *   g_20019daa                               @ 0x20019daa
 *   g_audio_stream_mgr_busy_flag             @ 0x20019dab
 */
/* Full reconstruction audioStreamFileManagerHandler @ 0x2f94c. */
#include <stdint.h>
typedef uint8_t undefined; typedef uint8_t undefined1; typedef uint16_t undefined2;
typedef uint32_t undefined4; typedef uint64_t undefined8; typedef uint8_t byte;
typedef uint32_t uint; typedef uint64_t ulonglong; typedef uint32_t code(uintptr_t,...);
#define firmware_data_0002fbc8 ((volatile int *)((unsigned long)&g_audio_stream_mgr_busy_flag) /*=0x20019dab*/)
#define firmware_data_0002fbcc ((unsigned long)&g_audio_msgq) /*=0x20003890*/
#define firmware_data_0002fbd0 ((volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/)
#define firmware_data_0002fbd4 ((volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)
#define firmware_data_0002fbd8 ((unsigned long)&rodata_a4926) /*=0xa4926*/
#define firmware_data_0002fbdc 0x000a4369u
#define firmware_data_0002fbe0 ((unsigned long)&rodata_a4395) /*=0xa4395*/
#define firmware_data_0002fbe4 ((unsigned long)&rodata_87bf0) /*=0x87bf0*/
#define firmware_data_0002fbe8 ((unsigned long)&rodata_9e9ea) /*=0x9e9ea*/
#define firmware_data_0002fbec ((unsigned long)&rodata_9ea0a) /*=0x9ea0a*/
#define firmware_data_0002fbf0 0x5aa5aa5au
#define firmware_data_0002fbf4 ((unsigned long)&rodata_a43b9) /*=0xa43b9*/
#define firmware_data_0002fbf8 ((unsigned long)&g_voice_block_dir_buf) /*=0x20018daa*/
#define firmware_data_0002fbfc ((unsigned long)&rodata_8a050) /*=0x8a050*/
#define firmware_data_0002fc00 ((unsigned long)&rodata_9eba7) /*=0x9eba7*/
#define firmware_data_0002fc04 ((unsigned long)&rodata_9ebc6) /*=0x9ebc6*/
#define firmware_data_0002fc08 ((unsigned long)&rodata_a43f3) /*=0xa43f3*/
#define firmware_data_0002fc0c ((unsigned long)&rodata_a4413) /*=0xa4413*/
#define firmware_data_0002fc10 ((unsigned long)&rodata_a4439) /*=0xa4439*/
#define firmware_data_0002fc14 ((unsigned long)&rodata_a447d) /*=0xa447d*/
#define firmware_data_0002fc18 ((volatile int *)((unsigned long)&g_20019daa) /*=0x20019daa*/)
#define firmware_data_0002fc1c ((unsigned long)&rodata_a44bf) /*=0xa44bf*/
#define firmware_data_0002fc20 ((volatile int *)((unsigned long)&g_20007bb8) /*=0x20007bb8*/)
#define firmware_data_0002fc24 ((volatile int *)((unsigned long)&g_20007bb4) /*=0x20007bb4*/)
#define firmware_data_0002fc28 ((volatile int *)((unsigned long)&g_20007bbc) /*=0x20007bbc*/)
#define firmware_data_0002fe74 ((unsigned long)&g_audio_msgq) /*=0x20003890*/
#define firmware_data_0002fe78 ((volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/)
#define firmware_data_0002fe7c ((volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)
#define firmware_data_0002fe80 ((unsigned long)&rodata_a4926) /*=0xa4926*/
#define firmware_data_0002fe84 ((unsigned long)&rodata_a4511) /*=0xa4511*/
#define firmware_data_0002fe88 ((volatile int *)((unsigned long)&g_20007bb8) /*=0x20007bb8*/)
#define firmware_data_0002fe8c ((unsigned long)&rodata_a4558) /*=0xa4558*/
#define firmware_data_0002fe90 ((unsigned long)&rodata_a457d) /*=0xa457d*/
#define firmware_data_0002fe94 ((unsigned long)&rodata_87bf0) /*=0x87bf0*/
#define firmware_data_0002fe98 ((volatile int *)((unsigned long)&g_20019daa) /*=0x20019daa*/)
#define firmware_data_0002fe9c ((unsigned long)&rodata_a45c1) /*=0xa45c1*/
#define firmware_data_0002fea0 ((unsigned long)&rodata_a461a) /*=0xa461a*/
#define firmware_data_0002fea4 ((unsigned long)&rodata_a46fd) /*=0xa46fd*/
#define firmware_data_0002fea8 ((unsigned long)&rodata_a4675) /*=0xa4675*/
#define firmware_data_0002feac ((unsigned long)&g_voice_block_dir_buf) /*=0x20018daa*/
#define firmware_data_0002feb0 ((volatile int *)((unsigned long)&g_20007bb4) /*=0x20007bb4*/)
#define firmware_data_00030138 ((volatile int *)((unsigned long)&g_20007bbc) /*=0x20007bbc*/)
#define firmware_data_0003013c ((unsigned long)&g_voice_block_dir_buf) /*=0x20018daa*/
#define firmware_data_00030140 ((volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)
#define firmware_data_00030144 ((unsigned long)&rodata_a4926) /*=0xa4926*/
#define firmware_data_00030148 ((unsigned long)&rodata_a4690) /*=0xa4690*/
#define firmware_data_0003014c ((unsigned long)&rodata_a46cb) /*=0xa46cb*/
#define firmware_data_00030150 ((volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/)
#define firmware_data_00030154 ((unsigned long)&rodata_a486b) /*=0xa486b*/
#define firmware_data_00030158 ((unsigned long)&rodata_a4739) /*=0xa4739*/
#define firmware_data_0003015c ((unsigned long)&rodata_a47a2) /*=0xa47a2*/
#define firmware_data_00030160 0x000a47d7u
#define firmware_data_00030164 0x000a4840u
#define firmware_data_00030168 ((volatile int *)((unsigned long)&g_20007bb8) /*=0x20007bb8*/)
extern uint32_t log_message(uintptr_t,...);
extern uint32_t get_device_info(uintptr_t,...);
extern uint32_t debug_print(uintptr_t,...);
extern uint32_t crc32_update(uintptr_t,...);
extern uint32_t getAudioMessageQueueCacheData(uintptr_t,...);
extern uint32_t delVoiceBlock(uintptr_t,...);
extern uint32_t drain_audio_msgq(uintptr_t,...);
extern uint32_t atomic_get_3(uintptr_t,...);
extern uint32_t requestAudioInfoToApp(uintptr_t,...);
extern uint32_t display_DelayClose(uintptr_t,...);
extern uint32_t get_timestamp(uintptr_t,...);
extern uint32_t z_device_is_ready(uintptr_t,...);
extern uint32_t memcpy(uintptr_t,...);
extern uint32_t memset_bytes(uintptr_t,...);
extern uint32_t sync_to_slave(uintptr_t,...);

undefined4 audioStreamFileManagerHandler(void)

{
  byte bVar1;
  char *pcVar2;
  int *piVar3;
  byte *pbVar4;
  undefined1 *puVar5;
  int *piVar6;
  undefined4 *puVar7;
  int iVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  int *piVar11;
  int iVar12;
  uint uVar13;
  uint uVar14;
  int *piVar15;
  code *pcVar16;
  int *piVar17;
  int iVar18;
  undefined8 uVar19;
  undefined2 local_f8 [2];
  char local_f4 [2];
  short local_f2;
  byte local_f0 [204];

  pcVar2 = (char *)(uintptr_t)firmware_data_0002fbc8;
  if (*firmware_data_0002fbc8 == '\0') {
    if (*(int *)(firmware_data_0002fbcc + 0x24) == 0) {
      return 0;
    }
    iVar8 = getAudioMessageQueueCacheData((uintptr_t)local_f4);
    piVar17 = (int *)(uintptr_t)firmware_data_0002fbd0;
    if (iVar8 != 0) goto control_label_0002f976;
    if (local_f4[0] != '\x01') {
      if (local_f4[0] != '\x03') {
        if (local_f4[0] == '\x04') {
          delVoiceBlock((uintptr_t)local_f0[0]);
          return 0;
        }
        if (local_f4[0] != '\x02') {
          return 0;
        }
      }
      drain_audio_msgq(0);
      return 0;
    }
    if (2 < *firmware_data_0002fbd0) {
      if (*firmware_data_0002fbd4 == 0) {
        log_message(firmware_data_0002fbe0,firmware_data_0002fbd8);
      }
      else {
        debug_print(0);
      }
    }
    piVar15 = (int *)(uintptr_t)firmware_data_0002fbe4;
    iVar8 = z_device_is_ready(firmware_data_0002fbe4);
    piVar3 = (int *)(uintptr_t)firmware_data_0002fbf8;
    if (iVar8 != 0) {
      memset_bytes(firmware_data_0002fbf8,0,0x1000);
      iVar8 = get_device_info(0);
      pcVar16 = *(code **)(iVar8 + 0x1030);
      uVar9 = get_device_info(0);
      iVar8 = (*pcVar16)(uVar9,0x400000,piVar3,0x1000);
      iVar12 = *piVar17;
      if (iVar8 != 0) {
control_label_0002fa04:
        if (iVar12 < 1) {
          return 0;
        }
        iVar8 = 0x400000;
        iVar12 = *firmware_data_0002fbd4;
        uVar9 = firmware_data_0002fbec;
        uVar10 = firmware_data_0002fbd8;
        goto control_label_0002fc9e;
      }
      if (*piVar3 == firmware_data_0002fbf0) {
control_label_0002fac2:
        piVar15 = (int *)(uintptr_t)firmware_data_0002fbd4;
        iVar8 = 0x7fffffff;
        uVar13 = 0;
        uVar14 = 0;
        do {
          if (piVar3[uVar14 * 5 + 2] == 0) {
            if (2 < *piVar17) {
              if (*firmware_data_0002fbd4 == 0) {
                log_message(firmware_data_0002fc0c,firmware_data_0002fbd8,uVar14);
              }
              else {
                debug_print(0);
              }
            }
            uVar13 = uVar14 & 0xff;
            goto control_label_0002fb54;
          }
          if (2 < *piVar17) {
            if (*piVar15 == 0) {
              log_message(firmware_data_0002fc10,firmware_data_0002fbd8,piVar3[uVar14 * 5 + 5],iVar8);
            }
            else {
              debug_print(firmware_data_0002fc10,firmware_data_0002fbd8,piVar3[uVar14 * 5 + 5],iVar8);
            }
          }
          piVar11 = piVar3 + uVar14 * 5 + 4;
          if ((piVar3[uVar14 * 5 + 5] < iVar8) &&
             ((iVar12 = atomic_get_3(0), iVar12 == 0 ||
              (iVar12 = atomic_get_3(0), iVar12 - 1U != uVar14)))) {
            iVar8 = piVar11[1];
            uVar13 = uVar14 & 0xff;
          }
          uVar14 = uVar14 + 1;
        } while (uVar14 != 4);
        if (2 < *piVar17) {
          if (*firmware_data_0002fbd4 == 0) {
            log_message(firmware_data_0002fc14,firmware_data_0002fbd8,uVar13);
          }
          else {
            debug_print(0);
          }
        }
control_label_0002fb54:
        *firmware_data_0002fc18 = (char)uVar13;
        if (2 < *piVar17) {
          if (*firmware_data_0002fbd4 == 0) {
            log_message(firmware_data_0002fc1c,firmware_data_0002fbd8,uVar13);
          }
          else {
            debug_print(0);
          }
        }
        *firmware_data_0002fc20 = 0;
        piVar17 = (int *)(uintptr_t)firmware_data_0002fbf8;
        *firmware_data_0002fc24 = 0;
        memset_bytes((uintptr_t)piVar17,0,0x1000);
        *pcVar2 = '\x01';
        *firmware_data_0002fc28 = 0;
        return 0;
      }
      if (2 < iVar12) {
        if (*firmware_data_0002fbd4 == 0) {
          log_message(firmware_data_0002fbf4,firmware_data_0002fbd8);
        }
        else {
          debug_print(0);
        }
      }
      memset_bytes(firmware_data_0002fbf8,0,0x1000);
      memcpy(firmware_data_0002fbf8,firmware_data_0002fbfc,0x58);
      iVar8 = get_device_info(0);
      pcVar16 = *(code **)(iVar8 + 0x1038);
      uVar9 = get_device_info(0);
      uVar19 = (*pcVar16)(uVar9,0x400000,0x1000);
      iVar8 = (int)uVar19;
      if (iVar8 == 0) {
        iVar8 = get_device_info(0,(int)((ulonglong)uVar19 >> 0x20),0);
        pcVar16 = *(code **)(iVar8 + 0x1034);
        uVar9 = get_device_info(0);
        iVar8 = (*pcVar16)(uVar9,0x400000,firmware_data_0002fbf8,0x1000);
        iVar12 = *piVar17;
        if (iVar8 == 0) {
          if (2 < iVar12) {
            if (*firmware_data_0002fbd4 == 0) {
              log_message(firmware_data_0002fc08,firmware_data_0002fbd8,0);
            }
            else {
              debug_print(0);
            }
          }
          goto control_label_0002fac2;
        }
control_label_0002faa0:
        if (iVar12 < 1) {
          return 0;
        }
        iVar12 = *firmware_data_0002fbd4;
        uVar9 = firmware_data_0002fc04;
        uVar10 = firmware_data_0002fbd8;
        goto control_label_0002fc9e;
      }
      iVar12 = *piVar17;
control_label_0002fa68:
      if (iVar12 < 3) {
        return 0;
      }
      iVar12 = *firmware_data_0002fbd4;
      uVar9 = firmware_data_0002fc00;
      uVar10 = firmware_data_0002fbd8;
      goto control_label_0002fc9e;
    }
    iVar8 = *piVar17;
  }
  else {
    if (*firmware_data_0002fbc8 != '\x01') {
      return 0;
    }
    if (*(int *)(firmware_data_0002fe74 + 0x24) == 0) {
      return 0;
    }
    iVar8 = getAudioMessageQueueCacheData((uintptr_t)local_f4);
    puVar5 = (undefined1 *)(uintptr_t)firmware_data_0002feac;
    piVar3 = (int *)(uintptr_t)firmware_data_0002fe88;
    piVar17 = (int *)(uintptr_t)firmware_data_0002fe78;
    if (iVar8 != 0) {
control_label_0002f976:
      if (*firmware_data_0002fbd0 < 1) {
        return 0;
      }
      iVar8 = *firmware_data_0002fbd4;
      uVar9 = firmware_data_0002fbdc;
      uVar10 = firmware_data_0002fbd8;
control_label_0002f986:
      if (iVar8 != 0) {
        debug_print(0);
        return 0;
      }
      log_message(uVar9,uVar10);
      return 0;
    }
    if (local_f4[0] == '\x01') {
      *pcVar2 = '\0';
      if (*piVar17 < 1) {
        return 0;
      }
      iVar8 = *firmware_data_0002fe7c;
      uVar9 = firmware_data_0002fe84;
      uVar10 = firmware_data_0002fe80;
      goto control_label_0002f986;
    }
    if (local_f4[0] == '\x02') {
      iVar12 = *firmware_data_0002fe88;
      iVar8 = local_f2 + iVar12;
      iVar18 = *firmware_data_0002fe78;
      if (iVar8 < 0x1000) {
        memcpy(firmware_data_0002feac + iVar12,local_f0);
        *piVar3 = iVar8;
        if (iVar18 < 3) {
          return 0;
        }
        iVar12 = *firmware_data_0002fe7c;
        uVar9 = firmware_data_0002fe8c;
        uVar10 = firmware_data_0002fe80;
        goto control_label_0002fc9e;
      }
      memcpy(firmware_data_0002feac + iVar12,local_f0,0x1000 - iVar12);
      if (2 < iVar18) {
        if (*firmware_data_0002fe7c == 0) {
          log_message(firmware_data_0002fe90,firmware_data_0002fe80);
        }
        else {
          debug_print(0);
        }
      }
      piVar15 = (int *)(uintptr_t)firmware_data_0002fe94;
      iVar8 = z_device_is_ready(firmware_data_0002fe94);
      piVar6 = (int *)(uintptr_t)firmware_data_0002feb0;
      piVar11 = (int *)(uintptr_t)firmware_data_0002fe7c;
      if (iVar8 != 0) {
        iVar12 = (uint)*firmware_data_0002fe98 * 0x20000 + 0x421000 + *firmware_data_0002feb0 * 0x1000;
        if ((int)((uint)*firmware_data_0002fe98 * 0x20000 + 0x431000) < iVar12) {
          if (0 < *piVar17) {
            if (*firmware_data_0002fe7c == 0) {
              log_message(firmware_data_0002fe9c,firmware_data_0002fe80);
            }
            else {
              debug_print(0);
            }
            if (0 < *piVar17) {
              if (*piVar11 == 0) {
                log_message(firmware_data_0002fea0,firmware_data_0002fe80);
              }
              else {
                debug_print(0);
              }
            }
          }
          local_f8[0] = 1;
          uVar9 = get_device_info(0);
          sync_to_slave(uVar9,6,local_f8,2);
          display_DelayClose(10000);
          goto control_label_0002fd4a;
        }
        if (2 < *piVar17) {
          if (*firmware_data_0002fe7c == 0) {
            log_message(firmware_data_0002fea8,firmware_data_0002fe80,iVar12);
          }
          else {
            debug_print(0);
          }
        }
        iVar8 = get_device_info(0);
        pcVar16 = *(code **)(iVar8 + 0x1038);
        uVar9 = get_device_info(0);
        uVar19 = (*pcVar16)(uVar9,iVar12,0x1000);
        iVar8 = (int)uVar19;
        if (iVar8 == 0) {
          iVar8 = get_device_info(0,(int)((ulonglong)uVar19 >> 0x20),0);
          pcVar16 = *(code **)(iVar8 + 0x1034);
          uVar9 = get_device_info(0);
          iVar8 = (*pcVar16)(uVar9,iVar12,firmware_data_0002feac,0x1000);
          puVar7 = (undefined4 *)(uintptr_t)firmware_data_00030138;
          if (iVar8 == 0) {
            uVar9 = crc32_update(*firmware_data_00030138,firmware_data_0003013c,0x1000);
            iVar8 = *piVar6;
            *puVar7 = uVar9;
            *piVar6 = iVar8 + 1;
            if (2 < *piVar17) {
              if (*firmware_data_00030140 == 0) {
                log_message(firmware_data_00030148,firmware_data_00030144,iVar12);
              }
              else {
                debug_print(0);
              }
            }
            iVar8 = firmware_data_0003013c;
            iVar12 = *piVar3;
            *piVar3 = 0;
            memset_bytes(iVar8,0,0x1000);
            iVar8 = -iVar12 + 0x1000;
            if (2 < *piVar17) {
              if (*firmware_data_00030140 == 0) {
                log_message(firmware_data_0003014c,firmware_data_00030144,local_f2 - iVar8);
              }
              else {
                debug_print(0);
              }
            }
            iVar18 = *piVar3;
            iVar8 = local_f2 - iVar8;
            memcpy((uintptr_t)(puVar5 + iVar18),(uintptr_t)(local_f0 + (0x1000 - iVar12)),iVar8);
            *piVar3 = iVar18 + iVar8;
            return 0;
          }
          iVar12 = *piVar17;
          goto control_label_0002faa0;
        }
        goto control_label_0002fe48;
      }
    }
    else {
      if (local_f4[0] != '\x03') {
        if (local_f4[0] == '\x04') {
          if (1 < *firmware_data_00030150) {
            if (*firmware_data_00030140 == 0) {
              log_message(firmware_data_00030154,firmware_data_00030144,(uint)local_f0[0]);
            }
            else {
              debug_print(0);
            }
          }
          delVoiceBlock((uintptr_t)local_f0[0]);
          *pcVar2 = '\0';
          return 0;
        }
        return 0;
      }
control_label_0002fd4a:
      piVar15 = (int *)(uintptr_t)firmware_data_0002fe7c;
      piVar17 = (int *)(uintptr_t)firmware_data_0002fe78;
      if (2 < *firmware_data_0002fe78) {
        if (*firmware_data_0002fe7c == 0) {
          log_message(firmware_data_0002fea4,firmware_data_0002fe80);
        }
        else {
          debug_print(0);
        }
        if (2 < *piVar17) {
          if (*piVar15 == 0) {
            log_message(firmware_data_0002fe90,firmware_data_0002fe80);
          }
          else {
            debug_print(0);
          }
        }
      }
      piVar15 = (int *)(uintptr_t)firmware_data_0002fe94;
      iVar8 = z_device_is_ready(firmware_data_0002fe94);
      piVar3 = (int *)(uintptr_t)firmware_data_0002feb0;
      pbVar4 = (byte *)(uintptr_t)firmware_data_0002fe98;
      if (iVar8 != 0) {
        iVar12 = (uint)*firmware_data_0002fe98 * 0x20000 + 0x421000 + *firmware_data_0002feb0 * 0x1000;
        if (2 < *piVar17) {
          if (*firmware_data_0002fe7c == 0) {
            log_message(firmware_data_0002fea8,firmware_data_0002fe80,iVar12);
          }
          else {
            debug_print(0);
          }
        }
        iVar8 = get_device_info(0);
        pcVar16 = *(code **)(iVar8 + 0x1038);
        uVar9 = get_device_info(0);
        uVar19 = (*pcVar16)(uVar9,iVar12,0x1000);
        iVar8 = (int)uVar19;
        if (iVar8 == 0) {
          iVar8 = get_device_info(0,(int)((ulonglong)uVar19 >> 0x20),0);
          puVar5 = (undefined1 *)(uintptr_t)firmware_data_0002feac;
          pcVar16 = *(code **)(iVar8 + 0x1034);
          uVar9 = get_device_info(0);
          iVar8 = (*pcVar16)(uVar9,iVar12,puVar5,0x1000);
          piVar15 = (int *)(uintptr_t)firmware_data_00030168;
          puVar7 = (undefined4 *)(uintptr_t)firmware_data_00030138;
          if (iVar8 != 0) {
            if (*piVar17 < 1) {
              return 0;
            }
            iVar12 = *firmware_data_0002fe7c;
            uVar9 = firmware_data_0002fc04;
            uVar10 = firmware_data_0002fbd8;
            goto control_label_0002fc9e;
          }
          uVar9 = crc32_update(*firmware_data_00030138,puVar5,*firmware_data_00030168);
          *puVar7 = uVar9;
          memset_bytes((uintptr_t)puVar5,0,0x1000);
          iVar8 = get_device_info(0);
          pcVar16 = *(code **)(iVar8 + 0x1030);
          uVar9 = get_device_info(0);
          iVar8 = (*pcVar16)(uVar9,0x400000,puVar5,0x1000);
          if (iVar8 != 0) {
            iVar12 = *piVar17;
            goto control_label_0002fa04;
          }
          iVar8 = get_device_info(0);
          pcVar16 = *(code **)(iVar8 + 0x1038);
          uVar9 = get_device_info(0);
          iVar8 = (*pcVar16)(uVar9,0x400000,0x1000);
          if (iVar8 == 0) {
            puVar5[1] = 0xaa;
            *puVar5 = 0x5a;
            puVar5[3] = 0x5a;
            uVar13 = (uint)*pbVar4;
            puVar5[2] = 0xa5;
            iVar8 = *piVar3;
            iVar18 = uVar13 * 0x20000 + 0x421000;
            *(int *)(puVar5 + uVar13 * 0x14 + 0xc) = iVar18;
            iVar12 = *piVar15;
            puVar5[4] = 0;
            puVar5[5] = 0;
            puVar5[6] = 0;
            puVar5[7] = 0;
            *(int *)(puVar5 + uVar13 * 0x14 + 0x10) = iVar18 + iVar8 * 0x1000 + iVar12;
            puVar5[uVar13 * 0x14 + 8] = 2;
            puVar5[uVar13 * 0x14 + 9] = 0;
            puVar5[uVar13 * 0x14 + 10] = 0;
            puVar5[uVar13 * 0x14 + 0xb] = 0;
            uVar9 = get_timestamp(0);
            bVar1 = *pbVar4;
            iVar8 = *piVar17;
            *(undefined4 *)(puVar5 + (uint)bVar1 * 0x14 + 0x14) = uVar9;
            *(undefined4 *)(puVar5 + (uint)bVar1 * 0x14 + 0x18) = *puVar7;
            if (2 < iVar8) {
              if (*firmware_data_00030140 == 0) {
                log_message(firmware_data_00030158,firmware_data_00030144);
              }
              else {
                debug_print(0);
              }
            }
            piVar15 = (int *)(uintptr_t)firmware_data_00030168;
            iVar8 = firmware_data_0003013c;
            iVar12 = (uint)*pbVar4 * 0x14 + firmware_data_0003013c;
            if (*(int *)(iVar12 + 0xc) == *(int *)(iVar12 + 0x10)) {
              if (2 < *piVar17) {
                if (*firmware_data_00030140 == 0) {
                  log_message(firmware_data_0003015c,firmware_data_00030144);
                }
                else {
                  debug_print(0);
                }
              }
              *pcVar2 = '\0';
              *pbVar4 = 0;
              *piVar15 = 0;
              *piVar3 = 0;
              drain_audio_msgq(0);
              if (*piVar17 < 1) {
                return 0;
              }
              iVar8 = *firmware_data_00030140;
              uVar9 = firmware_data_00030160;
              uVar10 = firmware_data_00030144;
            }
            else {
              iVar12 = get_device_info(0);
              pcVar16 = *(code **)(iVar12 + 0x1034);
              uVar9 = get_device_info(0);
              iVar8 = (*pcVar16)(uVar9,0x400000,iVar8,0x1000);
              *pcVar2 = '\0';
              *pbVar4 = 0;
              *piVar15 = 0;
              *piVar3 = 0;
              drain_audio_msgq(0);
              requestAudioInfoToApp(1);
              if (iVar8 != 0) {
                if (*piVar17 < 1) {
                  return 0;
                }
                iVar12 = *firmware_data_00030140;
                uVar9 = firmware_data_0002fc04;
                uVar10 = firmware_data_0002fbd8;
                goto control_label_0002fc9e;
              }
              if (*piVar17 < 3) {
                return 0;
              }
              iVar8 = *firmware_data_00030140;
              uVar9 = firmware_data_00030164;
              uVar10 = firmware_data_00030144;
            }
            goto control_label_0002f986;
          }
        }
control_label_0002fe48:
        iVar12 = *piVar17;
        goto control_label_0002fa68;
      }
    }
    iVar8 = *piVar17;
  }
  if (iVar8 < 1) {
    return 0;
  }
  iVar8 = *piVar15;
  iVar12 = *firmware_data_0002fbd4;
  uVar9 = firmware_data_0002fbe8;
  uVar10 = firmware_data_0002fbd8;
control_label_0002fc9e:
  if (iVar12 == 0) {
    log_message(uVar9,uVar10,iVar8);
  }
  else {
    debug_print(0);
  }
  return 0;
}
