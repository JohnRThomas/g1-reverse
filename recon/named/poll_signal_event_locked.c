/* readable reconstruction; identity: FUN_000757b0 @ 0x000757b0
 * public-name: poll_signal_event_locked
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_spin_lock_valid                        <= FUN_00072040 @ 0x00072040
 *   z_spin_unlock_valid                      <= FUN_0007205c @ 0x0007205c
 *   z_spin_lock_set_owner                    <= FUN_00072078 @ 0x00072078
 *   z_reschedule                             <= FUN_000739f0 @ 0x000739f0
 *   poll_signal_event_locked                 <= FUN_000757b0 @ 0x000757b0
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   signal_poll_event                        <= FUN_000867da @ 0x000867da
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f08c7                             @ 0x000f08c7
 *   rodata_f08f4                             @ 0x000f08f4
 *   rodata_f090b                             @ 0x000f090b
 *   rodata_f0920                             @ 0x000f0920
 *   rodata_f0935                             @ 0x000f0935
 *   poll_spinlock                            @ 0x2000b4a0
 */
/* Reconstructed FUN_000757b0 @ 0x757b0  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include <cmsis_gcc.h>
typedef uint32_t u32;
extern void printk(u32,u32,...);
extern void assert_post_action(u32,u32);
extern int z_spin_lock_valid(u32);
extern void z_spin_lock_set_owner(u32);
extern int z_spin_unlock_valid(u32);
extern u32 signal_poll_event(void*,u32);
extern void z_reschedule(u32,u32);
static inline u32 rd_basepri(void){return __get_BASEPRI();}
static inline void wr_basepri_max(u32 v){__set_BASEPRI_MAX(v);}
static inline void wr_basepri(u32 v){__set_BASEPRI(v);}
static inline void isb_(void){__ISB();}
u32 poll_signal_event_locked(int* param_1, int param_2){
    u32 uVar7 = rd_basepri();
    wr_basepri_max(0x20);
    isb_();
    int iVar3 = z_spin_lock_valid(0x2000b4a0);
    if(iVar3 != 0){
        z_spin_lock_set_owner(0x2000b4a0);
        int* piVar4 = (int*)*param_1;
        param_1[3] = param_2;
        param_1[2] = 1;
        u32 uVar6;
        if(param_1 == piVar4){
            iVar3 = z_spin_unlock_valid(0x2000b4a0);
            if(iVar3 == 0){
                printk(0x00099cbd, 0x000f08f4, 0x000f08c7, 0xf0);
                printk(0x000f090b, 0x2000b4a0);
                assert_post_action(0x000f08c7, 0xf0);
                return 0;
            }
            wr_basepri(uVar7);
            isb_();
            uVar6 = 0;
        } else {
            int iVar3b = *piVar4;
            int* piVar5 = (int*)piVar4[1];
            *piVar5 = iVar3b;
            *(int**)(iVar3b+4) = piVar5;
            piVar4[0] = 0;
            piVar4[1] = 0;
            uVar6 = signal_poll_event(piVar4, 1);
            z_reschedule(0x2000b4a0, uVar7);
        }
        return uVar6;
    }
    printk(0x00099cbd, 0x000f0920, 0x000f08c7, 0x72);
    printk(0x000f0935, 0x2000b4a0);
    assert_post_action(0x000f08c7, 0x72);
    return 0;
}
