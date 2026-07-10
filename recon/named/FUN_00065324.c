/* named: FUN_00065324 */
/* Reconstructed FUN_00065324 @ 0x65324  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void assert_post_action(void);
extern void printk(void);
extern void FUN_00065000(void);

void FUN_00065324(int param_1, int param_2)
{
    if (*(volatile uint8_t*)0x2000b320 == 0) {
        printk();
        assert_post_action();
    }
    FUN_00065000();
}

