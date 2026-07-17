#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00016658 @ 0x00016658
 * public-name: init_dashboard_startup_mode_info_defaults
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   init_dashboard_startup_mode_info_defaults <= FUN_00016658 @ 0x00016658
 * address symbols (name @ address):
 *   device_info                              @ 0x200069fc
 *   g_widget0_index_raw                      @ 0x2001b816
 *   g_dashboard_startup_mode_info_defaults   @ 0x2007fc00
 *   g_all_static_info_fc04                   @ 0x2007fc04
 *   g_dashboard_startup_mode_info_field_05   @ 0x2007fc05
 *   g_all_static_info_fc08                   @ 0x2007fc08
 *   g_all_static_info_fc0c                   @ 0x2007fc0c
 *   g_all_static_info                        @ 0x2007fc10
 *   g_dashboard_startup_mode_info_field_14   @ 0x2007fc14
 *   g_dashboard_startup_mode_info_field_18   @ 0x2007fc18
 *   g_dashboard_startup_mode_info_field_1c   @ 0x2007fc1c
 *   g_all_static_info_fc35                   @ 0x2007fc35
 *   g_dashboard_startup_mode_info_field_39   @ 0x2007fc39
 *   g_all_static_info_fc5f                   @ 0x2007fc5f
 *   g_all_static_info_fc60                   @ 0x2007fc60
 *   g_dashboard_startup_mode_info_field_61   @ 0x2007fc61
 *   g_all_static_info_fc62                   @ 0x2007fc62
 *   g_all_static_info_fc68                   @ 0x2007fc68
 *   g_dashboard_default_widget0_index        @ 0x2007fc69
 */
/* Reconstructed FUN_00016658 @ 0x16658  (parity: 300/300 trials, PROVEN) */
void init_dashboard_startup_mode_info_defaults(void){
  int iVar7 = *(volatile int*)((unsigned long)&device_info) /*=0x200069fc*/;
  int dst = *(volatile int*)(iVar7+0xfec);
  *(volatile int*)dst = *(volatile int*)((unsigned long)&g_dashboard_startup_mode_info_defaults) /*=0x2007fc00*/ + 1;
  *(volatile unsigned char*)(dst+4) = *(volatile unsigned char*)((unsigned long)&g_all_static_info_fc04) /*=0x2007fc04*/;
  *(volatile unsigned char*)(dst+5) = *(volatile unsigned char*)((unsigned long)&g_dashboard_startup_mode_info_field_05) /*=0x2007fc05*/;
  *(volatile int*)(dst+6) = *(volatile int*)((unsigned long)&g_all_static_info_fc08) /*=0x2007fc08*/;
  *(volatile int*)(dst+0xa) = *(volatile int*)((unsigned long)&g_all_static_info_fc0c) /*=0x2007fc0c*/;
  *(volatile unsigned char*)(dst+0x5d) = *(volatile unsigned char*)((unsigned long)&g_all_static_info_fc5f) /*=0x2007fc5f*/;
  *(volatile unsigned char*)(dst+0x5e) = *(volatile unsigned char*)((unsigned long)&g_all_static_info_fc60) /*=0x2007fc60*/;
  *(volatile unsigned char*)(dst+0x61) = *(volatile unsigned char*)((unsigned long)&g_all_static_info_fc62) /*=0x2007fc62*/;
  *(volatile unsigned char*)(dst+0x60) = *(volatile unsigned char*)((unsigned long)&g_dashboard_startup_mode_info_field_61) /*=0x2007fc61*/;
  *(volatile unsigned char*)(dst+0x63) = *(volatile unsigned char*)((unsigned long)&g_all_static_info_fc68) /*=0x2007fc68*/;
  { unsigned char b = *(volatile unsigned char*)((unsigned long)&g_dashboard_default_widget0_index) /*=0x2007fc69*/;
    if (b <= 3) *(volatile unsigned char*)((unsigned long)&g_widget0_index_raw) /*=0x2001b816*/ = b; }
  *(volatile int*)(dst+0x0e) = *(volatile int*)((unsigned long)&g_all_static_info) /*=0x2007fc10*/;
  *(volatile int*)(dst+0x12) = *(volatile int*)((unsigned long)&g_dashboard_startup_mode_info_field_14) /*=0x2007fc14*/;
  *(volatile int*)(dst+0x16) = *(volatile int*)((unsigned long)&g_dashboard_startup_mode_info_field_18) /*=0x2007fc18*/;
  *(volatile int*)(dst+0x1a) = *(volatile int*)((unsigned long)&g_dashboard_startup_mode_info_field_1c) /*=0x2007fc1c*/;
  *(volatile int*)(dst+0x1e) = *(volatile int*)0x2007fc20UL;
  *(volatile int*)(dst+0x22) = *(volatile int*)0x2007fc24UL;
  *(volatile int*)(dst+0x26) = *(volatile int*)0x2007fc28UL;
  *(volatile int*)(dst+0x2a) = *(volatile int*)0x2007fc2cUL;
  *(volatile int*)(dst+0x2e) = *(volatile int*)0x2007fc30UL;
  *(volatile unsigned char*)(dst+0x32) = *(volatile unsigned char*)0x2007fc34UL;
  *(volatile int*)(dst+0x33) = *(volatile int*)((unsigned long)&g_all_static_info_fc35) /*=0x2007fc35*/;
  *(volatile int*)(dst+0x37) = *(volatile int*)((unsigned long)&g_dashboard_startup_mode_info_field_39) /*=0x2007fc39*/;
  *(volatile int*)(dst+0x3b) = *(volatile int*)0x2007fc3dUL;
  *(volatile int*)(dst+0x3f) = *(volatile int*)0x2007fc41UL;
  *(volatile int*)(dst+0x43) = *(volatile int*)0x2007fc45UL;
  *(volatile int*)(dst+0x47) = *(volatile int*)0x2007fc49UL;
  *(volatile int*)(dst+0x4b) = *(volatile int*)0x2007fc4dUL;
  *(volatile int*)(dst+0x4f) = *(volatile int*)0x2007fc51UL;
  *(volatile int*)(dst+0x53) = *(volatile int*)0x2007fc55UL;
  *(volatile int*)(dst+0x57) = *(volatile int*)0x2007fc59UL;
  *(volatile unsigned short*)(dst+0x5b) = *(volatile unsigned short*)0x2007fc5dUL;
}
