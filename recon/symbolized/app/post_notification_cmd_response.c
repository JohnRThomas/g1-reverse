#include "g1_app_symbols.h"
/* named: post_notification_cmd_response */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed post_notification_cmd_response @ 0x340c4  (parity: 300/300 trials, PROVEN) */
extern void DEBUG_PRINT(int,...);
extern void debug_print(int,...);
extern void send_data_in_ble_chunks(int);
extern void push_message(int);
extern int  is_on_whitelist_by_identifier(int);
extern void strncpy_zero_pad(int,int,int);
#define VI(a) (*(volatile int*)(a))
#define VB(a) (*(volatile unsigned char*)(a))
#define VH(a) (*(volatile unsigned short*)(a))

int post_notification_cmd_response(int param_1,int param_2,int param_3,int param_4,int param_5,int *param_6){
  volatile int *lvl=(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/, *g8=(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
  int iVar5, format;
  if (param_1==0||param_2==0||param_3==0||param_4==0||param_5==0||param_6==0) {
    if (1 < *lvl) { if(*g8==0) DEBUG_PRINT("%s(): input parm invalid !\n" /*=0xa7ef6*/,"post_notification_cmd_response" /*=0xa831f*/,param_5,0,param_1,param_2,param_3); else debug_print(0); }
    return 0;
  }
  if (2 < *lvl) { if(*g8==0) DEBUG_PRINT("%s(): BLE_REQ_POST_NOTIFICATION_MSG source:%d\n" /*=0xa7f12*/,"post_notification_cmd_response" /*=0xa831f*/,VB(param_4+1),0,param_1,param_2,param_3); else debug_print(0); }
  if (VB(param_4+1) == 4) {
    strncpy_zero_pad(VI(param_1+0xff8)+8, param_2+0x54, 0x10);
    strncpy_zero_pad(VI(param_1+0xff8)+0x19, param_2+0x94, 0x96);
    { int p3=VI(param_1+0xff8); VB(p3)=0; VB(p3+1)=0; VB(p3+2)=0; VB(p3+3)=0; }
    if (VB(param_1+0xd5)==0) VB(param_1+0xb0d)=1;
    if (2 < *lvl) { if(*g8==0) DEBUG_PRINT("%s(): schedule_notif#title:%s, desc:%s, ts:%d, date:%s\n" /*=0xa7f41*/,"post_notification_cmd_response" /*=0xa831f*/); else debug_print("%s(): schedule_notif#title:%s, desc:%s, ts:%d, date:%s\n" /*=0xa7f41*/); }
  } else {
    if (VH(param_4+2) != 0x1b4) {
      if (*lvl < 1) return 0;
      if (*g8 != 0) { debug_print("%s(): [%s-%d] invliad  message len, data_len is %d\n\n" /*=0xa7f79*/,"post_notification_cmd_response" /*=0xa831f*/,"post_notification_cmd_response" /*=0xa8300*/); return 0; }
      DEBUG_PRINT("%s(): [%s-%d] invliad  message len, data_len is %d\n\n" /*=0xa7f79*/,"post_notification_cmd_response" /*=0xa831f*/,"post_notification_cmd_response" /*=0xa8300*/,0x158,VH(param_4+2),param_2,param_3); return 0;
    }
    if ((unsigned int)VI(param_2+0x1b4) < 2) {
      iVar5 = is_on_whitelist_by_identifier(param_2+0x14);
      if ((((unsigned int)(iVar5-2)) & 0xff) > 1) { if (iVar5 == 1) send_data_in_ble_chunks(param_2+4); }
      else push_message(param_2+4);
    } else push_message(param_2+4);
  }
  if (VB(param_3+1) == 4) {
    if (*lvl < 3) goto LAB_341a8;
    iVar5 = *g8; format = ((uintptr_t)&tbl_a7e85) /*=0xa7fae*/;
  } else {
    if (VB(param_3+1) != 6 || *lvl < 3) goto LAB_341a8;
    iVar5 = *g8; format = ((uintptr_t)&rodata_a7fe3) /*=0xa7fe3*/;
  }
  if (iVar5 == 0) DEBUG_PRINT(format,"post_notification_cmd_response" /*=0xa831f*/); else debug_print(0);
LAB_341a8:
  { int d="Good" /*=0xa1f49*/; *(volatile int*)param_6 = VI(d); *(volatile unsigned char*)((int)param_6+4)=VB(d+4); }
  return 5;
}

