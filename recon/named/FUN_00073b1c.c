/* named: FUN_00073b1c */
/* globals referenced:
//   0x2000b448  g_zephyr_kernel              
*/
/* Reconstructed FUN_00073b1c @ 0x73b1c  (parity: 300/300 trials, PROVEN) */

extern int z_spin_lock_valid(unsigned a);
extern int z_spin_unlock_valid(unsigned a);
extern void z_spin_lock_set_owner(unsigned a);
extern void assert_post_action(unsigned a, unsigned b);
extern void printk(unsigned a, unsigned b, unsigned c, unsigned d);
void FUN_00073b1c(void){
    unsigned r4;
    __asm__ volatile("mrs %0, basepri" : "=r"(r4));
    unsigned tmp = 0x20;
    __asm__ volatile("msr basepri_max, %0" :: "r"(tmp) : "memory");
    __asm__ volatile("isb");
    int iVar3 = z_spin_lock_valid(0x2000b490);
    if (iVar3 == 0){
        printk(0x00099cbd,0x000f0920,0x000f08c7,0x72);
        printk(0x000f0935,0x2000b490,0,0);
        assert_post_action(0x000f08c7,0x72);
        return;
    }
    z_spin_lock_set_owner(0x2000b490);
    unsigned ipsr;
    __asm__ volatile("mrs %0, ipsr" : "=r"(ipsr));
    if (ipsr != 0){
        printk(0x00099cbd,0x000f801f,0x000f84f7,0xfd);
        printk(0x000f53ff,0,0,0);
        assert_post_action(0x000f84f7,0xfd);
        return;
    }
    int r2 = *(volatile int*)(0x2000b448 + 8);
    unsigned char cVar1 = *(volatile unsigned char*)(r2 + 0xf);
    if (cVar1 == 1){
        printk(0x00099cbd,0x000f8522,0x000f84f7,0xfe);
        printk(0x000f53ff,0,0,0);
        assert_post_action(0x000f84f7,0xfe);
        return;
    }
    *(volatile unsigned char*)(r2 + 0xf) = (unsigned char)(cVar1 - 1);
    int iv = z_spin_unlock_valid(0x2000b490);
    if (iv == 0){
        printk(0x00099cbd,0x000f08f4,0x000f08c7,0xf0);
        printk(0x000f090b,0x2000b490,0,0);
        assert_post_action(0x000f08c7,0xf0);
        return;
    }
    __asm__ volatile("msr basepri, %0" :: "r"(r4) : "memory");
    __asm__ volatile("isb");
    return;
}

