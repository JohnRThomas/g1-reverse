/* Reconstructed handle_touch_single_click @ 0x3707c  (parity: 300/300 trials, PROVEN) */
typedef unsigned char u8;

extern void sub_1672c(unsigned int action);

int handle_touch_single_click(unsigned int param_1)
{
    unsigned int action = param_1 & 0xffu;
    *(volatile u8 *)(0x20004950UL + 1) = action;
    *(volatile u8 *)0x2001b816UL = action;
    sub_1672c(action);
    return 0;
}
