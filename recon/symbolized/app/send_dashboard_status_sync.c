#include "g1_app_symbols.h"
/* named: send_dashboard_status_sync */
/* globals referenced:
//   0x20004950  g_dashboard_widget_state     
*/
/* Reconstructed send_dashboard_status_sync @ 0x3ae6c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef uint32_t u32; typedef uint8_t u8;
extern int get_device_info(void);
extern int msg_content_recalc_unread(void);
extern int sync_dashboard_default_language(void);
extern int getStocksIndex(void);
extern int getNewsIndex(void);
extern void send_response_data_to_msgqueue(void*,int);
extern void send_response_data_to_ble(void);
void send_dashboard_status_sync(u32 param_1,u32 param_2,u32 param_3,u32 param_4){
    u32 local[5];
    local[0]=param_1; local[1]=param_2; local[2]=param_3; local[3]=param_4;
    char* pcVar3 = (char*)get_device_info();
    if(*pcVar3 == 2) return;
    local[0]=0xa22; local[2]=0; local[3]=0; local[1]=1;
    int uVar1 = msg_content_recalc_unread();
    ((u8*)local)[5] = (u8)uVar1;
    int iVar4;
    iVar4 = get_device_info();
    ((u8*)local)[6] = *(u8*)(*(int*)(iVar4+0xfec)+0x5f);
    iVar4 = get_device_info();
    ((u8*)local)[7] = *(u8*)(*(int*)(iVar4+0xfec)+0x64);
    iVar4 = get_device_info();
    ((u8*)local)[8] = *(u8*)(*(int*)(iVar4+0xfec)+0x65);
    char cVar2 = *(volatile char*)(((uintptr_t)&g_dashboard_widget_state) /*=0x20004950*/+0x1a);
    if(cVar2 == 0){ cVar2 = (char)sync_dashboard_default_language(); }
    else if(cVar2 == 1){ cVar2 = (char)getStocksIndex(); }
    else {
        if(cVar2 != 2) goto LAB;
        cVar2 = (char)getNewsIndex();
    }
    ((u8*)local)[9] = (u8)(cVar2 + 1);
LAB:
    send_response_data_to_msgqueue(local, 10);
    send_response_data_to_ble();
}

