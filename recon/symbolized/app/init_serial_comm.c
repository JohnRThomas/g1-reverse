#include "g1_app_symbols.h"
/* named: init_serial_comm */
/* Reconstructed init_serial_comm @ 0x33340  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned int a);
extern int FUN_00033088(unsigned int a);
extern int process_pt_data(void);
extern int init_serial_port(void);
extern void FUN_00074844(unsigned int a, unsigned int b);

int init_serial_comm(void)
{
    int iVar1;

    iVar1 = init_serial_port();
    if (iVar1 == 0) {
        iVar1 = FUN_00033088(((uintptr_t)&tbl_87b30) /*=0x87bc0*/);
        if (iVar1 == 0) {
            iVar1 = process_pt_data();
            if (iVar1 != 0) {
                iVar1 = -3;
            }
        } else {
            DEBUG_PRINT("init_serial_comm is failed\n" /*=0xa7907*/);
            FUN_00074844(0x4000, 0);
            iVar1 = -2;
        }
    } else {
        iVar1 = -1;
    }
    return iVar1;
}

