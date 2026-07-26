/* readable reconstruction; identity: FUN_0002ed68 @ 0x0002ed68
 * public-name: app_codec_lc3_test
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   enqueue_dmic                             <= FUN_0002ec5c @ 0x0002ec5c
 *   app_codec_lc3_test                       <= FUN_0002ed68 @ 0x0002ed68
 *   sendAudioStram2Cache                     <= FUN_0002f6b0 @ 0x0002f6b0
 *   is_battery_critical                      <= FUN_00032ee4 @ 0x00032ee4
 *   get_synced_clock_time                    <= FUN_0004a4d0 @ 0x0004a4d0
 *   qspi_nor_write                           <= FUN_00060f20 @ 0x00060f20
 *   lc3_frame_samples                        <= FUN_00068e40 @ 0x00068e40
 *   lc3_encoder_size                         <= FUN_00068ecc @ 0x00068ecc
 *   lc3_setup_encoder                        <= FUN_00068f94 @ 0x00068f94
 *   lc3_encode                               <= FUN_00069238 @ 0x00069238
 *   malloc                                   <= FUN_00076d6c @ 0x00076d6c
 *   free                                     <= FUN_00076d7c @ 0x00076d7c
 *   z_device_is_ready                        <= FUN_0008638c @ 0x0008638c
 * address symbols (name @ address):
 *   rodata_87bf0                             @ 0x00087bf0
 *   rodata_87bf8                             @ 0x00087bf8
 *   rodata_9e9ea                             @ 0x0009e9ea
 *   rodata_9ebc6                             @ 0x0009ebc6
 *   rodata_a3f7f                             @ 0x000a3f7f   [INLINED -- G6 literal batch]
 *   rodata_a3fbe                             @ 0x000a3fbe   [INLINED -- G6 literal batch]
 *   rodata_a3fdf                             @ 0x000a3fdf   [INLINED -- G6 literal batch]
 *   rodata_a41c2                             @ 0x000a41c2   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_audio_flash_write_offset               @ 0x20002404
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_pending_event_word                     @ 0x20007b78
 */
/* Reconstructed FUN_0002ed68 @ 0x2ed68  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "../headers/g1_log.h"
typedef unsigned int uint;
typedef unsigned undefined4;
extern void enqueue_dmic(int a);
extern void sendAudioStram2Cache(int a);
extern int is_battery_critical(void);
extern void get_synced_clock_time(void *a);
extern unsigned qspi_nor_write(void);
extern int lc3_frame_samples(int a, int b);
extern unsigned lc3_encoder_size(int a, int b);
extern unsigned lc3_setup_encoder(int a, int b, int c, int d);
extern int lc3_encode(unsigned a, int b, int c, int d, int e, int f, unsigned g, int h);
extern int malloc(unsigned a);
extern void free(int a);
extern int z_device_is_ready(int a);

void app_codec_lc3_test(int param_1, int param_2)
{
    volatile int *v = (volatile int *)0x2000230c;
    volatile int *dbg = (volatile int *)0x20007554;
    volatile int *S = (volatile int *)0x00087bf0;
    volatile uint *puVar2v = (volatile uint *)0x20002404;
    int *piVar1;
    uint *puVar2;
    unsigned uVar3;
    uint uVar4;
    int iVar5, iVar6, iVar7, iVar8, iVar9, iVar10, iVar11;
    struct codec_statistics { unsigned first, second; } local_stats;

    uVar3 = lc3_encoder_size(10000, 16000);
    uVar4 = lc3_frame_samples(10000, 16000);
    iVar5 = malloc(uVar3);
    iVar11 = (uVar4 & 0x7fff) * 2;
    iVar6 = malloc(iVar11);
    iVar10 = (param_2 / iVar11 & 0xffffU) * 0x14;
    iVar7 = malloc(iVar10);
    if (iVar5 == 0) {
        if (0 < *v) {
            if (*dbg == 0) log_message(((unsigned long)"%s(): malloc error\r\n\n"), ((unsigned long)"app_codec_lc3_test"));
            else debug_print(((unsigned long)"%s(): malloc error\r\n\n"), ((unsigned long)"app_codec_lc3_test"));
        }
LAB_0002edf8:
        iVar5 = iVar6;
        if (iVar6 != 0) goto LAB_0002ede2;
    } else {
        if (iVar6 != 0) {
            if (iVar7 != 0) {
                iVar8 = is_battery_critical();
                piVar1 = (int *)S;
                if ((iVar8 == 1) && (iVar8 = z_device_is_ready(0x87bf0), iVar8 == 0)) {
                    if (0 < *v) {
                        iVar9 = *piVar1;
                        iVar10 = *dbg;
                        uVar3 = 0x9e9ea;
LAB_0002ee5a:
                        if (iVar10 == 0) log_message(uVar3, ((unsigned long)"app_codec_lc3_test"), iVar9);
                        else debug_print(uVar3, ((unsigned long)"app_codec_lc3_test"), iVar9);
                    }
                } else {
                    uVar3 = lc3_setup_encoder(10000, 16000, 0, iVar5);
                    iVar8 = iVar7;
                    do {
                        if (iVar8 == iVar10 + iVar7) {
                            iVar11 = is_battery_critical();
                            puVar2 = (uint *)puVar2v;
                            if (iVar11 != 1) {
                                if (*(volatile int *)0x20007b78 == 0) {
                                    enqueue_dmic(iVar7);
                                } else {
                                    local_stats.first = 0;
                                    local_stats.second = 0;
                                    get_synced_clock_time(&local_stats);
                                    if (2 < *v) {
                                        if (*dbg == 0) {
                                            log_message(((unsigned long)"%s(): send audio stream data to storage thread,timestemp = %lld\n"), ((unsigned long)"app_codec_lc3_test"),
                                                        local_stats.first,
                                                        local_stats.second);
                                        }
                                        else debug_print(((unsigned long)"%s(): send audio stream data to storage thread,timestemp = %lld\n"), ((unsigned long)"app_codec_lc3_test"),
                                                         local_stats.first,
                                                         local_stats.second);
                                    }
                                    sendAudioStram2Cache(iVar7);
                                }
                                goto LAB_0002eeb6;
                            }
                            if (0x40ffff < *puVar2v) goto LAB_0002eeb6;
                            typedef int (*codec_write_fn)(int, uint, int, int);
                            codec_write_fn write_frame =
                                *(volatile codec_write_fn*)(
                                    *(volatile uint32_t*)0x00087bf8UL + 4);
                            iVar9 = write_frame(0x00087bf0, *puVar2v,
                                               iVar7, iVar10);
                            if (iVar9 != 0) {
                                if (*v < 1) goto LAB_0002eeb6;
                                iVar10 = *dbg;
                                uVar3 = 0x9ebc6;
                                goto LAB_0002ee5a;
                            }
                            if (0 < *v) {
                                if (*dbg == 0) log_message(((unsigned long)"%s(): Flash write to addr 0x%x\n\n"), ((unsigned long)"app_codec_lc3_test"), *puVar2);
                                else debug_print(((unsigned long)"%s(): Flash write to addr 0x%x\n\n"), ((unsigned long)"app_codec_lc3_test"),
                                                 *puVar2);
                            }
                            *puVar2 = *puVar2 + iVar10;
                            goto LAB_0002eeb6;
                        }
                        iVar9 = lc3_encode(uVar3, 0, param_1, 1, 0x14, iVar8, uVar3, param_1);
                        iVar8 = iVar8 + 0x14;
                        param_1 = param_1 + iVar11;
                    } while (iVar9 == 0);
                    if (0 < *v) {
                        iVar10 = *dbg;
                        uVar3 = 0xa3f95;
                        goto LAB_0002ee5a;
                    }
                }
LAB_0002eeb6:
                free(iVar5);
                free(iVar6);
                goto LAB_0002edce;
            }
            if (*v < 1) {
                free(iVar5);
                iVar7 = iVar6;
                goto LAB_0002edce;
            }
LAB_0002ee16:
            if (*dbg == 0) log_message(((unsigned long)"%s(): malloc error\r\n\n"), ((unsigned long)"app_codec_lc3_test"));
            else debug_print(((unsigned long)"%s(): malloc error\r\n\n"), ((unsigned long)"app_codec_lc3_test"));
            free(iVar5);
            goto LAB_0002edf8;
        }
        if (0 < *v) goto LAB_0002ee16;
LAB_0002ede2:
        free(iVar5);
    }
    if (iVar7 == 0) return;
LAB_0002edce:
    free(iVar7);
    return;
}
