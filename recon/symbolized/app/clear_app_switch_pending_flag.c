#include "g1_app_symbols.h"
/* named: clear_app_switch_pending_flag */
/* Reconstructed clear_app_switch_pending_flag @ 0x7dada  (parity: 300/300 trials, PROVEN) */

extern int get_device_info(void);
extern unsigned int get_current_burial_point_type(void);

void clear_app_switch_pending_flag(void)
{
    int iVar1;
    unsigned int uVar2;
    iVar1 = get_device_info();
    if ((*(volatile unsigned char*)(iVar1 + 0x10ac) != 0) && ((uVar2 = get_current_burial_point_type()), uVar2 < 7)) {
        iVar1 = get_device_info();
        *(volatile unsigned char*)(iVar1 + 0x10ac) = 0;
    }
}

