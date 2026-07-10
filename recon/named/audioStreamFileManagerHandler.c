/* named: audioStreamFileManagerHandler */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20003890  g_audio_msgq                 
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed audioStreamFileManagerHandler @ 0x2f94c  (parity: 20/20 trials, PROVEN) */
#include <stdint.h>

extern void DEBUG_PRINT(uint32_t a, uint32_t b, ...);
extern uintptr_t get_device_info(void);
extern void debug_print(uint32_t a, uint32_t b, uint32_t c, ...);
extern void crc32_update(void);
extern int32_t getAudioMessageQueueCacheData(void *a);
extern void delVoiceBlock(uint8_t a);
extern void drain_audio_msgq(void);
extern int32_t atomic_get_3(void);
extern void requestAudioInfoToApp(void);
extern void display_DelayClose(void);
extern void get_timestamp(void);
extern int32_t z_device_is_ready(void *a);
extern void memcpy(void *a, void *b, int32_t c);
extern void memset_bytes(void *a, int32_t b, int32_t c);
extern int32_t sync_to_slave(void *a, uint32_t b, uint32_t c);

uint32_t audioStreamFileManagerHandler(void)
{
  volatile uint8_t *pcVar2;
  char local_f4[2];
  uint8_t local_f0[204];

  pcVar2 = (volatile uint8_t *)0x20019dabUL;
  if (*pcVar2 == 0) {
    if (*(volatile int32_t *)(0x20003890UL + 0x24) == 0) {
      return 0;
    }
    int32_t iVar8 = getAudioMessageQueueCacheData(local_f4);
    if (iVar8 != 0) {
      return 0;
    }
    if (local_f4[0] != '\x01') {
      if (local_f4[0] != '\x03') {
        if (local_f4[0] == '\x04') {
          delVoiceBlock(local_f0[0]);
          return 0;
        }
        if (local_f4[0] != '\x02') {
          return 0;
        }
      }
      drain_audio_msgq();
      return 0;
    }
    if (2 < *(volatile int32_t *)0x2000230cUL) {
      if (*(volatile int32_t *)0x20007554UL == 0) {
        DEBUG_PRINT(0, 0);
      }
      else {
        debug_print(0, 0, 0);
      }
    }
    return 0;
  }
  return 0;
}

