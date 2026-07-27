#include "g1_app_symbols.h"
struct k_sem;
/* readable reconstruction; identity: FUN_0002f080 @ 0x0002f080
 * public-name: dmic_stream_start
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   rodata_87bf0                             @ 0x00087bf0
 *   rodata_87d40                             @ 0x00087d40
 *   rodata_88694                             @ 0x00088694
 *   rodata_9ebc6                             @ 0x0009ebc6
 *   rodata_a3fbe                             @ 0x000a3fbe   [INLINED -- G6 literal batch]
 *   rodata_a4038                             @ 0x000a4038   [INLINED -- G6 literal batch]
 *   rodata_a404b                             @ 0x000a404b   [INLINED -- G6 literal batch]
 *   rodata_a4062                             @ 0x000a4062   [INLINED -- G6 literal batch]
 *   rodata_a4075                             @ 0x000a4075   [INLINED -- G6 literal batch]
 *   rodata_a40e6                             @ 0x000a40e6   [INLINED -- G6 literal batch]
 *   rodata_a4120                             @ 0x000a4120   [INLINED -- G6 literal batch]
 *   rodata_a4147                             @ 0x000a4147   [INLINED -- G6 literal batch]
 *   rodata_a417e                             @ 0x000a417e   [INLINED -- G6 literal batch]
 *   rodata_a41a0                             @ 0x000a41a0   [INLINED -- G6 literal batch]
 *   rodata_a41b0                             @ 0x000a41b0   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_audio_flash_write_offset               @ 0x20002404
 *   g_low_battery_sync_flag                  @ 0x2000302f
 *   g_20003778                               @ 0x20003778
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_dmic_msgq                              @ 0x20007b7c
 *   g_20018da9                               @ 0x20018da9
 */
/* Reconstructed dmic_stream_start @ 0x0002f080.
 * Raw identity/back-map: FUN_0002f080 @ 0x0002f080.
 *
 * The shipped CFG owns the complete PDM capture loop through 0x0002f43c.
 * In particular, its non-flash arm calls app_codec_lc3_test at 0x0002f3f2;
 * the former 44-line reconstruction stopped before that live edge. */
#include <stdint.h>
#include "../../headers/g1_log.h"

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef int (*device_call)(u32 device, ...);

/* FUN_0007dda4 */
extern int get_device_info(void);                         /* FUN_000167a8 */
extern int enqueue_bt_data(unsigned long, unsigned char); /* FUN_00017eec */
extern int ancs_get_conn_ctx(void);                       /* FUN_000181fc */
/* FUN_00019c70 */
extern int init_dmic_msgq(void);                          /* FUN_0002ebd8 */
extern int clean_dmic_msgq(void);                         /* FUN_0002ec1c */
extern void app_codec_lc3_test(int, int);   /* FUN_0002ed68 */
extern int erase_audio_buffer(void);                      /* FUN_0002f008 */
extern int is_battery_critical(void);                     /* FUN_00032ee4 */
extern void k_mem_slab_free(struct k_mem_slab *, void *);          /* FUN_00071cf4 */
extern void k_sem_give(struct k_sem *);                     /* FUN_00072880 */
extern _Bool z_device_is_ready(const struct device *);                 /* FUN_0008638c */
extern void memset_bytes(void*, int, int);/* FUN_00086c78 */

#define g_log_level              (*(volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/)
#define g_log_use_alt_sink       (*(volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)
#define g_audio_flash_offset     (*(volatile u32 *)((unsigned long)&g_audio_flash_write_offset) /*=0x20002404*/)
#define g_audio_ready_to_send    (*(volatile u8 *)((unsigned long)&g_20018da9) /*=0x20018da9*/)
#define g_audio_stop_requested   (*(volatile u8 *)((unsigned long)&g_low_battery_sync_flag) /*=0x2000302f*/)
#define g_pending_event_context  ((volatile u8 *)((unsigned long)&g_dmic_msgq) /*=0x20007b7c*/)

#define PDM_DEVICE               ((unsigned long)&rodata_87d40) /*=0x87d40*/
#define QSPI_DEVICE              ((unsigned long)&rodata_87bf0) /*=0x87bf0*/
#define DMIC_SLAB                ((unsigned long)&g_20003778) /*=0x20003778*/

static __attribute__((always_inline)) inline device_call
device_method(u32 device, u32 slot)
{
    u32 api = *(volatile u32 *)(device + 8U);
    return (device_call)(uintptr_t)*(volatile u32 *)(api + slot * 4U);
}

static __attribute__((always_inline)) inline void
dmic_log(u32 level, u32 format, u32 source, u32 value, int with_value)
{
    if ((int)level < g_log_level) {
        if (g_log_use_alt_sink == 0) {
            if (with_value) log_message(format, source, value);
            else log_message(format, source);
        } else {
            if (with_value) debug_print(format, source, value);
            else debug_print(format, source);
        }
    }
}

u32 dmic_stream_start(void)
{
    int connection = ancs_get_conn_ctx();
    int device_info = get_device_info();
    u32 result = *(volatile u16 *)(device_info + 0x105c) & 2U;

    if (result != 0U) {
        dmic_log(2, ((unsigned long)"%s(): DMIC sample\n") /*=0xa4038*/, ((unsigned long)"dmic_stream_start") /*=0xa41b0*/, 0, 0);
        if (z_device_is_ready(PDM_DEVICE) == 0) {
            dmic_log(0, ((unsigned long)"%s(): %s is not ready\n") /*=0xa404b*/, ((unsigned long)"dmic_stream_start") /*=0xa41b0*/,
                     *(volatile u32 *)PDM_DEVICE, 1);
            result = 1;
            goto stop_stream;
        }

        dmic_log(2, ((unsigned long)"%s(): %s is ready\n") /*=0xa4062*/, ((unsigned long)"dmic_stream_start") /*=0xa41b0*/,
                 *(volatile u32 *)PDM_DEVICE, 1);
        if (init_dmic_msgq() != 0) {
            result = 1;
            goto stop_stream;
        }

        /* Exact stack object layout passed to the PDM configure callback:
         * stream { rate=16000, format=0x0c800010 }, slab=0x20003778;
         * config { min=1000000, max=3500000, gainL=40, gainR=60, ...,
         *          stream=&stream, request/trigger flags at +0x24/+0x26 }. */
        u32 stream[2];
        u8 config[40];
        stream[0] = 16000U;
        stream[1] = 0x0c800010U;
        memset_bytes(config, 0, 30U);
        *(u32 *)(config + 0) = 1000000U;
        *(u32 *)(config + 4) = 3500000U;
        config[8] = 40;
        config[9] = 60;
        *(u32 *)(config + 16) = (u32)(uintptr_t)stream;
        config[36] = 1;
        config[38] = 1;

        if (is_battery_critical() == 1) {
            int erase_status = erase_audio_buffer();
            if (erase_status < 0) {
                dmic_log(0, ((unsigned long)"%s(): Failed to erase_audio_buffer %d\n") /*=0xa4075*/, ((unsigned long)"dmic_stream_start") /*=0xa41b0*/,
                         (u32)erase_status, 1);
                result = (u32)-1;
                goto stop_stream;
            }
        }

        int status = device_method(PDM_DEVICE, 0)(PDM_DEVICE, config);
        if (status < 0) {
            dmic_log(0, 0x000a409cU, ((unsigned long)"dmic_stream_start") /*=0xa41b0*/, (u32)status, 1);
            result = (u32)-1;
            goto stop_stream;
        }
        status = device_method(PDM_DEVICE, 1)(PDM_DEVICE, 1);
        if (status < 0) {
            dmic_log(0, 0x000a40c6U, ((unsigned long)"dmic_stream_start") /*=0xa41b0*/, (u32)status, 1);
            result = (u32)-1;
            goto stop_stream;
        }

        g_audio_ready_to_send = 0;
        g_audio_stop_requested = 0;
        while (g_audio_stop_requested != 1U) {
            u32 block = 0;
            u32 bytes = 0;

            if (is_battery_critical() == 1 &&
                *(volatile u8 *)(get_device_info() + 0x108c) == 1U &&
                z_device_is_ready(QSPI_DEVICE) == 0) {
                dmic_log(0, ((unsigned long)"%s():  [%s] device not ready.\n") /*=0xa40e6*/, ((unsigned long)"do_pdm_transfer") /*=0xa41a0*/,
                         *(volatile u32 *)QSPI_DEVICE, 1);
                if (block != 0U) k_mem_slab_free(DMIC_SLAB, block);
                dmic_log(0, ((unsigned long)"%s(): !!!do_pdm_transfer exec failed.\n") /*=0xa4120*/, ((unsigned long)"dmic_stream_start") /*=0xa41b0*/, 0, 0);
                result = (u32)-1;
                goto stop_stream;
            }

            status = device_method(PDM_DEVICE, 2)(PDM_DEVICE, 0,
                                                   &block, &bytes, 1000);
            if (status != 0) {
                dmic_log(0, 0x000a4105U, ((unsigned long)"do_pdm_transfer") /*=0xa41a0*/,
                         (u32)status, 1);
                if (block != 0U) k_mem_slab_free(DMIC_SLAB, block);
                dmic_log(0, ((unsigned long)"%s(): !!!do_pdm_transfer exec failed.\n") /*=0xa4120*/, ((unsigned long)"dmic_stream_start") /*=0xa41b0*/, 0, 0);
                result = (u32)-1;
                goto stop_stream;
            }

            if (is_battery_critical() == 1 &&
                *(volatile u8 *)(get_device_info() + 0x108c) == 1U) {
                if (g_audio_flash_offset < 0x410000U - bytes) {
                    status = device_method(QSPI_DEVICE, 1)(QSPI_DEVICE);
                    if (status != 0) {
                        dmic_log(0, ((unsigned long)&rodata_9ebc6) /*=0x9ebc6*/, ((unsigned long)"do_pdm_transfer") /*=0xa41a0*/,
                                 (u32)status, 1);
                        if (block != 0U) k_mem_slab_free(DMIC_SLAB, block);
                        dmic_log(0, ((unsigned long)"%s(): !!!do_pdm_transfer exec failed.\n") /*=0xa4120*/, ((unsigned long)"dmic_stream_start") /*=0xa41b0*/, 0, 0);
                        result = (u32)-1;
                        goto stop_stream;
                    }
                    dmic_log(0, ((unsigned long)"%s(): Flash write to addr 0x%x\n\n") /*=0xa3fbe*/, ((unsigned long)"do_pdm_transfer") /*=0xa41a0*/,
                             g_audio_flash_offset, 1);
                    g_audio_flash_offset += bytes;
                }
                if (block != 0U) k_mem_slab_free(DMIC_SLAB, block);
            } else if (block != 0U) {
                app_codec_lc3_test(block, bytes);
                k_mem_slab_free(DMIC_SLAB, block);
            }

            result = 0;
            if (g_audio_stop_requested == 0U &&
                is_battery_critical() == 0 &&
                *(volatile u32 *)(g_pending_event_context + 0x24) != 0U) {
                if (*(volatile u8 *)(connection + 0x248) == 0U &&
                    *(volatile u32 *)(connection + 0x220) == 0U) {
                    g_audio_ready_to_send = 1;
                    k_sem_give((u32)connection + 0x218U);
                } else {
                    u8 event[3];
                    u16 event_id = *(volatile u16 *)((unsigned long)&rodata_88694) /*=0x88694*/;
                    event[0] = 0xf1;
                    event[1] = (u8)(event_id >> 8);
                    event[2] = 0xcc;
                    enqueue_bt_data(event, 3);
                }
            }
        }
    }

stop_stream:
    {
        int status = device_method(PDM_DEVICE, 1)(PDM_DEVICE, 0);
        if (status < 0) {
            dmic_log(0, ((unsigned long)"%s(): STOP trigger failed\n") /*=0xa4147*/, ((unsigned long)"dmic_stream_start") /*=0xa41b0*/, (u32)status, 1);
        } else {
            dmic_log(0, 0x000a4162U, ((unsigned long)"dmic_stream_start") /*=0xa41b0*/, 0, 0);
        }
    }
    clean_dmic_msgq();
    g_audio_flash_offset = 0x400000U;
    dmic_log(2, ((unsigned long)"%s(): Exiting\n") /*=0xa417e*/, ((unsigned long)"dmic_stream_start") /*=0xa41b0*/, 0, 0);
    return result;
}
