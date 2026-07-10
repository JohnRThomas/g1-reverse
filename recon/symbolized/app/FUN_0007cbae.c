#include "g1_app_symbols.h"
/* named: FUN_0007cbae */
/* Reconstructed FUN_0007cbae @ 0x7cbae  (parity: 300/300 trials, PROVEN) */
extern char* get_device_info(void);
extern int is_system_idle_ready(void);
extern char* ext3cebc(void);
char* FUN_0007cbae(int p1,int p2,int p3){
  char *r; int iv;
  (void)p1;(void)p2;(void)p3;
  r = (char*)get_device_info();
  if (*r == 1){
    iv = (int)get_device_info();
    if (*(char*)(*(int*)(iv+0x1010)+1) != 0){
      if (is_system_idle_ready() != 0) goto tail;
    }
  }
  r = (char*)get_device_info();
  if (*r != 2) return r;
  iv = (int)get_device_info();
  if (*(char*)(*(int*)(iv+0x1010)+1) == 0) return (char*)(iv+0x1000);
 tail:
  iv = (int)get_device_info();
  { volatile char c = *(char*)(*(int*)(iv+0x1010)+2); (void)c; }
  return ext3cebc();
}

