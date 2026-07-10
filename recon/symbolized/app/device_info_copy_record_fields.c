#include "g1_app_symbols.h"
/* named: device_info_copy_record_fields */
/* globals referenced:
//   0x200069fc  device_info                  
//   0x2007fc00  g_dashboard_startup_mode_info_defaults 
*/
/* Reconstructed device_info_copy_record_fields @ 0x165cc  (parity: 300/300 trials, PROVEN) */

void device_info_copy_record_fields(void){
  int src = *(volatile int*)(*(volatile int*)((uintptr_t)&device_info) /*=0x200069fc*/ + 0xfec);
  unsigned r1 = *(volatile unsigned*)src;
  unsigned r0 = *(volatile unsigned*)(src+6);
  *(volatile unsigned*)((uintptr_t)&g_dashboard_startup_mode_info_defaults) /*=0x2007fc00*/ = r1;
  *(volatile unsigned char*)((uintptr_t)&g_all_static_info_fc04) /*=0x2007fc04*/ = *(volatile unsigned char*)(src+4);
  *(volatile unsigned char*)((uintptr_t)&g_dashboard_startup_mode_info_field_05) /*=0x2007fc05*/ = *(volatile unsigned char*)(src+5);
  unsigned r1b = *(volatile unsigned*)(src+0xa);
  *(volatile unsigned*)((uintptr_t)&g_all_static_info_fc08) /*=0x2007fc08*/ = r0;
  *(volatile unsigned*)((uintptr_t)&g_all_static_info_fc0c) /*=0x2007fc0c*/ = r1b;
  *(volatile unsigned char*)((uintptr_t)&g_all_static_info_fc5f) /*=0x2007fc5f*/ = *(volatile unsigned char*)(src+0x5d);
  *(volatile unsigned char*)((uintptr_t)&g_all_static_info_fc60) /*=0x2007fc60*/ = *(volatile unsigned char*)(src+0x5e);
  *(volatile unsigned char*)((uintptr_t)&g_all_static_info_fc62) /*=0x2007fc62*/ = *(volatile unsigned char*)(src+0x61);
  *(volatile unsigned char*)((uintptr_t)&g_dashboard_startup_mode_info_field_61) /*=0x2007fc61*/ = *(volatile unsigned char*)(src+0x60);
  unsigned dst5 = ((uintptr_t)&g_all_static_info) /*=0x2007fc10*/; int r4 = src+0xe; int r6 = src+0x2e;
  do{
    unsigned a=*(volatile unsigned*)r4; unsigned b=*(volatile unsigned*)(r4+4); r4+=8;
    *(volatile unsigned*)dst5 = a; *(volatile unsigned*)(dst5+4) = b; dst5+=8;
  }while(r4!=r6);
  *(volatile unsigned*)dst5 = *(volatile unsigned*)r4;
  *(volatile unsigned char*)(dst5+4) = *(volatile unsigned char*)(r4+4);
  volatile unsigned char *dp=(volatile unsigned char*)((uintptr_t)&g_all_static_info_fc35) /*=0x2007fc35*/; int r3p=src+0x33; int r2end=src+0x5b;
  do{ unsigned v=*(volatile unsigned*)r3p; r3p+=4; *(volatile unsigned*)dp = v; dp+=4; }while(r3p!=r2end);
  *(volatile unsigned short*)dp = *(volatile unsigned short*)r3p;
}

