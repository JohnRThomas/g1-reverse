/* named: FUN_00073518 */
/* Reconstructed FUN_00073518 @ 0x73518  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef uint32_t u32;
extern void printk(u32,u32,...);
extern void assert_post_action(u32,u32);
extern int z_spin_lock_valid(u32);
extern void z_spin_lock_set_owner(u32);
extern int z_spin_unlock_valid(u32);
extern void unschedule_locked(int);
extern u32 cancel_async_locked(int);
static inline u32 rd_basepri(void){u32 v;__asm__ volatile("mrs %0, basepri":"=r"(v));return v;}
static inline void wr_basepri_max(u32 v){__asm__ volatile("msr basepri_max, %0"::"r"(v):"memory");}
static inline void wr_basepri(u32 v){__asm__ volatile("msr basepri, %0"::"r"(v):"memory");}
static inline void isb_(void){__asm__ volatile("isb");}
u32 FUN_00073518(int param_1, u32 param_2, u32 param_3, u32 param_4){
    u32 uVar4, uVar5;
    if(param_1==0){
        printk(0x00099cbd, 0x000f82df, 0x000f820f, 0x400, param_4);
        uVar4=0x400; uVar5=0x000f820f;
    } else {
        uVar5 = rd_basepri();
        wr_basepri_max(0x20);
        isb_();
        int iVar3 = z_spin_lock_valid(0x2000b480);
        if(iVar3==0){
            printk(0x00099cbd, 0x000f0920, 0x000f08c7, 0x72, param_4);
            printk(0x000f0935, 0x2000b480);
            uVar4=0x72; uVar5=0x000f08c7;
        } else {
            z_spin_lock_set_owner(0x2000b480);
            unschedule_locked(param_1);
            uVar4 = cancel_async_locked(param_1);
            iVar3 = z_spin_unlock_valid(0x2000b480);
            if(iVar3!=0){
                wr_basepri(uVar5);
                isb_();
                return uVar4;
            }
            printk(0x00099cbd, 0x000f08f4, 0x000f08c7, 0xf0);
            printk(0x000f090b, 0x2000b480);
            uVar4=0xf0; uVar5=0x000f08c7;
        }
    }
    assert_post_action(uVar5, uVar4);
    return 0;
}

