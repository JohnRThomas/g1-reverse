#include "g1_app_symbols.h"
/* named: msg_content_check_timeout_state */
/* globals referenced:
//   0x20007dac  g_message_pool               
*/
/* Reconstructed msg_content_check_timeout_state @ 0x347cc  (parity: 300/300 trials, PROVEN) */

extern int get_device_info(void);
extern unsigned int get_timestamp(void);

int msg_content_check_timeout_state(void)
{
  int iVar2;
  unsigned int uVar3;
  int r0;
  unsigned char b;
  unsigned int val;

  r0 = get_device_info();
  b = *(volatile unsigned char*)(long)(r0 + 0xdd);
  iVar2 = *(volatile int*)(long)((g_message_pool) /*=0x20007dac*/ + (unsigned int)(b - 1) * 0x1b4);
  if (iVar2 != 0) {
    uVar3 = get_timestamp();
    r0 = get_device_info();
    b = *(volatile unsigned char*)(long)(r0 + 0xdd);
    val = *(volatile unsigned int*)(long)((g_message_pool) /*=0x20007dac*/ + (unsigned int)(b - 1) * 0x1b4);
    if ((unsigned int)(val + 0xf) < uVar3) iVar2 = 2; else iVar2 = 1;
  }
  return iVar2;
}

