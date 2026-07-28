/* Reconstructed FUN_00034944 @ 0x34944  (parity: 300/300 trials, PROVEN) */

extern void FUN_0003441c(void);
extern void FUN_00086c78(int a, int b, int c);
extern void FUN_00035744(void);

void FUN_00034944(void)
{
    *(volatile unsigned char *)0x2001a22bUL = 10;
    *(volatile unsigned char *)0x2001a22aUL = 0;
    *(volatile unsigned char *)0x2001a229UL = 0;
    /* shipped 0x34946 `movs r0,#0' sets the memset fill BEFORE the call;
     * FUN_0003441c/msg_content_decrement_timer is void and never writes r0. */
    FUN_0003441c();
    FUN_00086c78(0x20007dac, 0, 0x2210);
    FUN_00035744();
}

