#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0004d100 @ 0x0004d100
 * public-name: rpmsg_virtio_init_vdev
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   rpmsg_virtio_init_vdev                   <= FUN_0004d100 @ 0x0004d100
 *   rpmsg_virtqueue_channel_init             <= FUN_00071358 @ 0x00071358
 *   rpmsg_init_vdev                          <= FUN_00071560 @ 0x00071560
 *   rpmsg_virtio_init_shm_pool               <= FUN_00085be8 @ 0x00085be8
 * address symbols (name @ address):
 *   ADDR_FUN_0004d058_THUMB                  @ 0x0004d059
 */
/* Reconstructed FUN_0004d100 @ 0x4d100  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef uint32_t u32;
extern u32 rpmsg_virtqueue_channel_init(int,...);
extern u32 rpmsg_init_vdev(int,...);
extern void rpmsg_virtio_init_shm_pool(int,int,u32);
u32 rpmsg_virtio_init_vdev(int p1,int p2,int* p3,u32 p4,u32 p5,int p6,u32 p7,int p8){
    if(p1==0 || p6==0) return 0xffffffea;
    if(p8==0) p8 = ADDR_FUN_0004d058_THUMB /*=0x4d059*/;
    if(p2 != 0){
        return rpmsg_init_vdev(p1+0xe0, p5, p8, p4, 0);
    }
    struct { int *first; int *second; int zero; } request = { p3, p3, 0 };
    rpmsg_virtio_init_shm_pool(p1+0x19c, p6, p7);
    return rpmsg_virtqueue_channel_init(p1+0xe0, p5, p8, p4, p1+0x19c, &request);
}
