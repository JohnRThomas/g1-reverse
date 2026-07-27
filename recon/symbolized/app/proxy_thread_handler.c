#include "g1_app_symbols.h"
struct device;
/* readable reconstruction; identity: FUN_00047c48 @ 0x00047c48
 * public-name: proxy_thread_handler
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   upgradeAppLanguageInfoToFlash            <= FUN_00023af0 @ 0x00023af0
 *   upgradeDashboardStartupModeInfoToFlash   <= FUN_00023bfc @ 0x00023bfc
 *   get_ui_mode_flag2                        <= FUN_00023eec @ 0x00023eec
 *   atomic_exchange_proxy_scratch            <= FUN_0002f910 @ 0x0002f910
 *   z_log_dropped_read_and_clear             <= FUN_0002f928 @ 0x0002f928
 *   sendAudioStreamFileToApp                 <= FUN_00047bf8 @ 0x00047bf8
 *   display_powerEvent                       <= FUN_00049a28 @ 0x00049a28
 *   get_synced_clock_time                    <= FUN_0004a4d0 @ 0x0004a4d0
 *   k_msgq_get                               <= FUN_00072240 @ 0x00072240
 *   mutex_unlock_syscall_handler             <= FUN_000745c8 @ 0x000745c8
 *   k_sleep                                  <= FUN_00074844 @ 0x00074844
 *   z_device_is_ready                        <= FUN_0008638c @ 0x0008638c
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 *   safe_memcpy_checked                      <= FUN_00086c1e @ 0x00086c1e
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_28000                             @ 0x00028000
 *   rodata_87bf0                             @ 0x00087bf0
 *   rodata_9e9ea                             @ 0x0009e9ea
 *   rodata_9ea0a                             @ 0x0009ea0a
 *   rodata_a1027                             @ 0x000a1027   [INLINED -- G6 literal batch]
 *   rodata_a116d                             @ 0x000a116d   [INLINED -- G6 literal batch]
 *   rodata_a125e                             @ 0x000a125e   [INLINED -- G6 literal batch]
 *   rodata_ef081                             @ 0x000ef081
 *   rodata_ef0a1                             @ 0x000ef0a1   [INLINED -- G6 literal batch]
 *   rodata_ef0c9                             @ 0x000ef0c9   [INLINED -- G6 literal batch]
 *   rodata_ef0fb                             @ 0x000ef0fb
 *   rodata_ef135                             @ 0x000ef135   [INLINED -- G6 literal batch]
 *   rodata_ef16d                             @ 0x000ef16d   [INLINED -- G6 literal batch]
 *   rodata_ef1a8                             @ 0x000ef1a8   [INLINED -- G6 literal batch]
 *   rodata_ef1ea                             @ 0x000ef1ea   [INLINED -- G6 literal batch]
 *   rodata_ef214                             @ 0x000ef214
 *   rodata_ef260                             @ 0x000ef260   [INLINED -- G6 literal batch]
 *   rodata_ef29b                             @ 0x000ef29b
 *   rodata_ef2df                             @ 0x000ef2df   [INLINED -- G6 literal batch]
 *   rodata_ef2fc                             @ 0x000ef2fc   [INLINED -- G6 literal batch]
 *   rodata_ef338                             @ 0x000ef338   [INLINED -- G6 literal batch]
 *   rodata_ef377                             @ 0x000ef377   [INLINED -- G6 literal batch]
 *   rodata_ef3e2                             @ 0x000ef3e2
 *   rodata_ef40d                             @ 0x000ef40d   [INLINED -- G6 literal batch]
 *   rodata_ef437                             @ 0x000ef437   [INLINED -- G6 literal batch]
 *   rodata_ef472                             @ 0x000ef472   [INLINED -- G6 literal batch]
 *   rodata_ef76f                             @ 0x000ef76f
 *   g_log_level                              @ 0x2000230c
 *   g_dashboard_response_msgq                @ 0x2000392c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_20007b38                               @ 0x20007b38
 *   g_2000a078                               @ 0x2000a078
 *   g_2000a07c                               @ 0x2000a07c
 *   g_2000a080                               @ 0x2000a080
 *   g_2000a084                               @ 0x2000a084
 *   g_2000a088                               @ 0x2000a088
 *   g_2000a08c                               @ 0x2000a08c
 *   g_2000ff04                               @ 0x2000ff04
 *   g_20011d81                               @ 0x20011d81
 *   g_2001d262                               @ 0x2001d262
 *   g_2001d263                               @ 0x2001d263
 *   g_2001d264                               @ 0x2001d264
 *   g_2001d26a                               @ 0x2001d26a
 *   g_2001d26e                               @ 0x2001d26e
 *   g_2001d34a                               @ 0x2001d34a
 *   g_2001d34b                               @ 0x2001d34b
 *   g_2001d431                               @ 0x2001d431
 *   g_2001d432                               @ 0x2001d432
 */
/* Recovered proxy_thread_handler <= FUN_00047c48 @ 0x00047c48.
 * Reviewed image span is 0xbf8 bytes through 0x4883f.  The original catalog
 * stopped inside opcode seven at 0x486f8; live retry/default/atomic tails end
 * at 0x48815, followed by literals and independent FUN_00048840.
 * Durable reverse mapping: recon/catalogs/function_names_app.json.
 */
#include <stdint.h>

typedef uint8_t  undefined1;
typedef uint32_t undefined4;
typedef uint16_t ushort;
typedef uint8_t  byte;

typedef union {
    struct {
        uint8_t opcode;
        uint8_t reserved_01;
        uint16_t payload_length;
        int8_t subtype;
        int8_t value;
        uint8_t payload[18];
    } field;
    uint8_t bytes[24];
} proxy_message_t;

typedef union {
    struct {
        uint32_t low;
        uint32_t high;
    } word;
    uint64_t value;
    uint8_t bytes[8];
} proxy_transfer_packet_t;

typedef struct {
    uint8_t command;
    uint8_t value;
} proxy_short_packet_t;

/* Semantic aliases retain exact raw linker identities. */
#define get_device_info get_device_info
#define debug_print debug_print
#define upgrade_language_setting upgradeAppLanguageInfoToFlash
#define upgrade_dashboard_start_mode upgradeDashboardStartupModeInfoToFlash
#define get_pending_language_code get_ui_mode_flag2
#define set_current_audio_segment atomic_exchange_proxy_scratch
#define finish_audio_proxy_transfer z_log_dropped_read_and_clear
#define enqueue_proxy_progress sendAudioStreamFileToApp
#define display_power_event display_powerEvent
#define get_proxy_timestamp get_synced_clock_time
#define receive_proxy_message k_msgq_get
#define reschedule_after_power_event mutex_unlock_syscall_handler
#define wait_for_proxy_event k_sleep
#define device_is_ready z_device_is_ready
#define copy_bytes memcpy
#define checked_copy_bytes safe_memcpy_checked
#define clear_bytes memset_bytes

/* K&R prototypes are retained only at variadic/decompiler boundaries. */
extern void log_message(unsigned long, ...);
extern int get_device_info();
extern void debug_print(unsigned long, ...);
extern int upgrade_language_setting();
extern int upgrade_dashboard_start_mode();
extern int get_pending_language_code();
extern int set_current_audio_segment();
extern int finish_audio_proxy_transfer();
extern int enqueue_proxy_progress();
extern int display_power_event();
extern int get_proxy_timestamp();
extern int receive_proxy_message();
extern int reschedule_after_power_event();
extern int wait_for_proxy_event();
extern _Bool device_is_ready(const struct device *);
extern int copy_bytes();
extern int checked_copy_bytes();
extern int clear_bytes();
extern unsigned int change_work_mode_to(unsigned int);
extern int sync_to_slave();

void proxy_thread_handler(int param_1)
{
    int *piVar1;
    ushort *puVar2;
    byte *pbVar3;
    int *piVar4;
    int *piVar5;
    int *piVar6;
    int *piVar7;
    char *pcVar8;
    undefined4 uVar9;
    undefined1 *puVar10;
    char *pcVar11;
    int iVar12;
    undefined4 uVar13;
    undefined1 uVar14;
    int iVar15;
    int iVar16;
    int iVar17;
    ushort uVar18;
    int *piVar19;
    int (**pcVar20)();
    int iVar21;
    undefined1 *puVar22;
    char cVar23;
    proxy_short_packet_t short_packet;
    proxy_transfer_packet_t transfer_packet;
    proxy_message_t message;

    piVar1 = (int *)((unsigned long)&g_log_level) /*=0x2000230c*/;
    clear_bytes(message.bytes, 0, 0x18);
    if (*piVar1 < 3) goto LAB_00047c76;
    iVar16 = *(int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
    uVar9 = ((unsigned long)&rodata_ef081) /*=0xef081*/;
    uVar13 = ((unsigned long)&rodata_ef76f) /*=0xef76f*/;
LAB_00047c6a:
    if (iVar16 == 0) {
        log_message(uVar9, uVar13);
    } else {
        debug_print(uVar9, uVar13);
    }
LAB_00047c76:
    do {
        if ((*(char *)(param_1 + 1) != '\x01') && (*(char *)(param_1 + 1) != '\b')) {
            if (-1 < (int)((uint32_t)*(ushort *)(param_1 + 0x105c) << 0x18)) {
                uVar9 = 0x8000;
                goto LAB_00047c86;
            }
            clear_bytes(message.bytes, 0, 0x18);
            iVar16 = receive_proxy_message((void *)((unsigned long)&g_dashboard_response_msgq) /*=0x2000392c*/, message.bytes, 0xffffffff, 0xffffffff);
            cVar23 = message.field.subtype;
            if (iVar16 == 0) {
                switch (message.field.opcode) {
                case 0:
                    if (2 < *piVar1) {
                        if (*(int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                            log_message(((unsigned long)"%s(): store app response data to cache\n") /*=0xef0a1*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/);
                        } else {
                            debug_print(((unsigned long)"%s(): store app response data to cache\n") /*=0xef0a1*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/);
                        }
                    }
                    clear_bytes((void *)((unsigned long)&g_2001d432) /*=0x2001d432*/, 0, 0x14);
                    uVar18 = message.field.payload_length;
                    if (0x13 < message.field.payload_length) {
                        uVar18 = 0x14;
                    }
                    copy_bytes((void *)((unsigned long)&g_2001d432) /*=0x2001d432*/, &message.field.subtype, uVar18);
                    *(ushort *)((unsigned long)&g_2000ff04) /*=0x2000ff04*/ = uVar18;
                    *(char *)((unsigned long)&g_2001d431) /*=0x2001d431*/ = '\x01';
                    goto LAB_00047c76;
                case 1:
                    if (2 < *piVar1) {
                        if (*(int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                            log_message(((unsigned long)"%s(): received send response data to app command\n") /*=0xef0c9*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/);
                        } else {
                            debug_print(((unsigned long)"%s(): received send response data to app command\n") /*=0xef0c9*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/);
                        }
                    }
                    pcVar11 = (char *)((unsigned long)&g_2001d431) /*=0x2001d431*/;
                    puVar2 = (ushort *)((unsigned long)&g_2000ff04) /*=0x2000ff04*/;
                    if (*(char *)((unsigned long)&g_2001d431) /*=0x2001d431*/ != '\0') {
                        iVar16 = (*(int (**)())(param_1 + 0x788))((void *)((unsigned long)&g_2001d432) /*=0x2001d432*/, *(ushort *)((unsigned long)&g_2000ff04) /*=0x2000ff04*/);
                        if ((iVar16 < 0) && (1 < *piVar1)) {
                            if (*(int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                                log_message(((unsigned long)&rodata_ef0fb) /*=0xef0fb*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/);
                            } else {
                                debug_print(((unsigned long)&rodata_ef0fb) /*=0xef0fb*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/);
                            }
                        }
                        transfer_packet.value = 0;
                        get_proxy_timestamp(transfer_packet.bytes);
                        if (2 < *piVar1) {
                            if (*(int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                                log_message(((unsigned long)"%s(): success send cache data to app ,diff_time = %lld\n") /*=0xef135*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/,
                                            transfer_packet.word.low,
                                            transfer_packet.word.high);
                            } else {
                                debug_print(((unsigned long)"%s(): success send cache data to app ,diff_time = %lld\n") /*=0xef135*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/);
                            }
                        }
                        *pcVar11 = '\0';
                        *puVar2 = 0;
                    }
                    goto LAB_00047c76;
                case 2:
                    if (2 < *piVar1) {
                        if (*(int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                            log_message(((unsigned long)"%s(): running proxy thread,send audio stream data to app \n") /*=0xef16d*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/);
                        } else {
                            debug_print(((unsigned long)"%s(): running proxy thread,send audio stream data to app \n") /*=0xef16d*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/);
                        }
                    }
                    pcVar8 = (char *)((unsigned long)&g_2001d263) /*=0x2001d263*/;
                    piVar7 = (int *)((unsigned long)&g_2000a080) /*=0x2000a080*/;
                    piVar6 = (int *)((unsigned long)&g_2000a078) /*=0x2000a078*/;
                    pcVar11 = (char *)((unsigned long)&g_2001d262) /*=0x2001d262*/;
                    piVar5 = (int *)((unsigned long)&g_2000a07c) /*=0x2000a07c*/;
                    piVar4 = (int *)((unsigned long)&g_2000a084) /*=0x2000a084*/;
                    piVar19 = (int *)((unsigned long)&g_2000a08c) /*=0x2000a08c*/;
                    pbVar3 = (byte *)((unsigned long)&g_2001d34a) /*=0x2001d34a*/;
                    if (message.field.subtype == '\0') {
                        *(byte *)((unsigned long)&g_2001d34a) /*=0x2001d34a*/ = message.field.value - 1;
                        piVar19 = (int *)((unsigned long)&rodata_87bf0) /*=0x87bf0*/;
                        iVar16 = device_is_ready((void *)((unsigned long)&rodata_87bf0) /*=0x87bf0*/);
                        piVar4 = (int *)((unsigned long)&g_2001d34b) /*=0x2001d34b*/;
                        if (iVar16 == 0) goto LAB_00047de2;
                        clear_bytes((void *)((unsigned long)&g_2001d34b) /*=0x2001d34b*/, 0, 0xe6);
                        iVar16 = get_device_info();
                        pcVar20 = *(int (***)())(iVar16 + 0x1030);
                        uVar9 = get_device_info();
                        iVar16 = (*pcVar20)(uVar9, 0x400000, piVar4, 0xe6);
                        piVar19 = (int *)((unsigned long)&g_2000a08c) /*=0x2000a08c*/;
                        if (iVar16 == 0) {
                            if ((*piVar4 == 0x5aa5aa5a) && (piVar4[(uint32_t)*pbVar3 * 5 + 2] == 2)) {
                                *(int *)((unsigned long)&g_2000a08c) /*=0x2000a08c*/ = piVar4[(uint32_t)*pbVar3 * 5 + 3];
                                *(int *)((unsigned long)&g_2000a088) /*=0x2000a088*/ = piVar4[(uint32_t)*pbVar3 * 5 + 4];
                            }
                            if (2 < *piVar1) {
                                if (*(int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                                    log_message(((unsigned long)"%s(): read voice manager block data,start send voice data to app\n") /*=0xef1a8*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/);
                                } else {
                                    debug_print(((unsigned long)"%s(): read voice manager block data,start send voice data to app\n") /*=0xef1a8*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/);
                                }
                            }
                            clear_bytes((void *)((unsigned long)&g_2001d34b) /*=0x2001d34b*/, 0, 0xe6);
                            iVar16 = get_device_info();
                            pcVar20 = *(int (***)())(iVar16 + 0x1030);
                            uVar9 = get_device_info();
                            iVar16 = (*pcVar20)(uVar9, *piVar19, (void *)((unsigned long)&g_2001d34b) /*=0x2001d34b*/, 0xbe);
                            piVar5 = (int *)((unsigned long)&g_2000a084) /*=0x2000a084*/;
                            piVar4 = (int *)((unsigned long)&g_2000a088) /*=0x2000a088*/;
                            if (iVar16 == 0) {
                                *(int *)((unsigned long)&g_2000a084) /*=0x2000a084*/ = (*(int *)((unsigned long)&g_2000a088) /*=0x2000a088*/ - *piVar19) / 0xbe;
                                iVar16 = *piVar4 - *piVar19;
                                if (iVar16 != (iVar16 / 0xbe) * 0xbe) {
                                    *piVar5 = *piVar5 + 1;
                                }
                                pcVar11 = (char *)((unsigned long)&g_2001d263) /*=0x2001d263*/;
                                piVar7 = (int *)((unsigned long)&g_2000a080) /*=0x2000a080*/;
                                piVar6 = (int *)((unsigned long)&g_2000a078) /*=0x2000a078*/;
                                piVar5 = (int *)((unsigned long)&g_2000a07c) /*=0x2000a07c*/;
                                puVar10 = (undefined1 *)((unsigned long)&g_2001d264) /*=0x2001d264*/;
                                *(int *)((unsigned long)&g_2000a080) /*=0x2000a080*/ = *piVar4 - *piVar19;
                                *pcVar11 = '\0';
                                *piVar5 = 0;
                                *piVar6 = 0;
                                clear_bytes(puVar10, 0, 0xe6);
                                *puVar10 = 0x1e;
                                puVar10[2] = 0;
                                piVar19 = (int *)((unsigned long)&g_2000a084) /*=0x2000a084*/;
                                puVar10[3] = *pcVar11;
                                uVar9 = ((unsigned long)&g_2001d34b) /*=0x2001d34b*/;
                                *pcVar11 = *pcVar11 + '\x01';
                                puVar10[4] = 2;
                                iVar16 = 3;
                                puVar10[5] = (char)*piVar19;
                                uVar13 = ((unsigned long)&g_2001d26e) /*=0x2001d26e*/;
                                puVar10[6] = (char)((uint32_t)*piVar19 >> 8);
                                puVar22 = (undefined1 *)((unsigned long)&g_2001d264) /*=0x2001d264*/;
                                *piVar5 = *piVar5 + 1;
                                puVar10[7] = (char)*piVar5;
                                puVar10[8] = (char)((uint32_t)*piVar5 >> 8);
                                puVar10[9] = *pbVar3 + 1;
                                piVar19 = (int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
                                if (*piVar7 - *piVar6 < 0xbe) {
                                    iVar12 = *piVar7 - *piVar6;
                                } else {
                                    iVar12 = 0xbe;
                                }
                                checked_copy_bytes(uVar13, uVar9, iVar12, 0xdc);
                                puVar10[1] = (char)iVar12 + '\n';
                                while (iVar15 = (*(int (**)())(param_1 + 0x788))(puVar22, puVar10[1]), iVar15 < 0) {
                                    if (1 < *piVar1) {
                                        if (*piVar19 == 0) {
                                            log_message(((unsigned long)"%s(): retry send audio data first packet\n") /*=0xef1ea*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/);
                                        } else {
                                            debug_print(((unsigned long)"%s(): retry send audio data first packet\n") /*=0xef1ea*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/);
                                        }
                                    }
                                    iVar16 = iVar16 + -1;
                                    if (iVar16 == 0) {
                                        if (*piVar1 < 2) goto LAB_00047c76;
                                        iVar16 = *(int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
                                        uVar9 = ((unsigned long)&rodata_ef214) /*=0xef214*/;
                                        uVar13 = ((unsigned long)&rodata_ef76f) /*=0xef76f*/;
                                        goto LAB_00047c6a;
                                    }
                                    if (1 < *piVar1) {
                                        if (*piVar19 == 0) {
                                            log_message(((unsigned long)&rodata_ef214) /*=0xef214*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/);
                                        } else {
                                            debug_print(((unsigned long)&rodata_ef214) /*=0xef214*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/);
                                        }
                                    }
                                }
                                *(char *)((unsigned long)&g_2001d262) /*=0x2001d262*/ = '\x01';
                                *piVar6 = *piVar6 + iVar12;
                                set_current_audio_segment(*pbVar3);
                                goto LAB_00048054;
                            }
                        }
LAB_00047e22:
                        if (0 < *piVar1) {
                            iVar16 = 0x400000;
                            iVar12 = *(int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
                            uVar9 = ((unsigned long)&rodata_9ea0a) /*=0x9ea0a*/;
                            uVar13 = ((unsigned long)&rodata_ef76f) /*=0xef76f*/;
                            goto LAB_00047e36;
                        }
                        goto LAB_00047c76;
                    }
                    if (message.field.subtype != '\x01') goto LAB_00047c76;
                    if (*(char *)((unsigned long)&g_2001d262) /*=0x2001d262*/ == '\0') {
                        if (2 < *piVar1) {
                            if (*(int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                                log_message(((unsigned long)"%s(): error packet order,can't send any audio data to app\n") /*=0xef260*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/);
                            } else {
                                debug_print(((unsigned long)"%s(): error packet order,can't send any audio data to app\n") /*=0xef260*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/);
                            }
                        }
LAB_00048082:
                        finish_audio_proxy_transfer();
                        goto LAB_00047c76;
                    }
                    if (*(int *)((unsigned long)&g_2000a078) /*=0x2000a078*/ < *(int *)((unsigned long)&g_2000a080) /*=0x2000a080*/) {
                        clear_bytes((void *)((unsigned long)&g_2001d264) /*=0x2001d264*/, 0, 0xe6);
                        puVar10 = (undefined1 *)((unsigned long)&g_2001d264) /*=0x2001d264*/;
                        if (*(int *)((unsigned long)&g_2000a080) /*=0x2000a080*/ - *piVar6 < 0xbe) {
                            iVar16 = 0;
                            if (*(int *)((unsigned long)&g_2000a080) /*=0x2000a080*/ - *piVar6 < 0xbe) {
                                iVar16 = *(int *)((unsigned long)&g_2000a080) /*=0x2000a080*/ - *piVar6;
                            }
                        } else {
                            iVar16 = 0xbe;
                        }
                        *(undefined1 *)((unsigned long)&g_2001d264) /*=0x2001d264*/ = 0x1e;
                        puVar10[1] = (char)iVar16 + '\n';
                        puVar10[2] = 0;
                        uVar9 = ((unsigned long)&g_2001d34b) /*=0x2001d34b*/;
                        puVar10[3] = *pcVar8;
                        *pcVar8 = *pcVar8 + '\x01';
                        puVar10[4] = 2;
                        puVar10[5] = (char)*piVar4;
                        puVar10[6] = (char)((uint32_t)*piVar4 >> 8);
                        *piVar5 = *piVar5 + 1;
                        puVar10[7] = (char)*piVar5;
                        piVar4 = (int *)((unsigned long)&g_2000a078) /*=0x2000a078*/;
                        puVar10[8] = (char)((uint32_t)*piVar5 >> 8);
                        puVar10[9] = *(char *)((unsigned long)&g_2001d34a) /*=0x2001d34a*/ + '\x01';
                        clear_bytes(uVar9, 0, 0xe6);
                        iVar12 = get_device_info();
                        pcVar20 = *(int (***)())(iVar12 + 0x1030);
                        uVar9 = get_device_info();
                        iVar12 = (*pcVar20)(uVar9, *piVar4 + *piVar19, (void *)((unsigned long)&g_2001d34b) /*=0x2001d34b*/, iVar16);
                        if (iVar12 != 0) {
                            if (0 < *piVar1) {
                                if (*(int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                                    log_message(((unsigned long)&rodata_9ea0a) /*=0x9ea0a*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/, 0x400000);
                                } else {
                                    debug_print(((unsigned long)&rodata_9ea0a) /*=0x9ea0a*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/, 0x400000);
                                }
                            }
LAB_0004820e:
                            *pcVar11 = '\0';
                            goto LAB_00048082;
                        }
                        checked_copy_bytes(puVar10 + 10, (void *)((unsigned long)&g_2001d34b) /*=0x2001d34b*/, iVar16, 0xdc);
                        piVar19 = (int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
                        iVar12 = 3;
                        while (iVar15 = (*(int (**)())(param_1 + 0x788))(puVar10, puVar10[1]), iVar15 < 0) {
                            if (1 < *piVar1) {
                                if (*piVar19 == 0) {
                                    log_message(((unsigned long)"%s(): retry send audio data\n") /*=0xef2df*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/);
                                } else {
                                    debug_print(((unsigned long)"%s(): retry send audio data\n") /*=0xef2df*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/);
                                }
                            }
                            iVar12 = iVar12 + -1;
                            if (iVar12 == 0) {
                                if (1 < *piVar1) {
                                    if (*(int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                                        log_message(((unsigned long)&rodata_ef214) /*=0xef214*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/);
                                    } else {
                                        debug_print(((unsigned long)&rodata_ef214) /*=0xef214*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/);
                                    }
                                }
                                goto LAB_0004820e;
                            }
                            if (1 < *piVar1) {
                                if (*piVar19 == 0) {
                                    log_message(((unsigned long)"%s(): retry send audio data\n") /*=0xef2df*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/);
                                } else {
                                    debug_print(((unsigned long)"%s(): retry send audio data\n") /*=0xef2df*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/);
                                }
                            }
                        }
                        *piVar4 = *piVar4 + iVar16;
                        if (2 < *piVar1) {
                            if (*(int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                                log_message(((unsigned long)"%s(): send %d byte data to app,total send data length = %d\n") /*=0xef2fc*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/, iVar16, *piVar4);
                            } else {
                                debug_print(((unsigned long)"%s(): send %d byte data to app,total send data length = %d\n") /*=0xef2fc*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/, iVar16, *piVar4);
                            }
                        }
LAB_00048054:
                        enqueue_proxy_progress(1, 0);
                        goto LAB_00047c76;
                    }
                    *(char *)((unsigned long)&g_2001d262) /*=0x2001d262*/ = '\0';
                    *piVar4 = 0;
                    *piVar7 = 0;
                    piVar4 = (int *)((unsigned long)&g_2000a088) /*=0x2000a088*/;
                    *piVar6 = 0;
                    *pcVar8 = '\0';
                    *piVar5 = 0;
                    *piVar4 = 0;
                    *piVar19 = 0;
                    finish_audio_proxy_transfer();
                    if (*piVar1 < 1) goto LAB_00047c76;
                    if (*(int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                        iVar16 = get_device_info();
                        iVar16 = **(int **)(iVar16 + 0xfec);
                        uVar9 = ((unsigned long)&rodata_ef29b) /*=0xef29b*/;
                        uVar13 = ((unsigned long)&rodata_ef76f) /*=0xef76f*/;
                        goto LAB_000480f4;
                    }
                    iVar16 = get_device_info();
                    iVar16 = **(int **)(iVar16 + 0xfec);
                    uVar9 = ((unsigned long)&rodata_ef29b) /*=0xef29b*/;
                    uVar13 = ((unsigned long)&rodata_ef76f) /*=0xef76f*/;
                    break;
                case 3:
                    if (2 < *piVar1) {
                        if (*(int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                            log_message(((unsigned long)"%s(): running proxy thread,send audio infomation data to app \n") /*=0xef338*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/);
                        } else {
                            debug_print(((unsigned long)"%s(): running proxy thread,send audio infomation data to app \n") /*=0xef338*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/);
                        }
                    }
                    piVar19 = (int *)((unsigned long)&rodata_87bf0) /*=0x87bf0*/;
                    iVar16 = device_is_ready((void *)((unsigned long)&rodata_87bf0) /*=0x87bf0*/);
                    if (iVar16 == 0) {
LAB_00047de2:
                        if (*piVar1 < 1) goto LAB_00047c76;
                        iVar16 = *piVar19;
                        iVar12 = *(int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
                        uVar9 = ((unsigned long)&rodata_9e9ea) /*=0x9e9ea*/;
                        uVar13 = ((unsigned long)&rodata_ef76f) /*=0xef76f*/;
                    } else {
                        clear_bytes((void *)((unsigned long)&g_2001d34b) /*=0x2001d34b*/, 0, 0xe6);
                        iVar16 = get_device_info();
                        pcVar20 = *(int (***)())(iVar16 + 0x1030);
                        uVar9 = get_device_info();
                        iVar16 = (*pcVar20)(uVar9, 0x400000, (void *)((unsigned long)&g_2001d34b) /*=0x2001d34b*/, 0xe6);
                        if (iVar16 != 0) goto LAB_00047e22;
                        puVar10 = (undefined1 *)clear_bytes((void *)((unsigned long)&g_2001d264) /*=0x2001d264*/, 0, 0xe6);
                        pcVar11 = (char *)((unsigned long)&g_2001d263) /*=0x2001d263*/;
                        if (message.field.subtype == '\0') {
                            uVar14 = 0x1e;
                        } else {
                            uVar14 = 0x21;
                        }
                        *puVar10 = uVar14;
                        puVar10[2] = 0;
                        cVar23 = '\0';
                        puVar10[3] = *pcVar11;
                        *pcVar11 = *pcVar11 + '\x01';
                        puVar22 = (undefined1 *)((unsigned long)&g_2001d26a) /*=0x2001d26a*/;
                        iVar16 = ((unsigned long)&g_2001d34b) /*=0x2001d34b*/;
                        puVar10[4] = 1;
                        iVar12 = 0;
                        do {
                            iVar15 = iVar12 * 0x14 + iVar16;
                            iVar21 = iVar12 + 1;
                            if (2 < *piVar1) {
                                iVar17 = *(int *)(iVar15 + 0xc);
                                if (*(int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                                    uVar9 = 0xef077;
                                    if (*(int *)(iVar15 + 8) != 2) {
                                        uVar9 = 0xef07c;
                                    }
                                    log_message(((unsigned long)"%s(): voice %d %s, timestamp = %d,crc32 = 0x%x start addr = %d,end addr = %d,total audio stream size = %d\n") /*=0xef377*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/, iVar21, uVar9, *(undefined4 *)(iVar15 + 0x14),
                                                *(undefined4 *)(iVar15 + 0x18), iVar17, *(int *)(iVar15 + 0x10),
                                                *(int *)(iVar15 + 0x10) - iVar17);
                                } else {
                                    uVar9 = 0xef077;
                                    if (*(int *)(iVar15 + 8) != 2) {
                                        uVar9 = 0xef07c;
                                    }
                                    debug_print(((unsigned long)"%s(): voice %d %s, timestamp = %d,crc32 = 0x%x start addr = %d,end addr = %d,total audio stream size = %d\n") /*=0xef377*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/, iVar21, uVar9, *(undefined4 *)(iVar15 + 0x14),
                                                 *(undefined4 *)(iVar15 + 0x18), iVar17, *(int *)(iVar15 + 0x10),
                                                 *(int *)(iVar15 + 0x10) - iVar17);
                                }
                            }
                            iVar12 = iVar12 * 0x14 + iVar16;
                            puVar10 = puVar22;
                            if (*(int *)(iVar12 + 8) == 2) {
                                *puVar22 = (char)iVar21;
                                uVar9 = *(undefined4 *)(iVar12 + 0x14);
                                cVar23 = cVar23 + '\x01';
                                puVar22[1] = (char)uVar9;
                                puVar22[2] = (char)((uint32_t)uVar9 >> 8);
                                puVar22[3] = (char)((uint32_t)uVar9 >> 0x10);
                                puVar22[4] = (char)((uint32_t)uVar9 >> 0x18);
                                uVar9 = *(undefined4 *)(iVar12 + 0x18);
                                puVar10 = puVar22 + 9;
                                puVar22[5] = (char)uVar9;
                                puVar22[6] = (char)((uint32_t)uVar9 >> 8);
                                puVar22[7] = (char)((uint32_t)uVar9 >> 0x10);
                                puVar22[8] = (char)((uint32_t)uVar9 >> 0x18);
                            }
                            iVar15 = ((unsigned long)&g_2001d264) /*=0x2001d264*/;
                            iVar12 = iVar21;
                            puVar22 = puVar10;
                        } while (iVar21 != 4);
                        *(char *)(((unsigned long)&g_2001d264) /*=0x2001d264*/ + 1) = cVar23 * '\t' + '\x06';
                        piVar19 = (int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
                        *(char *)(iVar15 + 5) = cVar23;
                        uVar13 = ((unsigned long)&rodata_ef3e2) /*=0xef3e2*/;
                        uVar9 = ((unsigned long)&rodata_ef76f) /*=0xef76f*/;
                        for (iVar16 = 0; iVar16 < (int)(uint32_t)*(byte *)(iVar15 + 1); iVar16 = iVar16 + 1) {
                            if (3 < *piVar1) {
                                if (*piVar19 == 0) {
                                    log_message(uVar13, uVar9, iVar16, (uint32_t)*(byte *)(iVar15 + iVar16));
                                } else {
                                    debug_print(uVar13, uVar9, iVar16, *(undefined1 *)(iVar15 + iVar16));
                                }
                            }
                        }
                        iVar16 = (*(int (**)())(param_1 + 0x788))((void *)((unsigned long)&g_2001d264) /*=0x2001d264*/, *(undefined1 *)(iVar15 + 1));
                        if ((-1 < iVar16) || (*piVar1 < 2)) goto LAB_00047c76;
                        iVar12 = *(int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
                        uVar9 = ((unsigned long)&rodata_ef0fb) /*=0xef0fb*/;
                        uVar13 = ((unsigned long)&rodata_ef76f) /*=0xef76f*/;
                    }
LAB_00047e36:
                    if (iVar12 == 0) {
LAB_000480f4:
                        log_message(uVar9, uVar13, iVar16);
                        goto LAB_00047c76;
                    }
                    break;
                case 4:
                    iVar16 = 1;
                    *(uint16_t *)transfer_packet.bytes =
                        ((uint16_t)(uint8_t)message.field.subtype << 8) | 7;
                    do {
                        uVar9 = get_device_info();
                        iVar12 = sync_to_slave(uVar9, 6,
                                              transfer_packet.bytes, 2);
                        if (iVar12 < 5000) {
                            if (2 < *piVar1) {
                                if (*(int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                                    log_message(((unsigned long)"%s(): SEND power event to slave success.\n") /*=0xef40d*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/);
                                } else {
                                    debug_print(((unsigned long)"%s(): SEND power event to slave success.\n") /*=0xef40d*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/);
                                }
                            }
                            display_power_event(cVar23);
                            reschedule_after_power_event();
                            break;
                        }
                        if (1 < *piVar1) {
                            if (*(int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                                log_message(((unsigned long)"%s(): SYNC TO Slave failed % times,don't exec quick note start function.\n") /*=0xa125e*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/, iVar16);
                            } else {
                                debug_print(((unsigned long)"%s(): SYNC TO Slave failed % times,don't exec quick note start function.\n") /*=0xa125e*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/, iVar16);
                            }
                        }
                        iVar16 = iVar16 + 1;
                    } while (iVar16 != 4);
                    goto LAB_00047c76;
                case 5:
                    iVar16 = 1;
                    *(uint16_t *)transfer_packet.bytes =
                        ((uint16_t)(uint8_t)message.field.subtype << 8) | 8;
                    do {
                        uVar9 = get_device_info();
                        iVar12 = sync_to_slave(uVar9, 6,
                                              transfer_packet.bytes, 2);
                        if (iVar12 < 5000) {
                            if (2 < *piVar1) {
                                if (*(int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                                    log_message(((unsigned long)"%s(): Send app language upgrade msg to setting proxy task\n") /*=0xef437*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/);
                                } else {
                                    debug_print(((unsigned long)"%s(): Send app language upgrade msg to setting proxy task\n") /*=0xef437*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/);
                                }
                            }
                            upgrade_language_setting(cVar23);
                            break;
                        }
                        if (1 < *piVar1) {
                            if (*(int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                                log_message(((unsigned long)"%s(): SYNC TO Slave failed % times,don't exec quick note start function.\n") /*=0xa125e*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/, iVar16);
                            } else {
                                debug_print(((unsigned long)"%s(): SYNC TO Slave failed % times,don't exec quick note start function.\n") /*=0xa125e*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/, iVar16);
                            }
                        }
                        iVar16 = iVar16 + 1;
                    } while (iVar16 != 4);
                    goto LAB_00047c76;
                case 6:
                    iVar16 = 1;
                    short_packet.command = 9;
                    short_packet.value = message.field.subtype;
                    do {
                        uVar9 = get_device_info();
                        iVar12 = sync_to_slave(uVar9, 6, &short_packet, 2);
                        if (iVar12 < 5000) {
                            if (2 < *piVar1) {
                                if (*(int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                                    log_message(((unsigned long)"%s(): Send Dashboard startup  mode  msg to setting proxy task\n") /*=0xef472*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/);
                                } else {
                                    debug_print(((unsigned long)"%s(): Send Dashboard startup  mode  msg to setting proxy task\n") /*=0xef472*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/);
                                }
                            }
                            transfer_packet.word.low =
                                ((uint32_t)(uint8_t)*(char *)((unsigned long)&g_20011d81) /*=0x20011d81*/ << 24) |
                                0x608;
                            transfer_packet.word.high =
                                (((uint32_t)((uint16_t)transfer_packet.word.high << 16) |
                                  ((uint8_t)cVar23 << 8)) & 0xffffff00) | 3;
                            iVar16 = (*(int (**)())(param_1 + 0x788))(
                                transfer_packet.bytes, 6);
                            if ((iVar16 < 0) && (1 < *piVar1)) {
                                if (*(int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                                    log_message(((unsigned long)&rodata_ef0fb) /*=0xef0fb*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/);
                                } else {
                                    debug_print(((unsigned long)&rodata_ef0fb) /*=0xef0fb*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/);
                                }
                            }
                            upgrade_dashboard_start_mode(cVar23);
                            break;
                        }
                        if (1 < *piVar1) {
                            if (*(int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                                log_message(((unsigned long)"%s(): SYNC TO Slave failed % times,don't exec quick note start function.\n") /*=0xa125e*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/, iVar16);
                            } else {
                                debug_print(((unsigned long)"%s(): SYNC TO Slave failed % times,don't exec quick note start function.\n") /*=0xa125e*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/, iVar16);
                            }
                        }
                        iVar16 = iVar16 + 1;
                    } while (iVar16 != 4);
                    goto LAB_00047c76;
                case 7:
                    iVar16 = get_pending_language_code();
                    if (((iVar16 == 1) && (iVar16 = get_device_info(), *(char *)(iVar16 + 0xd5) == '\0')) &&
                        (pcVar11 = (char *)get_device_info(), *pcVar11 == '\x01')) {
                        iVar16 = get_device_info();
                        *(undefined1 *)(iVar16 + 0xfe6) = 5;
                        iVar16 = get_device_info();
                        iVar12 = get_device_info();
                        piVar19 = (int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
                        *(undefined1 *)(iVar12 + 0xcb) = *(undefined1 *)(iVar16 + 0xed5);
                        uVar9 = get_device_info();
                        sync_to_slave(uVar9, 2, 0, 0);
                        change_work_mode_to(2);
                        *(uint16_t *)transfer_packet.bytes = 0x10a;
                        iVar16 = 1;
                        do {
                            uVar9 = get_device_info();
                            iVar12 = sync_to_slave(uVar9, 6,
                                                  transfer_packet.bytes, 2);
                            if (iVar12 < 5000) {
                                if (2 < *piVar1) {
                                    if (*(int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                                        log_message(((unsigned long)"%s(): SEND DELAY CLOSE TO SLAVE SUCCESS,master start delay close function\n") /*=0xa116d*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/);
                                    } else {
                                        debug_print(((unsigned long)"%s(): SEND DELAY CLOSE TO SLAVE SUCCESS,master start delay close function\n") /*=0xa116d*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/);
                                    }
                                }
                                *(int *)((unsigned long)&g_20007b38) /*=0x20007b38*/ = *(int *)((unsigned long)&g_20007b38) /*=0x20007b38*/ | 2;
                                break;
                            }
                            if (1 < *piVar1) {
                                if (*piVar19 == 0) {
                                    log_message(((unsigned long)"%s(): SYNC TO Slave failed % times,don't exec double click startup dashboard function.\n") /*=0xa1027*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/, iVar16);
                                } else {
                                    debug_print(((unsigned long)"%s(): SYNC TO Slave failed % times,don't exec double click startup dashboard function.\n") /*=0xa1027*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/, iVar16);
                                }
                            }
                            iVar16 = iVar16 + 1;
                        } while (iVar16 != 4);
                    }
                    iVar16 = get_pending_language_code();
                    if ((((iVar16 == 1) && (iVar16 = get_device_info(), *(char *)(iVar16 + 0xd5) == '\x06')) ||
                         ((iVar16 = get_pending_language_code(), iVar16 == 2 &&
                          (iVar16 = get_device_info(), *(char *)(iVar16 + 0xd5) == '\x06')))) &&
                        (pcVar11 = (char *)get_device_info(), piVar19 = (int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/, *pcVar11 == '\x01')) {
                        *(uint16_t *)transfer_packet.bytes = 0x10a;
                        iVar16 = 1;
                        do {
                            uVar9 = get_device_info();
                            iVar12 = sync_to_slave(uVar9, 6,
                                                  transfer_packet.bytes, 2);
                            if (iVar12 < 5000) {
                                if (2 < *piVar1) {
                                    if (*(int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                                        log_message(((unsigned long)"%s(): SEND DELAY CLOSE TO SLAVE SUCCESS,master start delay close function\n") /*=0xa116d*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/);
                                    } else {
                                        debug_print(((unsigned long)"%s(): SEND DELAY CLOSE TO SLAVE SUCCESS,master start delay close function\n") /*=0xa116d*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/);
                                    }
                                }
                                *(int *)((unsigned long)&g_20007b38) /*=0x20007b38*/ = *(int *)((unsigned long)&g_20007b38) /*=0x20007b38*/ | 2;
                                break;
                            }
                            if (1 < *piVar1) {
                                if (*piVar19 == 0) {
                                    log_message(((unsigned long)"%s(): SYNC TO Slave failed % times,don't exec double click startup dashboard function.\n") /*=0xa1027*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/, iVar16);
                                } else {
                                    debug_print(((unsigned long)"%s(): SYNC TO Slave failed % times,don't exec double click startup dashboard function.\n") /*=0xa1027*/, ((unsigned long)&rodata_ef76f) /*=0xef76f*/, iVar16);
                                }
                            }
                            iVar16 = iVar16 + 1;
                        } while (iVar16 != 4);
                    }
                    goto LAB_00047c76;
                default:
                    goto switchD_00047ccc_caseD_8;
                }
                debug_print(uVar9, uVar13, iVar16);
            }
            goto LAB_00047c76;
        }
        uVar9 = ((unsigned long)&rodata_28000) /*=0x28000*/;
LAB_00047c86:
        wait_for_proxy_event(uVar9, 0);
    } while (1);
switchD_00047ccc_caseD_8:
    if (0 < *piVar1) goto code_r0x0004880a;
    goto LAB_00047c76;
code_r0x0004880a:
    iVar16 = *(int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
    uVar9 = 0xef4b1;
    uVar13 = ((unsigned long)&rodata_ef76f) /*=0xef76f*/;
    goto LAB_00047c6a;
}
