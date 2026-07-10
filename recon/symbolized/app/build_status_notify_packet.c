#include "g1_app_symbols.h"
/* named: build_status_notify_packet */
/* Reconstructed build_status_notify_packet @ 0x21334  (parity: 11/300 trials, PROVEN) */
#include <stdint.h>
extern void memset_bytes(void*,int,int);
extern unsigned char get_glassbox_charge_status(void);
extern unsigned char get_glassbox_charge_percent(void);

unsigned build_status_notify_packet(int param_1, unsigned short *param_2){
  unsigned char loc[0x18];
  *(unsigned*)loc = 0;
  memset_bytes(loc+4, 0, 0x11);
  unsigned char bVar2 = *((unsigned char*)param_2 + 1);
  if(bVar2 > 0x12){
    if(bVar2 == 0xf1){
      *(unsigned short*)loc = ((uintptr_t)&rodata_c90f) /*=0xc90f*/;
      loc[2] = *(unsigned char*)(param_1 - 0x6b0);
    } else if(bVar2 == 0xf2){
      *(unsigned short*)loc = ((uintptr_t)&rodata_c94e) /*=0xc94e*/;
      loc[2] = *(unsigned char*)(param_1 - 0x6b0);
    } else if(bVar2 == 0xf0){
      *(unsigned short*)loc = ((uintptr_t)&rodata_c90d) /*=0xc90d*/;
      loc[2] = *(unsigned char*)(param_1 - 0x6af);
    } else {
      goto def;
    }
    loc[3] = *(volatile unsigned char*)((uintptr_t)&g_ble_xfer_seq_cur) /*=0x20018d9a*/;
    *(volatile unsigned char*)((uintptr_t)&g_ble_xfer_seq_cur) /*=0x20018d9a*/ = 0;
    loc[4] = *(volatile unsigned char*)((uintptr_t)&g_ble_xfer_seq_prev) /*=0x20018d99*/;
    *(volatile unsigned char*)((uintptr_t)&g_ble_xfer_seq_prev) /*=0x20018d99*/ = 0;
    goto call;
  }
  if(bVar2 <= 8) goto def;
  switch(bVar2){
  case 9:
    bVar2 = *((unsigned char*)param_2 + 2);
    *(unsigned short*)loc = *param_2;
    break;
  case 10:
    *(unsigned short*)loc = 0xaf5;
    bVar2 = *(unsigned char*)(param_1 + 0x844);
    if(bVar2 == 0x5d){
      bVar2 = (*(char*)(param_1+0x846)==0) ? 0x5e : 0x5f;
    } else if(bVar2 == 0x5e){
      bVar2 = (*(char*)(param_1+0x846)==0) ? 0x60 : 0x61;
    } else if(bVar2 == 0x5f){
      bVar2 = 0x62;
    } else if(bVar2 == 0x60){
      bVar2 = 0x63;
    } else if(bVar2 > 0x60){
      bVar2 = 0x64;
    }
    break;
  case 0xe:
    *(unsigned short*)loc = 0xef5;
    loc[2] = get_glassbox_charge_status();
    goto call;
  case 0xf:
    *(unsigned short*)loc = 0xff5;
    loc[2] = get_glassbox_charge_percent();
    goto call;
  case 0x12:
    *(unsigned short*)loc = 0x12f5;
    bVar2 = *(unsigned char*)(param_1 + 0x759);
    break;
  default:
    goto def;
  }
  loc[2] = bVar2;
  goto call;
def:
  for(;;){ __asm volatile(""); }
call:
  (*(int(**)(void*,int))(param_1 + 0xc))(loc, 0x15);
  return 0;
}

