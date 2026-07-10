/* named: app_codec_lc3_test */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
//   0x20007b78  g_pending_event_word         
*/
/* Reconstructed app_codec_lc3_test @ 0x2ed68  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int uint;
typedef unsigned undefined4;
extern void DEBUG_PRINT(unsigned, ...);
extern void debug_print(unsigned, ...);
extern void enqueue_dmic(int a);
extern void sendAudioStram2Cache(int a);
extern int is_battery_critical(void);
extern void get_synced_clock_time(void *a);
extern unsigned qspi_nor_write(void);
extern int lc3_ns(int a, int b);
extern unsigned lc3_frame_param_compute(int a, int b);
extern unsigned lc3_ltpf_select_resampler_params(int a, int b, int c, int d);
extern int lc3_encode_frame(unsigned a, int b, int c, int d, int e, int f, unsigned g, int h);
extern int malloc(unsigned a);
extern void heap_free(int a);
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
    unsigned local_30, uStack_2c;

    uVar3 = lc3_frame_param_compute(10000, 16000);
    uVar4 = lc3_ns(10000, 16000);
    iVar5 = malloc(uVar3);
    iVar11 = (uVar4 & 0x7fff) * 2;
    iVar6 = malloc(iVar11);
    iVar10 = (param_2 / iVar11 & 0xffffU) * 0x14;
    iVar7 = malloc(iVar10);
    if (iVar5 == 0) {
        if (0 < *v) {
            if (*dbg == 0) DEBUG_PRINT(0xa3f7f, 0xa41c2);
            else debug_print(0);
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
                        if (iVar10 == 0) DEBUG_PRINT(uVar3, 0xa41c2, iVar9);
                        else debug_print(0);
                    }
                } else {
                    uVar3 = lc3_ltpf_select_resampler_params(10000, 16000, 0, iVar5);
                    iVar8 = iVar7;
                    do {
                        if (iVar8 == iVar10 + iVar7) {
                            iVar11 = is_battery_critical();
                            puVar2 = (uint *)puVar2v;
                            if (iVar11 != 1) {
                                if (*(volatile int *)0x20007b78 == 0) {
                                    enqueue_dmic(iVar7);
                                } else {
                                    local_30 = 0;
                                    uStack_2c = 0;
                                    get_synced_clock_time(&local_30);
                                    if (2 < *v) {
                                        if (*dbg == 0) DEBUG_PRINT(0xa3fdf, 0xa41c2, local_30, uStack_2c);
                                        else debug_print(0xa3fdf, 0xa41c2);
                                    }
                                    sendAudioStram2Cache(iVar7);
                                }
                                goto LAB_0002eeb6;
                            }
                            if (0x40ffff < *puVar2v) goto LAB_0002eeb6;
                            iVar9 = (**(int (***)(int, uint, int, int))(*(volatile int *)(0x87bf0 + 8) + 4))(0x87bf0, *puVar2v, iVar7, iVar10);
                            if (iVar9 != 0) {
                                if (*v < 1) goto LAB_0002eeb6;
                                iVar10 = *dbg;
                                uVar3 = 0x9ebc6;
                                goto LAB_0002ee5a;
                            }
                            if (0 < *v) {
                                if (*dbg == 0) DEBUG_PRINT(0xa3fbe, 0xa41c2, *puVar2);
                                else debug_print(0);
                            }
                            *puVar2 = *puVar2 + iVar10;
                            goto LAB_0002eeb6;
                        }
                        iVar9 = lc3_encode_frame(uVar3, 0, param_1, 1, 0x14, iVar8, uVar3, param_1);
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
                heap_free(iVar5);
                heap_free(iVar6);
                goto LAB_0002edce;
            }
            if (*v < 1) {
                heap_free(iVar5);
                iVar7 = iVar6;
                goto LAB_0002edce;
            }
LAB_0002ee16:
            if (*dbg == 0) DEBUG_PRINT(0xa3f7f, 0xa41c2);
            else debug_print(0);
            heap_free(iVar5);
            goto LAB_0002edf8;
        }
        if (0 < *v) goto LAB_0002ee16;
LAB_0002ede2:
        heap_free(iVar5);
    }
    if (iVar7 == 0) return;
LAB_0002edce:
    heap_free(iVar7);
    return;
}

