/* Full reconstruction ble_work_thread @ 0x21da8, exact extent 578 bytes.
 * CFG_VERIFY_PREFIX_FIRST CFG_VERIFY_PREFIX_K=80 */
#include <stdint.h>
extern int FUN_00019950(uintptr_t);
extern void FUN_00019bd0(void);
extern uintptr_t FUN_00076d6c(uint32_t);
extern uintptr_t FUN_000167a8(void);
extern void FUN_00074844(uint32_t,uint32_t);
extern uint64_t FUN_000181b8(void*);
extern void FUN_00072908(uintptr_t,uint32_t,uint32_t,uint32_t);
extern void FUN_00021d78(unsigned int, unsigned int, int);
extern int FUN_0007c108(void);
extern int FUN_00019308(void);
extern void FUN_00086c04(void*,const void*,uint32_t);
extern void FUN_00086c78(void*,int,uint32_t);
extern void DEBUG_PRINT(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);

static __attribute__((always_inline)) inline void
ble_log(uintptr_t format, uint32_t value, int threshold)
{
    if (*(volatile int*)0x2000230cu > threshold) {
        int alternate=*(volatile int*)0x20007554u;
        if (alternate) FUN_00019c70(format,0x0009df99u,value,(uint32_t)alternate);
        else DEBUG_PRINT(format,0x0009df99u,value,(uint32_t)alternate);
    }
}

/* Zephyr thread entries have the p1/p2/p3 ABI even though this worker uses
 * only p1.  The first diagnostic leaves incoming r2 intact, so name p3 and
 * forward it rather than manufacturing a padding value. */
void ble_work_thread(uintptr_t context, uintptr_t unused_p2, uint32_t p3)
{
    (void)unused_p2;
    ble_log(0x0009ded0u,p3,2);
    int rc=FUN_00019950(context);
    FUN_00019bd0();
    if(rc) ble_log(0x0009dedeu,(uint32_t)rc,2);
    *(volatile uintptr_t*)(context+0x10)=FUN_00076d6c(0x2b8);
    ble_log(0x0009deedu,0x2b8,2);

    uint8_t packet[260];
    for (;;) {
        uintptr_t owner;
        do {
            owner=FUN_000167a8();
            if ((int32_t)((uint32_t)*(volatile uint16_t*)(owner+0x105c)<<24)>=0)
                FUN_00074844(0x8000,0);
            else break;
        } while(1);

        uint64_t received=FUN_000181b8(packet);
        if ((uint32_t)received==0) {
            uint32_t length=packet[0];
            if(length<0x15) {
                FUN_00086c04(*(void**)(context+0x254),packet+1,length);
                *(volatile uint32_t*)(context+0x35c)=1;
                *(volatile uint32_t*)(context+0x358)=0;
                *(volatile uint32_t*)(context+0x360)=length;
            } else {
                FUN_00086c04((void*)(context+0x258),packet+1,length);
                *(volatile uint32_t*)(context+0x358)=length;
            }
        } else {
            *(volatile uint8_t*)(context+0x248)=0;
            FUN_00072908(context+0x218,(uint32_t)(received>>32),0xffffffffu,0xffffffffu);
            *(volatile uint8_t*)(context+0x248)=1;
            if (*(volatile uint32_t*)(context+0x35c)==0 &&
                *(volatile uint32_t*)(context+0x358)==0) {
                uint8_t pending=*(volatile uint8_t*)0x2000302eu;
                uint8_t *out=*(uint8_t**)(context+0x254);
                if(pending!=0xff) {
                    *(volatile uint32_t*)(context+0x35c)=1;
                    out[0]=0xf5; out[1]=pending;
                    *(volatile uint8_t*)0x2000302eu=0xff;
                    out[2]=0xcb;
                    *(volatile uint32_t*)(context+0x358)=0;
                    *(volatile uint32_t*)(context+0x360)=3;
                    if((uint8_t)(pending-9)<2) out[2]=*(uint8_t*)(context+0x18);
                } else if(*(volatile uint8_t*)0x20018da9u) {
                    *(volatile uint32_t*)(context+0x35c)=1;
                    out[0]=0xf1;
                    *(volatile uint8_t*)0x20018da9u=0;
                    out[1]=0; out[2]=0xcc;
                    *(volatile uint32_t*)(context+0x358)=0;
                } else if(*(volatile uint32_t*)0x20007550u) {
                    *(volatile uint32_t*)(context+0x35c)=1;
                    out[0]=0xf4; out[1]=0; out[2]=0xcb;
                    *(volatile uint32_t*)0x20007550u=0;
                    *(volatile uint32_t*)(context+0x358)=0;
                } else continue;
            }
        }

        if (*(volatile uint8_t*)(context+0x364)==0) {
            uint32_t long_length=*(volatile uint32_t*)(context+0x358);
            if(long_length) {
                FUN_00021d78((void*)(context+0x258),long_length,0);
                FUN_00086c78((void*)(context+0x258),0,0x100);
            } else {
                uint32_t slot=*(volatile uint32_t*)(context+0x35c);
                void *buffer=*(void**)(context+0x250+slot*4);
                FUN_00021d78(buffer,*(volatile uint32_t*)(context+0x360),0);
            }
            *(volatile uint32_t*)(context+0x358)=0;
            *(volatile uint32_t*)(context+0x35c)=0;
        } else {
            int state=FUN_0007c108();
            if(state==0) {
                ble_log(0x0009df28u,0,2);
                int error=FUN_00019308();
                if(error) DEBUG_PRINT(0x0009df51u,(uint32_t)error,0,
                                      *(volatile uint32_t*)0x20007554u);
            } else {
                ble_log(0x0009df00u,(uint32_t)state,1);
            }
            *(volatile uint8_t*)(context+0x364)=0;
        }
    }
}
