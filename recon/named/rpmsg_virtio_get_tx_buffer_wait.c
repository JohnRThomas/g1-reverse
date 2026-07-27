/* readable reconstruction; identity: FUN_00085b0c @ 0x00085b0c
 * public-name: rpmsg_virtio_get_tx_buffer_wait
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   k_sleep                                  <= FUN_00074844 @ 0x00074844
 *   virtqueue_get_buffer                     <= FUN_00085734 @ 0x00085734
 *   mutex_lock_wait_forever_dup              <= FUN_000859b6 @ 0x000859b6
 *   rpmsg_virtio_shm_pool_get_buffer         <= FUN_00085aee @ 0x00085aee
 *   rpmsg_virtio_get_tx_buffer_wait          <= FUN_00085b0c @ 0x00085b0c
 */
/* Reconstructed FUN_00085b0c @ 0x85b0c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int32_t k_sleep(k_timeout_t);
extern int* virtqueue_get_buffer(uint32_t,int*,void*,uint32_t,int);
extern void mutex_lock_wait_forever_dup(int);
extern int* rpmsg_virtio_shm_pool_get_buffer(unsigned int, unsigned int);
extern unsigned long process_sync_buffer(unsigned int, ...);
typedef int (*fp0)(void);
int* rpmsg_virtio_get_tx_buffer_wait(int param_1, int* param_2, int param_3){
    int iVar5=param_1;
    uint32_t uStack_24=(uint32_t)param_2;
    int iVar1=(*(volatile fp0*)(*(volatile int*)(*(volatile int*)(param_1+0xa0)+0x20)+8))();
    if((iVar1<<0x1d)>=0) return 0;
    if(param_3!=0) param_3=15000;
    int addr58=param_1+0x58;
    int iVar4; int* piVar3;
    while(1){
        mutex_lock_wait_forever_dup(addr58);
        piVar3=*(int* volatile*)(param_1+0xb4);
        iVar4=*(volatile int*)(*(volatile int*)(param_1+0xa0)+0x18);
        if(piVar3!=(int*)(param_1+0xb4) && piVar3!=0) break;
        if(iVar4==0){
            piVar3=virtqueue_get_buffer(*(volatile uint32_t*)(param_1+0xa8),param_2,(uint8_t*)&uStack_24+2,*(volatile uint32_t*)(param_1+0xa0),iVar5);
            if(piVar3!=0) goto L6a;
            if(*(volatile int16_t*)(*(volatile int*)(param_1+0xa8)+0x24)==0) goto L90;
            piVar3=rpmsg_virtio_shm_pool_get_buffer(*(volatile uint32_t*)(param_1+0xb0),*(volatile uint32_t*)(param_1+0x94));
            *param_2=*(volatile int*)(param_1+0x94);
            uStack_24=uStack_24&0xffff;
            process_sync_buffer(addr58);
            if(piVar3!=0) goto L70;
        } else {
L90:
            process_sync_buffer(addr58);
        }
        if(param_3==0) return 0;
        k_sleep(0x21,0);
        param_3=param_3-1;
    }
    {
        int p3_0=*(volatile int*)piVar3;
        int p3_1=*(volatile int*)((int)piVar3+4);
        *(volatile int*)(p3_0+4)=p3_1;
        *(volatile int*)(p3_1)=p3_0;
        *(volatile int*)((int)piVar3)=(int)piVar3;
        *(volatile int*)((int)piVar3+4)=(int)piVar3;
        if(iVar4==0){ *param_2=*(volatile int*)(param_1+0x94); }
    }
L6a:
    process_sync_buffer(addr58);
L70:
    *(volatile int*)((int)piVar3+8)=(int)(uStack_24>>0x10);
    *param_2=*(volatile int*)param_2-0x10;
    return (int*)((int)piVar3+0x10);
}
