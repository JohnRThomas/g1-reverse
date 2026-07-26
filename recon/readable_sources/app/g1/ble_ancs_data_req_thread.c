#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_app_ble_ctx_block__param_0038          [param_0038; G1-original]
 * Raw function identity: 0x00019718.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00019718 @ 0x00019718
 * public-name: ble_ancs_data_req_thread
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   init_msgq_ancs                           <= FUN_00018b6c @ 0x00018b6c
 *   enqueue_ancs                             <= FUN_00018bb4 @ 0x00018bb4
 *   init_msgq_uid                            <= FUN_00018e04 @ 0x00018e04
 *   dequeue_uid                              <= FUN_00018ff8 @ 0x00018ff8
 *   request_ancs_attr_ext                    <= FUN_000191e4 @ 0x000191e4
 *   ancs_notification_forward                <= FUN_0001965c @ 0x0001965c
 *   ble_ancs_data_req_thread                 <= FUN_00019718 @ 0x00019718
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   z_impl_k_sem_take                        <= FUN_00072908 @ 0x00072908
 *   k_msleep_ticks32768_d                    <= FUN_0007c0a8 @ 0x0007c0a8
 *   z_impl_k_sem_init                        <= FUN_00086534 @ 0x00086534
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_28000                             @ 0x00028000
 *   rodata_99969                             @ 0x00099969
 *   rodata_9adc7                             @ 0x0009adc7   [INLINED -- G6 literal batch]
 *   rodata_9adf5                             @ 0x0009adf5   [INLINED -- G6 literal batch]
 *   rodata_9ae34                             @ 0x0009ae34   [INLINED -- G6 literal batch]
 *   rodata_9ae92                             @ 0x0009ae92   [INLINED -- G6 literal batch]
 *   rodata_9aef3                             @ 0x0009aef3   [INLINED -- G6 literal batch]
 *   rodata_9b0d8                             @ 0x0009b0d8   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_ancs_notif_evt_id_latest               @ 0x20006aac
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed FUN_00019718 @ 0x19718 CFG_VERIFY_PREFIX_FIRST */
#include <stdint.h>
extern void z_impl_k_sem_init(void*,int,int),init_msgq_ancs(void),init_msgq_uid(void),wait_for_event(int,int);
extern uint8_t *get_device_info(void); extern void k_msleep_ticks32768_d(int);
extern void z_impl_k_sem_take(void*,int64_t);
extern int dequeue_uid(void*); extern int request_ancs_attr_ext(void); extern void enqueue_ancs(void*),memset_bytes(void*,int,int),ancs_notification_forward(void*);
extern void log_message(uint32_t,...),debug_print(uint32_t,...);
void ble_ancs_data_req_thread(uint8_t *c,uint32_t p2,uint32_t p3,uint32_t p4){
 volatile int *lv=(int*)((unsigned long)&g_log_level) /*=0x2000230c*/,*sink=(int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/; volatile uint32_t *ev=(uint32_t*)((unsigned long)&g_ancs_notif_evt_id_latest) /*=0x20006aac*/;
 if(*lv>2){if(!*sink)log_message(((unsigned long)&rodata_99969) /*=0x99969*/,((unsigned long)"ble_ancs_data_req_thread") /*=0x9b0d8*/,p3,0,p4);else debug_print(((unsigned long)&rodata_99969) /*=0x99969*/,((unsigned long)"ble_ancs_data_req_thread") /*=0x9b0d8*/,p3,*sink,p4);}
 z_impl_k_sem_init(c+0x200,0,10);z_impl_k_sem_init(c+0x1e8,0,10);init_msgq_ancs();init_msgq_uid();wait_for_event(((unsigned long)&rodata_28000) /*=0x28000*/,0);
 for(;;){uint8_t*g=get_device_info();if(g[1]==1){wait_for_event(((unsigned long)&rodata_28000) /*=0x28000*/,0);continue;}g=get_device_info();if(g[1]==8){wait_for_event(((unsigned long)&rodata_28000) /*=0x28000*/,0);continue;}g=get_device_info();
  if((*(uint16_t*)(g+0x105c)&0x80)==0){k_msleep_ticks32768_d(1000);continue;}
  if(*lv>0){if(!*sink)log_message(((unsigned long)"%s(): !!!!!!!!!wait -> ancs_get_attr_req_sem\n") /*=0x9adc7*/,((unsigned long)"ble_ancs_data_req_thread") /*=0x9b0d8*/);else debug_print(((unsigned long)"%s(): !!!!!!!!!wait -> ancs_get_attr_req_sem\n") /*=0x9adc7*/,((unsigned long)"ble_ancs_data_req_thread") /*=0x9b0d8*/);}z_impl_k_sem_take(c+0x200,-1LL);
  if(dequeue_uid((void*)ev)==0){if(*lv>0){if(!*sink)log_message(((unsigned long)"%s(): !!!!!!!!!!!!!!get -> ancs_get_attr_req_sem %d evt_id %d\n") /*=0x9adf5*/,((unsigned long)"ble_ancs_data_req_thread") /*=0x9b0d8*/,*ev,((uint8_t*)ev)[4]);else debug_print(((unsigned long)"%s(): !!!!!!!!!!!!!!get -> ancs_get_attr_req_sem %d evt_id %d\n") /*=0x9adf5*/,((unsigned long)"ble_ancs_data_req_thread") /*=0x9b0d8*/,*ev,((uint8_t*)ev)[4]);}
   if(((uint8_t*)ev)[4]<2){(void)request_ancs_attr_ext();if(*lv>0){if(!*sink)log_message(((unsigned long)"%s(): !!!!!!!!!!!!wait -> ancs_get_attr_req_sem add done, and wait -> ancs_get_attr_data_sem\n") /*=0x9ae34*/,((unsigned long)"ble_ancs_data_req_thread") /*=0x9b0d8*/);else debug_print(((unsigned long)"%s(): !!!!!!!!!!!!wait -> ancs_get_attr_req_sem add done, and wait -> ancs_get_attr_data_sem\n") /*=0x9ae34*/,((unsigned long)"ble_ancs_data_req_thread") /*=0x9b0d8*/);}z_impl_k_sem_take(c+0x1e8,0x8000LL);}
   else{*(uint32_t*)(c+0x1e4)=2;*(uint32_t*)(c+0x3c)=*ev;c[0x41]=0;c[0x44]=0x30;c[0x64]=0x30;c[0x42]=0;enqueue_ancs(c+0x34);memset_bytes(c+0x34,0,0x1b4);if(*lv>0){if(!*sink)log_message(((unsigned long)"%s(): !!!!!!!!!!!!wait -> ancs_get_attr_req_sem remove done, and wait -> ancs_get_attr_data_sem\n") /*=0x9ae92*/,((unsigned long)"ble_ancs_data_req_thread") /*=0x9b0d8*/);else debug_print(((unsigned long)"%s(): !!!!!!!!!!!!wait -> ancs_get_attr_req_sem remove done, and wait -> ancs_get_attr_data_sem\n") /*=0x9ae92*/,((unsigned long)"ble_ancs_data_req_thread") /*=0x9b0d8*/);}}
   ancs_notification_forward(c);if(*lv>0){if(!*sink)log_message(((unsigned long)"%s(): !!!!!!!!!!!!!!!!wait -> ancs_get_attr_data_sem done\n") /*=0x9aef3*/,((unsigned long)"ble_ancs_data_req_thread") /*=0x9b0d8*/);else debug_print(((unsigned long)"%s(): !!!!!!!!!!!!!!!!wait -> ancs_get_attr_data_sem done\n") /*=0x9aef3*/,((unsigned long)"ble_ancs_data_req_thread") /*=0x9b0d8*/);}}
 }}
