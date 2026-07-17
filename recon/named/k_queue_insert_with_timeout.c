/* readable reconstruction; identity: FUN_0005eeb4 @ 0x0005eeb4
 * public-name: k_queue_insert_with_timeout
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   k_queue_insert_with_timeout              <= FUN_0005eeb4 @ 0x0005eeb4
 *   z_spin_lock_valid                        <= FUN_00072040 @ 0x00072040
 *   z_spin_unlock_valid                      <= FUN_0007205c @ 0x0007205c
 *   z_spin_lock_set_owner                    <= FUN_00072078 @ 0x00072078
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   k_queue_prepend                          <= FUN_00086518 @ 0x00086518
 *   sys_timepoint_calc                       <= FUN_0008669c @ 0x0008669c
 *   sys_timepoint_timeout                    <= FUN_000866e4 @ 0x000866e4
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f08c7                             @ 0x000f08c7
 *   rodata_f08f4                             @ 0x000f08f4
 *   rodata_f090b                             @ 0x000f090b
 *   rodata_f0920                             @ 0x000f0920
 *   rodata_f0935                             @ 0x000f0935
 *   rodata_f539a                             @ 0x000f539a
 *   rodata_f53e9                             @ 0x000f53e9
 *   rodata_f53ee                             @ 0x000f53ee
 *   rodata_f53ff                             @ 0x000f53ff
 *   acl_tx_pool                              @ 0x20003a7c
 */
/* Reconstructed FUN_0005eeb4 @ 0x5eeb4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int z_spin_lock_valid(int);
extern int z_spin_unlock_valid(int);
extern void z_spin_lock_set_owner(int);
extern int FUN_000727ac(int,int,int,int);
extern void assert_post_action(uint32_t,uint32_t);
extern void printk(uint32_t,...);
extern void k_queue_prepend(int,int);
extern void sys_timepoint_calc(void *);
extern void sys_timepoint_timeout(void *,int,int,unsigned);

int k_queue_insert_with_timeout(int param_1, unsigned param_2, int param_3, int param_4)
{
    uint32_t frame[4] = {(uint32_t)param_1,param_2,(uint32_t)param_3,param_2};
    unsigned local_24 = param_2;
    int r4 = 0;
    int iVar6;
    unsigned uVar_h, uVar2, uVar1;

    sys_timepoint_calc(frame);
    if (param_1 == 0) {
        printk(0x99cbdu,0xf53e9u,0xf539au,0xf8u);
        assert_post_action(0xf539au,0xf8u);
        goto CONTINUE_AFTER_FATAL;
    }
    {
        int iVar6b = z_spin_lock_valid(param_1 + 0x1c);
        if (iVar6b == 0) {
            printk(0x99cbdu,0xf0920u,0xf08c7u,0x72u);
            printk(0xf0935u,param_1 + 0x1c);
            assert_post_action(0xf08c7u,0x72u);
            goto CONTINUE_AFTER_FATAL;
        }
    }
CONTINUE_AFTER_FATAL:
    z_spin_lock_set_owner(param_1 + 0x1c);
    uVar_h = *(volatile uint16_t*)(param_1 + 0x22);
    if (uVar_h == 0) {
        int t = z_spin_unlock_valid(param_1 + 0x1c);
        if (t == 0) goto EF40;
        r4 = FUN_000727ac(param_1,0,param_3,param_4);
        if (r4 != 0) goto EF60;
        return 0;
    } else {
        uVar2 = *(volatile uint16_t*)(param_1 + 0x20);
        if (uVar2 <= uVar_h) goto EFA0;
        r4 = FUN_000727ac(param_1,0,0,0);
        if (r4 == 0) goto EFA0;
        {
            int t = z_spin_unlock_valid(param_1 + 0x1c);
            if (t == 0) goto EF40;
            goto EF60;
        }
    }
EFA0:
    uVar1 = *(volatile uint16_t*)(param_1 + 0x22);
    *(volatile uint16_t*)(param_1 + 0x22) = (uint16_t)(uVar1 - 1);
    {
        int t = z_spin_unlock_valid(param_1 + 0x1c);
        if (t == 0) goto EF40;
    }
    {
        unsigned p20 = *(volatile uint16_t*)(param_1 + 0x20);
        unsigned mul = ((unsigned)*(volatile uint8_t*)(param_1 + 0x24) + 0x1b) & 0xfffffffc;
        int d = ((int)(param_1 - 0x20003a7c)) >> 2;
        r4 = (int)((p20 - uVar1) * mul) + *(volatile int*)(param_1 + 0x30);
        *(volatile int8_t*)(r4 + 10) = (int8_t)((uint32_t)0xc4ec4ec5 * (uint32_t)d);
        *(volatile uint8_t*)(r4 + 0xb) = *(volatile uint8_t*)(param_1 + 0x24);
    }
    goto EF60;
EF60:
    {
        unsigned r5v = local_24;
        if (r5v == 0) {
            *(volatile int*)(r4 + 0x14) = 0;
            goto EF2E;
        }
        sys_timepoint_timeout(frame,0,frame[0],frame[1]);
        {
            unsigned idx = *(volatile uint8_t*)(r4 + 0xa);
            int p = *(volatile int*)(0x34 * idx + 0x20003a7c + 0x2c);
            int p2 = *(volatile int*)p;
            int fn = *(volatile int*)p2;
            iVar6 = ((int(*)(int,int,int,int))(intptr_t)fn)(r4, (int)(intptr_t)&local_24, param_1, param_2);
            *(volatile int*)(r4 + 0x14) = iVar6;
            if (iVar6 == 0) {
                k_queue_prepend(0x20003a7c + 0x34 * *(volatile uint8_t*)(r4 + 0xa),r4);
                return 0;
            }
            if (r5v <= local_24) goto EF2E;
            printk(0x99cbdu,0xf53eeu,0xf539au,0x14fu);
            printk(0xf53ffu);
            assert_post_action(0xf539au,0x14fu);
            goto CONTINUE_AFTER_FATAL;
        }
    }
EF2E:
    *(volatile int*)(r4 + 4) = 0;
    *(volatile uint16_t*)(r4 + 8) = 1;
    *(volatile uint16_t*)(r4 + 0x10) = 0;
    *(volatile uint16_t*)(r4 + 0x12) = (uint16_t)local_24;
    *(volatile int*)(r4 + 0xc) = *(volatile int*)(r4 + 0x14);
    return r4;
EF40:
    printk(0x99cbdu,0xf08f4u,0xf08c7u,0xf0u);
    printk(0xf090bu,param_1 + 0x1c);
    assert_post_action(0xf08c7u,0xf0u);
    goto CONTINUE_AFTER_FATAL;
}
