/* named: st25dv_mailbox_set_enabled */
/* globals referenced:
//   0x20007a44  g_st25dv_dev                 
*/
/* Reconstructed st25dv_mailbox_set_enabled @ 0x24cc8  (parity: 300/300 trials, PROVEN) */

extern void read_bool_attr_0x2004(int a, void *b);
extern void FUN_0007c99e(int a, void *b);

char st25dv_mailbox_set_enabled(int param_1)
{
    char local_19;
    int local_18;
    int local_14;

    local_19 = 0;
    read_bool_attr_0x2004(*(volatile int *)0x20007a44UL, &local_19);
    if (local_19 == 0) {
        if (param_1 == 0) goto LAB_00024cf4;
        local_14 = 0;
        local_18 = 0;
    } else {
        if ((local_19 != 1) || (param_1 != 0)) goto LAB_00024cf4;
        local_18 = 0x12345678;
        local_14 = 0x12345678 + 0xf00000;
    }
    FUN_0007c99e(*(volatile int *)0x20007a44UL, &local_18);
LAB_00024cf4:
    read_bool_attr_0x2004(*(volatile int *)0x20007a44UL, &local_19);
    return local_19;
}

