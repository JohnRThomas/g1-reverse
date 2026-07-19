#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00071358 @ 0x00071358
 * public-name: rpmsg_virtqueue_channel_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   virtio_create_virtqueues                 <= FUN_00070e28 @ 0x00070e28
 *   rpmsg_register_endpoint                  <= FUN_00070f74 @ 0x00070f74
 *   rpmsg_virtqueue_channel_init             <= FUN_00071358 @ 0x00071358
 *   metal_io_block_set                       <= FUN_0008557c @ 0x0008557c
 *   virtqueue_add_buffer                     <= FUN_0008567c @ 0x0008567c
 *   virtqueue_ring_setup_flags               <= FUN_000857b2 @ 0x000857b2
 *   rpmsg_virtio_shm_pool_get_buffer         <= FUN_00085aee @ 0x00085aee
 *   z_impl_k_sem_init                        <= FUN_00086534 @ 0x00086534
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   ADDR_rpmsg_virtio_tx_enqueue_THUMB       @ 0x000710b5
 *   ADDR_rpmsg_virtio_rx_notify_THUMB        @ 0x0007118d
 *   ADDR_rpmsg_virtio_send_copy_THUMB        @ 0x00071295
 *   rodata_859a3                             @ 0x000859a3
 *   rodata_859b1                             @ 0x000859b1
 *   ADDR_FUN_000859c2_THUMB                  @ 0x000859c3
 *   ADDR_FUN_00085a04_THUMB                  @ 0x00085a05
 *   ADDR_virtqueue_return_rx_buffer_THUMB    @ 0x00085a9d
 *   ADDR_rpmsg_virtio_get_tx_buffer_wait_THUMB @ 0x00085b0d
 *   rodata_f7c28                             @ 0x000f7c28
 *   rodata_f7c2e                             @ 0x000f7c2e
 *   rodata_f7c34                             @ 0x000f7c34
 */
/* Reconstructed FUN_00071358 @ 0x71358  (parity: 300/300 trials, PROVEN) */
extern int virtio_create_virtqueues(int a0,int a1,int a2,void *a3,void *a4);
extern int rpmsg_register_endpoint(int a0,int a1,int a2,int a3,int a4,int a5,int a6);
extern void metal_io_block_set(int *a0,unsigned int a1,int a2,int a3);
extern int virtqueue_add_buffer(int a0,void *a1,int a2,int a3,int a4);
extern void virtqueue_ring_setup_flags(int a0);
extern int rpmsg_virtio_shm_pool_get_buffer(int a0,int a1);
extern void z_impl_k_sem_init(int a0,int a1);
extern void memset_bytes(int a0,int a1,int a2);

typedef int (*fn1_t)(int);
typedef int (*fn2_t)(int,int);

int rpmsg_virtqueue_channel_init(int param_1,int param_2,int param_3,int *param_4,int param_5,int *param_6)
{
    int uVar1, uVar3, iVar4, iVar6;
    unsigned int uVar2, uVar5;
    int local_38, local_34, local_30, local_2c, local_28, local_24;

    if (param_1 == 0) return (int)0xfffff82d;
    if (param_2 == 0) return (int)0xfffff82d;
    if (param_4 == (int*)0) return (int)0xfffff82d;

    memset_bytes(param_1, 0, 0x94);
    z_impl_k_sem_init(param_1 + 0x58, 1);
    uVar1 = ADDR_rpmsg_virtio_send_copy_THUMB /*=0x71295*/;
    *(int*)(param_1 + 0xa0) = param_2;
    *(int*)(param_1 + 0x70) = param_3;
    *(int*)(param_2 + 0x24) = param_1;
    *(int*)(param_1 + 0x78) = uVar1;
    iVar6 = *(int*)(param_1 + 0xa0);
    *(int*)(param_1 + 0x7c) = ((unsigned long)&rodata_859a3) /*=0x859a3*/;
    *(int*)(param_1 + 0x80) = ADDR_virtqueue_return_rx_buffer_THUMB /*=0x85a9d*/;
    *(int*)(param_1 + 0x84) = ADDR_rpmsg_virtio_get_tx_buffer_wait_THUMB /*=0x85b0d*/;
    *(int*)(param_1 + 0x88) = ADDR_rpmsg_virtio_tx_enqueue_THUMB /*=0x710b5*/;
    *(int*)(param_1 + 0x8c) = ADDR_FUN_000859c2_THUMB /*=0x859c3*/;
    iVar4 = *(int*)(iVar6 + 0x18);
    if (iVar4 == 0) {
        if (param_6 == (int*)0) return (int)0xfffff82d;
        uVar1 = param_6[1];
        uVar3 = param_6[2];
        /* The firmware copies this descriptor in ascending word order with
         * one LDM/STM pair.  Keep that observable order even on a later
         * faulting path; ordinary stores may be freely reordered by C. */
        *(volatile int*)(param_1 + 0x94) = *param_6;
        *(volatile int*)(param_1 + 0x98) = uVar1;
        *(volatile int*)(param_1 + 0x9c) = uVar3;
    }
    {
        fn1_t fp = *(fn1_t*)((*(int*)(iVar6 + 0x20)) + 0x10);
        uVar1 = fp(iVar6);
    }
    *(int*)(param_2 + 0x10) = uVar1;
    *(int*)(param_2 + 0x14) = 0;
    *(unsigned char*)(param_1 + 0x90) = (unsigned char)((unsigned int)uVar1 & 1);
    if (iVar4 == 0) {
        iVar6 = param_5;
        if (*(char*)(param_6 + 2) != 0) iVar6 = param_5 + 0xc;
        *(int*)(param_1 + 0xb0) = iVar6;
        if (param_5 == 0) return (int)0xfffff82d;
        if (*(int*)(param_5 + 8) == 0) return (int)0xfffff82e;
        if (*(int*)(iVar6 + 8) == 0) return (int)0xfffff82e;
        local_38 = ((unsigned long)&rodata_f7c28) /*=0xf7c28*/;
        local_34 = ((unsigned long)&rodata_f7c2e) /*=0xf7c2e*/;
        local_30 = ADDR_rpmsg_virtio_rx_notify_THUMB /*=0x7118d*/;
        local_2c = ((unsigned long)&rodata_859b1) /*=0x859b1*/;
        *(int*)(param_1 + 0xa4) = **(int**)(param_2 + 0x2c);
        *(int*)(param_1 + 0xa8) = *(int*)(*(int*)(param_2 + 0x2c) + 0x18);
    }
    *(int*)(param_1 + 0xb4) = param_1 + 0xb4;
    *(int*)(param_1 + 0xb8) = param_1 + 0xb4;
    *(int**)(param_1 + 0xac) = param_4;
    iVar6 = virtio_create_virtqueues(*(int*)(param_1 + 0xa0), 0, 2, &local_38, &local_30);
    if (iVar6 != 0) return iVar6;
    virtqueue_ring_setup_flags(*(int*)(param_1 + 0xa8));
    *(int**)(**(int**)(param_2 + 0x2c) + 0x28) = param_4;
    *(int**)(*(int*)(*(int*)(param_2 + 0x2c) + 0x18) + 0x28) = param_4;
    if (iVar4 == 0) {
        local_24 = *(int*)(param_1 + 0x98);
        (void)local_24;
        for (uVar5 = 0; uVar5 < *(unsigned short*)(*(int*)(param_1 + 0xa4) + 0xa); uVar5 = uVar5 + 1) {
            iVar6 = rpmsg_virtio_shm_pool_get_buffer(param_5, *(int*)(param_1 + 0x98));
            if (iVar6 == 0) return (int)0xfffff82e;
            uVar2 = (unsigned int)iVar6 - (unsigned int)(*param_4);
            if ((unsigned int)param_4[2] <= uVar2) uVar2 = 0xffffffff;
            local_28 = iVar6;
            metal_io_block_set(param_4, uVar2, 0, *(int*)(param_1 + 0x98));
            iVar6 = virtqueue_add_buffer(*(int*)(param_1 + 0xa4), &local_28, 0, 1, iVar6);
            if (iVar6 != 0) return iVar6;
        }
        *(int*)param_1 = param_1;
        *(int*)(param_1 + 4) = param_1;
        if (*(char*)(param_1 + 0x90) == 0) goto LAB_00071498;
    } else {
        *(int*)param_1 = param_1;
        *(int*)(param_1 + 4) = param_1;
        if (*(char*)(param_1 + 0x90) == 0) return 0;
    }
    rpmsg_register_endpoint(param_1, param_1 + 8, ((unsigned long)&rodata_f7c34) /*=0xf7c34*/, 0x35, 0x35, ADDR_FUN_00085a04_THUMB /*=0x85a05*/, 0);
    if (iVar4 != 0) return 0;
LAB_00071498:
    {
        fn2_t fp2 = *(fn2_t*)((*(int*)(*(int*)(param_1 + 0xa0) + 0x20)) + 0xc);
        fp2(*(int*)(param_1 + 0xa0), 4);
    }
    return 0;
}
