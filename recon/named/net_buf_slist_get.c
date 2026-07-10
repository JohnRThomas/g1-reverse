/* named: net_buf_slist_get */
/* Reconstructed net_buf_slist_get @ 0x5f148  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef uint32_t u32;
extern void printk(u32,u32,...);
extern void assert_post_action(u32,u32);
extern int z_spin_lock_valid(u32);
extern void z_spin_lock_set_owner(u32);
extern int z_spin_unlock_valid(u32);
static inline u32 rd_basepri(void){u32 v;__asm__ volatile("mrs %0, basepri":"=r"(v));return v;}
static inline void wr_basepri_max(u32 v){__asm__ volatile("msr basepri_max, %0"::"r"(v):"memory");}
static inline void wr_basepri(u32 v){__asm__ volatile("msr basepri, %0"::"r"(v):"memory");}
static inline void isb_(void){__asm__ volatile("isb");}
u32* net_buf_slist_get(u32* param_1){
    u32 uVar4, uVar6;
    if(param_1 == 0){
        printk(0x00099cbd, 0x000f3630, 0x000f539a, 0x1ba);
        uVar4=0x1ba; uVar6=0x000f539a;
    } else {
        uVar6 = rd_basepri();
        wr_basepri_max(0x20);
        isb_();
        int iVar3 = z_spin_lock_valid(0x2000b004);
        if(iVar3==0){
            printk(0x00099cbd, 0x000f0920, 0x000f08c7, 0x72);
            printk(0x000f0935, 0x2000b004);
            uVar4=0x72; uVar6=0x000f08c7;
        } else {
            z_spin_lock_set_owner(0x2000b004);
            u32* puVar5 = (u32*)*param_1;
            if(puVar5 != 0){
                uVar4 = *puVar5;
                *param_1 = uVar4;
                if(puVar5 == (u32*)param_1[1]) param_1[1] = uVar4;
            }
            iVar3 = z_spin_unlock_valid(0x2000b004);
            if(iVar3!=0){
                wr_basepri(uVar6);
                isb_();
                return puVar5;
            }
            printk(0x00099cbd, 0x000f08f4, 0x000f08c7, 0xf0);
            printk(0x000f090b, 0x2000b004);
            uVar4=0xf0; uVar6=0x000f08c7;
        }
    }
    assert_post_action(uVar6, uVar4);
    return 0;
}

