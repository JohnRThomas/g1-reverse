/* readable reconstruction; identity: FUN_0007118c @ 0x0007118c
 * public-name: rpmsg_virtio_rx_notify
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   rpmsg_virtio_rx_notify                   <= FUN_0007118c @ 0x0007118c
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   virtqueue_add_buffer                     <= FUN_0008567c @ 0x0008567c
 *   virtqueue_get_buffer                     <= FUN_00085734 @ 0x00085734
 *   dma_xfer_end_handler                     <= FUN_000857e0 @ 0x000857e0
 *   rpmsg_get_endpoint                       <= FUN_00085900 @ 0x00085900
 *   mutex_lock_wait_forever_dup              <= FUN_000859b6 @ 0x000859b6
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f7ba6                             @ 0x000f7ba6
 *   rodata_f7c0e                             @ 0x000f7c0e
 */
/* Reconstructed FUN_0007118c @ 0x7118c */
#include <stdint.h>
extern void mutex_lock_wait_forever_dup(void *); extern void FUN_000859b2(void *);
extern void *virtqueue_get_buffer(void *,uint32_t *,uint16_t *); extern void *rpmsg_get_endpoint(void *,int,uint32_t,uint32_t);
extern int virtqueue_add_buffer(void *,const void *,int,int,void *); extern void dma_xfer_end_handler(void *);
extern void printk(uint32_t,...); extern void assert_post_action(uint32_t,uint32_t);
typedef int (*send_fn)(void *,void *,uint16_t,uint32_t,uint32_t);
void rpmsg_virtio_rx_notify(uint8_t **arg)
{
    uint8_t *ctx=*(uint8_t **)(*arg+0x24), *lock=ctx+0x58; uint32_t aux; uint16_t n;
    mutex_lock_wait_forever_dup(lock);
    if (*(uint32_t *)(*(uint8_t **)(ctx+0xa0)+0x18)) { FUN_000859b2(lock); return; }
    uint32_t *msg=virtqueue_get_buffer(*(void **)(ctx+0xa4),&aux,&n); FUN_000859b2(lock);
    while (msg) {
        msg[2]=n; mutex_lock_wait_forever_dup(lock);
        uint8_t *dst=rpmsg_get_endpoint(ctx,0,msg[1],UINT32_MAX); FUN_000859b2(lock);
        if (dst) {
            uint32_t seq=*(uint32_t *)(dst+0x28)+1;
            if (!seq) *(uint32_t *)(dst+0x28)=msg[0];
            int rc=((send_fn)*(uintptr_t *)(dst+0x2c))(dst,msg+4,(uint16_t)msg[3],msg[0],*(uint32_t *)(dst+0x3c));
            if (rc<0) { printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"),0xf7c0e,0xf7ba6,0x245); assert_post_action(0xf7ba6,0x245); }
        }
        mutex_lock_wait_forever_dup(lock);
        if ((int32_t)msg[2]>=0) {
            if (*(uint32_t *)(*(uint8_t **)(ctx+0xa0)+0x18)) goto stop;
            struct { void *msg; uint32_t aux; } e={msg,aux}; virtqueue_add_buffer(*(void **)(ctx+0xa4),&e,0,1,msg);
        }
        if (*(uint32_t *)(*(uint8_t **)(ctx+0xa0)+0x18)) goto stop;
        msg=virtqueue_get_buffer(*(void **)(ctx+0xa4),&aux,&n);
        if (!msg) goto stop;
        FUN_000859b2(lock);
    }
    return;
stop: dma_xfer_end_handler(*(void **)(ctx+0xa4)); FUN_000859b2(lock);
}
