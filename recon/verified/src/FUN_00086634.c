/* Reconstructed FUN_00086634 @ 0x86634  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include <cmsis_gcc.h>

extern void FUN_000501d4(void);
void FUN_00086634(int param_1) {
    if (param_1 == 0) {
        unsigned int ipsr = __get_IPSR();
        if (ipsr == 0) {
            FUN_000501d4();
            return;
        }
    }
    __set_BASEPRI((unsigned int)param_1);
    __ISB();
}
