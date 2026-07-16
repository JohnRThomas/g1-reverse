/* Reconstructed FUN_0007118c @ 0x7118c */
#include <stdint.h>
extern void FUN_000859b6(void *); extern void FUN_000859b2(void *);
extern void *FUN_00085734(void *,uint32_t *,uint16_t *); extern void *FUN_00085900(void *,int,uint32_t,uint32_t);
extern int FUN_0008567c(void *,const void *,int,int,void *); extern void FUN_000857e0(void *);
extern void FUN_0007e2fa(uint32_t,...); extern void FUN_0007e2ec(uint32_t,uint32_t);
typedef int (*send_fn)(void *,void *,uint16_t,uint32_t,uint32_t);
void FUN_0007118c(uint8_t **arg)
{
    uint8_t *ctx=*(uint8_t **)(*arg+0x24), *lock=ctx+0x58; uint32_t aux; uint16_t n;
    FUN_000859b6(lock);
    if (*(uint32_t *)(*(uint8_t **)(ctx+0xa0)+0x18)) { FUN_000859b2(lock); return; }
    uint32_t *msg=FUN_00085734(*(void **)(ctx+0xa4),&aux,&n); FUN_000859b2(lock);
    while (msg) {
        msg[2]=n; FUN_000859b6(lock);
        uint8_t *dst=FUN_00085900(ctx,0,msg[1],UINT32_MAX); FUN_000859b2(lock);
        if (dst) {
            uint32_t seq=*(uint32_t *)(dst+0x28)+1;
            if (!seq) *(uint32_t *)(dst+0x28)=msg[0];
            int rc=((send_fn)*(uintptr_t *)(dst+0x2c))(dst,msg+4,(uint16_t)msg[3],msg[0],*(uint32_t *)(dst+0x3c));
            if (rc<0) { FUN_0007e2fa(0x99cbd,0xf7c0e,0xf7ba6,0x245); FUN_0007e2ec(0xf7ba6,0x245); }
        }
        FUN_000859b6(lock);
        if ((int32_t)msg[2]>=0) {
            if (*(uint32_t *)(*(uint8_t **)(ctx+0xa0)+0x18)) goto stop;
            struct { void *msg; uint32_t aux; } e={msg,aux}; FUN_0008567c(*(void **)(ctx+0xa4),&e,0,1,msg);
        }
        if (*(uint32_t *)(*(uint8_t **)(ctx+0xa0)+0x18)) goto stop;
        msg=FUN_00085734(*(void **)(ctx+0xa4),&aux,&n);
        if (!msg) goto stop;
        FUN_000859b2(lock);
    }
    return;
stop: FUN_000857e0(*(void **)(ctx+0xa4)); FUN_000859b2(lock);
}
