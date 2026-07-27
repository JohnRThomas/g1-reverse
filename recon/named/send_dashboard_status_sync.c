/* readable reconstruction; identity: FUN_0003ae6c @ 0x0003ae6c
 * public-name: send_dashboard_status_sync
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   msg_content_recalc_unread                <= FUN_00033cf8 @ 0x00033cf8
 *   sync_dashboard_default_language          <= FUN_00037060 @ 0x00037060
 *   getStocksIndex                           <= FUN_000370bc @ 0x000370bc
 *   getNewsIndex                             <= FUN_0003719c @ 0x0003719c
 *   send_dashboard_status_sync               <= FUN_0003ae6c @ 0x0003ae6c
 *   send_response_data_to_msgqueue           <= FUN_00047b1c @ 0x00047b1c
 *   send_response_data_to_ble                <= FUN_00047ba8 @ 0x00047ba8
 * address symbols (name @ address):
 *   g_dashboard_widget_state                 @ 0x20004950
 */
/* Reconstructed FUN_0003ae6c @ 0x3ae6c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef uint32_t u32; typedef uint8_t u8;
extern int get_device_info(void);
extern int msg_content_recalc_unread(void);
extern unsigned long sync_dashboard_default_language(void);
extern unsigned long getStocksIndex(void);
extern unsigned long getNewsIndex(void);
extern unsigned int send_response_data_to_msgqueue(void*, unsigned int);
extern void send_response_data_to_ble(void);
void send_dashboard_status_sync(u32 param_1,u32 param_2,u32 param_3,u32 param_4){
    u32 local[4];
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
    u8 cVar2 = *(volatile u8*)(0x20004950UL+0x1a);
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
