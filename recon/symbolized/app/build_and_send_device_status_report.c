#include "g1_app_symbols.h"
/* named: build_and_send_device_status_report */
/* Reconstructed build_and_send_device_status_report @ 0x22b00  (parity: 300/300 trials, PROVEN) */
extern void memset_bytes(void*,int,int);
extern void flash_settings_write_and_verify(int,void*,int);
int build_and_send_device_status_report(int param_1){
  unsigned char buf[0x84];
  (void)param_1;
  memset_bytes(buf, 0, 0x78);
  flash_settings_write_and_verify(FLASH_OFF_130000 /*=0x130000*/, buf, 0x84);
  return 0;
}

