/*
 * audio: digital-mic (DMIC/PDM) capture, LC3 encode, and voice-record streaming.
 *
 * Captures PCM from the on-glasses digital microphone via the nRF PDM peripheral,
 * encodes it with LC3, and streams the compressed voice blocks to the phone over
 * BLE (Even-AI voice, QuickNote voice memos, calls). The module owns four message
 * queues (DMIC block queue, audio record/stream cache, UID queue, file-id queue),
 * the PDM driver instance and its DMA buffer slab, an audio-codec register
 * interface, and the mic power rail (shared with the IMU). LC3 encode itself is a
 * codec library (lc3_encode_frame + helpers); this module is the capture / queue /
 * transport glue and the codec/PDM hardware bring-up.
 *
 * PUBLIC / INTERNAL split is taken from the authoritative reference graph:
 * "public" below = the subset of audio functions actually called from OTHER
 * modules (the graph's `api` set). Everything else is module-internal (marked
 * INTERNAL) or a thread/callback entry point invoked by the RTOS, not by a
 * direct C caller.
 *
 * NOTE on clustering: the raw topic cluster for "audio" (194 funcs) also swept in
 * a large number of Zephyr kernel / driver primitives (z_reschedule, k_msgq_*,
 * net_buf_*, sys_heap chunk_*, nrfx_clock/uarte/qspi, log_*) because they share
 * call edges with the codec/transport code. Those are NOT audio's API and are
 * intentionally NOT declared here; they belong to the kernel/driver modules.
 */
#ifndef G1_AUDIO_H
#define G1_AUDIO_H

#include <stdint.h>
typedef unsigned int uint;

/* ============================================================================
 * PUBLIC API  (called from other modules — the reference graph's `api` set)
 * ==========================================================================*/

/* power / hardware-lock (mic shares its rail with the IMU) */
unsigned int power_down_imu_and_mic(void);          /* 0x160b4 */
uint8_t      audio_hw_lock_get_status_byte(void);   /* 0x7ef1c */

/* DMIC control + record entry */
int          send_dmic_msg(int arg);                /* 0x19ed4  open/close dmic cmd */
void         dmic_record_start(void);               /* 0x3b78c  begin bounded record */

/* record / stream session + cache */
unsigned int stopAudioStreamRecord(void);           /* 0x2f80c */
uint32_t     audioStreamFileManagerHandler(void);   /* 0x2f94c  drains audio cache queue */
int          erase_audio_buffer(void);              /* 0x2f008  reset record cache flag */
int          dequeue_file(unsigned int arg);        /* 0x235a4  pop phone file-id entry */

/* PDM capture DMA callback + buffer release (transport net_buf) */
uint         dmic_pdm_event_handler(void *evt);     /* 0x5ffa4  (FUN_5ffa4): PDM buffer done */
void         audio_buf_release(int buf, int pool);  /* 0x80b0e */

/* ============================================================================
 * INTERNAL  (module-owned, but only called within audio / from RTOS entry)
 * ==========================================================================*/

/* --- power / readiness ---------------------------------------------------- */
unsigned int power_for_imu_and_mic(void);           /* 0x15f80  entry */
unsigned int check_device_readiness(void);          /* 0x167b4  gates capture */

/* --- DMIC message queue (g_dmic_msgq) + PDM stream ------------------------ */
int          init_dmic_msgq(void);                  /* 0x2ebd8 */
int          clean_dmic_msgq(void);                 /* 0x2ec1c */
unsigned int get_dmic_msgq_count(void);             /* 0x2ecf4 */
int          enqueue_dmic(unsigned int msg);
int          dequeue_dmic(unsigned int arg);
uint         dmic_stream_start(void);               /* 0x2f080  entry */
/* PDM driver bring-up / worker (FUN_ names retained where semantics inferred): */
/*   0x5fa94 dmic_read_block   — k_msgq_get filled PDM block from driver queue */
/*   0x5fb30 pdm_resume        — nrfx_pdm_start wrapper                        */
/*   0x5fb8c pdm_stop          — nrfx_pdm_stop + teardown                      */
/*   0x5fc7c pdm_reconfigure   — nrfx_pdm_init/uninit + sample-rate math       */

/* --- audio record cache (g_audio_msgq) ------------------------------------ */
unsigned int startAudioStreamRecord(void);          /* 0x2f764  entry */
unsigned int delAudioStreamRecord(unsigned char id);/* 0x2f878  entry */
unsigned int sendAudioStram2Cache(void *block);     /* 0x2f6b0  producer */
int          getAudioMessageQueueCacheData(void *out);
void         delVoiceBlock(unsigned char id);
void         drain_audio_msgq(void);                /* 0x2f688 */

/* --- UID / file-id queues (map captured blocks -> phone file ids) --------- */
int          init_msgq_uid(void);                   /* 0x18e04  (g_uid_pipe) */
int          enqueue_uid(unsigned *q, unsigned a, unsigned b);
int          dequeue_uid(unsigned int *q, unsigned int a, unsigned int b);/* 0x18ff8 entry */
int          file_subsystem_queue_init(void);       /* g_file_msg_pipe */
int          enqueue_file(unsigned int a, unsigned int b);/* 0x23514 entry */

/* --- BLE app interface / analytics / codec self-test ---------------------- */
int          requestAudioInfoToApp(unsigned char arg);/* 0x48840 */
void         sendAudioStreamFileToApp(void);        /* 0x47bf8  entry */
void         burial_point_record_info_init(void);   /* 0x4ab3c  usage analytics */
void         app_codec_lc3_test(int a, int b);

#endif /* G1_AUDIO_H */
