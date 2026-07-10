/* named: FUN_0004d100 */
/* Reconstructed FUN_0004d100 @ 0x4d100  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef uint32_t u32;
extern u32 rpmsg_virtqueue_channel_init(int,...);
extern void rpmsg_virtio_init_shm_pool(int,int,u32);
u32 FUN_0004d100(int p1,int p2,int* p3,u32 p4,u32 p5,int p6,u32 p7,int p8){
    if(p1==0 || p6==0) return 0xffffffea;
    if(p8==0) p8 = 0x0004d059;
    if(p2 != 0){
        return rpmsg_virtqueue_channel_init(p1+0xe0, p5, p8, p4, 0);
    }
    rpmsg_virtio_init_shm_pool(p1+0x19c, p6, p7);
    return rpmsg_virtqueue_channel_init(p1+0xe0, p5, p8, p4, p1+0x19c, 0);
}

