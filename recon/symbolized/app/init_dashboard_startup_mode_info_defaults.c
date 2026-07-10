#include "g1_app_symbols.h"
/* named: init_dashboard_startup_mode_info_defaults */
/* globals referenced:
//   0x200069fc  device_info                  
//   0x2001b816  g_widget0_index_raw          
//   0x2007fc00  g_dashboard_startup_mode_info_defaults 
*/
/* Reconstructed init_dashboard_startup_mode_info_defaults @ 0x16658  (parity: 300/300 trials, PROVEN) */
void init_dashboard_startup_mode_info_defaults(void){
  int iVar7 = *(volatile int*)((uintptr_t)&device_info) /*=0x200069fc*/;
  int dst = *(volatile int*)(iVar7+0xfec);
  *(volatile int*)dst = *(volatile int*)((uintptr_t)&g_dashboard_startup_mode_info_defaults) /*=0x2007fc00*/ + 1;
  *(volatile unsigned char*)(dst+4) = *(volatile unsigned char*)((uintptr_t)&g_all_static_info_fc04) /*=0x2007fc04*/;
  *(volatile unsigned char*)(dst+5) = *(volatile unsigned char*)((uintptr_t)&g_dashboard_startup_mode_info_field_05) /*=0x2007fc05*/;
  *(volatile int*)(dst+6) = *(volatile int*)((uintptr_t)&g_all_static_info_fc08) /*=0x2007fc08*/;
  *(volatile int*)(dst+0xa) = *(volatile int*)((uintptr_t)&g_all_static_info_fc0c) /*=0x2007fc0c*/;
  *(volatile unsigned char*)(dst+0x5d) = *(volatile unsigned char*)((uintptr_t)&g_all_static_info_fc5f) /*=0x2007fc5f*/;
  *(volatile unsigned char*)(dst+0x5e) = *(volatile unsigned char*)((uintptr_t)&g_all_static_info_fc60) /*=0x2007fc60*/;
  *(volatile unsigned char*)(dst+0x61) = *(volatile unsigned char*)((uintptr_t)&g_all_static_info_fc62) /*=0x2007fc62*/;
  *(volatile unsigned char*)(dst+0x60) = *(volatile unsigned char*)((uintptr_t)&g_dashboard_startup_mode_info_field_61) /*=0x2007fc61*/;
  *(volatile unsigned char*)(dst+0x63) = *(volatile unsigned char*)((uintptr_t)&g_all_static_info_fc68) /*=0x2007fc68*/;
  { unsigned char b = *(volatile unsigned char*)((uintptr_t)&g_dashboard_default_widget0_index) /*=0x2007fc69*/;
    if (b <= 3) *(volatile unsigned char*)((uintptr_t)&g_widget0_index_raw) /*=0x2001b816*/ = b; }
  *(volatile int*)(dst+0x0e) = *(volatile int*)((uintptr_t)&g_all_static_info) /*=0x2007fc10*/;
  *(volatile int*)(dst+0x12) = *(volatile int*)((uintptr_t)&g_dashboard_startup_mode_info_field_14) /*=0x2007fc14*/;
  *(volatile int*)(dst+0x16) = *(volatile int*)((uintptr_t)&g_dashboard_startup_mode_info_field_18) /*=0x2007fc18*/;
  *(volatile int*)(dst+0x1a) = *(volatile int*)((uintptr_t)&g_dashboard_startup_mode_info_field_1c) /*=0x2007fc1c*/;
  *(volatile int*)(dst+0x1e) = *(volatile int*)((uintptr_t)&g_dashboard_startup_mode_info_defaults_fld_20) /*=0x2007fc20*/;
  *(volatile int*)(dst+0x22) = *(volatile int*)((uintptr_t)&g_dashboard_startup_mode_info_defaults_fld_24) /*=0x2007fc24*/;
  *(volatile int*)(dst+0x26) = *(volatile int*)((uintptr_t)&g_dashboard_startup_mode_info_defaults_fld_28) /*=0x2007fc28*/;
  *(volatile int*)(dst+0x2a) = *(volatile int*)((uintptr_t)&g_dashboard_startup_mode_info_defaults_fld_2c) /*=0x2007fc2c*/;
  *(volatile int*)(dst+0x2e) = *(volatile int*)((uintptr_t)&g_dashboard_startup_mode_info_defaults_fld_30) /*=0x2007fc30*/;
  *(volatile unsigned char*)(dst+0x32) = *(volatile unsigned char*)((uintptr_t)&g_dashboard_startup_mode_info_defaults_fld_34) /*=0x2007fc34*/;
  *(volatile int*)(dst+0x33) = *(volatile int*)((uintptr_t)&g_all_static_info_fc35) /*=0x2007fc35*/;
  *(volatile int*)(dst+0x37) = *(volatile int*)((uintptr_t)&g_dashboard_startup_mode_info_field_39) /*=0x2007fc39*/;
  *(volatile int*)(dst+0x3b) = *(volatile int*)((uintptr_t)&g_dashboard_startup_mode_info_defaults_fld_3d) /*=0x2007fc3d*/;
  *(volatile int*)(dst+0x3f) = *(volatile int*)((uintptr_t)&g_dashboard_startup_mode_info_defaults_fld_41) /*=0x2007fc41*/;
  *(volatile int*)(dst+0x43) = *(volatile int*)((uintptr_t)&g_dashboard_startup_mode_info_defaults_fld_45) /*=0x2007fc45*/;
  *(volatile int*)(dst+0x47) = *(volatile int*)((uintptr_t)&g_dashboard_startup_mode_info_defaults_fld_49) /*=0x2007fc49*/;
  *(volatile int*)(dst+0x4b) = *(volatile int*)((uintptr_t)&g_dashboard_startup_mode_info_defaults_fld_4d) /*=0x2007fc4d*/;
  *(volatile int*)(dst+0x4f) = *(volatile int*)((uintptr_t)&g_dashboard_startup_mode_info_defaults_fld_51) /*=0x2007fc51*/;
  *(volatile int*)(dst+0x53) = *(volatile int*)((uintptr_t)&g_dashboard_startup_mode_info_defaults_fld_55) /*=0x2007fc55*/;
  *(volatile int*)(dst+0x57) = *(volatile int*)((uintptr_t)&g_dashboard_startup_mode_info_defaults_fld_59) /*=0x2007fc59*/;
  *(volatile unsigned short*)(dst+0x5b) = *(volatile unsigned short*)((uintptr_t)&g_dashboard_startup_mode_info_defaults_fld_5d) /*=0x2007fc5d*/;
}

