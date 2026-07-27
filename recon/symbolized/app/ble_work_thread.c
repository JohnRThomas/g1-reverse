#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00021da8 @ 0x00021da8
 * public-name: ble_work_thread
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   dequeue_bt_data                          <= FUN_000181b8 @ 0x000181b8
 *   bt_start                                 <= FUN_00019308 @ 0x00019308
 *   ancs_main                                <= FUN_00019950 @ 0x00019950
 *   debug_log_queue_init                     <= FUN_00019bd0 @ 0x00019bd0
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   ble_packet_receive_dispatch              <= FUN_00021d78 @ 0x00021d78
 *   z_impl_k_sem_take                        <= FUN_00072908 @ 0x00072908
 *   k_sleep                                  <= FUN_00074844 @ 0x00074844
 *   malloc                                   <= FUN_00076d6c @ 0x00076d6c
 *   device_resume_state_advance              <= FUN_0007c108 @ 0x0007c108
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_9ded0                             @ 0x0009ded0   [INLINED -- G6 literal batch]
 *   rodata_9dede                             @ 0x0009dede   [INLINED -- G6 literal batch]
 *   rodata_9deed                             @ 0x0009deed   [INLINED -- G6 literal batch]
 *   rodata_9df00                             @ 0x0009df00   [INLINED -- G6 literal batch]
 *   rodata_9df28                             @ 0x0009df28   [INLINED -- G6 literal batch]
 *   rodata_9df51                             @ 0x0009df51   [INLINED -- G6 literal batch]
 *   rodata_9df99                             @ 0x0009df99   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_send_event_pending_id                  @ 0x2000302e
 *   g_ring_log_pending                       @ 0x20007550
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_20018da9                               @ 0x20018da9
 */
/* Full reconstruction ble_work_thread @ 0x21da8, exact extent 578 bytes.
 * CFG_VERIFY_PREFIX_FIRST CFG_VERIFY_PREFIX_K=80 */
#include <stdint.h>
#include "../../headers/g1_log.h"
extern int ancs_main(uintptr_t);
extern void debug_log_queue_init(void);
extern uintptr_t malloc(uint32_t);
extern uintptr_t get_device_info(void);
extern void k_sleep(uint32_t,uint32_t);
extern uint64_t dequeue_bt_data(void*);
extern void z_impl_k_sem_take(uintptr_t,uint32_t,uint32_t,uint32_t);
extern void ble_packet_receive_dispatch(unsigned int, unsigned int, int);
extern int device_resume_state_advance(void);
extern int bt_start(void);
extern void memcpy(void*,const void*,uint32_t);
extern void memset_bytes(void*,int,uint32_t);

static __attribute__((always_inline)) inline void
ble_log(uintptr_t format, uint32_t value, int threshold)
{
    if (*(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/ > threshold) {
        int alternate=*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
        if (alternate) debug_print(format,((unsigned long)"ble_work_thread") /*=0x9df99*/,value,(uint32_t)alternate);
        else log_message(format,((unsigned long)"ble_work_thread") /*=0x9df99*/,value,(uint32_t)alternate);
    }
}

/* Zephyr thread entries have the p1/p2/p3 ABI even though this worker uses
 * only p1.  The first diagnostic leaves incoming r2 intact, so name p3 and
 * forward it rather than manufacturing a padding value. */
void ble_work_thread(uintptr_t context, uintptr_t unused_p2, uint32_t p3)
{
    (void)unused_p2;
    ble_log(((unsigned long)"%s(): start\n\n") /*=0x9ded0*/,p3,2);
    int rc=ancs_main(context);
    debug_log_queue_init();
    if(rc) ble_log(((unsigned long)"%s(): err:%d\n\n") /*=0x9dede*/,(uint32_t)rc,2);
    *(volatile uintptr_t*)(context+0x10)=malloc(0x2b8);
    ble_log(((unsigned long)"%s(): tx_size:%d\n\n") /*=0x9deed*/,0x2b8,2);

    uint8_t packet[260];
    for (;;) {
        uintptr_t owner;
        do {
            owner=get_device_info();
            if ((int32_t)((uint32_t)*(volatile uint16_t*)(owner+0x105c)<<24)>=0)
                k_sleep(0x8000,0);
            else break;
        } while(1);

        uint64_t received=dequeue_bt_data(packet);
        if ((uint32_t)received==0) {
            uint32_t length=packet[0];
            if(length<0x15) {
                memcpy(*(void**)(context+0x254),packet+1,length);
                *(volatile uint32_t*)(context+0x35c)=1;
                *(volatile uint32_t*)(context+0x358)=0;
                *(volatile uint32_t*)(context+0x360)=length;
            } else {
                memcpy((void*)(context+0x258),packet+1,length);
                *(volatile uint32_t*)(context+0x358)=length;
            }
        } else {
            *(volatile uint8_t*)(context+0x248)=0;
            z_impl_k_sem_take(context+0x218,(uint32_t)(received>>32),0xffffffffu,0xffffffffu);
            *(volatile uint8_t*)(context+0x248)=1;
            if (*(volatile uint32_t*)(context+0x35c)==0 &&
                *(volatile uint32_t*)(context+0x358)==0) {
                uint8_t pending=*(volatile uint8_t*)((unsigned long)&g_send_event_pending_id) /*=0x2000302e*/;
                uint8_t *out=*(uint8_t**)(context+0x254);
                if(pending!=0xff) {
                    *(volatile uint32_t*)(context+0x35c)=1;
                    out[0]=0xf5; out[1]=pending;
                    *(volatile uint8_t*)((unsigned long)&g_send_event_pending_id) /*=0x2000302e*/=0xff;
                    out[2]=0xcb;
                    *(volatile uint32_t*)(context+0x358)=0;
                    *(volatile uint32_t*)(context+0x360)=3;
                    if((uint8_t)(pending-9)<2) out[2]=*(uint8_t*)(context+0x18);
                } else if(*(volatile uint8_t*)((unsigned long)&g_20018da9) /*=0x20018da9*/) {
                    *(volatile uint32_t*)(context+0x35c)=1;
                    out[0]=0xf1;
                    *(volatile uint8_t*)((unsigned long)&g_20018da9) /*=0x20018da9*/=0;
                    out[1]=0; out[2]=0xcc;
                    *(volatile uint32_t*)(context+0x358)=0;
                } else if(*(volatile uint32_t*)((unsigned long)&g_ring_log_pending) /*=0x20007550*/) {
                    *(volatile uint32_t*)(context+0x35c)=1;
                    out[0]=0xf4; out[1]=0; out[2]=0xcb;
                    *(volatile uint32_t*)((unsigned long)&g_ring_log_pending) /*=0x20007550*/=0;
                    *(volatile uint32_t*)(context+0x358)=0;
                } else continue;
            }
        }

        if (*(volatile uint8_t*)(context+0x364)==0) {
            uint32_t long_length=*(volatile uint32_t*)(context+0x358);
            if(long_length) {
                ble_packet_receive_dispatch((void*)(context+0x258),long_length,0);
                memset_bytes((void*)(context+0x258),0,0x100);
            } else {
                uint32_t slot=*(volatile uint32_t*)(context+0x35c);
                void *buffer=*(void**)(context+0x250+slot*4);
                ble_packet_receive_dispatch(buffer,*(volatile uint32_t*)(context+0x360),0);
            }
            *(volatile uint32_t*)(context+0x358)=0;
            *(volatile uint32_t*)(context+0x35c)=0;
        } else {
            int state=device_resume_state_advance();
            if(state==0) {
                ble_log(((unsigned long)"%s(): charge plug off, call bt_start. \n\n") /*=0x9df28*/,0,2);
                int error=bt_start();
                if(error) log_message(((unsigned long)"Advertising failed to start (err %d)\n") /*=0x9df51*/,(uint32_t)error,0,
                                      *(volatile uint32_t*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/);
            } else {
                ble_log(((unsigned long)"%s(): bt_le_adv_stop failed!!! err=%d\n\n") /*=0x9df00*/,(uint32_t)state,1);
            }
            *(volatile uint8_t*)(context+0x364)=0;
        }
    }
}
