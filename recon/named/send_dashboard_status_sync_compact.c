/* named: send_dashboard_status_sync_compact */
/* Reconstructed send_dashboard_status_sync_compact @ 0x3af04  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int get_device_info(void);
extern int sync_dashboard_default_language(void);
extern int getStocksIndex(void);
extern int getNewsIndex(void);
extern void send_response_data_to_msgqueue(void*,int);
extern void send_response_data_to_ble(void);
void send_dashboard_status_sync_compact(uint32_t p1,uint32_t p2,uint32_t p3,uint32_t p4){
  char* pcVar3=(char*)get_device_info();
  if(*(volatile int8_t*)pcVar3==2) return;
  int iVar4=get_device_info();
  volatile uint8_t cVar2b=*(volatile uint8_t*)(*(volatile int*)(iVar4+0xfec)+0x64);
  (void)cVar2b;
  int cVar2=*(volatile int8_t*)0x2000496aUL;
  if(cVar2==0){ (void)sync_dashboard_default_language(); }
  else if(cVar2==1){ (void)getStocksIndex(); }
  else if(cVar2==2){ (void)getNewsIndex(); }
  send_response_data_to_msgqueue((void*)0,8);
  send_response_data_to_ble();
}

