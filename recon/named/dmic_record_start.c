/* named: dmic_record_start */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
//   0x20007b78  g_pending_event_word         
*/
/* Reconstructed dmic_record_start @ 0x3b78c  (parity: 300/300 trials, PROVEN) */

extern int get_device_info(int, int);
extern void debug_print(void);
extern void drain_audio_msgq(void);
extern void startAudioStreamRecord(void);
extern void FUN_00072880(int);
extern int DEBUG_PRINT(int, ...);

void dmic_record_start(void)
{
  int iVar1;
  unsigned int uVar2;

  iVar1 = get_device_info(0, 0);
  *(volatile unsigned char*)(iVar1 + 0x1059) = 4;
  if (*(int*)0x2000230cUL > 2) {
    if (*(int*)0x20007554UL == 0) {
      DEBUG_PRINT(0x9d30b, 0xa9843);
    } else {
      debug_print();
    }
  }
  drain_audio_msgq();
  startAudioStreamRecord();
  uVar2 = *(volatile unsigned int*)0x20007b78UL;
  *(volatile unsigned int*)0x20007b78UL = 1;
  iVar1 = get_device_info(0, uVar2);
  *(volatile unsigned int*)(iVar1 + 0x104c) = 0x1d;
  iVar1 = get_device_info(0, 0);
  FUN_00072880(iVar1 + 0x68);
}

