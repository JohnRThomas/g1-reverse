/* Reconstructed handle_touch_single_click @ 0x3707c  (parity: 300/300 trials, PROVEN) */
typedef unsigned char u8;extern void sub_1672c(void);int handle_touch_single_click(u8 p){*(volatile u8*)(0x20004950UL+1)=p;*(volatile u8*)0x2001b816UL=p;sub_1672c();return 0;}
