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
#define DAT_0002fbc8 ((volatile int *)0x20019dabu)
#define DAT_0002fbcc 0x20003890u
#define DAT_0002fbd0 ((volatile int *)0x2000230cu)
#define DAT_0002fbd4 ((volatile int *)0x20007554u)
#define DAT_0002fbd8 0x000a4926u
#define DAT_0002fbdc 0x000a4369u
#define DAT_0002fbe0 0x000a4395u
#define DAT_0002fbe4 0x00087bf0u
#define DAT_0002fbe8 0x0009e9eau
#define DAT_0002fbec 0x0009ea0au
#define DAT_0002fbf0 0x5aa5aa5au
#define DAT_0002fbf4 0x000a43b9u
#define DAT_0002fbf8 0x20018daau
#define DAT_0002fbfc 0x0008a050u
#define DAT_0002fc00 0x0009eba7u
#define DAT_0002fc04 0x0009ebc6u
#define DAT_0002fc08 0x000a43f3u
#define DAT_0002fc0c 0x000a4413u
#define DAT_0002fc10 0x000a4439u
#define DAT_0002fc14 0x000a447du
#define DAT_0002fc18 ((volatile int *)0x20019daau)
#define DAT_0002fc1c 0x000a44bfu
#define DAT_0002fc20 ((volatile int *)0x20007bb8u)
#define DAT_0002fc24 ((volatile int *)0x20007bb4u)
#define DAT_0002fc28 ((volatile int *)0x20007bbcu)
#define DAT_0002fe74 0x20003890u
#define DAT_0002fe78 ((volatile int *)0x2000230cu)
#define DAT_0002fe7c ((volatile int *)0x20007554u)
#define DAT_0002fe80 0x000a4926u
#define DAT_0002fe84 0x000a4511u
#define DAT_0002fe88 ((volatile int *)0x20007bb8u)
#define DAT_0002fe8c 0x000a4558u
#define DAT_0002fe90 0x000a457du
#define DAT_0002fe94 0x00087bf0u
#define DAT_0002fe98 ((volatile int *)0x20019daau)
#define DAT_0002fe9c 0x000a45c1u
#define DAT_0002fea0 0x000a461au
#define DAT_0002fea4 0x000a46fdu
#define DAT_0002fea8 0x000a4675u
#define DAT_0002feac 0x20018daau
#define DAT_0002feb0 ((volatile int *)0x20007bb4u)
#define DAT_00030138 ((volatile int *)0x20007bbcu)
#define DAT_0003013c 0x20018daau
#define DAT_00030140 ((volatile int *)0x20007554u)
#define DAT_00030144 0x000a4926u
#define DAT_00030148 0x000a4690u
#define DAT_0003014c 0x000a46cbu
#define DAT_00030150 ((volatile int *)0x2000230cu)
#define DAT_00030154 0x000a486bu
#define DAT_00030158 0x000a4739u
#define DAT_0003015c 0x000a47a2u
#define DAT_00030160 0x000a47d7u
#define DAT_00030164 0x000a4840u
#define DAT_00030168 ((volatile int *)0x20007bb8u)
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

  pcVar2 = (char *)(uintptr_t)DAT_0002fbc8;
  if (*DAT_0002fbc8 == '\0') {
    if (*(int *)(DAT_0002fbcc + 0x24) == 0) {
      return 0;
    }
    iVar8 = getAudioMessageQueueCacheData((uintptr_t)local_f4);
    piVar17 = (int *)(uintptr_t)DAT_0002fbd0;
    if (iVar8 != 0) goto LAB_0002f976;
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
    if (2 < *DAT_0002fbd0) {
      if (*DAT_0002fbd4 == 0) {
        log_message(DAT_0002fbe0,DAT_0002fbd8);
      }
      else {
        debug_print(0);
      }
    }
    piVar15 = (int *)(uintptr_t)DAT_0002fbe4;
    iVar8 = z_device_is_ready(DAT_0002fbe4);
    piVar3 = (int *)(uintptr_t)DAT_0002fbf8;
    if (iVar8 != 0) {
      memset_bytes(DAT_0002fbf8,0,0x1000);
      iVar8 = get_device_info(0);
      pcVar16 = *(code **)(iVar8 + 0x1030);
      uVar9 = get_device_info(0);
      iVar8 = (*pcVar16)(uVar9,0x400000,piVar3,0x1000);
      iVar12 = *piVar17;
      if (iVar8 != 0) {
LAB_0002fa04:
        if (iVar12 < 1) {
          return 0;
        }
        iVar8 = 0x400000;
        iVar12 = *DAT_0002fbd4;
        uVar9 = DAT_0002fbec;
        uVar10 = DAT_0002fbd8;
        goto LAB_0002fc9e;
      }
      if (*piVar3 == DAT_0002fbf0) {
LAB_0002fac2:
        piVar15 = (int *)(uintptr_t)DAT_0002fbd4;
        iVar8 = 0x7fffffff;
        uVar13 = 0;
        uVar14 = 0;
        do {
          if (piVar3[uVar14 * 5 + 2] == 0) {
            if (2 < *piVar17) {
              if (*DAT_0002fbd4 == 0) {
                log_message(DAT_0002fc0c,DAT_0002fbd8,uVar14);
              }
              else {
                debug_print(0);
              }
            }
            uVar13 = uVar14 & 0xff;
            goto LAB_0002fb54;
          }
          if (2 < *piVar17) {
            if (*piVar15 == 0) {
              log_message(DAT_0002fc10,DAT_0002fbd8,piVar3[uVar14 * 5 + 5],iVar8);
            }
            else {
              debug_print(DAT_0002fc10,DAT_0002fbd8,piVar3[uVar14 * 5 + 5],iVar8);
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
          if (*DAT_0002fbd4 == 0) {
            log_message(DAT_0002fc14,DAT_0002fbd8,uVar13);
          }
          else {
            debug_print(0);
          }
        }
LAB_0002fb54:
        *DAT_0002fc18 = (char)uVar13;
        if (2 < *piVar17) {
          if (*DAT_0002fbd4 == 0) {
            log_message(DAT_0002fc1c,DAT_0002fbd8,uVar13);
          }
          else {
            debug_print(0);
          }
        }
        *DAT_0002fc20 = 0;
        piVar17 = (int *)(uintptr_t)DAT_0002fbf8;
        *DAT_0002fc24 = 0;
        memset_bytes((uintptr_t)piVar17,0,0x1000);
        *pcVar2 = '\x01';
        *DAT_0002fc28 = 0;
        return 0;
      }
      if (2 < iVar12) {
        if (*DAT_0002fbd4 == 0) {
          log_message(DAT_0002fbf4,DAT_0002fbd8);
        }
        else {
          debug_print(0);
        }
      }
      memset_bytes(DAT_0002fbf8,0,0x1000);
      memcpy(DAT_0002fbf8,DAT_0002fbfc,0x58);
      iVar8 = get_device_info(0);
      pcVar16 = *(code **)(iVar8 + 0x1038);
      uVar9 = get_device_info(0);
      uVar19 = (*pcVar16)(uVar9,0x400000,0x1000);
      iVar8 = (int)uVar19;
      if (iVar8 == 0) {
        iVar8 = get_device_info(0,(int)((ulonglong)uVar19 >> 0x20),0);
        pcVar16 = *(code **)(iVar8 + 0x1034);
        uVar9 = get_device_info(0);
        iVar8 = (*pcVar16)(uVar9,0x400000,DAT_0002fbf8,0x1000);
        iVar12 = *piVar17;
        if (iVar8 == 0) {
          if (2 < iVar12) {
            if (*DAT_0002fbd4 == 0) {
              log_message(DAT_0002fc08,DAT_0002fbd8,0);
            }
            else {
              debug_print(0);
            }
          }
          goto LAB_0002fac2;
        }
LAB_0002faa0:
        if (iVar12 < 1) {
          return 0;
        }
        iVar12 = *DAT_0002fbd4;
        uVar9 = DAT_0002fc04;
        uVar10 = DAT_0002fbd8;
        goto LAB_0002fc9e;
      }
      iVar12 = *piVar17;
LAB_0002fa68:
      if (iVar12 < 3) {
        return 0;
      }
      iVar12 = *DAT_0002fbd4;
      uVar9 = DAT_0002fc00;
      uVar10 = DAT_0002fbd8;
      goto LAB_0002fc9e;
    }
    iVar8 = *piVar17;
  }
  else {
    if (*DAT_0002fbc8 != '\x01') {
      return 0;
    }
    if (*(int *)(DAT_0002fe74 + 0x24) == 0) {
      return 0;
    }
    iVar8 = getAudioMessageQueueCacheData((uintptr_t)local_f4);
    puVar5 = (undefined1 *)(uintptr_t)DAT_0002feac;
    piVar3 = (int *)(uintptr_t)DAT_0002fe88;
    piVar17 = (int *)(uintptr_t)DAT_0002fe78;
    if (iVar8 != 0) {
LAB_0002f976:
      if (*DAT_0002fbd0 < 1) {
        return 0;
      }
      iVar8 = *DAT_0002fbd4;
      uVar9 = DAT_0002fbdc;
      uVar10 = DAT_0002fbd8;
LAB_0002f986:
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
      iVar8 = *DAT_0002fe7c;
      uVar9 = DAT_0002fe84;
      uVar10 = DAT_0002fe80;
      goto LAB_0002f986;
    }
    if (local_f4[0] == '\x02') {
      iVar12 = *DAT_0002fe88;
      iVar8 = local_f2 + iVar12;
      iVar18 = *DAT_0002fe78;
      if (iVar8 < 0x1000) {
        memcpy(DAT_0002feac + iVar12,local_f0);
        *piVar3 = iVar8;
        if (iVar18 < 3) {
          return 0;
        }
        iVar12 = *DAT_0002fe7c;
        uVar9 = DAT_0002fe8c;
        uVar10 = DAT_0002fe80;
        goto LAB_0002fc9e;
      }
      memcpy(DAT_0002feac + iVar12,local_f0,0x1000 - iVar12);
      if (2 < iVar18) {
        if (*DAT_0002fe7c == 0) {
          log_message(DAT_0002fe90,DAT_0002fe80);
        }
        else {
          debug_print(0);
        }
      }
      piVar15 = (int *)(uintptr_t)DAT_0002fe94;
      iVar8 = z_device_is_ready(DAT_0002fe94);
      piVar6 = (int *)(uintptr_t)DAT_0002feb0;
      piVar11 = (int *)(uintptr_t)DAT_0002fe7c;
      if (iVar8 != 0) {
        iVar12 = (uint)*DAT_0002fe98 * 0x20000 + 0x421000 + *DAT_0002feb0 * 0x1000;
        if ((int)((uint)*DAT_0002fe98 * 0x20000 + 0x431000) < iVar12) {
          if (0 < *piVar17) {
            if (*DAT_0002fe7c == 0) {
              log_message(DAT_0002fe9c,DAT_0002fe80);
            }
            else {
              debug_print(0);
            }
            if (0 < *piVar17) {
              if (*piVar11 == 0) {
                log_message(DAT_0002fea0,DAT_0002fe80);
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
          goto LAB_0002fd4a;
        }
        if (2 < *piVar17) {
          if (*DAT_0002fe7c == 0) {
            log_message(DAT_0002fea8,DAT_0002fe80,iVar12);
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
          iVar8 = (*pcVar16)(uVar9,iVar12,DAT_0002feac,0x1000);
          puVar7 = (undefined4 *)(uintptr_t)DAT_00030138;
          if (iVar8 == 0) {
            uVar9 = crc32_update(*DAT_00030138,DAT_0003013c,0x1000);
            iVar8 = *piVar6;
            *puVar7 = uVar9;
            *piVar6 = iVar8 + 1;
            if (2 < *piVar17) {
              if (*DAT_00030140 == 0) {
                log_message(DAT_00030148,DAT_00030144,iVar12);
              }
              else {
                debug_print(0);
              }
            }
            iVar8 = DAT_0003013c;
            iVar12 = *piVar3;
            *piVar3 = 0;
            memset_bytes(iVar8,0,0x1000);
            iVar8 = -iVar12 + 0x1000;
            if (2 < *piVar17) {
              if (*DAT_00030140 == 0) {
                log_message(DAT_0003014c,DAT_00030144,local_f2 - iVar8);
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
          goto LAB_0002faa0;
        }
        goto LAB_0002fe48;
      }
    }
    else {
      if (local_f4[0] != '\x03') {
        if (local_f4[0] == '\x04') {
          if (1 < *DAT_00030150) {
            if (*DAT_00030140 == 0) {
              log_message(DAT_00030154,DAT_00030144,(uint)local_f0[0]);
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
LAB_0002fd4a:
      piVar15 = (int *)(uintptr_t)DAT_0002fe7c;
      piVar17 = (int *)(uintptr_t)DAT_0002fe78;
      if (2 < *DAT_0002fe78) {
        if (*DAT_0002fe7c == 0) {
          log_message(DAT_0002fea4,DAT_0002fe80);
        }
        else {
          debug_print(0);
        }
        if (2 < *piVar17) {
          if (*piVar15 == 0) {
            log_message(DAT_0002fe90,DAT_0002fe80);
          }
          else {
            debug_print(0);
          }
        }
      }
      piVar15 = (int *)(uintptr_t)DAT_0002fe94;
      iVar8 = z_device_is_ready(DAT_0002fe94);
      piVar3 = (int *)(uintptr_t)DAT_0002feb0;
      pbVar4 = (byte *)(uintptr_t)DAT_0002fe98;
      if (iVar8 != 0) {
        iVar12 = (uint)*DAT_0002fe98 * 0x20000 + 0x421000 + *DAT_0002feb0 * 0x1000;
        if (2 < *piVar17) {
          if (*DAT_0002fe7c == 0) {
            log_message(DAT_0002fea8,DAT_0002fe80,iVar12);
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
          puVar5 = (undefined1 *)(uintptr_t)DAT_0002feac;
          pcVar16 = *(code **)(iVar8 + 0x1034);
          uVar9 = get_device_info(0);
          iVar8 = (*pcVar16)(uVar9,iVar12,puVar5,0x1000);
          piVar15 = (int *)(uintptr_t)DAT_00030168;
          puVar7 = (undefined4 *)(uintptr_t)DAT_00030138;
          if (iVar8 != 0) {
            if (*piVar17 < 1) {
              return 0;
            }
            iVar12 = *DAT_0002fe7c;
            uVar9 = DAT_0002fc04;
            uVar10 = DAT_0002fbd8;
            goto LAB_0002fc9e;
          }
          uVar9 = crc32_update(*DAT_00030138,puVar5,*DAT_00030168);
          *puVar7 = uVar9;
          memset_bytes((uintptr_t)puVar5,0,0x1000);
          iVar8 = get_device_info(0);
          pcVar16 = *(code **)(iVar8 + 0x1030);
          uVar9 = get_device_info(0);
          iVar8 = (*pcVar16)(uVar9,0x400000,puVar5,0x1000);
          if (iVar8 != 0) {
            iVar12 = *piVar17;
            goto LAB_0002fa04;
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
              if (*DAT_00030140 == 0) {
                log_message(DAT_00030158,DAT_00030144);
              }
              else {
                debug_print(0);
              }
            }
            piVar15 = (int *)(uintptr_t)DAT_00030168;
            iVar8 = DAT_0003013c;
            iVar12 = (uint)*pbVar4 * 0x14 + DAT_0003013c;
            if (*(int *)(iVar12 + 0xc) == *(int *)(iVar12 + 0x10)) {
              if (2 < *piVar17) {
                if (*DAT_00030140 == 0) {
                  log_message(DAT_0003015c,DAT_00030144);
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
              iVar8 = *DAT_00030140;
              uVar9 = DAT_00030160;
              uVar10 = DAT_00030144;
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
                iVar12 = *DAT_00030140;
                uVar9 = DAT_0002fc04;
                uVar10 = DAT_0002fbd8;
                goto LAB_0002fc9e;
              }
              if (*piVar17 < 3) {
                return 0;
              }
              iVar8 = *DAT_00030140;
              uVar9 = DAT_00030164;
              uVar10 = DAT_00030144;
            }
            goto LAB_0002f986;
          }
        }
LAB_0002fe48:
        iVar12 = *piVar17;
        goto LAB_0002fa68;
      }
    }
    iVar8 = *piVar17;
  }
  if (iVar8 < 1) {
    return 0;
  }
  iVar8 = *piVar15;
  iVar12 = *DAT_0002fbd4;
  uVar9 = DAT_0002fbe8;
  uVar10 = DAT_0002fbd8;
LAB_0002fc9e:
  if (iVar12 == 0) {
    log_message(uVar9,uVar10,iVar8);
  }
  else {
    debug_print(0);
  }
  return 0;
}
