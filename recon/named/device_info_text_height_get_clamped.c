/* named: device_info_text_height_get_clamped */
/* Reconstructed device_info_text_height_get_clamped @ 0x7d446  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int get_device_info(void);
uint16_t device_info_text_height_get_clamped(void){
  int b;
  b=get_device_info();
  if(*(volatile uint16_t*)(b+0x1072)==0) goto L492;
 L456:
  b=get_device_info();
  if(*(volatile uint16_t*)(b+0x1074)>0x40) goto L4a2;
 L466:
  b=get_device_info();
  if(*(volatile uint16_t*)(b+0x1074)>3) goto L484;
  b=get_device_info();
  *(volatile uint16_t*)(b+0x1074)=4;
 L484:
  b=get_device_info();
  return *(volatile uint16_t*)(b+0x1074);
 L492:
  b=get_device_info();
  if(*(volatile uint16_t*)(b+0x1074)!=0) goto L456;
 L4a2:
  b=get_device_info();
  *(volatile uint16_t*)(b+0x1074)=0x20;
  goto L466;
}

