/* named: bt_keys_foreach_type */
/* globals referenced:
//   0x2000af4c  bt_keys_pool                 
*/
/* Reconstructed bt_keys_foreach_type @ 0x5e758  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef void (*fnptr)(unsigned int, unsigned int);
extern void assert_post_action(void);
extern void printk(void);

void bt_keys_foreach_type(unsigned short param_1, fnptr param_2, unsigned int param_3)
{
    if (param_2 == 0) {
        printk();
        assert_post_action();
        return;
    }
    uintptr_t base = 0x2000af4cUL;
    unsigned short m1 = *(volatile unsigned short*)(base + 0xe);
    if ((m1 & param_1) != 0) {
        param_2((unsigned int)base, param_3);
    }
    unsigned short m2 = *(volatile unsigned short*)(base + 0x6a);
    if ((m2 & param_1) != 0) {
        param_2(0x2000afa8UL, param_3);
        return;
    }
}
