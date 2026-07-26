/* readable reconstruction; identity: FUN_00062930 @ 0x00062930
 * public-name: opt3001_chip_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_log_msg_runtime_create                 <= FUN_0004d944 @ 0x0004d944
 *   opt3001_chip_init                        <= FUN_00062930 @ 0x00062930
 *   i2c_read_reg16_be                        <= FUN_000847d8 @ 0x000847d8
 *   z_device_is_ready                        <= FUN_0008638c @ 0x0008638c
 * address symbols (name @ address):
 *   rodata_88250                             @ 0x00088250
 *   rodata_f6521                             @ 0x000f6521   [INLINED -- G6 literal batch]
 *   rodata_f6539                             @ 0x000f6539   [INLINED -- G6 literal batch]
 *   rodata_f6552                             @ 0x000f6552   [INLINED -- G6 literal batch]
 *   rodata_f6565                             @ 0x000f6565   [INLINED -- G6 literal batch]
 */
/* Full reconstruction FUN_00062930 @ 0x62930, exact extent 222 bytes. */
#include <stdint.h>
extern int z_log_msg_runtime_create(uintptr_t,uint32_t,void*,...);
extern int i2c_read_reg16_be(void*,uint32_t,void*,int);
extern int z_device_is_ready(uintptr_t);
typedef int (*transfer_fn)(uintptr_t,void*,uint32_t,int16_t);

static __attribute__((always_inline)) inline void
report_descriptor(uint8_t frame[32], uint32_t flags, uintptr_t text, uint32_t value)
{
    *(uint32_t *)(frame+0)=flags;
    *(uintptr_t *)(frame+4)=text;
    *(uint32_t *)(frame+8)=value;
    z_log_msg_runtime_create(0x00088250u,flags==3?0x1840:0x1040,frame);
}

uint32_t opt3001_chip_init(uintptr_t request)
{
    uint8_t frame[32];
    void *device=*(void **)(request+4);
    uintptr_t instance=*(uintptr_t *)device;
    if(z_device_is_ready(instance)==0) {
        *(uint32_t *)(frame+24)=2;
        *(uintptr_t *)(frame+28)=0x000f6521u;
        z_log_msg_runtime_create(0x00088250u,0x1040,frame+24,0);
        return 0xffffffea;
    }
    uint16_t value;
    if(i2c_read_reg16_be(device,0x7e,&value,1)!=0) return 0xffffffea;
    if(value!=0x5449) { report_descriptor(frame,3,0x000f6539u,value); return 0xffffffea; }
    if(i2c_read_reg16_be(device,0x7f,&value,0)!=0) return 0xffffffea;
    if(value!=0x3001) { report_descriptor(frame,3,0x000f6552u,value); return 0xffffffea; }
    if(i2c_read_reg16_be(device,1,&value,0)==0) {
        frame[4]=1;
        frame[5]=(uint8_t)(((value&0xf9ffu)>>8)|6u);
        frame[6]=(uint8_t)(value&0xf9ffu);
        void *payload=frame+4;
        *(void **)(frame+8)=payload;
        *(uint32_t *)(frame+12)=3;
        frame[16]=2;
        uintptr_t vtable=*(uintptr_t *)(instance+8);
        transfer_fn transfer=*(transfer_fn *)(vtable+8);
        if(transfer(instance,frame+8,1,(int16_t)*(uint32_t *)((uint8_t*)device+4))==0)
            return 0;
    }
    *(uint32_t *)(frame+24)=2;
    *(uintptr_t *)(frame+28)=0x000f6565u;
    z_log_msg_runtime_create(0x00088250u,0x1040,frame+24,0);
    return 0xffffffea;
}
