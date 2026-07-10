/* named: consume_pending_event_and_refresh_flag */
/* globals referenced:
//   0x20007b78  g_pending_event_word         
*/
/* Reconstructed consume_pending_event_and_refresh_flag @ 0x3b800  (parity: 300/300 trials, PROVEN) */

extern void stopAudioStreamRecord(unsigned int, unsigned int);
extern void mark_master_or_low_battery_flag(void);

void consume_pending_event_and_refresh_flag(void)
{
  unsigned int uVar1;

  uVar1 = *(volatile unsigned int*)0x20007b78UL;
  *(volatile unsigned int*)0x20007b78UL = 0;
  stopAudioStreamRecord(0,uVar1);
  mark_master_or_low_battery_flag();
  return;
}

